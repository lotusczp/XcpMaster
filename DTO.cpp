#include "DTO.h"
#include <QDebug>
#include "DAQ.h"
#include "DAQPackets.h"

DTO::DTO()
    : XcpPacket ()
{

}

DTO::DTO(const QVector<uint8_t> &a_rData, uint8_t TimestampSize, bool TimestampFixed, uint8_t IdentificationFieldType, DaqLayout &a_rDaqLayout)
    : XcpPacket ()
{
    m_bIsTimestamped = false;
    m_dwTimestamp = 0;
    m_bIsCTRed = false;
    m_byCtr = 0;
    m_byFill = 0;
    m_wDaq = 0;
    m_wDaqIndex = 0;
    m_byOdtIndex = 0;
    uint8_t Mode = 0;
    ODT currentOdtLayout;

    uint32_t ptr = 0;
    setPid(a_rData[ptr]); //between 0x00-0xFB
    ptr++;
    if (IdentificationFieldType == GetDaqProcessorInfoResponse::IdentificationFieldType::ABSOLUTE_ODT_NUMBER) {
        if(!a_rDaqLayout.calcDaqNumberFromAbsPid(getPid(), m_wDaqIndex)) return;
        if(!a_rDaqLayout.calcOdtNumberFromAbsPid(getPid(), m_byOdtIndex)) return;
        Mode = a_rDaqLayout.getDaq(m_wDaqIndex).getMode();
        if(!a_rDaqLayout.getOdtFromAbsolutePid(getPid(), currentOdtLayout)) return;
        if (currentOdtLayout.isFirst() && (SetDaqListModePacket::ModeFieldBits::DTO_CTR&Mode))
        {
            m_byCtr = a_rData[ptr];
            ptr++;
        }
    }
    else if (IdentificationFieldType == GetDaqProcessorInfoResponse::IdentificationFieldType::RELATIVE_ODT_ABSOLUTE_DAQ_BYTE)
    {
        m_wDaq = a_rData[ptr];
        m_wDaqIndex = m_wDaq;
        m_byOdtIndex = getPid();
        ptr++;
        Mode = a_rDaqLayout.getDaq(m_wDaq).getMode();
        currentOdtLayout = a_rDaqLayout.getDaq(m_wDaq).getOdt(getPid());
        if (currentOdtLayout.isFirst() && (SetDaqListModePacket::ModeFieldBits::DTO_CTR&Mode))
        {
            m_byCtr = a_rData[ptr];
            ptr++;
        }
    }
    else if (IdentificationFieldType == GetDaqProcessorInfoResponse::IdentificationFieldType::RELATIVE_ODT_ABSOLUTE_DAQ_WORD)
    {
        uint16_t t1 = a_rData[ptr];
        uint16_t t2 = a_rData[ptr + 1];
        m_wDaq = t1 & 0xFF;
        m_wDaq |= (t2 << 8) & 0xFF00;
        m_wDaqIndex = m_wDaq;
        m_byOdtIndex = getPid();
        Mode = a_rDaqLayout.getDaq(m_wDaq).getMode();
        currentOdtLayout = a_rDaqLayout.getDaq(m_wDaq).getOdt(getPid());
        if (currentOdtLayout.isFirst() && (SetDaqListModePacket::ModeFieldBits::DTO_CTR&Mode))
        {
            m_byCtr = a_rData[ptr];
            ptr += 3;
        }
        else
        {
            ptr += 2;
        }
    }
    else if (IdentificationFieldType == GetDaqProcessorInfoResponse::IdentificationFieldType::RELATIVE_ODT_ABSOLUTE_DAQ_WORD_ALIGNED)
    {
        m_byFill = a_rData[ptr];
        uint16_t t1 = a_rData[ptr + 1];
        uint16_t t2 = a_rData[ptr + 2];
        m_wDaq = t1 & 0xFF;
        m_wDaq |= (t2 << 8) & 0xFF00;
        m_wDaqIndex = m_wDaq;
        m_byOdtIndex = getPid();
        Mode = a_rDaqLayout.getDaq(m_wDaq).getMode();
        ptr += 3;
    }


    if (Mode&SetDaqListModePacket::ModeFieldBits::DTO_CTR)
    {
        m_bIsCTRed = true;
    }

    if ((Mode&SetDaqListModePacket::ModeFieldBits::TIMESTAMP || TimestampFixed) && currentOdtLayout.isFirst())
    {
        m_bIsTimestamped = true;
        if (TimestampSize == 1)
        {
            m_dwTimestamp = a_rData[ptr];
            ptr++;
        }
        else if (TimestampSize == 2)
        {
            uint32_t t1, t2;
            t1 = a_rData[ptr];
            t2 = a_rData[ptr + 1];
            ptr += 2;
            m_dwTimestamp = t1 & 0xFF;
            m_dwTimestamp |= ((t2 << 8) & 0xFF00);
        }
        else if (TimestampSize == 4)
        {
            uint32_t t1, t2, t3, t4;
            t1 = a_rData[ptr];
            t2 = a_rData[ptr + 1];
            t3 = a_rData[ptr + 2];
            t4 = a_rData[ptr + 3];
            ptr += 4;
            m_dwTimestamp = t1 & 0xFF;
            m_dwTimestamp |= ((t2 << 8) & 0x0000FF00);
            m_dwTimestamp |= ((t3 << 16) & 0x00FF0000);
            m_dwTimestamp |= ((t4 << 24) & 0xFF000000);
        }
    }

    uint32_t dwDataLength = currentOdtLayout.getOdtSize();
    m_dataField.resize(dwDataLength);
    for (uint32_t i = 0; i < dwDataLength; i++)
    {
        m_dataField[i] = a_rData[i + ptr];
    }
}

DTO::~DTO()
{

}
