#ifndef ITEM_H
#define ITEM_H

#include <QWidget>

#include "dish.h"
#include "guest.h"

namespace Ui {
class Item;
}

class Item : public QWidget
{
    Q_OBJECT

public:
    //explicit
    Item(Guest& guest, const Dish& dish, int num, QWidget *parent = 0);
    //explicit Item(Guest& guest, const OrderedDish& dish, int num, QWidget *parent = 0);
    ~Item();Dish dish;

public slots:
    void addItemNum();
    void subItemNum();

private:
    Ui::Item *ui;

    Guest *guest;
    int dishNum;

private slots:
    void setNumTo();
};

#endif // ITEM_H
