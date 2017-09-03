#include "tableitem.h"
#include "ui_tableitem.h"
#include "table.h"
#include "guestwindow.h"

TableItem::TableItem(Guest& guest, const Table& table, GuestWindow* guestWindow, QWidget *parent) :
    guest(&guest),
    table(table),
    guestWindow(guestWindow),
    QWidget(parent),
    ui(new Ui::TableItem)
{
    ui->setupUi(this);

    ui->tableNum->setText("No. " + QString().setNum(table.getTableID()));
    ui->seatsInfo->setMaximum(table.getSeats());
    ui->seatsInfo->setValue(table.getFreeSeats());

    if(table.getFreeSeats() == 0)
        ui->selectTable->setEnabled(false);

    this->show();
}

TableItem::~TableItem()
{
    delete ui;
}

void TableItem::on_selectTable_clicked()
{

    guestWindow->setSelectedTable(table.getTableID());
}
