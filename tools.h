#ifndef _TOOSL_H
#define _TOOSL_H

#include <QString>
#include <vector>

using namespace std;

QString getTime();
QString getTimeUniform();
void viewResultList(vector<vector<QString> >);
void viewErrInfo(const QString &errInfo);
bool confirm(const QString &info);
double getTimeDifference(const QString &oriTime);
template<typename T> void clearPointerList(vector<T*>& pointerList) {
    for(unsigned int i = 0; i < pointerList.size(); i ++)
            delete pointerList[i];
        pointerList.clear();
}

#endif
