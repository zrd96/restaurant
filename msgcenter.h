#ifndef MSGCENTER_H
#define MSGCENTER_H

#include <QWidget>

namespace Ui {
class MsgCenter;
}

class MsgCenter : public QWidget
{
    Q_OBJECT

public:
    explicit MsgCenter(QWidget *parent = 0);
    ~MsgCenter();

private:
    Ui::MsgCenter *ui;
};

#endif // MSGCENTER_H
