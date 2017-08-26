#ifndef CHEFWINDOW_H
#define CHEFWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChefWindow;
}

class ChefWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChefWindow(QWidget *parent = 0);
    ~ChefWindow();

private:
    Ui::ChefWindow *ui;
};

#endif // CHEFWINDOW_H
