#include <string>

#include "table.h"
#include "clerk.h"

void Table::viewAll() {}

bool Table::linkClerk(Clerk& clerk) {
        this->clerk = clerk.getPhone();
        return true;
}


