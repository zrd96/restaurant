#include <string>
#include <vector>
#include <algorithm>

#include "dish.h"
#include "datamanager.h"
#include "staticdata.h"

using namespace std;

Dish::Dish(string name, double price, int timeNeeded, string imgdir): name(name), price(price), timeNeeded(timeNeeded), imgdir(imgdir) {
        dishID = StaticData::db->queryID(name, price, timeNeeded, imgdir);
        StaticData::db->doQuery("dish", "rate, rateNum", "dishid = \"" + ntos(getDishID()) + "\"");
        vector<vector<string> > dishInfo = StaticData::db->getResultList();
        rate = (dishInfo[0][0] == "NULL" ? 0: atof(dishInfo[0][0].c_str()));
        rateNum = (dishInfo[0][1] == "NULL" ? 0: atoi(dishInfo[0][1].c_str()));
}

bool Dish::updateRate(double newRate) {
        rate = (rate * rateNum + newRate) / (++rateNum);
        if(!StaticData::db->update("dish", "rateNum", ntos(rateNum), "dishid = " + ntos(dishID)))
                return false;
        return StaticData::db->update("dish", "rate", ntos(rate), "dishid = " + ntos(dishID));
}

void Dish::show() const {}

void Dish::showAll() {}

OrderedDish::OrderedDish(const Dish &dish, int orderer, int num): Dish(dish), orderer(orderer), num(num) {}

OrderedDish::OrderedDish(const Dish &dish, int orderedDishID, int orderer, int num): Dish(dish), orderedDishID(orderedDishID), orderer(orderer), num(num) {}
