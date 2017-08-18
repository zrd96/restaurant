#ifndef _PERSON_H
#define _PERSON_H

#include <string>
#include <vector>

#include "msg.h"

using namespace std;

class Person {
        public:
                Person(string phone, string name, int type);
                string getName() {return name;}
                string getPhone() {return phone;}
                bool sendMsg(string receiver, string msg);
        private:
                string name;
                string phone;
};
#endif
