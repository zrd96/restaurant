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
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

public slots:
    void openWindow(const QString user);

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
