#ifndef _CART_H
#define _CART_H

#include <vector>

#include "dish.h"

class Cart {
        public:
                Cart();
                int getNum() const {return num;}
                double getSumInCart() const {return sum;}
                vector<OrderedDish>& getOrderedDishList() {return orderedDishes;}
                bool submit(const QString &orderer, int table, const QString &request);
                //owner is used to generate orderedDishID
                bool add(const Dish& dish, const QString &owner, int tableNum);
                bool remove(const Dish& dish);
        private:
                int num;
                double sum;
                vector<OrderedDish> orderedDishes;
};

#endif
