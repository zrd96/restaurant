#include <QString>

#include "table.h"
#include "clerk.h"
#include "staticdata.h"

Table::Table(int id, int seats, int freeSeats, const QString &clerk):
    id(id),
    seats(seats),
    freeSeats(freeSeats),
    clerk(clerk) {}

void Table::viewAll() {}

void Table::linkClerk(Clerk& clerk) {
    this->clerk = clerk.getPhone();
    StaticData::modifyTable(this->getTableID(), *this);
}

bool Table::addGuest() {
    if(freeSeats == 0)
        return false;
    freeSeats --;
    StaticData::modifyTable(this->getTableID(), *this);
    return true;
}
