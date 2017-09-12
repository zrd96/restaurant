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
    imgdir(imgdir) {
//        dishID = StaticData::db->queryID(name, price, timeNeeded, imgdir);
//        StaticData::db->doQuery("dish", "rate, rateNum", "dishid = \"" + getDishID() + "\"");
//        vector<vector<string> > dishInfo = StaticData::db->getResultList();
//        if (dishInfo.empty()) {
//                rate = 0;
//                rateNum = 0;
//                return;
//        }
//        rate = (dishInfo[0][0] == "NULL" ? 0: atof(dishInfo[0][0].c_str()));
//        rateNum = (dishInfo[0][1] == "NULL" ? 0: atoi(dishInfo[0][1].c_str()));
}

Dish::Dish(const Dish &dish):
    dishID(dish.getDishID()),
    name(dish.getName()),
    price(dish.getPrice()),
    rate(dish.getRate()),
    rateNum(dish.getRateNum()),
    timeNeeded(dish.getTimeNeeded()),
    imgdir(dish.getImgDir()) {}

void Dish::updateRate(double newRate) {
        rate = (rate * rateNum + newRate) / (++rateNum);
        Dish newDish(*this);
        StaticData::modifyDish(this->getDishID(), newDish);
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
