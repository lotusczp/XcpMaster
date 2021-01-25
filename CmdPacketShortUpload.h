#ifndef CMDPACKETSHORTUPLOAD_H
#define CMDPACKETSHORTUPLOAD_H

#include "CmdPacket.h"

class CmdPacketShortUpload : public CmdPacket
{
public:
    CmdPacketShortUpload();

    void setAddress(uint32_t a_dwAddress, bool a_bIsLittleEndian);
    uint32_t getAddress(bool a_bIsLittleEndian);

    void setAddressExtension(uint8_t a_byAddressExtension);
    uint8_t getAddressExtension();

    void setNumberOfDataElements(uint8_t a_byNumberOfDataElements);
    uint8_t getNumberOfDataElements();
};

#endif // CMDPACKETSHORTUPLOAD_H
