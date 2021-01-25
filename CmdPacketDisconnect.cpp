#include "CmdPacketDisconnect.h"

CmdPacketDisconnect::CmdPacketDisconnect()
    : CmdPacket()
{
    m_idField.append(CTO::DISCONNECT);
}
