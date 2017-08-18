#ifndef _MYSQLMANAGER_H
#define _MYSQLMANAGER_H

#include <mysql/mysql.h>

#include <string>
#include <cstring>
#include <vector>

#include "datamanager.h"

using namespace std;

class MySQLManager: public DataManager {
        public:
                MySQLManager(string host, string userName, string password, unsigned int port);
                ~MySQLManager();
                void initConnection();
                bool doQuery(string table, string columns, string wheres = "NULL");
                int queryID(string name, double price, int timeNeeded, string imgdir);
                vector<Msg> queryMsg(string receiver);
                bool insert(string table, string values);
                bool update(string table, string column, string newValue, string wheres);
                bool deleteRow(string table, string wheres);
                void destroyConnection();
                bool getConnectionStatus() const {return isConnected;}
                bool runSQLCommand(const string cmd);
                bool initDB();
        private:
                MYSQL mySQLClient;
                bool isConnected;
                char *HOST;
                char *USERNAME;
                char *PASSWORD;
                char *DBNAME;
                unsigned int DEFAULTPORT;
};

#endif
