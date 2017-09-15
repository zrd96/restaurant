#ifndef EMPTYRESULT_H
#define EMPTYRESULT_H

#include <QString>

class EmptyResult
{
public:
    EmptyResult(const QString &errInfo);
    QString getErrInfo() const {return errInfo;}
private:
    QString errInfo;
};

#endif // EMPTYRESULT_H
