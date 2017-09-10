#ifndef _ADMIN_H
#define _ADMIN_H

#include <string>

#include "person.h"
#include "dish.h"
#include "person.h"

class Admin: public Person {
        public:
                Admin(string phone, string name);
                Admin(string phone, string name, string password);
                void setPhone(string newPhone);
                void addDish(const Dish &dish);
                void removeDish(const Dish &dish);
                void modifyDish(const Dish& dish, string newName, double newPrice, int newTime, string nreImgDir);

                void addPerson(const Person& person, int type);
                void removePerson(const Person& person);
                void modifyPerson(const Person& person, string newPhone, string newName, string newPassword);

                void addTable(const Table& table);
                void removeTable(const Table& table);
};

#endif
