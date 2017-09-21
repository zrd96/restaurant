#ifndef _GUEST_H
#define _GUEST_H

#include <QString>
#include <vector>

#include "person.h"
#include "cart.h"
#include "table.h"
#include "dish.h"
#include "rate.h"

class Guest: public Person {
    public:
        //Guest(const QString &phone, const QString &name);
        Guest(const QString &phone, const QString &name, const QString &password, int table = -1);

        int getTable() const {return table;}

        double getSumInCart() const {return cart.getSumInCart();}
        vector<OrderedDish>& getOrderedDishList() {return cart.getOrderedDishList();}

        bool selectTable(Table& table);
        void addDish(const Dish& dish);
        void removeDish(const Dish& dish);
        void modifyTable(int newTableNum);
        void submitCart(const QString &request);
        void rateDish(Dish& dish, const Rate &rate);
        void rateClerk(Clerk& clerk, double rate);
        void freeTable();
        void setPhone(const QString &newPhone);
    private:
        int table;
        Cart cart;
};

#endif
