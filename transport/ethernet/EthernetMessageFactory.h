#ifndef ETHERNETMESSAGEFACTORY_H
#define ETHERNETMESSAGEFACTORY_H

#include "MessageFactory.h"

class EthernetMessageFactory : public MessageFactory
{
public:
    EthernetMessageFactory();
    ~EthernetMessageFactory();

    virtual XcpMessage* createMessage(XcpPacket* a_pPacket);

    virtual QVector<uint8_t> getPacketBytes(const QVector<uint8_t>& a_rMsgBytes);

private:
    uint16_t m_wNumberOfCreatedMessages;
};

#endif // ETHERNETMESSAGEFACTORY_H
