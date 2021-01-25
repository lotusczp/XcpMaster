#ifndef CMDPACKETUPLOAD_H
#define CMDPACKETUPLOAD_H

#include "CmdPacket.h"

class CmdPacketUpload : public CmdPacket
{
public:
    //Number of dataelements: 1..[MAXCTO/AG - 1] in standardmode, 1..255 in block mode
    CmdPacketUpload(uint8_t a_byNumberOfDataElements);

    void setNumberOfDataElements(uint8_t a_byNum);
    uint8_t getNumberOfDataElements();
};

#endif // CMDPACKETUPLOAD_H
