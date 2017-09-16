#ifndef COMMENT_H
#define COMMENT_H

#include <QWidget>
#include "rate.h"
#include "dish.h"

namespace Ui {
class Comment;
}

class Comment : public QWidget
{
    Q_OBJECT

public:
    explicit Comment(const Rate &rate, QWidget *parent = 0);
    explicit Comment(OrderedDish &dish, QWidget *parent = 0);
    ~Comment();
signals:
    void rateSet(Rate rate);

private:
    Ui::Comment *ui;
    void setEditable(bool isEditable);
    double rateVal;

private slots:
    void setRate(double newRate) {this->rateVal = newRate;}
};

#endif // COMMENT_H
