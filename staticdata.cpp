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

//vector<Person> StaticData::personList;
DataManager* StaticData::db = NULL;

bool StaticData::queryDish() {
    dishList.clear();
        if (!db->doQuery("dish", "*"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(int i = 0; i < resultList.size(); i ++)
                dishList.push_back(Dish(resultList[i][1], atof(resultList[i][2].c_str()), atoi(resultList[i][5].c_str()), resultList[i][6], atoi(resultList[i][0].c_str())));
        return true;
}

bool StaticData::queryOrderedDish() {
        if (!db->doQuery("orderedDish", "*"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(int i = 0; i < resultList.size(); i ++)
                orderedDishList.push_back(OrderedDish(getDishByID(atoi(resultList[i][1].c_str())), atoi(resultList[i][0].c_str()), resultList[i][2], atoi(resultList[i][3].c_str()), atoi(resultList[i][4].c_str())));
        return true;
}

bool StaticData::queryMsg() {
        if (!db->doQuery("msg", "*"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for (int i = 0; i < resultList.size(); i ++)
                msgList.push_back(Msg(resultList[i][1], resultList[i][2], resultList[i][3], resultList[i][4], atoi(resultList[i][5].c_str())));
        return true;
}

bool StaticData::queryClerk() {
        if(!db->doQuery("person", "*", "type = 3"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(int i = 0; i < resultList.size(); i ++)
                clerkList.push_back(Clerk(resultList[i][0], resultList[i][1], atof(resultList[i][3].c_str()), atoi(resultList[i][4].c_str())));
        return true;
}

//bool StaticData::queryPerson() {return true;}

Dish& StaticData::getDishByID(int dishID) {
        for(int i = 0; i < dishList.size(); i ++)
                if(dishList[i].getDishID() == dishID)
                        return dishList[i];
        return dishList[0];
}

OrderedDish& StaticData::getOrderedDishByID(int orderedDishID) {
        for(int i = 0; i < orderedDishList.size(); i ++)
                if(orderedDishList[i].getOrderedDishID() == orderedDishID)
                        return orderedDishList[i];
        return orderedDishList[0];
}

vector<Msg> StaticData::getMsgByReceiver(string receiver) {
        vector<Msg> msgListByReceiver;
        for(int i = 0; i < msgList.size(); i ++)
                if(msgList[i].getReceiver() == receiver)
                        msgListByReceiver.push_back(msgList[i]);
        return msgListByReceiver;
}

string StaticData::getClerkPhoneByTable(int table) {
        if(!db->doQuery("tableList", "clerk", "id = " + ntos(table)))
                return "";
        return db->getResultList()[0][0];
}

//Person& getPersonByID(int id) {
//        return personList[0];
//}
