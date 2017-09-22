#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "emptyresult.h"
#include "messagedlg.h"

ManagerWindow::ManagerWindow(const QString &user, QWidget *parent) :
    manager(Manager("x", "x", "x")),
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
    try {
        manager = StaticData::getManagerByPhone(user);
    } catch (EmptyResult) {
        viewErrInfo("Fatal error, user not found");
        this->close();
    }
    aboutMe = new AboutMeWidget(&manager, this, ui->selfTab);
    aboutMe->show();
    viewChefList();
    viewClerkList();
    ui->tabWidget->setCurrentIndex(0);
    on_tabWidget_currentChanged(0);
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::viewChefList() {
    ui->chefList->setRowCount(0);
    for (unsigned int i = 0; i < StaticData::getChefList().size(); i ++) {
        if (StaticData::getChefMaintainList()[i] >= 0) {
            Chef &cur = StaticData::getChefList()[i];
            int row = ui->chefList->rowCount();
            ui->chefList->setRowCount(row + 1);
            ui->chefList->setItem(row, 0, new QTableWidgetItem(cur.getPhone()));
            ui->chefList->setItem(row, 1, new QTableWidgetItem(cur.getName()));
            ui->chefList->setItem(row, 2, new QTableWidgetItem(QString().setNum(cur.getDishNum())));
            ui->chefList->setItem(row, 3, new QTableWidgetItem(QString().setNum(cur.getAverageRate())));
            ui->chefList->setItem(row, 4, new QTableWidgetItem(QString().setNum(cur.getAverageTimeDifference())));
        }
    }
}

void ManagerWindow::viewClerkList() {
    ui->clerkList->setRowCount(0);
    for (unsigned int i = 0; i < StaticData::getClerkList().size(); i ++) {
        if (StaticData::getClerkMaintainList()[i] >= 0) {
            Clerk &cur = StaticData::getClerkList()[i];
            int row = ui->clerkList->rowCount();
            ui->clerkList->setRowCount(row + 1);
            ui->clerkList->setItem(row, 0, new QTableWidgetItem(cur.getPhone()));
            ui->clerkList->setItem(row, 1, new QTableWidgetItem(cur.getName()));
            ui->clerkList->setItem(row, 2, new QTableWidgetItem(QString().setNum(cur.getServeTableNum())));
            ui->clerkList->setItem(row, 3, new QTableWidgetItem(QString().setNum(cur.getServeDishNum())));
            ui->clerkList->setItem(row, 4, new QTableWidgetItem(QString().setNum(cur.getAverageServeTime())));
            ui->clerkList->setItem(row, 5, new QTableWidgetItem(QString().setNum(cur.getRate())));
            ui->clerkList->setItem(row, 6, new QTableWidgetItem(QString().setNum(cur.getRateNum())));
        }
    }
}

void ManagerWindow::on_chefList_cellDoubleClicked(int row, int column)
{
    QString receiver = ui->chefList->item(row, 0)->text();
    MessageDlg *msgdlg = new MessageDlg(manager, receiver);
    msgdlg->show();
}

void ManagerWindow::on_clerkList_cellDoubleClicked(int row, int column)
{
    QString receiver = ui->clerkList->item(row, 0)->text();
    MessageDlg *msgdlg = new MessageDlg(manager, receiver);
    msgdlg->show();
}

void ManagerWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0)
        ui->title->setText("   View Chef Data List");
    else if (index == 1)
        ui->title->setText("   View Clerk Data List");
    else if (index == 2)
        ui->title->setText("   About Me");
}
