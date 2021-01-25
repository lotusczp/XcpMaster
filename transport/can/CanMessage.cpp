#include "CanMessage.h"

#include "CanHeader.h"
#include "CanTail.h"

CanMessage::CanMessage(XcpPacket *a_pPacket)
    : XcpMessage(a_pPacket)
{
    m_pHeader = new CanHeader;
    m_pTail = new CanTail;
}
