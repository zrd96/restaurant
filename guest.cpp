#include <string>
#include <vector>

#include "tools.h"
#include "datamanager.h"
#include "cart.h"
#include "mysqlmanager.h"
#include "guest.h"
#include "dish.h"
#include "staticdata.h"

Guest::Guest(string phone, string name): Person(phone, name), Cart(), table(-1) {}
Guest::Guest(string phone, string name, string password): Person(phone, name, password), Cart(), table(-1) {}
Guest::Guest(string phone, string name, string password, int table):  Person(phone, name, password), Cart(), table(table) {}

void Guest::addDish(const Dish& dish) {
    add(dish, getPhone(), table);
}

void Guest::removeDish(const Dish& dish) {
    remove(dish);
}

bool Guest::selectTable(Table& table) {
    if(!table.addGuest()) {
        return false;
    }
    this->table = table.getTableID();
    modifyTable(table.getTableID());
    return true;
}

void Guest::viewProgress() {}

void Guest::rateDish(Dish& dish, double rate) {
        dish.updateRate(rate);
}

void Guest::rateClerk(Clerk& clerk, double rate) {
        clerk.updateRate(rate);
}

void Guest::modifyTable(int newTableNum) {
    for(unsigned int i = 0; i < orderedDishes.size(); i ++)
        orderedDishes[i].setTableNum(newTableNum);
    for(unsigned int i = 0; i < StaticData::getOrderedDishList().size(); i ++)
        if(StaticData::getOrderedDishList()[i].getOrderer() == this->getPhone())
            StaticData::getOrderedDishList()[i].setTableNum(newTableNum);
}

void Guest::setPhone(string newPhone) {
    for(unsigned int i = 0; i < orderedDishes.size(); i ++)
        orderedDishes[i].setOrderer(newPhone);
    changePhone(newPhone);
}
