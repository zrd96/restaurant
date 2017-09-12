#ifndef CHEFWINDOW_H
#define CHEFWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <vector>
#include "chef.h"
#include "item.h"
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
    void viewOrderedDishList();
    void viewTakenDishList();

public slots:
    void openWindow(const QString user);

private:
    Ui::ChefWindow *ui;
    Chef chef;
    vector<Item*> orderedDishItem;
    vector<Item*> takenDishItem;
    AboutMeWidget* aboutMe;
signals:
    void closeEvent(QCloseEvent *ev);
private slots:
    void on_tabWidget_currentChanged(int index);
};

#endif // CHEFWINDOW_H
