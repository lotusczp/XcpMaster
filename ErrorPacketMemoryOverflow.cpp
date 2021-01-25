#include "ErrorPacketMemoryOverflow.h"

ErrorPacketMemoryOverflow::ErrorPacketMemoryOverflow()
    : ErrorPacket()
{
    m_dataField.resize(1);
    m_dataField[0] = ErrorCodes::ERR_MEMORY_OVERFLOW;
}
