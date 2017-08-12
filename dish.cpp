#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "dish.h"
#include "datamanager.h"

using namespace std;

DishDB::DishDB(DataManager *mydb, string name, double price, int timeNeeded = -1): name(name), price(price), timeNeeded(timeNeeded) {
        id = mydb->queryID(name, price, timeNeeded);
        mydb->doQuery("dishDB", "rate, rateNum", "dishid = \"" + ntos(id) + "\"");
        vector<vector<string> > dishInfo = mydb->getResultList();
        rate = (dishInfo[0][0] == "NULL" ? 0: atof(dishInfo[0][0].c_str()));
        rateNum = (dishInfo[0][1] == "NULL" ? 0: atoi(dishInfo[0][1].c_str()));
}

bool DishDB::updateRate(double newRate) {
        rate = (rate * rateNum + newRate) / (++rateNum);
        return true;
}

void DishDB::show() const {}

void DishDB::showAll() {}

Dish::Dish(DishDB dish, int orderer, int num): DishDB(dish), orderer(orderer), num(num) {}
