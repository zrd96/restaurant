#ifndef _CHEF_H
#define _CHEF_H

#include <vector>

#include "datamanager.h"
#include "dish.h"
#include "staticdata.h"
#include "person.h"

class Chef: public Person {
        public:
                //Chef(const QString &phone, const QString &name);
                Chef(const QString &phone, const QString &name, const QString &password, int dishNum = 0, double averageTimeDifference = 0, int rateNum = 0, double averageRate = 0);

                int getDishNum() const {return dishNum;}
                double getAverageTimeDifference() const {return averageTimeDifference;}
                double getAverageRate() const {return averageRate;}
                int getRateNum() const {return rateNum;}
                vector<OrderedDish>& getTakenDish() {return dishTaken;}

                //main functions
                void takeDish(OrderedDish &dish);
                void finishDish(OrderedDish &dish);
                void updateRate(double newRate);

                //tool functions
                void checkDish();
                void setPhone(const QString &newPhone);
        private:
                int dishNum;
                double averageTimeDifference;
                double averageRate;
                int rateNum;
                vector<OrderedDish>dishTaken;
};

#endif
