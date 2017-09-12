#include <string>
#include <vector>

#include "msg.h"

using namespace std;

//Msg::Msg(string sender, string receiver, string msg, string datetime, bool isActive):
//    msgID(-1),
//    sender(sender),
//    receiver(receiver),
//    msg(msg),
//    datetime(datetime),
//    isActive(isActive) {}

Msg::Msg(const string &msgID, const string &sender, const string &receiver, const string &msg, const string &datetime, bool isActive):
    msgID(msgID),
    sender(sender),
    receiver(receiver),
    msg(msg),
    datetime(datetime),
    isActive(isActive) {}
