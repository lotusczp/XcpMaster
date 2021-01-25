#ifndef DTO_H
#define DTO_H

#include "XcpPacket.h"

class DaqLayout;

class DTO : public XcpPacket
{
public:
    DTO();
    DTO(const QVector<uint8_t>& a_rData, uint8_t TimestampSize, bool TimestampFixed, uint8_t IdentificationFieldType, DaqLayout& a_rDaqLayout);
    virtual ~DTO();
    uint16_t getDaqField() {return m_wDaq;}
    uint8_t getCtrField() {return m_byCtr;}
    uint8_t getFillField() {return m_byFill;}
    uint32_t getTimestamp() {return m_dwTimestamp;}
    bool isTimestamped() {return m_bIsTimestamped;}
    bool isCTRed() {return m_bIsCTRed;}
    //Gets the index of the packet in the DAQList int the DAQLayout descriptor. It is already calculated, so no more transformations needed. (Absolute ODT, relative odt abs DAQ)
    uint16_t getDaqIndex() {return m_wDaqIndex;}
    //Gets the index of the packet in the ODTList int the DAQLayout descriptor. It is already calculated, so no more transformations needed. (Absolute ODT, relative odt abs DAQ)
    uint8_t getOdtIndex() {return m_byOdtIndex;}

private:
    uint16_t    m_wDaq;
    uint8_t     m_byFill; //If in aligned DAQ mode, this is the ctr field
    uint8_t     m_byCtr;
    uint32_t    m_dwTimestamp;
    bool        m_bIsTimestamped;
    bool        m_bIsCTRed;
    uint16_t    m_wDaqIndex; //Index of the packet in the DAQList DaqLayout descriptor
    uint8_t     m_byOdtIndex; //Index of the packet in the ODTList in the DaqLayout descriptor

};

#endif // DTO_H
