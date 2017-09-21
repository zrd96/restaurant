#ifndef _CLERK_H
#define _CLERK_H

#include <string>

#include "person.h"
#include "table.h"

class Table;

class Clerk: public Person {
        public:
                //Clerk(const QString &phone, const QString &name, double rate = 0, int rateNum = 0);
                Clerk(const QString &phone, const QString &name, const QString &password, double rate = 0, int rateNum = 0, int serveTableNum = 0, int serveDishNum = 0, double averageServeTime = 0);

                double getRate() const {return rate;}
                int getRateNum() const {return rateNum;}
                int getServeTableNum() const {return serveTableNum;}
                int getServeDishNum() const {return serveDishNum;}
                double getAverageServeTime() const {return averageServeTime;}
                vector<int> &getTableList() {return tableList;}
                vector<Msg>& getMsgList() {return msgList;}

                void checkTable();
                void takeTable(Table& table);
                void queryMsg();
                void readMsg(Msg* msg);
                bool updateRate(double newRate);
                void setPhone(const QString &newPhone);
        private:
                double rate;
                int rateNum;
                int serveTableNum;
                int serveDishNum;
                double averageServeTime;
                vector<int> tableList;
                vector<Msg> msgList;
                void serveDish(const QString &orderedDishID, const QString &finishTime, const QString &orderer);
};

#endif
