#include "pgblpara.h"
#include <QFile>
#include <QDir>
#include <QDebug>
PGblPara* PGblPara::m_pInstance=NULL;
PGblPara::PGblPara()
{
}
void PGblPara::ZLoadCfgFile()
{
    QString versionFileName=QDir::currentPath()+"/update/PMSManager.ver";
    QString appFileName=QDir::currentPath()+"/update/PMSManager.exe";
    QFile verFfile(versionFileName);
    QFile appFile(appFileName);
    this->m_blockSize=(1*1024*1024);
    this->m_totalBlock=appFile.size()/this->m_blockSize;
    this->m_remainBytes=appFile.size()%this->m_blockSize;
    if(verFfile.open(QIODevice::ReadOnly))
    {
        this->m_newVersionNo=verFfile.read(QString("0.0.0").length());
        verFfile.close();
    }else{
        this->m_newVersionNo="0.0.0";
        this->m_totalBlock=0;
        this->m_blockSize=0;
        this->m_remainBytes=0;
    }
    qDebug()<<"PMSManager version file:"<<versionFileName;
    qDebug()<<"PMSManager binary file:"<<appFileName;
    qDebug()<<"PMSManager new version:"<<this->m_newVersionNo<<"totalBlock:"<<this->m_totalBlock<<"blockSize:"<<this->m_blockSize<<"remainSize:"<<this->m_remainBytes;
}
