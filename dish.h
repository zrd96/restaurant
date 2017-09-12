#ifndef _DISH_H
#define _DISH_H

#include <string>

#include "tools.h"
#include "datamanager.h"
#include "table.h"

class Dish {
        private:
                string dishID;
                string name;
                double price;
                double rate;
                int rateNum;
                int timeNeeded;
                string imgdir;
        public:
                Dish(string dishID, string name, double price, int timeNeeded = -1, double rate = 0, int rateNum = 0, string imgdir = "img/dishes/default.png");
                Dish(const Dish& dish);
                string getDishID() const {return dishID;}
                string getName() const {return name;}
                double getPrice() const {return price;}
                double getRate() const {return rate;}
                int getRateNum() const {return rateNum;}
                int getTimeNeeded() const {return timeNeeded;}
                string getImgDir() const {return imgdir;}
                void updateRate(double newRate);
                void show() const;
                static void showAll();
                virtual void doNothing() {}
};

class OrderedDish: public Dish {
        private:
                string orderer;
                string chef;
                int tableNum;
                int status;
                int num;
                string orderedDishID;
                string datetime;
        public:
                OrderedDish(const Dish& dish, const string &orderer, int tableNum, int status = -1, const string& chef = "NULL");
                OrderedDish(const Dish& dish, const string &orderedDishID, const string &orderer, int tableNum, int status = -1, const string& chef = "NULL");
                string getOrderer() const {return orderer;}
                string getOrderedDishID() const {return orderedDishID;}
                void setStatus(int status) {this->status = status;}
                int getStatus() const {return status;}
                int getNum() const {return num;}
                string getChef() {return chef;}
                string getDatetime() const {return datetime;}
                void setDatetime(const string &datetime) {this->datetime = datetime;}
                void add() {num ++;}
                void sub() {num --;}
                void setTableNum(int tableNum) {this->tableNum = tableNum;}
                void setOrderer(const string &orderer) {this->orderer = orderer;}
                void setOrderedDishID(const string& id) {orderedDishID = id;}
                void setChef(const string &chef) {this->chef = chef;}
                int getTable() const {return tableNum;}
                void doNothing() {}
};

#endif
