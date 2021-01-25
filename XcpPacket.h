#ifndef XCPPACKET_H
#define XCPPACKET_H

#include <QVector>

class XcpPacket
{
public:
    XcpPacket() {}
    virtual ~XcpPacket() {}

    quint8 getPid() const
    {
        if(m_idField.isEmpty()) {
            return 0;
        }
        return m_idField[0]; // Must available
    }

    void setPid(quint8 a_byPid)
    {
        if(m_idField.isEmpty()) {
            m_idField.append(a_byPid);
        }
        m_idField[0] = a_byPid;
    }

    QVector<quint8> getByteArray() const {return m_idField+m_timestampField+m_dataField;}

    QVector<quint8> getDataBytes() const {return m_dataField;}

protected:
    QVector<quint8> m_idField;
    QVector<quint8> m_timestampField;
    QVector<quint8> m_dataField;
};

#endif // XCPPACKET_H
