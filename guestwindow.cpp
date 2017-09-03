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

GuestWindow::GuestWindow(QWidget *parent) :
    QMainWindow(parent),
    guest("", ""),
    ui(new Ui::GuestWindow)
{
    ui->setupUi(this);
}

GuestWindow::~GuestWindow()
{
    clearPointerList(dishItem);
    clearPointerList(cartItem);
    delete ui;
}
//QItemDelegate
void GuestWindow::openWindow(const QString user) {
//    ui->dishList->setParent(ui->scrollAreaDishList);
//    ui->cartList->setParent(ui->scrollAreaCartList);
//    ui->dishTab->setParent(ui->tabWidget);
//    ui->cartTab->setParent(ui->tabWidget);
    guest = Guest(user.toStdString(), "Guest");
    StaticData::queryDish();
    this->show();
    viewDishList();
    viewCartList();
}

void GuestWindow::viewDishList() {
    clearPointerList(dishItem);
    ui->dishList->setMinimumSize(1080, 0);
    ui->dishList->resize(1080, 0);
    for(int i = 0; i < StaticData::dishList.size(); i ++) {
        Item* item = new Item(guest, StaticData::dishList[i], "dishList", ui->dishList);
        ui->dishList->addItem(item);
        dishItem.push_back(item);
    }
}

void GuestWindow::viewCartList() {
    clearPointerList(cartItem);
    ui->cartList->setMinimumSize(1080, 0);
    ui->cartList->resize(1080, 0);
    for(int i = 0; i < guest.getOrderedDishList().size(); i ++) {
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

void GuestWindow::clearPointerList(vector<Item*>& pointerList) {
    //viewErrInfo(ntos((int)pointerList.size()));
    for(int i = 0; i < pointerList.size(); i ++)
        delete pointerList[i];
    pointerList.clear();
}

void GuestWindow::setDishNum(int dishID, int finalNum) {
    for(int i = 0; i < dishItem.size(); i ++)
        if(dishItem[i]->getDishID() == dishID) {
            dishItem[i]->setDishNumText(finalNum);
            break;
        }
    updateSum();
}

void GuestWindow::showAll() {
    ui->dishTab->show();
    ui->cartTab->show();
    this->show();
}

void GuestWindow::on_RefreshCart_clicked()
{
    viewCartList();
}

void GuestWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 2)
        viewCartList();
    else if (index == 1) {
        for(int i = 0; i < dishItem.size(); i ++)
            dishItem[i] -> show();
        ui->scrollAreaDishList->show();
        ui->dishTab->show();
        this->show();
    }
}

void GuestWindow::updateSum() {
    ui->cartTotal->setText("￥" + QString().setNum(guest.getSumInCart()));
    if(guest.getSumInCart() == 0)
        ui->submitButton->setEnabled(false);
    else
        ui->submitButton->setEnabled(true);
}

void GuestWindow::on_submitButton_clicked()
{
    QString orderInfo = "Your order: \n\n";
    for (int i = 0; i < guest.getOrderedDishList().size(); i ++) {
        orderInfo += QString::fromStdString(guest.getOrderedDishList()[i].getName()) + "\n";
        orderInfo += "￥" + QString().setNum(guest.getOrderedDishList()[i].getPrice()) + " x " + QString().setNum(guest.getOrderedDishList()[i].getNum()) + " = ￥" + QString().setNum(guest.getOrderedDishList()[i].getPrice() * guest.getOrderedDishList()[i].getNum()) + "\n\n";
    }
    orderInfo += "Total: ￥" + QString().setNum(guest.getSumInCart()) + "\n\n Submit?";
    int reply = QMessageBox::question(NULL, "Confirm Order", orderInfo, QMessageBox::Yes, QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        guest.submit();
        for(int i = 0; i < cartItem.size(); i ++) {
            //cartItem[i] -> updateStatus();
            cartItem[i] -> setEnabled(false);
        }
    }

}
