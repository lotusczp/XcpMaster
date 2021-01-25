#ifndef RESPACKET_H
#define RESPACKET_H

#include "CTO.h"

class ResPacket : public CTO
{
public:
    ResPacket() : CTO()
    {
        m_idField.resize(1);
        m_idField[0] = CTO::RES;
    }
    virtual ~ResPacket() {}
};

#endif // RESPACKET_H
