#include "CmdPacketUpload.h"

CmdPacketUpload::CmdPacketUpload(uint8_t a_byNumberOfDataElements)
    : CmdPacket()
{
    m_idField.append(CTO::UPLOAD);
    m_dataField.resize(1); // Reserve 1 element in data field
    m_dataField[0] = a_byNumberOfDataElements;
}

void CmdPacketUpload::setNumberOfDataElements(uint8_t a_byNum)
{
    m_dataField[0] = a_byNum;
}

uint8_t CmdPacketUpload::getNumberOfDataElements()
{
    return m_dataField[0];
}
