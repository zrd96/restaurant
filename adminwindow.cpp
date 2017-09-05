#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QMessageBox>
#include "staticdata.h"

AdminWindow::AdminWindow(QWidget *parent) :
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
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::openWindow(const QString user) {
    this->show();
}
