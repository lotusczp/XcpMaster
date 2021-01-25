#include "EthernetTail.h"

EthernetTail::EthernetTail()
    : XcpTail()
{

}

EthernetTail::~EthernetTail()
{

}

QVector<quint8> EthernetTail::getByteArray()
{
    return QVector<quint8>();
}
