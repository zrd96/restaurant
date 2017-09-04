#include <vector>

#include "staticdata.h"
#include "datamanager.h"
#include "mysqlmanager.h"
#include "dish.h"
//#include "person.h"
#include "msg.h"

vector<Dish> StaticData::dishList;
vector<OrderedDish> StaticData::orderedDishList;
vector<Msg> StaticData::msgList;
vector<Clerk> StaticData::clerkList;
vector<Table> StaticData::tableList;

DataManager* StaticData::db = NULL;

bool StaticData::queryTable() {
    tableList.clear();
    if(!db->doQuery("tableList", "*"))
        return false;
    vector<vector<string> > resultList = db->getResultList();
    for(unsigned int i = 0; i < resultList.size(); i ++)
        tableList.push_back(Table(atoi(resultList[i][0].c_str()), atoi(resultList[i][1].c_str()), atoi(resultList[i][2].c_str()), resultList[i][3]));
    return true;
}

bool StaticData::queryDish() {
    dishList.clear();
        if (!db->doQuery("dish", "*"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                dishList.push_back(Dish(resultList[i][1], atof(resultList[i][2].c_str()), atoi(resultList[i][5].c_str()), resultList[i][6], atoi(resultList[i][0].c_str())));
        return true;
}

bool StaticData::queryOrderedDish() {
    orderedDishList.clear();
        if (!db->doQuery("orderedDish", "*"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                orderedDishList.push_back(OrderedDish(getDishByID(atoi(resultList[i][1].c_str())), atoi(resultList[i][0].c_str()), resultList[i][2], atoi(resultList[i][3].c_str()), atoi(resultList[i][4].c_str())));
        return true;
}

bool StaticData::queryMsg() {
    msgList.clear();
        if (!db->doQuery("msg", "*"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for (unsigned int i = 0; i < resultList.size(); i ++)
                msgList.push_back(Msg(resultList[i][1], resultList[i][2], resultList[i][3], resultList[i][4], atoi(resultList[i][5].c_str())));
        return true;
}

bool StaticData::queryClerk() {
    clerkList.clear();
        if(!db->doQuery("person", "*", "type = 3"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                clerkList.push_back(Clerk(resultList[i][0], resultList[i][1], atof(resultList[i][3].c_str()), atoi(resultList[i][4].c_str())));
        return true;
}

//bool StaticData::queryPerson() {return true;}

Dish& StaticData::getDishByID(int dishID) {
        for(unsigned int i = 0; i < dishList.size(); i ++)
                if(dishList[i].getDishID() == dishID)
                        return dishList[i];
        return dishList[0];
}

OrderedDish& StaticData::getOrderedDishByID(int orderedDishID) {
        for(unsigned int i = 0; i < orderedDishList.size(); i ++)
                if(orderedDishList[i].getOrderedDishID() == orderedDishID)
                        return orderedDishList[i];
        return orderedDishList[0];
}

vector<Msg> StaticData::getMsgByReceiver(string receiver) {
        vector<Msg> msgListByReceiver;
        for(unsigned int i = 0; i < msgList.size(); i ++)
                if(msgList[i].getReceiver() == receiver)
                        msgListByReceiver.push_back(msgList[i]);
        return msgListByReceiver;
}

vector<Msg> StaticData::getMsgBySender(string sender) {
        vector<Msg> msgListBySender;
        for(unsigned int i = 0; i < msgList.size(); i ++)
                if(msgList[i].getSender() == sender)
                        msgListBySender.push_back(msgList[i]);
        return msgListBySender;
}

string StaticData::getClerkPhoneByTable(int table) {
        if(!db->doQuery("tableList", "clerk", "id = " + ntos(table)))
                return "";
        return db->getResultList()[0][0];
}

string StaticData::getPersonNameByPhone(string phone) {
    if(!db->doQuery("person", "name", "phone = \"" + phone + "\""))
            return false;
    return db->getResultList()[0][0];
}

void StaticData::updateEverythingAboutUser(Person *person, string newPhone) {
    for(unsigned int i = 0; i < clerkList.size(); i ++)
        if(clerkList[i].getPhone() == person->getPhone())
            clerkList[i].setPhone(newPhone);
    for(unsigned int i = 0; i < orderedDishList.size(); i ++)
        if(orderedDishList[i].getOrderer() == person->getPhone())
            orderedDishList[i].setOrderer(newPhone);
    for(unsigned int i = 0; i < msgList.size(); i ++) {
        if(msgList[i].getSender() == person->getPhone())
            msgList[i].setSender(newPhone);
        if(msgList[i].getReceiver() == person->getPhone())
            msgList[i].setReceiver(newPhone);
    }
    db->update("msg", "sender", "\"" + newPhone + "\"", "sender = \"" + person->getPhone() + "\"");
    db->update("msg", "receiver", "\"" + newPhone + "\"", "receiverer = \"" + person->getPhone() + "\"");
    db->update("orderedDish", "orderer", "\"" + newPhone + "\"", "orderer = \"" + person->getPhone() + "\"");
    person->setPhone(newPhone);
}

//Person& getPersonByID(int id) {
//        return personList[0];
//}
