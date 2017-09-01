#include <string>
#include <vector>

#include "tools.h"
#include "datamanager.h"
#include "cart.h"
#include "mysqlmanager.h"
#include "guest.h"
#include "dish.h"

Guest::Guest(string phone, string name): Person(phone, name), Cart() {}
Guest::Guest(string phone, string name, string password): Person(phone, name, password), Cart() {}

bool Guest::addDish(const Dish& dish) {
    return add(dish, getPhone(), table);
}

bool Guest::removeDish(const Dish& dish) {
    return remove(dish);
}

bool Guest::selectTable(Table& table) {
        this->table = table.getNum();
}

void Guest::viewProgress() {}

bool Guest::rateDish(Dish& dish, double rate) {
        return dish.updateRate(rate);
}

bool Guest::rateClerk(Clerk& clerk, double rate) {
        return clerk.updateRate(rate);
}
