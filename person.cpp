#include <string>
#include <vector>

#include "person.h"
#include "mysqlmanager.h"
#include "tools.h"

using namespace std;

Person::Person(string phone, string name): phone(phone), name(name = "顾客") {
        id = getIDFromDB();
}

vector<Msg> Person::getMsg(DataManager *mydb) {
        return mydb->queryMsg(id);
}

bool Person::sendMsg(DataManger *mydb, int receiver, string msg) {
        return mydb->insert("msg", "NULL, " + itos(id) + ", " + itos(receiver) + ", " + msg + ", " + getTime());
}


