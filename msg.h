#ifndef _MSG_H
#define _MSG_H

#include <string>

using namespace std;

class Msg {
        private:
                int msgID;
                string sender;
                string receiver;
                string msg;
                string datetime;
                bool isActive;
        public:
                Msg(string sender, string receiver, string msg, string datetime, bool isActive);
                Msg(string sender, string receiver, string msg, string datetime, bool isActive, int msgID);
                int getMsgID() const {return msgID;}
                string getSender() const {return sender;}
                string getReceiver() const {return receiver;}
                string getMsg() const {return msg;}
                string getDatetime() const {return datetime;}
                void setSender(string newSender) {sender = newSender;}
                void setReceiver(string newReceiver) {receiver = newReceiver;}
                bool getState() const {return isActive;}
};

#endif
