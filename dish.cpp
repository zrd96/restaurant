#include <QString>
#include <vector>
#include <algorithm>

#include "dish.h"
#include "datamanager.h"
#include "staticdata.h"

using namespace std;

Dish::Dish(const QString &dishID, const QString &name, const QString &intro,  double price, int timeNeeded, double rate, int rateNum, QString imgdir):
    dishID(dishID),
    name(name),
    intro(intro),
    price(price),
    timeNeeded(timeNeeded),
    rate(rate),
    rateNum(rateNum),
    imgdir(imgdir)
{
    queryRate();
}

void Dish::updateRate(const Rate &newRate) {
        rate = (rate * rateNum + newRate.getRate()) / (++rateNum);
        StaticData::insertRate(newRate, 1);
        this->queryRate();
        StaticData::modifyDish(this->getDishID(), *this);
}

void Dish::queryRate() {
    this->rateList.clear();
    if (StaticData::getRateList().empty())
        StaticData::queryRate();
    rate = 0;
    rateNum = 0;
    for (unsigned int i = 0; i < StaticData::getRateList().size(); i ++) {
        Rate &cur = StaticData::getRateList()[i];
        if (cur.getObject() == this->dishID) {
            rate = (rate * rateNum + cur.getRate()) / (++rateNum);
            rateList.push_back(cur);
        }
    }
}

void Dish::show() const {}

void Dish::showAll() {}

//OrderedDish::OrderedDish(const Dish& dish, const QString &orderer, int tableNum, int status, const QString &chef):
//    Dish(dish),
//    orderer(orderer),
//    tableNum(tableNum),
//    status(status),
//    chef(chef),
//    num(1) {}

OrderedDish::OrderedDish(const Dish &dish, const QString &orderedDishID, const QString &orderer, int tableNum, const QString &datetime, const QString &request, int status, const QString &chef, double rate):
    Dish(dish),
    orderedDishID(orderedDishID),
    orderer(orderer),
    tableNum(tableNum),
    datetime(datetime),
    request(request),
    status(status),
    chef(chef),
    userRate(rate),
    num(1) {}
