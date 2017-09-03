#include <vector>

#include "dish.h"
#include "cart.h"
#include "tools.h"
#include "staticdata.h"

Cart::Cart(): num(0), sum(0) {}

bool Cart::add(const Dish &dish, string owner, int tableNum) {
        bool found = false;
        for(int i = 0; i < orderedDishes.size(); i ++)
                if(orderedDishes[i].getDishID() == dish.getDishID()) {
                        orderedDishes[i].add();
                        found = true;
                }
        if(!found)
                orderedDishes.push_back(OrderedDish(dish, owner,tableNum, 0));
        num ++;
        sum += dish.getPrice();

        return true;
}

bool Cart::remove(const Dish &dish) {
        bool found = false;
        for (int i = 0; i < orderedDishes.size(); i ++)
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

bool Cart::submit() {
    for(int i = 0; i < orderedDishes.size(); i ++) {
        orderedDishes[i].setStatus(1);
        for(int j = 0; j < orderedDishes[i].getNum(); j ++)//split orders of the same dish and disable the num feature
            StaticData::orderedDishList.push_back(orderedDishes[i]);
    }
    orderedDishes.clear();
    num = 0;
    sum = 0;
    return true;
}

bool Cart::checkout() {return true;}

void Cart::show() const {}
