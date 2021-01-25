#include "DAQ.h"

#include <QDebug>

OdtEntry::OdtEntry()
{
    m_dwAddress = 0;
    m_byAddressExtension = 0;
    m_byLength = 0;
    m_byDataType = 0;
}

OdtEntry::OdtEntry(uint32_t a_dwAddress, uint8_t a_byAddressExtension, uint8_t a_byLength)
{
    m_dwAddress = a_dwAddress;
    m_byAddressExtension = a_byAddressExtension;
    m_byLength = a_byLength;
}

OdtEntry::OdtEntry(const OdtEntry &other)
{
    m_dwAddress = other.m_dwAddress;
    m_byAddressExtension = other.m_byAddressExtension;
    m_byLength = other.m_byLength;
    m_byDataType = other.m_byDataType;
}

void OdtEntry::setDataType(uint8_t a_byDataType)
{
    m_byDataType = a_byDataType;
    switch (m_byDataType)
    {
    case MeasurementDataTypes::eInt8:
    case MeasurementDataTypes::eUint8:
        m_byLength = 1;
        break;
    case MeasurementDataTypes::eInt16:
    case MeasurementDataTypes::eUint16:
        m_byLength = 2;
        break;
    case MeasurementDataTypes::eInt32:
    case MeasurementDataTypes::eUint32:
    case MeasurementDataTypes::eFloat:
        m_byLength = 4;
        break;
    case MeasurementDataTypes::eDouble:
    case MeasurementDataTypes::eInt64:
    case MeasurementDataTypes::eUint64:
        m_byLength = 8;
        break;
    default:
        m_byLength = 0; //undefined data type = error
        break;
    }
}

ODT::ODT()
{
    m_bIsFirst = false;
}

ODT::ODT(const ODT &other)
    : m_listEntry(other.m_listEntry)
{
    m_bIsFirst = other.m_bIsFirst;
}

ODT::~ODT()
{
    m_listEntry.clear();
}

void ODT::addEntry(OdtEntry a_rEntry)
{
    m_listEntry.push_back(a_rEntry);
}

OdtEntry &ODT::getEntry(uint32_t a_dwIndex)
{
    return m_listEntry[a_dwIndex];
}

uint32_t ODT::getOdtSize() const
{
    uint32_t dwSize = 0;
    foreach(OdtEntry odtEntry, m_listEntry) {
        dwSize += odtEntry.getLength();
    }
    return dwSize;
}

uint32_t ODT::getNumberOfEntries() const
{
    return (uint32_t)m_listEntry.size();
}

bool ODT::isFirst() const
{
    return m_bIsFirst;
}

void ODT::setFirst(bool a_bIsFirst)
{
    m_bIsFirst = a_bIsFirst;
}

DAQ::DAQ(const DAQ &other)
    : DTO(),
      m_listOdt(other.m_listOdt)
{
    m_byMode = other.m_byMode;
    m_wEventChannel = other.m_wEventChannel;
    m_byPrescaler = other.m_byPrescaler;
    m_byPriority = other.m_byPriority;
    m_byFirstPid = other.m_byFirstPid;
    m_dwLastTimestamp = other.m_dwLastTimestamp;
}

DAQ::~DAQ()
{
    m_listOdt.clear();
}

void DAQ::addOdt(ODT a_Odt)
{
    if (m_listOdt.size() == 0)
    {
        a_Odt.setFirst(true);
    }
    m_listOdt.push_back(a_Odt);
}

ODT &DAQ::getOdt(uint32_t a_dwIndex)
{
    return m_listOdt[a_dwIndex];
}

DaqLayout::DaqLayout(const DaqLayout &other)
    : m_listDaq(other.m_listDaq)
{
    m_bInitialized = other.m_bInitialized;
}

DaqLayout::~DaqLayout()
{
    m_listDaq.clear();
}

void DaqLayout::setDaq(unsigned int a_nId, DAQ a_daq)
{
    if(a_nId < m_listDaq.size()) {
        m_listDaq[a_nId] = a_daq;
    }
}

bool DaqLayout::calcDaqNumberFromAbsPid(uint8_t a_byPid, uint16_t &a_rDaqNumber)
{
    for(int i=0; i<getNumberOfDaqLists(); i++) {
        uint8_t t1 = getDaq(i).getFirstPid();
        for (int j = 0; j < getDaq(i).getNumberOfOdts(); j++)
        {
            if (t1 == a_byPid)
            {
                a_rDaqNumber = i;
                return true;
            }
            t1++;
        }
    }

    return false;
}

bool DaqLayout::calcOdtNumberFromAbsPid(uint8_t a_byPid, uint8_t &a_rOdtNumber)
{
    for(int i=0; i<getNumberOfDaqLists(); i++) {
        uint8_t t1 = getDaq(i).getFirstPid();
        for (int j = 0; j < getDaq(i).getNumberOfOdts(); j++)
        {
            if (t1 == a_byPid)
            {
                a_rOdtNumber = j;
                return true;
            }
            t1++;
        }
    }

    return false;
}

bool DaqLayout::getOdtFromAbsolutePid(uint8_t a_byPid, ODT &a_rOdt)
{
    for(int i=0; i<getNumberOfDaqLists(); i++) {
        uint8_t t1 = getDaq(i).getFirstPid();
        for (int j = 0; j < getDaq(i).getNumberOfOdts(); j++)
        {
            if (t1 == a_byPid)
            {
                a_rOdt = getDaq(i).getOdt(j);
                return true;
            }
            t1++;
        }
    }

    return false;
}
