#ifndef XCPMESSAGE_H
#define XCPMESSAGE_H

#include "XcpHeader.h"
#include "XcpPacket.h"
#include "XcpTail.h"

class XcpMessage
{
public:
    XcpMessage(XcpPacket* a_pPacket) {m_pPacket = a_pPacket;}

    QVector<quint8> getByteArray() const;

    XcpPacket* getPacket();

protected:
    XcpHeader   *m_pHeader;
    XcpPacket   *m_pPacket;
    XcpTail     *m_pTail;
};

#endif // XCPMESSAGE_H
