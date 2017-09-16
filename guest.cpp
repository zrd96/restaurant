#include <QString>
#include <vector>

#include "tools.h"
#include "datamanager.h"
#include "cart.h"
#include "mysqlmanager.h"
#include "guest.h"
#include "dish.h"
#include "staticdata.h"

Guest::Guest(const QString &phone, const QString &name): Person(phone, name), cart(Cart()), table(-1) {}
Guest::Guest(const QString &phone, const QString &name, const QString &password): Person(phone, name, password), cart(Cart()), table(-1) {}
Guest::Guest(const QString &phone, const QString &name, const QString &password, int table):  Person(phone, name, password), cart(Cart()), table(table) {}

void Guest::addDish(const Dish& dish) {
    cart.add(dish, getPhone(), table);
}

void Guest::removeDish(const Dish& dish) {
    cart.remove(dish);
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
    for(unsigned int i = 0; i < cart.getOrderedDishList().size(); i ++) {
        OrderedDish &cur = cart.getOrderedDishList()[i];
        cur.setTableNum(newTableNum);
        StaticData::modifyOrderedDish(cur.getOrderedDishID(), cur);
    }
}

void Guest::submitCart() {
    cart.submit(this->getPhone(), this->getTable());
}

void Guest::setPhone(const QString &newPhone) {
    for(unsigned int i = 0; i < cart.getOrderedDishList().size(); i ++) {
        OrderedDish &cur = cart.getOrderedDishList()[i];
        cur.setOrderer(newPhone);
        StaticData::modifyOrderedDish(cur.getOrderedDishID(), cur);
    }
    changePhone(newPhone);
}
