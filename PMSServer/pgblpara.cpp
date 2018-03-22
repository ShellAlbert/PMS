#include "pgblpara.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QSettings>
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

    //load config file.
    QString iniFileName(QDir::currentPath()+"/PMS.ini");
    if(!QFile::exists(iniFileName))
    {
        //if ini file is not exist,create it and fill with default value.
        QSettings iniFile(iniFileName,QSettings::IniFormat);
        iniFile.setIniCodec("UTF8");
        iniFile.beginGroup("MySQL");
        iniFile.setValue("IP","127.0.0.1");
        iniFile.setValue("PORT","3306");
        iniFile.setValue("USER","root");
        iniFile.setValue("PASS","123456");
        iniFile.endGroup();

        iniFile.beginGroup("TCP");
        iniFile.setValue("PORT","6800");
        iniFile.endGroup();
    }
    //read config file.
    QSettings iniFile(iniFileName,QSettings::IniFormat);
    iniFile.setIniCodec("UTF8");
    iniFile.beginGroup("MySQL");
    this->m_mysqlIP=iniFile.value("IP","127.0.0.1").toString();
    this->m_mysqlPort=iniFile.value("PORT","3306").toString();
    this->m_mysqlUser=iniFile.value("USER","root").toString();
    this->m_mysqlPass=iniFile.value("PASS","123456").toString();
    iniFile.endGroup();
    iniFile.beginGroup("TCP");
    this->m_tcpPort=iniFile.value("PORT","6800").toString();
    iniFile.endGroup();
}
quint64 PGblPara::ZGetPathSize(QString path)
{
    QDir dir(path);
    quint64 size = 0;
    foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files))
    {
        size += fileInfo.size();
    }
    foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        size += this->ZGetPathSize(path + QDir::separator() + subDir);
    }
    return size;
}
