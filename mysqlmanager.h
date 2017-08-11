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
                int queryID(string phone, string name, string type);
                vector<Msg> queryMsg(int receiver);
                bool insert(string table, string values);
                void destroyConnection();
                bool getConnectionStatus() const {return isConnected;}
                string getErrInfo() {return MySQLManager::errInfo;}
                bool runSQLCommand(const string cmd);
                bool initDB();
        private:
                MYSQL mySQLClient;
                bool isConnected;
                string errInfo;
                char *HOST;
                char *USERNAME;
                char *PASSWORD;
                char *DBNAME;
                unsigned int DEFAULTPORT;
};

#endif
