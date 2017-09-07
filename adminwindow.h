#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>

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

public slots:
    void openWindow(const QString user);

private slots:
    void on_refreshButtonTable_clicked();

    void on_restoreButtonTable_clicked();

    void on_addButtonTable_clicked();

    void on_removeButtonDish_clicked();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
