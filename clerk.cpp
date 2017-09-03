#include <string>
#include <vector>
#include <cstring>
#include <cstdio>

#include "clerk.h"
#include "person.h"
#include "staticdata.h"
#include "tools.h"
#include "table.h"

Clerk::Clerk(string phone, string name, double rate, int rateNum): Person(phone, name), rate(rate), rateNum(rateNum) {
        vector<Msg> allMsg = StaticData::getMsgByReceiver(phone);
        for(unsigned int i = 0; i < allMsg.size(); i ++)
                if(allMsg[i].getState())
                        unReadMsg.push_back(allMsg[i]);
}

Clerk::Clerk(string phone, string name, string password, double rate, int rateNum): Person(phone, name, password), rate(rate), rateNum(rateNum) {}

bool Clerk::takeTable(Table& table) {
        return table.linkClerk(*this);
}

void Clerk::checkReadyDishes() {
        for(unsigned int i = 0; i < unReadMsg.size(); i ++)
                if(unReadMsg[i].getMsg().find("Dish ready") >= 0) {
                        int tableNum, orderedDishID;
                        char orderer[15];
                        sscanf(unReadMsg[i].getMsg().c_str(), "Dish ready%d%s%d", &tableNum, orderer, &orderedDishID);
                        serveDish(orderedDishID, tableNum, (string)orderer);
                }
}

void Clerk::readMsg(Msg& msg) {}

bool Clerk::updateRate(double newRate) {
        rate = (rate * rateNum + newRate) / ++rateNum;
        return (StaticData::db->update("person", "rate", ntos(rate), "phone = \"" + getPhone() + "\"")
                && StaticData::db->update("person", "rateNum", ntos(rateNum), "phone = \"" + getPhone() + "\""));
}

void Clerk::serveDish(int orderedDishID, int tableNum, string orderer) {
        StaticData::db->update("orderedDish", "status", "3", "id = " + ntos(orderedDishID));
}
