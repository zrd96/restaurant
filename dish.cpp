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

void Dish::updateRate(double newRate) {
        rate = (rate * rateNum + newRate) / (++rateNum);
        Dish newDish(*this);
        StaticData::modifyDish(this->getDishID(), newDish);
}

void Dish::queryRate() {
    if (StaticData::getRateList().empty())
        StaticData::queryRate();
    for (unsigned int i = 0; i < StaticData::getRateList().size(); i ++)
        if (StaticData::getRateList()[i].getObject() == this->dishID)
            rateList.push_back(StaticData::getRateList()[i]);
}

void Dish::show() const {}

void Dish::showAll() {}

OrderedDish::OrderedDish(const Dish& dish, const QString &orderer, int tableNum, int status, const QString &chef):
    Dish(dish),
    orderer(orderer),
    tableNum(tableNum),
    status(status),
    chef(chef),
    num(1) {}

OrderedDish::OrderedDish(const Dish& dish, const QString &orderedDishID, const QString &orderer, int tableNum, int status, const QString &chef):
    Dish(dish),
    orderedDishID(orderedDishID),
    orderer(orderer),
    tableNum(tableNum),
    status(status),
    chef(chef),
    num(1) {}
