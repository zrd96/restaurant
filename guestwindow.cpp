#include <vector>
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

void GuestWindow::openWindow(const QString user) {
    guest = Guest(user.toStdString(), "Guest");
    StaticData::queryDish();
    for(int i = 0; i < StaticData::dishList.size(); i ++) {
        if(i % 2 == 0)
            guest.addDish(StaticData::dishList[i]);
    }
    this->show();
    viewDishList();
    viewCartList();
}

void GuestWindow::viewDishList() {
    clearPointerList(dishItem);
    ui->dishList->setMinimumSize(1080, 0);
    ui->dishList->resize(1080, 0);
    StaticData::queryDish();
    for(int i = 0; i < StaticData::dishList.size(); i ++) {
        Item* item = new Item(guest, StaticData::dishList[i], i, ui->dishList);
        ui->dishList->addItem(item);
        dishItem.push_back(item);
    }
    ui->dishTab->show();
    show();
}

void GuestWindow::viewCartList() {
    clearPointerList(cartItem);
    ui->cartList->setMinimumSize(1080, 0);
    ui->cartList->resize(1080, 0);
    viewErrInfo(ntos((int)guest.getOrderedDishList().size()));
    for(int i = 0; i < guest.getOrderedDishList().size(); i ++) {
        Item* item = new Item(guest, guest.getOrderedDishList()[i], i, ui->cartList);
        ui->cartList->addItem(item);
        cartItem.push_back(item);
    }
    ui->scrollAreaCartList->show();
    ui->cartTab->show();
    show();
}

void GuestWindow::clearPointerList(vector<Item*>& pointerList) {
    viewErrInfo(ntos((int)pointerList.size()));
    for(int i = 0; i < pointerList.size(); i ++)
        delete pointerList[i];
    pointerList.clear();
}

void GuestWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 2)
        viewCartList();
//    else if (index == 1)
//        viewDishList();
}




void GuestWindow::on_RefreshCart_clicked()
{
    viewCartList();
}
