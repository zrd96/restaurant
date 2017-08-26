#ifndef _CHEF_H
#define _CHEF_H

#include <vector>

#include "datamanager.h"
#include "dish.h"
#include "staticdata.h"
#include "person.h"

class Chef: public Person {
        public:
                Chef(string phone, string name);
                Chef(string phone, string name, string password);
                bool takeDish(const OrderedDish &dish);
                bool finishDish(const OrderedDish &dish);
        private:
                vector<OrderedDish>dishTaken;

};

#endif
