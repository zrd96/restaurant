#include <QString>
#include <string>
#include <ctime>
#include <vector>
#include <iostream>

#include "tools.h"

using namespace std;

QString getTime() {
        char *res = new char[30];
        time_t now = time(NULL);
        tm *ltm = localtime(&now);
        strftime(res, 30, "%F %T", ltm);
        return QString(res);
}

QString getTimeUniform() {
    char *res = new char[30];
    time_t now = time(NULL);
    tm *ltm = localtime(&now);
    strftime(res, 30, "%Y%m%d%H%M%S", ltm);
    return QString(res);
}

void viewResultList(vector<vector<QString> > resultList) {
        for(unsigned int i = 0; i < resultList.size(); i ++) {
                for(unsigned int j = 0; j < resultList[i].size(); j ++)
                        cout<<resultList[i][j].toStdString()<<' ';
                cout<<endl;
        }
}

void viewErrInfo(const QString &errInfo) {cout<<errInfo.toStdString()<<endl;}

bool confirm(const QString &info) {
        cout<<info.toStdString()<<" (y/n)"<<endl;
        //char ch = getchar();
        //getchar();
        //if(ch == 'Y' || ch == 'y')
                return true;
        return false;
}
