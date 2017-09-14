#include <string>
#include <vector>

#include "chef.h"
#include "dish.h"
#include "staticdata.h"
#include "datamanager.h"
#include "mysqlmanager.h"

using namespace std;

Chef::Chef(string phone, string name): Person(phone, name) {}
Chef::Chef(string phone, string name, string password): Person(phone, name, password) {}

bool Chef::takeDish(OrderedDish &dish) {
    dish.setStatus(2);
    dish.setChef(this->getPhone());
    StaticData::modifyOrderedDish(dish.getOrderedDishID(), dish);
    dishTaken.push_back(dish);
    return true;
}

bool Chef::finishDish(OrderedDish &dish) {
        sendMsg("Table_" + ntos(dish.getTable()), "Dish ready " + dish.getOrderedDishID());
        dish.setStatus(3);
        StaticData::modifyOrderedDish(dish.getOrderedDishID(), dish);
//        for (unsigned int i = 0; i < dishTaken.size(); i ++)
//            if (dishTaken[i].getOrderedDishID() == dish.getOrderedDishID())
//                dishTaken.erase(dishTaken.begin() + i);
        return true;
}

void Chef::checkDish() {
    this->dishTaken.clear();
    for (unsigned int i = 0; i < StaticData::getOrderedDishList().size(); i ++)
        if (StaticData::getOrderedDishMaintainList()[i] >= 0
                && StaticData::getOrderedDishList()[i].getChef() == this->getPhone()
                && StaticData::getOrderedDishList()[i].getStatus() < 3)
            this->dishTaken.push_back(StaticData::getOrderedDishList()[i]);
}

void Chef::setPhone(string newPhone) {
    changePhone(newPhone);
}
