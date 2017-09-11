#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include "staticdata.h"
#include "guest.h"
#include "chef.h"
#include "clerk.h"
#include "admin.h"
#include "aboutmewidget.h"

AdminWindow::AdminWindow(const QString& user, QWidget *parent) :
    QMainWindow(parent),
    admin(Admin("", "")),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    StaticData::db->doQuery("person", "name, password", "phone = \"" + user.toStdString() + "\"");
    admin = Admin(user.toStdString(),
                      StaticData::db->getResultList()[0][0],
                StaticData::db->getResultList()[0][1]);
    StaticData::queryGuest();
    StaticData::queryClerk();
    StaticData::queryChef();
    connect(ui->addButton, &QPushButton::clicked, this, [this]{addItem(getActiveList());});
    connect(ui->removeButton, &QPushButton::clicked, this, [this]{removeSelected(getActiveList());});
    //connect(ui->refreshButton, &QPushButton::clicked, this, [this]{refreshList();});
    connect(ui->restoreButton, &QPushButton::clicked, this, [this]{refreshList();});
    connect(ui->saveButton, &QPushButton::clicked, this, [this]{saveList(ui->tabWidget->currentIndex());});
    aboutMe = new AboutMeWidget(&admin, this, ui->selfTab);
    aboutMe->show();
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
    //qDebug() << QString("jhs").toInt();
}

void AdminWindow::viewTableList() {
    ui->tableList->setRowCount(0);
    for(unsigned int i = 0; i < StaticData::getTableList().size(); i ++)
        if (StaticData::getTableMaintainList()[i] >= 0) {
            ui->tableList->setRowCount(ui->tableList->rowCount() + 1);
            Table& cur = StaticData::getTableList()[i];
            ui->tableList->setItem(i, 0, new QTableWidgetItem(QString().setNum(cur.getTableID())));
            ui->tableList->setItem(i, 1, new QTableWidgetItem(QString().setNum(cur.getSeats())));
            ui->tableList->item(i, 0)->setData(Qt::UserRole, cur.getTableID());
            ui->tableList->item(i, 1)->setData(Qt::UserRole, cur.getSeats());
        }
}

void AdminWindow::viewDishList() {
    ui->dishList->setRowCount(0);
    for(unsigned int i = 0; i < StaticData::getDishList().size(); i ++)
        if (StaticData::getDishMaintainList()[i] >= 0) {
            ui->dishList->setRowCount(ui->dishList->rowCount() + 1);
            Dish& cur = StaticData::getDishList()[i];
            ui->dishList->setItem(i, 0, new QTableWidgetItem(QString().setNum(cur.getDishID())));
            ui->dishList->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(cur.getImgDir())));
            ui->dishList->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(cur.getName())));
            ui->dishList->setItem(i, 3, new QTableWidgetItem(QString().setNum(cur.getPrice())));
            ui->dishList->setItem(i, 4, new QTableWidgetItem(QString().setNum(cur.getTimeNeeded())));
            ui->dishList->setItem(i, 5, new QTableWidgetItem(QString().setNum(cur.getRate())));
            ui->dishList->setItem(i, 6, new QTableWidgetItem(QString().setNum(cur.getRateNum())));
            for (int j = 0; j < 7; j ++)
                ui->dishList->item(i, j)->setData(Qt::UserRole, ui->dishList->item(i, j)->text());
        }
}

void AdminWindow::viewGuestList() {
    ui->guestList->setRowCount(0);
    for(unsigned int i = 0; i < StaticData::getGuestList().size(); i ++)
        if (StaticData::getGuestMaintainList()[i] >= 0) {
            ui->guestList->setRowCount(ui->guestList->rowCount() + 1);
            Guest& cur = StaticData::getGuestList()[i];
            ui->guestList->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(cur.getPhone())));
            ui->guestList->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(cur.getName())));
            ui->guestList->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(cur.getPassword())));
            ui->guestList->setItem(i, 3, new QTableWidgetItem(QString::fromStdString("0")));
            for (int j = 0; j < 4; j ++)
                ui->guestList->item(i, j)->setData(Qt::UserRole, ui->guestList->item(i, j)->text());
        }
}

void AdminWindow::viewChefList() {
    ui->chefList->setRowCount(0);
    for(unsigned int i = 0; i < StaticData::getChefList().size(); i ++)
        if (StaticData::getChefMaintainList()[i] >= 0) {
            ui->chefList->setRowCount(ui->chefList->rowCount() + 1);
            Chef& cur = StaticData::getChefList()[i];
            ui->chefList->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(cur.getPhone())));
            ui->chefList->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(cur.getName())));
            ui->chefList->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(cur.getPassword())));
            ui->chefList->setItem(i, 3, new QTableWidgetItem(QString::fromStdString("0")));
            for (int j = 0; j < 4; j ++)
                ui->chefList->item(i, j)->setData(Qt::UserRole, ui->chefList->item(i, j)->text());
        }
}

void AdminWindow::viewClerkList() {
    ui->clerkList->setRowCount(0);
    for(unsigned int i = 0; i < StaticData::getClerkList().size(); i ++)
        if (StaticData::getClerkMaintainList()[i] >= 0) {
            ui->clerkList->setRowCount(ui->clerkList->rowCount() + 1);
            Clerk& cur = StaticData::getClerkList()[i];
            ui->clerkList->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(cur.getPhone())));
            ui->clerkList->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(cur.getName())));
            ui->clerkList->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(cur.getPassword())));
            ui->clerkList->setItem(i, 3, new QTableWidgetItem(QString().setNum(cur.getRate())));
            ui->clerkList->setItem(i, 4, new QTableWidgetItem(QString().setNum(cur.getRateNum())));
            ui->clerkList->setItem(i, 5, new QTableWidgetItem(QString::fromStdString("0")));
            for (int j = 0; j < 6; j ++)
                ui->clerkList->item(i, j)->setData(Qt::UserRole, ui->clerkList->item(i, j)->text());
        }
}

void AdminWindow::addItem(QTableWidget *list) {
    if (list == NULL)
        return;
    list->setRowCount(list->rowCount() + 1);
    int index = ui->tabWidget->currentIndex();
    int buttomRow = list->rowCount() - 1;
    for (int i = 0; i < list->columnCount(); i ++)
        list->setItem(buttomRow, i, new QTableWidgetItem(""));
    QTableWidgetItem* curItem = list->item(buttomRow, 0);
    curItem->setData(Qt::UserRole, QString("999%1%2")
                     .arg(buttomRow + 1)
                     .arg(StaticData::getTableList().size()
                          + StaticData::getDishList().size()
                          + StaticData::getGuestList().size()
                          + StaticData::getChefList().size()
                          + StaticData::getClerkList().size()));
    if(index == 0) {
        list->item(buttomRow, 1)->setData(Qt::UserRole, 0);
        Table newTable(curItem->data(Qt::UserRole).toInt(), 0, 0);
        admin.addTable(newTable);
    }
    else if (index == 1) {
        list->item(buttomRow, 1)->setData(Qt::UserRole, 0);
        list->item(buttomRow, 2)->setData(Qt::UserRole, "");
        list->item(buttomRow, 3)->setData(Qt::UserRole, "img/dishes/default.png");
        list->item(buttomRow, 4)->setData(Qt::UserRole, 0);
        list->item(buttomRow, 5)->setData(Qt::UserRole, 0);
        list->item(buttomRow, 6)->setData(Qt::UserRole, 0);
        Dish newDish("", 0, -1, "img/dishes/default.png", curItem->data(Qt::UserRole).toInt());
        admin.addDish(newDish);
    }
    else if (index == 2) {
        list->item(buttomRow, 1)->setData(Qt::UserRole, "");
        list->item(buttomRow, 2)->setData(Qt::UserRole, "");
        list->item(buttomRow, 3)->setData(Qt::UserRole, 0);
        Guest newGuest(curItem->data(Qt::UserRole).toString().toStdString(), "");
        admin.addPerson(newGuest, 1);
    }
    else if (index == 3) {
        list->item(buttomRow, 1)->setData(Qt::UserRole, "");
        list->item(buttomRow, 2)->setData(Qt::UserRole, "");
        list->item(buttomRow, 3)->setData(Qt::UserRole, 0);
        Chef newChef(curItem->data(Qt::UserRole).toString().toStdString(), "");
        admin.addPerson(newChef, 2);
    }
    else if (index == 4) {
        list->item(buttomRow, 1)->setData(Qt::UserRole, "");
        list->item(buttomRow, 2)->setData(Qt::UserRole, "");
        list->item(buttomRow, 3)->setData(Qt::UserRole, 0);
        list->item(buttomRow, 4)->setData(Qt::UserRole, 0);
        list->item(buttomRow, 5)->setData(Qt::UserRole, 0);
        Clerk newClerk(curItem->data(Qt::UserRole).toString().toStdString(), "");
        admin.addPerson(newClerk, 3);
    }
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
            selectedRows[j] = true;
        }
    for(int i = list->rowCount() - 1; i >= 0; i --)
        if(selectedRows[i]) {
            markRemoved(ui->tabWidget->currentIndex(), i);
            list->removeRow(i);
        }
    delete []selectedRows;
}

void AdminWindow::markRemoved(int listTab, int row) {
    if (listTab == 0) {
        Table tmpTable(ui->tableList->item(row, 0)->data(Qt::UserRole).toInt(), 0, 0);
        StaticData::removeTable(tmpTable);
    }
    else if (listTab == 1) {
        Dish tmpDish("", 0, 0, "", ui->dishList->item(row, 0)->data(Qt::UserRole).toInt());
        StaticData::removeDish(tmpDish);
    }
    else if (listTab == 2) {
        Guest tmpGuest(ui->guestList->item(row, 0)->data(Qt::UserRole).toString().toStdString(), "");
        StaticData::removeGuest(tmpGuest);
    }
    else if (listTab == 3) {
        Chef tmpChef(ui->chefList->item(row, 0)->data(Qt::UserRole).toString().toStdString(), "");
        StaticData::removeChef(tmpChef);
    }
    else if (listTab == 4) {
        Clerk tmpClerk(ui->clerkList->item(row, 0)->data(Qt::UserRole).toString().toStdString(), "");
        StaticData::removeClerk(tmpClerk);
    }
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

void AdminWindow::saveList(int listTab) {
    if (listTab == 0) {
        for (int row = 0; row < ui->tableList->rowCount(); row ++)
            for (int col = 0; col < ui->tableList->columnCount(); col ++) {
                QTableWidgetItem* curItem = ui->tableList->item(row, col);
                //detected some difference at line row, update the whole line
                if (curItem->text() != curItem->data(Qt::UserRole).toString()) {
                    curItem = ui->tableList->item(row, 0);
                    //check and update col 0
                    if(!checkID(ui->tableList, row, 0)) {
                        ui->tableList->editItem(curItem);
                        return;
                    }
                    curItem = ui->tableList->item(row, 1);
                    //check and update col 1
                    if (!checkNum(curItem->text())) {
                        viewErrInfo("Invalid seat number at line " + ntos(row + 1));
                        ui->tableList->editItem(curItem);
                        return;
                    }
                    Table newTable(ui->tableList->item(row, 0)->text().toInt(),
                                   ui->tableList->item(row, 1)->text().toInt(),
                                   ui->tableList->item(row, 1)->text().toInt());
                    StaticData::modifyTable(ui->tableList->item(row, 0)->data(Qt::UserRole).toInt(), newTable);
                    setRowData(ui->tableList, row);

                    break;//this line has already been updated, exit inner loop and check the next line
                }
            }
    }
    else if (listTab == 1) {
        for (int row = 0; row < ui->dishList->rowCount(); row ++)
            for (int col = 0; col < ui->dishList->columnCount(); col ++) {
                QTableWidgetItem* curItem = ui->dishList->item(row, col);
                if (curItem->text() != curItem->data(Qt::UserRole).toString()) {
                    curItem = ui->dishList->item(row, 0);
                    if (curItem->text() != curItem->data(Qt::UserRole).toString())
                        if (!checkID(ui->dishList, row, 0)) {
                            ui->dishList->editItem(curItem);
                            return;
                        }
                    curItem = ui->dishList->item(row, 3);//price
                    if (curItem->text() != curItem->data(Qt::UserRole).toString())
                        if (!checkNum(curItem->text())) {
                            viewErrInfo("Invalid price");
                            ui->dishList->editItem(curItem);
                            return;
                        }
                    curItem = ui->dishList->item(row, 1);
                    if (curItem->text() != curItem->data(Qt::UserRole).toString())
                        if(curItem->text()[0] == '/') {
                            QString path = "img/" + ui->dishList->item(row, 0)->text() + "." + curItem->text().section('.', -1);
                            QFile::copy(curItem->text(), path);
                            curItem->setText(path);
                        }
                    break;
                }
        }
    }
}

bool AdminWindow::checkID(QTableWidget *list, int row, int col) {
    bool allDigit = true;
    list->item(row, col)->text().toInt(&allDigit, 10);
    if(!allDigit) {
        viewErrInfo("Invalid ID at line " + ntos(row + 1));
        return false;
    }
    for (int i = 0; i < list->rowCount(); i ++) {
        if(row != i && list->item(i, col)->text() == list->item(row, col)->text()) {
            viewErrInfo("Duplicate ID at lines " + ntos(row + 1) + " and " + ntos(i + 1));
            return false;
        }
    }
    return true;
}

bool AdminWindow::checkNum(QString numString) {
    bool allDigit = true;
    if(numString.toInt(&allDigit, 10) < 0)
        return false;
    return allDigit;
}

void AdminWindow::setRowData(QTableWidget *list, int row) {
    for (int i = 0; i < list->columnCount(); i ++)
        list->item(row, i)->setData(Qt::UserRole, list->item(row, i)->text());
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

void AdminWindow::on_refreshButton_clicked()
{
    int index = ui->tabWidget->currentIndex();
    if (index == 0) {
        for(int i = 0; i < ui->tableList->rowCount(); i ++)
            for (int j = 0; j < ui->tableList->columnCount(); j ++)
                ui->tableList->item(i, j)->setText(ui->tableList->item(i, j)->data(Qt::UserRole).toString());
    }
    else if (index == 1) {
        for(int i = 0; i < ui->dishList->rowCount(); i ++)
            for (int j = 0; j < ui->dishList->columnCount(); j ++)
                ui->dishList->item(i, j)->setText(ui->dishList->item(i, j)->data(Qt::UserRole).toString());
    }
    else if (index == 2) {
        for(int i = 0; i < ui->guestList->rowCount(); i ++)
            for (int j = 0; j < ui->guestList->columnCount(); j ++)
                ui->guestList->item(i, j)->setText(ui->guestList->item(i, j)->data(Qt::UserRole).toString());
    }
    else if (index == 3) {
        for(int i = 0; i < ui->chefList->rowCount(); i ++)
            for (int j = 0; j < ui->chefList->columnCount(); j ++)
                ui->chefList->item(i, j)->setText(ui->chefList->item(i, j)->data(Qt::UserRole).toString());
    }
    else if (index == 1) {
        for(int i = 0; i < ui->clerkList->rowCount(); i ++)
            for (int j = 0; j < ui->clerkList->columnCount(); j ++)
                ui->clerkList->item(i, j)->setText(ui->clerkList->item(i, j)->data(Qt::UserRole).toString());
    }
}

void AdminWindow::on_dishList_cellDoubleClicked(int row, int column)
{
    if (column != 1)
        return;
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.png *.bmp *.tif *.GIF)"));
    if (path.size() == 0)
        viewErrInfo("Empty file");
    else {
        QFile::copy(path, "img/copytest.png");
        ui->dishList->item(row, column)->setText(path);
    }
}
