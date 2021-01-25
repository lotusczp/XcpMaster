#include "CmdPacketDownload.h"

CmdPacketDownload::CmdPacketDownload()
    : CmdPacket()
{
    m_idField.append(CTO::DOWNLOAD);
    m_dataField.resize(5);
}

void CmdPacketDownload::setNumberOfDataElements(uint8_t a_byNum)
{
    m_dataField[0] = a_byNum;
}

uint8_t CmdPacketDownload::getNumberOfDataElements()
{
    return m_dataField[0];
}

uint32_t CmdPacketDownload::getDataElements(bool a_bIsLittleEndian)
{
    if(a_bIsLittleEndian) {
        return  (((uint32_t)m_dataField[4]) << 24) | (((uint32_t)m_dataField[3]) << 16) | (((uint32_t)m_dataField[2]) << 8) | m_dataField[1];
    }
    else {
        //do byte-swap
        return (((uint32_t)m_dataField[1]) << 24) | (((uint32_t)m_dataField[2]) << 16) | (((uint32_t)m_dataField[3]) << 8) | m_dataField[4];
    }
}

void CmdPacketDownload::setDataElements(uint32_t a_dwData, bool a_bIsLittleEndian)
{
    uint8_t i1, i2, i3, i4;
    i1 = a_dwData & 0xFF;
    i2 = (a_dwData >> 8) & 0xFF;
    i3 = (a_dwData >> 16) & 0xFF;
    i4 = (a_dwData >> 24) & 0xFF;

    if(a_bIsLittleEndian) {
        if(m_dataField[0] == 4) {
            m_dataField[1] = i1;
            m_dataField[2] = i2;
            m_dataField[3] = i3;
            m_dataField[4] = i4;
        }
        else if(m_dataField[0] == 2) {
            m_dataField[1] = i1;
            m_dataField[2] = i2;
            m_dataField[3] = 0;
            m_dataField[4] = 0;
        }
        else if(m_dataField[0] == 1) {
            m_dataField[1] = i1;
            m_dataField[2] = 0;
            m_dataField[3] = 0;
            m_dataField[4] = 0;
        }
    }
    else {
        if(m_dataField[0] == 4) {
            m_dataField[1] = i4;
            m_dataField[2] = i3;
            m_dataField[3] = i2;
            m_dataField[4] = i1;
        }
        else if(m_dataField[0] == 2) {
            m_dataField[1] = i2;
            m_dataField[2] = i1;
            m_dataField[3] = 0;
            m_dataField[4] = 0;
        }
        else if(m_dataField[0] == 1) {
            m_dataField[1] = i1;
            m_dataField[2] = 0;
            m_dataField[3] = 0;
            m_dataField[4] = 0;
        }
    }
}
