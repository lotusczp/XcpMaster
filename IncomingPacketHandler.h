#ifndef INCOMINGPACKETHANDLER_H
#define INCOMINGPACKETHANDLER_H

#include <QVector>
#include "XcpMaster.h"
#include "ResPacket.h"
#include "ResPacketConnect.h"
#include "ResPacketGetStatus.h"
#include "ErrorPacketSync.h"
#include "ResPacketUpload.h"
#include "ErrorPacketAccessLocked.h"
#include "ErrorPacketOutOfRange.h"
#include "ErrorPacketSequence.h"
#include "ErrorPacketMemoryOverflow.h"
#include "DAQPackets.h"
#include "ResPacketGetSeed.h"
#include "ResPacketUnlock.h"
#include "DAQPackets.h"
#include "DTO.h"
#include "ErrorPacketCmdUnknown.h"

class IncomingPacketHandler
{
public:
    IncomingPacketHandler(XcpMaster &a_rMaster);
    ~IncomingPacketHandler();

    void handle(XcpPacket *a_pPacket);

    void handle(ResPacket& a_rPacket);
    void handle(ResPacketConnect& a_rPacket);
    void handle(ResPacketGetStatus& a_rPacket);
    void handle(ErrorPacketSync& a_rPacket);
    void handle(ResPacketUpload& a_rPacket);
    void handle(ErrorPacketAccessLocked& a_rPacket);
    void handle(ErrorPacketOutOfRange& a_rPacket);
    void handle(ErrorPacketSequence& a_rPacket);
    void handle(ErrorPacketMemoryOverflow& a_rPacket);
    void handle(StartStopDaqListPositiveResponse& a_rPacket);
    void handle(ResPacketGetSeed& a_rPacket);
    void handle(ResPacketUnlock& a_rPacket);
    void handle(GetDaqProcessorInfoResponse& a_rPacket);
    void handle(DTO& a_rPacket);
    void handle(ErrorPacketCmdUnknown& a_rPacket);

    const QVector<quint8>& getUnlockKey() const;

private:
    void resetSeedAndKey();

private:
    XcpMaster           &m_rMaster;
    QVector<quint8>     m_baKey;
    QVector<uint8_t>    m_baSeed;
    uint8_t             m_byKeyLength;
    uint32_t            m_dwProcessedSeedLength;
    int32_t             m_lRemainingSeedLength;
    uint32_t            m_dwReceivedDtoCount;
};

#endif // INCOMINGPACKETHANDLER_H
