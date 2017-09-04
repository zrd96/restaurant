#ifndef ABOUTMEWIDGET_H
#define ABOUTMEWIDGET_H

#include <QWidget>
#include "person.h"

namespace Ui {
class AboutMeWidget;
}

class AboutMeWidget : public QWidget
{
    Q_OBJECT

public:
    AboutMeWidget(Person* person, QWidget *parent = 0);
    ~AboutMeWidget();

private slots:
    void on_refreshInfoButton_clicked();

    void on_submitInfoButton_clicked();

    void on_nameEdit_textChanged(const QString &newName);

    void on_phoneEdit_textChanged(const QString &newPhone);

    void on_newPassword_textChanged(const QString &newPassword);

    void on_currentPassword_textChanged(const QString &curPassword);

private:
    Ui::AboutMeWidget *ui;
    void dealWithRateInfo();
    Person* person;
};

#endif // ABOUTMEWIDGET_H
