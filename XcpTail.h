#ifndef XCPTAIL_H
#define XCPTAIL_H

#include <QVector>

class XcpTail
{
public:
    XcpTail () {}
    virtual ~XcpTail() {}
    virtual QVector<quint8> getByteArray() = 0;
};

#endif // XCPTAIL_H
