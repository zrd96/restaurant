#include "aboutmechefpart.h"
#include "ui_aboutmechefpart.h"
#include "chef.h"
#include "rateitem.h"

AboutMeChefPart::AboutMeChefPart(const Chef &chef, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutMeChefPart)
{
    ui->setupUi(this);
    ui->dishNumLabel->setText(QString().setNum(chef.getDishNum()));
    ui->timeDifferenceLabel->setText((chef.getAverageTimeDifference() > 0 ? "+" : "") + QString("%1%").arg(chef.getAverageTimeDifference()));
    ui->rateInfo->setText(QString("Rated %1 from %2 dishes").arg(chef.getAverageRate()).arg(chef.getRateNum()));
    RateItem *rate = new RateItem(this);
    rate->setGeometry(240, 165, 150, 30);
    rate->setRate(chef.getAverageRate());
    rate->show();
}

AboutMeChefPart::~AboutMeChefPart()
{
    delete ui;
}
