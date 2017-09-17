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
#include "emptyresult.h"
#include <QApplication>
#include <QDebug>
#include <QString>
#include <iostream>
#include <QTextCodec>

using namespace std;

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
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
        try {
            Clerk tmp = StaticData::getClerkByPhone("12345");
        } catch (EmptyResult) {
            qDebug() << "er.getErrInfo()" <<endl;
        }
    }
    QApplication a(argc, argv);
    LoginDlg* loginDlg = new LoginDlg();
    loginDlg->show();
    a.setQuitOnLastWindowClosed(false);
    QFile qssfile("stylesheet/style.css");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();
    a.setStyleSheet(qss);
    qssfile.close();
    return a.exec();
}
