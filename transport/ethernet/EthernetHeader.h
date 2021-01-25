#ifndef ETHERNETHEADER_H
#define ETHERNETHEADER_H

#include "XcpHeader.h"

class EthernetHeader : public XcpHeader
{
public:
    EthernetHeader(uint16_t a_wLen, uint16_t a_wCtr);
    virtual ~EthernetHeader();

    virtual QVector<quint8> getByteArray();

    void setLength(uint16_t a_wLen) {m_wLength = a_wLen;}
    uint16_t getLength() {return m_wLength;}
    void setCtr(uint16_t a_wCtr) {m_wCtr = a_wCtr;}
    uint16_t getCtr() {return m_wCtr;}

private:
    uint16_t m_wLength;
    uint16_t m_wCtr;
};

#endif // ETHERNETHEADER_H
