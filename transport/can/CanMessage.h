#ifndef CANMESSAGE_H
#define CANMESSAGE_H

#include "XcpMessage.h"

class CanMessage : public XcpMessage
{
public:
    CanMessage(XcpPacket* a_pPacket);
};

#endif // CANMESSAGE_H
