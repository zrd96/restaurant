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
    if(order->isFinished()) {
        ui->isFinishedIcon->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->isFinishedIcon->setScaledContents(true);
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
