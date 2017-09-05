#include "item.h"
#include "ui_item.h"
#include "dish.h"
#include "tools.h"
#include "guest.h"
#include "rateitem.h"
#include "staticdata.h"

Item::Item(Guest& guest, Dish& oriDish, QString listType, QWidget *parent) :
    guest(&guest),
    dish(oriDish),
    dishNum(0),
    listType(listType),
    QWidget(parent),
    ui(new Ui::Item)
{
    ui->setupUi(this);

    connect(ui->addButton, &QToolButton::clicked, this, [this] {this->addItemNum();});
    connect(ui->subButton, &QToolButton::clicked, this, [this] {this->subItemNum();});
    connect(ui->itemNum, SIGNAL(editingFinished()), this, SLOT(setNumTo()));

    QImage *dishImg = new QImage;
    if(!dishImg->load(QString::fromStdString(dish.getImgDir())))
        dishImg->load("img/dishes/default.jpg");
    ui->itemImg->setPixmap(QPixmap::fromImage(*dishImg));
    ui->itemImg->setScaledContents(true);
    ui->itemName->setPlainText(QString::fromStdString(dish.getName()));
    ui->itemRate->setValue((int)(20 * StaticData::getDishByID(dish.getDishID()).getRate()));
    ui->itemRateInfo->setText(QString("Rated %1/5 from %2 people")
                              .arg(StaticData::getDishByID(dish.getDishID()).getRate())
                              .arg(StaticData::getDishByID(dish.getDishID()).getRateNum()));
    ui->itemPrice->setText("￥ " + QString::fromStdString(ntos(dish.getPrice())));
    if(dish.getTimeNeeded() > 0)
        ui->itemStatus->setPlainText("Time Needed: " + QString::fromStdString(ntos(dish.getTimeNeeded())));
    try {
        OrderedDish& orderedDish = dynamic_cast<OrderedDish &> (oriDish);
        dishNum = orderedDish.getNum();
        //viewErrInfo(ntos(dishNum));
        ui->itemNum->setText(QString().setNum(dishNum));
        QString status;
        switch (orderedDish.getStatus()) {
            case 0 :
                status = "Not submitted";
                break;
            case 1:
                status = "Queueing";
                break;
            case 2:
                status = "Cooking";
                break;
            case 3:
                status = "Waiting to be served";
                break;
            case 4:
                status = "Served";
                break;
            case 5:
                status = "Checked out";
                ui->addButton->hide();
                ui->subButton->hide();
                ui->itemNum->hide();
                RateItem* rateItem = new RateItem(this);
                connect(rateItem, SIGNAL(rateSet(double)), this, SLOT(rateDish(double)));
                rateItem->setGeometry(860, 80, 150, 30);
                break;
        }
        ui->itemStatus->setPlainText(status);
        if(listType == "orderList") {
            ui->addButton->setEnabled(false);
            ui->subButton->setEnabled(false);
            ui->itemNum->setText("1");
            ui->itemNum->setEnabled(false);
        }
    } catch(bad_cast) {}
    //show();
}

Item::~Item()
{
    delete ui;
}
void Item::addItemNum() {
    guest->addDish(dish);
    dishNum ++;
    ui->itemNum->setText(QString().setNum(dishNum));
    //show();
    emit dishNumChanged(dish.getDishID(), dishNum);
}
void Item::subItemNum() {
    if(dishNum <= 0)
        return;
    guest->removeDish(dish);
    dishNum --;
    ui->itemNum->setText(QString().setNum(dishNum));
    //show();
    emit dishNumChanged(dish.getDishID(), dishNum);
    //viewErrInfo(ntos((int)guest->getOrderedDishList().size()));
}

void Item::setNumTo() {
    int num = ui->itemNum->text().toInt();
    int curNum = dishNum;

    if(num < 0) {
        for(int i = 0; i < curNum; i ++)
            subItemNum();
        ui->itemNum->setText(QString().setNum(dishNum));
    }
    else {
        for(int i = 0; i < curNum - num; i ++)
            subItemNum();
        for(int i = 0; i < num - curNum; i ++)
            addItemNum();
    }
}

void Item::setDishNumText(int finalNum) {
    ui->itemNum->setText(QString().setNum(finalNum));
    dishNum = finalNum;
}

void Item::rateDish(double newRate) {
    guest->rateDish(StaticData::getDishByID(dish.getDishID()), newRate);
    ui->itemRate->setValue((int)(20 * StaticData::getDishByID(dish.getDishID()).getRate()));
    ui->itemRateInfo->setText(QString("Rated %1/5 from %2 people")
                              .arg(StaticData::getDishByID(dish.getDishID()).getRate())
                              .arg(StaticData::getDishByID(dish.getDishID()).getRateNum()));
}
