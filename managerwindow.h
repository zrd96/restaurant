#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "manager.h"
#include "chef.h"
#include "clerk.h"
#include "staticdata.h"
#include "aboutmewidget.h"

namespace Ui {
class ManagerWindow;
}

class ManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerWindow(const QString &user, QWidget *parent = 0);
    ~ManagerWindow();

private slots:
    void on_chefList_cellDoubleClicked(int row, int column);

    void on_clerkList_cellDoubleClicked(int row, int column);

signals:
    void closeEvent(QCloseEvent *ev);

private:
    Ui::ManagerWindow *ui;
    AboutMeWidget *aboutMe;
    Manager manager;
    void viewChefList();
    void viewClerkList();
};

#endif // MANAGERWINDOW_H
