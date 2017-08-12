#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "dish.h"
#include "datamanager.h"

using namespace std;

Dish::Dish(DataManager *mydb, string name, double price, int timeNeeded = -1): name(name), price(price), timeNeeded(timeNeeded) {
        id = mydb->queryID(name, price, timeNeeded);
        mydb->doQuery("dishes", "rate, rateNum", "dishid = \"" + ntos(id) + "\"");
        vector<vector<string> > dishInfo = mydb->getResultList();
        rate = (dishInfo[0][0] == "NULL" ? 0: atof(dishInfo[0][0].c_str()));
        rateNum = (dishInfo[0][1] == "NULL" ? 0: atoi(dishInfo[0][1].c_str()));
}

bool Dish::updateRate(double newRate) {
        rate = (rate * rateNum + newRate) / (++rateNum);
        return true;
}

void Dish::show() const {}

void Dish::showAll() {}

