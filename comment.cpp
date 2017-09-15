#include "comment.h"
#include "ui_comment.h"
#include "rate.h"
#include "rateitem.h"

Comment::Comment(const Rate &rate, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Comment)
{
    ui->setupUi(this);
    ui->commentUser->setText(QString("%1****%2").arg(rate.getSubject().mid(0, 3)).arg(rate.getSubject().mid(7, 4)));
    ui->commentTitle->setText(rate.getTitle());
    ui->commentText->setPlainText(rate.getComments());
    ui->commentTime->setText(rate.getDatetime());
    RateItem *rateItem = new RateItem(this);
    rateItem->setGeometry(120, 70, 150, 30);
    rateItem->setRate(rate.getRate());
    rateItem->show();
    this->show();
}

Comment::~Comment()
{
    delete ui;
}
