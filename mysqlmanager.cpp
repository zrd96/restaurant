#include <QString>
#include <cstring>
#include <cstdio>
#include <vector>

#include "msg.h"
#include "mysqlmanager.h"
#include "tools.h"
#include "emptyresult.h"

using namespace std;

MySQLManager::MySQLManager(const QString &host, const QString &userName, const QString &password, unsigned int port)
{

        isConnected = false;

        errInfo = "";

        resultList.clear();

        HOST = new char[host.length()];
        strcpy(HOST, host.toUtf8().data());
        
        USERNAME = new char[userName.length()];
        strcpy(USERNAME, userName.toUtf8().data());

        PASSWORD = new char[password.length()];
        strcpy(PASSWORD, password.toUtf8().data());

        DBNAME = NULL;

        DEFAULTPORT = port;
}

MySQLManager::~MySQLManager() {
        destroyConnection();
}

void MySQLManager::initConnection() {
        if (isConnected)
                return;
        mysql_init(&mySQLClient);
        isConnected = mysql_real_connect(&mySQLClient, HOST, USERNAME, PASSWORD, DBNAME, DEFAULTPORT, NULL, 0);
        if (isConnected) {
#define USESQL
        }
        else {
            throw EmptyResult("SQL Error");
        }
}

bool MySQLManager::runSQLCommand(const QString &cmd) {
        int queryReturn = mysql_real_query(&mySQLClient, cmd.toLocal8Bit().data(), (unsigned int)strlen(cmd.toLocal8Bit().data()));
        if (queryReturn) {
                errInfo = mysql_error(&mySQLClient);
                if (!errInfo.contains("exist")) {
                    viewErrInfo(errInfo);
                    return false;
                }
        }
        return true;
}

bool MySQLManager::initDB() {
        if(!runSQLCommand("create database restaurant character set utf8"))
            return false;
        runSQLCommand("use restaurant");
        if(!runSQLCommand("create table person(phone char(15) not NULL primary key, name char(20) default \"Client\", password char(20) not NULL, type tinyint not NULL, rate float, rateNum int unsigned, tableID int unsigned)"))
            return false;
        if(!runSQLCommand("create table msg(msgid char(50) not NULL primary key, sender char(15) not NULL, receiver char(15) not NULL, msg char(200) not NULL, time datetime not NULL, isActive tinyint unsigned not NULL)"))
            return false;
        if(!runSQLCommand("create table dish(dishid char(50) not NULL primary key, name char(200) not NULL, intro char(200), price float not NULL, rate float default 0, rateNum int unsigned default 0, time tinyint unsigned, imgdir char(250) default \"img/dishes/default.jpg\")"))
            return false;
        if(!runSQLCommand("create table orderedDish(id char(50) not NULL primary key, dishid char(50) not NULL, orderer char(15) not NULL, tableNum int unsigned not NULL, status tinyint unsigned not NULL, datetime char(20) not NULL, chef char(15) not NULL, request char(200) not NULL, rate float not NULL)"))
            return false;
        if(!runSQLCommand("create table tableList(id int unsigned not NULL auto_increment primary key, seats int unsigned not NULL, freeSeats int unsigned not NULL, clerk char(15) not NULL)"))
            return false;
        if(!runSQLCommand("create table rate(rateID char(100) not NULL primary key, rate float not NULL, subject char(15) not NULL, object char(50) not NULL, datetime char(20) not NULL, title char(50) not NULL, comments char(200) not NULL)"))
            return false;
        if(!runSQLCommand("create table orderList(orderID char(50) not NULL primary key, orderer char(15) not NULL, datetime char(20) not NULL, clerk char(15) not NULL, tableID tinyint unsigned not NULL, rate float not NULL)"));
            return false;
        return true;
}

bool MySQLManager::doQuery(const QString &table, const QString &columns, const QString &wheres) {
        QString cmd = "select " + columns + " from " + table;
        if(wheres != "NULL")
                cmd += " where " + wheres;
        if (!runSQLCommand(cmd))
            return false;

        MYSQL_RES *res = new MYSQL_RES;
        MYSQL_ROW row;

        res = mysql_store_result(&mySQLClient);
        resultList.clear();
        while (row = mysql_fetch_row(res)) {
                vector<QString> objectValue;
                for(int i = 0; i < mysql_num_fields(res); i ++) {
                        objectValue.push_back((row[i] == NULL ? "NULL": QString::fromLocal8Bit(row[i])));
                }
                resultList.push_back(objectValue);
        }

        mysql_free_result(res);
        return true;
}

bool MySQLManager::insert(const QString &table, const QString &values) {
        QString cmd = "insert into " + table + " values(" + values +")";
        return runSQLCommand(cmd);
}

bool MySQLManager::update(const QString &table, const QString &column, const QString &newValue, const QString &wheres) {
        QString cmd = "update " + table + " set " + column + " = " + newValue + " where " + wheres;
        return runSQLCommand(cmd);
}

bool MySQLManager::deleteRow(const QString &table, const QString &wheres) {
        QString cmd = "delete from " + table + " where " + wheres;
        return runSQLCommand(cmd);
}

bool MySQLManager::doesExist(const QString &table, const QString &wheres) {
    doQuery(table, "*", wheres);
    return (resultList.size() > 0);
}

void MySQLManager::destroyConnection() {
        mysql_close(&mySQLClient);
        isConnected = false;
}
