#ifndef _CART_H
#define _CART_H

#include <vector>

#include "dish.h"

class Cart {
        public:
                Cart();
                bool add(const Dish &dish, int owner);
                bool remove(const Dish &dish);
                bool submit();
                bool checkout();
                double getSumInCart() const {return sum;}
                void show() const;
        protected:
                int num;
                double sum;
                vector<OrderedDish> orderedDishes;
};

#endif
