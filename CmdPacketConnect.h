#ifndef CMDPACKETCONNECT_H
#define CMDPACKETCONNECT_H

#include "CmdPacket.h"

class CmdPacketConnect : public CmdPacket
{
public:
    enum ConnectMode
    {
        NORMAL = 0x00,
        USER_DEFINED = 0x01
    };

public:
    CmdPacketConnect(ConnectMode a_eMode);
};

#endif // CMDPACKETCONNECT_H
