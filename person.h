#ifndef _PERSON_H
#define _PERSON_H

#include <string>
#include <vector>

#include "msg.h"

using namespace std;

class Person {
        public:
                Person(string phone, string name);
                int getID() {return id;}
                string getName() {return name;}
                string getPhone() {return phone;}
                vector<Msg> getMsg(MySQLManager *mysql);                      //get msg from MySQL
                bool sendMsg(int receiver, string msg);
        private:
                int id;
                string name;
                string phone;
                virtual int getIDFromDB() = 0;
};

#endif
