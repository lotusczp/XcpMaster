#include "ErrorPacketSequence.h"

ErrorPacketSequence::ErrorPacketSequence()
    : ErrorPacket()
{
    m_dataField.resize(1);
    m_dataField[0] = ErrorCodes::ERR_SEQUENCE;
}
