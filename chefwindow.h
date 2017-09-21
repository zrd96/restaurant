#ifndef CHEFWINDOW_H
#define CHEFWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "chef.h"
#include "aboutmewidget.h"

namespace Ui {
class ChefWindow;
}

class ChefWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChefWindow(const QString& user, QWidget *parent = 0);
    ~ChefWindow();

private:
    Ui::ChefWindow *ui;
    Chef chef;
    AboutMeWidget* aboutMe;

    //main functions
    void viewOrderedDishList();
    void viewTakenDishList();

signals:
    void closeEvent(QCloseEvent *ev);

private slots:
    void on_tabWidget_currentChanged(int index);
    void on_refreshButton_clicked();
    void on_saveButton_clicked();
    void on_logoutButton_clicked();
};

#endif // CHEFWINDOW_H
