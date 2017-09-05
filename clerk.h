#ifndef _CLERK_H
#define _CLERK_H

#include <string>

#include "person.h"
#include "table.h"

class Table;

class Clerk: public Person {
        public:
                Clerk(string phone, string name, double rate = 0, int rateNum = 0);
                Clerk(string phone, string name, string password, double rate = 0, int rateNum = 0);
                bool takeTable(Table& table);
                void checkReadyDishes();
                void queryMsg();
                void readMsg(Msg* msg);
                bool updateRate(double newRate);
                double getRate() const {return rate;}
                int getRateNum() const {return rateNum;}
                void setPhone(string newPhone);
        private:
                double rate;
                vector<Msg*> unReadMsg;
                int rateNum;
                void serveDish(int orderedDishID, int tableNum, string orderer);
};

#endif
