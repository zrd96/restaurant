#include "tableitem.h"
#include "ui_tableitem.h"
#include "table.h"

TableItem::TableItem(const Table& table, QWidget *parent) :
    table(table),
    QWidget(parent),
    ui(new Ui::TableItem)
{
    ui->setupUi(this);

    ui->tableNum->setText("No. " + QString().setNum(table.getTableID()));
    ui->seatsInfo->setMaximum(table.getSeats());
    ui->seatsInfo->setValue(table.getFreeSeats());

//    if(table.getFreeSeats() == 0)
//        ui->selectTable->setEnabled(false);

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
