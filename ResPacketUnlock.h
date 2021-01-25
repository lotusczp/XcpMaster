#ifndef RESPACKETUNLOCK_H
#define RESPACKETUNLOCK_H

#include <QVector>
#include "ResPacket.h"

class ResPacketUnlock : public ResPacket
{
public:
    ResPacketUnlock(const QVector<uint8_t>& a_rPacketBytes);

    void setCurrentResourceProtection(uint8_t a_byCurrentProection);
    uint8_t getCurrentResourceProtection();

    static ResPacketUnlock* deserialize(const QVector<uint8_t>& a_rPacketBytes);

};

#endif // RESPACKETUNLOCK_H
