#ifndef CLERKWINDOW_H
#define CLERKWINDOW_H

#include <QMainWindow>

namespace Ui {
class ClerkWindow;
}

class ClerkWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClerkWindow(QWidget *parent = 0);
    ~ClerkWindow();

private:
    Ui::ClerkWindow *ui;
};

#endif // CLERKWINDOW_H
