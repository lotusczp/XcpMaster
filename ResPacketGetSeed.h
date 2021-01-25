#ifndef RESPACKETGETSEED_H
#define RESPACKETGETSEED_H

#include <QVector>
#include "ResPacket.h"

class ResPacketGetSeed : public ResPacket
{
public:
    ResPacketGetSeed(const QVector<uint8_t>& a_rPacketBytes);
    uint8_t getLengthField();
    uint8_t getSeedPart(uint8_t a_byElement);
    uint8_t getSeedPartSize();
    static ResPacketGetSeed* deserialize(const QVector<uint8_t>& a_rPacketBytes);
};

#endif // RESPACKETGETSEED_H
