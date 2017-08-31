#include "item.h"
#include "ui_item.h"
#include "dish.h"
#include "tools.h"
#include "guest.h"

Item::Item(Guest& guest, const Dish& dish, int num, QWidget *parent) :
    guest(&guest),
    dish(dish),
    dishNum(0),
    QWidget(parent),
    ui(new Ui::Item)
{
    ui->setupUi(this);

    connect(ui->addButton, &QToolButton::clicked, this, [this] {this->addItemNum();});
    connect(ui->subButton, &QToolButton::clicked, this, [this] {this->subItemNum();});
    connect(ui->itemNum, SIGNAL(editingFinished()), this, SLOT(setNumTo()));

    setGeometry(60, num * 140, 1080, 140);

    QImage *dishImg = new QImage;
    if(!dishImg->load(QString::fromStdString(dish.getImgDir())))
        dishImg->load("img/dishes/default.jpg");
    *dishImg = dishImg->scaled(120, 120);
    ui->itemImg->setPixmap(QPixmap::fromImage(*dishImg));
    ui->itemName->setText(QString::fromStdString(dish.getName()));
    ui->itemRate->setValue((int)(dish.getRate() * 10));
    ui->itemRateInfo->setText("Rate: " + QString::fromStdString(ntos(dish.getRate())) + "/10\n Rate people: " + QString::fromStdString(ntos(dish.getRateNum())));
    ui->itemPrice->setText("￥ " + QString::fromStdString(ntos(dish.getPrice())));
    ui->itemStatus->setText("");
    if(dish.getTimeNeeded() > 0)
        ui->itemStatus->setText("Time Needed: " + QString::fromStdString(ntos(dish.getTimeNeeded())));
    //this->show();
}

Item::~Item()
{
    delete ui;
}
void Item::addItemNum() {
    dishNum ++;
    ui->itemNum->setText(QString().setNum(dishNum));
    guest->addDish(dish);

    //viewErrInfo(ntos((int)guest->getOrderedDishList().size()));
}
void Item::subItemNum() {
    if(dishNum <= 0)
        return;
    dishNum --;
    ui->itemNum->setText(QString().setNum(dishNum));
    guest->removeDish(dish);

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
