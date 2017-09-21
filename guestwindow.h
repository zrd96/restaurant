#ifndef GUESTWINDOW_H
#define GUESTWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTableWidgetItem>
#include <QCloseEvent>
#include <QString>

#include "dish.h"
#include "guest.h"
#include "order.h"
#include "aboutmewidget.h"
#include "rateitem.h"
#include "item.h"


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

public slots:

private slots:
    void submitCart();
    void submitTable();
    void viewDishInOrderList(Order* order);
    void setDishNum(const QString& dishID, int finalNum);
    void updateSum();
    void setSelectedTable(int tableID);
    void rateClerk(double newRate);

    void on_tabWidget_currentChanged(int index);
    void on_sendMsgButton_clicked();
    void on_checkOutButton_clicked();
    void on_backButton_clicked();
    void on_refreshButton_clicked();
    void on_submitButton_clicked();
    void on_logoutButton_clicked();

signals:
    //void windowClosed();
    void closeEvent(QCloseEvent* ev);

private:
    Ui::GuestWindow *ui;
    int selectedTable;
    Guest guest;
    double orderedSum;
    AboutMeWidget* aboutMe;
    bool checkedOut;
    Order* currentOrder;
    RateItem* rateClerkItem;
    vector<Item*> dishItem;
    void sendMsg(const QString &msg);
    void viewTableList();
    void viewDishList();
    void viewCartList();
    void viewOrderList();
    void viewMsgList();
};

#endif // GUESTWINDOW_H
