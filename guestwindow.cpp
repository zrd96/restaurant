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
#include "itemlist.h"
#include "tableitem.h"
#include "table.h"
#include "msg.h"
#include "aboutmewidget.h"
#include "order.h"
#include "orderitem.h"

GuestWindow::GuestWindow(const QString user, QWidget *parent) :
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
    for(unsigned int i = 0; i < StaticData::orderedDishList.size(); i ++)
        if(StaticData::orderedDishList[i].getOrderer() == guest.getPhone())
            submittedSum += StaticData::orderedDishList[i].getPrice();
    ui->inboxList->setColumnWidth(0, 150);
    ui->inboxList->setColumnWidth(1, 150);
    ui->inboxList->setColumnWidth(2, 850);
    ui->outboxList->setColumnWidth(0, 150);
    ui->outboxList->setColumnWidth(1, 150);
    ui->outboxList->setColumnWidth(2, 850);
    aboutMe = new AboutMeWidget(&guest, this, ui->selfTab);
    aboutMe->show();
    this->show();
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
    for(unsigned int i = 0; i < StaticData::tableList.size(); i ++) {
        if(i % 3 == 0 && ui->tableList->rowCount() <= (int)i/3)
            ui->tableList->setRowCount(ui->tableList->rowCount() + 1);
        int row = i / 3;
        int col = i % 3;
        TableItem* table = new TableItem(guest, StaticData::tableList[i], this, ui->tableList);
        ui->tableList->setCellWidget(row, col, table);
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
    ui->dishList->setMinimumSize(1080, 0);
    ui->dishList->resize(1080, 0);
    for(unsigned int i = 0; i < StaticData::dishList.size(); i ++) {
        Item* item = new Item(guest, StaticData::dishList[i], "dishList", ui->dishList);
        ui->dishList->addItem(item);
        dishItem.push_back(item);
    }
}

void GuestWindow::viewCartList() {
    clearPointerList(cartItem);
    ui->cartList->setMinimumSize(1080, 0);
    ui->cartList->resize(1080, 0);
    for(unsigned int i = 0; i < guest.getOrderedDishList().size(); i ++) {
        Item* item = new Item(guest, guest.getOrderedDishList()[i], "cartList", ui->cartList);
        connect(item, SIGNAL(dishNumChanged(int,int)), this, SLOT(setDishNum(int, int)));
        ui->cartList->addItem(item);
        cartItem.push_back(item);
    }
    updateSum();
    ui->scrollAreaCartList->show();
    ui->cartTab->show();
    this->show();
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
    vector<bool> isFinished;
    for(unsigned int i = 0; i < StaticData::orderList.size(); i ++) {
        if(StaticData::orderList[i].getOrderer().toStdString() == guest.getPhone()) {
            OrderItem* item = new OrderItem(&StaticData::orderList[i], ui->orderList);
            orderItem.push_back(item);
            isFinished.push_back(StaticData::orderList[i].isFinished());
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
    ui->orderList->clearContents();
    ui->orderList->setRowCount(0);
    bool orderAllServed = true;
    for(unsigned int i = 0; i < order->getOrderDishes().size(); i ++) {
        Item* item = new Item(guest, order->getOrderDishes()[i], "orderList", ui->orderList);
        ui->orderList->setRowCount(ui->orderList->rowCount() + 1);
        ui->orderList->setCellWidget(ui->orderList->rowCount() - 1, 0, item);
        dishInOrderItem.push_back(item);
        if(order->getOrderDishes()[i].getStatus() < 4)
            orderAllServed = false;
        item->show();
    }
    ui->checkOutButton->setEnabled(orderAllServed);
}

void GuestWindow::viewMsgList() {
    ui->inboxList->clearContents();
    ui->outboxList->clearContents();
    clearPointerList(msgItem);

    vector<Msg*> msgReceived = StaticData::getMsgByReceiver(guest.getPhone());
    for(unsigned int i = 0; i < msgReceived.size(); i ++) {
        ui->inboxList->setRowCount(ui->inboxList->rowCount() + 1);
        QTableWidgetItem* cell1 = new QTableWidgetItem(QString::fromStdString(StaticData::getPersonNameByPhone(msgReceived[i]->getSender())));
        ui->inboxList->setItem(ui->inboxList->rowCount() - 1, 0, cell1);
        QTableWidgetItem* cell2 = new QTableWidgetItem(QString::fromStdString(msgReceived[i]->getDatetime()));
        ui->inboxList->setItem(ui->inboxList->rowCount() - 1, 1, cell2);
        QTableWidgetItem* cell3 = new QTableWidgetItem(QString::fromStdString(msgReceived[i]->getMsg()));
        ui->inboxList->setItem(ui->inboxList->rowCount() - 1, 2, cell3);
        msgItem.push_back(cell1);
        msgItem.push_back(cell2);
        msgItem.push_back(cell3);
    }

    vector<Msg*> msgSent = StaticData::getMsgBySender(guest.getPhone());
    for(unsigned int i = 0; i < msgReceived.size(); i ++) {
        ui->outboxList->setRowCount(ui->outboxList->rowCount() + 1);
        QTableWidgetItem* cell1 = new QTableWidgetItem(QString::fromStdString(StaticData::getPersonNameByPhone(msgSent[i]->getSender())));
        ui->outboxList->setItem(ui->outboxList->rowCount() - 1, 0, cell1);
        QTableWidgetItem* cell2 = new QTableWidgetItem(QString::fromStdString(msgSent[i]->getDatetime()));
        ui->outboxList->setItem(ui->outboxList->rowCount() - 1, 1, cell2);
        QTableWidgetItem* cell3 = new QTableWidgetItem(QString::fromStdString(msgSent[i]->getMsg()));
        ui->outboxList->setItem(ui->outboxList->rowCount() - 1, 2, cell3);
        msgItem.push_back(cell1);
        msgItem.push_back(cell2);
        msgItem.push_back(cell3);
    }
}

template<typename T> void GuestWindow::clearPointerList(vector<T*>& pointerList) {
    for(unsigned int i = 0; i < pointerList.size(); i ++)
            delete pointerList[i];
        pointerList.clear();
}

void GuestWindow::setDishNum(int dishID, int finalNum) {
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

void GuestWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 2) {
        viewCartList();
        viewOrderList();
    }
    else if (index == 1) {
        for(unsigned int i = 0; i < dishItem.size(); i ++)
            dishItem[i] -> show();
        ui->scrollAreaDishList->show();
        ui->dishTab->show();
        this->show();
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
    for(unsigned int i = 0; i < StaticData::tableList.size(); i ++)
        if(StaticData::tableList[i].getTableID() == selectedTable) {
            if(!guest.selectTable(StaticData::tableList[i])) {
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
    if(ui->newMsgText->toPlainText().size() == 0) {
        viewErrInfo("Empty message");
        return;
    }
    guest.sendMsg(StaticData::getClerkPhoneByTable(guest.getTable()), ui->newMsgText->toPlainText().toStdString());
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
        StaticData::getOrderedDishByID(currentOrder->getOrderDishes()[i].getOrderedDishID()).setStatus(5);
    }
    currentOrder->checkFinished();
    viewDishInOrderList(currentOrder);
}
