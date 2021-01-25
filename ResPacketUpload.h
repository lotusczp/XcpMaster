#ifndef RESPACKETUPLOAD_H
#define RESPACKETUPLOAD_H

#include <QVector>
#include "ResPacket.h"

class ResPacketUpload : public ResPacket
{
public:
    static ResPacketUpload* deserialize(const QVector<uint8_t>& a_rPacketBytes, uint8_t a_byAG);

    uint8_t getNumberOfElements() {return m_byNumberOfElements;}

private:
    ResPacketUpload(const QVector<uint8_t>& a_rPacketBytes, uint8_t a_byAG);

private:
    uint8_t m_byElementSizeInBytes;
    uint8_t m_byNumberOfElements;
};

#endif // RESPACKETUPLOAD_H
