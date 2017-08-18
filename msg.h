#ifndef _MSG_H
#define _MSG_H

#include <string>

using namespace std;

class Msg {
        private:
                string sender;
                string receiver;
                string msg;
                string datetime;
                bool isActive;
        public:
                Msg(string sender, string receiver, string msg, string datetime, bool isActive);
                string getSender() const {return sender;}
                string getReceiver() const {return receiver;}
                string getMsg() const {return msg;}
                string getDatetime() const {return datetime;}
                bool getState() const {return isActive;}
};

#endif
