#ifndef _MSG_H
#define _MSG_H

#include <string>

using namespace std;

class Msg {
        private:
                int sender;
                int receiver;
                string msg;
                string datetime;
        public:
                Msg(int sender, int receiver, string msg, string datetime);
                int getSender() const {return sender;}
                int getReceiver() const {return receiver;}
                string getMsg() const {return msg;}
                string getDatetime() const {return datetime;}
};

#endif
