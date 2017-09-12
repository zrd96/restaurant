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
        Guest(string phone, string name, string password, int table);
        void addDish(const Dish& dish);
        void removeDish(const Dish& dish);
        bool selectTable(Table& table);
        int getTable() const {return table;}
        void viewProgress();
        void rateDish(Dish& dish, double rate);
        void rateClerk(Clerk& clerk, double rate);
        void modifyTable(int newTableNum);
        void setPhone(string newPhone);
    private:
        int table;
};

#endif
