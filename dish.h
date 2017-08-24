#ifndef _DISH_H
#define _DISH_H

#include <string>

#include "tools.h"
#include "datamanager.h"
#include "table.h"

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
                Dish(string name, double price, int timeNeeded = -1, string imgdir = "img/dishes/default.jpg", int confirmedDishID = -1);
                int getDishID() const {return dishID;}
                string getName() const {return name;}
                double getPrice() const {return price;}
                double getRate() const {return rate;}
                int getRateNum() const {return rateNum;}
                int getTimeNeeded() const {return timeNeeded;}
                string getImgDir() const {return imgdir;}
                bool updateRate(double newRate);
                void show() const;
                static void showAll();
};

class OrderedDish: public Dish {
        private:
                string orderer;
                int tableNum;
                int num;
                int orderedDishID;
        public:
                OrderedDish(const Dish dish, string orderer, int num, int tableNum);
                OrderedDish(const Dish dish, int orderedDishID, string orderer, int num, int tableNum);
                string getOrderer() const {return orderer;}
                int getNum() const {return num;}
                int getOrderedDishID() const {return orderedDishID;}
                void add() {num ++;}
                void sub() {num --;}
                int getTable() const {return tableNum;}
};

#endif
