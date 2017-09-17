#include "chefwindow.h"
#include "ui_chefwindow.h"
#include "tools.h"
#include "staticdata.h"
#include "chef.h"
#include "dish.h"
#include "emptyresult.h"

ChefWindow::ChefWindow(const QString& user, QWidget *parent) :
    QMainWindow(parent),
    chef(Chef("", "")),
    ui(new Ui::ChefWindow)
{
    ui->setupUi(this);
    try {
        chef = StaticData::getChefByPhone(user);
    } catch (EmptyResult) {
        viewErrInfo("Fatal error: user not found, please retry later");
        this->close();
    }
    viewOrderedDishList();
    aboutMe = new AboutMeWidget(&chef, this, ui->selfTab);
    aboutMe->show();
}

ChefWindow::~ChefWindow()
{
    clearPointerList(orderedDishItem);
    delete ui;
}

void ChefWindow::openWindow(const QString user) {
    this->show();
}

void ChefWindow::viewOrderedDishList() {
    clearPointerList(orderedDishItem);
    ui->orderedDishList->clearContents();
    ui->orderedDishList->setRowCount(0);
    for (unsigned int i = 0; i < StaticData::getOrderedDishList().size(); i ++) {
        OrderedDish& curDish = StaticData::getOrderedDishList()[i];
        if (StaticData::getOrderedDishMaintainList()[i] >= 0 && curDish.getStatus() == 1) {
            Item* item = new Item(chef, curDish, "chefDishList", ui->orderedDishList);
            ui->orderedDishList->setRowCount(ui->orderedDishList->rowCount() + 1);
            ui->orderedDishList->setCellWidget(ui->orderedDishList->rowCount() - 1, 0, item);
            orderedDishItem.push_back(item);
            item->show();
        }
    }
}

void ChefWindow::viewTakenDishList() {
    clearPointerList(takenDishItem);
    ui->takenDishList->clearContents();
    ui->takenDishList->setRowCount(0);
    chef.checkDish();
    for (unsigned int i = 0; i < chef.getTakenDish().size(); i ++) {
        OrderedDish& curDish = chef.getTakenDish()[i];
        Item* item = new Item(chef, curDish, "chefTakenDishList", ui->takenDishList);
        ui->takenDishList->setRowCount(ui->takenDishList->rowCount() + 1);
        ui->takenDishList->setCellWidget(ui->takenDishList->rowCount() - 1, 0, item);
        takenDishItem.push_back(item);
        item->show();
    }
}

void ChefWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0) {
        ui->title->setText("   View Ordered Dish List");
        viewOrderedDishList();
    }
    else if (index == 1) {
        ui->title->setText("   View Taken Dish List");
        viewTakenDishList();
    }
    else if (index == 2) {
        ui->title->setText("   About Me");
    }
}

void ChefWindow::on_pushButton_clicked()
{
    viewOrderedDishList();
}

void ChefWindow::on_pushButton_2_clicked()
{
    viewTakenDishList();
}
