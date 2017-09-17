#include <vector>
#include <QMessageBox>
#include "guestwindow.h"
#include "ui_guestwindow.h"
#include "guest.h"
#include "person.h"
#include "staticdata.h"
#include "tools.h"
#include "dish.h"
#include "item.h"
#include "tableitem.h"
#include "table.h"
#include "msg.h"
#include "aboutmewidget.h"
#include "order.h"
#include "orderitem.h"
#include "emptyresult.h"

GuestWindow::GuestWindow(const QString& user, QWidget *parent) :
    QMainWindow(parent),
    guest("", ""),
    orderedSum(0),
    checkedOut(true),
    currentOrder(NULL),
    rateClerkItem(NULL),
    ui(new Ui::GuestWindow)
{
    ui->setupUi(this);
//    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
//    ui->tabWidget->tabBar()->setExpanding(true);
//    QLabel *fillColor = new QLabel(this);
//    fillColor->setGeometry(0, 360, 80, 800);
//    fillColor->setText("");
//    fillColor->setStyleSheet("background-color: rgb(4, 64, 160);");
    ui->tabWidget->tabBar()->setCursor(QCursor(Qt::PointingHandCursor));
    try {
        guest = StaticData::getGuestByPhone(user);
    } catch (EmptyResult) {
        StaticData::db->doQuery("person", "name, password, tableID", "phone = \"" + user + "\"");
        if(StaticData::db->getResultList()[0][2] != "NULL")
            guest = Guest(user,
                          StaticData::db->getResultList()[0][0],
                    StaticData::db->getResultList()[0][1],
                    StaticData::db->getResultList()[0][2].toInt());
        else
            guest = Guest(user,
                          StaticData::db->getResultList()[0][0],
                    StaticData::db->getResultList()[0][1]);
    }
    StaticData::queryMsg(guest.getPhone());
    ui->inboxList->setColumnWidth(0, 150);
    ui->inboxList->setColumnWidth(1, 150);
    ui->inboxList->setColumnWidth(2, 850);
    ui->outboxList->setColumnWidth(0, 150);
    ui->outboxList->setColumnWidth(1, 150);
    ui->outboxList->setColumnWidth(2, 850);
    aboutMe = new AboutMeWidget(&guest, this, ui->selfTab);
    aboutMe->show();
    this->show();
    connect(ui->sendWaterButton, &QPushButton::clicked, this, [this] {sendMsg("Water");});
    connect(ui->sendNapkinButton, &QPushButton::clicked, this, [this] {sendMsg("Napkin");});
    connect(ui->sendQuicklyButton, &QPushButton::clicked, this, [this] {sendMsg("Quickly");});
    connect(this, &GuestWindow::closeEvent, this, [this] {
        //viewErrInfo("XXX");
        StaticData::insertGuest(guest, 2);
    });
    viewTableList();
    viewDishList();
    viewCartList();
    viewOrderList();
    viewMsgList();
    ui->tabWidget->setCurrentIndex(0);
    ui->title->setText("   Select Table");
}

GuestWindow::~GuestWindow()
{
    clearPointerList(tableItem);
    clearPointerList(dishItem);
    clearPointerList(cartItem);
    clearPointerList(orderItem);
    delete aboutMe;
    delete ui;
}
//QItemDelegate

void GuestWindow::viewTableList() {
    clearPointerList(tableItem);
    for(unsigned int i = 0; i < StaticData::getTableList().size(); i ++) {
        if(i % 3 == 0 && ui->tableList->rowCount() <= (int)i/3)
            ui->tableList->setRowCount(ui->tableList->rowCount() + 1);
        int row = i / 3;
        int col = i % 3;
        TableItem* table = new TableItem(StaticData::getTableList()[i], ui->tableList);
        connect(table, SIGNAL(tableSelected(int)), this, SLOT(setSelectedTable(int)));
        ui->tableList->setCellWidget(row, col, table);
        if (StaticData::getTableList()[i].getFreeSeats() == 0)
            table->setEnabled(false);
        tableItem.push_back(table);
    }
    if(guest.getTable() > 0) {
        selectedTable = guest.getTable();
        ui->selectedTable->setText(QString("Selected Table: No. %1").arg(selectedTable));
        ui->submitTableButton->setEnabled(false);
    }
    ui->tableList->setEnabled(ui->submitTableButton->isEnabled());
}

void GuestWindow::viewDishList() {
    clearPointerList(dishItem);
    ui->dishList->setRowCount(0);
    for(unsigned int i = 0; i < StaticData::getDishList().size(); i ++) {
        int row = ui->dishList->rowCount();
        ui->dishList->setRowCount(row + 1);
        Item* item = new Item(guest, StaticData::getDishList()[i], "dishList", ui->dishList);
        ui->dishList->setCellWidget(row, 0, item);
        dishItem.push_back(item);
    }
}

void GuestWindow::viewCartList() {
    clearPointerList(cartItem);
    ui->cartList->setRowCount(0);
    for(unsigned int i = 0; i < guest.getOrderedDishList().size(); i ++) {
        int row = ui->cartList->rowCount();
        ui->cartList->setRowCount(row + 1);
        Item* item = new Item(guest, guest.getOrderedDishList()[i], "cartList", ui->cartList);
        connect(item, SIGNAL(dishNumChanged(const QString&, int)), this, SLOT(setDishNum(const QString&, int)));
        ui->cartList->setCellWidget(row, 0, item);
        cartItem.push_back(item);
    }
    updateSum();
    if(guest.getSumInCart() == 0)
        ui->submitButton->setEnabled(false);
    else
        ui->submitButton->setEnabled(true);
}

void GuestWindow::viewOrderList() {
    ui->rateClerkNote->hide();
    if (rateClerkItem != NULL) {
        delete rateClerkItem;
        rateClerkItem = NULL;
    }
    //ui->viewOrderButton->setText("Refresh");
    //ui->viewOrderButton->setGeometry(1010, 790, 80, 50);
    ui->refreshOrderInfoButton->hide();
    ui->checkOutButton->hide();
    ui->backButton->hide();
    ui->viewOrderButton->show();
    clearPointerList(dishInOrderItem);
    clearPointerList(orderItem);
    ui->orderList->setRowCount(0);
    //check each order, if they are active, show them first;
    vector<bool> isFinished;
    for(unsigned int i = 0; i < StaticData::getOrderList().size(); i ++) {
        if(StaticData::getOrderList()[i].getOrderer() == guest.getPhone()) {
            OrderItem* item = new OrderItem(&StaticData::getOrderList()[i], ui->orderList);
            orderItem.push_back(item);
            isFinished.push_back(StaticData::getOrderList()[i].checkStatus() == 5);
        }
    }
    for(unsigned int i = 0; i < isFinished.size(); i ++)
        if(!isFinished[i]) {
            connect(orderItem[i], SIGNAL(orderClicked(Order*)), this, SLOT(viewDishInOrderList(Order*)));
            ui->orderList->setRowCount(ui->orderList->rowCount() + 1);
            ui->orderList->setCellWidget(ui->orderList->rowCount() - 1, 0, orderItem[i]);
            checkedOut = false;
            orderItem[i]->show();
            checkedOut = false;
        }
    for(unsigned int i = 0; i < isFinished.size(); i ++)
        if(isFinished[i]) {
            connect(orderItem[i], SIGNAL(orderClicked(Order*)), this, SLOT(viewDishInOrderList(Order*)));
            ui->orderList->setRowCount(ui->orderList->rowCount() + 1);
            ui->orderList->setCellWidget(ui->orderList->rowCount() - 1, 0, orderItem[i]);
            orderItem[i]->show();
        }
}

void GuestWindow::viewDishInOrderList(Order* order) {
    currentOrder = order;
    //ui->viewOrderButton->setText("Back");
    //ui->viewOrderButton->setGeometry(730, 790, 80, 50);
    ui->viewOrderButton->hide();
    ui->refreshOrderInfoButton->show();
    ui->checkOutButton->show();
    ui->backButton->show();
    clearPointerList(orderItem);
    clearPointerList(dishInOrderItem);
    ui->orderList->setRowCount(0);
    for(unsigned int i = 0; i < order->getOrderDishes().size(); i ++) {
        Item* item = new Item(guest, StaticData::getOrderedDishByID(order->getOrderDishes()[i]), "orderList", ui->orderList);
        connect(item, &Item::refreshRequested, this, [this] {viewDishInOrderList(currentOrder);});
        ui->orderList->setRowCount(ui->orderList->rowCount() + 1);
        ui->orderList->setCellWidget(ui->orderList->rowCount() - 1, 0, item);
        dishInOrderItem.push_back(item);
        item->show();
    }
    ui->checkOutButton->setEnabled(order->checkStatus() == 4);
    if (order->checkStatus() == 6) {
        //Rate& rateClerkInfo = StaticData::getRateBySubjectAndObject(guest.getPhone(), currentOrder->getClerk());
        ui->rateClerkNote->setText("You have rated your clerk: " + currentOrder->getClerk());
        ui->rateClerkNote->show();
        if (rateClerkItem != NULL) {
            delete rateClerkItem;
            rateClerkItem = NULL;
        }
        rateClerkItem = new RateItem(ui->orderTab);
        rateClerkItem->setGeometry(360, 745, 150, 30);
        rateClerkItem->setRate(currentOrder->getRate());
        rateClerkItem->show();
    }
    else if (order->checkStatus() == 5){
        ui->rateClerkNote->setText("Please rate your clerk: " + currentOrder->getClerk());
        ui->rateClerkNote->show();
        if (rateClerkItem != NULL) {
            delete rateClerkItem;
            rateClerkItem = NULL;
        }
        rateClerkItem = new RateItem(ui->orderTab);
        rateClerkItem->setGeometry(360, 745, 150, 30);
        connect(rateClerkItem, SIGNAL(rateSet(double)), this, SLOT(rateClerk(double)));
        rateClerkItem->show();
    }
}

void GuestWindow::viewMsgList() {
    ui->inboxList->setRowCount(0);
    vector<Msg*> msgReceived = StaticData::getMsgByReceiver(guest.getPhone());
    for(unsigned int i = 0; i < msgReceived.size(); i ++) {
        int row = ui->inboxList->rowCount();
        ui->inboxList->setRowCount(row + 1);
        ui->inboxList->setItem(row, 0, new QTableWidgetItem((StaticData::getPersonNameByPhone(msgReceived[i]->getSender()))));
        ui->inboxList->setItem(row, 1, new QTableWidgetItem((msgReceived[i]->getDatetime())));
        ui->inboxList->setItem(row, 2, new QTableWidgetItem((msgReceived[i]->getMsg())));
    }
    ui->outboxList->setRowCount(0);
    vector<Msg*> msgSent = StaticData::getMsgBySender(guest.getPhone());
    for(unsigned int i = 0; i < msgSent.size(); i ++) {
        int row = ui->outboxList->rowCount();
        ui->outboxList->setRowCount(row + 1);
        ui->outboxList->setItem(row, 0, new QTableWidgetItem((msgSent[i]->getReceiver())));
        ui->outboxList->setItem(row, 1, new QTableWidgetItem((msgSent[i]->getDatetime())));
        ui->outboxList->setItem(row, 2, new QTableWidgetItem((msgSent[i]->getMsg())));
    }
}

void GuestWindow::setDishNum(const QString& dishID, int finalNum) {
    for(unsigned int i = 0; i < dishItem.size(); i ++)
        if(dishItem[i]->getDishID() == dishID) {
            dishItem[i]->setDishNumText(finalNum);
            break;
        }
    updateSum();
}

void GuestWindow::on_RefreshCart_clicked()
{
    viewCartList();
    viewOrderList();
}

void GuestWindow::rateClerk(double newRate) {
    try {
        currentOrder->rateClerk(newRate);
        StaticData::insertRate(Rate(QString("R%1%2%3%4").arg(getTimeUniform()).arg(guest.getPhone()).arg(currentOrder->getClerk()).arg(StaticData::getRateList().size()),
                                    newRate,
                                    guest.getPhone(),
                                    currentOrder->getClerk(),
                                    getTimeUniform()), 1);
        ui->rateClerkNote->setText("You have rated your clerk: " + currentOrder->getClerk());
    } catch (EmptyResult) {
        viewErrInfo("Operation failed, please retry later");
    }
}

void GuestWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0) {
        ui->title->setText("   Select Table");
    }
    else if(index == 2) {
        ui->title->setText("   View Cart");
        viewCartList();
        viewOrderList();
    }
    else if (index == 1) {
        ui->title->setText("   Select Dishes");
        viewDishList();
    }
    else if (index == 3) {
        ui->title->setText("   View Order");
    }
    else if (index == 4) {
        ui->title->setText("   Message Center");
    }
    else if (index == 5) {
        ui->title->setText("   About Me");
    }
}

void GuestWindow::updateSum() {
    orderedSum = guest.getSumInCart();
    ui->cartTotal->setText("￥" + QString().setNum(orderedSum));
    if(guest.getSumInCart() == 0)
        ui->submitButton->setEnabled(false);
    else
        ui->submitButton->setEnabled(true);
}

void GuestWindow::sendMsg(const QString &msg) {
    if (ui->submitTableButton->isEnabled()) {
        viewErrInfo("Please select a table before sending messages");
        return;
    }
    if (msg.length() == 0) {
        viewErrInfo("Empty message");
        return;
    }
    guest.sendMsg(QString("Table_%1").arg(guest.getTable()), msg);
    viewErrInfo("Success");
    viewMsgList();
}

void GuestWindow::setSelectedTable(int tableID) {
    selectedTable = tableID;
    ui->selectedTable->setText(QString("Selected Table: No. %1").arg(selectedTable));
    viewTableList();
}

void GuestWindow::on_submitButton_clicked()
{
    if(ui->submitTableButton->isEnabled()) {
        viewErrInfo("You haven't selected a table, please select one");
        return;
    }
    QString orderInfo = "Your order: \n\n";
    for (unsigned int i = 0; i < guest.getOrderedDishList().size(); i ++) {
        orderInfo += (guest.getOrderedDishList()[i].getName()) + "\n";
        orderInfo += "￥" + QString().setNum(guest.getOrderedDishList()[i].getPrice()) + " x " + QString().setNum(guest.getOrderedDishList()[i].getNum()) + " = ￥" + QString().setNum(guest.getOrderedDishList()[i].getPrice() * guest.getOrderedDishList()[i].getNum()) + "\n\n";
    }
    orderInfo += "Total: ￥" + QString().setNum(guest.getSumInCart()) + "\n\n Submit?";
    int reply = QMessageBox::question(NULL, "Confirm Order", orderInfo, QMessageBox::Yes, QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        guest.modifyTable(guest.getTable());
        guest.submitCart(ui->requestText->text());
        viewDishList();
        viewCartList();
        viewOrderList();
        ui->tabWidget->setCurrentIndex(3);
    }
    checkedOut = false;
}

void GuestWindow::on_submitTableButton_clicked()
{
    if(!guest.selectTable(StaticData::getTableByID(selectedTable))) {
        viewErrInfo(QString("No seats left for Table No. %1, please reselect.").arg(selectedTable));
        return;
    }
    ui->submitTableButton->setEnabled(false);
    viewTableList();
}

void GuestWindow::on_refreshTableButton_clicked()
{
    viewTableList();
}

void GuestWindow::on_sendMsgButton_clicked()
{
    sendMsg(ui->newMsgText->toPlainText());
}

void GuestWindow::on_refreshMsg_clicked()
{
    viewMsgList();
}

void GuestWindow::on_viewOrderButton_clicked()
{
    viewOrderList();
}

void GuestWindow::on_refreshOrderInfoButton_clicked()
{
    viewDishInOrderList(currentOrder);
}

void GuestWindow::on_checkOutButton_clicked()
{
    for(unsigned int i = 0; i < currentOrder->getOrderDishes().size(); i ++) {
        StaticData::getOrderedDishByID(currentOrder->getOrderDishes()[i]).setStatus(5);
        StaticData::modifyOrderedDish(currentOrder->getOrderDishes()[i], StaticData::getOrderedDishByID(currentOrder->getOrderDishes()[i]));
    }
    sendMsg("Check Out");
    ui->checkOutButton->setEnabled(currentOrder->checkStatus() == 4);
    viewDishInOrderList(currentOrder);
    checkedOut = true;
    for (unsigned int i = 0; i < StaticData::getOrderList().size(); i ++)
        if (StaticData::getOrderList()[i].getOrderer() == guest.getPhone()
                && StaticData::getOrderList()[i].checkStatus() < 5) {
            checkedOut = false;
            break;
        }
    if (checkedOut)
        guest.freeTable();
}

void GuestWindow::on_refreshDishListButton_clicked()
{
    viewDishList();
}

void GuestWindow::on_backButton_clicked()
{
    viewOrderList();
}
