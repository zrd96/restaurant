#include <string>
#include <typeinfo>
#include <vector>

#include "person.h"
#include "mysqlmanager.h"
#include "datamanager.h"
#include "tools.h"
#include "msg.h"
#include "staticdata.h"

using namespace std;

Person::Person(string phone, string name): phone(phone), name(name = "Guest") {
        //StaticData::db->insert("person", "\"" + phone + "\", \"" + name + "\", " + ntos(type) + ", NULL, NULL");
}

Person::Person(string phone, string name, string password): phone(phone), password(password), name(name) {}

void Person::sendMsg(string receiver, string msg) {
    Msg newMsg("M" + getTimeUniform() + this->phone + receiver + ntos((int)StaticData::getMsgList().size()), this->phone, receiver, msg, getTime(), true);
    StaticData::insertMsg(newMsg, 1);
    //    return StaticData::db->insert("msg", "NULL, \"" + phone + "\", \"" + receiver + "\", \"" + msg + "\", \"" + getTime() + "\", 1");
}

