#include "comment.h"
#include "ui_comment.h"
#include "rate.h"
#include "rateitem.h"
#include "dish.h"
#include "tools.h"
#include "staticdata.h"
#include <QPushButton>

Comment::Comment(const Rate &rate, QWidget *parent) :
    QWidget(parent),
    rateVal(-1),
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
    setEditable(false);
    rateItem->show();
    this->show();
}

Comment::Comment(OrderedDish &dish, QWidget *parent) :
    QWidget(parent),
    rateVal(-1),
    ui(new Ui::Comment)
{
    ui->setupUi(this);
    ui->commentUser->setText(dish.getOrderer());
    ui->commentTitle->setPlaceholderText("Title here");
    ui->commentText->setPlaceholderText("Your comment here");
    ui->commentTime->setText("");
    RateItem *rateItem = new RateItem(this);
    rateItem->setGeometry(120, 70, 150, 30);
    connect(rateItem, SIGNAL(rateSet(double)), this, SLOT(setRate(double)));
    setEditable(true);
    this->resize(460, 280);
    QPushButton *submit = new QPushButton(this);
    submit->setGeometry(205, 230, 50, 40);
    submit->setText("Submit");
    connect(submit, &QPushButton::clicked, this, [&, this] {
        if (rateVal < 0) {
            viewErrInfo("Please set a rate");
            return;
        }
        dish.updateRate(Rate("R" + getTimeUniform() + dish.getOrderer() + dish.getDishID(),
                    rateVal,
                    dish.getOrderer(),
                    dish.getDishID(),
                    getTime(),
                    ui->commentTitle->text(),
                    ui->commentText->toPlainText()));
        dish.setStatus(6);
        StaticData::modifyOrderedDish(dish.getOrderedDishID(), dish);
        viewErrInfo("Success");
        this->close();
    });
    this->show();
}

void Comment::setEditable(bool isEditable) {
    ui->commentTitle->setReadOnly(!isEditable);
    ui->commentText->setReadOnly(!isEditable);
    ui->label->setCursor(QCursor(Qt::ArrowCursor));
    ui->commentText->setCursor(QCursor(Qt::ArrowCursor));
    ui->commentUser->setCursor(QCursor(Qt::ArrowCursor));
    ui->commentTitle->setCursor(QCursor(Qt::ArrowCursor));
    ui->commentText->setCursor(QCursor(Qt::ArrowCursor));
    if (isEditable) {
        ui->commentTitle->setCursor(QCursor(Qt::IBeamCursor));
        ui->commentText->setCursor(QCursor(Qt::IBeamCursor));
    }
}

Comment::~Comment()
{
    delete ui;
}
