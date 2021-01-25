#include "EthernetMessage.h"

#include "EthernetHeader.h"
#include "EthernetTail.h"

EthernetMessage::EthernetMessage(XcpPacket *a_pPacket, uint16_t a_wCtr)
    : XcpMessage(a_pPacket)
{
    m_pHeader = new EthernetHeader(a_pPacket->getByteArray().size(), a_wCtr);
    m_pTail = new EthernetTail;
}
