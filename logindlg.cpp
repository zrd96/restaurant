#include "logindlg.h"
#include "ui_logindlg.h"
#include "datamanager.h"
#include "mysqlmanager.h"
#include "staticdata.h"
#include "adminwindow.h"
#include "guestwindow.h"
#include "chefwindow.h"
#include "clerkwindow.h"
#include "table.h"
#include "msg.h"
#include "dish.h"
#include "tools.h"
#include <cstdlib>
#include <QMessageBox>
#include <QString>
#include <QCloseEvent>

LoginDlg::LoginDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
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

    StaticData::db->doQuery("person", "phone, password, type", "phone = \"" + phone + "\"");
    if(StaticData::db->getResultList().empty() || (StaticData::db->getResultList()[0][2].toInt() != userType && userType != 1)) {
        QMessageBox::information(this, tr("Error"), tr("No such user"));
        return false;
    }

    if ((StaticData::db->getResultList()[0][1]) != password) {
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
    if(password.size() < 6) {
        QMessageBox::information(this, tr("Error"), tr("Password must be longer than 6 digits"));
        return false;
    }

    if(password != ui->lineEditRepeatPasswordSignup->text()) {
        QMessageBox::information(this, tr("Error"), tr("Password not identical"));
        return false;
    }

    StaticData::db->doQuery("person", "phone, password, type", "phone = \"" + phone + "\"");
    if(!StaticData::db->getResultList().empty()) {
        QMessageBox::information(this, tr("Error"), tr("User exists"));
        return false;
    }

    StaticData::db->insert("person", QString("\"%1\", \"%2\", \"%3\", %4, NULL, NULL, NULL").arg(phone).arg(name).arg(password).arg(userType));
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
        case 0:
            adminWindow = new AdminWindow(user, this);
            connect(adminWindow, SIGNAL(closeEvent(QCloseEvent*)), this, SLOT(show()));
            adminWindow->show();
            break;
        case 1:
            guestWindow = new GuestWindow(user, this);
            connect(guestWindow, SIGNAL(closeEvent(QCloseEvent*)), this, SLOT(show()));
            guestWindow->show();
            break;
        case 2:
            chefWindow = new ChefWindow(user, this);
            connect(chefWindow, SIGNAL(closeEvent(QCloseEvent*)), this, SLOT(show()));
            chefWindow->show();
            break;
        case 3:
            clerkWindow = new ClerkWindow(user, this);
            connect(clerkWindow, SIGNAL(closeEvent(QCloseEvent*)), this, SLOT(show()));
            clerkWindow->show();
            break;
    }
    this->hide();
}

void LoginDlg::closeEvent(QCloseEvent *ev) {
    StaticData::writeTable();
    StaticData::writeDish();
    StaticData::writeOrderedDish();
    StaticData::writeMsg();
    StaticData::writeGuest();
    StaticData::writeChef();
    StaticData::writeClerk();
    StaticData::writeOrder();
    StaticData::writeRate();
}
