#ifndef _STATICDATA_H
#define _STATICDATA_H

#include <vector>

//#include "person.h"
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
                //static vector<Person> personList;
                
                static bool queryDish();
                static bool queryOrderedDish();
                static bool queryMsg();
                //static bool queryPerson();

                static Dish& getDishByID(int dishID);
                static OrderedDish& getOrderedDishByID(int orderedDishID);
                static Msg& getMsgByReceiver(int receiver);
                //static Person& getPersonByID(int id);
};

#endif
