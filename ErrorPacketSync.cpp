#include "ErrorPacketSync.h"

ErrorPacketSync::ErrorPacketSync()
    : ErrorPacket()
{
    m_dataField.resize(1);
    m_dataField[0] = ErrorCodes::ERR_CMD_SYNCH;
}
