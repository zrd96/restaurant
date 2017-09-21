#include "logindlg.h"
#include "staticdata.h"
#include "emptyresult.h"
#include <QApplication>
#include <QDebug>
#include <QString>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    StaticData::db = new MySQLManager("127.0.0.1", "root", "L#f0e7d#X", 3306u);
    StaticData::db->initConnection();
    if(StaticData::db->getConnectionStatus()) {
        StaticData::db->initDB();
        StaticData::queryTable();
        StaticData::queryDish();
        StaticData::queryOrderedDish();
        StaticData::queryOrder();
        StaticData::queryClerk();
        StaticData::queryChef();
        StaticData::queryRate();
        StaticData::queryManager();
    }
    QApplication restaurant(argc, argv);
    LoginDlg* loginDlg = new LoginDlg();
    loginDlg->show();
    restaurant.setQuitOnLastWindowClosed(false);
    QFile qssfile("stylesheet/style.css");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();
    restaurant.setStyleSheet(qss);
    qssfile.close();
    return restaurant.exec();
}
