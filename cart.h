#ifndef _CART_H
#define _CART_H

#include <vector>

#include "dish.h"

class Cart {
        public:
                Cart();
                bool submit();
                bool checkout();
                double getSumInCart() const {return sum;}
                void show() const;
        protected:
                bool add(const Dish& dish, string owner, int tableNum);
                bool remove(const Dish& dish);
                int num;
                double sum;
                vector<OrderedDish> orderedDishes;
};

#endif
