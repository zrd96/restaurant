#include "item.h"
#include "ui_item.h"
#include "dish.h"
#include "tools.h"
#include "guest.h"
#include "rateitem.h"
#include "staticdata.h"
#include "emptyresult.h"
#include "dishinfo.h"
#include "comment.h"
#include <QPushButton>
#include <QDebug>
#include <QString>

Item::Item(Person& person, Dish& oriDish, const QString &listType, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Item),
    dish(oriDish),
    person(&person),
    guest(NULL),
    chef(NULL),
    dishNum(0),
    listType(listType),
    itemRate(new RateItem(this))
{
    ui->setupUi(this);

    connect(ui->addButton, &QPushButton::clicked, this, [this] {this->addItemNum();});
    connect(ui->subButton, &QPushButton::clicked, this, [this] {this->subItemNum();});
    connect(ui->itemNum, SIGNAL(editingFinished()), this, SLOT(setNumTo()));

    //normal condition: oriDish is indeed a dish
    QImage *dishImg = new QImage;
    if(!dishImg->load((dish.getImgDir())))
        dishImg->load("img/dishes/default.png");
    ui->itemImg->setPixmap(QPixmap::fromImage(*dishImg));
    ui->itemImg->setScaledContents(true);
    ui->itemName->setText((dish.getName()));
    itemRate->setGeometry(420, 80, 150, 30);
    itemRate->setRate(StaticData::getDishByID(dish.getDishID()).getRate());

    ui->itemRateInfo->setText(QString("Rated %1/5 from %2 people")
                              .arg(StaticData::getDishByID(dish.getDishID()).getRate(), 0, 'f', 2)
                              .arg(StaticData::getDishByID(dish.getDishID()).getRateNum()));
    ui->itemPrice->setText(QString("￥ %1").arg(dish.getPrice()));
    if(dish.getTimeNeeded() > 0)
        ui->itemStatus->setPlainText(QString("Time Needed: %1").arg(dish.getTimeNeeded()));

    //check whether a guest is viewing or a chef
    guest = dynamic_cast<Guest*> (this->person);
    chef = dynamic_cast<Chef*> (this->person);

    //condition: oriDish is actually an OrderedDish, then show order status
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
            case 5: {
                    status = "Checked out";
                    ui->addButton->hide();
                    ui->subButton->hide();
                    ui->itemNum->hide();
                    QPushButton* rateButon = new QPushButton(this);
                    rateButon->setGeometry(860, 80, 80, 40);
                    rateButon->setText("");
                    QIcon icon;
                    icon.addFile(QStringLiteral(":/res/img/img/comment.png"), QSize(), QIcon::Normal, QIcon::Off);
                    rateButon->setIcon(icon);
                    rateButon->setIconSize(QSize(40, 40));
                    connect(rateButon, &QPushButton::clicked, this, [&, this] {
                        Comment *newComment = new Comment(orderedDish);
                        connect(newComment, &Comment::closeEvent, this, [this] {emit refreshRequested();});
                    });
                }
                break;
            case 6: {
                    status = "Rated";
                    ui->addButton->hide();
                    ui->subButton->hide();
                    ui->itemNum->hide();
                    RateItem *rateItem =  new RateItem(this);
                    rateItem->setGeometry(860, 80, 150, 30);
                    rateItem->setRate(orderedDish.getUserRate());
                    rateItem->show();
                    QLabel *userRateInfo = new QLabel(this);
                    userRateInfo->setGeometry(860, 110, 150, 20);
                    userRateInfo->setText("You have rated this dish");
                    userRateInfo->show();
                }
                break;
        }
        ui->itemStatus->setPlainText(status);
        if(listType == "orderList") {
            ui->addButton->setEnabled(false);
            ui->subButton->setEnabled(false);
            ui->itemNum->setText("1");
            ui->itemNum->setEnabled(false);
        }

        //if a chef is viewing, show request and add buttons "Take" or "Finish"
        if (chef != NULL) {
            ui->addButton->hide();
            ui->subButton->hide();
            ui->itemNum->hide();
            QPushButton *takeButton = new QPushButton(this);
            takeButton->setGeometry(860, 70, 80, 40);
            QIcon iconTake;
            iconTake.addFile(QStringLiteral(":/res/img/img/checkout.png"), QSize(), QIcon::Normal, QIcon::Off);
            QIcon iconFinished;
            iconFinished.addFile(QStringLiteral(":/res/img/img/finished.png"), QSize(), QIcon::Normal, QIcon::Off);
            ui->itemStatus->setPlainText(orderedDish.getRequest());
            if (listType == "chefDishList") {
                takeButton->setText("");
                takeButton->setIcon(iconTake);
                takeButton->setIconSize(QSize(30, 30));
                connect(takeButton, &QPushButton::clicked, this, [&, takeButton] () {
                    chef->takeDish(StaticData::getOrderedDishByID(orderedDish.getOrderedDishID()));
                    takeButton->setText("");
                    QIcon iconActive;
                    iconActive.addFile(QStringLiteral(":/res/img/img/active-blue.png"), QSize(), QIcon::Normal, QIcon::Off);
                    takeButton->setIcon(iconActive);
                    takeButton->setIconSize(QSize(30, 30));
                    takeButton->setEnabled(false);
                });
            }
            else if (listType == "chefTakenDishList") {
                QIcon iconActive;
                iconActive.addFile(QStringLiteral(":/res/img/img/active-blue.png"), QSize(), QIcon::Normal, QIcon::Off);
                takeButton->setIcon(iconActive);
                takeButton->setIconSize(QSize(30, 30));
                takeButton->setText("");
                if(orderedDish.getStatus() >= 3) {
                    takeButton->setText("");
                    takeButton->setIcon(iconFinished);
                    takeButton->setEnabled(false);
                }
                connect(takeButton, &QPushButton::clicked, this, [&, takeButton] () {
                    chef->finishDish(StaticData::getOrderedDishByID(orderedDish.getOrderedDishID()));
                    takeButton->setText("");
                    QIcon iconFinished;
                    iconFinished.addFile(QStringLiteral(":/res/img/img/finished.png"), QSize(), QIcon::Normal, QIcon::Off);
                    takeButton->setIcon(iconFinished);
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

void Item::mousePressEvent(QMouseEvent *ev) {
    if (ev->x() >= 170 && ev->x() <= 170 + 880
            && ev->y() >= 10 && ev->y() <= 70) {
        DishInfo *dishInfo = new DishInfo(dish);
        dishInfo->show();
    }
}
