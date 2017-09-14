#include <string>
#include <vector>
#include <cstring>
#include <cstdio>

#include "clerk.h"
#include "person.h"
#include "staticdata.h"
#include "tools.h"
#include "table.h"

Clerk::Clerk(string phone, string name, double rate, int rateNum):
    Person(phone, name),
    rate(rate),
    rateNum(rateNum) {}

Clerk::Clerk(string phone, string name, string password, double rate, int rateNum):
    Person(phone, name, password),
    rate(rate),
    rateNum(rateNum) {}

void Clerk::takeTable(Table& table) {
    this->tableList.push_back(table.getTableID());
    table.linkClerk(*this);
}

void Clerk::checkTable() {
    tableList.clear();
    for (unsigned int i = 0; i < StaticData::getTableList().size(); i ++)
        if(StaticData::getTableList()[i].getClerk() == this->getPhone())
            this->tableList.push_back(StaticData::getTableList()[i].getTableID());
}

void Clerk::checkReadyDishes() {
//        for(unsigned int i = 0; i < unReadMsg.size(); i ++)
//                if(unReadMsg[i]->getMsg().find("Dish ready") >= 0) {
//                        int tableNum, orderedDishID;
//                        char orderer[15];
//                        sscanf(unReadMsg[i]->getMsg().c_str(), "Dish ready%d%s%d", &tableNum, orderer, &orderedDishID);
//                        serveDish(orderedDishID, tableNum, (string)orderer);
//                }
}

void Clerk::queryMsg() {
    checkTable();
    msgList.clear();
    for (unsigned int i = 0; i < this->tableList.size(); i ++)
        StaticData::queryMsg("Table_" + ntos(tableList[i]));
    StaticData::queryMsg(this->getPhone());
    for (unsigned int i = 0; i < StaticData::getMsgList().size(); i ++) {
        Msg &cur = StaticData::getMsgList()[i];
        if (cur.getReceiver() == this->getPhone()
                || cur.getSender() == this->getPhone()) {
            msgList.push_back(cur);
        }
        else {
            for (unsigned int j = 0; j < this->tableList.size(); j ++)
                if (cur.getSender() == "Table_" + ntos(this->tableList[j])
                        || cur.getReceiver() == "Table_" + ntos(this->tableList[j])) {
                    msgList.push_back(cur);
                    break;
                }
        }
    }
}

void Clerk::readMsg(Msg* msg) {}

bool Clerk::updateRate(double newRate) {
        rate = (rate * rateNum + newRate) / ++rateNum;
        return (StaticData::db->update("person", "rate", ntos(rate), "phone = \"" + getPhone() + "\"")
                && StaticData::db->update("person", "rateNum", ntos(rateNum), "phone = \"" + getPhone() + "\""));
}

void Clerk::serveDish(const string &orderedDishID, int tableNum, string orderer) {
    OrderedDish &newOrderedDish = StaticData::getOrderedDishByID(orderedDishID);
    newOrderedDish.setStatus(4);
    StaticData::modifyOrderedDish(orderedDishID, newOrderedDish);
}

void Clerk::setPhone(string newPhone) {
//    for(unsigned int i = 0; i < unReadMsg.size(); i ++)
//        unReadMsg[i]->setReceiver(newPhone);
    changePhone(newPhone);
}
