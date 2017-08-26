#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QWidget>

namespace Ui {
class LoginDlg;
}

class LoginDlg : public QWidget
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = 0);
    ~LoginDlg();

private:
    Ui::LoginDlg *ui;
};

#endif // LOGINDLG_H
