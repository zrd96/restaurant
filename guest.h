#ifndef _GUEST_H
#define _GUEST_H

#include <string>
#include <vector>

#include "person.h"
#include "cart.h"
#include "table.h"
#include "dish.h"

class Guest: public Person, public Cart {
    public:
        Guest(string phone, string name);
        Guest(string phone, string name, string password);
        bool addDish(const Dish& dish);
        bool removeDish(const Dish& dish);
        bool selectTable(Table& table);
        int getTable() const {return table;}
        void viewProgress();
        bool rateDish(Dish& dish, double rate);
        bool rateClerk(Clerk& clerk, double rate);
    private:
        int table;
};

#endif
