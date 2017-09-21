#ifndef MANAGER_H
#define MANAGER_H

#include <QString>
#include "person.h"

class Manager : public Person
{
public:
    Manager(const QString &phone, const QString &name, const QString &password);
    void setPhone(const QString &phone);
};

#endif // MANAGER_H
