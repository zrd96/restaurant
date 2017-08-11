#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include "msg.h"
#include "mysqlmanager.h"

using namespace std;

MySQLManager::MySQLManager(string host = "127.0.0.1", string userName = "root", string password = "", string dbName = "mysql", unsigned int port = 3022) {

        isConnected = false;

        HOST = new char[host.length()];
        strcpy(HOST, host.c_str());
        
        USERNAME = new char[userName.length()];
        strcpy(USERNAME, userName.c_str());

        PASSWORD = new char[password.length()];
        strcpy(PASSWORD, password.c_str());

        DBNAME = new char[dbName.length()];
        strcpy(DBNAME, dbName.c_str());

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

int MySQLManager::queryID(string phone) {
        string cmd = "select id from persons where phone = \'" + phone + "\'";
        int queryReturn = mysql_real_query(&mySQLClient, cmd.c_str(), (unsigned int)strlen(cmd.c_str()));
        if (queryReturn)
                return -1;

        MYSQL_RES *res;
        MYSQL_ROW row;

        res = mysql_store_result(&mySQLClient);
        row = mysql_fetch_row(res);
        if(mysql_num_rows(res) == 0)
                return 0;
        return atoi(row[0]);
}

vector<Msg> MySQLManager::queryMsg(int receiver) {
        char *receiverStringTmp = new char [20];
        sprintf(receiverStringTmp, "%d", receiver);

        string cmd = "select sender, receiver, msg, time from msg where receiver = \'" + (string)receiverStringTmp + "\'";
        int queryReturn = mysql_real_query(&mySQLClient, cmd.c_str(), (unsigned int)strlen(cmd.c_str()));

        vector<Msg> msgs;

        if (queryReturn)
                return msgs;

        MYSQL_RES *res;
        MYSQL_ROW row;
        res = mysql_store_result(&mySQLClient);

        while (row = mysql_fetch_row(res))
                msgs.push_back(Msg(atoi(row[0]), atoi(row[1]), (string)row[2], (string)row[3]));
        return msgs;
}

bool MySQLManager::insert(string table, string values) {
        string cmd = "insert into " + table + " values(" + values +")";
        
        int queryReturn = mysql_real_query(&mySQLClient, cmd.c_str(), (unsigned int)srelen(cmd.c_str()));

        if(queryReturn)
                return false;
        return true;
}

void MySQLManager::destroyConnection() {
        mysql_close(&mySQLClient);
        isConnected = false;
}

bool MySQLManager::getConnectionStatus() {return isConnected;}
