#include <string>
#include <vector>

#include "person.h"
#include "tools.h"
#include "admin.h"
#include "mysqlmanager.h"
#include "datamanager.h"
#include "staticdata.h"
#include "tools.h"

Admin::Admin(string phone, string name): Person(phone, name) {}

bool Admin::addDish(const Dish& dish) {
        StaticData::db->doQuery("dish", "dishid", "name = \"" + dish.getName() + "\"");
        if(StaticData::db->getResultList().size()) {
                if(!confirm("Dish " + dish.getName() + " already exists, overwrite?"))
                        return false;
                else 
                        StaticData::db->deleteRow("dish", "name = \"" + dish.getName() + "\"");
        }
        StaticData::db->insert("dish", "NULL, \"" + dish.getName() + "\", " + ntos(dish.getPrice()) + ", " + ntos(dish.getRate()) + ", " + ntos(dish.getRateNum()) + ", " + ntos(dish.getTimeNeeded()) + ", \"" + dish.getImgDir() + "\"");
        /*StaticData::db->doQuery("dish", "dishid", "name = \"" + dish.getName() + "\"");
        int insertedDishid = atoi(StaticData::db->getResultList()[0][0].c_str());
        dish.confirmID(insertedDishid);*/
        return true;
}

bool Admin::removeDish(const Dish& dish) {
        StaticData::db->doQuery("dish", "dishid", "name = \"" + dish.getName() + "\"");
        if(StaticData::db->getResultList().size() == 0) {
                viewErrInfo("Dish " + dish.getName() +" does not exist!");
                return false;
        }
                else if(!confirm("Remove dish " + dish.getName() + "?"))
                        return false;
                else
                        return StaticData::db->deleteRow("dish", "name = \"" + dish.getName() +"\"");
}

bool Admin::modifyDish(const Dish& dish, string newName, double newPrice, int newTime, string newImgDir) {
        StaticData::db->doQuery("dish", "dishid", "name = \"" + dish.getName() + "\"");
        if(StaticData::db->getResultList().size() == 0) {
                viewErrInfo("Dish " + dish.getName() +" does not exist!");
                return false;
        }
        else if(!confirm("Modify dish " + dish.getName() + "?"))
                return false;
        else {
                string currentID = StaticData::db->getResultList()[0][0];
                StaticData::db->update("dish", "name", "\"" + newName + "\"", "dishid = " + currentID);
                StaticData::db->update("dish", "price", ntos(newPrice), "dishid = " + currentID);
                StaticData::db->update("dish", "time", ntos(newTime), "dishid = " + currentID);
                StaticData::db->update("dish", "imgdir", "\"" + newImgDir + "\"", "dishid = " + currentID);
                return true;
        }
}

void Admin::viewDish() {
        Dish::showAll();
}

bool Admin::addPerson(const Person& person, int type) {
        StaticData::db->doQuery("person", "phone", "phone = \"" + person.getPhone() + "\"");
        if(StaticData::db->getResultList().size())
                if(!confirm("User " + person.getPhone() + " already exists, overwrite?"))
                        return false;
        return StaticData::db->insert("person", "\"" + person.getPhone() +"\", \"" + person.getName() + "\", \"" + person.getPassword() + "\", " + ntos(type) + ", NULL, NULL");
}

bool Admin::removePerson(const Person& person) {
        StaticData::db->doQuery("person", "phone", "phone = \"" + person.getPhone() + "\"");
        if(StaticData::db->getResultList().size() == 0) {
                viewErrInfo("User " + person.getPhone() +" does not exist!");
                return false;
        }
                else if(!confirm("Remove user " + person.getPhone() + "?"))
                        return false;
                else
                        return StaticData::db->deleteRow("person", "phone = \"" + person.getPhone() +"\"");
}

bool Admin::modifyPerson(const Person& person, string newPhone, string newName, string newPassword) {
        StaticData::db->doQuery("person", "phone", "phone = \"" + person.getPhone() + "\"");
        if(StaticData::db->getResultList().size() == 0) {
                viewErrInfo("User " + person.getPhone() +" does not exist!");
                return false;
        }
                else if(!confirm("Modify user " + person.getPhone() + "?"))
                        return false;
                else {
                        StaticData::db->update("person", "phone", "\"" + newPhone + "\"", "phone = \"" + person.getPhone() + "\"");
                        StaticData::db->update("person", "name", "\"" + newName + "\"", "phone = \"" + newPhone + "\"");
                        StaticData::db->update("person", "password", "\"" + newPassword + "\"", "phone = \"" + newPhone + "\"");
                        return true;
                }
}

void Admin::viewPerson() {}

bool Admin::addTable(const Table& table) {
        return StaticData::db->insert("tableList", ntos(table.getTableID()) + ", " + ntos(table.getSeats()) + ", " + ntos(table.getFreeSeats()) + ", \"NULL\"");
}

bool Admin::removeTable(const Table& table) {
        return StaticData::db->deleteRow("tableList", "id = " + ntos(table.getTableID()));
}

void Admin::setPhone(string newPhone) {
    changePhone(newPhone);
}
