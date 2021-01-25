#include "CmdPacketConnect.h"

CmdPacketConnect::CmdPacketConnect(CmdPacketConnect::ConnectMode a_eMode)
    : CmdPacket()
{
    m_idField.append(CTO::CONNECT);
    m_dataField.append(a_eMode);
}
