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
                MySQLManager(string host, string userName, string password, string dbName, unsigned int port);
                ~MySQLManager();
                void initConnection();
                int queryID(string phone);
                vector<Msg> queryMsg(int receiver);
                unsigned int insert(string request);
                void destroyConnection();
                bool getConnectionStatus();
        private:
                bool isConnected;
                MYSQL mySQLClient;
                char *HOST;
                char *USERNAME;
                char *PASSWORD;
                char *DBNAME;
                unsigned int DEFAULTPORT;
};

#endif
