#include "messagedlg.h"
#include "ui_messagedlg.h"
#include "tools.h"
#include "person.h"
#include "staticdata.h"

MessageDlg::MessageDlg(Person &sender,  const QString &receiver, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageDlg)
{
    ui->setupUi(this);
    ui->senderLabel->setText("From: " + sender.getPhone());
    ui->receiverLabel->setText("Receiver: " + receiver);
    connect(ui->sendButton, &QPushButton::clicked, this, [&, receiver] {
        if (ui->msgText->toPlainText().size() == 0) {
            viewErrInfo("Empty message");
            return;
        }
        sender.sendMsg(receiver, ui->msgText->toPlainText());
        viewErrInfo("Success");
        this->close();
    });
}

MessageDlg::~MessageDlg()
{
    delete ui;
}
