#include "ErrorPacketCmdUnknown.h"

ErrorPacketCmdUnknown::ErrorPacketCmdUnknown()
    : ErrorPacket()
{
    m_dataField.resize(1);
    m_dataField[0] = ErrorCodes::ERR_CMD_UNKNOWN;
}
