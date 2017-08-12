#ifndef _DATAMANAGER_H
#define _DATAMANAGER_H

#include <string>
#include <vector>

#include "msg.h"

using namespace std;

class DataManager {
        public:
                virtual bool doQuery(string, string, string) = 0;
                virtual int queryID(string, string, int) = 0;
                virtual int queryID(string, double, int) = 0;
                virtual vector<Msg> queryMsg(int receiver) = 0;
                virtual bool insert(string table, string values) = 0;
                vector<vector<string> > getResultList() const {return resultList;}
                string getErrInfo() const {return errInfo;}
        protected:
                vector<vector<string> > resultList;
                string errInfo;
};

#endif
