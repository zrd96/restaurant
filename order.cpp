#include "order.h"
#include "dish.h"
#include "tools.h"
#include "emptyresult.h"

#include <vector>
#include <QString>

Order::Order(const QString &orderer, const vector<OrderedDish>& orderedDishes, const QString &timeUniformed, int table):
    orderer(orderer),
    datetime(getTime()),
    orderID("O" + timeUniformed + orderer),
    orderSum(0),
    clerk("NULL"),
    table(table),
    rate(-1),
    status(0)
{
    for(unsigned int i = 0; i < orderedDishes.size(); i ++) {
        orderSum += orderedDishes[i].getPrice();
        dishes.push_back(orderedDishes[i].getOrderedDishID());
    }
    try {
        clerk = StaticData::getTableByID(table).getClerk();
    } catch (EmptyResult) {}
    checkStatus();
}

Order::Order(const QString &orderID, const QString &orderer, const QString &datetime, const QString &clerk, int table, double rate):
    orderer(orderer),
    datetime(datetime),
    orderID(orderID),
    orderSum(0),
    clerk(clerk),
    table(table),
    rate(rate),
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
    if (rate > 0)
        return status = 6;
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

void Order::rateClerk(double newRate) {
    if (status == 5) {
        Clerk &clerk = StaticData::getClerkByPhone(this->clerk);
        clerk.updateRate(newRate);
        rate = newRate;
        StaticData::modifyOrder(orderID, *this);
        status = 6;
    }
}
