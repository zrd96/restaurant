#include "guestwindow.h"
#include "ui_guestwindow.h"

GuestWindow::GuestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuestWindow)
{
    ui->setupUi(this);
}

GuestWindow::~GuestWindow()
{
    delete ui;
}

void GuestWindow::openWindow(const QString user) {
    this->show();
}
