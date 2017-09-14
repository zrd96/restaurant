#include "rate.h"
#include <QString>

Rate::Rate(const QString &rateID, const double &rate, const QString &subject, const QString &object, const QString &datetime, const QString &title, const QString &comments):
    rateID(rateID),
    rate(rate),
    subject(subject),
    object(object),
    datetime(datetime),
    title(title),
    comments(comments) {}
