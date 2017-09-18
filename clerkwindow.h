#ifndef CLERKWINDOW_H
#define CLERKWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "tableitem.h"
#include "table.h"
#include "clerk.h"

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
    void viewTableList();
    void viewReadyDishList();
    void viewMsgList();

private slots:
    void on_submitTableButton_clicked();
    void setSelectedTable(int tableID);

    void on_tabWidget_currentChanged(int index);

    void on_refreshMsgButton_clicked();

    void on_refreshReadyDishButton_clicked();

    void on_refreshButton_clicked();

    void on_submitButton_clicked();

    void on_logoutButton_clicked();

signals:
    void closeEvent(QCloseEvent *ev);

private:
    Ui::ClerkWindow *ui;
    Clerk clerk;
    AboutMeWidget* aboutMe;
    vector<TableItem*> tableItem;
    int selectedTable;
    void checkSelectedTables();
};

#endif // CLERKWINDOW_H
