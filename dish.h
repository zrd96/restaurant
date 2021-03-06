#ifndef _DISH_H
#define _DISH_H

#include <QString>

#include "tools.h"
#include "datamanager.h"
#include "table.h"
#include "rate.h"

class Dish {
        private:
                QString dishID;
                QString name;
                QString intro;
                double price;
                double rate;
                int rateNum;
                int timeNeeded;
                QString imgdir;
                vector<Rate> rateList;
        public:
                Dish(const QString &dishID, const QString &name, const QString &intro, double price, int timeNeeded = -1, double rate = 0, int rateNum = 0, QString imgdir = "img/dishes/default.png");

                QString getDishID() const {return dishID;}
                QString getName() const {return name;}
                QString getIntro() const {return intro;}
                double getPrice() const {return price;}
                double getRate() const {return rate;}
                int getRateNum() const {return rateNum;}
                int getTimeNeeded() const {return timeNeeded;}
                QString getImgDir() const {return imgdir;}
                vector<Rate>& getRateList() {return rateList;}

                void updateRate(const Rate &newRate);
                void queryRate();

                //it dose nothing but makes Dish and OrderedDish polymorphic classes
                virtual void doNothing() {}
};

class OrderedDish: public Dish {
private:
    QString orderedDishID;
    QString orderer;
    QString request;
    int num;
    int tableNum;
    QString datetime;

    QString chef;
    int status;
    double userRate;
public:
    //OrderedDish(const Dish& dish, const QString &orderer, int tableNum, int status = -1, const QString& chef = "NULL");
    OrderedDish(const Dish& dish, const QString &orderedDishID, const QString &orderer, int tableNum, const QString &datetime, const QString &request = "", int status = -1, const QString& chef = "NULL", double rate = -1);

    QString getOrderedDishID() const {return orderedDishID;}
    QString getOrderer() const {return orderer;}
    QString getRequest() const {return request;}
    int getNum() const {return num;}
    int getTable() const {return tableNum;}
    QString getDatetime() const {return datetime;}

    QString getChef() {return chef;}
    void setStatus(int status) {this->status = status;}
    int getStatus() const {return status;}
    double getUserRate() const {return this->userRate;}

    void setRate(double rate);
    void add() {num ++;}
    void sub() {num --;}
    void setTableNum(int tableNum);
    void setOrderer(const QString &orderer);
    //void setOrderedDishID(const QString& id) {orderedDishID = id;}
    void setChef(const QString &chef);
    void doNothing() {}
};
/* status:
 * 0  not submitted
 * 1  queueing
 * 2  cooking
 * 3  waiting to be served (cooked)
 * 4  served
 * 5  cheched out
 * 6  rated
*/

#endif
