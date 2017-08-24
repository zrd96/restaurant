#ifndef _TABLE_H
#define _TABLE_H

#include <string>

#include "person.h"
#include "clerk.h"

class Clerk;

class Table {
        public:
                Table(int num) {tableNum = num;}
                bool linkClerk(Clerk& clerk);
                int getNum() const {return tableNum;}
                string getClerk() const {return clerk;}
                static void viewAll();
        private:
                int tableNum;
                string clerk;
};

#endif
