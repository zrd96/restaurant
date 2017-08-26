#include "clerkwindow.h"
#include "ui_clerkwindow.h"

ClerkWindow::ClerkWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClerkWindow)
{
    ui->setupUi(this);
}

ClerkWindow::~ClerkWindow()
{
    delete ui;
}
