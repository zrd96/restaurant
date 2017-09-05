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
//    connect(this, SIGNAL(openAdminWindow(const QString)), adminWindow, SLOT(openWindow(QString)));
//    connect(this, SIGNAL(openGuestWindow(const QString)), guestWindow, SLOT(openWindow(QString)));
//    connect(this, SIGNAL(openChefWindow(const QString)), chefWindow, SLOT(openWindow(QString)));
//    connect(this, SIGNAL(openClerkWindow(const QString)), clerkWindow, SLOT(openWindow(QString)));
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
    if(StaticData::db->getResultList().empty() || (atoi(StaticData::db->getResultList()[0][2].c_str()) != userType && userType != 1)) {
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
    if(password.size() < 6) {
        QMessageBox::information(this, tr("Error"), tr("Password must be longer than 6 digits"));
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

    StaticData::db->insert("person", "\"" + phone.toStdString() + "\", \"" + name.toStdString() + "\", \"" + password.toStdString() + "\", " + ntos(userType) + ", NULL, NULL, NULL");
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
            adminWindow = new AdminWindow();
            adminWindow->show();
            break;
        case 1:
            guestWindow = new GuestWindow(user, this);
            guestWindow->show();
            break;
        case 2:
            chefWindow = new ChefWindow();
            chefWindow->show();
            break;
        case 3:
            clerkWindow = new ClerkWindow();
            clerkWindow->show();
            break;
    }
    this->hide();
}

void LoginDlg::closeEvent(QCloseEvent *ev) {
    viewErrInfo("*****");
    for(unsigned int i = 0; i < StaticData::tableList.size(); i ++) {
        Table& cur = StaticData::tableList[i];
        if(StaticData::db->doesExist("tableList", "id = " + ntos(cur.getTableID()))) {
            StaticData::db->update("tableList", "seats", ntos(cur.getSeats()), "id = " + ntos(cur.getTableID()));
            StaticData::db->update("tableList", "freeSeats", ntos(cur.getFreeSeats()), "id = " + ntos(cur.getTableID()));
            StaticData::db->update("tableList", "clerk",
                                   "\"" + (cur.getClerk() != "" ? cur.getClerk() : (string)"NULL") + "\"",
                                   "id = " + ntos(cur.getTableID()));
        }
        else {
            StaticData::db->insert("tableList",
                                   ntos(cur.getTableID()) + ", "
                                   + ntos(cur.getSeats()) + ", "
                                   + ntos(cur.getFreeSeats()) + ", \""
                                   + cur.getClerk() + "\"");
        }
    }

    for(unsigned int i = 0; i < StaticData::dishList.size(); i ++) {
        Dish& cur = StaticData::dishList[i];
        if(StaticData::db->doesExist("dish", "dishID = " + ntos(cur.getDishID()))) {
            StaticData::db->update("dish", "name", "\"" + cur.getName() + "\"", "dishID = " + ntos(cur.getDishID()));
            StaticData::db->update("dish", "price", ntos(cur.getPrice()), "dishID = " + ntos(cur.getDishID()));
            StaticData::db->update("dish", "rate", ntos(cur.getRate()), "dishID = " + ntos(cur.getDishID()));
            StaticData::db->update("dish", "rateNum", ntos(cur.getRateNum()), "dishID = " + ntos(cur.getDishID()));
            StaticData::db->update("dish", "time", ntos(cur.getTimeNeeded()), "dishID = " + ntos(cur.getDishID()));
            StaticData::db->update("dish", "imgdir", "\"" + cur.getImgDir() + "\"", "dishID = " + ntos(cur.getDishID()));
        }
        else {
            StaticData::db->insert("dish",
                                   "NULL, \"" + cur.getName() + "\", "
                                   + ntos(cur.getPrice()) + ", "
                                   + ntos(cur.getRate()) + ", " + ntos(cur.getRateNum()) + ", "
                                   + "\"" + cur.getImgDir() + "\"");
        }
    }

    for(unsigned int i = 0; i < StaticData::orderedDishList.size(); i ++) {
        OrderedDish& cur = StaticData::orderedDishList[i];
        if(StaticData::db->doesExist("orderedDish",
                                     "id = "
                                     + ntos(cur.getOrderedDishID()))) {
            StaticData::db->update("orderedDish",
                                   "orderer", "\"" + cur.getOrderer() + "\"",
                                   "id = " + ntos(cur.getOrderedDishID()));
            StaticData::db->update("orderedDish",
                                   "tableNum", ntos(cur.getTable()),
                                   "id = " + ntos(cur.getOrderedDishID()));
            StaticData::db->update("orderedDish",
                                   "status", ntos(cur.getStatus()),
                                   "id = " + ntos(cur.getOrderedDishID()));
            StaticData::db->update("orderedDish",
                                   "datetime", "\"" + cur.getDatetime() + "\"",
                                   "id = " + ntos(cur.getOrderedDishID()));
        }
        else {
            StaticData::db->insert("orderedDish",
                                   "NULL, "
                                   + ntos(cur.getDishID()) + ", \""
                                   + cur.getOrderer() + "\", "
                                   + ntos(cur.getTable()) + ", "
                                   + ntos(cur.getStatus()) + ", \""
                                   + cur.getDatetime() + "\"");
        }
    }

    for(unsigned int i = 0; i < StaticData::msgList.size(); i ++) {
        Msg& cur = StaticData::msgList[i];
        if(StaticData::db->doesExist("msg", "msgid = " + ntos(cur.getMsgID()))) {
            StaticData::db->update("msg", "isActive", ntos(cur.getState()), "msgid = " + ntos(cur.getMsgID()));
        }
        else {
            StaticData::db->insert("msg",
                                   "NULL, \"" + cur.getSender() + "\", \""
                                   + cur.getReceiver() + "\", \""
                                   + cur.getMsg() + "\", \""
                                   + cur.getDatetime() + "\", "
                                   + ntos(cur.getState()));
        }
    }
}
