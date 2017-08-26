#include <string>
#include <cstring>
#include <vector>

#include "msg.h"
#include "mysqlmanager.h"
#include "tools.h"

using namespace std;

MySQLManager::MySQLManager(string host = "127.0.0.1", string userName = "root", string password = "", unsigned int port = 3022) {

        isConnected = false;

        errInfo = "";

        resultList.clear();

        HOST = new char[host.length()];
        strcpy(HOST, host.c_str());
        
        USERNAME = new char[userName.length()];
        strcpy(USERNAME, userName.c_str());

        PASSWORD = new char[password.length()];
        strcpy(PASSWORD, password.c_str());

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
}

bool MySQLManager::runSQLCommand(const string cmd) {
        int queryReturn = mysql_real_query(&mySQLClient, cmd.c_str(), (unsigned int)strlen(cmd.c_str()));
        if (queryReturn) {
                errInfo = mysql_error(&mySQLClient);
                viewErrInfo(errInfo);
                return false;
        }
        return true;
}

bool MySQLManager::initDB() {
        if(!runSQLCommand("create database restaurant character set utf8")) {
                errInfo = (string)mysql_error(&mySQLClient);
                if(errInfo.find("exist") < 0) {
                        viewErrInfo(errInfo);
                        return false;
                }
                errInfo = "";
        }
        runSQLCommand("use restaurant");
        if(!runSQLCommand("create table person(phone char(15) not NULL primary key, name char(20) default \"Client\", password char(20) not NULL, type tinyint not NULL, rate float, rateNum int unsigned)")) {
                errInfo = (string)mysql_error(&mySQLClient);
                if(errInfo.find("exist") < 0) {
                        viewErrInfo(errInfo);
                        return false;
                }
                errInfo = "";
        }
        if(!runSQLCommand("create table msg(msgid int unsigned not NULL auto_increment primary key, sender char(15) not NULL, receiver char(15) not NULL, msg char(200) not NULL, time datetime not NULL, isActive tinyint unsigned not NULL)")) {
                errInfo = (string)mysql_error(&mySQLClient);
                if(errInfo.find("exist") < 0) {
                        viewErrInfo(errInfo);
                        return false;
                }
                errInfo = "";
        }
        if(!runSQLCommand("create table dish(dishid int unsigned not NULL auto_increment primary key, name char(200) not NULL, price float not NULL, rate float default 0, rateNum int unsigned default 0, time tinyint unsigned, imgdir char(250) default \"img/dishes/default.jpg\")")) {
                errInfo = (string)mysql_error(&mySQLClient);
                viewErrInfo(errInfo);
                if(errInfo.find("exist") < 0) {
                        viewErrInfo(errInfo);
                        return false;
                }
                errInfo = "";
        }
        if(!runSQLCommand("create table orderedDish(id int unsigned not NULL auto_increment primary key, dishid int unsigned not NULL, orderer char(15) not NULL, tableNum int unsigned not NULL, num int unsigned not NULL, status tinyint unsigned not NULL)")) {
                errInfo = (string)mysql_error(&mySQLClient);
                if(errInfo.find("exist") < 0) {
                        viewErrInfo(errInfo);
                        return false;
                }
                errInfo = "";
        }
        if(!runSQLCommand("create table tableList(id int unsigned not NULL auto_increment primary key, seats int unsigned not NULL, clerk char(15))")) {
                errInfo = (string)mysql_error(&mySQLClient);
                if(errInfo.find("exist") < 0) {
                        viewErrInfo(errInfo);
                        return false;
                }
                errInfo = "";
        }

        /*
        insert("person", "\"18110026291\", \"ZRD\", 0, NULL, NULL");
        insert("person", "\"18110020001\", \"gst1\", 1, NULL, NULL");
        insert("person", "\"18110020002\", \"gst2\", 1, NULL, NULL");
        insert("person", "\"18110020003\", \"chef1\", 2, NULL, NULL");
        insert("person", "\"18110020004\", \"chef2\", 2, NULL, NULL");
        insert("person", "\"18110020005\", \"clk1\", 3, 8.9, 20");
        insert("person", "\"18110020006\", \"clk2\", 3, 8.8, 25");
        insert("person", "\"18110020007\", \"clk3\", 3,9.2, 40");

        insert("msg", "1, \"18110026291\", \"18110020005\", \"water\", \"2017-08-11 15:40:00\", 1");
        insert("msg", "2, \"18110020001\", \"18110020007\", \"water\", \"2017-08-11 15:45:00\", 1");
        insert("msg", "3, \"18110020001\", \"18110020007\", \"napkin\", \"2017-08-11 15:50:00\", 1");
        insert("msg", "4, \"18110020002\", \"18110020007\", \"quickly\", \"2017-08-11 15:55:00\", 1");
        insert("msg", "5, \"18110020007\", \"18110020003\", \"quickly\", \"2017-08-11 15:56:00\", 1");

        insert("dish", "1, \"rice\", 2, 9.3, 258, 1, \"img/dishes/default.jpg\"");
        insert("dish", "2, \"noodle\", 12, 8.9, 127, 5, \"img/dishes/default.jpg\"");
        insert("dish", "3, \"potato\", 12, NULL, NULL, 10, \"img/dishes/default.jpg\"");
        insert("dish", "4, \"tomato\", 9, NULL, NULL, 5, \"img/dishes/default.jpg\"");
        insert("dish", "5, \"beaf\", 48, 9.6, 328, 20, \"img/dishes/default.jpg\"");
        insert("dish", "6, \"lattice\", 8, 8.8, 68, 3, \"img/dishes/default.jpg\"");

        insert("tableList", "1, 1, \"18110020005\"");
        insert("tableList", "2, 1, \"18110020005\"");
        insert("tableList", "3, 1, \"18110020006\"");
        insert("tableList", "4, 1, \"18110020007\"");
        insert("tableList", "5, 1, \"18110020007\"");
*/
        return true;
}

bool MySQLManager::doQuery(string table, string columns, string wheres) {
        string cmd = "select " + columns + " from " + table;
        if(wheres != "NULL")
                cmd += " where " + wheres;
        int queryReturn = mysql_real_query(&mySQLClient, cmd.c_str(), (unsigned int)strlen(cmd.c_str()));
        if (queryReturn) {
                errInfo = mysql_error(&mySQLClient);
                viewErrInfo(errInfo);
                return false;
        }

        MYSQL_RES *res = new MYSQL_RES;
        MYSQL_ROW row;

        res = mysql_store_result(&mySQLClient);
        resultList.clear();
        while (row = mysql_fetch_row(res)) {
                vector<string> objectValue;
                for(int i = 0; i < mysql_num_fields(res); i ++)
                        objectValue.push_back((row[i] == NULL ? "NULL": (string)row[i]));
                resultList.push_back(objectValue);
        }

        mysql_free_result(res);
        return true;
}
/*
int MySQLManager::queryID(string phone, string name, int type) {
        if (!doQuery("person", "id", "phone = \"" + phone + "\""))
                return -1;

        if(!resultList.empty())
                return atoi(resultList[0][0].c_str());

        if(insert("person", "NULL, " + phone + ", " + name + ", " + ntos(type) + "NULL"))
                return queryID(phone, name, type);
        return -1;
}
*/
int MySQLManager::queryID(string name, double price, int timeNeeded, string imgdir) {
        if (!doQuery("dish", "dishid", "name = \"" + name + "\""))
                return -1;

        if(!resultList.empty())
                return atoi(resultList[0][0].c_str());

        if(insert("dish", "NULL, \"" + name + "\", " + ntos(price) + ", NULL, NULL, " + (ntos(timeNeeded) == "-1" ? "NULL" : ntos(timeNeeded)) + ", \"" + imgdir + "\""))
                return queryID(name, price, timeNeeded, imgdir);
        return -1;
}

vector<Msg> MySQLManager::queryMsg(string receiver) {
        vector<Msg> msgs;

        if (!doQuery("msg", "sender, receiver, msg, time, isActive", "receiver = \"" + receiver + "\""))
                return msgs;
        
        for (int i = 0; i < resultList.size(); i ++)
                msgs.push_back(Msg(resultList[i][0], resultList[i][1], resultList[i][2], resultList[i][3], atoi(resultList[i][4].c_str())));

        return msgs;
}

bool MySQLManager::insert(string table, string values) {
        string cmd = "insert into " + table + " values(" + values +")";
        return runSQLCommand(cmd);
}

bool MySQLManager::update(string table, string column, string newValue, string wheres) {
        string cmd = "update " + table + " set " + column + " = " + newValue + " where " + wheres;
        return runSQLCommand(cmd);
}

bool MySQLManager::deleteRow(string table, string wheres) {
        string cmd = "delete from " + table + " where " + wheres;
        return runSQLCommand(cmd);
}

void MySQLManager::destroyConnection() {
        mysql_close(&mySQLClient);
        isConnected = false;
}

