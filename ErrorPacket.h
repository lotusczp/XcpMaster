#ifndef ERRORPACKET_H
#define ERRORPACKET_H

#include "CTO.h"

class ErrorPacket : public CTO
{
public:
    enum ErrorCodes
    {
        ERR_CMD_SYNCH = 0x00,
        ERR_CMD_BUSY = 0x10,
        ERR_DAQ_ACTIVE = 0x11,
        ERR_PGM_ACTIVE = 0x12,
        ERR_CMD_UNKNOWN = 0x20,
        ERR_CMD_SYNTAX = 0x21,
        ERR_OUT_OF_RANGE = 0x22,
        ERR_WRITE_PROTECTED = 0x23,
        ERR_ACCESS_DENIED = 0x24,
        ERR_ACCESS_LOCKED = 0x25,
        ERR_PAGE_NOT_VALID = 0x26,
        ERR_MODE_NOT_VALID = 0x27,
        ERR_SEGMENT_NOT_VALID = 0x28,
        ERR_SEQUENCE = 0x29,
        ERR_DAQ_CONFIG = 0x2A,
        ERR_MEMORY_OVERFLOW = 0x30,
        ERR_GENERIC = 0x31,
        ERR_VERIFY = 0x32,
        ERR_RESOURCE_TEMPORARY_NOT_ACCESSIBLE = 0x33,
        ERR_SUBCMD_UNKNOWN = 0x34,
    };

public:
    ErrorPacket() : CTO()
    {
        m_idField.resize(1);
        m_idField[0] = CTO::ERR;
    }
    virtual ~ErrorPacket() {}

    virtual void setErrorCode(uint8_t a_byErrorCode)
    {
        m_dataField[0] = a_byErrorCode; // Must available
    }

    virtual uint8_t getErrorCode()
    {
        return m_dataField[0]; // Must available
    }
};

#endif // ERRORPACKET_H
