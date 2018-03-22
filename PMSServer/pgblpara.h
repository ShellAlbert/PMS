#ifndef PGBLPARA_H
#define PGBLPARA_H

#include <QString>
#include <QMutex>
#define PMSSERVER_VERSION   "V3.0.0" //2018/3/1

class PGblPara
{
public:
    PGblPara();
    static PGblPara* ZGetInstance()
    {
        if(m_pInstance==NULL)
        {
            m_pInstance=new PGblPara;
        }
        return m_pInstance;
    }
    void ZLoadCfgFile();

    quint64 ZGetPathSize(QString path);
public:
    QString m_newVersionNo;
    qint32 m_totalBlock;
    qint32 m_blockSize;
    qint32 m_remainBytes;
    //mutex for mysql.
    QMutex m_muxDB;

public:
    QString m_mysqlIP;
    QString m_mysqlPort;
    QString m_mysqlUser;
    QString m_mysqlPass;

    QString m_tcpPort;
private:
    static PGblPara* m_pInstance;
};

#endif // PGBLPARA_H
