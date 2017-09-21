#include "chefwindow.h"
#include "ui_chefwindow.h"
#include "tools.h"
#include "staticdata.h"
#include "chef.h"
#include "dish.h"
#include "item.h"
#include "emptyresult.h"

ChefWindow::ChefWindow(const QString& user, QWidget *parent) :
    QMainWindow(parent),
    chef(Chef("", "", "")),
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
    ui->tabWidget->setCurrentIndex(0);
    on_tabWidget_currentChanged(0);
}

ChefWindow::~ChefWindow()
{
    delete ui;
}

void ChefWindow::viewOrderedDishList() {
    ui->orderedDishList->clearContents();
    ui->orderedDishList->setRowCount(0);
    for (unsigned int i = 0; i < StaticData::getOrderedDishList().size(); i ++) {
        OrderedDish& curDish = StaticData::getOrderedDishList()[i];
        if (StaticData::getOrderedDishMaintainList()[i] >= 0 && curDish.getStatus() == 1) {
            Item* item = new Item(chef, curDish, "chefDishList", ui->orderedDishList);
            ui->orderedDishList->setRowCount(ui->orderedDishList->rowCount() + 1);
            ui->orderedDishList->setCellWidget(ui->orderedDishList->rowCount() - 1, 0, item);
            item->show();
        }
    }
}

void ChefWindow::viewTakenDishList() {
    ui->takenDishList->clearContents();
    ui->takenDishList->setRowCount(0);
    chef.checkDish();
    for (unsigned int i = 0; i < chef.getTakenDish().size(); i ++) {
        OrderedDish& curDish = chef.getTakenDish()[i];
        Item* item = new Item(chef, curDish, "chefTakenDishList", ui->takenDishList);
        ui->takenDishList->setRowCount(ui->takenDishList->rowCount() + 1);
        ui->takenDishList->setCellWidget(ui->takenDishList->rowCount() - 1, 0, item);
        item->show();
    }
}

void ChefWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0) {
        ui->title->setText("   View Ordered Dish List");
        ui->refreshButton->setGeometry(1020, 10, 60, 60);
        ui->saveButton->hide();
        viewOrderedDishList();
    }
    else if (index == 1) {
        ui->title->setText("   View Taken Dish List");
        ui->refreshButton->setGeometry(1020, 10, 60, 60);
        ui->saveButton->hide();
        viewTakenDishList();
    }
    else if (index == 2) {
        ui->title->setText("   About Me");
        ui->refreshButton->setGeometry(930, 10, 60, 60);
        ui->saveButton->show();
    }
}

void ChefWindow::on_refreshButton_clicked()
{
    int index = ui->tabWidget->currentIndex();
    if (index == 0) {
        viewOrderedDishList();
    }
    else if (index == 1) {
        viewTakenDishList();
    }
    else if (index  == 2) {
        aboutMe->refresh();
    }
}

void ChefWindow::on_saveButton_clicked()
{
    aboutMe->submit();
}

void ChefWindow::on_logoutButton_clicked()
{
    aboutMe->logout();
}
