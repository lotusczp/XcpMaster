#include "ErrorPacketOutOfRange.h"

ErrorPacketOutOfRange::ErrorPacketOutOfRange()
    : ErrorPacket()
{
    m_dataField.resize(1);
    m_dataField[0] = ErrorCodes::ERR_OUT_OF_RANGE;
}
