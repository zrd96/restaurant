#ifndef _PERSON_H
#define _PERSON_H

#include <string>
#include <vector>

#include "msg.h"

using namespace std;

class Person {
        public:
                Person(string phone, string name);
                Person(string phone, string name, string password);
                string getName() const {return name;}
                string getPhone() const {return phone;}
                string getPassword() const {return password;}
                virtual void setPhone(string newPhone) = 0;
                void changePhone(string newPhone) {this->phone = newPhone;}
                void setPassword(string password) {this->password = password;}
                void setName(string name) {this->name = name;}
                bool sendMsg(string receiver, string msg);
                virtual void doNothing() {}
        private:
                string name;
                string phone;
                string password;
};
#endif
