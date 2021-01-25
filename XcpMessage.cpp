#include "XcpMessage.h"


QVector<quint8> XcpMessage::getByteArray() const
{
    if(m_pHeader != nullptr
            && m_pPacket != nullptr
            && m_pTail != nullptr) {
        return m_pHeader->getByteArray() + m_pPacket->getByteArray() + m_pTail->getByteArray();
    }
    else {
        return QVector<quint8>();
    }
}

XcpPacket *XcpMessage::getPacket()
{
    return m_pPacket;
}
