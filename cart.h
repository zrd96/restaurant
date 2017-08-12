#ifndef _CART_H
#define _CART_H

#include <vector>

#include "dish.h"

class Cart {
        public:
                Cart(DataManager *mydb);
                bool add(DishDB dish, int owner);
                bool remove(DishDB dish);
                bool submit();
                bool checkout();
                double getSumInCart() const {return sum;}
                void show() const;
        protected:
                DataManager *mydb;
                int num;
                double sum;
                vector<Dish> dishes;
};

#endif
