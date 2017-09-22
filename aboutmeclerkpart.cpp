#include "aboutmeclerkpart.h"
#include "ui_aboutmeclerkpart.h"
#include "clerk.h"
#include "rateitem.h"

AboutMeClerkPart::AboutMeClerkPart(const Clerk &clerk, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutMeClerkPart)
{
    ui->setupUi(this);
    ui->tableNumLabel->setText(QString().setNum(clerk.getServeTableNum()));
    ui->dishNumLabel->setText(QString().setNum(clerk.getServeDishNum()));
    ui->timeLabel->setText(QString("%1 min").arg(clerk.getAverageServeTime(), 0, 'f', 2));
    ui->rateInfo->setText(QString("Rated %1 from %2 people").arg(clerk.getRate()).arg(clerk.getRateNum()));
    RateItem *rate = new RateItem(this);
    rate->setGeometry(240, 245, 150, 30);
    rate->setRate(clerk.getRate());
    rate->show();
}

AboutMeClerkPart::~AboutMeClerkPart()
{
    delete ui;
}
