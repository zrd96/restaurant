#include <QString>
#include <vector>
#include <cstring>
#include <cstdio>

#include "clerk.h"
#include "person.h"
#include "staticdata.h"
#include "tools.h"
#include "table.h"

//Clerk::Clerk(const QString &phone, const QString &name, double rate, int rateNum):
//    Person(phone, name),
//    rate(rate),
//    rateNum(rateNum)
//{}

Clerk::Clerk(const QString &phone, const QString &name, const QString &password, double rate, int rateNum, int serveTableNum, int serveDishNum, double averageServeTime):
    Person(phone, name, password),
    rate(rate),
    rateNum(rateNum),
    serveTableNum(serveTableNum),
    serveDishNum(serveDishNum),
    averageServeTime(averageServeTime)
{}

void Clerk::takeTable(Table& table) {
    this->tableList.push_back(table.getTableID());
    table.linkClerk(*this);
    for (unsigned int i = 0; i < StaticData::getOrderList().size(); i ++) {
        Order &cur = StaticData::getOrderList()[i];
        if (cur.getTable() == table.getTableID() && cur.checkStatus() < 5) {
            cur.setClerk(this->getPhone());
            StaticData::modifyOrder(cur.getOrderID(), cur);
        }
    }
    serveTableNum ++;
}

void Clerk::checkTable() {
    tableList.clear();
    for (unsigned int i = 0; i < StaticData::getTableList().size(); i ++)
        if(StaticData::getTableList()[i].getClerk() == this->getPhone())
            this->tableList.push_back(StaticData::getTableList()[i].getTableID());
}

void Clerk::queryMsg() {
    checkTable();
    msgList.clear();
    for (unsigned int i = 0; i < this->tableList.size(); i ++)
        StaticData::queryMsg(QString("Table_%1").arg(tableList[i]));
    StaticData::queryMsg(this->getPhone());
    for (unsigned int i = 0; i < StaticData::getMsgList().size(); i ++) {
        Msg &cur = StaticData::getMsgList()[i];
        if (cur.getReceiver() == this->getPhone()
                || cur.getSender() == this->getPhone()) {
            msgList.push_back(cur);
        }
        else {
            for (unsigned int j = 0; j < this->tableList.size(); j ++)
                if (cur.getSender() == QString("Table_%1").arg(this->tableList[j])
                        || cur.getReceiver() == QString("Table_%1").arg(this->tableList[j])) {
                    msgList.push_back(cur);
                    break;
                }
        }
    }
}

bool Clerk::updateRate(double newRate) {
        rate = (rate * rateNum + newRate) / ++rateNum;
        StaticData::modifyClerk(this->getPhone(), *this);
        return true;
}

void Clerk::serveDish(const QString &orderedDishID, const QString &finishTime, const QString &orderer) {
    OrderedDish &newOrderedDish = StaticData::getOrderedDishByID(orderedDishID);
    newOrderedDish.setStatus(4);
    StaticData::modifyOrderedDish(orderedDishID, newOrderedDish);
    averageServeTime = (averageServeTime * serveDishNum + getTimeDifference(finishTime)) / ++serveDishNum;
}

void Clerk::setPhone(const QString &newPhone) {
    for (unsigned int i = 0; i < msgList.size(); i ++) {
        Msg &cur = msgList[i];
        if (cur.getReceiver() == this->getPhone()) {
            cur.setReceiver(newPhone);
            StaticData::modifyMsg(cur.getMsgID(), cur);
        }
        if (cur.getSender() == this->getPhone()) {
            cur.setSender(newPhone);
            StaticData::modifyMsg(cur.getMsgID(), cur);
        }
    }
    changePhone(newPhone);
}
