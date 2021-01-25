#include "PacketFactory.h"

#include <QDebug>
#include "DTO.h"
#include "ResPacketConnect.h"
#include "ResPacketGetSeed.h"
#include "ResPacketGetStatus.h"
#include "ResPacketUpload.h"
#include "ResPacketUnlock.h"
#include "DAQPackets.h"
#include "ErrorPacket.h"
#include "ErrorPacketSync.h"
#include "ErrorPacketAccessLocked.h"
#include "ErrorPacketCmdUnknown.h"
#include "ErrorPacketMemoryOverflow.h"
#include "ErrorPacketOutOfRange.h"
#include "ErrorPacketSequence.h"
#include "CmdPacketDisconnect.h"
#include "CmdPacketGetStatus.h"
#include "CmdPacketSync.h"
#include "CmdPacketSetMta.h"
#include "CmdPacketUpload.h"
#include "CmdPacketUnlock.h"
#include "CmdPacketShortUpload.h"
#include "CmdPacketDownload.h"


PacketFactory::PacketFactory(XcpMaster &a_rMaster)
    : m_rMaster(a_rMaster)
{

}

PacketFactory::~PacketFactory()
{

}

XcpPacket *PacketFactory::createConnectPacket(CmdPacketConnect::ConnectMode a_eMode)
{
    return new CmdPacketConnect(a_eMode);
}

XcpPacket *PacketFactory::createDisconnectPacket()
{
    return new CmdPacketDisconnect();
}

XcpPacket *PacketFactory::createGetStatusPacket()
{
    return new CmdPacketGetStatus();
}

XcpPacket *PacketFactory::createSynchPacket()
{
    return new CmdPacketSync();
}

XcpPacket *PacketFactory::createSetMtaPacket(uint32_t a_dwAddress, uint8_t a_byExtension, bool a_bIsLittleEndian)
{
    CmdPacketSetMta* pPacket = new CmdPacketSetMta();
    pPacket->setAddress(a_dwAddress, a_bIsLittleEndian);
    pPacket->setAddressExtension(a_byExtension);
    return pPacket;
}

XcpPacket *PacketFactory::createUploadPacket(uint8_t a_byNumberOfElements)
{
    return new CmdPacketUpload(a_byNumberOfElements);
}

XcpPacket *PacketFactory::createShortUploadPacket(uint8_t a_byNumberOfElements, uint32_t a_dwAddress, uint8_t a_byAddressExtension, bool a_bIsLittleEndian)
{
    CmdPacketShortUpload* pPacket = new CmdPacketShortUpload();
    pPacket->setAddress(a_dwAddress, a_bIsLittleEndian);
    pPacket->setAddressExtension(a_byAddressExtension);
    pPacket->setNumberOfDataElements(a_byNumberOfElements);
    return pPacket;
}

XcpPacket *PacketFactory::createFreeDaqPacket()
{
    return new FreeDaqPacket();
}

XcpPacket *PacketFactory::createAllocDaqPacket(uint16_t a_wDaqCount, bool a_bIsLittleEndian)
{
    AllocDaqPacket* pPacket = new AllocDaqPacket();
    pPacket->setDaqCount(a_wDaqCount, a_bIsLittleEndian);
    return pPacket;
}

XcpPacket *PacketFactory::createAllocOdtPacket(uint16_t a_wDaqListNumber, uint8_t a_byOdtCount, bool a_bIsLittleEndian)
{
    AllocOdtPacket* pPacket = new AllocOdtPacket();
    pPacket->setDaqListNumber(a_wDaqListNumber, a_bIsLittleEndian);
    pPacket->setOdtCount(a_byOdtCount);
    return pPacket;
}

XcpPacket *PacketFactory::createAllocOdtEntryPacket(uint16_t a_wDaqListNumber, uint8_t a_byOdtNumber, uint8_t a_byOdtEntriesCount, bool a_bIsLittleEndian)
{
    AllocOdtEntryPacket* pPacket = new AllocOdtEntryPacket();
    pPacket->setDaqListNumber(a_wDaqListNumber, a_bIsLittleEndian);
    pPacket->setOdtNumber(a_byOdtNumber);
    pPacket->setOdtEntriesCount(a_byOdtEntriesCount);
    return pPacket;
}

XcpPacket *PacketFactory::createSetDaqPtrPacket(uint16_t a_wDaqListNumber, uint8_t a_byOdtNumber, uint8_t a_byOdtEntryNumber, bool a_bIsLittleEndian)
{
    SetDaqPtrPacket* pPacket = new SetDaqPtrPacket();
    pPacket->setDaqListNumber(a_wDaqListNumber, a_bIsLittleEndian);
    pPacket->setOdtNumber(a_byOdtNumber);
    pPacket->setOdtEntryNumber(a_byOdtEntryNumber);
    return pPacket;
}

XcpPacket *PacketFactory::createWriteDaqPacket(uint8_t a_byBitOffset, uint8_t a_bySize, uint8_t a_byAddressExtension, uint32_t a_dwAddress, bool a_bIsLittleEndian)
{
    WriteDaqPacket* pPacket = new WriteDaqPacket();
    pPacket->setBitOffset(a_byBitOffset);
    pPacket->setElementSize(a_bySize);
    pPacket->setAddressExtension(a_byAddressExtension);
    pPacket->setAddress(a_dwAddress, a_bIsLittleEndian);
    return pPacket;
}

XcpPacket *PacketFactory::createSetDaqListModePacket(uint8_t a_byMode, uint16_t a_wDaqListNumber, uint16_t a_wEventChannel, uint8_t a_byPrescaler, uint8_t a_byPriority, bool a_bIsLittleEndian)
{
    return new SetDaqListModePacket(a_byMode, a_wDaqListNumber, a_wEventChannel, a_byPrescaler, a_byPriority, a_bIsLittleEndian);
}

XcpPacket *PacketFactory::createStartStopDaqListPacket(uint8_t a_byMode, uint16_t a_wDaqListNumber, bool a_bIsLittleEndian)
{
    return new StartStopDaqListPacket(a_byMode, a_wDaqListNumber, a_bIsLittleEndian);
}

XcpPacket *PacketFactory::createStartStopSyncPacket(StartStopSynchPacket::Mode a_eMode)
{
    return new StartStopSynchPacket(a_eMode);
}

XcpPacket *PacketFactory::createGetSeedPacket(CmdPacketGetSeed::Mode a_eMode, CmdPacketGetSeed::Resource a_eResource)
{
    return new CmdPacketGetSeed(a_eMode, a_eResource);
}

XcpPacket *PacketFactory::createGetDaqProcessorInfoPacket()
{
    return new GetDaqProcessorInfo();
}

XcpPacket *PacketFactory::createClearDaqListPacket(uint16_t a_wDaqListNumber, bool a_bIsLittleEndian)
{
    return new ClearDAQListPacket(a_wDaqListNumber, a_bIsLittleEndian);
}

XcpPacket *PacketFactory::createDownloadPacket(uint8_t a_byNumOfDataElements, uint32_t a_dwData, bool a_bIsLittleEndian)
{
    CmdPacketDownload* pPacket = new CmdPacketDownload();
    pPacket->setNumberOfDataElements(a_byNumOfDataElements);
    pPacket->setDataElements(a_dwData, a_bIsLittleEndian);
    return pPacket;
}

QVector<XcpPacket *> PacketFactory::createUnlockPackets(const QVector<uint8_t> &a_rKey)
{
    return CmdPacketUnlock::createUnlockPackets(a_rKey, m_rMaster.getSlaveProperties().maxCto);
}

XcpPacket *PacketFactory::deserializeIncomingFromSlave(const QVector<uint8_t> &a_rData, CmdPacket *a_pLastSentCommand)
{
    if (a_rData.size() > 0) { //Handle empty messages
        uint8_t byPid = a_rData[0];
        switch (byPid)
        {
        case CTO::RES:
            return createResponsePacket(a_rData, a_pLastSentCommand);
        case CTO::EV:
            break;
        case CTO::ERR:
            return createErrorPacket(a_rData, a_pLastSentCommand);
        case CTO::SERV:
            break;
        default:
            if (byPid >= 0x00 && byPid <= 0xFB)
            {
                return deserializeIncomingDaq(a_rData);
            }
            break;
        }
    }
    return nullptr;
}

XcpPacket *PacketFactory::createResponsePacket(const QVector<uint8_t> &a_rData, CmdPacket *a_pLastSentCommand)
{
    if(a_pLastSentCommand) {
        uint8_t byLastCommandPID = a_pLastSentCommand->getPid();
        switch (byLastCommandPID)
        {
        case CTO::CONNECT:
            return ResPacketConnect::deserialize(a_rData);
        case CTO::DISCONNECT:
            return new ResPacket();
        case CTO::GET_STATUS:
            return ResPacketGetStatus::deserialize(a_rData);
        case CTO::UPLOAD:
            return ResPacketUpload::deserialize(a_rData, m_rMaster.getSlaveProperties().addressGranularity);
        case CTO::SHORT_UPLOAD:
            return ResPacketUpload::deserialize(a_rData, m_rMaster.getSlaveProperties().addressGranularity);
        case CTO::SET_MTA:
            return new ResPacket();
        case CTO::START_STOP_DAQ_LIST:
            return StartStopDaqListPositiveResponse::deserialize(a_rData);
        case CTO::GET_SEED:
            return ResPacketGetSeed::deserialize(a_rData);
        case CTO::UNLOCK:
            return ResPacketUnlock::deserialize(a_rData);
        case CTO::GET_DAQ_PROCESSOR_INFO:
            return GetDaqProcessorInfoResponse::deserialize(a_rData);
        default:
            return new ResPacket();
        }
    }
    qDebug() << "Internal error: Last sent command is a nullptr\a\n";
    return nullptr;
}

XcpPacket *PacketFactory::createErrorPacket(const QVector<uint8_t> &a_rData, CmdPacket *a_pLastSentCommand)
{
    if(a_pLastSentCommand) {
        uint8_t byErrorCode = a_rData[1];
        uint8_t byLastCommandPID = a_pLastSentCommand->getPid();
        switch (byLastCommandPID)
        {
        case ErrorPacket::ErrorCodes::ERR_CMD_SYNCH:
            return new ErrorPacketSync();
        case ErrorPacket::ErrorCodes::ERR_ACCESS_LOCKED:
            return new ErrorPacketAccessLocked();
        case ErrorPacket::ErrorCodes::ERR_OUT_OF_RANGE:
            return new ErrorPacketOutOfRange();
        case ErrorPacket::ErrorCodes::ERR_SEQUENCE:
            return new ErrorPacketSequence();
        case ErrorPacket::ErrorCodes::ERR_MEMORY_OVERFLOW:
            return new ErrorPacketMemoryOverflow();
        case ErrorPacket::ErrorCodes::ERR_CMD_UNKNOWN:
            return new ErrorPacketCmdUnknown();
        default:
            qDebug() << "Deserialization error: Unhandled errorcode\n";
            return nullptr;
        }
    }
    qDebug() << "Internal error: Last sent command is a nullptr\a\n";
    return nullptr;
}

XcpPacket *PacketFactory::deserializeIncomingDaq(const QVector<uint8_t> &a_rData)
{
    return new DTO(a_rData, m_rMaster.getSlaveProperties().DaqProperties.timestampSize, false, m_rMaster.getSlaveProperties().DaqProperties.identificationFieldType, m_rMaster.getDaqLayout());
}
