#include "ErrorPacketAccessLocked.h"

ErrorPacketAccessLocked::ErrorPacketAccessLocked()
    : ErrorPacket()
{
    m_dataField.resize(1);
    m_dataField[0] = ErrorCodes::ERR_ACCESS_LOCKED;
}
