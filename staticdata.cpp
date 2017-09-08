#include <vector>
#include <QString>

#include "staticdata.h"
#include "datamanager.h"
#include "mysqlmanager.h"
#include "dish.h"
//#include "person.h"
#include "msg.h"
#include "guest.h"
#include "clerk.h"
#include "chef.h"

vector<Dish> StaticData::dishList;
vector<OrderedDish> StaticData::orderedDishList;
vector<Order> StaticData::orderList;
vector<Msg> StaticData::msgList;
vector<Clerk> StaticData::clerkList;
vector<Chef> StaticData::chefList;
vector<Guest> StaticData::guestList;
vector<Table> StaticData::tableList;

vector<int> StaticData::dishMaintainList;
vector<int> StaticData::orderedDishMaintainList;
vector<int> StaticData::msgMaintainList;
vector<int> StaticData::guestMaintainList;
vector<int> StaticData::chefMaintainList;
vector<int> StaticData::clerkMaintainList;
vector<int> StaticData::tableMaintainList;

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
        for(unsigned int i = 0; i < resultList.size(); i ++) {
            OrderedDish tmp(getDishByID(atoi(resultList[i][1].c_str())),
                    atoi(resultList[i][0].c_str()),
                    resultList[i][2],
                    atoi(resultList[i][3].c_str()),
                    atoi(resultList[i][4].c_str()));
            tmp.setDatetime(resultList[i][5]);
            orderedDishList.push_back(tmp);
        }
        return true;
}

void StaticData::clearMsgList() {msgList.clear();}

bool StaticData::queryMsg(string person) {
        if (!db->doQuery("msg", "*", "sender = \"" + person + "\" or receiver = \"" + person + "\""))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for (unsigned int i = 0; i < resultList.size(); i ++) {
            int msgID = atoi(resultList[i][0].c_str());
            bool msgExists = false;
            for (unsigned int j = 0; j < msgList.size(); j ++)
                if(msgID == msgList[j].getMsgID()) {
                    msgExists = true;
                    break;
                }
            if(!msgExists)
                msgList.push_back(Msg(resultList[i][1], resultList[i][2], resultList[i][3], resultList[i][4], atoi(resultList[i][5].c_str()), atoi(resultList[i][0].c_str())));
        }
        return true;
}

bool StaticData::queryClerk() {
    clerkList.clear();
        if(!db->doQuery("person", "*", "type = 3"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                clerkList.push_back(Clerk(resultList[i][0], resultList[i][1], resultList[i][2], atof(resultList[i][3].c_str()), atoi(resultList[i][4].c_str())));
        return true;
}

bool StaticData::queryChef() {
    chefList.clear();
        if(!db->doQuery("person", "*", "type = 2"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                chefList.push_back(Chef(resultList[i][0], resultList[i][1], resultList[i][2]));
        return true;
}

bool StaticData::queryGuest() {
    guestList.clear();
        if(!db->doQuery("person", "*", "type = 1"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                guestList.push_back(Guest(resultList[i][0], resultList[i][1], resultList[i][2]));
        return true;
}

bool StaticData::queryOrder() {
    queryOrderedDish();
    orderList.clear();
    for(unsigned int i = 0; i < orderedDishList.size(); i ++) {
        bool found = 0;
        for(unsigned j = 0; j < orderList.size(); j ++)
            if(orderList[j].getOrderer().toStdString() == orderedDishList[i].getOrderer()
                    && orderList[j].getDatetime().toStdString() == orderedDishList[i].getDatetime()) {
                found = 1;
                orderList[j].insertDish(orderedDishList[i]);
                break;
            }
        if(!found) {
            Order newOrder(QString::fromStdString(orderedDishList[i].getOrderer()), QString::fromStdString(orderedDishList[i].getDatetime()));
            newOrder.insertDish(orderedDishList[i]);
            orderList.push_back(newOrder);
        }
    }
}

void StaticData::insertTable(const Table& table, int type) {
    tableList.push_back(table);
    tableMaintainList.push_back(type);
}

void StaticData::insertDish(const Dish& dish, int type) {
    dishList.push_back(dish);
    dishMaintainList.push_back(type);
}

void StaticData::insertOrderedDish(const OrderedDish& orderedDish, int type) {
    orderedDishList.push_back(orderedDish);
    orderedDishMaintainList.push_back(type);
}

void StaticData::insertMsg(const Msg& msg, int type) {
    msgList.push_back(msg);
    msgMaintainList.push_back(type);
}

void StaticData::insertGuest(const Guest& guest, int type) {
    guestList.push_back(guest);
    guestMaintainList.push_back(type);
}

void StaticData::insertClerk(const Clerk& clerk, int type) {
    clerkList.push_back(clerk);
    clerkMaintainList.push_back(type);
}

void StaticData::insertChef(const Chef& chef, int type) {
    chefList.push_back(chef);
    chefMaintainList.push_back(type);
}

void StaticData::insertOrder(const Order& order) {
    orderList.push_back(order);
}

void StaticData::removeTable(const Table& table) {
    for (unsigned int i = 0; i < tableList.size(); i ++) {
        if(table.getTableID() == tableList[i].getTableID()) {
            tableMaintainList.push_back(-1);
            break;
        }
    }
}

void StaticData::removeDish(const Dish& dish) {
    for (unsigned int i = 0; i < dishList.size(); i ++) {
        if(dish.getDishID() == dishList[i].getDishID()) {
            dishMaintainList.push_back(-1);
            break;
        }
    }
}

void StaticData::removeOrderedDish(const OrderedDish& orderedDish) {
    for (unsigned int i = 0; i < orderedDishList.size(); i ++) {
        if(orderedDish.getOrderedDishID() == orderedDishList[i].getOrderedDishID()) {
            orderedDishMaintainList.push_back(-1);
            break;
        }
    }
}

void StaticData::removeMsg(const Msg& msg) {
    for (unsigned int i = 0; i < msgList.size(); i ++) {
        if(msg.getMsgID() == msgList[i].getMsgID()) {
            msgMaintainList.push_back(-1);
            break;
        }
    }
}

void StaticData::removeGuest(const Guest& guest) {
    for (unsigned int i = 0; i < guestList.size(); i ++) {
        if(guest.getPhone() == guestList[i].getPhone()) {
            guestMaintainList.push_back(-1);
            break;
        }
    }
}

void StaticData::removeClerk(const Clerk& clerk) {
    for (unsigned int i = 0; i < clerkList.size(); i ++) {
        if(clerk.getPhone() == clerkList[i].getPhone()) {
            clerkMaintainList.push_back(-1);
            break;
        }
    }
}

void StaticData::removeChef(const Chef& chef) {
    for (unsigned int i = 0; i < chefList.size(); i ++) {
        if(chef.getPhone() == chefList[i].getPhone()) {
            chefMaintainList.push_back(-1);
            break;
        }
    }
}

void StaticData::modifyTable(const Table& table, const Table& newTable) {
    for (unsigned int i = 0; i < tableList.size(); i ++) {
        if(table.getTableID() == tableList[i].getTableID()) {
            tableList[i] = newTable;
            tableMaintainList.push_back(2);
            break;
        }
    }
}

void StaticData::modifyDish(const Dish& dish, const Dish& newDish) {
    for (unsigned int i = 0; i < dishList.size(); i ++) {
        if(dish.getDishID() == dishList[i].getDishID()) {
            dishList[i] = newDish;
            dishMaintainList.push_back(2);
            break;
        }
    }
}

void StaticData::modifyOrderedDish(const OrderedDish& orderedDish, const OrderedDish& newOrderedDish) {
    for (unsigned int i = 0; i < orderedDishList.size(); i ++) {
        if(orderedDish.getOrderedDishID() == orderedDishList[i].getOrderedDishID()) {
            orderedDishList[i] = newOrderedDish;
            orderedDishMaintainList.push_back(2);
            break;
        }
    }
}

void StaticData::modifyMsg(const Msg& msg, const Msg& newMsg) {
    for (unsigned int i = 0; i < msgList.size(); i ++) {
        if(msg.getMsgID() == msgList[i].getMsgID()) {
            msgList[i] = newMsg;
            msgMaintainList.push_back(2);
            break;
        }
    }
}

void StaticData::modifyGuest(const Guest& guest, const Guest& newGuest) {
    for (unsigned int i = 0; i < guestList.size(); i ++) {
        if(guest.getPhone() == guestList[i].getPhone()) {
            guestList[i] = newGuest;
            guestMaintainList.push_back(2);
            break;
        }
    }
}

void StaticData::modifyClerk(const Clerk& clerk, const Clerk& newClerk) {
    for (unsigned int i = 0; i < clerkList.size(); i ++) {
        if(clerk.getPhone() == clerkList[i].getPhone()) {
            clerkList[i] = newClerk;
            clerkMaintainList.push_back(2);
            break;
        }
    }
}

void StaticData::modifyChef(const Chef& chef, const Chef& newChef) {
    for (unsigned int i = 0; i < chefList.size(); i ++) {
        if(chef.getPhone() == chefList[i].getPhone()) {
            chefList[i] = newChef;
            chefMaintainList.push_back(2);
            break;
        }
    }
}

void StaticData::writeTable() {
    for(unsigned int i = 0; i < tableList.size(); i ++) {
        if(tableMaintainList[i] > 0) {
            Table& cur = tableList[i];
            if(db->doesExist("tableList", "id = " + ntos(cur.getTableID()))) {
                db->update("tableList", "seats", ntos(cur.getSeats()), "id = " + ntos(cur.getTableID()));
                db->update("tableList", "freeSeats", ntos(cur.getFreeSeats()), "id = " + ntos(cur.getTableID()));
                db->update("tableList", "clerk",
                                       "\"" + (cur.getClerk() != "" ? cur.getClerk() : (string)"NULL") + "\"",
                                       "id = " + ntos(cur.getTableID()));
            }
            else {
                db->insert("tableList",
                                       ntos(cur.getTableID()) + ", "
                                       + ntos(cur.getSeats()) + ", "
                                       + ntos(cur.getFreeSeats()) + ", \""
                                       + cur.getClerk() + "\"");
            }
        }
        else if (tableMaintainList[i] < 0)
            db->deleteRow("tableList", "id = " + ntos(cur.getTableID()));
    }
}

void StaticData::writeDish() {
    for(unsigned int i = 0; i < dishList.size(); i ++) {
        if(dishMaintainList[i] > 0) {
            Dish& cur = dishList[i];
            if(db->doesExist("dish", "dishID = " + ntos(cur.getDishID()))) {
                db->update("dish", "name", "\"" + cur.getName() + "\"", "dishID = " + ntos(cur.getDishID()));
                db->update("dish", "price", ntos(cur.getPrice()), "dishID = " + ntos(cur.getDishID()));
                db->update("dish", "rate", ntos(cur.getRate()), "dishID = " + ntos(cur.getDishID()));
                db->update("dish", "rateNum", ntos(cur.getRateNum()), "dishID = " + ntos(cur.getDishID()));
                db->update("dish", "time", ntos(cur.getTimeNeeded()), "dishID = " + ntos(cur.getDishID()));
                db->update("dish", "imgdir", "\"" + cur.getImgDir() + "\"", "dishID = " + ntos(cur.getDishID()));
            }
            else {
                db->insert("dish",
                                       "NULL, \"" + cur.getName() + "\", "
                                       + ntos(cur.getPrice()) + ", "
                                       + ntos(cur.getRate()) + ", " + ntos(cur.getRateNum()) + ", "
                                       + "\"" + cur.getImgDir() + "\"");
            }
        }
        else if (dishMaintainList[i] < 0)
            db->deleteRow("dish", "dishID = " + ntos(cur.getDishID()));
    }
}

void StaticData::writeOrderedDish() {
    for(unsigned int i = 0; i < orderedDishList.size(); i ++) {
        if(orderedDishMaintainList[i] > 0) {
            OrderedDish& cur = orderedDishList[i];
            if(db->doesExist("orderedDish", "id = " + ntos(cur.getOrderedDishID()))) {
                db->update("orderedDish",
                                       "orderer", "\"" + cur.getOrderer() + "\"",
                                       "id = " + ntos(cur.getOrderedDishID()));
                db->update("orderedDish",
                                       "tableNum", ntos(cur.getTable()),
                                       "id = " + ntos(cur.getOrderedDishID()));
                db->update("orderedDish",
                                       "status", ntos(cur.getStatus()),
                                       "id = " + ntos(cur.getOrderedDishID()));
                db->update("orderedDish",
                                       "datetime", "\"" + cur.getDatetime() + "\"",
                                       "id = " + ntos(cur.getOrderedDishID()));
            }
            else {
                db->insert("orderedDish",
                                       "NULL, "
                                       + ntos(cur.getDishID()) + ", \""
                                       + cur.getOrderer() + "\", "
                                       + ntos(cur.getTable()) + ", "
                                       + ntos(cur.getStatus()) + ", \""
                                       + cur.getDatetime() + "\"");
            }
        }
        else if (orderedDishMaintainList[i] < 0)
            db->deleteRow("orderedDish", "id = " + ntos(cur.getOrderedDishID()));
    }
}

void StaticData::writeMsg() {
    for(unsigned int i = 0; i < msgList.size(); i ++) {
        if(msgMaintainList[i] > 0) {
            Msg& cur = msgList[i];
            if(db->doesExist("msg", "msgid = " + ntos(cur.getMsgID()))) {
                db->update("msg", "isActive", ntos(cur.getState()), "msgid = " + ntos(cur.getMsgID()));
            }
            else {
                db->insert("msg",
                                       "NULL, \"" + cur.getSender() + "\", \""
                                       + cur.getReceiver() + "\", \""
                                       + cur.getMsg() + "\", \""
                                       + cur.getDatetime() + "\", "
                                       + ntos(cur.getState()));
            }
        }
        else if (msgMaintainList[i] < 0)
            db->deleteRow("msg", "msgid = " + ntos(cur.getMsgID()));
    }
}

void StaticData::writeGuest() {
    for (unsigned int i = 0; i < guestList.size(); i ++) {
        if (guestMaintainList[i] > 0) {
            Guest& cur = guestList[i];
            if(db->doesExist("person", "phone = \"" + cur.getPhone())) {
                db->update("person", "name", "\"" + cur.getName() + "\"",
                           "phone = \"" + cur.getPhone());
                db->update("person", "password", "\"" + cur.getPassword() + "\"",
                           "phone = \"" + cur.getPhone());
//                db->update("person", "password", "\"" + cur.getPassword() + "\"",
//                           "phone = \"" + cur.getPhone());
            }
            else {
                db->insert("person", "\"" + cur.getPhone() + "\", \""
                           + cur.getName() + "\", \""
                           + cur.getPassword() + "\", 1, NULL, NULL, NULL");
            }
        }
        else {
            db->deleteRow("person", "phone = \"" + cur.getPhone());
        }
    }
}

void StaticData::writeClerk() {}

void StaticData::writeChef() {}

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

vector<Msg*> StaticData::getMsgByReceiver(string receiver) {
        vector<Msg*> msgListByReceiver;
        for(unsigned int i = 0; i < msgList.size(); i ++)
                if(msgList[i].getReceiver() == receiver)
                        msgListByReceiver.push_back(&msgList[i]);
        return msgListByReceiver;
}

vector<Msg*> StaticData::getMsgBySender(string sender) {
        vector<Msg*> msgListBySender;
        for(unsigned int i = 0; i < msgList.size(); i ++)
                if(msgList[i].getSender() == sender)
                        msgListBySender.push_back(&msgList[i]);
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

Table& StaticData::getTableByID(int tableID) {
    for(unsigned int i = 0; i < tableList.size(); i ++) {
        if(tableList[i].getTableID() == tableID) {
            return tableList[i];
        }
    }
}

//Person& getPersonByID(int id) {
//        return personList[0];
//}
