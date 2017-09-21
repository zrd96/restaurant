#ifndef RATEITEM_H
#define RATEITEM_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class RateItem;
}

class RateItem : public QWidget
{
    Q_OBJECT

public:
    explicit RateItem(QWidget *parent = 0);
    void setRate(double rate);
    ~RateItem();

signals:
    void rateSet(double);

private:
    Ui::RateItem *ui;
    bool track;
    void mouseMoveEvent(QMouseEvent* ev);
    void mousePressEvent(QMouseEvent* ev);
    void leaveEvent(QEvent *ev);
};

#endif // RATEITEM_H
