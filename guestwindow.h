#ifndef GUESTWINDOW_H
#define GUESTWINDOW_H

#include <QMainWindow>
#include <vector>

#include "dish.h"
#include "guest.h"
#include "itemlist.h"


namespace Ui {
class GuestWindow;
}

class GuestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuestWindow(QWidget *parent = 0);
    ~GuestWindow();
    void viewDishList();
    void viewCartList();

public slots:
    void openWindow(const QString user);

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_RefreshCart_clicked();

private:
    Ui::GuestWindow *ui;
    vector<Item*> dishItem;
    vector<Item*> cartItem;
    Guest guest;
    void clearPointerList(vector<Item*>& pointerList);

};

#endif // GUESTWINDOW_H
