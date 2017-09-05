#ifndef GUESTWINDOW_H
#define GUESTWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTableWidgetItem>

#include "dish.h"
#include "guest.h"
#include "itemlist.h"
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
    explicit GuestWindow(const QString user, LoginDlg* loginDlg, QWidget *parent = 0);
    ~GuestWindow();
    void viewTableList();
    void viewDishList();
    void viewCartList();
    void viewOrderList();
    void viewMsgList();
    void setSelectedTable(int tableID);
    void setLoginDlg(LoginDlg* loginDlg) {this->loginDlg = loginDlg;}

public slots:
    void setDishNum(int dishID, int finalNum);
    void updateSum();

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
    template<typename T> void clearPointerList(vector<T*>& pointorList);
    Ui::GuestWindow *ui;
    AboutMeWidget* aboutMe;
    LoginDlg* loginDlg;

};

#endif // GUESTWINDOW_H
