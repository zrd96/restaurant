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

Person::Person(const QString &phone, const QString &name): phone(phone), name(name) {
        //StaticData::db->insert("person", "\"" + phone + "\", \"" + name + "\", " + ntos(type) + ", NULL, NULL");
}

Person::Person(const QString &phone, const QString &name, const QString &password): phone(phone), password(password), name(name) {}

void Person::sendMsg(const QString &receiver, const QString &msg) {
    Msg newMsg(QString("M%1%2%3%4").arg(getTimeUniform()).arg(this->phone).arg(receiver).arg(StaticData::getMsgList().size()), this->phone, receiver, msg, getTime(), true);
    StaticData::insertMsg(newMsg, 1);
    //    return StaticData::db->insert("msg", "NULL, \"" + phone + "\", \"" + receiver + "\", \"" + msg + "\", \"" + getTime() + "\", 1");
}

