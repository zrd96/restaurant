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

    //uesed to track mouse, when clicked on the dish name text, show detailed dish info
    void mousePressEvent(QMouseEvent *ev);

private slots:
    void setNumTo();

signals:
    void dishNumChanged(const QString& dishID, int finalNum);
    void refreshRequested();
};

#endif // ITEM_H
