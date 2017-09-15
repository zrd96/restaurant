#ifndef _GUEST_H
#define _GUEST_H

#include <QString>
#include <vector>

#include "person.h"
#include "cart.h"
#include "table.h"
#include "dish.h"

class Guest: public Person, public Cart {
    public:
        Guest(const QString &phone, const QString &name);
        Guest(const QString &phone, const QString &name, const QString &password);
        Guest(const QString &phone, const QString &name, const QString &password, int table);
        void addDish(const Dish& dish);
        void removeDish(const Dish& dish);
        bool selectTable(Table& table);
        int getTable() const {return table;}
        void viewProgress();
        void rateDish(Dish& dish, double rate);
        void rateClerk(Clerk& clerk, double rate);
        void modifyTable(int newTableNum);
        void setPhone(const QString &newPhone);
    private:
        int table;
};

#endif
