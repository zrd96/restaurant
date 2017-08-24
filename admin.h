#ifndef _ADMIN_H
#define _ADMIN_H

#include <string>

#include "person.h"
#include "dish.h"
#include "person.h"

class Admin: public Person {
        public:
                Admin(string phone, string name);
                bool addDish(Dish &dish);
                bool removeDish(Dish &dish);
                bool modifyDish(Dish& dish, string newName, double newPrice, int newTime, string nreImgDir);
                void viewDish();

                bool addPerson(Person& person, int type);
                bool removePerson(Person& person);
                bool modifyPerson(Person& person, string newPhone, string newName);
                void viewPerson();

                bool addTable(Table& table);
                bool removeTable(Table& table);
};

#endif
