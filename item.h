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
    explicit
    Item(Guest& guest, Dish& dish, int num, QWidget *parent = 0);
    //explicit Item(Guest& guest, const OrderedDish& dish, int num, QWidget *parent = 0);
    ~Item();
    int getDishID() const {return dish.getDishID();}
    void setDishNumText(int finalNum);

public slots:
    void addItemNum();
    void subItemNum();

private:
    Ui::Item *ui;
    Dish dish;
    Guest *guest;
    int dishNum;

private slots:
    void setNumTo();

signals:
    void dishNumChanged(int dishID, int finalNum);
};

#endif // ITEM_H
