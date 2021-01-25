#include "CanMessageFactory.h"

#include "CanMessage.h"

CanMessageFactory::CanMessageFactory()
    : MessageFactory()
{

}

CanMessageFactory::~CanMessageFactory()
{

}

XcpMessage *CanMessageFactory::createMessage(XcpPacket *a_pPacket)
{
    return new CanMessage(a_pPacket);
}

QVector<uint8_t> CanMessageFactory::getPacketBytes(const QVector<uint8_t> &a_rMsgBytes)
{
    QVector<uint8_t> retval = a_rMsgBytes;

    // CAN message has no header nor tail
    return retval;
}
