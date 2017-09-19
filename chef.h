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
                Chef(const QString &phone, const QString &name, const QString &password, int dishNum, double averageTimeDifference, int rateNum, double averageRate);
                int getDishNum() const {return dishNum;}
                double getAverageTimeDifference() const {return averageTimeDifference;}
                double getAverageRate() const {return averageRate;}
                int getRateNum() const {return rateNum;}
                bool takeDish(OrderedDish &dish);
                bool finishDish(OrderedDish &dish);
                void updateRate(double newRate);
                void checkDish();
                void setPhone(const QString &newPhone);
                vector<OrderedDish>& getTakenDish() {return dishTaken;}
        private:
                vector<OrderedDish>dishTaken;
                int dishNum;
                double averageTimeDifference;
                double averageRate;
                int rateNum;
};

#endif
