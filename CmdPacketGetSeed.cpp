#include "CmdPacketGetSeed.h"

CmdPacketGetSeed::CmdPacketGetSeed()
    : CmdPacket()
{
    m_idField.append(CTO::GET_SEED);
    m_dataField.resize(2); // Reserve 2 element in data field
}

CmdPacketGetSeed::CmdPacketGetSeed(CmdPacketGetSeed::Mode a_eMode, CmdPacketGetSeed::Resource a_eResource)
    : CmdPacketGetSeed()
{
    setMode(a_eMode);
    setResource(a_eResource);
}

void CmdPacketGetSeed::setMode(CmdPacketGetSeed::Mode a_eMode)
{
    m_dataField[0] = a_eMode;
}

void CmdPacketGetSeed::setResource(CmdPacketGetSeed::Resource a_eResource)
{
    m_dataField[1] = a_eResource;
}

uint8_t CmdPacketGetSeed::getResource()
{
    return m_dataField[1];
}
