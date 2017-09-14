#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QWidget>
#include "table.h"
#include "guest.h"
#include "guestwindow.h"

namespace Ui {
class TableItem;
}

class GuestWindow;

class TableItem : public QWidget
{
    Q_OBJECT

public:
    explicit TableItem(const Table& table, QWidget *parent = 0);
    ~TableItem();

private slots:
    void on_selectTable_clicked();

signals:
    void tableSelected(int);

private:
    Ui::TableItem *ui;
    Table table;
};

#endif // TABLEITEM_H
