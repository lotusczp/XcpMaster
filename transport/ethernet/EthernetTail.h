#ifndef ETHERNETTAIL_H
#define ETHERNETTAIL_H

#include "XcpTail.h"

class EthernetTail : public XcpTail
{
public:
    EthernetTail();
    virtual ~EthernetTail();

    virtual QVector<quint8> getByteArray();
};

#endif // ETHERNETTAIL_H
