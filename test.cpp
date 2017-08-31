/*#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

#include <mysql/mysql.h>

#include "mysqlmanager.h"
#include "staticdata.h"
#include "tools.h"
#include "dish.h"
#include "cart.h"
#include "chef.h"
#include "person.h"
#include "guest.h"
#include "admin.h"

using namespace std;
 
int main()
{
        StaticData::db = new MySQLManager("127.0.0.1", "root", "L#f0e7d#X", (unsigned int)3306);
        StaticData::db->initConnection();
        if(StaticData::db->getConnectionStatus()) {
                StaticData::db->initDB();

                Admin zrd("18110026291", "zrd");

                Dish potato("potato", 12, 10);
                Dish noodle("noodle", 12, 10);
                Dish chickenSoup("chickenSoup", 25, 20);
                Dish tomato("tomato", 9, 5);
                Dish beaf("beaf", 48, 20);
                zrd.addDish(potato);
                zrd.addDish(noodle);
                zrd.addDish(chickenSoup);
                zrd.addDish(tomato);
                zrd.addDish(beaf);

                cout<<"Adding dish succeeded"<<endl;
                getchar();

                zrd.modifyDish(beaf, "beaf", 68, 25, "img/dishes/beaf.jpg");

                cout<<"Modifying dish succeeded"<<endl;
                zrd.removeDish(potato);
                cout<<"Removing dish succeeded"<<endl;

                Table tb1(1), tb2(2), tb3(3), tb4(4);

                zrd.addTable(tb1);
                zrd.addTable(tb2);
                zrd.addTable(tb3);
                zrd.addTable(tb4);
                cout<<"Adding table succeeded"<<endl;

                zrd.removeTable(tb4);
                cout<<"removing table succeeded"<<endl;

                Guest daddy("18110020001", "daddy");
                
                daddy.selectTable(tb3);
                cout<<"Guest selecting table succeeded"<<endl;

                StaticData::queryDish();

                for(int i = 0; i < StaticData::dishList.size(); i ++)
                        daddy.addDish(StaticData::dishList[i]);
                daddy.addDish(StaticData::dishList[2]);
                daddy.removeDish(StaticData::dishList[1]);
                daddy.removeDish(StaticData::dishList[2]);

                cout<<"Cart management succeeded"<<endl;
                getchar();

                cout<<daddy.getSumInCart()<<endl;
                daddy.submit();
                cout<<"Cart submitted"<<endl;
                getchar();

                Chef chef1("18110020003", "chef1");
                Chef chef2("18110020004", "chef2");
                Clerk clk1("18110020005", "clk1");
                Clerk clk2("18110020006", "clk2");
                Clerk clk3("18110020007", "clk3");

                zrd.addPerson(chef1, 2);
                zrd.addPerson(chef2, 2);
                zrd.addPerson(clk1, 3);
                zrd.addPerson(clk2, 3);
                zrd.addPerson(clk3, 3);

                cout<<"Adding person succeeded"<<endl;
                getchar();

                zrd.modifyPerson(clk3, "18110020008", "clk3");
                cout<<"Modifying person succeeded"<<endl;
                getchar();
                Clerk newClk3("18110020008", "clk3");
                zrd.removePerson(newClk3);
                cout<<"Removing person succeeded"<<endl;
                getchar();



                StaticData::queryDish();
                StaticData::queryOrderedDish();
                chef1.takeDish(StaticData::getOrderedDishByID(2));
                chef1.finishDish(StaticData::getOrderedDishByID(2));
        }
        
        cout<<getTime()<<endl;

        return 0;
}*/
