#ifndef CANMESSAGEFACTORY_H
#define CANMESSAGEFACTORY_H

#include "MessageFactory.h"

class CanMessageFactory : public MessageFactory
{
public:
    CanMessageFactory();
    ~CanMessageFactory();

    virtual XcpMessage* createMessage(XcpPacket* a_pPacket);

    virtual QVector<uint8_t> getPacketBytes(const QVector<uint8_t>& a_rMsgBytes);
};

#endif // CANMESSAGEFACTORY_H
