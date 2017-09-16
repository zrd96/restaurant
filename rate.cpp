#include "rate.h"
#include <QString>

Rate::Rate(const QString &rateID, const double &rate, const QString &subject, const QString &object, const QString &datetime, const QString &title, const QString &comments):
    rateID(rateID),
    rate(rate),
    subject(subject),
    object(object),
    datetime(datetime),
    title(title),
    comments(comments) {
    if (title.length() == 0)
        this->title = "No title";
    if (comments.length() == 0)
        this->comments = "No comments";
}
