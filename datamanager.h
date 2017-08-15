#ifndef _DATAMANAGER_H
#define _DATAMANAGER_H

#include <string>
#include <vector>

#include "msg.h"

using namespace std;

class DataManager {
        public:
                virtual void initConnection() = 0;
                virtual bool initDB() = 0;
                virtual bool doQuery(string, string, string = "NULL") = 0;
                virtual int queryID(string, string, int) = 0;
                virtual int queryID(string, double, int, string) = 0;
                virtual vector<Msg> queryMsg(int receiver) = 0;
                virtual bool insert(string table, string values) = 0;
                virtual bool update(string table, string column, string newValue, string wheres) = 0;
                virtual bool deleteRow(string table, string wheres) = 0;
                virtual bool getConnectionStatus() const = 0;
                vector<vector<string> > getResultList() const {return resultList;}
                string getErrInfo() const {return errInfo;}
        protected:
                vector<vector<string> > resultList;
                string errInfo;
};

#endif
