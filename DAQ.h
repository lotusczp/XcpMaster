#ifndef DAQ_H
#define DAQ_H

#include <QVector>
#include "DTO.h"

enum MeasurementDataTypes
{
    eInt8 = 0,
    eUint8,
    eInt16,
    eUint16,
    eInt32,
    eUint32,
    eFloat,
    eDouble,
    eInt64,
    eUint64,
};

class OdtEntry
{
public:
    OdtEntry();
    OdtEntry(uint32_t a_dwAddress, uint8_t a_byAddressExtension, uint8_t a_byLength);
    OdtEntry(const OdtEntry& other);
    uint32_t getAddress() const {return m_dwAddress;}
    void setAddress(uint32_t a_dwAddress) {m_dwAddress = a_dwAddress;}
    uint8_t getAddressExtension() const {return m_byAddressExtension;}
    void setAddressExtension(uint8_t a_byAddressExtension) {m_byAddressExtension = a_byAddressExtension;}
    uint8_t getLength() const {return m_byLength;}
    void setDataType(uint8_t a_byDataType);
    uint8_t getDataType() const {return m_byDataType;}

private:
    uint32_t    m_dwAddress;
    uint8_t     m_byAddressExtension;
    uint8_t     m_byLength;
    uint8_t     m_byDataType;
};

class ODT
{
public:
    ODT();
    ODT(const ODT& other);
    ~ODT();
    void addEntry(OdtEntry a_rEntry);
    OdtEntry& getEntry(uint32_t a_dwIndex);
    uint32_t getOdtSize() const;
    uint32_t getNumberOfEntries() const;
    bool isFirst() const;
    void setFirst(bool a_bIsFirst);

private:
    QVector<OdtEntry> m_listEntry;
    bool m_bIsFirst;
};

class DAQ : public DTO
{
public:
    DAQ() : DTO() {}
    DAQ(const DAQ& other);
    virtual ~DAQ();
    void addOdt(ODT a_Odt);
    ODT& getOdt(uint32_t a_dwIndex);
    void setMode(uint8_t a_byMode) {m_byMode = a_byMode;}
    uint8_t getMode() const {return m_byMode;}
    uint16_t getEventChannel() const {return m_wEventChannel;}
    uint8_t getPrescaler() const {return m_byPrescaler;}
    uint8_t getPriority() const {return m_byPriority;}
    void setEventChannel(uint16_t a_wEventChannel) {m_wEventChannel = a_wEventChannel;}
    void setPrescaler(uint8_t a_byPrescaler) {m_byPrescaler = a_byPrescaler;}
    void setPriority(uint8_t a_byPriority) {m_byPriority = a_byPriority;}
    uint16_t getNumberOfOdts() const {return (uint16_t)m_listOdt.size();}
    uint8_t getFirstPid() {return m_byFirstPid;}
    void setFirstPid(uint8_t a_byFirstPid) {m_byFirstPid = a_byFirstPid;}
    void setLastTimestamp(uint32_t a_dwTimestamp) {m_dwLastTimestamp = a_dwTimestamp;}
    uint32_t getLastTimestamp() {return m_dwLastTimestamp;}

private:
    QVector<ODT>    m_listOdt;
    uint8_t         m_byMode;
    uint16_t        m_wEventChannel;
    uint8_t         m_byPrescaler;
    uint8_t         m_byPriority;
    uint8_t         m_byFirstPid;
    uint32_t        m_dwLastTimestamp;
};

class DaqLayout
{
public:
    DaqLayout() : m_bInitialized(false) {}
    DaqLayout(const DaqLayout &other);
    ~DaqLayout();
    void addDaq(DAQ a_daq) {m_listDaq.push_back(a_daq);}
    void setDaq(unsigned int a_nId, DAQ a_daq);
    DAQ& getDaq(uint32_t a_dwIndex) {return m_listDaq[a_dwIndex];}
    uint16_t getNumberOfDaqLists() const {return (uint16_t)m_listDaq.size();}
    bool calcDaqNumberFromAbsPid(uint8_t a_byPid, uint16_t &a_rDaqNumber);
    bool calcOdtNumberFromAbsPid(uint8_t a_byPid, uint8_t &a_rOdtNumber);
    bool getOdtFromAbsolutePid(uint8_t a_byPid, ODT &a_rOdt);
    bool isInitialized() const {return m_bInitialized;}
    void setInitialized(bool a_bInitialized) {m_bInitialized = a_bInitialized;}

private:
    QVector<DAQ>    m_listDaq;
    bool            m_bInitialized;
};

#endif // DAQ_H
