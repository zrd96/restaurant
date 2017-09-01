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
        Item* item = new Item(guest, StaticData::dishList[i], i, ui->dishList);
        ui->dishList->addItem(item);
        dishItem.push_back(item);
    }
    showAll();
}

void GuestWindow::viewCartList() {
    clearPointerList(cartItem);
    ui->cartList->setMinimumSize(1080, 0);
    ui->cartList->resize(1080, 0);
    for(int i = 0; i < guest.getOrderedDishList().size(); i ++) {
        Item* item = new Item(guest, guest.getOrderedDishList()[i], i, ui->cartList);
        connect(item, SIGNAL(dishNumChanged(int,int)), this, SLOT(setDishNum(int, int)));
        ui->cartList->addItem(item);
        cartItem.push_back(item);
    }
    ui->scrollAreaCartList->show();
    ui->cartTab->show();
    this->show();
}

void GuestWindow::clearPointerList(vector<Item*>& pointerList) {
    //viewErrInfo(ntos((int)pointerList.size()));
    for(int i = 0; i < pointerList.size(); i ++)
        delete pointerList[i];
    pointerList.clear();
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

void GuestWindow::setDishNum(int dishID, int finalNum) {
    for(int i = 0; i < dishItem.size(); i ++)
        if(dishItem[i]->getDishID() == dishID) {
            dishItem[i]->setDishNumText(finalNum);
            break;
        }
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
