#ifndef _ADMIN_H
#define _ADMIN_H

#include <string>

#include "person.h"
#include "dish.h"
#include "person.h"

class Admin: public Person {
        public:
                Admin(string phone, string name);
                void setPhone(string newPhone);
                bool addDish(const Dish &dish);
                bool removeDish(const Dish &dish);
                bool modifyDish(const Dish& dish, string newName, double newPrice, int newTime, string nreImgDir);
                void viewDish();

                bool addPerson(const Person& person, int type);
                bool removePerson(const Person& person);
                bool modifyPerson(const Person& person, string newPhone, string newName, string newPassword);
                void viewPerson();

                bool addTable(const Table& table);
                bool removeTable(const Table& table);
};

#endif
