#include "msgcenter.h"
#include "ui_msgcenter.h"

MsgCenter::MsgCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgCenter)
{
    ui->setupUi(this);
}

MsgCenter::~MsgCenter()
{
    delete ui;
}
