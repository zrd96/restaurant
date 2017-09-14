#ifndef _TABLE_H
#define _TABLE_H

#include <string>

#include "person.h"
#include "clerk.h"

class Clerk;

class Table {
        public:
                Table(int id, int seats, int freeSeats, string clerk = "");
                void linkClerk(Clerk& clerk);
                int getTableID() const {return id;}
                int getSeats() const {return seats;}
                int getFreeSeats() const {return freeSeats;}
                bool addGuest();
                string getClerk() const {return clerk;}
                static void viewAll();
        private:
                int id;
                int seats;
                int freeSeats;
                string clerk;
};

#endif
