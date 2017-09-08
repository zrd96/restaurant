#ifndef _STATICDATA_H
#define _STATICDATA_H

#include <vector>

#include "person.h"
#include "guest.h"
#include "admin.h"
#include "chef.h"
#include "clerk.h"
#include "dish.h"
#include "msg.h"
#include "datamanager.h"
#include "mysqlmanager.h"
#include "order.h"

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
    static vector<Table> tableList;
    static vector<Order> orderList;

    static vector<int> dishMaintainList;
    static vector<int> orderedDishMaintainList;
    static vector<int> msgMaintainList;
    static vector<int> guestMaintainList;
    static vector<int> chefMaintainList;
    static vector<int> clerkMaintainList;
    static vector<int> tableMaintainList;
    //static vector<int> orderMaintainList;

public:
    static DataManager *db;

    static bool queryTable();
    static bool queryDish();
    static bool queryOrderedDish();
    static bool queryMsg(string person);
    static bool queryClerk();
    static bool queryGuest();
    static bool queryChef();
    static bool queryOrder();
    static void clearMsgList();

    static void insertTable(const Table& table, int type = 0);
    static void insertDish(const Dish& dish, int type = 0);
    static void insertOrderedDish(const OrderedDish& orderedDish, int type = 0);
    static void insertMsg(const Msg& msg, int type = 0);
    static void insertGuest(const Guest& guest, int type = 0);
    static void insertClerk(const Clerk& clerk, int type = 0);
    static void insertChef(const Chef& chef, int type = 0);
    static void insertOrder(const Order& order);

    static void removeTable(const Table& table);
    static void removeDish(const Dish& dish);
    static void removeOrderedDish(const OrderedDish& orderedDish);
    static void removeMsg(const Msg& msg);
    static void removeGuest(const Guest& guest);
    static void removeClerk(const Clerk& clerk);
    static void removeChef(const Chef& chef);
    //static void removeOrder(const Order& order);

    static void modifyTable(const Table& table, const Table& newTable);
    static void modifyDish(const Dish& dish, const Dish& newDish);
    static void modifyOrderedDish(const OrderedDish& orderedDish, const OrderedDish& newOrderedDish);
    static void modifyMsg(const Msg& msg, const Msg& newMsg);
    static void modifyGuest(const Guest& guest, const Guest& newGuest);
    static void modifyClerk(const Clerk& clerk, const Clerk& newClerk);
    static void modifyChef(const Chef& chef, const Chef& newChef);
    //static void modifyOrder(const Order& order, const Order& newOrder);

    static void writeTable();
    static void writeDish();
    static void writeOrderedDish();
    static void writeMsg();
    static void writeGuest();
    static void writeClerk();
    static void writeChef();
    //static void writeOrder();

    static vector<Table>& getTableList() {return tableList;}
    static vector<Dish>& getDishList() {return dishList;}
    static vector<OrderedDish>& getOrderedDishList() {return orderedDishList;}
    static vector<Msg>& getMsgList() {return msgList;}
    static vector<Guest>& getGuestList() {return guestList;}
    static vector<Clerk>& getClerkList() {return clerkList;}
    static vector<Chef>& getChefList() {return chefList;}
    static vector<Order>& getOrderList() {return orderList;}

    static vector<int>& getTableMaintainMaintainList() {return tableMaintainList;}
    static vector<int>& getDishMaintainList() {return dishMaintainList;}
    static vector<int>& getOrderedDishMaintainList() {return orderedDishMaintainList;}
    static vector<int>& getMsgMaintainList() {return msgMaintainList;}
    static vector<int>& getGuestMaintainList() {return guestMaintainList;}
    static vector<int>& getClerkMaintainList() {return clerkMaintainList;}
    static vector<int>& getChefMaintainList() {return chefMaintainList;}
    static vector<int>& getOrderMaintainList() {return orderMaintainList;}

    static Dish& getDishByID(int dishID);
    static OrderedDish& getOrderedDishByID(int orderedDishID);
    static vector<Msg*> getMsgByReceiver(string receiver);
    static vector<Msg*> getMsgBySender(string sender);
    static string getClerkPhoneByTable(int table);
    static string getPersonNameByPhone(string phone);
    static void updateEverythingAboutUser(Person* person, string newPhone);
    static Table& getTableByID(int tableID);
};

#endif
