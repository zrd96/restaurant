#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <vector>
#include <QCloseEvent>
#include "admin.h"
#include "aboutmewidget.h"

namespace Ui {
class AdminWindow;
}

class AboutMeWidget;

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(const QString& user, QWidget *parent = 0);
    ~AdminWindow();

signals:
    void closeEvent(QCloseEvent* ev);

private slots:
    void on_refreshButton_clicked();
    void on_dishList_cellDoubleClicked(int row, int column);
    void on_tabWidget_currentChanged(int index);
    void on_logoutButton_clicked();

private:
    Ui::AdminWindow *ui;
    Admin admin;
    AboutMeWidget* aboutMe;

    //main functions of Admin
    void viewTableList();
    void viewDishList();
    void viewGuestList();
    void viewChefList();
    void viewClerkList();
    void viewManagerList();
    void addItem(QTableWidget* list);
    void removeSelected(QTableWidget* list);
    void saveList(int tabList);

    //some tool functions
    void markRemoved(int listTab, int row);
    void refreshList();
    QTableWidget* getActiveList();
    bool checkID(QTableWidget* list, int row, int col);
    bool checkNum(const QString& numString);
    void setRowData(QTableWidget* list, int row);
};

#endif // ADMINWINDOW_H
