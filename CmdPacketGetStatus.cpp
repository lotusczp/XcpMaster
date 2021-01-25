#include "CmdPacketGetStatus.h"

CmdPacketGetStatus::CmdPacketGetStatus()
    : CmdPacket()
{
    m_idField.append(CTO::GET_STATUS);
}
