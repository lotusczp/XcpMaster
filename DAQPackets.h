#ifndef DAQPACKETS_H
#define DAQPACKETS_H

#include "CmdPacket.h"
#include "ResPacket.h"

class FreeDaqPacket final : public CmdPacket
{
public:
    FreeDaqPacket();
};


class AllocDaqPacket final : public CmdPacket
{
public:
    AllocDaqPacket();
    void setDaqCount(uint16_t a_wDaqCount, bool a_bIsLittleEndian);
    uint16_t getDaqCount(bool a_bIsLittleEndian);
};


class AllocOdtPacket final : public CmdPacket
{
public:
    AllocOdtPacket();
    void setDaqListNumber(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian);
    void setOdtCount(uint8_t a_byOdtCount);
};


class AllocOdtEntryPacket final : public CmdPacket
{
public:
    AllocOdtEntryPacket();
    void setDaqListNumber(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian);
    void setOdtNumber(uint8_t a_byOdtNumber);
    void setOdtEntriesCount(uint8_t a_byOdtEntriesCount);
};


class SetDaqPtrPacket final : public CmdPacket
{
public:
    SetDaqPtrPacket();
    void setDaqListNumber(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian);
    void setOdtNumber(uint8_t a_byOdtNumber);
    void setOdtEntryNumber(uint8_t a_byOdtEntryNumber);
};


class WriteDaqPacket final : public CmdPacket
{
public:
    WriteDaqPacket();
    // For DAQ diresction it is a bitmask, for STIM direction it is the position of the bit to be manipulated.
    // The DAQ pointer is auto post incremented within an ODT.
    // After the last ODT entry the pointer value is undefined.
    void setBitOffset(uint8_t a_byOffset);
    void setElementSize(uint8_t a_bySize);
    void setAddressExtension(uint8_t a_byAddressExtension);
    void setAddress(uint32_t a_dwAddress, bool a_bIsLittleEndian);
};


class SetDaqListModePacket final : public CmdPacket
{
public:
    enum ModeFieldBits
    {
        ALTERNATING = 0x01, //0: disable alternating display mode, 1: enable
        DIRECTION = 0x02, //0: DAQ direction, 1: STIM direction
        DTO_CTR = 0x08, //0: do not use DTO ctr field, 1: use ctr
        TIMESTAMP = 0x10, //0: disable timestamp, 1: enable
        PID_OFF = 0x20, //0: transmit DTO with identification field, 1: transmit DTO WITHOUT identifictation field
    };

public:
    SetDaqListModePacket();
    SetDaqListModePacket(uint8_t a_byMode, uint16_t a_wDaqListNumber, uint16_t a_wEventChannel, uint8_t a_byPrescaler, uint8_t a_byPriority, bool a_bIsLittleEndian);
    void setMode(uint8_t a_byMode);
    void setDaqListNumber(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian);
    void setEventChannel(uint16_t a_wEventChannel, bool a_bIsLittleEndian);
    void setTransmissionRatePrescaler(uint8_t a_byPrescaler);
    void setDaqListPriority(uint8_t a_byPriority);
};


class StartStopDaqListPacket final : public CmdPacket
{
public:
    enum Mode
    {
        STOP = 0x0,
        START = 0x1,
        SELECT = 0x2,
    };

public:
    StartStopDaqListPacket();
    //Mode: 0 stop, 1 start, 2 select
    StartStopDaqListPacket(uint8_t a_byMode, uint16_t a_wDaqListNumber, bool a_bIsLittleEndian);
    void setMode(uint8_t a_byMode);
    void setDaqListNumber(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian);
    uint16_t getDaqListNumber(bool a_bIsLittleEndian);
};


class StartStopDaqListPositiveResponse final : public ResPacket
{
public:
    StartStopDaqListPositiveResponse(const QVector<uint8_t>& a_rData);
    uint8_t getFirstPid();
    static StartStopDaqListPositiveResponse* deserialize(const QVector<uint8_t>& a_rData);
};


class StartStopSynchPacket final : public CmdPacket
{
public:
    enum Mode
    {
        STOP_ALL = 0x00,
        START_SELECTED = 0x01,
        STOP_SELECTED = 0x02,
    };
    StartStopSynchPacket(Mode a_eMode);
    void setMode(uint8_t a_byMode);
};


class GetDaqProcessorInfo final : public CmdPacket
{
public:
    GetDaqProcessorInfo();
};


class GetDaqProcessorInfoResponse final : public ResPacket
{
public:
    enum DaqPropertiesBits
    {
        DAQ_CONFIG_TYPE = 0x01, //0: Static DAQ list configuration, 1: dynamic daq list configuration
        PRESCALER_SUPPORTED = 0x02, //0: prescaler not supported, 1: prescaler supported
        RESUME_SUPPORTED = 0x04, //0: DAQ list can not be set to resume mode, 1: Daq list can be set to resume mode
        BIT_STIM_SUPPORTED = 0x08, //0: bitwise datastimulation not supported, 1: supported
        TIMESTAMP_SUPPORTED = 0x10, //0: timestamped mode not supported, 1: supported
        PID_OFF_SUPPORTED = 0x20, //0: Identification field can not be switched off, 1: Identification field may be switched off
        OVERLOAD_MSB = 0x40,
        OVERLOAD_EVENT = 0x80, //OE-OM: 0-0:No overload indication | 0-1:overload indication in MSB of PID | 1-0: overload indication by Event Packet | 1-1: not allowed

        OVERLOAD_INDICATION_MODE = 0xC0, //the 2 before, only combined
    };

    enum DaqKeyByteBits
    {
        OPTIMISATION_TYPE_0 = 0x01, //The Optimisation_Type flags indicate the type of Optimisation Method the master preferably should use.
        OPTIMISATION_TYPE_1 = 0x02,
        OPTIMISATION_TYPE_2 = 0x04,
        OPTIMISATION_TYPE_3 = 0x08, //OT3-2-1-0: 0000: OM_DEFAULT | 0001: OM_ODT_TYPE_16 | 0010: OM_ODT_TYPE_32 | 0011: OM_ODT_TYPE_64 | 0100: OM_ODT_TYPE_ALIGNMENT | 0101: OM_MAX_ENTRY_SIZE

        OPTIMISATION_TYPE = 0x0F, ////the 4 entries before this one, only that it is combined into one

        ADDRESS_EXTENSION_ODT = 0x10, //The ADDR_EXTENSION flag indicates whether the address extension of all entries within one ODT or within one DAQ must be the same.
        ADDRESS_EXTENSION_DAQ = 0x20, //AEDAQ-AEODT: 00: address extension can be different within one and the same ODT | 01: 0 1 address extension to be the same for all entries within one ODT | 10: not allowed | 11: address extension to be the same for all entries within one DAQ

        ADDRESS_EXTENSION = 0x30,

        IDENTIFICATION_FIELD_TYPE_0 = 0x40,
        IDENTIFICATION_FIELD_TYPE_1 = 0x80, //00: absoulute odt number | 01: Relative ODT number, absolute DAQ list number (BYTE) | Relative ODT number, absolute DAQ list number (WORD) | 11: Relative ODT number, absolute DAQ list number (WORD, aligned)

        IDENTIFICATION_FIELD_TYPE = 0xC0, //the two entries before this one, only that it is combined into one
    };

    enum OverloadIndicationMode
    {
        NO_INDICATION = 0x00,
        MSB_PID = 0x40,
        EVENT_PACKET = 0x80,
        NOT_ALLOWED = 0xC0,
    };

    enum OptimisationMode
    {
        OM_DEFAULT = 0x00,
        OM_ODT_TYPE_16 = 0x01,
        OM_ODT_TYPE_32 = 0x02,
        OM_ODT_TYPE_64 = 0x03,
        OM_ODT_TYPE_ALIGNMENT = 0x04,
        OM_MAX_ENTRY_SIZE = 0x05,
    };

    enum AddressExtensionType
    {
        CAN_BE_DIFFERENT = 0x00,
        SAME_FOR_ALL_ENTRIES_ODT = 0x10,
//		NOT_ALLOWED = 0x20,
        SAME_FOR_ALL_ENTRIES_DAQ = 0x30
    };

    enum IdentificationFieldType
    {
        ABSOLUTE_ODT_NUMBER = 0x00,
        RELATIVE_ODT_ABSOLUTE_DAQ_BYTE = 0x40,
        RELATIVE_ODT_ABSOLUTE_DAQ_WORD = 0x80,
        RELATIVE_ODT_ABSOLUTE_DAQ_WORD_ALIGNED = 0xC0,
    };

    GetDaqProcessorInfoResponse(const QVector<uint8_t>& a_rData);
    static GetDaqProcessorInfoResponse* deserialize(const QVector<uint8_t>& a_rData);
    uint8_t getDaqProperties();
    //total number of DAQ lists available in the slave device. If DAQ_CONFIG_TYPE =	dynamic, MAX_DAQ equals MIN_DAQ + DAQ_COUNT
    uint16_t getMaxDaq(bool a_bIsLittleEndian);
    //MAX_EVENT_CHANNEL is the number of available event channels. MAX_EVENT_CHANNEL = 0x00 means that the number of events in the slave is unknown.
    uint16_t getMaxEventChannel(bool a_bIsLittleEndian);
    //MIN_DAQ is the number of predefined DAQ lists.
    uint8_t getMinDaq();
    uint8_t getDaqKeyByte();
};


class ClearDAQListPacket final : public CmdPacket
{
public:
    ClearDAQListPacket(uint16_t a_wDAQListNumber, bool a_bIsLittleEndian);
    void setDaqListNumber(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian);
    uint16_t getDaqListNumber(bool a_bIsLittleEndian);
};

#endif // DAQPACKETS_H
