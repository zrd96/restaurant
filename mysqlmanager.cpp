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
        if (queryReturn)
                return false;
        return true;
}

bool MySQLManager::initDB() {
        if(!runSQLCommand("create database restaurant character set gbk")) {
                errInfo = (string)mysql_error(&mySQLClient);
                if(errInfo.find("exist") < 0)
                        return false;
                errInfo = "";
        }
        runSQLCommand("use restaurant");
        if(!runSQLCommand("create table persons(id int unsigned not NULL auto_increment primary key, phone char(15) not NULL, name char(20) default \"Client\", type tinyint not NULL, rate float)")) {
                errInfo = (string)mysql_error(&mySQLClient);
                if(errInfo.find("exist") < 0)
                        return false;
                errInfo = "";
        }
        if(!runSQLCommand("create table msg(msgid int unsigned not NULL auto_increment primary key, sender int unsigned not NULL, receiver int unsigned not NULL, msg char(200) not NULL, time datetime not NULL)")) {
                errInfo = (string)mysql_error(&mySQLClient);
                if(errInfo.find("exist") < 0)
                        return false;
                errInfo = "";
        }
        if(!runSQLCommand("create table dishes(dishid int unsigned not NULL auto_increment primary key, name char(200) not NULL, price float not NULL, rate float default 0, rateNum int unsigned default 0, time tinyint unsigned, imgdir char(300) default \"img\\dishes\\default.jpg\")")) {
                errInfo = (string)mysql_error(&mySQLClient);
                if(errInfo.find("exist") < 0)
                        return false;
                errInfo = "";
        }
        return true;
}

bool MySQLManager::doQuery(string table, string columns, string wheres) {
        string cmd = "select " + columns + " from " + table + " where " + wheres;
        int queryReturn = mysql_real_query(&mySQLClient, cmd.c_str(), (unsigned int)strlen(cmd.c_str()));
        if (queryReturn) {
                errInfo = mysql_error(&mySQLClient);
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

int MySQLManager::queryID(string phone, string name, int type) {
        if (!doQuery("persons", "id", "phone = \"" + phone + "\""))
                return -1;

        if(!resultList.empty())
                return atoi(resultList[0][0].c_str());

        if(insert("persons", "NULL, " + phone + ", " + name + ", " + ntos(type) + "NULL"))
                return queryID(phone, name, type);
        return -1;
}

int MySQLManager::queryID(string name, double price, int timeNeeded) {
        if (!doQuery("dishes", "dishid", "name = \"" + name + "\""))
                return -1;

        if(!resultList.empty())
                return atoi(resultList[0][0].c_str());

        if(insert("dishes", "NULL, \"" + name + "\", " + ntos(price) + ", NULL, NULL, " + (ntos(timeNeeded) == "-1" ? "NULL" : ntos(timeNeeded))))
                return queryID(name, price, timeNeeded);
        return -1;
}

vector<Msg> MySQLManager::queryMsg(int receiver) {
        vector<Msg> msgs;

        if (!doQuery("msg", "sender, receiver, msg, time", "receiver = \"" + ntos(receiver) + "\""))
                return msgs;
        
        for (int i = 0; i < resultList.size(); i ++)
                msgs.push_back(Msg(atoi(resultList[i][0].c_str()), atoi(resultList[i][1].c_str()), resultList[i][2], resultList[i][3]));

        return msgs;
}

bool MySQLManager::insert(string table, string values) {
        string cmd = "insert into " + table + " values(" + values +")";
        
        int queryReturn = mysql_real_query(&mySQLClient, cmd.c_str(), (unsigned int)strlen(cmd.c_str()));

        if(queryReturn) {
                errInfo = mysql_error(&mySQLClient);
                return false;
        }
        return true;
}

void MySQLManager::destroyConnection() {
        mysql_close(&mySQLClient);
        isConnected = false;
}

