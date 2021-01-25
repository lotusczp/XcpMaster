#include "IncomingPacketHandler.h"

#include <QString>
#include <QDebug>

IncomingPacketHandler::IncomingPacketHandler(XcpMaster &a_rMaster)
    : m_rMaster(a_rMaster)
{
    m_dwReceivedDtoCount = 0;
    resetSeedAndKey();
}

IncomingPacketHandler::~IncomingPacketHandler()
{

}

void IncomingPacketHandler::handle(XcpPacket *a_pPacket)
{
    ResPacketConnect *pResPacketConnect = dynamic_cast<ResPacketConnect*>(a_pPacket);
    if(pResPacketConnect) {
        handle(*pResPacketConnect);
        return;
    }
    ResPacketGetStatus *pResPacketGetStatus = dynamic_cast<ResPacketGetStatus*>(a_pPacket);
    if(pResPacketGetStatus) {
        handle(*pResPacketGetStatus);
        return;
    }
    ResPacketUpload *pResPacketUpload = dynamic_cast<ResPacketUpload*>(a_pPacket);
    if(pResPacketUpload) {
        handle(*pResPacketUpload);
        return;
    }
    StartStopDaqListPositiveResponse *pStartStopDaqListPositiveResponse = dynamic_cast<StartStopDaqListPositiveResponse*>(a_pPacket);
    if(pStartStopDaqListPositiveResponse) {
        handle(*pStartStopDaqListPositiveResponse);
        return;
    }
    ResPacketGetSeed *pResPacketGetSeed = dynamic_cast<ResPacketGetSeed*>(a_pPacket);
    if(pResPacketGetSeed) {
        handle(*pResPacketGetSeed);
        return;
    }
    ResPacketUnlock *pResPacketUnlock = dynamic_cast<ResPacketUnlock*>(a_pPacket);
    if(pResPacketUnlock) {
        handle(*pResPacketUnlock);
        return;
    }
    GetDaqProcessorInfoResponse *pGetDaqProcessorInfoResponse = dynamic_cast<GetDaqProcessorInfoResponse*>(a_pPacket);
    if(pGetDaqProcessorInfoResponse) {
        handle(*pGetDaqProcessorInfoResponse);
        return;
    }
    // Put ResPacket after all RES packets
    ResPacket *pResPacket = dynamic_cast<ResPacket*>(a_pPacket);
    if(pResPacket) {
        handle(*pResPacket);
    }

    ErrorPacketSync *pErrorPacketSync = dynamic_cast<ErrorPacketSync*>(a_pPacket);
    if(pErrorPacketSync) {
        handle(*pErrorPacketSync);
        return;
    }

    ErrorPacketAccessLocked *pErrorPacketAccessLocked = dynamic_cast<ErrorPacketAccessLocked*>(a_pPacket);
    if(pErrorPacketAccessLocked) {
        handle(*pErrorPacketAccessLocked);
        return;
    }

    ErrorPacketOutOfRange *pErrorPacketOutOfRange = dynamic_cast<ErrorPacketOutOfRange*>(a_pPacket);
    if(pErrorPacketOutOfRange) {
        handle(*pErrorPacketOutOfRange);
        return;
    }

    ErrorPacketSequence *pErrorPacketSequence = dynamic_cast<ErrorPacketSequence*>(a_pPacket);
    if(pErrorPacketSequence) {
        handle(*pErrorPacketSequence);
        return;
    }

    ErrorPacketMemoryOverflow *pErrorPacketMemoryOverflow = dynamic_cast<ErrorPacketMemoryOverflow*>(a_pPacket);
    if(pErrorPacketMemoryOverflow) {
        handle(*pErrorPacketMemoryOverflow);
        return;
    }

    ErrorPacketCmdUnknown *pErrorPacketCmdUnknown = dynamic_cast<ErrorPacketCmdUnknown*>(a_pPacket);
    if(pErrorPacketCmdUnknown) {
        handle(*pErrorPacketCmdUnknown);
        return;
    }

    DTO *pDTO = dynamic_cast<DTO*>(a_pPacket);
    if(pDTO) {
        handle(*pDTO);
        return;
    }
}

void IncomingPacketHandler::handle(ResPacket &a_rPacket)
{
    qDebug() << "General Ack packet received (or an unhandled packet format) PID: " << (int)a_rPacket.getPid();
}

void IncomingPacketHandler::handle(ResPacketConnect &a_rPacket)
{
    XcpMaster::SlaveProperties properties = m_rMaster.getSlaveProperties();

    properties.CAL_PG = ((a_rPacket.getResource()&ResPacketConnect::ResourceParameterBits::CAL_PG) != 0);
    properties.DAQ = ((a_rPacket.getResource()&ResPacketConnect::ResourceParameterBits::DAQ) != 0);
    properties.PGM = ((a_rPacket.getResource()&ResPacketConnect::ResourceParameterBits::PGM) != 0);
    properties.STIM = ((a_rPacket.getResource()&ResPacketConnect::ResourceParameterBits::STIM) != 0);

    properties.byteOrder = ((a_rPacket.getCommModeBasic()&ResPacketConnect::CommModeBasicBits::BYTE_ORDER) != 0);
    properties.addressGranularity = ((a_rPacket.getCommModeBasic()&ResPacketConnect::CommModeBasicBits::ADDRESS_GRANULARITY_BOTH) >> 1);
    properties.slaveBlockMode = ((a_rPacket.getCommModeBasic()&ResPacketConnect::CommModeBasicBits::SLAVE_BLOCK_MODE) != 0);
    properties.optionalData = ((a_rPacket.getCommModeBasic()&ResPacketConnect::CommModeBasicBits::OPTIONAL) != 0);

    properties.maxCto = a_rPacket.getMaxCto();
    properties.maxDto = a_rPacket.getMaxDto(!properties.byteOrder); //at this point we have already set the ByteOrder, true for little endian and false for big
    properties.transportLayerVersion = a_rPacket.getTransportLayerVersion();
    properties.protocolLayerVersion = a_rPacket.getProtocolLayerVersion();

    m_rMaster.setSlaveProperties(properties); //write back Slave properties to the Master

    qDebug()
        << "PID: " << (int)a_rPacket.getPid()
        << " | Resource:" << (int)a_rPacket.getResource()
        << " (CAL/PG: " << properties.CAL_PG << ", "
        << "DAQ: " << properties.DAQ << ", "
        << "STIM: " << properties.STIM << ", "
        << "PGM: " << properties.PGM << ") "
        << " | CommMode:" << (int)a_rPacket.getCommModeBasic()
        << " | MaxCTO:" << (int)properties.maxCto
        << " | MaxDTO:" << (int)properties.maxDto
        << " | ProtocolLayer version:" << (int)properties.protocolLayerVersion
        << " | Transport Layer version:" << (int)properties.transportLayerVersion << "\n";

    qDebug() << "Byte order: " << properties.byteOrder << "\n";
    qDebug() << "Address granularity: " << (int)properties.addressGranularity << "\n";
    qDebug() << "Slave block mode: " << properties.slaveBlockMode << "\n";
    qDebug() << "Optional data: " << properties.optionalData << "\n";
}

void IncomingPacketHandler::handle(ResPacketGetStatus &a_rPacket)
{
    qDebug() << "Receive get status resonse packet";
}

void IncomingPacketHandler::handle(ErrorPacketSync &a_rPacket)
{
    qDebug() << "Receive Sync Error packet";
}

void IncomingPacketHandler::handle(ResPacketUpload &a_rPacket)
{
    qDebug() << "Receive Upload packet";

    m_rMaster.emitSendUploadByteArray(a_rPacket.getDataBytes());
}

void IncomingPacketHandler::handle(ErrorPacketAccessLocked &a_rPacket)
{
    qDebug() << "Error, Access Denied, Seed & Key is required";
}

void IncomingPacketHandler::handle(ErrorPacketOutOfRange &a_rPacket)
{
    qDebug() << a_rPacket.getErrorCode();
    qDebug() << "Error: OUT_OF_RANGE";
}

void IncomingPacketHandler::handle(ErrorPacketSequence &a_rPacket)
{
    qDebug() << "Error: ERR_SEQUENCE";
}

void IncomingPacketHandler::handle(ErrorPacketMemoryOverflow &a_rPacket)
{
    qDebug() << "Error: Memory overflow";
}

void IncomingPacketHandler::handle(StartStopDaqListPositiveResponse &a_rPacket)
{
    if(m_rMaster.getDaqLayout().isInitialized()) {
        qDebug() << "Start/Stop Daq list response | FIRST PID: 0x" + QString::number(a_rPacket.getFirstPid(), 16);
        StartStopDaqListPacket* command = dynamic_cast<StartStopDaqListPacket*>(m_rMaster.getLastSentCmd());
        if(command) {
            DaqLayout& dl = m_rMaster.getDaqLayout();
            DAQ& d = dl.getDaq(command->getDaqListNumber(m_rMaster.getSlaveProperties().byteOrder == 0));
            d.setFirstPid(a_rPacket.getFirstPid());
        }
        else {
            qDebug() << "There was an error while setting the first PID on the DAQListDescriptor";
        }
    }
    else {
        qDebug() << "Warning! Daq layout was not initialized before starting daq transfer.";
    }
}

void IncomingPacketHandler::handle(ResPacketGetSeed &a_rPacket)
{
    qDebug() << "GetSeedResponse";
    if (m_baSeed.size() == 0) //Mode 0
    {
        m_lRemainingSeedLength = a_rPacket.getLengthField();
    }

    unsigned int nSeedPartSize = a_rPacket.getSeedPartSize();
    for (unsigned int i = 0; i < nSeedPartSize; i++)
    {
        m_baSeed.push_back(a_rPacket.getSeedPart(i));
    }

    m_dwProcessedSeedLength += nSeedPartSize;
    m_lRemainingSeedLength -= nSeedPartSize;
    CmdPacketGetSeed* pLastPacket = dynamic_cast<CmdPacketGetSeed*>(m_rMaster.getLastSentCmd());
    if(m_lRemainingSeedLength == 0) {
        XCP_ComputeKeyFromSeedPtr_t ptr = m_rMaster.getComputeKeyPtr();
        if(pLastPacket && ptr) {
            ptr(pLastPacket->getResource(), a_rPacket.getLengthField(), m_baSeed.data(), &m_byKeyLength, m_baKey.data());
            m_baKey.resize(m_byKeyLength);
        }
    }
}

void IncomingPacketHandler::handle(ResPacketUnlock &a_rPacket)
{
    qDebug() << "UnlockResponse packet";
    XcpMaster::SlaveProperties properties = m_rMaster.getSlaveProperties();
    properties.CAL_PG = ((a_rPacket.getCurrentResourceProtection()&ResPacketConnect::ResourceParameterBits::CAL_PG) != 0);
    properties.DAQ = ((a_rPacket.getCurrentResourceProtection()&ResPacketConnect::ResourceParameterBits::DAQ) != 0);
    properties.PGM = ((a_rPacket.getCurrentResourceProtection()&ResPacketConnect::ResourceParameterBits::PGM) != 0);
    properties.STIM = ((a_rPacket.getCurrentResourceProtection()&ResPacketConnect::ResourceParameterBits::STIM) != 0);
    m_rMaster.setSlaveProperties(properties);

    qDebug() << "(CAL/PG: " << properties.CAL_PG << ", "
        << "DAQ: " << properties.DAQ << ", "
        << "STIM: " << properties.STIM << ", "
        << "PGM: " << properties.PGM << ") \n";
    resetSeedAndKey();
}

void IncomingPacketHandler::handle(GetDaqProcessorInfoResponse &a_rPacket)
{
    qDebug() << "GetDaqProcessorInfoResponsePacket\n";
    XcpMaster::SlaveProperties properties = m_rMaster.getSlaveProperties();
    properties.DaqProperties.configType = ((a_rPacket.getDaqProperties()&GetDaqProcessorInfoResponse::DaqPropertiesBits::DAQ_CONFIG_TYPE) != 0);
    properties.DaqProperties.prescalerSupported = ((a_rPacket.getDaqProperties()&GetDaqProcessorInfoResponse::DaqPropertiesBits::PRESCALER_SUPPORTED) != 0);
    properties.DaqProperties.resumeSupported = ((a_rPacket.getDaqProperties()&GetDaqProcessorInfoResponse::DaqPropertiesBits::RESUME_SUPPORTED) != 0);
    properties.DaqProperties.bitStimSupported = ((a_rPacket.getDaqProperties()&GetDaqProcessorInfoResponse::DaqPropertiesBits::BIT_STIM_SUPPORTED) != 0);
    properties.DaqProperties.timeStampSupported = ((a_rPacket.getDaqProperties()&GetDaqProcessorInfoResponse::DaqPropertiesBits::TIMESTAMP_SUPPORTED) != 0);
    properties.DaqProperties.pidOffSupported = ((a_rPacket.getDaqProperties()&GetDaqProcessorInfoResponse::DaqPropertiesBits::PID_OFF_SUPPORTED) != 0);

    properties.DaqProperties.overloadIndicationMode = a_rPacket.getDaqProperties()&GetDaqProcessorInfoResponse::DaqPropertiesBits::OVERLOAD_INDICATION_MODE;
    properties.DaqProperties.optimisationType = a_rPacket.getDaqKeyByte()&GetDaqProcessorInfoResponse::DaqKeyByteBits::OPTIMISATION_TYPE;
    properties.DaqProperties.addressExtensionType = a_rPacket.getDaqKeyByte()&GetDaqProcessorInfoResponse::DaqKeyByteBits::ADDRESS_EXTENSION;
    properties.DaqProperties.identificationFieldType = a_rPacket.getDaqKeyByte()&GetDaqProcessorInfoResponse::DaqKeyByteBits::IDENTIFICATION_FIELD_TYPE;

    properties.DaqProperties.maxDaq = a_rPacket.getMaxDaq(properties.byteOrder==0);
    properties.DaqProperties.minDaq = a_rPacket.getMinDaq();
    properties.DaqProperties.maxEventChannel = a_rPacket.getMaxEventChannel(properties.byteOrder==0);

    m_rMaster.setSlaveProperties(properties);

    qDebug() << "Config type: ";
    if (properties.DaqProperties.configType == 0)
    {
        qDebug() << "Static DAQ\n";
    }
    else
    {
        qDebug() << "Dynamic DAQ\n";
    }
    qDebug() << "Prescaler supported: " << properties.DaqProperties.prescalerSupported << "\n";
    qDebug() << "Resume supported: " << properties.DaqProperties.resumeSupported << "\n";
    qDebug() << "BitStim supported: " << properties.DaqProperties.bitStimSupported << "\n";
    qDebug() << "Timestamp supported: " << properties.DaqProperties.timeStampSupported << "\n";
    qDebug() << "Pid off supported: " << properties.DaqProperties.pidOffSupported << "\n";
    qDebug() << "Overload indication mode: ";
    if (properties.DaqProperties.overloadIndicationMode == GetDaqProcessorInfoResponse::OverloadIndicationMode::EVENT_PACKET)
    {
        qDebug() << "Event Packet";
    }
    else if (properties.DaqProperties.overloadIndicationMode == GetDaqProcessorInfoResponse::OverloadIndicationMode::MSB_PID)
    {
        qDebug() << "MSB PID";
    }
    else if (properties.DaqProperties.overloadIndicationMode == GetDaqProcessorInfoResponse::OverloadIndicationMode::NO_INDICATION)
    {
        qDebug() << "No indication";
    }
    qDebug() << "\n";
    qDebug() << "Optimisation type: ";
    if (properties.DaqProperties.optimisationType == GetDaqProcessorInfoResponse::OptimisationMode::OM_DEFAULT)
    {
        qDebug() << "Default";
    }
    else if (properties.DaqProperties.optimisationType == GetDaqProcessorInfoResponse::OptimisationMode::OM_ODT_TYPE_16)
    {
        qDebug() << "OM_ODT_TYPE_16";
    }
    else if (properties.DaqProperties.optimisationType == GetDaqProcessorInfoResponse::OptimisationMode::OM_ODT_TYPE_32)
    {
        qDebug() << "OM_ODT_TYPE_32";
    }
    else if (properties.DaqProperties.optimisationType == GetDaqProcessorInfoResponse::OptimisationMode::OM_ODT_TYPE_64)
    {
        qDebug() << "OM_ODT_TYPE_64";
    }
    else if (properties.DaqProperties.optimisationType == GetDaqProcessorInfoResponse::OptimisationMode::OM_MAX_ENTRY_SIZE)
    {
        qDebug() << "OM_MAX_ENTRY_SIZE";
    }
    else if (properties.DaqProperties.optimisationType == GetDaqProcessorInfoResponse::OptimisationMode::OM_ODT_TYPE_ALIGNMENT)
    {
        qDebug() << "OM_ODT_TYPE_ALIGNMENT";
    }
    else
    {
        qDebug() << "Unknown mode: " << QString::number(properties.DaqProperties.optimisationType, 16);
    }
    qDebug() << "\n";

    qDebug() << "Address Extension type: ";
    if (properties.DaqProperties.addressExtensionType == GetDaqProcessorInfoResponse::AddressExtensionType::CAN_BE_DIFFERENT)
    {
        qDebug() << "address extension can be different within one and the same ODT";
    }
    else if (properties.DaqProperties.addressExtensionType == GetDaqProcessorInfoResponse::AddressExtensionType::SAME_FOR_ALL_ENTRIES_ODT)
    {
        qDebug() << "address extension to be the same for all entries within one ODT";
    }
    else if (properties.DaqProperties.addressExtensionType == GetDaqProcessorInfoResponse::AddressExtensionType::SAME_FOR_ALL_ENTRIES_DAQ)
    {
        qDebug() << "address extension to be the same for all entries within one DAQ";
    }
    else
    {
        qDebug() << "unknown: 0x" << QString::number(properties.DaqProperties.addressExtensionType, 16);
    }
    qDebug() << "\n";
    qDebug() << "Identification field type: ";
    if (properties.DaqProperties.identificationFieldType == GetDaqProcessorInfoResponse::IdentificationFieldType::ABSOLUTE_ODT_NUMBER)
    {
        qDebug() << "Absolute ODT number";
    }
    else if (properties.DaqProperties.identificationFieldType == GetDaqProcessorInfoResponse::IdentificationFieldType::RELATIVE_ODT_ABSOLUTE_DAQ_BYTE)
    {
        qDebug() << "Relative ODT number, absolute DAQ list number (byte)";
    }
    else if (properties.DaqProperties.identificationFieldType == GetDaqProcessorInfoResponse::IdentificationFieldType::RELATIVE_ODT_ABSOLUTE_DAQ_WORD)
    {
        qDebug() << "Relative ODT number, absolute DAQ list number (word)";
    }
    else if (properties.DaqProperties.identificationFieldType == GetDaqProcessorInfoResponse::IdentificationFieldType::RELATIVE_ODT_ABSOLUTE_DAQ_WORD_ALIGNED)
    {
        qDebug() << "Relative ODT number, absolute DAQ list number (word-aligned)";
    }
    qDebug() << "\n";
    qDebug() << "Max DAQ: " << (int)properties.DaqProperties.maxDaq<<"\n";
    qDebug() << "Max Event channel: " << (int)properties.DaqProperties.maxEventChannel<<"\n";
    qDebug() << "Min DAQ: " << (int)properties.DaqProperties.minDaq << "\n";
}

void IncomingPacketHandler::handle(DTO &a_rPacket)
{
    qDebug() << "DAQ packet:\n";
    qDebug() << a_rPacket.getDaqField()<<"\n";
    DaqLayout& daqlayout = m_rMaster.getDaqLayout();
    qDebug() << a_rPacket.getDaqIndex();
    DAQ& daq = daqlayout.getDaq(a_rPacket.getDaqIndex());
    uint32_t dwLastTimestamp = m_rMaster.getDaqLayout().getDaq(a_rPacket.getDaqIndex()).getLastTimestamp();
    if (a_rPacket.isTimestamped()) {
        qDebug() << a_rPacket.getTimestamp() << "\n";
        daq.setLastTimestamp(a_rPacket.getTimestamp());
    }

    ODT& odt = daq.getOdt(a_rPacket.getOdtIndex());
    uint32_t dwByteIndex = 0;
    for (uint32_t i=0; i<odt.getNumberOfEntries(); i++)
    {
        switch (odt.getEntry(i).getDataType())
        {
        case MeasurementDataTypes::eInt8:
        {
            if(a_rPacket.getDataBytes().size() >= 1+dwByteIndex) {
                int8_t value = (int8_t)a_rPacket.getDataBytes()[dwByteIndex];
                m_rMaster.emitSendOdtEntryValue(a_rPacket.getDaqIndex(), a_rPacket.getOdtIndex(), i, dwLastTimestamp, (double)value);
            }
            break;
        }
        case MeasurementDataTypes::eUint8:
        {
            if(a_rPacket.getDataBytes().size() >= 1+dwByteIndex) {
                uint8_t value = (uint8_t)a_rPacket.getDataBytes()[dwByteIndex];
                m_rMaster.emitSendOdtEntryValue(a_rPacket.getDaqIndex(), a_rPacket.getOdtIndex(), i, dwLastTimestamp, (double)value);
            }
            break;
        }
        case MeasurementDataTypes::eInt16:
        {
            if(a_rPacket.getDataBytes().size() >= 2+dwByteIndex) {
                QVector<uint8_t> bytes = a_rPacket.getDataBytes().mid(dwByteIndex);
                int16_t value = ((((uint32_t)bytes[0])<<8)&0xFF00)+((((uint32_t)bytes[1])<<0)&0xFF);
                m_rMaster.emitSendOdtEntryValue(a_rPacket.getDaqIndex(), a_rPacket.getOdtIndex(), i, dwLastTimestamp, (double)value);
            }
            break;
        }
        case MeasurementDataTypes::eUint16:
        {
            if(a_rPacket.getDataBytes().size() >= 2+dwByteIndex) {
                QVector<uint8_t> bytes = a_rPacket.getDataBytes().mid(dwByteIndex);
                uint16_t value = ((((uint32_t)bytes[0])<<8)&0xFF00)+((((uint32_t)bytes[1])<<0)&0xFF);
                m_rMaster.emitSendOdtEntryValue(a_rPacket.getDaqIndex(), a_rPacket.getOdtIndex(), i, dwLastTimestamp, (double)value);
            }
            break;
        }
        case MeasurementDataTypes::eInt32:
        {
            if(a_rPacket.getDataBytes().size() >= 4+dwByteIndex) {
                QVector<uint8_t> bytes = a_rPacket.getDataBytes().mid(dwByteIndex);
                int32_t value = ((((uint32_t)bytes[0])<<24)&0xFF000000)+((((uint32_t)bytes[1])<<16)&0xFF0000)+((((uint32_t)bytes[2])<<8)&0xFF00)+((((uint32_t)bytes[3])<<0)&0xFF);
                m_rMaster.emitSendOdtEntryValue(a_rPacket.getDaqIndex(), a_rPacket.getOdtIndex(), i, dwLastTimestamp, (double)value);
            }
            break;
        }
        case MeasurementDataTypes::eUint32:
        {
            if(a_rPacket.getDataBytes().size() >= 4+dwByteIndex) {
                QVector<uint8_t> bytes = a_rPacket.getDataBytes().mid(dwByteIndex);
                uint32_t value = ((((uint32_t)bytes[0])<<24)&0xFF000000)+((((uint32_t)bytes[1])<<16)&0xFF0000)+((((uint32_t)bytes[2])<<8)&0xFF00)+((((uint32_t)bytes[3])<<0)&0xFF);
                m_rMaster.emitSendOdtEntryValue(a_rPacket.getDaqIndex(), a_rPacket.getOdtIndex(), i, dwLastTimestamp, (double)value);
            }
            break;
        }
        case MeasurementDataTypes::eFloat:
        {
            if(a_rPacket.getDataBytes().size() >= 4+dwByteIndex) {
                QVector<uint8_t> bytes = a_rPacket.getDataBytes().mid(dwByteIndex);
                uint32_t value = ((((uint32_t)bytes[0])<<24)&0xFF000000)+((((uint32_t)bytes[1])<<16)&0xFF0000)+((((uint32_t)bytes[2])<<8)&0xFF00)+((((uint32_t)bytes[3])<<0)&0xFF);
                m_rMaster.emitSendOdtEntryValue(a_rPacket.getDaqIndex(), a_rPacket.getOdtIndex(), i, dwLastTimestamp, (double)(*((float*)&value)));
            }
            break;
        }
        case MeasurementDataTypes::eInt64:
        {
            if(a_rPacket.getDataBytes().size() >= 8+dwByteIndex) {
                QVector<uint8_t> bytes = a_rPacket.getDataBytes().mid(dwByteIndex);
                int64_t value = ((((uint64_t)bytes[0])<<56)&0xFF00000000000000)
                               +((((uint64_t)bytes[1])<<48)&0xFF000000000000)
                               +((((uint64_t)bytes[2])<<40)&0xFF0000000000)
                               +((((uint64_t)bytes[3])<<32)&0xFF00000000)
                               +((((uint64_t)bytes[4])<<24)&0xFF000000)
                               +((((uint64_t)bytes[5])<<16)&0xFF0000)
                               +((((uint64_t)bytes[6])<<8 )&0xFF00)
                               +((((uint64_t)bytes[7])<<0 )&0xFF);
                m_rMaster.emitSendOdtEntryValue(a_rPacket.getDaqIndex(), a_rPacket.getOdtIndex(), i, dwLastTimestamp, (double)value);
            }
            break;
        }
        case MeasurementDataTypes::eUint64:
        {
            if(a_rPacket.getDataBytes().size() >= 8+dwByteIndex) {
                QVector<uint8_t> bytes = a_rPacket.getDataBytes().mid(dwByteIndex);
                uint64_t value = ((((uint64_t)bytes[0])<<56)&0xFF00000000000000)
                                +((((uint64_t)bytes[1])<<48)&0xFF000000000000)
                                +((((uint64_t)bytes[2])<<40)&0xFF0000000000)
                                +((((uint64_t)bytes[3])<<32)&0xFF00000000)
                                +((((uint64_t)bytes[4])<<24)&0xFF000000)
                                +((((uint64_t)bytes[5])<<16)&0xFF0000)
                                +((((uint64_t)bytes[6])<<8 )&0xFF00)
                                +((((uint64_t)bytes[7])<<0 )&0xFF);
                m_rMaster.emitSendOdtEntryValue(a_rPacket.getDaqIndex(), a_rPacket.getOdtIndex(), i, dwLastTimestamp, (double)value);
            }
            break;
        }
        case MeasurementDataTypes::eDouble:
        {
            if(a_rPacket.getDataBytes().size() >= 8+dwByteIndex) {
                QVector<uint8_t> bytes = a_rPacket.getDataBytes().mid(dwByteIndex);
                uint64_t value = ((((uint64_t)bytes[0])<<56)&0xFF00000000000000)
                                +((((uint64_t)bytes[1])<<48)&0xFF000000000000)
                                +((((uint64_t)bytes[2])<<40)&0xFF0000000000)
                                +((((uint64_t)bytes[3])<<32)&0xFF00000000)
                                +((((uint64_t)bytes[4])<<24)&0xFF000000)
                                +((((uint64_t)bytes[5])<<16)&0xFF0000)
                                +((((uint64_t)bytes[6])<<8 )&0xFF00)
                                +((((uint64_t)bytes[7])<<0 )&0xFF);
                m_rMaster.emitSendOdtEntryValue(a_rPacket.getDaqIndex(), a_rPacket.getOdtIndex(), i, dwLastTimestamp, (*((double*)&value)));
            }
            break;
        }

        }
        dwByteIndex += odt.getEntry(i).getLength();
    }

    m_dwReceivedDtoCount++;
}

void IncomingPacketHandler::handle(ErrorPacketCmdUnknown &a_rPacket)
{
    qDebug() << "ERROR: Unknown command\n";
}

const QVector<quint8> &IncomingPacketHandler::getUnlockKey() const
{
    return m_baKey;
}

void IncomingPacketHandler::resetSeedAndKey()
{
    m_dwProcessedSeedLength = 0;
    m_lRemainingSeedLength = -1;
    m_baKey.clear();
    m_baKey.resize(255);
    m_byKeyLength = 255;
    m_baSeed.clear();
}
