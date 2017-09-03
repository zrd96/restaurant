#ifndef GUESTWINDOW_H
#define GUESTWINDOW_H

#include <QMainWindow>
#include <vector>

#include "dish.h"
#include "guest.h"
#include "itemlist.h"
#include "tableitem.h"


namespace Ui {
class GuestWindow;
}

class TableItem;

class GuestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuestWindow(QWidget *parent = 0);
    ~GuestWindow();
    void viewTableList();
    void viewDishList();
    void viewCartList();
    void viewOrderList();
    void setSelectedTable(int tableID);

public slots:
    void openWindow(const QString user);
    void setDishNum(int dishID, int finalNum);
    void updateSum();

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_RefreshCart_clicked();

    void on_submitButton_clicked();

    void on_submitTableButton_clicked();

    void on_refreshTableButton_clicked();

private:
    vector<TableItem*> tableItem;
    vector<Item*> dishItem;
    vector<Item*> cartItem;
    vector<Item*> orderItem;
    int selectedTable;
    Guest guest;
    double orderedSum, submittedSum;
    void clearPointerList(vector<Item*>& pointerList);
    void clearPointerList(vector<TableItem*>& pointerList);
    Ui::GuestWindow *ui;

};

#endif // GUESTWINDOW_H
