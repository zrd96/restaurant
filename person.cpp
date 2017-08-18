#include <string>
#include <typeinfo>
#include <vector>

#include "person.h"
#include "mysqlmanager.h"
#include "datamanager.h"
#include "tools.h"
#include "staticdata.h"

using namespace std;

Person::Person(string phone, string name, int type): phone(phone), name(name = "Guest") {
        StaticData::db->insert("person", "\"" + phone + "\", \"" + name + "\", " + ntos(type) + ", NULL, NULL");
}

bool Person::sendMsg(string receiver, string msg) {
        return StaticData::db->insert("msg", "NULL, \"" + phone + "\", \"" + receiver + "\", \"" + msg + "\", \"" + getTime() + "\"");
}

