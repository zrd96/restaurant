#ifndef _CLERK_H
#define _CLERK_H

#include <string>

#include "person.h"
#include "table.h"

class Table;

class Clerk: public Person {
        public:
                Clerk(string phone, string name, double rate = 0, int rateNum = 0);
                bool takeTable(Table& table);
                void checkReadyDishes();
                void readMsg(Msg& msg);
                bool updateRate(double newRate);
        private:
                double rate;
                vector<Msg> unReadMsg;
                int rateNum;
                void serveDish(int orderedDishID, int tableNum, string orderer);
};

#endif
