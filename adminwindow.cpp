#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QMessageBox>
#include <QTableWidget>
#include "staticdata.h"
#include "guest.h"
#include "chef.h"
#include "clerk.h"
#include "admin.h"

AdminWindow::AdminWindow(const QString& user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    StaticData::queryGuest();
    StaticData::queryClerk();
    StaticData::queryChef();
    connect(ui->addButton, &QPushButton::clicked, this, [this]{addItem(getActiveList());});
    connect(ui->removeButton, &QPushButton::clicked, this, [this]{removeSelected(getActiveList());});
    connect(ui->refreshButton, &QPushButton::clicked, this, [this]{refreshList();});
    connect(ui->restoreButton, &QPushButton::clicked, this, [this]{refreshList();});
    ui->tableList->setColumnWidth(0, 410);
    ui->tableList->setColumnWidth(1, 410);
    ui->dishList->setColumnWidth(0, 80);    //dishID
    ui->dishList->setColumnWidth(1, 105);   //imgdir
    ui->dishList->setColumnWidth(2, 400);   //name
    ui->dishList->setColumnWidth(3, 80);    //price
    ui->dishList->setColumnWidth(4, 80);    //time
    ui->dishList->setColumnWidth(5, 80);    //rate
    ui->dishList->setColumnWidth(6, 80);    //rateNum
    ui->guestList->setColumnWidth(0, 250);
    ui->guestList->setColumnWidth(1, 200);
    ui->guestList->setColumnWidth(2, 250);
    ui->guestList->setColumnWidth(3, 110);
    ui->chefList->setColumnWidth(0, 250);
    ui->chefList->setColumnWidth(1, 200);
    ui->chefList->setColumnWidth(2, 250);
    ui->chefList->setColumnWidth(3, 110);
    ui->clerkList->setColumnWidth(0, 210);
    ui->clerkList->setColumnWidth(1, 150);
    ui->clerkList->setColumnWidth(2, 210);
    ui->clerkList->setColumnWidth(3, 80);
    ui->clerkList->setColumnWidth(4, 80);
    ui->clerkList->setColumnWidth(5, 80);
    viewTableList();
    viewDishList();
    viewGuestList();
    viewChefList();
    viewClerkList();
}

void AdminWindow::viewTableList() {
    ui->tableList->setRowCount(StaticData::tableList.size());
    for(unsigned int i = 0; i < StaticData::tableList.size(); i ++) {
        Table& cur = StaticData::tableList[i];
        ui->tableList->setItem(i, 0, new QTableWidgetItem(QString().setNum(cur.getTableID())));
        ui->tableList->setItem(i, 1, new QTableWidgetItem(QString().setNum(cur.getSeats())));
    }
}

void AdminWindow::viewDishList() {
    ui->dishList->setRowCount(StaticData::dishList.size());
    for(unsigned int i = 0; i < StaticData::dishList.size(); i ++) {
        Dish& cur = StaticData::dishList[i];
        ui->dishList->setItem(i, 0, new QTableWidgetItem(QString().setNum(cur.getDishID())));
        ui->dishList->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(cur.getImgDir())));
        ui->dishList->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(cur.getName())));
        ui->dishList->setItem(i, 3, new QTableWidgetItem(QString().setNum(cur.getPrice())));
        ui->dishList->setItem(i, 4, new QTableWidgetItem(QString().setNum(cur.getTimeNeeded())));
        ui->dishList->setItem(i, 5, new QTableWidgetItem(QString().setNum(cur.getRate())));
        ui->dishList->setItem(i, 6, new QTableWidgetItem(QString().setNum(cur.getRateNum())));
    }
}

void AdminWindow::viewGuestList() {
    ui->guestList->setRowCount(StaticData::guestList.size());
    for(unsigned int i = 0; i < StaticData::guestList.size(); i ++) {
        Guest& cur = StaticData::guestList[i];
        ui->guestList->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(cur.getPhone())));
        ui->guestList->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(cur.getName())));
        ui->guestList->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(cur.getPassword())));
        ui->guestList->setItem(i, 3, new QTableWidgetItem(QString::fromStdString("0")));
    }
}

void AdminWindow::viewChefList() {
    ui->chefList->setRowCount(StaticData::chefList.size());
    for(unsigned int i = 0; i < StaticData::chefList.size(); i ++) {
        Chef& cur = StaticData::chefList[i];
        ui->chefList->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(cur.getPhone())));
        ui->chefList->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(cur.getName())));
        ui->chefList->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(cur.getPassword())));
        ui->chefList->setItem(i, 3, new QTableWidgetItem(QString::fromStdString("0")));
    }
}

void AdminWindow::viewClerkList() {
    ui->clerkList->setRowCount(StaticData::clerkList.size());
    for(unsigned int i = 0; i < StaticData::clerkList.size(); i ++) {
        Clerk& cur = StaticData::clerkList[i];
        ui->clerkList->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(cur.getPhone())));
        ui->clerkList->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(cur.getName())));
        ui->clerkList->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(cur.getPassword())));
        ui->clerkList->setItem(i, 3, new QTableWidgetItem(QString().setNum(cur.getRate())));
        ui->clerkList->setItem(i, 4, new QTableWidgetItem(QString().setNum(cur.getRateNum())));
        ui->clerkList->setItem(i, 5, new QTableWidgetItem(QString::fromStdString("0")));
    }
}

void AdminWindow::addItem(QTableWidget *list) {
    if (list == NULL)
        return;
    list->setRowCount(list->rowCount() + 1);
    list->setItem(list->rowCount() - 1, 0, new QTableWidgetItem(QString("")));
    list->editItem(list->item(list->rowCount() - 1, 0));
}

void AdminWindow::removeSelected(QTableWidget* list) {
    if (list == NULL)
        return;
    QList<QTableWidgetSelectionRange> selectedRowList = list->selectedRanges();
    bool* selectedRows = new bool[list->rowCount()];
    for(int i = 0; i < list->rowCount(); i ++)
        selectedRows[i] = false;
    for (unsigned int i = 0; i < selectedRowList.size(); i ++)
        for (unsigned int j = selectedRowList[i].topRow(); j <= selectedRowList[i].bottomRow(); j ++) {
            viewErrInfo(ntos((int)j));
            selectedRows[j] = true;
        }
    for(int i = list->rowCount() - 1; i >= 0; i --)
        if(selectedRows[i])
            list->removeRow(i);
    delete []selectedRows;
}

void AdminWindow::refreshList() {
    int index = ui->tabWidget->currentIndex();
    if(index == 0)
        viewTableList();
    else if (index == 1)
        viewDishList();
    else if (index == 2)
        viewGuestList();
    else if (index == 3)
        viewChefList();
    else if (index == 4)
        viewClerkList();
}

void AdminWindow::saveList() {

}

QTableWidget* AdminWindow::getActiveList() {
    int index = ui->tabWidget->currentIndex();
    if(index == 0)
        return ui->tableList;
    else if (index == 1)
        return ui->dishList;
    else if (index == 2)
        return ui->guestList;
    else if (index == 3)
        return ui->chefList;
    else if (index == 4)
        return ui->clerkList;
    else
        return NULL;
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
