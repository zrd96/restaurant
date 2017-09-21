#ifndef _DATAMANAGER_H
#define _DATAMANAGER_H

#include <vector>
#include <QString>

#include "msg.h"

using namespace std;

class DataManager {
        public:
                virtual void initConnection() = 0;
                virtual bool initDB() = 0;
                virtual bool doQuery(const QString &table, const QString &column, const QString &wheres = "NULL") = 0;
                virtual bool insert(const QString &table, const QString &values) = 0;
                virtual bool update(const QString &table, const QString &column, const QString &newValue, const QString &wheres) = 0;
                virtual bool deleteRow(const QString &table, const QString &wheres) = 0;
                virtual bool doesExist(const QString &table, const QString &wheres) = 0;
                virtual bool getConnectionStatus() const = 0;
                vector<vector<QString> > getResultList() const {return resultList;}
                QString getErrInfo() const {return errInfo;}
        protected:
                vector<vector<QString> > resultList;
                QString errInfo;
};

#endif
