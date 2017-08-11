#include <string>
#include <vector>

#include "msg.h"

using namespace std;

Msg::Msg(int sender, int receiver, string msg, string datetime): sender(sender), receiver(receiver), msg(msg), datetime(datetime) {}

