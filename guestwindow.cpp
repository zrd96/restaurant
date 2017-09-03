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

GuestWindow::GuestWindow(QWidget *parent) :
    QMainWindow(parent),
    guest("", ""),
    orderedSum(0),
    submittedSum(0),
    ui(new Ui::GuestWindow)
{
    ui->setupUi(this);
}

GuestWindow::~GuestWindow()
{
    clearPointerList(tableItem);
    clearPointerList(dishItem);
    clearPointerList(cartItem);
    clearPointerList(orderItem);
    delete ui;
}
//QItemDelegate
void GuestWindow::openWindow(const QString user) {
    guest = Guest(user.toStdString(), "Guest");
    StaticData::queryTable();
    StaticData::queryDish();
    this->show();
    viewTableList();
    viewDishList();
    viewCartList();
}

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
    clearPointerList(orderItem);
    for(unsigned int i = 0; i < StaticData::orderedDishList.size(); i ++) {
        if(StaticData::orderedDishList[i].getOrderer() == guest.getPhone()) {
            Item* item = new Item(guest, StaticData::orderedDishList[i], "orderList", ui->cartList);
            ui->cartList->addItem(item);
            orderItem.push_back(item);
        }
    }
    ui->scrollAreaCartList->show();
    ui->cartTab->show();
    this->show();
}

void GuestWindow::clearPointerList(vector<Item*>& pointerList) {
    //viewErrInfo(ntos((int)pointerList.size()));
    for(unsigned int i = 0; i < pointerList.size(); i ++)
        delete pointerList[i];
    pointerList.clear();
}

void GuestWindow::clearPointerList(vector<TableItem*>& pointerList) {
    //viewErrInfo(ntos((int)pointerList.size()));
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
