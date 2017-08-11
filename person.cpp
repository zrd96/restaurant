#include <string>
#include <mysql/mysql.h>

#include "person.h"
#include "mysqlmanager.h"

using namespace std;

void generateID() {

}

Person::Person(string phone, string name): phone(phone), name(name = "顾客") {
        id = generateID();
}


