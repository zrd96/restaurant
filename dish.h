#ifndef _DISH_H
#define _DISH_H

#include <string>

#include "tools.h"
#include "datamanager.h"

class Dish {
        private:
                int id;
                string name;
                double price;
                double rate;
                int rateNum;
                int timeNeeded;
                int status;
                DataManager *mydb;
        public:
                Dish(DataManager *mydb, string name, double price, int timeNeeded);
                int getID() const {return id;}
                string getName() const {return name;}
                double getPrice() const {return price;}
                double getRate() const {return rate;}
                int getRateNum() const {return rateNum;}
                int getTimeNeeded() const {return timeNeeded;}
                int getStatus() const {return status;}
                bool updateRate(double newRate);
                void show() const;
                static void showAll();
};

#endif
