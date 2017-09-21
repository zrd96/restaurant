#ifndef _MSG_H
#define _MSG_H

#include <QString>

using namespace std;

class Msg {
        private:
                QString msgID;
                QString sender;
                QString receiver;
                QString msg;
                QString datetime;
                bool isActive;
        public:
                Msg(const QString& msgID, const QString& sender, const QString& receiver, const QString& msg, const QString& datetime, bool isActive);
                QString getMsgID() const {return msgID;}
                QString getSender() const {return sender;}
                QString getReceiver() const {return receiver;}
                QString getMsg() const {return msg;}
                QString getDatetime() const {return datetime;}
                void setSender(const QString &newSender) {sender = newSender;}
                void setReceiver(const QString &newReceiver) {receiver = newReceiver;}
                bool getState() const {return isActive;}
                void readMsg() {isActive = false;}
};

#endif
