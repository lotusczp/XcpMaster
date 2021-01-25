#include "ResPacketGetStatus.h"

ResPacketGetStatus::ResPacketGetStatus(const QVector<uint8_t> &a_rPacketBytes)
    : ResPacket()
{
    m_dataField.resize(5);
    for(int i=0; i<5; i++) {
        m_dataField[i] = a_rPacketBytes[i+1];
    }
}

ResPacketGetStatus *ResPacketGetStatus::deserialize(const QVector<uint8_t> &a_rPacketBytes)
{
    return new ResPacketGetStatus(a_rPacketBytes);
}

uint8_t ResPacketGetStatus::getCurrentSessionStatus()
{
    return m_dataField[0];
}

void ResPacketGetStatus::setCurrentSessionStatus(uint8_t a_bySessionStatus)
{
    m_dataField[0] = a_bySessionStatus;
}

uint8_t ResPacketGetStatus::getCurrentResourceProtection()
{
    return m_dataField[1];
}

void ResPacketGetStatus::setCurrentResourceProtection(uint8_t a_byResourceProtection)
{
    m_dataField[0] = a_byResourceProtection;
}

uint8_t ResPacketGetStatus::getStateNumber()
{
    return m_dataField[2];
}

void ResPacketGetStatus::setStateNumber(uint8_t a_byState)
{
    m_dataField[2] = a_byState;
}

uint16_t ResPacketGetStatus::getSessionConfigurationId(bool a_bIsLittleEndian)
{
    if(a_bIsLittleEndian) {
        return (((uint16_t)m_dataField[4]) << 8) | m_dataField[3];
    }
    else {
        //do byte-swap
        return (((uint16_t)m_dataField[3]) << 8) | m_dataField[4];
    }
}

void ResPacketGetStatus::setSessionConfigurationId(uint16_t a_wSessionConfigurationId, bool a_bIsLittleEndian)
{
    uint8_t i1, i2;
    i1 = a_wSessionConfigurationId & 0xFF;
    i2 = (a_wSessionConfigurationId >> 8) & 0xFF;

    if(a_bIsLittleEndian) {
        m_dataField[3] = i1;
        m_dataField[4] = i2;
    }
    else {
        m_dataField[3] = i2;
        m_dataField[4] = i1;
    }
}
