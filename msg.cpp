#include <QString>
#include <vector>

#include "msg.h"

using namespace std;

Msg::Msg(const QString &msgID, const QString &sender, const QString &receiver, const QString &msg, const QString &datetime, bool isActive):
    msgID(msgID),
    sender(sender),
    receiver(receiver),
    msg(msg),
    datetime(datetime),
    isActive(isActive) {}
