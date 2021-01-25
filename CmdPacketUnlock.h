#ifndef CMDPACKETUNLOCK_H
#define CMDPACKETUNLOCK_H

#include "CmdPacket.h"

class CmdPacketUnlock : public CmdPacket
{
public:
    CmdPacketUnlock(const QVector<uint8_t> &a_rKey, uint8_t a_byStartIndex, uint8_t a_byMaxCto);

    static QVector<XcpPacket*> createUnlockPackets(const QVector<uint8_t>& a_rKey, uint8_t a_byMaxCto);

    uint8_t getRemainingKeyLength();
};

#endif // CMDPACKETUNLOCK_H
