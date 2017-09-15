#include "aboutmewidget.h"
#include "ui_aboutmewidget.h"
#include "person.h"
#include "clerk.h"
#include "tools.h"
#include "staticdata.h"
#include "rateitem.h"
#include <QMessageBox>

AboutMeWidget::AboutMeWidget(Person* person, QMainWindow* mainWindow, QWidget *parent) :
    QWidget(parent),
    person(person),
    mainWindow(mainWindow),
    ui(new Ui::AboutMeWidget)
{
    ui->setupUi(this);
    ui->nameEdit->setText((person->getName()));
    ui->phoneEdit->setText((person->getPhone()));
    dealWithRateInfo();
    ui->nameEdit->setEnabled(false);
    ui->phoneEdit->setEnabled(false);
    ui->newPassword->setEnabled(false);
    ui->repeatNewPassword->setEnabled(false);
    ui->submitInfoButton->setEnabled(false);
}

AboutMeWidget::~AboutMeWidget()
{
    delete ui;
}

void AboutMeWidget::dealWithRateInfo() {
    Clerk* clerk = dynamic_cast<Clerk*> (person);
    if(clerk == NULL) {
        ui->rateLabel->setVisible(false);
        ui->rateInfo->setVisible(false);
        //ui->rateProgressBar->setVisible(false);
        return;
    }
    RateItem* rate = new RateItem(this);
    rate->setGeometry(590, 510, 150, 30);
    rate->setRate(clerk->getRate());
    rate->show();
    ui->rateInfo->setText(QString("Rate %1/5 from %2 people").arg(clerk->getRate()).arg(clerk->getRateNum()));
}

void AboutMeWidget::on_refreshInfoButton_clicked()
{
    ui->nameEdit->setText((person->getName()));
    ui->phoneEdit->setText((person->getPhone()));
    dealWithRateInfo();
}

void AboutMeWidget::on_submitInfoButton_clicked()
{
    QString newName = ui->nameEdit->text();
    QString newPhone = ui->phoneEdit->text();
    QString newPassword = person->getPassword();
    if(ui->currentPassword->text() != person->getPassword()) {
        viewErrInfo("Password Incorrect");
        return;
    }
    if(ui->newPassword->text().length() > 0) {
        if(ui->newPassword->text().length() < 6) {
            viewErrInfo("Password must be longer than 6 digits");
            return;
        }
        if(ui->newPassword->text() != ui->repeatNewPassword->text()) {
            viewErrInfo("Password not identical");
            return;
        }
        newPassword = ui->newPassword->text();
    }
    if(newPhone != person->getPhone()) {
        StaticData::db->doQuery("person", "phone", "phone = \"" + newPhone + "\"");
        if(!StaticData::db->getResultList().empty()) {
            viewErrInfo("Phone already regesitered");
            return;
        }
    }
    if(StaticData::db->update("person", "phone", "\"" + newPhone + "\"", "phone = \"" + person->getPhone() + "\"")
            && newPhone != person->getPhone()) {
        StaticData::updateEverythingAboutUser(person, newPhone);
    }
    StaticData::db->update("person", "name", "\"" + newName + "\"", "phone = \"" + newPhone + "\"");
    StaticData::db->update("person", "password", "\"" + newPassword + "\"", "phone = \"" + newPhone + "\"");
    person->setName(newName);
    //person->setPhone(newPhone);
    person->setPassword(newPassword);
    viewErrInfo("Succeeded");
}

void AboutMeWidget::on_newPassword_textChanged(const QString &newPassword)
{
    if(newPassword.length() >= 6)
        ui->submitInfoButton->setEnabled(true);
}

void AboutMeWidget::on_currentPassword_textChanged(const QString &curPassword)
{
    if(curPassword.length() >= 6) {
        ui->nameEdit->setEnabled(true);
        ui->phoneEdit->setEnabled(true);
        ui->newPassword->setEnabled(true);
        ui->repeatNewPassword->setEnabled(true);
    }
}

void AboutMeWidget::on_nameEdit_textChanged(const QString &newName)
{
    if(newName != person->getName())
        ui->submitInfoButton->setEnabled(true);
}

void AboutMeWidget::on_phoneEdit_textChanged(const QString &newPhone)
{
    if(newPhone != person->getPhone())
        ui->submitInfoButton->setEnabled(true);
}

void AboutMeWidget::on_logoutButton_clicked()
{
    int reply = QMessageBox::question(NULL, "Log Out", "Your unsubmitted contents will not be saved, log out?", QMessageBox::Yes, QMessageBox::No);
    if(reply != QMessageBox::Yes)
        return;
    mainWindow->close();
}
