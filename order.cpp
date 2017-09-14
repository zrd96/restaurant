#include "order.h"
#include "dish.h"
#include "tools.h"

#include <vector>
#include <QString>

Order::Order(const QString &orderer, const vector<OrderedDish>& orderedDishes):
    orderer(orderer),
    datetime(QString::fromStdString(getTimeUniform())),
    orderID("O" + datetime + orderer),
    orderSum(0),
    status(0)
{
    for(unsigned int i = 0; i < orderedDishes.size(); i ++) {
        //orderedDishes[i].setStatus(0);
        for(int j = 0; j < orderedDishes[i].getNum(); j ++) {
            orderSum += orderedDishes[i].getPrice();
            dishes.push_back(orderedDishes[i]);
        }
    }
    checkStatus();
}

Order::Order(const QString &orderer, const QString &datetime):
    orderer(orderer),
    datetime(datetime),
    orderID("O" + datetime + orderer),
    orderSum(0),
    status(0) {}

void Order::insertDish(const OrderedDish dish) {
    orderSum += dish.getPrice();
    dishes.push_back(dish);
    if(dish.getStatus() < 5 && status == 5)
        status = 4;
    if(dish.getStatus() < 4 && status == 4)
        status = 3;
}

int Order::checkStatus() {
    bool checkedOut = true;
    for(unsigned int i = 0; i < dishes.size(); i ++)
        if(dishes[i].getStatus() < 5) {
            checkedOut = false;
            break;
        }
    if (checkedOut) {
        status = 5;
        return status;
    }
    bool allServed = true;
    for(unsigned int i = 0; i < dishes.size(); i ++)
        if(dishes[i].getStatus() < 4) {
            allServed = false;
            break;
        }
    if (allServed) {
        status = 4;
        return status;
    }
    return status = 3;
}
