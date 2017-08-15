#ifndef _PERSON_H
#define _PERSON_H

#include <string>
#include <vector>

#include "msg.h"

using namespace std;

class Person {
        public:
                Person(string phone, string name, int type);
                int getID() {return id;}
                string getName() {return name;}
                string getPhone() {return phone;}
                bool sendMsg(int receiver, string msg);
        private:
                int id;
                string name;
                string phone;
};
#endif
