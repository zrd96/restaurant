#ifndef CLERKWINDOW_H
#define CLERKWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "clerk.h"
#include "aboutmewidget.h"

namespace Ui {
class ClerkWindow;
}

class TableItem;

class ClerkWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClerkWindow(const QString &user, QWidget *parent = 0);
    ~ClerkWindow();

private slots:
    void setSelectedTable(int tableID);
    void on_tabWidget_currentChanged(int index);
    void on_refreshButton_clicked();
    void on_submitButton_clicked();
    void on_logoutButton_clicked();

signals:
    void closeEvent(QCloseEvent *ev);

private:
    Ui::ClerkWindow *ui;
    Clerk clerk;
    AboutMeWidget* aboutMe;
    int selectedTable;

    //main functions
    void viewTableList();
    void viewReadyDishList();
    void viewMsgList();

    //tools
    void checkSelectedTables();
    void submitTable();
};

#endif // CLERKWINDOW_H
