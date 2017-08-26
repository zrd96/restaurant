#include "chefwindow.h"
#include "ui_chefwindow.h"

ChefWindow::ChefWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChefWindow)
{
    ui->setupUi(this);
}

ChefWindow::~ChefWindow()
{
    delete ui;
}
