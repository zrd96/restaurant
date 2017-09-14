#ifndef RATE_H
#define RATE_H

#include <QString>

class Rate
{
public:
    Rate(const QString &rateID, const double &rate, const QString &subject, const QString &object, const QString &datetime, const QString &title = "No title", const QString &comments = "No comments");
    QString getRateID() const {return rateID;}
    double getRate() const {return rate;}
    QString getSubject() const {return subject;}
    QString getObject() const {return object;}
    QString getDatetime() const {return datetime;}
    QString getTitle() const {return title;}
    QString getComments() const {return comments;}

private:
    QString rateID;
    double rate;
    QString subject;
    QString object;
    QString datetime;
    QString title;
    QString comments;
};

#endif // RATE_H
