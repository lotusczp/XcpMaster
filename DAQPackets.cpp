#include "DAQPackets.h"

FreeDaqPacket::FreeDaqPacket()
    : CmdPacket()
{
    m_idField.append(CTO::FREE_DAQ);
}

AllocDaqPacket::AllocDaqPacket()
    : CmdPacket()
{
    m_idField.append(CTO::ALLOC_DAQ);
    m_dataField.resize(3); // Reserve 3 element in data field
    m_dataField[0] = 0;
}

void AllocDaqPacket::setDaqCount(uint16_t a_wDaqCount, bool a_bIsLittleEndian)
{
    uint8_t t1, t2;
    t1 = a_wDaqCount & 0xFF;
    t2 = (a_wDaqCount >> 8) & 0xFF;

    if(a_bIsLittleEndian) {
        m_dataField[1] = t1;
        m_dataField[2] = t2;
    }
    else {
        m_dataField[1] = t2;
        m_dataField[2] = t1;
    }
}

uint16_t AllocDaqPacket::getDaqCount(bool a_bIsLittleEndian)
{
    uint16_t retval;
    uint16_t t1, t2;
    t1 = m_dataField[1];
    t2 = m_dataField[2];

    if(a_bIsLittleEndian) {
        retval = (t2 << 8) | t1;
    }
    else {
        retval = (t1 << 8) | t2;
    }

    return retval;
}

AllocOdtPacket::AllocOdtPacket()
    : CmdPacket()
{
    m_idField.append(CTO::ALLOC_ODT);
    m_dataField.resize(4); // Reserve 4 element in data field
    m_dataField[0] = 0;
}

void AllocOdtPacket::setDaqListNumber(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian)
{
    uint8_t t1, t2;
    t1 = a_wDaqListNumber & 0xFF;
    t2 = (a_wDaqListNumber >> 8) & 0xFF;

    if(a_bIsLittleEndian) {
        m_dataField[1] = t1;
        m_dataField[2] = t2;
    }
    else {
        m_dataField[1] = t2;
        m_dataField[2] = t1;
    }
}

void AllocOdtPacket::setOdtCount(uint8_t a_byOdtCount)
{
    m_dataField[3] = a_byOdtCount;
}

AllocOdtEntryPacket::AllocOdtEntryPacket()
    : CmdPacket()
{
    m_idField.append(CTO::ALLOC_ODT_ENTRY);
    m_dataField.resize(5); // Reserve 5 element in data field
    m_dataField[0] = 0;
}

void AllocOdtEntryPacket::setDaqListNumber(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian)
{
    uint8_t t1, t2;
    t1 = a_wDaqListNumber & 0xFF;
    t2 = (a_wDaqListNumber >> 8) & 0xFF;

    if(a_bIsLittleEndian) {
        m_dataField[1] = t1;
        m_dataField[2] = t2;
    }
    else {
        m_dataField[1] = t2;
        m_dataField[2] = t1;
    }
}

void AllocOdtEntryPacket::setOdtNumber(uint8_t a_byOdtNumber)
{
    m_dataField[3] = a_byOdtNumber;
}

void AllocOdtEntryPacket::setOdtEntriesCount(uint8_t a_byOdtEntriesCount)
{
    m_dataField[4] = a_byOdtEntriesCount;
}

SetDaqPtrPacket::SetDaqPtrPacket()
    : CmdPacket()
{
    m_idField.append(CTO::SET_DAQ_PTR);
    m_dataField.resize(5); // Reserve 5 element in data field
    m_dataField[0] = 0;
}

void SetDaqPtrPacket::setDaqListNumber(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian)
{
    uint8_t t1, t2;
    t1 = a_wDaqListNumber & 0xFF;
    t2 = (a_wDaqListNumber >> 8) & 0xFF;

    if(a_bIsLittleEndian) {
        m_dataField[1] = t1;
        m_dataField[2] = t2;
    }
    else {
        m_dataField[1] = t2;
        m_dataField[2] = t1;
    }
}

void SetDaqPtrPacket::setOdtNumber(uint8_t a_byOdtNumber)
{
    m_dataField[3] = a_byOdtNumber;
}

void SetDaqPtrPacket::setOdtEntryNumber(uint8_t a_byOdtEntryNumber)
{
    m_dataField[4] = a_byOdtEntryNumber;
}

WriteDaqPacket::WriteDaqPacket()
    : CmdPacket()
{
    m_idField.append(CTO::WRITE_DAQ);
    m_dataField.resize(7); // Reserve 7 element in data field
}

void WriteDaqPacket::setBitOffset(uint8_t a_byOffset)
{
    m_dataField[0] = a_byOffset;
}

void WriteDaqPacket::setElementSize(uint8_t a_bySize)
{
    m_dataField[1] = a_bySize;
}

void WriteDaqPacket::setAddressExtension(uint8_t a_byAddressExtension)
{
    m_dataField[2] = a_byAddressExtension;
}

void WriteDaqPacket::setAddress(uint32_t a_dwAddress, bool a_bIsLittleEndian)
{
    uint8_t i1, i2, i3, i4;
    i1 = a_dwAddress & 0xFF;
    i2 = (a_dwAddress >> 8) & 0xFF;
    i3 = (a_dwAddress >> 16) & 0xFF;
    i4 = (a_dwAddress >> 24) & 0xFF;

    if(a_bIsLittleEndian) {
        m_dataField[3] = i1;
        m_dataField[4] = i2;
        m_dataField[5] = i3;
        m_dataField[6] = i4;
    }
    else {
        m_dataField[3] = i4;
        m_dataField[4] = i3;
        m_dataField[5] = i2;
        m_dataField[6] = i1;
    }
}

SetDaqListModePacket::SetDaqListModePacket()
    : CmdPacket()
{
    m_idField.append(CTO::SET_DAQ_LIST_MODE);
    m_dataField.resize(7); // Reserve 7 element in data field
}

SetDaqListModePacket::SetDaqListModePacket(uint8_t a_byMode, uint16_t a_wDaqListNumber, uint16_t a_wEventChannel, uint8_t a_byPrescaler, uint8_t a_byPriority, bool a_bIsLittleEndian)
    : CmdPacket()
{
    m_idField.resize(1);
    m_idField[0] = CTO::SET_DAQ_LIST_MODE;
    m_dataField.resize(7); // Reserve 7 element in data field

    setMode(a_byMode);
    setDaqListNumber(a_wDaqListNumber,a_bIsLittleEndian);
    setEventChannel(a_wEventChannel, a_bIsLittleEndian);
    setTransmissionRatePrescaler(a_byPrescaler);
    setDaqListPriority(a_byPriority);
}

void SetDaqListModePacket::setMode(uint8_t a_byMode)
{
    m_dataField[0] = a_byMode;
}

void SetDaqListModePacket::setDaqListNumber(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian)
{
    uint8_t t1, t2;
    t1 = a_wDaqListNumber & 0xFF;
    t2 = (a_wDaqListNumber >> 8) & 0xFF;

    if(a_bIsLittleEndian) {
        m_dataField[1] = t1;
        m_dataField[2] = t2;
    }
    else {
        m_dataField[1] = t2;
        m_dataField[2] = t1;
    }
}

void SetDaqListModePacket::setEventChannel(uint16_t a_wEventChannel, bool a_bIsLittleEndian)
{
    uint8_t t1, t2;
    t1 = a_wEventChannel & 0xFF;
    t2 = (a_wEventChannel >> 8) & 0xFF;

    if(a_bIsLittleEndian) {
        m_dataField[3] = t1;
        m_dataField[4] = t2;
    }
    else {
        m_dataField[3] = t2;
        m_dataField[4] = t1;
    }
}

void SetDaqListModePacket::setTransmissionRatePrescaler(uint8_t a_byPrescaler)
{
    m_dataField[5] = a_byPrescaler;
}

void SetDaqListModePacket::setDaqListPriority(uint8_t a_byPriority)
{
    m_dataField[6] = a_byPriority;
}

StartStopDaqListPacket::StartStopDaqListPacket()
    : CmdPacket()
{
    m_idField.append(CTO::START_STOP_DAQ_LIST);
    m_dataField.resize(3); // Reserve 3 element in data field
}

StartStopDaqListPacket::StartStopDaqListPacket(uint8_t a_byMode, uint16_t a_wDaqListNumber, bool a_bIsLittleEndian)
    : CmdPacket()
{
    m_idField.append(CTO::START_STOP_DAQ_LIST);
    m_dataField.resize(3); // Reserve 3 element in data field
    setMode(a_byMode);
    setDaqListNumber(a_wDaqListNumber, a_bIsLittleEndian);
}

void StartStopDaqListPacket::setMode(uint8_t a_byMode)
{
    m_dataField[0] = a_byMode;
}

void StartStopDaqListPacket::setDaqListNumber(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian)
{
    uint8_t t1, t2;
    t1 = a_wDaqListNumber & 0xFF;
    t2 = (a_wDaqListNumber >> 8) & 0xFF;

    if(a_bIsLittleEndian) {
        m_dataField[1] = t1;
        m_dataField[2] = t2;
    }
    else {
        m_dataField[1] = t2;
        m_dataField[2] = t1;
    }
}

uint16_t StartStopDaqListPacket::getDaqListNumber(bool a_bIsLittleEndian)
{
    uint16_t retval;
    if(a_bIsLittleEndian) {
        retval = m_dataField[1];
        retval |= (((uint16_t)m_dataField[2])<<8);
    }
    else {
        retval = m_dataField[2];
        retval |= (((uint16_t)m_dataField[1]) << 8);
    }
    return retval;
}

StartStopDaqListPositiveResponse::StartStopDaqListPositiveResponse(const QVector<uint8_t> &a_rData)
    : ResPacket()
{
    m_dataField.resize(1);
    for(int i=0; i<m_dataField.size(); i++)
    {
        m_dataField[i] = a_rData[i+1];
    }
}

uint8_t StartStopDaqListPositiveResponse::getFirstPid()
{
    return m_dataField[0];
}

StartStopDaqListPositiveResponse *StartStopDaqListPositiveResponse::deserialize(const QVector<uint8_t> &a_rData)
{
    return new StartStopDaqListPositiveResponse(a_rData);
}

StartStopSynchPacket::StartStopSynchPacket(StartStopSynchPacket::Mode a_eMode)
    : CmdPacket()
{
    m_idField.append(CTO::START_STOP_SYNCH);
    m_dataField.resize(1); // Reserve 1 element in data field
    setMode(a_eMode);
}

void StartStopSynchPacket::setMode(uint8_t a_byMode)
{
    m_dataField[0] = a_byMode;
}

GetDaqProcessorInfo::GetDaqProcessorInfo()
    : CmdPacket()
{
    m_idField.append(CTO::GET_DAQ_PROCESSOR_INFO);
}

GetDaqProcessorInfoResponse::GetDaqProcessorInfoResponse(const QVector<uint8_t> &a_rData)
    : ResPacket()
{
    m_dataField.resize(7);
    for(int i=0; i<m_dataField.size(); i++) {
        m_dataField[i] = a_rData[i + 1];
    }
}

GetDaqProcessorInfoResponse *GetDaqProcessorInfoResponse::deserialize(const QVector<uint8_t> &a_rData)
{
    return new GetDaqProcessorInfoResponse(a_rData);
}

uint8_t GetDaqProcessorInfoResponse::getDaqProperties()
{
    return m_dataField[0];
}

uint16_t GetDaqProcessorInfoResponse::getMaxDaq(bool a_bIsLittleEndian)
{
    if(a_bIsLittleEndian) {
        return (((uint16_t)m_dataField[2]) << 8) | m_dataField[1];
    }
    else {
        //do byte-swap
        return (((uint16_t)m_dataField[1]) << 8) | m_dataField[2];
    }
}

uint16_t GetDaqProcessorInfoResponse::getMaxEventChannel(bool a_bIsLittleEndian)
{
    if(a_bIsLittleEndian) {
        return (((uint16_t)m_dataField[4]) << 8) | m_dataField[3];
    }
    else {
        //do byte-swap
        return (((uint16_t)m_dataField[3]) << 8) | m_dataField[4];
    }
}

uint8_t GetDaqProcessorInfoResponse::getMinDaq()
{
    return m_dataField[5];
}

uint8_t GetDaqProcessorInfoResponse::getDaqKeyByte()
{
    return m_dataField[6];
}

ClearDAQListPacket::ClearDAQListPacket(uint16_t a_wDAQListNumber, bool a_bIsLittleEndian)
    : CmdPacket()
{
    m_idField.append(CTO::CLEAR_DAQ_LIST);
    m_dataField.resize(3); // Reserve 3 element in data field
    m_dataField[0] = 0; //Reserved
    setDaqListNumber(a_wDAQListNumber, a_bIsLittleEndian);
}

void ClearDAQListPacket::setDaqListNumber(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian)
{
    uint8_t t1, t2;
    t1 = a_wDaqListNumber & 0xFF;
    t2 = (a_wDaqListNumber >> 8) & 0xFF;

    if(a_bIsLittleEndian) {
        m_dataField[1] = t1;
        m_dataField[2] = t2;
    }
    else {
        m_dataField[1] = t2;
        m_dataField[2] = t1;
    }
}

uint16_t ClearDAQListPacket::getDaqListNumber(bool a_bIsLittleEndian)
{
    if(a_bIsLittleEndian) {
        return (((uint16_t)m_dataField[2]) << 8) | m_dataField[1];
    }
    else {
        //do byte-swap
        return (((uint16_t)m_dataField[1]) << 8) | m_dataField[2];
    }
}
