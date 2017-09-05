#include "adminwindow.h"
#include "guestwindow.h"
#include "chefwindow.h"
#include "clerkwindow.h"
#include "logindlg.h"
#include "staticdata.h"
#include "datamanager.h"
#include "mysqlmanager.h"
#include "admin.h"
#include "guest.h"
#include "chef.h"
#include "clerk.h"
#include "dish.h"
#include <QApplication>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
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
        Dish mutton("Mutton", 48, 20);
        Dish fish("Fish", 38, 20);
        Dish ds1("ds1", 20);
        Dish ds2("ds2", 15, 5);
        Dish ds3("ds3", 15);
        zrd.addDish(potato);
        zrd.addDish(noodle);
        zrd.addDish(chickenSoup);
        zrd.addDish(tomato);
        zrd.addDish(beaf);
        zrd.addDish(mutton);
        zrd.addDish(fish);
        zrd.addDish(ds1);
        zrd.addDish(ds2);
        zrd.addDish(ds3);

        cout<<"Adding dish succeeded"<<endl;

        zrd.modifyDish(beaf, "beaf", 68, 25, "img/dishes/beaf.jpg");

        cout<<"Modifying dish succeeded"<<endl;
        zrd.removeDish(potato);
        cout<<"Removing dish succeeded"<<endl;

        Table tb1(1, 2, 2), tb2(2, 2, 2), tb3(3, 10, 10), tb4(4, 2, 2), tb5(5, 2, 2), tb6(6, 4, 4), tb7(7, 4, 4), tb8(8, 10, 10), tb9(9, 10, 10), tb10(10, 2, 2);

        zrd.addTable(tb1);
        zrd.addTable(tb2);
        zrd.addTable(tb3);
        zrd.addTable(tb4);
        zrd.addTable(tb5);
        zrd.addTable(tb6);
        zrd.addTable(tb7);
        zrd.addTable(tb8);
        zrd.addTable(tb9);
        zrd.addTable(tb10);
        cout<<"Adding table succeeded"<<endl;

        zrd.removeTable(tb4);
        cout<<"removing table succeeded"<<endl;

        //Guest daddy("18110020001", "daddy", "000000");

        //daddy.selectTable(tb3);
        //cout<<"Guest selecting table succeeded"<<endl;

        //StaticData::queryDish();

//        for(int i = 0; i < StaticData::dishList.size(); i ++)
//                daddy.addDish(StaticData::dishList[i]);
//        daddy.addDish(StaticData::dishList[2]);
//        daddy.removeDish(StaticData::dishList[1]);
//        daddy.removeDish(StaticData::dishList[2]);

//        cout<<"Cart management succeeded"<<endl;

//        cout<<daddy.getSumInCart()<<endl;
//        //daddy.submit();
//        cout<<"Cart submitted"<<endl;

        Chef chef1("18110020003", "chef1", "123456");
        Chef chef2("18110020004", "chef2", "66666");
        Clerk clk1("18110020005", "clk1", "666666");
        Clerk clk2("18110020006", "clk2", "888888");
        Clerk clk3("18110020007", "clk3", "111111");

        zrd.addPerson(chef1, 2);
        zrd.addPerson(chef2, 2);
        zrd.addPerson(clk1, 3);
        zrd.addPerson(clk2, 3);
        zrd.addPerson(clk3, 3);
        //zrd.addPerson(daddy, 1);

        cout<<"Adding person succeeded"<<endl;

        zrd.modifyPerson(clk3, "18110020008", "clk3", "000000");
        cout<<"Modifying person succeeded"<<endl;
        Clerk newClk3("18110020008", "clk3");
        zrd.removePerson(newClk3);
        cout<<"Removing person succeeded"<<endl;

        StaticData::queryDish();
        StaticData::queryOrderedDish();
        //chef1.takeDish(StaticData::getOrderedDishByID(2));
        //chef1.finishDish(StaticData::getOrderedDishByID(2));
    }
    QApplication a(argc, argv);
    //w.show();
//    AdminWindow *adminWindow = new AdminWindow();
//    GuestWindow *guestWindow = new GuestWindow();
//    ChefWindow *chefWindow = new ChefWindow();
//    ClerkWindow *clerkWindow = new ClerkWindow();
    LoginDlg* loginDlg = new LoginDlg();
//    guestWindow->setLoginDlg(loginDlg);
//    adminWindow->setParent(loginDlg);
//    guestWindow->setParent(loginDlg);
//    chefWindow->setParent(loginDlg);
//    clerkWindow->setParent(loginDlg);
    loginDlg->show();

    return a.exec();
}
