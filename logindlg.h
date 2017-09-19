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

class AdminWindow;
class GuestWindow;
class ChefWindow;
class ClerkWindow;
class ManagerWindow;

class LoginDlg : public QWidget
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = 0);
    ~LoginDlg();

private slots:

    void on_loginButton_clicked();

    void on_signupButton_clicked();

signals:
    void openAdminWindow(const QString user);
    void openGuestWindow(const QString user);
    void openChefWindow(const QString user);
    void openClerkWindow(const QString user);

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
