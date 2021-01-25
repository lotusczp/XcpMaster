#ifndef PACKETFACTORY_H
#define PACKETFACTORY_H

#include <QVector>
#include "XcpMaster.h"
#include "XcpPacket.h"
#include "CmdPacket.h"
#include "CmdPacketConnect.h"
#include "DAQPackets.h"
#include "CmdPacketGetSeed.h"

class PacketFactory
{
public:
    PacketFactory(XcpMaster &a_rMaster);
    virtual ~PacketFactory();

    XcpPacket* createConnectPacket(CmdPacketConnect::ConnectMode a_eMode);
    XcpPacket* createDisconnectPacket();
    XcpPacket* createGetStatusPacket();
    XcpPacket* createSynchPacket();
    XcpPacket* createSetMtaPacket(uint32_t a_dwAddress, uint8_t a_byExtension, bool a_bIsLittleEndian);
    XcpPacket* createUploadPacket(uint8_t a_byNumberOfElements);
    XcpPacket* createShortUploadPacket(uint8_t a_byNumberOfElements, uint32_t a_dwAddress, uint8_t a_byAddressExtension, bool a_bIsLittleEndian);
    XcpPacket* createFreeDaqPacket();
    XcpPacket* createAllocDaqPacket(uint16_t a_wDaqCount, bool a_bIsLittleEndian);
    XcpPacket* createAllocOdtPacket(uint16_t a_wDaqListNumber, uint8_t a_byOdtCount, bool a_bIsLittleEndian);
    XcpPacket* createAllocOdtEntryPacket(uint16_t a_wDaqListNumber, uint8_t a_byOdtNumber, uint8_t a_byOdtEntriesCount, bool a_bIsLittleEndian);
    XcpPacket* createSetDaqPtrPacket(uint16_t a_wDaqListNumber, uint8_t a_byOdtNumber, uint8_t a_byOdtEntryNumber, bool a_bIsLittleEndian);
    XcpPacket* createWriteDaqPacket(uint8_t a_byBitOffset, uint8_t a_bySize, uint8_t a_byAddressExtension, uint32_t a_dwAddress, bool a_bIsLittleEndian);
    XcpPacket* createSetDaqListModePacket(uint8_t a_byMode, uint16_t a_wDaqListNumber, uint16_t a_wEventChannel, uint8_t a_byPrescaler, uint8_t a_byPriority, bool a_bIsLittleEndian);
    XcpPacket* createStartStopDaqListPacket(uint8_t a_byMode, uint16_t a_wDaqListNumber, bool a_bIsLittleEndian);
    XcpPacket* createStartStopSyncPacket(StartStopSynchPacket::Mode a_eMode);
    XcpPacket* createGetSeedPacket(CmdPacketGetSeed::Mode a_eMode, CmdPacketGetSeed::Resource a_eResource);
    XcpPacket* createGetDaqProcessorInfoPacket();
    XcpPacket* createClearDaqListPacket(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian);
    XcpPacket* createDownloadPacket(uint8_t a_byNumOfDataElements, uint32_t a_dwData, bool a_bIsLittleEndian);
    QVector<XcpPacket*> createUnlockPackets(const QVector<uint8_t>& a_rKey);


    XcpPacket* deserializeIncomingFromSlave(const QVector<uint8_t>& a_rData, CmdPacket* a_pLastSentCommand);

private:
    XcpPacket* createResponsePacket(const QVector<uint8_t>& a_rData, CmdPacket* a_pLastSentCommand);
    XcpPacket* createErrorPacket(const QVector<uint8_t>& a_rData, CmdPacket* a_pLastSentCommand);
    XcpPacket* deserializeIncomingDaq(const QVector<uint8_t>& a_rData);

private:
    XcpMaster   &m_rMaster;
};

#endif // PACKETFACTORY_H
