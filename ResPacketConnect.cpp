#include "ResPacketConnect.h"

ResPacketConnect::ResPacketConnect(uint8_t a_byResource, uint8_t a_byCommModeBasic, uint8_t a_byMaxCto, uint16_t a_wMaxDto, uint8_t a_byProtocolLayerVersion, uint8_t a_byTransportLayerVersion)
    : ResPacket ()
{
    m_dataField.resize(7);

    setResource(a_byResource);
    setCommModeBasic(a_byCommModeBasic);
    setMaxCto(a_byMaxCto);
    setMaxDto(a_wMaxDto);
    setProtocolLayerVersion(a_byProtocolLayerVersion);
    setTransportLayerVersion(a_byTransportLayerVersion);
}

uint8_t ResPacketConnect::getResource()
{
    return m_dataField[0];
}

uint8_t ResPacketConnect::getCommModeBasic()
{
    return m_dataField[1];
}

uint8_t ResPacketConnect::getMaxCto()
{
    return m_dataField[2];
}

uint16_t ResPacketConnect::getMaxDto(bool a_bIsLittleEndian)
{
    if(a_bIsLittleEndian) {
        return (((uint16_t)m_dataField[4]) << 8) | m_dataField[3];
    }
    else {
        //do byte-swap
        return (((uint16_t)m_dataField[3]) << 8) | m_dataField[4];
    }
}

uint8_t ResPacketConnect::getProtocolLayerVersion()
{
    return m_dataField[5];
}

uint8_t ResPacketConnect::getTransportLayerVersion()
{
    return m_dataField[6];
}

void ResPacketConnect::setResource(uint8_t a_byResource)
{
    m_dataField[0] = a_byResource;
}

void ResPacketConnect::setCommModeBasic(uint8_t a_byCommModeBasic)
{
    m_dataField[1] = a_byCommModeBasic;
}

void ResPacketConnect::setMaxCto(uint8_t a_byCto)
{
    m_dataField[2] = a_byCto;
}

void ResPacketConnect::setMaxDto(uint16_t a_wDto)
{
    m_dataField[3] = a_wDto & 0xFF;
    m_dataField[4] = (a_wDto & 0xFF00) >> 8;
}

void ResPacketConnect::setProtocolLayerVersion(uint8_t a_byVersion)
{
    m_dataField[5] = a_byVersion;
}

void ResPacketConnect::setTransportLayerVersion(uint8_t a_byVersion)
{
    m_dataField[6] = a_byVersion;
}

ResPacketConnect *ResPacketConnect::deserialize(const QVector<uint8_t> &a_rPacketBytes)
{
    return new ResPacketConnect(a_rPacketBytes);
}

ResPacketConnect::ResPacketConnect(const QVector<uint8_t> &a_rPacketBytes)
    : ResPacket ()
{
    m_dataField.resize(7);

    for (int i=0; i<7; i++) {
        m_dataField[i] = a_rPacketBytes[i+1];
    }

}
