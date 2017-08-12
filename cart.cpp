#include <vector>

#include "dish.h"
#include "cart.h"
#include "tools.h"

Cart::Cart(DataManager *mydb): num(0), sum(0), mydb(mydb) {}

bool Cart::add(DishDB dish, int owner) {
        bool found = false;
        for(int i = 0; i < dishes.size(); i ++)
                if(dishes[i].getID() == dish.getID()) {
                        dishes[i].add();
                        found = true;
                }
        if(!found)
                dishes.push_back(Dish(dish, owner, 1));
        num ++;
        sum += dish.getPrice();

        return true;
}

bool Cart::remove(DishDB dish) {
        bool found = false;
        for (int i = 0; i < dishes.size(); i ++)
                if(dishes[i].getID() == dish.getID()) {
                        found = true;
                        if(dishes[i].getNum() > 1)
                                dishes[i].sub();
                        else
                                dishes.erase(dishes.begin() + i);
                        num --;
                }
        if(!found)
                return false;
        sum -= dish.getPrice();
        return true;
}

bool Cart::submit() {
        for (int i = 0; i < dishes.size(); i ++)
                if(!mydb->insert("dishes", "NULL, " + ntos(dishes[i].getID()) + ", " + ntos(dishes[i].getOrderer()) + ", 0"))
                        return false;
        return true;
}

bool Cart::checkout() {return true;}

void Cart::show() const {}
