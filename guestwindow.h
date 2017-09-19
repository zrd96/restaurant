#ifndef GUESTWINDOW_H
#define GUESTWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTableWidgetItem>
#include <QCloseEvent>
#include <QString>

#include "dish.h"
#include "item.h"
#include "guest.h"
#include "tableitem.h"
#include "aboutmewidget.h"
#include "logindlg.h"
#include "orderitem.h"
#include "rateitem.h"


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
    void setDishNum(const QString& dishID, int finalNum);
    void updateSum();
    void setSelectedTable(int tableID);
    void rateClerk(double newRate);

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_submitCartButton_clicked();

    void on_submitTableButton_clicked();

    void on_sendMsgButton_clicked();

    void viewDishInOrderList(Order* order);

    void on_checkOutButton_clicked();

    void on_backButton_clicked();

    void on_refreshButton_clicked();

    void on_submitButton_clicked();

    void on_logoutButton_clicked();

signals:
    //void windowClosed();
    void closeEvent(QCloseEvent* ev);

private:
    vector<TableItem*> tableItem;
    vector<Item*> dishItem;
    vector<Item*> cartItem;
    vector<OrderItem*> orderItem;
    vector<Item*> dishInOrderItem;
    int selectedTable;
    Guest guest;
    double orderedSum;
    Ui::GuestWindow *ui;
    AboutMeWidget* aboutMe;
    bool checkedOut;
    Order* currentOrder;
    RateItem* rateClerkItem;
    void sendMsg(const QString &msg);
    //void closeEvent(QCloseEvent* ev) {emit windowClosed();}
};

#endif // GUESTWINDOW_H
