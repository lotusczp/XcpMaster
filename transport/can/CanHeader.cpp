#include "CanHeader.h"

CanHeader::CanHeader()
    : XcpHeader()
{

}

CanHeader::~CanHeader()
{

}

QVector<quint8> CanHeader::getByteArray()
{
    return QVector<quint8>();
}
