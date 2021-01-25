#ifndef ETHERNETMESSAGE_H
#define ETHERNETMESSAGE_H

#include "XcpMessage.h"

class EthernetMessage : public XcpMessage
{
public:
    EthernetMessage(XcpPacket* a_pPacket, uint16_t a_wCtr);
};

#endif // ETHERNETMESSAGE_H
