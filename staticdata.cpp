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
    for(unsigned int i = 0; i < resultList.size(); i ++) {
        insertTable(Table(atoi(resultList[i][0].c_str()), atoi(resultList[i][1].c_str()), atoi(resultList[i][2].c_str()), resultList[i][3]));
    }
    return true;
}

bool StaticData::queryDish() {
    dishList.clear();
        if (!db->doQuery("dish", "*"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                insertDish(Dish(resultList[i][0],
                           resultList[i][1],
                        atof(resultList[i][2].c_str()),
                        atoi(resultList[i][5].c_str()),
                        atof(resultList[i][3].c_str()),
                        atoi(resultList[i][4].c_str()),
                        resultList[i][6]));
        return true;
}

bool StaticData::queryOrderedDish() {
    orderedDishList.clear();
        if (!db->doQuery("orderedDish", "*"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++) {
            OrderedDish tmp(getDishByID(resultList[i][1]),
                    resultList[i][0],
                    resultList[i][2],
                    atoi(resultList[i][3].c_str()),
                    atoi(resultList[i][4].c_str()));
            tmp.setDatetime(resultList[i][5]);
            tmp.setChef(resultList[i][6]);
            insertOrderedDish(tmp);
        }
        return true;
}

void StaticData::clearMsgList() {msgList.clear();}

bool StaticData::queryMsg(string person) {
        if (!db->doQuery("msg", "*", "sender = \"" + person + "\" or receiver = \"" + person + "\""))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for (unsigned int i = 0; i < resultList.size(); i ++) {
            string msgID = resultList[i][0].c_str();
            bool msgExists = false;
            for (unsigned int j = 0; j < msgList.size(); j ++)
                if(msgID == msgList[j].getMsgID()) {
                    msgExists = true;
                    break;
                }
            if(!msgExists)
                insertMsg(Msg(resultList[i][0], resultList[i][1], resultList[i][2], resultList[i][3], resultList[i][4], atoi(resultList[i][5].c_str())));
        }
        return true;
}

bool StaticData::queryClerk() {
    clerkList.clear();
        if(!db->doQuery("person", "*", "type = 3"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                insertClerk(Clerk(resultList[i][0], resultList[i][1], resultList[i][2], atof(resultList[i][3].c_str()), atoi(resultList[i][4].c_str())));
        return true;
}

bool StaticData::queryChef() {
    chefList.clear();
        if(!db->doQuery("person", "*", "type = 2"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                insertChef(Chef(resultList[i][0], resultList[i][1], resultList[i][2]));
        return true;
}

bool StaticData::queryGuest() {
    guestList.clear();
        if(!db->doQuery("person", "*", "type = 1"))
                return false;
        vector<vector<string> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                insertGuest(Guest(resultList[i][0], resultList[i][1], resultList[i][2]));
        return true;
}

bool StaticData::queryOrder() {
    //queryOrderedDish();
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
            insertOrder(newOrder);
        }
    }
}

void StaticData::insertTable(const Table table, int type) {
    tableList.push_back(table);
    tableMaintainList.push_back(type);
}

void StaticData::insertDish(const Dish dish, int type) {
    dishList.push_back(dish);
    dishMaintainList.push_back(type);
}

void StaticData::insertOrderedDish(const OrderedDish orderedDish, int type) {
    orderedDishList.push_back(orderedDish);
    orderedDishMaintainList.push_back(type);
}

void StaticData::insertMsg(const Msg msg, int type) {
    msgList.push_back(msg);
    msgMaintainList.push_back(type);
}

void StaticData::insertGuest(const Guest guest, int type) {
    guestList.push_back(guest);
    guestMaintainList.push_back(type);
}

void StaticData::insertClerk(const Clerk clerk, int type) {
    clerkList.push_back(clerk);
    clerkMaintainList.push_back(type);
}

void StaticData::insertChef(const Chef chef, int type) {
    chefList.push_back(chef);
    chefMaintainList.push_back(type);
}

void StaticData::insertOrder(const Order order) {
    orderList.push_back(order);
}

void StaticData::removeTable(int tableID) {
    for (unsigned int i = 0; i < tableList.size(); i ++) {
        if(tableID == tableList[i].getTableID()) {
            tableMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::removeDish(const string& dishID) {
    for (unsigned int i = 0; i < dishList.size(); i ++) {
        if(dishID == dishList[i].getDishID()) {
            dishMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::removeOrderedDish(const string& orderedDishID) {
    for (unsigned int i = 0; i < orderedDishList.size(); i ++) {
        if(orderedDishID == orderedDishList[i].getOrderedDishID()) {
            orderedDishMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::removeMsg(const string& msgID) {
    for (unsigned int i = 0; i < msgList.size(); i ++) {
        if(msgID == msgList[i].getMsgID()) {
            msgMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::removeGuest(const string& phone) {
    for (unsigned int i = 0; i < guestList.size(); i ++) {
        if(phone == guestList[i].getPhone()) {
            guestMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::removeClerk(const string& phone) {
    for (unsigned int i = 0; i < clerkList.size(); i ++) {
        if(phone == clerkList[i].getPhone()) {
            clerkMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::removeChef(const string& phone) {
    for (unsigned int i = 0; i < chefList.size(); i ++) {
        if(phone == chefList[i].getPhone()) {
            chefMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::modifyTable(int tableID, const Table& newTable) {
    for (unsigned int i = 0; i < tableList.size(); i ++) {
        if(tableID == tableList[i].getTableID()) {
            tableList[i] = newTable;
            tableMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::modifyDish(const string& dishID, const Dish& newDish) {
    for (unsigned int i = 0; i < dishList.size(); i ++) {
        if(dishID == dishList[i].getDishID()) {
            dishList[i] = newDish;
            dishMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::modifyOrderedDish(const string& orderedDishID, const OrderedDish& newOrderedDish) {
    for (unsigned int i = 0; i < orderedDishList.size(); i ++) {
        if(orderedDishID == orderedDishList[i].getOrderedDishID()) {
            orderedDishList[i] = newOrderedDish;
            orderedDishMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::modifyMsg(const string& msgID, const Msg& newMsg) {
    for (unsigned int i = 0; i < msgList.size(); i ++) {
        if(msgID == msgList[i].getMsgID()) {
            msgList[i] = newMsg;
            msgMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::modifyGuest(const string& phone, const Guest& newGuest) {
    for (unsigned int i = 0; i < guestList.size(); i ++) {
        if(phone == guestList[i].getPhone()) {
            guestList[i] = newGuest;
            guestMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::modifyClerk(const string& phone, const Clerk& newClerk) {
    for (unsigned int i = 0; i < clerkList.size(); i ++) {
        if(phone == clerkList[i].getPhone()) {
            clerkList[i] = newClerk;
            clerkMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::modifyChef(const string& phone, const Chef& newChef) {
    for (unsigned int i = 0; i < chefList.size(); i ++) {
        if(phone == chefList[i].getPhone()) {
            chefList[i] = newChef;
            chefMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::writeTable() {
    for(unsigned int i = 0; i < tableList.size(); i ++) {
        Table& cur = tableList[i];
        if(tableMaintainList[i] > 0) {
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
        Dish& cur = dishList[i];
        if(dishMaintainList[i] > 0) {
            if(db->doesExist("dish", "dishID = \"" + cur.getDishID() + "\"")) {
                db->update("dish", "name", "\"" + cur.getName() + "\"", "dishID = \"" + cur.getDishID() + "\"");
                db->update("dish", "price", ntos(cur.getPrice()), "dishID = \"" + cur.getDishID() + "\"");
                db->update("dish", "rate", ntos(cur.getRate()), "dishID = \"" + cur.getDishID() + "\"");
                db->update("dish", "rateNum", ntos(cur.getRateNum()), "dishID = \"" + cur.getDishID() + "\"");
                db->update("dish", "time", ntos(cur.getTimeNeeded()), "dishID = \"" + cur.getDishID() + "\"");
                db->update("dish", "imgdir", "\"" + cur.getImgDir() + "\"", "dishID = \"" + cur.getDishID() + "\"");
            }
            else {
                db->insert("dish",
                           "\"" + cur.getDishID() + "\", \"" + cur.getName() + "\", "
                           + ntos(cur.getPrice()) + ", "
                           + ntos(cur.getRate()) + ", " + ntos(cur.getRateNum()) + ", "
                           + ntos(cur.getTimeNeeded()) + ", \""
                           + cur.getImgDir() + "\"");
            }
        }
        else if (dishMaintainList[i] < 0)
            db->deleteRow("dish", "dishID = \"" + cur.getDishID() + "\"");
    }
}

void StaticData::writeOrderedDish() {
    for(unsigned int i = 0; i < orderedDishList.size(); i ++) {
        OrderedDish& cur = orderedDishList[i];
        if(orderedDishMaintainList[i] > 0) {
            if(db->doesExist("orderedDish", "id = \"" + cur.getOrderedDishID() + "\"")) {
                db->update("orderedDish",
                                       "orderer", "\"" + cur.getOrderer() + "\"",
                                       "id = \"" + cur.getOrderedDishID() + "\"");
                db->update("orderedDish",
                                       "tableNum", ntos(cur.getTable()),
                                       "id = \"" + cur.getOrderedDishID() + "\"");
                db->update("orderedDish",
                                       "status", ntos(cur.getStatus()),
                                       "id = \"" + cur.getOrderedDishID() + "\"");
                db->update("orderedDish",
                                       "datetime", "\"" + cur.getDatetime() + "\"",
                                       "id = \"" + cur.getOrderedDishID() + "\"");
                db->update("orderedDish",
                                       "chef", "\"" + cur.getChef() + "\"",
                                       "id = \"" + cur.getOrderedDishID() + "\"");
            }
            else {
                db->insert("orderedDish",
                           "\"" + cur.getOrderedDishID() + "\", \""
                           + cur.getDishID() + "\", \""
                           + cur.getOrderer() + "\", "
                           + ntos(cur.getTable()) + ", "
                           + ntos(cur.getStatus()) + ", \""
                           + cur.getDatetime() + "\", \""
                           + cur.getChef() + "\"");
            }
        }
        else if (orderedDishMaintainList[i] < 0)
            db->deleteRow("orderedDish", "id = \"" + cur.getOrderedDishID() + "\"");
    }
}

void StaticData::writeMsg() {
    for(unsigned int i = 0; i < msgList.size(); i ++) {
        Msg& cur = msgList[i];
        if(msgMaintainList[i] > 0) {
            if(db->doesExist("msg", "msgid = \"" + cur.getMsgID() + "\"")) {
                db->update("msg", "isActive", ntos(cur.getState()), "msgid = \"" + cur.getMsgID() + "\"");
            }
            else {
                db->insert("msg",
                           "\"" + cur.getMsgID() + "\", \""
                           + cur.getSender() + "\", \""
                           + cur.getReceiver() + "\", \""
                           + cur.getMsg() + "\", \""
                           + cur.getDatetime() + "\", "
                           + ntos(cur.getState()));
            }
        }
        else if (msgMaintainList[i] < 0)
            db->deleteRow("msg", "msgid = \"" + cur.getMsgID() + "\"");
    }
}

void StaticData::writeGuest() {
    for (unsigned int i = 0; i < guestList.size(); i ++) {
        Guest& cur = guestList[i];
        if (guestMaintainList[i] > 0) {
            if(db->doesExist("person", "phone = \"" + cur.getPhone() + "\"")) {
                db->update("person", "name", "\"" + cur.getName() + "\"",
                           "phone = \"" + cur.getPhone() + "\"");
                db->update("person", "password", "\"" + cur.getPassword() + "\"",
                           "phone = \"" + cur.getPhone() + "\"");
                db->update("peson", "table", ntos(cur.getTable()),
                           "phone = \"" + cur.getPhone() + "\"");
//                db->update("person", "password", "\"" + cur.getPassword() + "\"",
//                           "phone = \"" + cur.getPhone() + "\"");
            }
            else {
                db->insert("person", "\"" + cur.getPhone() + "\", \""
                           + cur.getName() + "\", \""
                           + cur.getPassword() + "\", 1, NULL, NULL, "
                           + (cur.getTable() > 0 ? ntos(cur.getTable()) : "NULL"));
            }
        }
        else if (guestMaintainList[i] < 0) {
            db->deleteRow("person", "phone = \"" + cur.getPhone() + "\"");
        }
    }
}

void StaticData::writeClerk() {
    for (unsigned int i = 0; i < clerkList.size(); i ++) {
        Clerk& cur = clerkList[i];
        if (clerkMaintainList[i] > 0) {
            if(db->doesExist("person", "phone = \"" + cur.getPhone() + "\"")) {
                db->update("person", "name", "\"" + cur.getName() + "\"",
                           "phone = \"" + cur.getPhone() + "\"");
                db->update("person", "password", "\"" + cur.getPassword() + "\"",
                           "phone = \"" + cur.getPhone() + "\"");
                db->update("peson", "rate", ntos(cur.getRate()),
                           "phone = \"" + cur.getPhone() + "\"");
                db->update("peson", "rateNum", ntos(cur.getRateNum()),
                           "phone = \"" + cur.getPhone() + "\"");
//                db->update("peson", "table", ntos(cur.getTable()),
//                           "phone = \"" + cur.getPhone() + "\"");
//                db->update("person", "password", "\"" + cur.getPassword() + "\"",
//                           "phone = \"" + cur.getPhone() + "\"");
            }
            else {
                db->insert("person", "\"" + cur.getPhone() + "\", \""
                           + cur.getName() + "\", \""
                           + cur.getPassword() + "\", 3, "
                           + ntos(cur.getRate()) + ", "
                           + ntos(cur.getRateNum()) + ", NULL");
            }
        }
        else if (clerkMaintainList[i] < 0) {
            db->deleteRow("person", "phone = \"" + cur.getPhone() + "\"");
        }
    }
}

void StaticData::writeChef() {
    for (unsigned int i = 0; i < chefList.size(); i ++) {
        Chef& cur = chefList[i];
        if (chefMaintainList[i] > 0) {
            if(db->doesExist("person", "phone = \"" + cur.getPhone() + "\"")) {
                db->update("person", "name", "\"" + cur.getName() + "\"",
                           "phone = \"" + cur.getPhone() + "\"");
                db->update("person", "password", "\"" + cur.getPassword() + "\"",
                           "phone = \"" + cur.getPhone() + "\"");
//                db->update("peson", "table", ntos(cur.getTable()),
//                           "phone = \"" + cur.getPhone() + "\"");
//                db->update("person", "password", "\"" + cur.getPassword() + "\"",
//                           "phone = \"" + cur.getPhone() + "\"");
            }
            else {
                db->insert("person", "\"" + cur.getPhone() + "\", \""
                           + cur.getName() + "\", \""
                           + cur.getPassword() + "\", 2, NULL, NULL, NULL");
            }
        }
        else if (chefMaintainList[i] < 0) {
            db->deleteRow("person", "phone = \"" + cur.getPhone() + "\"");
        }
    }
}

Dish& StaticData::getDishByID(const string& dishID) {
        for(unsigned int i = 0; i < dishList.size(); i ++)
                if(dishList[i].getDishID() == dishID)
                        return dishList[i];
        return dishList[0];
}

OrderedDish& StaticData::getOrderedDishByID(const string& orderedDishID) {
        for(unsigned int i = 0; i < orderedDishList.size(); i ++)
                if(orderedDishList[i].getOrderedDishID() == orderedDishID)
                        return orderedDishList[i];
        return orderedDishList[0];
}

vector<Msg*> StaticData::getMsgByReceiver(const string& receiver) {
        vector<Msg*> msgListByReceiver;
        for(unsigned int i = 0; i < msgList.size(); i ++)
                if(msgList[i].getReceiver() == receiver)
                        msgListByReceiver.push_back(&msgList[i]);
        return msgListByReceiver;
}

vector<Msg*> StaticData::getMsgBySender(const string& sender) {
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

string StaticData::getPersonNameByPhone(const string& phone) {
    if(!db->doQuery("person", "name", "phone = \"" + phone + "\""))
            return false;
    return db->getResultList()[0][0];
}

void StaticData::updateEverythingAboutUser(Person *person, const string& newPhone) {
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
