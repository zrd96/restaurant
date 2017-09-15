#ifndef DISHINFO_H
#define DISHINFO_H

#include <QWidget>
#include "dish.h"

namespace Ui {
class DishInfo;
}

class DishInfo : public QWidget
{
    Q_OBJECT

public:
    explicit DishInfo(Dish &dish, QWidget *parent = 0);
    ~DishInfo();

private:
    Ui::DishInfo *ui;
    void viewComments(Dish &dish);
};

#endif // DISHINFO_H
