#include "dishinfohead.h"
#include "ui_dishinfohead.h"
#include "dish.h"
#include "rateitem.h"
#include "tools.h"

DishInfoHead::DishInfoHead(const Dish &dish, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DishInfoHead)
{
    ui->setupUi(this);
    QImage *dishImg = new QImage;
    if(!dishImg->load(QString::fromStdString(dish.getImgDir())))
        dishImg->load("img/dishes/default.png");
    ui->dishImg->setPixmap(QPixmap::fromImage(*dishImg));
    ui->dishImg->setScaledContents(true);
    ui->dishName->setPlainText(QString::fromStdString(dish.getName()));
    ui->dishPrice->setText(QString("￥ %1").arg(dish.getPrice()));
    ui->dishIntro->setPlainText("No introduction");
    ui->dishRateInfo->setText(QString("Rated %1/5 from %2 people").arg(dish.getRate()).arg(dish.getRateNum()));
    RateItem *rateItem = new RateItem(this);
    rateItem->setGeometry(130, 250, 150, 30);
    rateItem->setRate(dish.getRate());
    rateItem->show();
    this->show();
}

DishInfoHead::~DishInfoHead()
{
    delete ui;
}
