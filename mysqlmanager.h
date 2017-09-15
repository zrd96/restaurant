#ifndef _MYSQLMANAGER_H
#define _MYSQLMANAGER_H

#include <mysql/mysql.h>

#include <QString>
#include <vector>

#include "datamanager.h"

using namespace std;

class MySQLManager: public DataManager {
        public:
                MySQLManager(const QString &host, const QString &userName, const QString &password, unsigned int port);
                ~MySQLManager();
                void initConnection();
                bool doQuery(const QString &table, const QString &columns, const QString &wheres = "NULL");
                int queryID(const QString &name, double price, int timeNeeded, const QString &imgdir);
                vector<Msg> queryMsg(const QString &receiver);
                bool insert(const QString &table, const QString &values);
                bool update(const QString &table, const QString &column, const QString &newValue, const QString &wheres);
                bool deleteRow(const QString &table, const QString &wheres);
                bool doesExist(const QString &table, const QString &wheres);
                void destroyConnection();
                bool getConnectionStatus() const {return isConnected;}
                bool runSQLCommand(const QString &cmd);
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
