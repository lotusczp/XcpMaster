#ifndef CMDPACKETDOWNLOAD_H
#define CMDPACKETDOWNLOAD_H

#include "CmdPacket.h"

class CmdPacketDownload : public CmdPacket
{
public:
    CmdPacketDownload();

    void setNumberOfDataElements(uint8_t a_byNum);
    uint8_t getNumberOfDataElements();

    uint32_t getDataElements(bool a_bIsLittleEndian);
    void setDataElements(uint32_t a_dwData, bool a_bIsLittleEndian);
};

#endif // CMDPACKETDOWNLOAD_H
