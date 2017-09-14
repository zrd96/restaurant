#include <string>
#include <vector>
#include <algorithm>

#include "dish.h"
#include "datamanager.h"
#include "staticdata.h"

using namespace std;

Dish::Dish(string dishID, string name, double price, int timeNeeded, double rate, int rateNum, string imgdir):
    dishID(dishID),
    name(name),
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
        if (StaticData::getRateList()[i].getObject().toStdString() == this->dishID)
            rateList.push_back(StaticData::getRateList()[i]);
}

void Dish::show() const {}

void Dish::showAll() {}

OrderedDish::OrderedDish(const Dish& dish, const string &orderer, int tableNum, int status, const string &chef):
    Dish(dish),
    orderer(orderer),
    tableNum(tableNum),
    status(status),
    chef(chef),
    num(1) {}

OrderedDish::OrderedDish(const Dish& dish, const string &orderedDishID, const string &orderer, int tableNum, int status, const string &chef):
    Dish(dish),
    orderedDishID(orderedDishID),
    orderer(orderer),
    tableNum(tableNum),
    status(status),
    chef(chef),
    num(1) {}
