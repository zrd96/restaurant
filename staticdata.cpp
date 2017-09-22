#include <vector>
#include <QString>

#include "staticdata.h"
#include "datamanager.h"
#include "mysqlmanager.h"
#include "dish.h"
#include "msg.h"
#include "guest.h"
#include "clerk.h"
#include "chef.h"
#include "rate.h"
#include "emptyresult.h"

vector<Dish> StaticData::dishList;
vector<OrderedDish> StaticData::orderedDishList;
vector<Order> StaticData::orderList;
vector<Msg> StaticData::msgList;
vector<Clerk> StaticData::clerkList;
vector<Chef> StaticData::chefList;
vector<Guest> StaticData::guestList;
vector<Manager> StaticData::managerList;
vector<Table> StaticData::tableList;
vector<Rate> StaticData::rateList;

vector<int> StaticData::dishMaintainList;
vector<int> StaticData::orderedDishMaintainList;
vector<int> StaticData::msgMaintainList;
vector<int> StaticData::guestMaintainList;
vector<int> StaticData::chefMaintainList;
vector<int> StaticData::clerkMaintainList;
vector<int> StaticData::managerMaintainList;
vector<int> StaticData::tableMaintainList;
vector<int> StaticData::orderMaintainList;
vector<int> StaticData::rateMaintainList;

DataManager* StaticData::db = NULL;

bool StaticData::queryTable() {
    tableList.clear();
    tableMaintainList.clear();
    if(!db->doQuery("tableList", "*"))
        return false;
    vector<vector<QString> > resultList = db->getResultList();
    for(unsigned int i = 0; i < resultList.size(); i ++) {
        insertTable(Table(resultList[i][0].toInt(), resultList[i][1].toInt(), resultList[i][2].toInt(), resultList[i][3]));
    }
    return true;
}

bool StaticData::queryDish() {
    dishList.clear();
    dishMaintainList.clear();
        if (!db->doQuery("dish", "*"))
                return false;
        vector<vector<QString> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                insertDish(Dish(resultList[i][0],
                           resultList[i][1],
                        resultList[i][2],
                        resultList[i][3].toDouble(),
                        resultList[i][6].toInt(),
                        resultList[i][4].toDouble(),
                        resultList[i][5].toInt(),
                        resultList[i][7]));
        return true;
}

bool StaticData::queryOrderedDish() {
    orderedDishList.clear();
    orderedDishMaintainList.clear();
        if (!db->doQuery("orderedDish", "*"))
                return false;
        vector<vector<QString> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++) {
            try {
                OrderedDish tmp(getDishByID(resultList[i][1]),
                        resultList[i][0],
                        resultList[i][2],
                        resultList[i][3].toInt(),
                        resultList[i][5],
                        resultList[i][7], //request
                        resultList[i][4].toInt(),
                        resultList[i][6],
                        resultList[i][8].toDouble());
                insertOrderedDish(tmp);
            } catch (EmptyResult) {}
        }
        return true;
}

void StaticData::clearMsgList() {
    msgList.clear();
    msgMaintainList.clear();
}

bool StaticData::queryMsg(const QString &person) {
        if (!db->doQuery("msg", "*", "sender = \"" + person + "\" or receiver = \"" + person + "\""))
                return false;
        vector<vector<QString> > resultList = db->getResultList();
        for (unsigned int i = 0; i < resultList.size(); i ++) {
            QString msgID = resultList[i][0];
            bool msgExists = false;
            for (unsigned int j = 0; j < msgList.size(); j ++)
                if(msgID == msgList[j].getMsgID()) {
                    msgExists = true;
                    break;
                }
            if(!msgExists)
                insertMsg(Msg(resultList[i][0], resultList[i][1], resultList[i][2], resultList[i][3], resultList[i][4], resultList[i][5].toInt()));
        }
        return true;
}

bool StaticData::queryClerk() {
    clerkList.clear();
    clerkMaintainList.clear();
        if(!db->doQuery("person", "*", "type = 3"))
                return false;
        vector<vector<QString> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                insertClerk(Clerk(resultList[i][0], resultList[i][1], resultList[i][2], resultList[i][4].toDouble(), resultList[i][5].toInt(), resultList[i][6].toInt(), resultList[i][7].toInt(), resultList[i][8].toDouble()));
        return true;
}

bool StaticData::queryChef() {
    chefList.clear();
    chefMaintainList.clear();
        if(!db->doQuery("person", "*", "type = 2"))
                return false;
        vector<vector<QString> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                insertChef(Chef(resultList[i][0], resultList[i][1], resultList[i][2], resultList[i][7].toInt(), resultList[i][8].toDouble(), resultList[i][4].toInt(), resultList[i][5].toDouble()));
        return true;
}

bool StaticData::queryGuest() {
    guestList.clear();
    guestMaintainList.clear();
        if(!db->doQuery("person", "*", "type = 1"))
                return false;
        vector<vector<QString> > resultList = db->getResultList();
        for(unsigned int i = 0; i < resultList.size(); i ++)
                insertGuest(Guest(resultList[i][0], resultList[i][1], resultList[i][2]));
        return true;
}

bool StaticData::queryManager() {
    managerList.clear();
    if (!db->doQuery("person", "*", "type = 4"))
        return false;
    vector<vector<QString> > resultList = db->getResultList();
    for(unsigned int i = 0; i < resultList.size(); i ++)
        insertManager(Manager(resultList[i][0], resultList[i][1], resultList[i][2]));
    return true;
}

bool StaticData::queryOrder() {
    //queryOrderedDish();
    orderList.clear();
    orderMaintainList.clear();
    if (!db->doQuery("orderList", "*"))
        return false;
    vector<vector<QString> > resultList = db->getResultList();
    for (unsigned int i = 0; i < resultList.size(); i ++)
        insertOrder(Order(resultList[i][0], resultList[i][1], resultList[i][2], resultList[i][3], resultList[i][4].toInt(), resultList[i][5].toDouble()));
    for(unsigned int i = 0; i < orderedDishList.size(); i ++) {
        bool found = 0;
        for(unsigned j = 0; j < orderList.size(); j ++)
            if("O" + orderedDishList[i].getDatetime() + orderedDishList[i].getOrderer() == orderList[j].getOrderID()) {
                found = 1;
                orderList[j].insertDish(orderedDishList[i]);
                break;
            }
        if(!found) {
            throw EmptyResult("Found orderedDish that doesn't belong to any order");
        }
    }
}

bool StaticData::queryRate() {
    rateList.clear();
    rateMaintainList.clear();
    if (!db->doQuery("rate", "*"))
        return false;
    vector<vector<QString> > resultList = db->getResultList();
    for(unsigned int i = 0; i < resultList.size(); i ++)
        insertRate(Rate((resultList[i][0]),
                   resultList[i][1].toDouble(),
                (resultList[i][2]),
                (resultList[i][3]),
                (resultList[i][4]),
                (resultList[i][5]),
                (resultList[i][6])));
    return true;
}

void StaticData::insertTable(const Table &table, int type) {
    tableList.push_back(table);
    tableMaintainList.push_back(type);
}

void StaticData::insertDish(const Dish &dish, int type) {
    dishList.push_back(dish);
    dishMaintainList.push_back(type);
}

void StaticData::insertOrderedDish(const OrderedDish &orderedDish, int type) {
    orderedDishList.push_back(orderedDish);
    orderedDishMaintainList.push_back(type);
}

void StaticData::insertMsg(const Msg &msg, int type) {
    msgList.push_back(msg);
    msgMaintainList.push_back(type);
}

void StaticData::insertGuest(const Guest &guest, int type) {
    guestList.push_back(guest);
    guestMaintainList.push_back(type);
}

void StaticData::insertClerk(const Clerk &clerk, int type) {
    clerkList.push_back(clerk);
    clerkMaintainList.push_back(type);
}

void StaticData::insertManager(const Manager &manager, int type) {
    managerList.push_back(manager);
    managerMaintainList.push_back(type);
}

void StaticData::insertChef(const Chef &chef, int type) {
    chefList.push_back(chef);
    chefMaintainList.push_back(type);
}

void StaticData::insertOrder(const Order &order, int type) {
    orderList.push_back(order);
    orderMaintainList.push_back(type);
}

void StaticData::insertRate(const Rate &rate, int type) {
    rateList.push_back(rate);
    rateMaintainList.push_back(type);
}

void StaticData::removeTable(int tableID) {
    for (unsigned int i = 0; i < tableList.size(); i ++) {
        if(tableID == tableList[i].getTableID()) {
            tableMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::removeDish(const QString& dishID) {
    for (unsigned int i = 0; i < dishList.size(); i ++) {
        if(dishID == dishList[i].getDishID()) {
            dishMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::removeOrderedDish(const QString& orderedDishID) {
    for (unsigned int i = 0; i < orderedDishList.size(); i ++) {
        if(orderedDishID == orderedDishList[i].getOrderedDishID()) {
            orderedDishMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::removeMsg(const QString& msgID) {
    for (unsigned int i = 0; i < msgList.size(); i ++) {
        if(msgID == msgList[i].getMsgID()) {
            msgMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::removeGuest(const QString& phone) {
    for (unsigned int i = 0; i < guestList.size(); i ++) {
        if(phone == guestList[i].getPhone()) {
            guestMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::removeClerk(const QString& phone) {
    for (unsigned int i = 0; i < clerkList.size(); i ++) {
        if(phone == clerkList[i].getPhone()) {
            clerkMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::removeManager(const QString& phone) {
    for (unsigned int i = 0; i < managerList.size(); i ++) {
        if(phone == managerList[i].getPhone()) {
            managerMaintainList[i] = -1;
            break;
        }
    }
}

void StaticData::removeChef(const QString& phone) {
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

void StaticData::modifyDish(const QString& dishID, const Dish& newDish) {
    for (unsigned int i = 0; i < dishList.size(); i ++) {
        if(dishID == dishList[i].getDishID()) {
            dishList[i] = newDish;
            dishMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::modifyOrderedDish(const QString& orderedDishID, const OrderedDish& newOrderedDish) {
    for (unsigned int i = 0; i < orderedDishList.size(); i ++) {
        if(orderedDishID == orderedDishList[i].getOrderedDishID()) {
            orderedDishList[i] = newOrderedDish;
            orderedDishMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::modifyMsg(const QString& msgID, const Msg& newMsg) {
    for (unsigned int i = 0; i < msgList.size(); i ++) {
        if(msgID == msgList[i].getMsgID()) {
            msgList[i] = newMsg;
            msgMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::modifyGuest(const QString& phone, const Guest& newGuest) {
    for (unsigned int i = 0; i < guestList.size(); i ++) {
        if(phone == guestList[i].getPhone()) {
            guestList[i] = newGuest;
            guestMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::modifyClerk(const QString& phone, const Clerk& newClerk) {
    for (unsigned int i = 0; i < clerkList.size(); i ++) {
        if(phone == clerkList[i].getPhone()) {
            clerkList[i] = newClerk;
            clerkMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::modifyManager(const QString& phone, const Manager& newManager) {
    for (unsigned int i = 0; i < managerList.size(); i ++) {
        if(phone == managerList[i].getPhone()) {
            managerList[i] = newManager;
            managerMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::modifyChef(const QString& phone, const Chef& newChef) {
    for (unsigned int i = 0; i < chefList.size(); i ++) {
        if(phone == chefList[i].getPhone()) {
            chefList[i] = newChef;
            chefMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::modifyOrder(const QString &orderID, const Order &newOrder) {
    for (unsigned int i = 0; i < orderList.size(); i ++) {
        if (orderID == orderList[i].getOrderID()) {
            orderList[i] = newOrder;
            orderMaintainList[i] = 2;
            break;
        }
    }
}

void StaticData::writeTable() {
    for(unsigned int i = 0; i < tableList.size(); i ++) {
        Table& cur = tableList[i];
        if(tableMaintainList[i] > 0) {
            if(db->doesExist("tableList", QString("id = %1").arg(cur.getTableID()))) {
                db->update("tableList", "seats", QString().setNum(cur.getSeats()), QString("id = %1").arg(cur.getTableID()));
                db->update("tableList", "freeSeats", QString().setNum(cur.getFreeSeats()), QString("id = %1").arg(cur.getTableID()));
                db->update("tableList", "clerk",
                                       "\"" + (cur.getClerk() != "" ? cur.getClerk() : (QString)"NULL") + "\"",
                                       QString("id = %1").arg(cur.getTableID()));
            }
            else {
                db->insert("tableList", QString("%1, %2, %3, \"%4\"").arg(cur.getTableID()).arg(cur.getSeats()).arg(cur.getFreeSeats()).arg(cur.getClerk()));
            }
        }
        else if (tableMaintainList[i] < 0)
            db->deleteRow("tableList", QString("id = %1").arg(cur.getTableID()));
    }
}

void StaticData::writeDish() {
    for(unsigned int i = 0; i < dishList.size(); i ++) {
        Dish& cur = dishList[i];
        if(dishMaintainList[i] > 0) {
            if(db->doesExist("dish", QString("dishID = \"%1\"").arg(cur.getDishID()))) {
                db->update("dish", "name", "\"" + cur.getName() + "\"", QString("dishID = \"%1\"").arg(cur.getDishID()));
                db->update("dish", "price", QString().setNum(cur.getPrice()), QString("dishID = \"%1\"").arg(cur.getDishID()));
                db->update("dish", "rate", QString().setNum(cur.getRate()), QString("dishID = \"%1\"").arg(cur.getDishID()));
                db->update("dish", "rateNum", QString().setNum(cur.getRateNum()), QString("dishID = \"%1\"").arg(cur.getDishID()));
                db->update("dish", "time", QString().setNum(cur.getTimeNeeded()), QString("dishID = \"%1\"").arg(cur.getDishID()));
                db->update("dish", "imgdir", "\"" + cur.getImgDir() + "\"", QString("dishID = \"%1\"").arg(cur.getDishID()));
            }
            else {
                db->insert("dish", QString("\"%1\", \"%2\", \"%8\", %3, %4, %5, %6, \"%7\"")
                           .arg(cur.getDishID())
                           .arg(cur.getName())
                           .arg(cur.getPrice())
                           .arg(cur.getRate())
                           .arg(cur.getRateNum())
                           .arg(cur.getTimeNeeded())
                           .arg(cur.getImgDir())
                           .arg(cur.getIntro()));
            }
        }
        else if (dishMaintainList[i] < 0)
            db->deleteRow("dish", QString("dishID = \"%1\"").arg(cur.getDishID()));
    }
}

void StaticData::writeOrderedDish() {
    for(unsigned int i = 0; i < orderedDishList.size(); i ++) {
        OrderedDish& cur = orderedDishList[i];
        if(orderedDishMaintainList[i] > 0) {
            if(db->doesExist("orderedDish", QString("id = \"%1\"").arg(cur.getOrderedDishID()))) {
                db->update("orderedDish",
                                       "orderer", "\"" + cur.getOrderer() + "\"",
                                       QString("id = \"%1\"").arg(cur.getOrderedDishID()));
                db->update("orderedDish",
                                       "tableNum", QString().setNum(cur.getTable()),
                                       QString("id = \"%1\"").arg(cur.getOrderedDishID()));
                db->update("orderedDish",
                                       "status", QString().setNum(cur.getStatus()),
                                       QString("id = \"%1\"").arg(cur.getOrderedDishID()));
                db->update("orderedDish",
                                       "datetime", "\"" + cur.getDatetime() + "\"",
                                       QString("id = \"%1\"").arg(cur.getOrderedDishID()));
                db->update("orderedDish",
                                       "chef", "\"" + cur.getChef() + "\"",
                                       QString("id = \"%1\"").arg(cur.getOrderedDishID()));
                db->update("orderedDish",
                                       "request", "\"" + cur.getRequest() + "\"",
                                       QString("id = \"%1\"").arg(cur.getOrderedDishID()));
                db->update("orderedDish",
                                       "rate", QString().setNum(cur.getUserRate()),
                                       QString("id = \"%1\"").arg(cur.getOrderedDishID()));
            }
            else {
                db->insert("orderedDish", QString("\"%1\", \"%2\", \"%3\", %4, %5, \"%6\", \"%7\", \"%8\", %9")
                           .arg(cur.getOrderedDishID())
                           .arg(cur.getDishID())
                           .arg(cur.getOrderer())
                           .arg(cur.getTable())
                           .arg(cur.getStatus())
                           .arg(cur.getDatetime())
                           .arg(cur.getChef())
                           .arg(cur.getRequest())
                           .arg(cur.getUserRate()));
            }
        }
        else if (orderedDishMaintainList[i] < 0)
            db->deleteRow("orderedDish", QString("id = \"%1\"").arg(cur.getOrderedDishID()));
    }
}

void StaticData::writeMsg() {
    for(unsigned int i = 0; i < msgList.size(); i ++) {
        Msg& cur = msgList[i];
        if(msgMaintainList[i] > 0) {
            if(db->doesExist("msg", QString("msgid = \"%1\"").arg(cur.getMsgID()))) {
                db->update("msg", "isActive", QString().setNum(cur.getState()), QString("msgid = \"%1\"").arg(cur.getMsgID()));
            }
            else {
                db->insert("msg", QString("\"%1\", \"%2\", \"%3\", \"%4\", \"%5\", %6")
                           .arg(cur.getMsgID())
                           .arg(cur.getSender())
                           .arg(cur.getReceiver())
                           .arg(cur.getMsg())
                           .arg(cur.getDatetime())
                           .arg(cur.getState()));
            }
        }
        else if (msgMaintainList[i] < 0)
            db->deleteRow("msg", QString("msgid = \"%1\"").arg(cur.getMsgID()));
    }
}

void StaticData::writeGuest() {
    for (unsigned int i = 0; i < guestList.size(); i ++) {
        Guest& cur = guestList[i];
        if (guestMaintainList[i] > 0) {
            if(db->doesExist("person", QString("phone = \"%1\"").arg(cur.getPhone()))) {
                db->update("person", "name", "\"" + cur.getName() + "\"", QString("phone = \"%1\"").arg(cur.getPhone()));
                db->update("person", "password", "\"" + cur.getPassword() + "\"", QString("phone = \"%1\"").arg(cur.getPhone()));
                db->update("person", "tableID", QString().setNum(cur.getTable()), QString("phone = \"%1\"").arg(cur.getPhone()));
            }
            else {
                db->insert("person", "\"" + cur.getPhone() + "\", \""
                           + cur.getName() + "\", \""
                           + cur.getPassword() + "\", 1, NULL, NULL, "
                           + (cur.getTable() > 0 ? QString().setNum(cur.getTable()) : "NULL")
                           + ", 0, 0");
            }
        }
        else if (guestMaintainList[i] < 0) {
            db->deleteRow("person", QString("phone = \"%1\"").arg(cur.getPhone()));
        }
    }
}

void StaticData::writeClerk() {
    for (unsigned int i = 0; i < clerkList.size(); i ++) {
        Clerk& cur = clerkList[i];
        if (clerkMaintainList[i] > 0) {
            if(db->doesExist("person", QString("phone = \"%1\"").arg(cur.getPhone())))
                db->deleteRow("person", QString("phone = \"%1\"").arg(cur.getPhone()));
            db->insert("person", QString("\"%1\", \"%2\", \"%3\", 3, %4, %5, %6, %7, %8")
                       .arg(cur.getPhone())
                       .arg(cur.getName())
                       .arg(cur.getPassword())
                       .arg(cur.getRate())
                       .arg(cur.getRateNum())
                       .arg(cur.getServeTableNum())
                       .arg(cur.getServeDishNum())
                       .arg(cur.getAverageServeTime()));
        }
        else if (clerkMaintainList[i] < 0) {
            db->deleteRow("person", QString("phone = \"%1\"").arg(cur.getPhone()));
        }
    }
}

void StaticData::writeManager() {
    for (unsigned int i = 0; i < managerList.size(); i ++) {
        Manager& cur = managerList[i];
        if (managerMaintainList[i] > 0) {
            if(db->doesExist("person", QString("phone = \"%1\"").arg(cur.getPhone())))
                db->deleteRow("person", QString("phone = \"%1\"").arg(cur.getPhone()));
            db->insert("person", QString("\"%1\", \"%2\", \"%3\", 4, 0, 0, 0, 0, 0")
                       .arg(cur.getPhone())
                       .arg(cur.getName())
                       .arg(cur.getPassword()));
        }
        else if (managerMaintainList[i] < 0) {
            db->deleteRow("person", QString("phone = \"%1\"").arg(cur.getPhone()));
        }
    }
}

void StaticData::writeChef() {
    for (unsigned int i = 0; i < chefList.size(); i ++) {
        Chef& cur = chefList[i];
        if (chefMaintainList[i] > 0) {
            if(db->doesExist("person", QString("phone = \"%1\"").arg(cur.getPhone())))
                db->deleteRow("person", QString("phone = \"%1\"").arg(cur.getPhone()));
            db->insert("person",QString("\"%1\", \"%2\", \"%3\", 2, %4, %5, NULL, %6, %7")
                       .arg(cur.getPhone())
                       .arg(cur.getName())
                       .arg(cur.getPassword())
                       .arg(cur.getAverageRate())
                       .arg(cur.getRateNum())
                       .arg(cur.getDishNum())
                       .arg(cur.getAverageTimeDifference()));
        }
        else if (chefMaintainList[i] < 0) {
            db->deleteRow("person", QString("phone = \"%1\"").arg(cur.getPhone()));
        }
    }
}

void StaticData::writeRate() {
    for (unsigned int i = 0; i < rateList.size(); i ++) {
        Rate& cur = rateList[i];
        if (rateMaintainList[i] > 0) {
                db->insert("rate", QString("\"%1\", %2, \"%3\", \"%4\", \"%5\", \"%6\", \"%7\"")
                           .arg(cur.getRateID())
                           .arg(cur.getRate())
                           .arg(cur.getSubject())
                           .arg(cur.getObject())
                           .arg(cur.getDatetime())
                           .arg(cur.getTitle())
                           .arg(cur.getComments()));
        }
    }
}

void StaticData::writeOrder() {
    for (unsigned int i = 0; i < orderList.size(); i ++) {
        Order &cur = orderList[i];
        if (orderMaintainList[i] > 0) {
            if (db->doesExist("orderList", QString("orderID = \"%1\"").arg(cur.getOrderID())))
                db->deleteRow("orderList", QString("orderID = \"%1\"").arg(cur.getOrderID()));
            db->insert("orderList", QString("\"%1\", \"%2\", \"%3\", \"%4\", %5, %6")
                       .arg(cur.getOrderID())
                       .arg(cur.getOrderer())
                       .arg(cur.getDatetime())
                       .arg(cur.getClerk())
                       .arg(cur.getTable())
                       .arg(cur.getRate()));
        }
    }
}

Dish& StaticData::getDishByID(const QString& dishID) {
    if (dishList.empty())
        queryDish();
        for(unsigned int i = 0; i < dishList.size(); i ++)
                if(dishList[i].getDishID() == dishID)
                        return dishList[i];
        throw(EmptyResult("Dish not found"));
}

OrderedDish& StaticData::getOrderedDishByID(const QString& orderedDishID) {
    if (orderedDishList.empty())
        queryOrderedDish();
        for(unsigned int i = 0; i < orderedDishList.size(); i ++)
                if(orderedDishList[i].getOrderedDishID() == orderedDishID)
                        return orderedDishList[i];
        throw(EmptyResult("OrderedDish not found"));
}

vector<Msg*> StaticData::getMsgByReceiver(const QString& receiver) {
        queryMsg(receiver);
        vector<Msg*> msgListByReceiver;
        for(unsigned int i = 0; i < msgList.size(); i ++)
                if(msgList[i].getReceiver() == receiver)
                        msgListByReceiver.push_back(&msgList[i]);
        return msgListByReceiver;
}

vector<Msg*> StaticData::getMsgBySender(const QString& sender) {
    queryMsg(sender);
        vector<Msg*> msgListBySender;
        for(unsigned int i = 0; i < msgList.size(); i ++)
                if(msgList[i].getSender() == sender)
                        msgListBySender.push_back(&msgList[i]);
        return msgListBySender;
}

QString StaticData::getClerkPhoneByTable(int table) {
    if (clerkList.empty())
        queryClerk();
    for (unsigned int i = 0; i < clerkList.size(); i ++)
        for (unsigned int j = 0; j < clerkList[i].getTableList().size(); j ++)
            if (clerkList[i].getTableList()[j] == table)
                return clerkList[i].getPhone();
    throw(EmptyResult("Clerk Phone not found"));
}

QString StaticData::getPersonNameByPhone(const QString& phone) {
    if(!db->doQuery("person", "name", "phone = \"" + phone + "\""))
            throw(EmptyResult("Person Name not found"));
    return db->getResultList()[0][0];
}

void StaticData::updateEverythingAboutUser(Person *person, const QString& newPhone) {
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
    if (tableList.empty())
        queryTable();
    for(unsigned int i = 0; i < tableList.size(); i ++)
        if(tableList[i].getTableID() == tableID)
            return tableList[i];
    throw(EmptyResult("Table not found"));
}

Guest& StaticData::getGuestByPhone(const QString &phone) {
    for (unsigned int i = 0; i < guestList.size(); i ++)
        if (guestList[i].getPhone() == phone)
            return guestList[i];
    throw(EmptyResult("Guest not found"));
}

Chef& StaticData::getChefByPhone(const QString &phone) {
    if (chefList.empty())
        queryChef();
    for (unsigned int i = 0; i < chefList.size(); i ++)
        if (chefList[i].getPhone() == phone)
            return chefList[i];
    throw(EmptyResult("Chef not found"));
}

Clerk& StaticData::getClerkByPhone(const QString &phone) {
    if (clerkList.empty())
        queryClerk();
    for (unsigned int i = 0; i < clerkList.size(); i ++)
        if (clerkList[i].getPhone() == phone)
            return clerkList[i];
    throw(EmptyResult("Clerk not found"));
}

Rate& StaticData::getRateBySubjectAndObject(const QString &subject, const QString &object) {
    if (rateList.empty())
        queryRate();
    for (unsigned int i = 0; i < rateList.size(); i ++) {
        if (rateList[i].getSubject() == subject && rateList[i].getObject() == object)
            return rateList[i];
    }
    throw(EmptyResult("Rate not found"));
}

Manager& StaticData::getManagerByPhone(const QString &phone) {
    if (managerList.empty())
        queryManager();
    for (unsigned int i = 0; i < managerList.size(); i ++) {
        if (managerList[i].getPhone() == phone)
            return managerList[i];
    }
    throw EmptyResult("Manager not found");
}

//Person& getPersonByID(int id) {
//        return personList[0];
//}
