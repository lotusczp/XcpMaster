#include "ResPacketGetSeed.h"


ResPacketGetSeed::ResPacketGetSeed(const QVector<uint8_t> &a_rPacketBytes)
    : ResPacket()
{
    int iDataLength = a_rPacketBytes.size() - 1;
    m_dataField.resize(iDataLength);
    for(int i = 0; i<iDataLength; i++) {
        m_dataField[i] = a_rPacketBytes[1+i];
    }
}

uint8_t ResPacketGetSeed::getLengthField()
{
    return m_dataField[0];
}

uint8_t ResPacketGetSeed::getSeedPart(uint8_t a_byElement)
{
    return m_dataField[1+a_byElement];
}

uint8_t ResPacketGetSeed::getSeedPartSize()
{
    return (uint8_t)(m_dataField.size()-1);
}

ResPacketGetSeed *ResPacketGetSeed::deserialize(const QVector<uint8_t> &a_rPacketBytes)
{
    return new ResPacketGetSeed(a_rPacketBytes);
}
