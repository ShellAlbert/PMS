#ifndef PGBLPARA_H
#define PGBLPARA_H

#include <QString>
#include <QMutex>
#define PMSSERVER_VERSION   "V3.0.0"
#define TCP_PORT        6800
#define MYSQL_IP        "127.0.0.1"
#define MYSQL_PORT      3306
#define MYSQL_DB        "PMS"
#define MYSQL_USER      "root"
#define MYSQL_PASS      "123456"
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
public:
    QString m_newVersionNo;
    qint32 m_totalBlock;
    qint32 m_blockSize;
    qint32 m_remainBytes;
    //mutex for mysql.
    QMutex m_muxDB;
private:
    static PGblPara* m_pInstance;
};

#endif // PGBLPARA_H
