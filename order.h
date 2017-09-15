#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <QString>
#include "dish.h"
#include "staticdata.h"

class StaticData;

class Order {
private:
    QString orderer;
    QString datetime;
    QString orderID;
    double orderSum;
    int status;      //3 not all served, 4 all served, 5 all checked out, 6 clerk rated
    vector<OrderedDish> dishes;
    void insertDish(const OrderedDish dish);
public:
    Order(const QString& orderer, const vector<OrderedDish>& orderedDishes);
    Order(const QString& orderer, const QString& datetime);
    QString getOrderID() const {return orderID;}
    QString getOrderer() const {return orderer;}
    QString getDatetime() const {return datetime;}
    double getOrderSum() const {return orderSum;}
    int checkStatus();
    vector<OrderedDish>& getOrderDishes() {return dishes;}
    friend class StaticData;
};

#endif // ORDER_H
/**********************
 * Need to create a table to store order's info apart from orderedDishes
 * ********************/
