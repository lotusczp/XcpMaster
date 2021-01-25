#ifndef RESPACKETCONNECT_H
#define RESPACKETCONNECT_H

#include "ResPacket.h"

class ResPacketConnect : public ResPacket
{
public:
    //If a resource is available the mandatory commands of this resource must be supported
    enum ResourceParameterBits
    {
        CAL_PG	= 0x1,	//Calibration and Paging: 0 = not available , 1 = avilable
        DAQ		= 0x4,	//DAQ list supported: 0 = not avaliable, 1 = available
        STIM	= 0x8,	//STIM - Data stimulation of a daq list: 0 = not available, 1 = available
        PGM		= 0x10,	//Programming: 0 = flash programming not available, 1 = available
    };

    enum CommModeBasicBits
    {
        BYTE_ORDER				= 0x1,	//Byte order for multibyte parameters. 0 = Little endian (Intel format), 1 = Big Endian (Motorola format)
        ADDRESS_GRANULARITY_0	= 0x2,	//The address granularity indicates the size of an element
        ADDRESS_GRANULARITY_1	= 0x4,	//The address granularity indicates the size of an element: 00-byte, 01-word, 10-DWORD, 11-reserved
        ADDRESS_GRANULARITY_BOTH = 0x6,
        SLAVE_BLOCK_MODE		= 0x40, //Inidicates if slave block mode is available
        OPTIONAL				= 0x80, //The OPTIONAL flag indicates whether additional information on supported types of 	Communication mode is available.The master can get that additional information with GET_COMM_MODE_INFO.
    };

public:
    ResPacketConnect(uint8_t a_byResource, uint8_t a_byCommModeBasic, uint8_t a_byMaxCto, uint16_t a_wMaxDto, uint8_t a_byProtocolLayerVersion, uint8_t a_byTransportLayerVersion);
    uint8_t getResource();
    uint8_t getCommModeBasic();
    uint8_t getMaxCto();
    uint16_t getMaxDto(bool a_bIsLittleEndian);
    uint8_t getProtocolLayerVersion();
    uint8_t getTransportLayerVersion();
    void setResource(uint8_t a_byResource);
    void setCommModeBasic(uint8_t a_byCommModeBasic);
    void setMaxCto(uint8_t a_byCto);
    void setMaxDto(uint16_t a_wDto);
    void setProtocolLayerVersion(uint8_t a_byVersion);
    void setTransportLayerVersion(uint8_t a_byVersion);

    static ResPacketConnect* deserialize(const QVector<uint8_t>& a_rPacketBytes);

private:
    ResPacketConnect(const QVector<uint8_t>& a_rPacketBytes);
};

#endif // RESPACKETCONNECT_H
