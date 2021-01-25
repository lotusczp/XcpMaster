#ifndef RESPACKETGETSTATUS_H
#define RESPACKETGETSTATUS_H

#include <QVector>
#include "ResPacket.h"

class ResPacketGetStatus : public ResPacket
{
public:
    enum CurrentSessionStatusBits
    {
        STORE_CAL_REQ = 0x01, //Pending request to store data into non-volatile memory
        STORE_DAQ_REQ = 0x04, //Pending request to save daq list into non-volatile memory
        CLEAR_DAQ_REQ = 0x08, //pending request to clear all daq list in non-volatile memory
        DAQ_RUNNING = 0x40, //at least one daq list has been started and is in running mode
        RESUME = 0x80, //slave is in resume mode
    };

    enum CurrentResourceProtectionBits //The given resorce is protected with Seed&key. If a resource is protected, an attempt to exectue a command on it before a successful GET_SEED/UNLOCK sequence will result in ERR_ACCESS_LOCKED
    {
        CAL_PG = 0x01,
        DAQ = 0x04,
        STIM = 0x08,
        PGM = 0x10,
    };

public:
    ResPacketGetStatus(const QVector<uint8_t>& a_rPacketBytes);

    static ResPacketGetStatus* deserialize(const QVector<uint8_t>& a_rPacketBytes);

    uint8_t getCurrentSessionStatus();
    void setCurrentSessionStatus(uint8_t a_bySessionStatus);

    uint8_t getCurrentResourceProtection();
    void setCurrentResourceProtection(uint8_t a_byResourceProtection);

    uint8_t getStateNumber(); //If the XCP slave supports ECU_STATES the current STATE_NUMBER will be given to the XCP master in the response of GET_STATUS.
    void setStateNumber(uint8_t a_byState);

    uint16_t getSessionConfigurationId(bool a_bIsLittleEndian);
    void setSessionConfigurationId(uint16_t a_wSessionConfigurationId, bool a_bIsLittleEndian);
};

#endif // RESPACKETGETSTATUS_H
