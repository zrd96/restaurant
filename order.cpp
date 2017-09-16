#include "order.h"
#include "dish.h"
#include "tools.h"

#include <vector>
#include <QString>

Order::Order(const QString &orderer, const vector<OrderedDish>& orderedDishes, const QString &timeUniformed, int table):
    orderer(orderer),
    datetime(getTime()),
    orderID("O" + timeUniformed + orderer),
    orderSum(0),
    clerk("NULL"),
    table(table),
    status(0)
{
    for(unsigned int i = 0; i < orderedDishes.size(); i ++) {
        //orderedDishes[i].setStatus(0);
        for(int j = 0; j < orderedDishes[i].getNum(); j ++) {
            orderSum += orderedDishes[i].getPrice();
            dishes.push_back(orderedDishes[i].getOrderedDishID());
        }
    }
    checkStatus();
}

Order::Order(const QString &orderID, const QString &orderer, const QString &datetime, const QString &clerk, int table):
    orderer(orderer),
    datetime(datetime),
    orderID(orderID),
    orderSum(0),
    clerk(clerk),
    table(table),
    status(0) {
    checkStatus();
}

void Order::insertDish(const OrderedDish& dish) {
    orderSum += dish.getPrice();
    dishes.push_back(dish.getOrderedDishID());
    if(dish.getStatus() < 5 && status == 5)
        status = 4;
    if(dish.getStatus() < 4 && status == 4)
        status = 3;
}

int Order::checkStatus() {
    bool checkedOut = true;
    for(unsigned int i = 0; i < dishes.size(); i ++) {
        OrderedDish &cur = StaticData::getOrderedDishByID(dishes[i]);
        if(cur.getStatus() < 5) {
            checkedOut = false;
            break;
        }
    }
    if (checkedOut)
        return status = 5;

    bool allServed = true;
    for(unsigned int i = 0; i < dishes.size(); i ++) {
        OrderedDish &cur = StaticData::getOrderedDishByID(dishes[i]);
        if(cur.getStatus() < 4) {
            allServed = false;
            break;
        }
    }
    if (allServed)
        return status = 4;

    return status = 3;
}
