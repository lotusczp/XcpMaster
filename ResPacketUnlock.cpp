#include "ResPacketUnlock.h"

ResPacketUnlock::ResPacketUnlock(const QVector<uint8_t> &a_rPacketBytes)
    : ResPacket()
{
    m_dataField.resize(1);
    m_dataField[0] = a_rPacketBytes[1];
}

void ResPacketUnlock::setCurrentResourceProtection(uint8_t a_byCurrentProection)
{
    m_dataField[0] = a_byCurrentProection;
}

uint8_t ResPacketUnlock::getCurrentResourceProtection()
{
    return m_dataField[0];
}

ResPacketUnlock *ResPacketUnlock::deserialize(const QVector<uint8_t> &a_rPacketBytes)
{
    return new ResPacketUnlock(a_rPacketBytes);
}
