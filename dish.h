#ifndef _DISH_H
#define _DISH_H

#include <string>

#include "tools.h"
#include "datamanager.h"

class Dish {
        private:
                int dishID;
                string name;
                double price;
                double rate;
                int rateNum;
                int timeNeeded;
                string imgdir;
        public:
                Dish(string name, double price, int timeNeeded = -1, string imgdir = "img/dishes/default.jpg");
                int getDishID() const {return dishID;}
                string getName() const {return name;}
                double getPrice() const {return price;}
                double getRate() const {return rate;}
                int getRateNum() const {return rateNum;}
                int getTimeNeeded() const {return timeNeeded;}
                string getImgdir() const {return imgdir;}
                bool updateRate(double newRate);
                void show() const;
                static void showAll();
};

class OrderedDish: public Dish {
        private:
                int orderer;
                int num;
                int orderedDishID;
        public:
                OrderedDish(const Dish &dish, int orderer, int num);
                OrderedDish(const Dish &dish, int orderedDishID, int orderer, int num);
                int getOrderer() const {return orderer;}
                int getNum() const {return num;}
                int getOrderedDishID() const {return orderedDishID;}
                void add() {num ++;}
                void sub() {num --;}
};

#endif
