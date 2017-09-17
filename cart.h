#ifndef _CART_H
#define _CART_H

#include <vector>

#include "dish.h"

class Cart {
        public:
                Cart();
                bool submit(const QString &orderer, int table, const QString &request);
                bool checkout();
                double getSumInCart() const {return sum;}
                void show() const;
                bool add(const Dish& dish, const QString &owner, int tableNum);
                bool remove(const Dish& dish);
                vector<OrderedDish>& getOrderedDishList() {return orderedDishes;}
        private:
                int num;
                double sum;
                vector<OrderedDish> orderedDishes;
};

#endif
