#ifndef _STATICDATA_H
#define _STATICDATA_H

#include <vector>

#include "person.h"
#include "guest.h"
#include "admin.h"
#include "chef.h"
#include "clerk.h"
#include "manager.h"
#include "dish.h"
#include "msg.h"
#include "datamanager.h"
#include "mysqlmanager.h"
#include "order.h"
#include "rate.h"

class Order;
class Chef;

class StaticData {
private:
    static vector<Dish> dishList;
    static vector<OrderedDish> orderedDishList;
    static vector<Msg> msgList;
    static vector<Guest> guestList;
    static vector<Chef> chefList;
    static vector<Clerk> clerkList;
    static vector<Manager> managerList;
    static vector<Table> tableList;
    static vector<Order> orderList;
    static vector<Rate> rateList;

    static vector<int> dishMaintainList;
    static vector<int> orderedDishMaintainList;
    static vector<int> msgMaintainList;
    static vector<int> guestMaintainList;
    static vector<int> chefMaintainList;
    static vector<int> clerkMaintainList;
    static vector<int> managerMaintainList;
    static vector<int> tableMaintainList;
    static vector<int> rateMaintainList;
    static vector<int> orderMaintainList;

public:
    static DataManager *db;

    static bool queryTable();
    static bool queryDish();
    static bool queryOrderedDish();
    static bool queryMsg(const QString &person);
    static bool queryClerk();
    static bool queryGuest();
    static bool queryChef();
    static bool queryOrder();
    static bool queryRate();
    static bool queryManager();
    static void clearMsgList();

    static void insertTable(const Table &table, int type = 0);
    static void insertDish(const Dish &dish, int type = 0);
    static void insertOrderedDish(const OrderedDish &orderedDish, int type = 0);
    static void insertMsg(const Msg &msg, int type = 0);
    static void insertGuest(const Guest &guest, int type = 0);
    static void insertClerk(const Clerk &clerk, int type = 0);
    static void insertManager(const Manager &manager, int type = 0);
    static void insertChef(const Chef &chef, int type = 0);
    static void insertOrder(const Order &order, int type = 0);
    static void insertRate(const Rate &rate, int type = 0);

    static void removeTable(int tableID);
    static void removeDish(const QString& dishID);
    static void removeOrderedDish(const QString& orderedDishID);
    static void removeMsg(const QString& msgID);
    static void removeGuest(const QString& phone);
    static void removeClerk(const QString& phone);
    static void removeManager(const QString& phone);
    static void removeChef(const QString& phone);
    //static void removeOrder(const Order& order);

    static void modifyTable(int tableID, const Table& newTable);
    static void modifyDish(const QString& dishID, const Dish& newDish);
    static void modifyOrderedDish(const QString& orderedDishID, const OrderedDish& newOrderedDish);
    static void modifyMsg(const QString& msgID, const Msg& newMsg);
    static void modifyGuest(const QString& phone, const Guest& newGuest);
    static void modifyClerk(const QString& phone, const Clerk& newClerk);
    static void modifyManager(const QString& phone, const Manager& newManager);
    static void modifyChef(const QString& phone, const Chef& newChef);
    static void modifyOrder(const QString &orderID, const Order& newOrder);

    static void writeTable();
    static void writeDish();
    static void writeOrderedDish();
    static void writeMsg();
    static void writeGuest();
    static void writeClerk();
    static void writeManager();
    static void writeChef();
    static void writeRate();
    static void writeOrder();

    static vector<Table>& getTableList() {return tableList;}
    static vector<Dish>& getDishList() {return dishList;}
    static vector<OrderedDish>& getOrderedDishList() {return orderedDishList;}
    static vector<Msg>& getMsgList() {return msgList;}
    static vector<Guest>& getGuestList() {return guestList;}
    static vector<Clerk>& getClerkList() {return clerkList;}
    static vector<Chef>& getChefList() {return chefList;}
    static vector<Manager>& getManagerList() {return managerList;}
    static vector<Order>& getOrderList() {return orderList;}
    static vector<Rate>& getRateList() {return rateList;}

    static vector<int>& getTableMaintainList() {return tableMaintainList;}
    static vector<int>& getDishMaintainList() {return dishMaintainList;}
    static vector<int>& getOrderedDishMaintainList() {return orderedDishMaintainList;}
    static vector<int>& getMsgMaintainList() {return msgMaintainList;}
    static vector<int>& getGuestMaintainList() {return guestMaintainList;}
    static vector<int>& getClerkMaintainList() {return clerkMaintainList;}
    static vector<int>& getChefMaintainList() {return chefMaintainList;}
    static vector<int>& getManagerMaintainList() {return managerMaintainList;}
    static vector<int>& getRateMaintainList() {return rateMaintainList;}
    static vector<int>& getOrderMaintainList() {return orderMaintainList;}

    static Dish& getDishByID(const QString& dishID);
    static OrderedDish& getOrderedDishByID(const QString& orderedDishID);
    static vector<Msg*> getMsgByReceiver(const QString& receiver);
    static vector<Msg*> getMsgBySender(const QString& sender);
    static QString getClerkPhoneByTable(int table);
    static QString getPersonNameByPhone(const QString& phone);
    static void updateEverythingAboutUser(Person* person, const QString& newPhone);
    static Table& getTableByID(int tableID);
    static Guest& getGuestByPhone(const QString &phone);
    static Chef& getChefByPhone(const QString &phone);
    static Clerk& getClerkByPhone(const QString &phone);
    static Rate& getRateBySubjectAndObject(const QString &subject, const QString &object);
    static Manager& getManagerByPhone(const QString &phone);
};

#endif
