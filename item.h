#ifndef ITEM_H
#define ITEM_H

#include <QWidget>

#include "dish.h"
#include "guest.h"
#include "chef.h"
#include "rateitem.h"
#include <QMouseEvent>

namespace Ui {
class Item;
}

class Item : public QWidget
{
    Q_OBJECT

public:
    Item(Person& person, Dish& oriDish, const QString &listType, QWidget *parent = 0);
    //explicit Item(Guest& guest, const OrderedDish& dish, int num, QWidget *parent = 0);
    ~Item();
    QString getDishID() const {return dish.getDishID();}
    void setDishNumText(int finalNum);

public slots:
    void addItemNum();
    void subItemNum();

private:
    Ui::Item *ui;
    Dish dish;
    Person* person;
    Guest *guest;
    Chef* chef;
    int dishNum;
    QString listType;
    RateItem* itemRate;
    void mousePressEvent(QMouseEvent *ev);

private slots:
    void setNumTo();
    void rateDish(double newRate);

signals:
    void dishNumChanged(const QString& dishID, int finalNum);
    void numChanged();
    void refreshRequested();
};

#endif // ITEM_H
