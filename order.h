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
    QString clerk;
    int table;
    int status;      //3 not all served, 4 all served, 5 all checked out, 6 clerk rated
    vector<QString> dishes;
    void insertDish(const OrderedDish& dish);
public:
    Order(const QString& orderer, const vector<OrderedDish>& orderedDishes, const QString &datetime, int table);
    Order(const QString &orderID, const QString& orderer, const QString& datetime, const QString &clerk, int table);
    QString getOrderID() const {return orderID;}
    QString getOrderer() const {return orderer;}
    QString getDatetime() const {return datetime;}
    double getOrderSum() const {return orderSum;}
    QString getClerk() const {return clerk;}
    int getTable() const {return table;}
    void setClerk(const QString &clerk) {this->clerk = clerk;}
    int checkStatus();
    vector<QString>& getOrderDishes() {return dishes;}
    friend class StaticData;
};

#endif // ORDER_H
/**********************
 * Need to create a table to store order's info apart from orderedDishes
 * ********************/
