#include "CmdPacketSetMta.h"

CmdPacketSetMta::CmdPacketSetMta()
    : CmdPacket()
{
    m_idField.append(CTO::SET_MTA);
    m_dataField.resize(7); // Reserve 7 element in data field
    m_dataField[0] = 0; // Unused
    m_dataField[1] = 0; // Unused
}

uint8_t CmdPacketSetMta::getAddressExtension()
{
    return m_dataField[2];
}

void CmdPacketSetMta::setAddressExtension(uint8_t a_byAddressExtension)
{
    m_dataField[2] = a_byAddressExtension;
}

uint32_t CmdPacketSetMta::getAddress(bool a_bIsLittleEndian)
{
    if(a_bIsLittleEndian) {
        return  (((uint32_t)m_dataField[6]) << 24) | (((uint32_t)m_dataField[5]) << 16) | (((uint32_t)m_dataField[4]) << 8) | m_dataField[3];
    }
    else {
        //do byte-swap
        return (((uint32_t)m_dataField[3]) << 24) | (((uint32_t)m_dataField[4]) << 16) | (((uint32_t)m_dataField[5]) << 8) | m_dataField[6];
    }
}

void CmdPacketSetMta::setAddress(uint32_t a_dwAddress, bool a_bIsLittleEndian)
{
    uint8_t i1, i2, i3, i4;
    i1 = a_dwAddress & 0xFF;
    i2 = (a_dwAddress >> 8) & 0xFF;
    i3 = (a_dwAddress >> 16) & 0xFF;
    i4 = (a_dwAddress >> 24) & 0xFF;

    if(a_bIsLittleEndian) {
        m_dataField[3] = i1;
        m_dataField[4] = i2;
        m_dataField[5] = i3;
        m_dataField[6] = i4;
    }
    else {
        m_dataField[3] = i4;
        m_dataField[4] = i3;
        m_dataField[5] = i2;
        m_dataField[6] = i1;
    }
}
