#include <string>
#include <cstring>
#include <ctime>
#include <vector>
#include <iostream>
#include <sstream>

#include "tools.h"

using namespace std;

string ntos(int i) {
        stringstream stream;
        stream<<i;
        string s;
        stream>>s;
        return s;
}

string ntos(double f) {
    stringstream stream;
    stream<<f;
    string s;
    stream>>s;
    return s;
}

string getTime() {
        char *res = new char[30];
        time_t now = time(NULL);
        tm *ltm = localtime(&now);
        strftime(res, 30, "%F %T", ltm);
        return (string)res;
}

void viewResultList(vector<vector<string> > resultList) {
        for(unsigned int i = 0; i < resultList.size(); i ++) {
                for(unsigned int j = 0; j < resultList[i].size(); j ++)
                        cout<<resultList[i][j]<<' ';
                cout<<endl;
        }
}

void viewErrInfo(string errInfo) {cout<<errInfo<<endl;}

bool confirm(string info) {
        cout<<info<<" (y/n)"<<endl;
        //char ch = getchar();
        //getchar();
        //if(ch == 'Y' || ch == 'y')
                return true;
        return false;
}
