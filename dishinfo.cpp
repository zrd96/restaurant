#include "dishinfo.h"
#include "ui_dishinfo.h"
#include "dish.h"
#include "dishinfohead.h"
#include "comment.h"
#include "rate.h"
#include "staticdata.h"
#include <vector>

DishInfo::DishInfo(Dish &dish, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DishInfo)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setRowHeight(0, 300);
    DishInfoHead* head = new DishInfoHead(dish, this);
    ui->tableWidget->setCellWidget(0, 0, head);
    viewComments(dish);
}

DishInfo::~DishInfo()
{
    delete ui;
}

void DishInfo::viewComments(Dish &dish) {
    ui->tableWidget->setRowCount(1);
    dish.queryRate();
    for (unsigned int i = 0; i < dish.getRateList().size(); i ++) {
        Rate &rate = dish.getRateList()[i];
        Comment* newComment = new Comment(rate, this);
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row + 1);
        ui->tableWidget->setRowHeight(row, 220);
        ui->tableWidget->setCellWidget(row, 0, newComment);
    }
}
