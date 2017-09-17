#include <vector>

#include "dish.h"
#include "cart.h"
#include "tools.h"
#include "staticdata.h"

Cart::Cart(): num(0), sum(0) {}

bool Cart::add(const Dish &dish, const QString &owner, int tableNum) {
        bool found = false;
        for(unsigned int i = 0; i < orderedDishes.size(); i ++)
                if(orderedDishes[i].getDishID() == dish.getDishID()) {
                        orderedDishes[i].add();
                        found = true;
                }
        if(!found)
                orderedDishes.push_back(OrderedDish(dish, "OD" + getTimeUniform() + owner, owner, tableNum, 0));
        num ++;
        sum += dish.getPrice();

        return true;
}

bool Cart::remove(const Dish &dish) {
        bool found = false;
        for (unsigned int i = 0; i < orderedDishes.size(); i ++)
                if(orderedDishes[i].getDishID() == dish.getDishID()) {
                        found = true;
                        if(orderedDishes[i].getNum() > 1)
                                orderedDishes[i].sub();
                        else
                                orderedDishes.erase(orderedDishes.begin() + i);
                        num --;
                        break;
                }
        if(!found)
                return false;
        sum -= dish.getPrice();
        return true;
}

bool Cart::submit(const QString &orderer, int table, const QString &request) {
    QString datetime = getTimeUniform();
    vector<OrderedDish> reshapedOrderedDish;
    for(unsigned int i = 0; i < orderedDishes.size(); i ++) {
        OrderedDish &cur = orderedDishes[i];
        for(int j = 0; j < cur.getNum(); j ++) {//split orders of the same dish and disable the num feature
            //orderedDishes[i].setOrderedDishID(QString("OD%1%2%3%4").arg(datetime).arg(orderer).arg(i).arg(j));
            OrderedDish tmp(StaticData::getDishByID(cur.getDishID()),
                            QString("OD%1%2%3%4").arg(datetime).arg(orderer).arg(i).arg(j),
                            orderer,
                            cur.getTable(),
                            datetime,
                            request,
                            1);
            reshapedOrderedDish.push_back(tmp);
            StaticData::insertOrderedDish(tmp, 1);
        }
    }
    Order newOrder(orderer, reshapedOrderedDish, datetime, table);
    StaticData::insertOrder(newOrder, 1);
    orderedDishes.clear();
    num = 0;
    sum = 0;
    return true;
}

bool Cart::checkout() {return true;}

void Cart::show() const {}
