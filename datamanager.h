#ifndef _DATAMANAGER_H
#define _DATAMANAGER_H

#include <string>
#include <vector>

#include "msg.h"

using namespace std;

class DataManager {
        public:
                virtual int queryID(string phone) = 0;
                virtual vector<Msg> queryMsg(int receiver) = 0;
                virtual unsigned int insert(string request) = 0;
};

#endif
