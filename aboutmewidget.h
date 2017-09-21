#ifndef ABOUTMEWIDGET_H
#define ABOUTMEWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include "person.h"

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
    void refresh();
    void submit();
    void logout();

private slots:
    void on_nameEdit_textChanged(const QString &newName);
    void on_phoneEdit_textChanged(const QString &newPhone);
    void on_newPassword_textChanged(const QString &newPassword);
    void on_currentPassword_textChanged(const QString &curPassword);

private:
    Ui::AboutMeWidget *ui;
    Person* person;
    QMainWindow* mainWindow;
};

#endif // ABOUTMEWIDGET_H
