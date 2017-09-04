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

class StaticData {
        public:
                static DataManager *db;
                static vector<Dish> dishList;
                static vector<OrderedDish> orderedDishList;
                static vector<Msg> msgList;
                static vector<Clerk> clerkList;
                static vector<Table> tableList;
                //static vector<Person> personList;
                
                static bool queryTable();
                static bool queryDish();
                static bool queryOrderedDish();
                static bool queryMsg();
                static bool queryClerk();
                //static bool queryPerson();

                static Dish& getDishByID(int dishID);
                static OrderedDish& getOrderedDishByID(int orderedDishID);
                static vector<Msg> getMsgByReceiver(string receiver);
                static vector<Msg> getMsgBySender(string sender);
                static string getClerkPhoneByTable(int table);
                static string getPersonNameByPhone(string phone);

                //static Person& getPersonByID(int id);
};

#endif
