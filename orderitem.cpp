#include "orderitem.h"
#include "ui_orderitem.h"
#include "order.h"
#include <vector>

OrderItem::OrderItem(Order* order, QWidget *parent) :
    order(order),
    QWidget(parent),
    ui(new Ui::OrderItem)
{
    ui->setupUi(this);
    ui->orderID->setText(order->getOrderID());
    ui->orderInfo->setPlainText(QString("Order Info\n"
                                        "Order time: %1\n"
                                        "Orderer: %2\n"
                                        "Total dishes: %3\n"
                                        "Sum: %4")
                                .arg(order->getDatetime())
                                .arg(order->getOrderer())
                                .arg(order->getOrderDishes().size())
                                .arg(order->getOrderSum()));
    if(order->checkStatus() >= 5) {
        ui->isFinishedIcon->setPixmap(QPixmap(QString::fromUtf8("img/finished.png")));
        ui->isFinishedIcon->setScaledContents(true);
        ui->isFinished->setText("Finished");
    }
    else {
        ui->isFinishedIcon->setPixmap(QPixmap(QString::fromUtf8("img/active.png")));
        ui->isFinishedIcon->setScaledContents(true);
        ui->isFinished->setText("Active");
    }
    show();
}

OrderItem::~OrderItem()
{
    delete ui;
}

void OrderItem::on_pushButton_clicked()
{
    emit orderClicked(order);
}
