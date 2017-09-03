#include "itemlist.h"
#include "ui_itemlist.h"

ItemList::ItemList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemList)
{
    ui->setupUi(this);
    this->resize(1080, 0);
    //this->setSizePolicy(QSizePolicy(0));
}

ItemList::~ItemList()
{
    delete ui;
}

void ItemList::addItem(Item *item) {
    //this->setMinimumSize(1080, this->height() + 140);
    //this->resize(1080, this->height() + 140);
    //this->setGeometry(0, 0, 1080, this->height() + 140);
    this->setMinimumSize(1080, this->height() + 140);
    item->setGeometry(60, this->height() - 140, 1080, 140);
    item->show();
    this->show();
}

