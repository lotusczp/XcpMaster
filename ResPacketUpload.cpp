#include "ResPacketUpload.h"

ResPacketUpload *ResPacketUpload::deserialize(const QVector<uint8_t> &a_rPacketBytes, uint8_t a_byAG)
{
    return new ResPacketUpload(a_rPacketBytes, a_byAG);
}

ResPacketUpload::ResPacketUpload(const QVector<uint8_t> &a_rPacketBytes, uint8_t a_byAG)
{
    int iDataLength = a_rPacketBytes.size() - 1; // size - PID fieldsize
    m_dataField.resize(iDataLength);
    for(int i=0; i<iDataLength; i++) {
        m_dataField[i] = a_rPacketBytes[1+i];
    }
    m_byElementSizeInBytes = 1 << a_byAG;
    if (m_byElementSizeInBytes == 1) {
        m_byNumberOfElements = iDataLength;
    }
    else if(m_byElementSizeInBytes == 2) {
        m_byNumberOfElements = (iDataLength - 1)/2;
    }
    else if(m_byElementSizeInBytes == 4) {
        m_byNumberOfElements = (iDataLength - 3)/4;
    }
    else {
        // Error
        m_byNumberOfElements = 0;
    }
}
