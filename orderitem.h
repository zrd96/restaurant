#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QWidget>
#include "order.h"

namespace Ui {
class OrderItem;
}

class OrderItem : public QWidget
{
    Q_OBJECT

public:
    explicit OrderItem(Order* order, QWidget *parent = 0);
    ~OrderItem();

signals:
    void orderClicked(Order* order);

private slots:
    void on_pushButton_clicked();

private:
    Ui::OrderItem *ui;
    Order* order;
};

#endif // ORDERITEM_H
