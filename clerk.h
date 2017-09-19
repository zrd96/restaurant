#ifndef _CLERK_H
#define _CLERK_H

#include <string>

#include "person.h"
#include "table.h"

class Table;

class Clerk: public Person {
        public:
                Clerk(const QString &phone, const QString &name, double rate = 0, int rateNum = 0);
                Clerk(const QString &phone, const QString &name, const QString &password, double rate, int rateNum, int serveTableNum, int serveDishNum, double averageServeTime);
                void takeTable(Table& table);
                void checkReadyDishes();
                void queryMsg();
                vector<Msg>& getMsgList() {return msgList;}
                void readMsg(Msg* msg);
                bool updateRate(double newRate);
                int getServeTableNum() const {return serveTableNum;}
                int getServeDishNum() const {return serveDishNum;}
                double getAverageServeTime() const {return averageServeTime;}
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
                int serveDishNum;
                double averageServeTime;
                int serveTableNum;
                void serveDish(const QString &orderedDishID, const QString &finishTime, const QString &orderer);
};

#endif
