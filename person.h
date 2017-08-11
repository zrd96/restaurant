#ifndef _PERSON_H
#define _PERSON_H

#include <string>

using namespace std;

class Person {
        public:
                Person(string phone, string name);
                int getID() {return id;}
                string getName() {return name;}
                string getPhone() {return phone;}
                void getMsg();                      //get msg from MySQL
                void sendMsg(Person *p, string msg);
        private:
                int id;
                string name;
                string phone;
};

#endif
