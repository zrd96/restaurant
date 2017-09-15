#ifndef _CHEF_H
#define _CHEF_H

#include <vector>

#include "datamanager.h"
#include "dish.h"
#include "staticdata.h"
#include "person.h"

class Chef: public Person {
        public:
                Chef(const QString &phone, const QString &name);
                Chef(const QString &phone, const QString &name, const QString &password);
                bool takeDish(OrderedDish &dish);
                bool finishDish(OrderedDish &dish);
                void checkDish();
                void setPhone(const QString &newPhone);
                vector<OrderedDish>& getTakenDish() {return dishTaken;}
        private:
                vector<OrderedDish>dishTaken;

};

#endif
