#ifndef _ADMIN_H
#define _ADMIN_H

#include <QString>

#include "person.h"
#include "dish.h"
#include "table.h"

class Admin: public Person {
        public:
                //Admin(const QString &phone, const QString &name);
                Admin(const QString &phone, const QString &name, const QString &password);
                void setPhone(const QString &newPhone);
//                void addDish(const Dish &dish);
//                void removeDish(const Dish &dish);
//                void modifyDish(const Dish& dish, const QString &newName, double newPrice, int newTime, const QString &nreImgDir);

//                void addPerson(const Person& person, int type);
//                void removePerson(const Person& person);
//                void modifyPerson(const Person& person, const QString &newPhone, const QString &newName, const QString &newPassword);

//                void addTable(const Table& table);
//                void removeTable(const Table& table);
};

#endif
