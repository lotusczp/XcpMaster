#ifndef CMDPACKET_H
#define CMDPACKET_H

#include "CTO.h"

class CmdPacket : public CTO
{
public:
    CmdPacket() : CTO() {}
    virtual ~CmdPacket() {}
};

#endif // CMDPACKET_H
