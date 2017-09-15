#ifndef _CLERK_H
#define _CLERK_H

#include <string>

#include "person.h"
#include "table.h"

class Table;

class Clerk: public Person {
        public:
                Clerk(const QString &phone, const QString &name, double rate = 0, int rateNum = 0);
                Clerk(const QString &phone, const QString &name, const QString &password, double rate = 0, int rateNum = 0);
                void takeTable(Table& table);
                void checkReadyDishes();
                void queryMsg();
                vector<Msg>& getMsgList() {return msgList;}
                void readMsg(Msg* msg);
                bool updateRate(double newRate);
                double getRate() const {return rate;}
                int getRateNum() const {return rateNum;}
                void setPhone(const QString &newPhone);
                vector<int> &getTableList() {return tableList;}
                void checkTable();
        private:
                double rate;
                vector<Msg> msgList;
                int rateNum;
                vector<int> tableList;
                void serveDish(const QString &orderedDishID, int tableNum, const QString &orderer);
};

#endif
