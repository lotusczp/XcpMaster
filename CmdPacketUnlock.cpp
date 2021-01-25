#include "CmdPacketUnlock.h"

CmdPacketUnlock::CmdPacketUnlock(const QVector<uint8_t> &a_rKey, uint8_t a_byStartIndex, uint8_t a_byMaxCto)
    : CmdPacket()
{
    m_idField.append(CTO::UNLOCK);

    uint8_t byDataLength = 0;
    if((uint8_t)a_rKey.size() - a_byStartIndex >= a_byMaxCto - 2) {
        byDataLength = a_byMaxCto - 2;
    }
    else {
        byDataLength = (uint32_t)a_rKey.size() + 1;
    }

    m_dataField.resize(byDataLength);
    m_dataField[0] = (uint8_t)a_rKey.size() - a_byStartIndex;
    for(unsigned int i = 0; i < byDataLength-1; i++) {
        m_dataField[1 + i] = a_rKey[a_byStartIndex + i];
    }
}

QVector<XcpPacket *> CmdPacketUnlock::createUnlockPackets(const QVector<uint8_t> &a_rKey, uint8_t a_byMaxCto)
{
    QVector<XcpPacket *> retval;
    uint8_t byRemainingKeyLength = (uint8_t)a_rKey.size();
    do {
        CmdPacketUnlock* pToAdd = new CmdPacketUnlock(a_rKey, 0, a_byMaxCto);
        byRemainingKeyLength -= pToAdd->getRemainingKeyLength();
        retval.push_back(pToAdd);
    } while(byRemainingKeyLength);

    return retval;
}

uint8_t CmdPacketUnlock::getRemainingKeyLength()
{
    return m_dataField[0];
}
