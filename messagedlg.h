#ifndef MESSAGEDLG_H
#define MESSAGEDLG_H

#include <QWidget>
#include "person.h"

namespace Ui {
class MessageDlg;
}

class MessageDlg : public QWidget
{
    Q_OBJECT

public:
    explicit MessageDlg(Person &sender, const QString &receiver, QWidget *parent = 0);
    ~MessageDlg();

private:
    Ui::MessageDlg *ui;
};

#endif // MESSAGEDLG_H
