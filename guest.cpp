#include <string>
#include <vector>

#include "tools.h"
#include "datamanager.h"
#include "cart.h"
#include "mysqlmanager.h"
#include "guest.h"
#include "dish.h"
#include "staticdata.h"

Guest::Guest(string phone, string name): Person(phone, name), Cart() {}
Guest::Guest(string phone, string name, string password): Person(phone, name, password), Cart() {}

bool Guest::addDish(const Dish& dish) {
    return add(dish, getPhone(), table);
}

bool Guest::removeDish(const Dish& dish) {
    return remove(dish);
}

bool Guest::selectTable(Table& table) {
    if(!table.addGuest()) {
        return false;
    }
    this->table = table.getTableID();
    return true;
}

void Guest::viewProgress() {}

bool Guest::rateDish(Dish& dish, double rate) {
        return dish.updateRate(rate);
}

bool Guest::rateClerk(Clerk& clerk, double rate) {
        return clerk.updateRate(rate);
}

void Guest::modifyTable(int newTableNum) {
    for(unsigned int i = 0; i < orderedDishes.size(); i ++)
        orderedDishes[i].setTableNum(newTableNum);
    for(unsigned int i = 0; i < StaticData::orderedDishList.size(); i ++)
        if(StaticData::orderedDishList[i].getOrderer() == this->getPhone())
            StaticData::orderedDishList[i].setTableNum(newTableNum);
}
