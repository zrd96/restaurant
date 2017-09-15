#include "item.h"
#include "ui_item.h"
#include "dish.h"
#include "tools.h"
#include "guest.h"
#include "rateitem.h"
#include "staticdata.h"
#include "emptyresult.h"
#include "dishinfo.h"
#include <QPushButton>
#include <QDebug>
#include <QString>

Item::Item(Person& person, Dish& oriDish, const QString &listType, QWidget *parent) :
    person(&person),
    dish(oriDish),
    dishNum(0),
    listType(listType),
    itemRate(new RateItem(this)),
    QWidget(parent),
    ui(new Ui::Item)
{
    ui->setupUi(this);

    connect(ui->addButton, &QToolButton::clicked, this, [this] {this->addItemNum();});
    connect(ui->subButton, &QToolButton::clicked, this, [this] {this->subItemNum();});
    connect(ui->itemNum, SIGNAL(editingFinished()), this, SLOT(setNumTo()));
    QImage *dishImg = new QImage;
    if(!dishImg->load((dish.getImgDir())))
        dishImg->load("img/dishes/default.png");
    ui->itemImg->setPixmap(QPixmap::fromImage(*dishImg));
    ui->itemImg->setScaledContents(true);
    ui->itemName->setText((dish.getName()));
    itemRate->setGeometry(420, 80, 150, 30);
    itemRate->setRate(StaticData::getDishByID(dish.getDishID()).getRate());

    ui->itemRateInfo->setText(QString("Rated %1/5 from %2 people")
                              .arg(StaticData::getDishByID(dish.getDishID()).getRate())
                              .arg(StaticData::getDishByID(dish.getDishID()).getRateNum()));
    ui->itemPrice->setText(QString("￥ %1").arg(dish.getPrice()));
    if(dish.getTimeNeeded() > 0)
        ui->itemStatus->setPlainText(QString("Time Needed: %1").arg(dish.getTimeNeeded()));
    guest = dynamic_cast<Guest*> (this->person);
    chef = dynamic_cast<Chef*> (this->person);
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
        if (chef != NULL) {
            ui->addButton->hide();
            ui->subButton->hide();
            ui->itemNum->hide();
            QPushButton *takeButton = new QPushButton(this);
            takeButton->setGeometry(860, 70, 80, 40);
            if (listType == "chefDishList") {
                takeButton->setText("Take this dish");
                connect(takeButton, &QPushButton::clicked, this, [takeButton, &orderedDish, this] () {
                    chef->takeDish(StaticData::getOrderedDishByID(orderedDish.getOrderedDishID()));
                    takeButton->setText("Taken");
                    takeButton->setEnabled(false);
                });
            }
            else if (listType == "chefTakenDishList") {
                takeButton->setText("Finish cooking");
                if(orderedDish.getStatus() >= 3) {
                    takeButton->setText("Finished");
                    takeButton->setEnabled(false);
                }
                connect(takeButton, &QPushButton::clicked, this, [takeButton, &orderedDish, this] () {
                    chef->finishDish(StaticData::getOrderedDishByID(orderedDish.getOrderedDishID()));
                    takeButton->setText("Finished");
                    takeButton->setEnabled(false);
                });
            }
        }
    } catch(bad_cast) {}

    //show();
}

Item::~Item()
{
    delete ui;
}
void Item::addItemNum() {
    if (guest == NULL)
        return;
    guest->addDish(dish);
    dishNum ++;
    ui->itemNum->setText(QString().setNum(dishNum));
    //show();
    emit dishNumChanged(dish.getDishID(), dishNum);
}
void Item::subItemNum() {
    if (guest == NULL || dishNum <= 0)
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
    try {
        Dish& staticDish = StaticData::getDishByID(dish.getDishID());
        guest->rateDish(staticDish, newRate);
        itemRate->setRate(staticDish.getRate());
        ui->itemRateInfo->setText(QString("Rated %1/5 from %2 people")
                                  .arg(staticDish.getRate())
                                  .arg(staticDish.getRateNum()));
    } catch (EmptyResult er) {
        viewErrInfo(er.getErrInfo());
    }
}

void Item::mousePressEvent(QMouseEvent *ev) {
    if (ev->x() >= 170 && ev->x() <= 170 + 880
            && ev->y() >= 10 && ev->y() <= 70) {
        DishInfo *dishInfo = new DishInfo(dish);
        dishInfo->show();
    }
}
