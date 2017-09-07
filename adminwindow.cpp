#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QMessageBox>
#include <QTableWidget>
#include "staticdata.h"

AdminWindow::AdminWindow(const QString& user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    QMessageBox::information(NULL, "StaticData",
                             QString("tableList: %1\n"
                                     "dishList: %2 \n"
                                     "orderedDishList: %3\n"
                                     "msgList: %4\n")
                             .arg(StaticData::tableList.size())
                             .arg(StaticData::dishList.size())
                             .arg(StaticData::orderedDishList.size())
                             .arg(StaticData::msgList.size()));
    ui->tableList->setColumnWidth(0, 410);
    ui->tableList->setColumnWidth(1, 410);
    ui->dishList->setColumnWidth(0, 80);    //dishID
    ui->dishList->setColumnWidth(1, 105);   //imgdir
    ui->dishList->setColumnWidth(2, 400);   //name
    ui->dishList->setColumnWidth(3, 80);    //price
    ui->dishList->setColumnWidth(4, 80);    //time
    ui->dishList->setColumnWidth(5, 80);    //rate
    ui->dishList->setColumnWidth(6, 80);    //rateNum
    viewTableList();
    viewDishList();
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

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::openWindow(const QString user) {
    this->show();
}

void AdminWindow::on_refreshButtonTable_clicked()
{
    viewTableList();
}

void AdminWindow::on_restoreButtonTable_clicked()
{
    viewTableList();
}

void AdminWindow::on_addButtonTable_clicked()
{
    ui->tableList->setRowCount(ui->tableList->rowCount() + 1);
}

void AdminWindow::on_removeButtonDish_clicked()
{
    QList<QTableWidgetSelectionRange> selectedRowList = ui->dishList->selectedRanges();
    bool* selectedRows = new bool[ui->dishList->rowCount()];
    for(int i = 0; i < ui->dishList->rowCount(); i ++)
        selectedRows[i] = false;
    for (unsigned int i = 0; i < selectedRowList.size(); i ++)
        for (unsigned int j = selectedRowList[i].topRow(); j <= selectedRowList[i].bottomRow(); j ++) {
            viewErrInfo(ntos((int)j));
            selectedRows[j] = true;
        }
    for(int i = ui->dishList->rowCount() - 1; i >= 0; i --)
        if(selectedRows[i])
            ui->dishList->removeRow(i);

    delete []selectedRows;
}
