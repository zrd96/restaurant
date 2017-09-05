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
    void mouseMoveEvent(QMouseEvent* ev);
    void mousePressEvent(QMouseEvent* ev);
    ~RateItem();

signals:
    void rateSet(double);

private:
    Ui::RateItem *ui;
    bool track;
};

#endif // RATEITEM_H
