#ifndef _DISH_H
#define _DISH_H

#include <string>

#include "tools.h"
#include "datamanager.h"

class DishDB {
        private:
                int id;
                string name;
                double price;
                double rate;
                int rateNum;
                int timeNeeded;
        protected:
                DataManager *mydb;
        public:
                DishDB(DataManager *mydb, string name, double price, int timeNeeded);
                int getID() const {return id;}
                string getName() const {return name;}
                double getPrice() const {return price;}
                double getRate() const {return rate;}
                int getRateNum() const {return rateNum;}
                int getTimeNeeded() const {return timeNeeded;}
                bool updateRate(double newRate);
                void show() const;
                static void showAll();
};

class Dish: public DishDB {
        private:
                int orderer;
                int num;
        public:
                Dish(DishDB dish, int orderer, int num);
                int getOrderer() const {return orderer;}
                int getNum() const {return num;}
                void add() {num ++;}
                void sub() {num --;}
};

#endif
