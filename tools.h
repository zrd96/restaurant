#ifndef _TOOSL_H
#define _TOOSL_H

#include <string>
#include <vector>

using namespace std;

string ntos(int i);
string ntos(double f);
string getTime();
string getTimeUniform();
void viewResultList(vector<vector<string> >);
void viewErrInfo(string errInfo);
bool confirm(string info);
template<typename T> void clearPointerList(vector<T*>& pointerList) {
    for(unsigned int i = 0; i < pointerList.size(); i ++)
            delete pointerList[i];
        pointerList.clear();
}

#endif
