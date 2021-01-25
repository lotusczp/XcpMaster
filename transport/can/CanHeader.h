#ifndef CANHEADER_H
#define CANHEADER_H

#include "XcpHeader.h"

class CanHeader : public XcpHeader
{
public:
    CanHeader();
    virtual ~CanHeader();

    virtual QVector<quint8> getByteArray();
};

#endif // CANHEADER_H
