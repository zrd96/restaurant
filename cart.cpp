#include <vector>

#include "dish.h"
#include "cart.h"
#include "tools.h"
#include "staticdata.h"

Cart::Cart(): num(0), sum(0) {}

bool Cart::add(const Dish &dish, int owner) {
        bool found = false;
        for(int i = 0; i < orderedDishes.size(); i ++)
                if(orderedDishes[i].getDishID() == dish.getDishID()) {
                        orderedDishes[i].add();
                        found = true;
                }
        if(!found)
                orderedDishes.push_back(OrderedDish(dish, owner, 1));
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
                }
        if(!found)
                return false;
        sum -= dish.getPrice();
        return true;
}

bool Cart::submit() {
        for (int i = 0; i < orderedDishes.size(); i ++)
                if(!StaticData::db->insert("orderedDishes", "NULL, " + ntos(orderedDishes[i].getDishID()) + ", " + ntos(orderedDishes[i].getOrderer()) + ", 0"))
                        return false;
        return true;
}

bool Cart::checkout() {return true;}

void Cart::show() const {}
