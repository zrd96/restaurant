#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <QString>
#include "dish.h"
#include "staticdata.h"

class StaticData;

class Order {
private:
    QString orderID;
    int table;
    QString orderer;
    vector<QString> dishes;
    QString datetime;
    double orderSum;
    QString clerk;
    int status;      //3 not all served, 4 all served, 5 all checked out, 6 clerk rated
    double rate;
    void insertDish(const OrderedDish& dish);
public:
    Order(const QString& orderer, const vector<OrderedDish>& orderedDishes, const QString &datetime, int table);
    Order(const QString &orderID, const QString& orderer, const QString& datetime, const QString &clerk, int table, double rate);

    QString getOrderID() const {return orderID;}
    QString getOrderer() const {return orderer;}
    QString getDatetime() const {return datetime;}
    double getOrderSum() const {return orderSum;}
    QString getClerk() const {return clerk;}
    void rateClerk(double newRate);
    int getTable() const {return table;}
    double getRate() const {return rate;}
    void setClerk(const QString &clerk) {this->clerk = clerk;}
    int checkStatus();
    vector<QString>& getOrderDishes() {return dishes;}
    friend class StaticData;
};

#endif // ORDER_H
