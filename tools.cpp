#include <string>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <vector>
#include <iostream>

#include "tools.h"

using namespace std;

string ntos(int i) {
        char *s = new char[20];
        sprintf(s, "%d", i);
        return (string)s;
}

string ntos(double f) {
        char *s = new char[20];
        sprintf(s, "%lf", f);
        return (string)s;
}

string getTime() {
        char *res = new char[30];
        time_t now = time(NULL);
        tm *ltm = localtime(&now);
        strftime(res, 30, "%F %T", ltm);
        return (string)res;
}

void viewResultList(vector<vector<string> > resultList) {
        for(int i = 0; i < resultList.size(); i ++) {
                for(int j = 0; j < resultList[i].size(); j ++)
                        cout<<resultList[i][j]<<' ';
                cout<<endl;
        }
}
