#include "rateitem.h"
#include "ui_rateitem.h"
#include "tools.h"
#include <QMouseEvent>
#include <QDebug>

RateItem::RateItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RateItem),
    track(true)
{
    ui->setupUi(this);
}

RateItem::~RateItem()
{
    delete ui;
}

void RateItem::mouseMoveEvent(QMouseEvent *ev) {
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

void RateItem::leaveEvent(QEvent *ev) {
    if (track) {
        ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
    }
}

void RateItem::mousePressEvent(QMouseEvent *ev) {
    if(track && ev->y() >= 0 && ev->y() <= 30 && ev->x() >= 0 && ev->x() <= 150) {
        track = false;
        this->setCursor(QCursor(Qt::ArrowCursor));
        ui->star1->setCursor(QCursor(Qt::ArrowCursor));
        ui->star2->setCursor(QCursor(Qt::ArrowCursor));
        ui->star3->setCursor(QCursor(Qt::ArrowCursor));
        ui->star4->setCursor(QCursor(Qt::ArrowCursor));
        ui->star5->setCursor(QCursor(Qt::ArrowCursor));
        emit rateSet(1.0 * ((int)(ev->x() / 30) + 1));
    }
}

void RateItem::setRate(double rate) {
    track = false;
    this->setCursor(QCursor(Qt::ArrowCursor));
    ui->star1->setCursor(QCursor(Qt::ArrowCursor));
    ui->star2->setCursor(QCursor(Qt::ArrowCursor));
    ui->star3->setCursor(QCursor(Qt::ArrowCursor));
    ui->star4->setCursor(QCursor(Qt::ArrowCursor));
    ui->star5->setCursor(QCursor(Qt::ArrowCursor));
    if(rate < 0.1) {
        ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
    }
    else if(rate < 0.9) {
        ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-half.png")));
        ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
    }
    else if (rate < 1.1) {
        ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
    }
    else if (rate < 1.9) {
        ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star-half.png")));
        ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
    }
    else if (rate < 2.1) {
        ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
    }
    else if (rate < 2.9) {
        ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star-half.png")));
        ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
    }
    else if (rate < 3.1) {
        ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
        ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
    }
    else if (rate < 3.9) {
        ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star-half.png")));
        ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
    }
    else if (rate < 4.1) {
        ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star.png")));
    }
    else if (rate < 4.9) {
        ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star-half.png")));
    }
    else if (rate <= 5.0) {
        ui->star1->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star2->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star3->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star4->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
        ui->star5->setPixmap(QPixmap(QString::fromUtf8("img/star-filled.png")));
    }
}
