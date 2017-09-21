#include <QString>
#include <string>
#include <ctime>
#include <vector>
#include <iostream>
#include <QMessageBox>

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

double getTimeDifference(const QString &oriTime) {
    int oriYear, oriMonth, oriDay, oriHour, oriMinute, oriSecond;
    if (oriTime.contains("-")) {
        oriYear = oriTime.mid(0, 4).toInt();
        oriMonth = oriTime.mid(5, 2).toInt();
        oriDay = oriTime.mid(8, 2).toInt();
        oriHour = oriTime.mid(11, 2).toInt();
        oriMinute = oriTime.mid(14, 2).toInt();
        oriSecond = oriTime.mid(17, 2).toInt();
    }
    else {
        oriYear = oriTime.mid(0, 4).toInt();
        oriMonth = oriTime.mid(4, 2).toInt();
        oriDay = oriTime.mid(6, 2).toInt();
        oriHour = oriTime.mid(8, 2).toInt();
        oriMinute = oriTime.mid(10, 2).toInt();
        oriSecond = oriTime.mid(12, 2).toInt();
    }
    tm oriTimeTm;
    oriTimeTm.tm_year = oriYear - 1900;
    oriTimeTm.tm_mon = oriMonth - 1;
    oriTimeTm.tm_mday = oriDay;
    oriTimeTm.tm_hour = oriHour;
    oriTimeTm.tm_min = oriMinute;
    oriTimeTm.tm_sec = oriSecond;

    return difftime(time(NULL), mktime(&oriTimeTm)) / 60;
}

void viewResultList(vector<vector<QString> > resultList) {
        for(unsigned int i = 0; i < resultList.size(); i ++) {
                for(unsigned int j = 0; j < resultList[i].size(); j ++)
                        cout<<resultList[i][j].toStdString()<<' ';
                cout<<endl;
        }
}

void viewErrInfo(const QString &errInfo) {
    QMessageBox::information(NULL, "System", errInfo);
    //cout<<errInfo.toStdString()<<endl;
}

bool confirm(const QString &info) {
    return (QMessageBox::question(NULL, "Confirm", info, QMessageBox::Yes, QMessageBox::Cancel) == QMessageBox::Yes);
}
