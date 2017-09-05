#include "rateitem.h"
#include "ui_rateitem.h"
#include "tools.h"
#include <QMouseEvent>
#include <QDebug>

RateItem::RateItem(QWidget *parent) :
    QWidget(parent),
    track(true),
    ui(new Ui::RateItem)
{
    ui->setupUi(this);
}

RateItem::~RateItem()
{
    delete ui;
}

void RateItem::mouseMoveEvent(QMouseEvent *ev) {
    viewErrInfo(ntos(ev->x()));
    if(track && ev->y() >= 0 && ev->y() <= 30 && ev->x() >= 0) {
        if(ev->x() <= 30) {
            ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
            ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
            ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
            ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        }
        else if(ev->x() <= 60) {
            ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
            ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
            ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        }
        else if(ev->x() <= 90) {
            ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
            ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        }
        else if(ev->x() <= 120) {
            ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        }
        else if(ev->x() <= 150) {
            ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
            ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        }
    }
}

void RateItem::mousePressEvent(QMouseEvent *ev) {
    if(track && ev->y() >= 0 && ev->y() <= 30 && ev->x() >= 0 && ev->x() <= 150) {
        track = false;
        emit rateSet(1.0 * ((int)(ev->x() / 30) + 1));
    }
}
