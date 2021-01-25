#ifndef CMDPACKETSETMTA_H
#define CMDPACKETSETMTA_H

#include "CmdPacket.h"

class CmdPacketSetMta : public CmdPacket
{
public:
    CmdPacketSetMta();

    uint8_t getAddressExtension();
    void setAddressExtension(uint8_t a_byAddressExtension);

    uint32_t getAddress(bool a_bIsLittleEndian);
    void setAddress(uint32_t a_dwAddress, bool a_bIsLittleEndian);
};

#endif // CMDPACKETSETMTA_H
