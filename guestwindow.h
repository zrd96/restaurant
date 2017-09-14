#ifndef GUESTWINDOW_H
#define GUESTWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTableWidgetItem>
#include <QCloseEvent>

#include "dish.h"
#include "item.h"
#include "guest.h"
#include "tableitem.h"
#include "aboutmewidget.h"
#include "logindlg.h"
#include "orderitem.h"


namespace Ui {
class GuestWindow;
}

class TableItem;
class LoginDlg;
class AboutMeWidget;

class GuestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuestWindow(const QString& user, QWidget *parent = 0);
    ~GuestWindow();
    void viewTableList();
    void viewDishList();
    void viewCartList();
    void viewOrderList();
    void viewMsgList();

public slots:
    void setDishNum(const string& dishID, int finalNum);
    void updateSum();
    void setSelectedTable(int tableID);

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_RefreshCart_clicked();

    void on_submitButton_clicked();

    void on_submitTableButton_clicked();

    void on_refreshTableButton_clicked();

    void on_sendMsgButton_clicked();

    void on_refreshMsg_clicked();

    void viewDishInOrderList(Order* order);

    void on_viewOrderButton_clicked();

    void on_refreshOrderInfoButton_clicked();

    void on_checkOutButton_clicked();

    void on_refreshDishListButton_clicked();

signals:
    //void windowClosed();
    void closeEvent(QCloseEvent* ev);

private:
    vector<TableItem*> tableItem;
    vector<Item*> dishItem;
    vector<Item*> cartItem;
    //vector<Item*> orderItem;
    vector<OrderItem*> orderItem;
    vector<Item*> dishInOrderItem;
    vector<QTableWidgetItem*> msgItem;
    int selectedTable;
    Guest guest;
    double orderedSum, submittedSum;
    Ui::GuestWindow *ui;
    AboutMeWidget* aboutMe;
    bool checkedOut;
    Order* currentOrder;
    //void closeEvent(QCloseEvent* ev) {emit windowClosed();}
};

#endif // GUESTWINDOW_H
