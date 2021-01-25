#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include "XcpMessage.h"

class MessageFactory
{
public:
    MessageFactory() {}
    virtual ~MessageFactory() {}

    virtual XcpMessage* createMessage(XcpPacket* a_pPacket) = 0;

    virtual QVector<uint8_t> getPacketBytes(const QVector<uint8_t>& a_rMsgBytes) = 0;
};

#endif // MESSAGEFACTORY_H
