#include "logindlg.h"
#include "staticdata.h"
#include "emptyresult.h"
#include <QApplication>
#include <QDebug>
#include <QString>
#include <iostream>
#include <QSettings>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication restaurant(argc, argv);
    try {
        QSettings *SQLConf = new QSettings("MySQL.ini", QSettings::IniFormat);
        QString host = SQLConf->value("Config/HOST").toString();
        QString user = SQLConf->value("Config/USER").toString();
        QString password = SQLConf->value("Config/PASSWORD").toString();
        unsigned int port = SQLConf->value("Config/PORT").toUInt();
        StaticData::db = new MySQLManager(host, user, password, port);
        StaticData::db->initConnection();
    } catch (...) {
        viewErrInfo("MySQL Config error, using default");
        StaticData::db = new MySQLManager("127.0.0.1", "root", "L#f0e7d#X", 3306u);
        StaticData::db->initConnection();
    }
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
