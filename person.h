#ifndef _PERSON_H
#define _PERSON_H

#include <QString>
#include <vector>

#include "msg.h"

using namespace std;

class Person {
        public:
                Person(const QString &phone, const QString &name);
                Person(const QString &phone, const QString &name, const QString &password);
                QString getName() const {return name;}
                QString getPhone() const {return phone;}
                QString getPassword() const {return password;}
                virtual void setPhone(const QString &newPhone) = 0;
                void changePhone(const QString &newPhone) {this->phone = newPhone;}
                void setPassword(const QString &password) {this->password = password;}
                void setName(const QString &name) {this->name = name;}
                void sendMsg(const QString &receiver, const QString &msg);
                virtual void doNothing() {}
        private:
                QString name;
                QString phone;
                QString password;
};
#endif
