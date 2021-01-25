#ifndef CANTAIL_H
#define CANTAIL_H

#include "XcpTail.h"

class CanTail : public XcpTail
{
public:
    CanTail();
    virtual ~CanTail();

    virtual QVector<quint8> getByteArray();
};

#endif // CANTAIL_H
