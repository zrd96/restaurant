#include <string>
#include <typeinfo>
#include <vector>

#include "person.h"
#include "mysqlmanager.h"
#include "datamanager.h"
#include "tools.h"
#include "staticdata.h"

using namespace std;

Person::Person(string phone, string name, int type): phone(phone), name(name = "顾客") {
        id = StaticData::db->queryID(phone, name, type);
}

bool Person::sendMsg(int receiver, string msg) {
        return StaticData::db->insert("msg", "NULL, " + ntos(id) + ", " + ntos(receiver) + ", " + msg + ", " + getTime());
}


