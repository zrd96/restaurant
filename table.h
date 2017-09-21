#ifndef _TABLE_H
#define _TABLE_H

#include <QString>

#include "person.h"
#include "clerk.h"

class Clerk;

class Table {
        public:
                Table(int id, int seats, int freeSeats, const QString &clerk = "");

                int getTableID() const {return id;}
                int getSeats() const {return seats;}
                int getFreeSeats() const {return freeSeats;}
                QString getClerk() const {return clerk;}
                bool addGuest();
                void freeGuest();
                void linkClerk(Clerk& clerk);
        private:
                int id;
                int seats;
                int freeSeats;
                QString clerk;
};

#endif
