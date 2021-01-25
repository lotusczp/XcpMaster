#ifndef XCPMASTER_H
#define XCPMASTER_H

#include <QObject>
#include <QVector>

#include "XcpMessage.h"
#include "CmdPacket.h"
#include "XcpMessage.h"
#include "CmdPacketConnect.h"
#include "DAQ.h"
#include "DAQPackets.h"
#include "CmdPacketGetSeed.h"
#include "MessageFactory.h"

typedef uint32_t(*XCP_GetAvailablePrivilegesPtr_t)(uint8_t* AvailablePrivilege);
typedef uint32_t(*XCP_ComputeKeyFromSeedPtr_t)(uint8_t RequestedPrivilege, uint8_t ByteLenghtSeed, uint8_t* PointerToSeed, uint8_t* ByteLengthKey, uint8_t* PointerToKey);

class IncomingPacketHandler;
class PacketFactory;

class XcpMaster : public QObject
{
    Q_OBJECT

public:
    enum TransportLayer
    {
        CAN,
        ETHERNET,
        USB,
        FLEXRAY
    };

    struct SlaveProperties
    {
        bool CAL_PG;
        bool DAQ;
        bool STIM;
        bool PGM;

        bool byteOrder;
        uint8_t addressGranularity;
        bool slaveBlockMode;
        bool optionalData;

        uint16_t maxDto;
        uint8_t maxCto;
        uint8_t protocolLayerVersion;
        uint8_t transportLayerVersion;

        struct
        {
            bool configType;
            bool prescalerSupported;
            bool resumeSupported;
            bool bitStimSupported;
            bool timeStampSupported;
            bool pidOffSupported;
            uint8_t overloadIndicationMode;
            uint8_t optimisationType;
            uint8_t addressExtensionType;
            uint8_t identificationFieldType;
            uint16_t maxDaq;
            uint8_t minDaq;
            uint16_t maxEventChannel;
            uint8_t timestampSize;

        } DaqProperties;
    };

public:
    XcpMaster(TransportLayer a_eTransportlayer);
    virtual ~XcpMaster();

    const SlaveProperties& getSlaveProperties() const;
    void setSlaveProperties(const SlaveProperties& a_rProperties);

    XcpMessage* createConnectMessage(CmdPacketConnect::ConnectMode a_eMode);
    XcpMessage* createDisconnectMessage();
    XcpMessage* createGetStatusMessage();
    XcpMessage* createSynchMessage();
    XcpMessage* createSetMtaMessage(uint32_t a_dwAddress, uint8_t a_byExtension);
    XcpMessage* createUploadMessage(uint8_t a_byNumberOfElements);
    XcpMessage* createShortUploadMessage(uint8_t a_byNumberOfElements, uint32_t a_dwAddress, uint8_t a_byAddressExtension);
    XcpMessage* createFreeDaqMessage();
    XcpMessage* createAllocDaqMessage(uint16_t a_wDaqCount);
    XcpMessage* createAllocOdtMessage(uint16_t a_wDaqListNumber, uint8_t a_byOdtCount);
    XcpMessage* createAllocOdtEntryMessage(uint16_t a_wDaqListNumber, uint8_t a_byOdtNumber, uint8_t a_byOdtEntryCount);
    XcpMessage* createSetDaqPtrMessage(uint16_t a_wDaqListNumber, uint8_t a_byOdtNumber, uint8_t a_byOdtEntryNumber);
    XcpMessage* createWriteDaqMessage(uint8_t a_byBitOffset, uint8_t a_byElementSize, uint8_t a_byAddressExtension, uint32_t a_dwAddress);
    XcpMessage* createSetDaqListModeMessage(uint8_t a_byMode, uint16_t a_wDaqListNumber, uint16_t a_wEventChannel, uint8_t a_byPrescaler, uint8_t a_byPriority);
    XcpMessage* createStartStopDaqListMessage(StartStopDaqListPacket::Mode a_eMode, uint16_t a_wDaqListNumber);
    XcpMessage* createStartStopSynchMessage(StartStopSynchPacket::Mode a_eMode);
    XcpMessage* createGetSeedMessage(CmdPacketGetSeed::Mode a_eMode, CmdPacketGetSeed::Resource a_eResource);
    XcpMessage* createGetDaqProcessorInfoMessage();
    XcpMessage* createClearDaqListMessage(uint16_t a_wDaqListNumber);
    XcpMessage* createDownloadMessage(uint8_t a_byNumOfDataElements, uint32_t a_dwData);
    QVector<XcpMessage*> createUnlockMessages();

    void deserializeMessage(const QVector<uint8_t> &a_rData);

    DaqLayout& getDaqLayout();
    void setDaqLayout(const DaqLayout &a_rDaqLayout);

    void handleSentMessage(XcpMessage *a_pMessage);
    CmdPacket* getLastSentCmd();
    bool isCommandQueueEmpty() const;

    void emitSendUploadByteArray(const QVector<uint8_t> &a_rBytes);
    void emitSendOdtEntryValue(uint16_t a_wDaqIndex, uint8_t a_byOdtIndex, uint32_t a_dwOdtEntryIndex, qint64 a_timestamp, double value);

    void setSeedAndKeyFunctions(XCP_GetAvailablePrivilegesPtr_t GetAvailablePrivilegesPtr, XCP_ComputeKeyFromSeedPtr_t ComputeKeyPtr);
    XCP_ComputeKeyFromSeedPtr_t getComputeKeyPtr();
    XCP_GetAvailablePrivilegesPtr_t getAvailablePrivilegesPtr();

signals:
    void sendUploadByteArray(QVector<uint8_t> bytes);
    void sendOdtEntryValue(uint16_t a_wDaqIndex, uint8_t a_byOdtIndex, uint32_t a_dwOdtEntryIndex, qint64 a_timestamp, double value);

private:
    XcpMaster() {}

private:
    QVector<CmdPacket*>             m_queueSentCommand;
    IncomingPacketHandler           *m_pIncomingPacketHandler;
    PacketFactory                   *m_pPacketFactory;
    MessageFactory                  *m_pMessageFactory;
    SlaveProperties                 m_slaveProperties;
    DaqLayout                       m_DaqLayout;
    XCP_GetAvailablePrivilegesPtr_t m_getAvailablePrivileges;
    XCP_ComputeKeyFromSeedPtr_t     m_computeKeyFromSeed;
};

#endif // XCPMASTER_H
