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

bool Chef::takeDish(const OrderedDish &dish) {
        if(StaticData::db->update("orderedDish", "status", "1", "id = " + ntos(dish.getOrderedDishID()))) {
                dishTaken.push_back(dish);
                return true;
        }
        return false;
}

bool Chef::finishDish(const OrderedDish &dish) {
        sendMsg(StaticData::getClerkPhoneByTable(dish.getTable()), "Dish ready " + ntos(dish.getTable()) + " " + dish.getOrderer() + " " + ntos(dish.getOrderedDishID()));
        return StaticData::db->update("orderedDish", "status", "2", "id = " + ntos(dish.getOrderedDishID()));
}


