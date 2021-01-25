#include "EthernetHeader.h"

EthernetHeader::EthernetHeader(uint16_t a_wLen, uint16_t a_wCtr)
    : XcpHeader()
{
    m_wLength = a_wLen;
    m_wCtr = a_wCtr;
}

EthernetHeader::~EthernetHeader()
{

}

QVector<quint8> EthernetHeader::getByteArray()
{
    QVector<quint8> retval;

    retval.push_back((uint8_t)(m_wLength) & 0xFF);
    retval.push_back((uint8_t)(((m_wLength) & 0xFF00)>>8));
    retval.push_back((uint8_t)(m_wCtr) & 0xFF);
    retval.push_back((uint8_t)(((m_wCtr) & 0xFF00) >> 8));

    return retval;
}
