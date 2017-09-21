#include "manager.h"

Manager::Manager(const QString &phone, const QString &name, const QString &password):
    Person(phone, name, password) {}

void Manager::setPhone(const QString &phone) {
    changePhone(phone);
}
