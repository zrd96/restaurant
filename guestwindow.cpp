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
    submittedSum(0),
    checkedOut(true),
    currentOrder(NULL),
    ui(new Ui::GuestWindow)
{
    ui->setupUi(this);
    StaticData::db->doQuery("person", "name, password, tableID", "phone = \"" + user.toStdString() + "\"");
    if(StaticData::db->getResultList()[0][2] != "NULL")
        guest = Guest(user.toStdString(),
                      StaticData::db->getResultList()[0][0],
                StaticData::db->getResultList()[0][1],
                atoi(StaticData::db->getResultList()[0][2].c_str()));
    else
        guest = Guest(user.toStdString(),
                      StaticData::db->getResultList()[0][0],
                StaticData::db->getResultList()[0][1]);
    StaticData::queryMsg(guest.getPhone());
    for(unsigned int i = 0; i < StaticData::getOrderedDishList().size(); i ++)
        if(StaticData::getOrderedDishList()[i].getOrderer() == guest.getPhone())
            submittedSum += StaticData::getOrderedDishList()[i].getPrice();
    ui->inboxList->setColumnWidth(0, 150);
    ui->inboxList->setColumnWidth(1, 150);
    ui->inboxList->setColumnWidth(2, 850);
    ui->outboxList->setColumnWidth(0, 150);
    ui->outboxList->setColumnWidth(1, 150);
    ui->outboxList->setColumnWidth(2, 850);
    aboutMe = new AboutMeWidget(&guest, this, ui->selfTab);
    aboutMe->show();
    this->show();
    StaticData::queryOrder();
    connect(ui->sendWaterButton, &QPushButton::clicked, this, [this] {sendMsg("Water");});
    connect(ui->sendNapkinButton, &QPushButton::clicked, this, [this] {sendMsg("Napkin");});
    connect(ui->sendQuicklyButton, &QPushButton::clicked, this, [this] {sendMsg("Quickly");});
    viewTableList();
    viewDishList();
    viewCartList();
    viewOrderList();
    viewMsgList();
    ui->tabWidget->setCurrentIndex(0);
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
        connect(item, SIGNAL(dishNumChanged(const string&, int)), this, SLOT(setDishNum(const string&, int)));
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
    ui->viewOrderButton->setText("Refresh");
    ui->viewOrderButton->setGeometry(1010, 790, 80, 50);
    ui->refreshOrderInfoButton->hide();
    ui->checkOutButton->hide();
    clearPointerList(dishInOrderItem);
    clearPointerList(orderItem);
    ui->orderList->clearContents();
    ui->orderList->setRowCount(0);
    //check each order, if they are active, show them first;
    vector<bool> isFinished;
    for(unsigned int i = 0; i < StaticData::getOrderList().size(); i ++) {
        if(StaticData::getOrderList()[i].getOrderer().toStdString() == guest.getPhone()) {
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
    ui->viewOrderButton->setText("Back");
    ui->viewOrderButton->setGeometry(730, 790, 80, 50);
    ui->refreshOrderInfoButton->show();
    ui->checkOutButton->show();
    clearPointerList(orderItem);
    clearPointerList(dishInOrderItem);
    ui->orderList->setRowCount(0);
    for(unsigned int i = 0; i < order->getOrderDishes().size(); i ++) {
        Item* item = new Item(guest, order->getOrderDishes()[i], "orderList", ui->orderList);
        ui->orderList->setRowCount(ui->orderList->rowCount() + 1);
        ui->orderList->setCellWidget(ui->orderList->rowCount() - 1, 0, item);
        dishInOrderItem.push_back(item);
        item->show();
    }
    ui->checkOutButton->setEnabled(order->checkStatus() == 4);
    if (order->checkStatus() == 5) {
        ui->rateClerkNote->show();
        RateItem* rateItem = new RateItem(this);
        rateItem->setGeometry(260, 800, 150, 30);
        connect(rateItem, SIGNAL(rateSet(double)), this, SLOT(rateClerk(double)));
        rateItem->show();
    }
}

void GuestWindow::viewMsgList() {
    ui->inboxList->setRowCount(0);
    vector<Msg*> msgReceived = StaticData::getMsgByReceiver(guest.getPhone());
    for(unsigned int i = 0; i < msgReceived.size(); i ++) {
        int row = ui->inboxList->rowCount();
        ui->inboxList->setRowCount(row + 1);
        ui->inboxList->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(StaticData::getPersonNameByPhone(msgReceived[i]->getSender()))));
        ui->inboxList->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(msgReceived[i]->getDatetime())));
        ui->inboxList->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(msgReceived[i]->getMsg())));
    }
    ui->outboxList->setRowCount(0);
    vector<Msg*> msgSent = StaticData::getMsgBySender(guest.getPhone());
    for(unsigned int i = 0; i < msgReceived.size(); i ++) {
        int row = ui->outboxList->rowCount();
        ui->outboxList->setRowCount(row + 1);
        ui->outboxList->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(StaticData::getPersonNameByPhone(msgSent[i]->getReceiver()))));
        ui->outboxList->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(msgSent[i]->getDatetime())));
        ui->outboxList->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(msgSent[i]->getMsg())));
    }
}

void GuestWindow::setDishNum(const string& dishID, int finalNum) {
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
        Clerk &clerk = StaticData::getClerkByPhone(QString::fromStdString(StaticData::getTableByID(guest.getTable()).getClerk()));
        clerk.updateRate(newRate);
        StaticData::modifyClerk(clerk.getPhone(), clerk);
        currentOrder->getOrderDishes()[0].setStatus(currentOrder->getOrderDishes()[0].getStatus() + 2);
        StaticData::modifyOrderedDish(currentOrder->getOrderDishes()[0].getOrderedDishID(), currentOrder->getOrderDishes()[0]);
    } catch (EmptyResult) {}
}

void GuestWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 2) {
        viewCartList();
        viewOrderList();
    }
    else if (index == 1) {
        viewDishList();
    }
}

void GuestWindow::updateSum() {
    orderedSum = guest.getSumInCart();
    ui->cartTotal->setText("￥" + QString().setNum(orderedSum));
    ui->submittedTotal->setText("");
    if(submittedSum > 0)
        ui->submittedTotal->setText(" + ￥" + QString().setNum(submittedSum));
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
    guest.sendMsg("Table_" + ntos(guest.getTable()), msg.toStdString());
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
        orderInfo += QString::fromStdString(guest.getOrderedDishList()[i].getName()) + "\n";
        orderInfo += "￥" + QString().setNum(guest.getOrderedDishList()[i].getPrice()) + " x " + QString().setNum(guest.getOrderedDishList()[i].getNum()) + " = ￥" + QString().setNum(guest.getOrderedDishList()[i].getPrice() * guest.getOrderedDishList()[i].getNum()) + "\n\n";
    }
    orderInfo += "Total: ￥" + QString().setNum(guest.getSumInCart()) + "\n\n Submit?";
    int reply = QMessageBox::question(NULL, "Confirm Order", orderInfo, QMessageBox::Yes, QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        submittedSum += guest.getSumInCart();
        guest.modifyTable(guest.getTable());
        guest.submit();
        viewDishList();
        viewCartList();
        viewOrderList();
        ui->tabWidget->setCurrentIndex(3);
    }
}

void GuestWindow::on_submitTableButton_clicked()
{
    for(unsigned int i = 0; i < StaticData::getTableList().size(); i ++)
        if(StaticData::getTableList()[i].getTableID() == selectedTable) {
            if(!guest.selectTable(StaticData::getTableList()[i])) {
                viewErrInfo("No seats left for Table No. " + ntos(selectedTable) + ", please reselect.");
                return;
            }
            break;
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
        currentOrder->getOrderDishes()[i].setStatus(5);
        StaticData::modifyOrderedDish(currentOrder->getOrderDishes()[i].getOrderedDishID(), currentOrder->getOrderDishes()[i]);
    }
    sendMsg("Check Out");
    ui->checkOutButton->setEnabled(currentOrder->checkStatus() == 4);
    viewDishInOrderList(currentOrder);
}

void GuestWindow::on_refreshDishListButton_clicked()
{
    viewDishList();
}
