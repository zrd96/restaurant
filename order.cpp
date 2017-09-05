#include "order.h"
#include "dish.h"
#include "tools.h"

#include <vector>
#include <QString>

Order::Order(const QString &orderer, const vector<OrderedDish>& orderedDishes):
    orderer(orderer),
    datetime(QString::fromStdString(getTime())),
    orderID("O" + datetime + orderer),
    orderSum(0),
    finished(true)
{
    for(unsigned int i = 0; i < orderedDishes.size(); i ++) {
        //orderedDishes[i].setStatus(0);
        for(int j = 0; j < orderedDishes[i].getNum(); j ++) {
            orderSum += orderedDishes[i].getPrice();
            dishes.push_back(orderedDishes[i]);
            if(orderedDishes[i].getStatus() < 5)
                finished = false;
        }
    }
}

void Order::insertDish(const OrderedDish dish) {
    orderSum += dish.getPrice();
    dishes.push_back(dish);
    if(dish.getStatus() < 5)
        finished = false;
}

Order::Order(const QString &orderer, const QString &datetime):
    orderer(orderer),
    datetime(datetime),
    orderID("O" + datetime + orderer),
    orderSum(0),
    finished(true) {}
