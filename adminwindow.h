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
    void viewTableList();
    void viewDishList();
    void viewGuestList();
    //void viewStuffList();
    void viewChefList();
    void viewClerkList();
    void addItem(QTableWidget* list);
    void removeSelected(QTableWidget* list);
    void markRemoved(int listTab, int row);
    void refreshList();
    void saveList(int tabList);

signals:
    void closeEvent(QCloseEvent* ev);

private slots:
    void on_refreshButton_clicked();

    void on_dishList_cellDoubleClicked(int row, int column);

private:
    Ui::AdminWindow *ui;
    Admin admin;
    AboutMeWidget* aboutMe;
    QTableWidget* getActiveList();
    bool checkID(QTableWidget* list, int row, int col);
    bool checkNum(QString numString);
    void setRowData(QTableWidget* list, int row);
    std::vector<bool> removeList;
};

#endif // ADMINWINDOW_H
