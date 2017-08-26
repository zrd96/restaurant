#include "logindlg.h"
#include "ui_logindlg.h"
#include "datamanager.h"
#include "mysqlmanager.h"
#include "staticdata.h"
#include "adminwindow.h"
#include "guestwindow.h"
#include "chefwindow.h"
#include "clerkwindow.h"
#include <cstdlib>
#include <QMessageBox>
#include <QString>

LoginDlg::LoginDlg(AdminWindow *adminWindow, GuestWindow *guestWindow, ChefWindow *chefWindow, ClerkWindow *clerkWindow, QWidget *parent) :
    adminWindow(adminWindow),
    guestWindow(guestWindow),
    chefWindow(chefWindow),
    clerkWindow(clerkWindow),
    QWidget(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
    connect(this, SIGNAL(openAdminWindow(const QString)), adminWindow, SLOT(openWindow(QString)));
    connect(this, SIGNAL(openGuestWindow(const QString)), guestWindow, SLOT(openWindow(QString)));
    connect(this, SIGNAL(openChefWindow(const QString)), chefWindow, SLOT(openWindow(QString)));
    connect(this, SIGNAL(openClerkWindow(const QString)), clerkWindow, SLOT(openWindow(QString)));
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_loginButton_clicked()
{
    phone = ui->lineEditPhoneLogin->text();
    password = ui->lineEditPasswordLogin->text();
    userType = checkedIDLogin();
    //QMessageBox::information(this, tr("Info"), QString::setNum(userType));
    if(checkEnteredLogin())
        logIn(phone, userType);
        //QMessageBox::information(this, tr("Success"), tr("Success"));
}

void LoginDlg::on_signupButton_clicked()
{
    phone = ui->lineEditPhoneSignup->text();
    password = ui->lineEditPasswordSignup->text();
    name = ui->lineEditNameSignup->text();
    userType = checkedIDSignup();
    if(checkEnteredSignup())
        logIn(phone, userType);
}

bool LoginDlg::checkEnteredLogin() {
    if(phone.size() != 11) {
        QMessageBox::information(this, tr("Error"), tr("Invalid phone number"));
        return false;
    }
    else
        for(int i = 0; i < 11; i ++)
            if(phone[i] > '9' || phone[i] < '0') {
                QMessageBox::information(this, tr("Error"), tr("Invalid phone number"));
                return false;
            }
    if(password.size() == 0) {
        QMessageBox::information(this, tr("Error"), tr("Empty password"));
        return false;
    }

    StaticData::db->doQuery("person", "phone, password, type", "phone = \"" + phone.toStdString() + "\"");
    if(StaticData::db->getResultList().empty() || atoi(StaticData::db->getResultList()[0][2].c_str()) != userType && userType != 1) {
        QMessageBox::information(this, tr("Error"), tr("No such user"));
        return false;
    }

    if (QString::fromStdString(StaticData::db->getResultList()[0][1]) != password) {
        QMessageBox::information(this, tr("Error"), tr("Phone and password do not match"));
        return false;
    }

    return true;
}

bool LoginDlg::checkEnteredSignup() {
    if(phone.size() != 11) {
        QMessageBox::information(this, tr("Error"), tr("Invalid phone number"));
        return false;
    }
    else
        for(int i = 0; i < 11; i ++)
            if(phone[i] > '9' || phone[i] < '0') {
                QMessageBox::information(this, tr("Error"), tr("Invalid phone number"));
                return false;
            }
    if(password.size() == 0) {
        QMessageBox::information(this, tr("Error"), tr("Empty password"));
        return false;
    }

    if(password != ui->lineEditRepeatPasswordSignup->text()) {
        QMessageBox::information(this, tr("Error"), tr("Password not identical"));
        return false;
    }

    StaticData::db->doQuery("person", "phone, password, type", "phone = \"" + phone.toStdString() + "\"");
    if(!StaticData::db->getResultList().empty()) {
        QMessageBox::information(this, tr("Error"), tr("User exists"));
        return false;
    }

    StaticData::db->insert("person", "\"" + phone.toStdString() + "\", \"" + name.toStdString() + "\", \"" + password.toStdString() + "\", " + ntos(userType) + ", NULL, NULL");
    QMessageBox::information(this, tr("Success"), tr("Successfully signed up, now log in using new account"));
    return true;
}

int LoginDlg::checkedIDLogin() {
    if (ui->adminButton->isChecked())
        return 0;
    if (ui->guestButton->isChecked())
        return 1;
    if (ui->chefButton->isChecked())
        return 2;
    if (ui->clerkButton->isChecked())
        return 3;
    return -1;
}

int LoginDlg::checkedIDSignup() {
    if (ui->guestButtonSignup->isChecked())
        return 1;
    if (ui->chefButtonSignup->isChecked())
        return 2;
    if (ui->clerkButtonSignup->isChecked())
        return 3;
    return -1;
}

void LoginDlg::logIn(const QString user, int userType) {
    switch (userType) {
        case 0: emit openAdminWindow(user);break;
        case 1: emit openGuestWindow(user);break;
        case 2: emit openChefWindow(user); break;
        case 3: emit openClerkWindow(user);break;
    }
    this->close();
}
/*
void LoginDlg::openAdminWindow(const QString user) {
    GuestWindow guestWindow;
    guestWindow.show();
    this->close();
}

void LoginDlg::openGuestWindow(const QString user) {}

void LoginDlg::openChefWindow(const QString user) {
    emit setUser()
    //GuestWindow guestWindow;
    //guestWindow.show();
    this->close();
}

void LoginDlg::openClerkWindow(const QString user) {}
*/


