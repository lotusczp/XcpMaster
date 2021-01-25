#include "XcpMaster.h"
#include <QDebug>
#include "IncomingPacketHandler.h"
#include "PacketFactory.h"
#include "transport/can/CanMessageFactory.h"
#include "transport/ethernet/EthernetMessageFactory.h"

XcpMaster::XcpMaster(XcpMaster::TransportLayer a_eTransportlayer)
{
    switch (a_eTransportlayer)
    {
    case TransportLayer::ETHERNET:
        m_pMessageFactory = new EthernetMessageFactory();
        break;
    case TransportLayer::CAN:
        m_pMessageFactory = new CanMessageFactory();
        break;
    default:
        m_pMessageFactory = nullptr;
        break;
    }

    m_pPacketFactory = new PacketFactory(*this);
    m_pIncomingPacketHandler = new IncomingPacketHandler(*this);

    m_getAvailablePrivileges = nullptr;
    m_computeKeyFromSeed = nullptr;
}

XcpMaster::~XcpMaster()
{
    qDeleteAll(m_queueSentCommand);
    m_queueSentCommand.clear();

    delete m_pIncomingPacketHandler;
    delete m_pPacketFactory;
    delete m_pMessageFactory;
}

const XcpMaster::SlaveProperties &XcpMaster::getSlaveProperties() const
{
    return m_slaveProperties;
}

void XcpMaster::setSlaveProperties(const XcpMaster::SlaveProperties &a_rProperties)
{
    m_slaveProperties = a_rProperties;
}

XcpMessage *XcpMaster::createConnectMessage(CmdPacketConnect::ConnectMode a_eMode)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createConnectPacket(a_eMode));
}

XcpMessage *XcpMaster::createDisconnectMessage()
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createDisconnectPacket());
}

XcpMessage *XcpMaster::createSynchMessage()
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createSynchPacket());
}

XcpMessage *XcpMaster::createSetMtaMessage(uint32_t a_dwAddress, uint8_t a_byExtension)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createSetMtaPacket(a_dwAddress, a_byExtension, m_slaveProperties.byteOrder==0));
}

XcpMessage *XcpMaster::createUploadMessage(uint8_t a_byNumberOfElements)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createUploadPacket(a_byNumberOfElements));
}

XcpMessage *XcpMaster::createShortUploadMessage(uint8_t a_byNumberOfElements, uint32_t a_dwAddress, uint8_t a_byAddressExtension)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createShortUploadPacket(a_byNumberOfElements, a_dwAddress, a_byAddressExtension, m_slaveProperties.byteOrder==0));
}

XcpMessage *XcpMaster::createFreeDaqMessage()
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createFreeDaqPacket());
}

XcpMessage *XcpMaster::createAllocDaqMessage(uint16_t a_wDaqCount)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createAllocDaqPacket(a_wDaqCount, m_slaveProperties.byteOrder==0));
}

XcpMessage *XcpMaster::createAllocOdtMessage(uint16_t a_wDaqListNumber, uint8_t a_byOdtCount)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createAllocOdtPacket(a_wDaqListNumber, a_byOdtCount, m_slaveProperties.byteOrder==0));
}

XcpMessage *XcpMaster::createAllocOdtEntryMessage(uint16_t a_wDaqListNumber, uint8_t a_byOdtNumber, uint8_t a_byOdtEntryCount)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createAllocOdtEntryPacket(a_wDaqListNumber, a_byOdtNumber, a_byOdtEntryCount, m_slaveProperties.byteOrder==0));
}

XcpMessage *XcpMaster::createSetDaqPtrMessage(uint16_t a_wDaqListNumber, uint8_t a_byOdtNumber, uint8_t a_byOdtEntryNumber)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createSetDaqPtrPacket(a_wDaqListNumber, a_byOdtNumber, a_byOdtEntryNumber, m_slaveProperties.byteOrder==0));
}

XcpMessage *XcpMaster::createWriteDaqMessage(uint8_t a_byBitOffset, uint8_t a_byElementSize, uint8_t a_byAddressExtension, uint32_t a_dwAddress)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createWriteDaqPacket(a_byBitOffset, a_byElementSize, a_byAddressExtension, a_dwAddress, m_slaveProperties.byteOrder==0));
}

XcpMessage *XcpMaster::createSetDaqListModeMessage(uint8_t a_byMode, uint16_t a_wDaqListNumber, uint16_t a_wEventChannel, uint8_t a_byPrescaler, uint8_t a_byPriority)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createSetDaqListModePacket(a_byMode, a_wDaqListNumber, a_wEventChannel, a_byPrescaler, a_byPriority, m_slaveProperties.byteOrder==0));
}

XcpMessage *XcpMaster::createStartStopDaqListMessage(StartStopDaqListPacket::Mode a_eMode, uint16_t a_wDaqListNumber)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createStartStopDaqListPacket(a_eMode, a_wDaqListNumber, m_slaveProperties.byteOrder==0));
}

XcpMessage *XcpMaster::createStartStopSynchMessage(StartStopSynchPacket::Mode a_eMode)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createStartStopSyncPacket(a_eMode));
}

XcpMessage *XcpMaster::createGetSeedMessage(CmdPacketGetSeed::Mode a_eMode, CmdPacketGetSeed::Resource a_eResource)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createGetSeedPacket(a_eMode, a_eResource));
}

XcpMessage *XcpMaster::createGetDaqProcessorInfoMessage()
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createGetDaqProcessorInfoPacket());
}

XcpMessage *XcpMaster::createClearDaqListMessage(uint16_t a_wDaqListNumber)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createClearDaqListPacket(a_wDaqListNumber, m_slaveProperties.byteOrder==0));
}

XcpMessage *XcpMaster::createDownloadMessage(uint8_t a_byNumOfDataElements, uint32_t a_dwData)
{
    return m_pMessageFactory->createMessage(m_pPacketFactory->createDownloadPacket(a_byNumOfDataElements, a_dwData, m_slaveProperties.byteOrder==0));
}

QVector<XcpMessage *> XcpMaster::createUnlockMessages()
{
    QVector<XcpMessage*> retval;
    QVector<XcpPacket*> packets = m_pPacketFactory->createUnlockPackets(m_pIncomingPacketHandler->getUnlockKey());
    foreach(XcpPacket* pPacket, packets) {
        retval.append(m_pMessageFactory->createMessage(pPacket));
    }

    return retval;
}

void XcpMaster::deserializeMessage(const QVector<uint8_t> &a_rData)
{
    CmdPacket* LastCommand = nullptr;
    if (m_queueSentCommand.size() > 0)
    {
        LastCommand = m_queueSentCommand.front();
    }

    QVector<uint8_t> packetBytes = m_pMessageFactory->getPacketBytes(a_rData);

    XcpPacket* pPacket = m_pPacketFactory->deserializeIncomingFromSlave(packetBytes, LastCommand);

    if(pPacket) {
        m_pIncomingPacketHandler->handle(pPacket);
        qDebug() << "---------------------------------------------\n";
        if (m_queueSentCommand.size() > 0 && pPacket->getPid() > 0xFB) //do not pop if this was a DAQ packet
        {
            CmdPacket *pCmdPacket = m_queueSentCommand[0];
            m_queueSentCommand.pop_front();
            delete pCmdPacket;
        }
        delete pPacket;
        return;
    }
    qDebug() << "couldnt deserialise the message\n";
    qDebug() << "---------------------------------------------\n";
    if (m_queueSentCommand.size() > 0)
    {
        CmdPacket *pCmdPacket = m_queueSentCommand[0];
        m_queueSentCommand.pop_front();
        delete pCmdPacket;
    }

    return;
}

DaqLayout &XcpMaster::getDaqLayout()
{
    return m_DaqLayout;
}

void XcpMaster::setDaqLayout(const DaqLayout &a_rDaqLayout)
{
    m_DaqLayout = a_rDaqLayout;
}

void XcpMaster::handleSentMessage(XcpMessage *a_pMessage)
{
    CmdPacket* pToAdd = dynamic_cast<CmdPacket*>(a_pMessage->getPacket());
    if(pToAdd) {
        m_queueSentCommand.push_back(pToAdd);
    }
    else {
        // Won't need any more, delete it
        if(a_pMessage) delete a_pMessage;
    }
}

CmdPacket *XcpMaster::getLastSentCmd()
{
    if(m_queueSentCommand.isEmpty()) return nullptr;
    return m_queueSentCommand.front();
}

bool XcpMaster::isCommandQueueEmpty() const
{
    return m_queueSentCommand.isEmpty();
}

void XcpMaster::emitSendUploadByteArray(const QVector<uint8_t> &a_rBytes)
{
    emit sendUploadByteArray(a_rBytes);
}

void XcpMaster::emitSendOdtEntryValue(uint16_t a_wDaqIndex, uint8_t a_byOdtIndex, uint32_t a_dwOdtEntryIndex, qint64 a_timestamp, double value)
{
    emit sendOdtEntryValue(a_wDaqIndex, a_byOdtIndex, a_dwOdtEntryIndex, a_timestamp, value);
}

void XcpMaster::setSeedAndKeyFunctions(XCP_GetAvailablePrivilegesPtr_t GetAvailablePrivilegesPtr, XCP_ComputeKeyFromSeedPtr_t ComputeKeyPtr)
{
    m_getAvailablePrivileges = GetAvailablePrivilegesPtr;
    m_computeKeyFromSeed = ComputeKeyPtr;
}

XCP_ComputeKeyFromSeedPtr_t XcpMaster::getComputeKeyPtr()
{
    return m_computeKeyFromSeed;
}

XCP_GetAvailablePrivilegesPtr_t XcpMaster::getAvailablePrivilegesPtr()
{
    return m_getAvailablePrivileges;
}
