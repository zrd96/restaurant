#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <vector>

namespace Ui {
class AdminWindow;
}

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
    void refreshList();
    void saveList();

private:
    Ui::AdminWindow *ui;
    QTableWidget* getActiveList();
    vector<bool> removeList;
};

#endif // ADMINWINDOW_H
