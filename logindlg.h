#ifndef LOGINDLG_H
#define LOGINDLG_H

#include "adminwindow.h"
#include "guestwindow.h"
#include "chefwindow.h"
#include "clerkwindow.h"
#include "managerwindow.h"
#include <QWidget>
#include <QString>
#include <QCloseEvent>

namespace Ui {
class LoginDlg;
}

class LoginDlg : public QWidget
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = 0);
    ~LoginDlg();

private slots:
    void on_loginButton_clicked();
    void on_signupButton_clicked();

private:
    Ui::LoginDlg *ui;
    QString phone;
    QString password;
    QString name;
    int userType;
    AdminWindow* adminWindow;
    GuestWindow* guestWindow;
    ChefWindow* chefWindow;
    ClerkWindow* clerkWindow;
    ManagerWindow* managerWindow;
    bool checkEnteredLogin();
    bool checkEnteredSignup();
    int checkedIDLogin();
    int checkedIDSignup();
    void logIn(QString user, int userType);
    void closeEvent(QCloseEvent* ev);
};

#endif // LOGINDLG_H
