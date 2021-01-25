#include "EthernetMessageFactory.h"

#include "EthernetMessage.h"

EthernetMessageFactory::EthernetMessageFactory()
{
    m_wNumberOfCreatedMessages = 0;
}

EthernetMessageFactory::~EthernetMessageFactory()
{

}

XcpMessage *EthernetMessageFactory::createMessage(XcpPacket *a_pPacket)
{
    return new EthernetMessage(a_pPacket, m_wNumberOfCreatedMessages++);
}

QVector<uint8_t> EthernetMessageFactory::getPacketBytes(const QVector<uint8_t> &a_rMsgBytes)
{
    QVector<uint8_t> retval = a_rMsgBytes;

    // Ethernet message has 4-byte header and no tail
    retval.removeAt(0);
    retval.removeAt(1);
    retval.removeAt(2);
    retval.removeAt(3);

    return retval;
}
