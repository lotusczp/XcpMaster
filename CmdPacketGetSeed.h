#ifndef CMDPACKETGETSEED_H
#define CMDPACKETGETSEED_H

#include "CmdPacket.h"

class CmdPacketGetSeed : public CmdPacket
{
public:
    enum Mode
    {
        FIRST_PART = 0x00,
        REMAINING_PART = 0x01
    };

    enum Resource
    {
        CAL_PG = 0x01,
        DAQ = 0x04,
        STIM = 0x08,
        PGM = 0x10,
    };

public:
    CmdPacketGetSeed();
    CmdPacketGetSeed(Mode a_eMode, Resource a_eResource);
    void setMode(Mode a_eMode);
    void setResource(Resource a_eResource);
    uint8_t getResource();
};

#endif // CMDPACKETGETSEED_H
