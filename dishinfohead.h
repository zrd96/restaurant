#ifndef DISHINFOHEAD_H
#define DISHINFOHEAD_H

#include <QWidget>
#include "dish.h"

namespace Ui {
class DishInfoHead;
}

class DishInfoHead : public QWidget
{
    Q_OBJECT

public:
    explicit DishInfoHead(const Dish &dish, QWidget *parent = 0);
    ~DishInfoHead();

private:
    Ui::DishInfoHead *ui;
};

#endif // DISHINFOHEAD_H
