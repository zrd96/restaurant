#include <string>
#include <vector>

#include "msg.h"

using namespace std;

Msg::Msg(string sender, string receiver, string msg, string datetime, bool isActive): sender(sender), receiver(receiver), msg(msg), datetime(datetime), isActive(isActive) {}

