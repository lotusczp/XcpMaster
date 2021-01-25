#include "CmdPacketSync.h"

CmdPacketSync::CmdPacketSync()
    : CmdPacket()
{
    m_idField.append(CTO::SYNCH);
}
