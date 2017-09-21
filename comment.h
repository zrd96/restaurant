#ifndef COMMENT_H
#define COMMENT_H

#include <QWidget>
#include <QCloseEvent>
#include "rate.h"
#include "dish.h"

namespace Ui {
class Comment;
}

class Comment : public QWidget
{
    Q_OBJECT

public:
    //view comment
    explicit Comment(const Rate &rate, QWidget *parent = 0);
    //write comment for a dish
    explicit Comment(OrderedDish &dish, QWidget *parent = 0);
    ~Comment();
signals:
    void rateSet(Rate rate);
    void closeEvent(QCloseEvent *ev);

private:
    Ui::Comment *ui;
    double rateVal;
    void setEditable(bool isEditable);

private slots:
    void setRate(double newRate) {this->rateVal = newRate;}
};

#endif // COMMENT_H
