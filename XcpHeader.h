#ifndef XCPHEADER_H
#define XCPHEADER_H

#include <QVector>

class XcpHeader
{
public:
    XcpHeader () {}
    virtual ~XcpHeader() {}
    virtual QVector<quint8> getByteArray() = 0;
};

#endif // XCPHEADER_H
