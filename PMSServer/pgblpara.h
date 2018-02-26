#ifndef PGBLPARA_H
#define PGBLPARA_H

#include <QString>
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
private:
    static PGblPara* m_pInstance;
};

#endif // PGBLPARA_H
