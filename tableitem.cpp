#include "tableitem.h"
#include "ui_tableitem.h"
#include "table.h"

TableItem::TableItem(const Table& table, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableItem),
    table(table)
{
    ui->setupUi(this);

    ui->tableNum->setText("No. " + QString().setNum(table.getTableID()));
    ui->seatsInfo->setMaximum(table.getSeats());
    ui->seatsInfo->setValue(table.getFreeSeats());

    this->show();
}

TableItem::~TableItem()
{
    delete ui;
}

void TableItem::on_selectTable_clicked()
{
    emit tableSelected(table.getTableID());
}
