#ifndef DISHINFOHEAD_H
#define DISHINFOHEAD_H

#include <QWidget>
#include "dish.h"
#include <QCloseEvent>

namespace Ui {
class DishInfoHead;
}

class DishInfoHead : public QWidget
{
    Q_OBJECT

public:
    DishInfoHead(Dish &dish, bool isEditable = false, QWidget *parent = 0);
    ~DishInfoHead();

private:
    Ui::DishInfoHead *ui;
    QString imgdir;
    QString dishID;
    void setDishImg();
    void submit();
signals:
    void closeEvent(QCloseEvent* ev);
};

#endif // DISHINFOHEAD_H
