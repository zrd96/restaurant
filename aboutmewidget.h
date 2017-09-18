#ifndef ABOUTMEWIDGET_H
#define ABOUTMEWIDGET_H

#include <QWidget>
#include "person.h"
#include "logindlg.h"

namespace Ui {
class AboutMeWidget;
}

class LoginDlg;

class AboutMeWidget : public QWidget
{
    Q_OBJECT

public:
    AboutMeWidget(Person* person, QMainWindow* mainWindow, QWidget *parent = 0);
    ~AboutMeWidget();

public slots:
    void on_refreshInfoButton_clicked();

    void on_submitInfoButton_clicked();

    void on_nameEdit_textChanged(const QString &newName);

    void on_phoneEdit_textChanged(const QString &newPhone);

    void on_newPassword_textChanged(const QString &newPassword);

    void on_currentPassword_textChanged(const QString &curPassword);

    void on_logoutButton_clicked();

private:
    Ui::AboutMeWidget *ui;
    void dealWithRateInfo();
    Person* person;
    QMainWindow* mainWindow;
};

#endif // ABOUTMEWIDGET_H
