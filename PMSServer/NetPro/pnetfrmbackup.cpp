#include "pnetfrmbackup.h"
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include <QProcess>
#include <QXmlStreamWriter>
#include "pgblpara.h"
PNetFrmBackup::PNetFrmBackup(QSqlDatabase db):PNetFrm(db)
{

}
void PNetFrmBackup::ZListBackup()
{
    //SELECT `BackupName`,`FileSize`,`Creator`,`CreateTime`) FROM `pms`.`BackupInfo`;
    qint32 retCode=0;
    QString errMsg;
    QSqlQuery query(this->m_db);
    if(!query.exec("SELECT `BackupName`,`FileSize`,`Creator`,`CreateTime` FROM `pms`.`BackupInfo`"))
    {
        retCode=-1;
        errMsg=query.lastError().text();
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Backup"));
    if(retCode<0)
    {
        tXmlWriter.writeStartElement(QString("Backup"));
        tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
        tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        tXmlWriter.writeCharacters("0B");//pathSize.
        tXmlWriter.writeEndElement();//Backup.
        this->m_opLogMsg=QString("list backup failed:[%1].").arg(errMsg);
    }else{
        QString strFileSystemDataSize=this->ZGetFileSystemDataSize();
        QString strDatabaseDataSize=this->ZGetDatabaseDataSize();
        while(query.next())
        {
            QString backupName=query.value(0).toString();
            QString fileSize=query.value(1).toString();
            QString creator=query.value(2).toString();
            QString createTime=query.value(3).toString();
            tXmlWriter.writeStartElement(QString("Backup"));
            tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
            tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
            tXmlWriter.writeAttribute(QString("backupName"),backupName);
            tXmlWriter.writeAttribute(QString("fileSize"),fileSize);
            tXmlWriter.writeAttribute(QString("creator"),creator);
            tXmlWriter.writeAttribute(QString("createTime"),createTime);
            tXmlWriter.writeCharacters(strDatabaseDataSize+":"+strFileSystemDataSize);
            tXmlWriter.writeEndElement();//Backup.
        }
        this->m_opLogMsg=QString("list backup success");
    }
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmBackup::ZDoBackup(QString creator)
{
    //do backup.
    QDateTime curTime=QDateTime::currentDateTime();
    QString dir=QDir::currentPath();
    QDir dirObj;
    dirObj.mkpath(dir+"/backup");
    QString backupName=curTime.toString("yyyyMMddhhmmss");
    QString backupTarFile=QString("%1/backup/data-%2.tar.bz2").arg(dir).arg(backupName);
    QString backupSrc=QString("data");
    QProcess p;
    p.start("tar",QStringList()<<"cvfj"<<backupTarFile<<backupSrc);
    p.waitForStarted();
    p.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(p.readAllStandardOutput());

    QString backupMysql=QString("mysqldump -uroot -p123456 pms");
    QString backupMysqlFile=QString("%1/backup/data-%2.sql").arg(dir).arg(backupName);
    QProcess processMysql;
    processMysql.setStandardOutputFile(backupMysqlFile);
    processMysql.start(backupMysql);
    processMysql.waitForStarted();
    processMysql.waitForFinished();
    //write to mysql.
    //INSERT INTO `pms`.`BackupInfo` (`BackupName`,`FileSize`,`Creator`,`CreateTime`) VALUES ('abc',1239,'root','2017-02-14 11:12:12');
    qint32 retCode=0;
    QString errMsg;
    QString createTime=curTime.toString("yyyy-MM-dd_hh:mm:ss");
    QSqlQuery query(this->m_db);
    query.prepare("INSERT INTO `pms`.`BackupInfo` (`BackupName`,`FileSize`,`Creator`,`CreateTime`) VALUES (:BackupName,:FileSize,:Creator,:CreateTime)");
    query.bindValue(":BackupName",backupName);
    QFile fileTar(backupTarFile);
    QFile fileSql(backupMysqlFile);
    query.bindValue(":FileSize",fileTar.size()+fileSql.size());
    query.bindValue(":Creator",creator);
    query.bindValue(":CreateTime",createTime);
    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Backup"));
    tXmlWriter.writeStartElement(QString("Backup"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("backup"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        this->m_opLogMsg=QString("backup [%1] failed:[%2].").arg(backupName).arg(errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("fileSize"),QString("%1").arg(fileTar.size()+fileSql.size()));
        tXmlWriter.writeAttribute(QString("creator"),creator);
        tXmlWriter.writeAttribute(QString("createTime"),createTime);
        this->m_opLogMsg=QString("backup [%1] success").arg(backupName);
    }
    tXmlWriter.writeCharacters(backupName);
    tXmlWriter.writeEndElement();//Backup.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmBackup::ZDoRestore(QString backupName)
{
    typedef struct{
        QString backupName;
        QString fileSize;
        QString creator;
        QString createTime;
    }BackupRecords;
    QList<BackupRecords> backupList;
    //SELECT `BackupName`,`FileSize`,`Creator`,`CreateTime` FROM `pms`.`BackupInfo`;
    QSqlQuery querySelect(this->m_db);
    if(querySelect.exec("SELECT `BackupName`,`FileSize`,`Creator`,`CreateTime` FROM `pms`.`BackupInfo`"))
    {
        while(querySelect.next())
        {
            BackupRecords rec;
            rec.backupName=querySelect.value(0).toString();
            rec.fileSize=querySelect.value(1).toString();
            rec.creator=querySelect.value(2).toString();
            rec.createTime=querySelect.value(3).toString();
            backupList.append(rec);
        }
    }
    qint32 retCode=0;
    QString errMsg;
    QString dir=QDir::currentPath();
    QString tarFile=QString("%1/backup/data-%2.tar.bz2").arg(dir).arg(backupName);
    QString sqlFile=QString("%1/backup/data-%2.sql").arg(dir).arg(backupName);
    //clear process.
    QProcess processRm;
    processRm.start("rm",QStringList()<<"-rvf"<<dir+"/data");
    processRm.waitForStarted();
    processRm.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(processRm.readAllStandardOutput());
    //unrar tar file.
    QProcess processTar;
    processTar.start("tar",QStringList()<<"-jxvf"<<tarFile<<"-C"<<dir);
    processTar.waitForStarted();
    processTar.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(processTar.readAllStandardOutput());
    //do sql import.
    QString restoreMysql=QString("mysql -uroot -p123456 pms");
    QProcess processMysql;
    processMysql.setStandardInputFile(sqlFile);
    processMysql.start(restoreMysql);
    processMysql.waitForStarted();
    processMysql.waitForFinished();

    //to avoid the old backup lost,so here write table.
    //INSERT INTO `pms`.`BackupInfo` (`BackupName`,`FileSize`,`Creator`,`CreateTime`) VALUES ('abc',1239,'root','2017-02-14 11:12:12');
    for(qint32 i=0;i<backupList.count();i++)
    {
        BackupRecords rec=backupList.at(i);
        QSqlQuery query(this->m_db);
        query.prepare("INSERT INTO `pms`.`BackupInfo` (`BackupName`,`FileSize`,`Creator`,`CreateTime`) VALUES (:BackupName,:FileSize,:Creator,:CreateTime)");
        query.bindValue(":BackupName",rec.backupName);
        query.bindValue(":FileSize",rec.fileSize);
        query.bindValue(":Creator",rec.creator);
        query.bindValue(":CreateTime",rec.createTime);
        if(!query.exec())
        {
            retCode=-1;
            errMsg=query.lastError().text();
        }
    }

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Backup"));
    tXmlWriter.writeStartElement(QString("Backup"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("restore"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        this->m_opLogMsg=QString("restore backup [%1] failed:[%2].").arg(backupName).arg(errMsg);
    }else{
        this->m_opLogMsg=QString("restore backup [%1] success.").arg(backupName);
    }
    tXmlWriter.writeCharacters(backupName);
    tXmlWriter.writeEndElement();//Backup.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmBackup::ZDoDelete(QString backupName)
{
    QString dir=QDir::currentPath();
    QString tarFile=QString("%1/backup/data-%2.tar.bz2").arg(dir).arg(backupName);
    QString sqlFile=QString("%1/backup/data-%2.sql").arg(dir).arg(backupName);
    QProcess p;
    p.start("rm",QStringList()<<"-rf"<<tarFile<<sqlFile);
    p.waitForStarted();
    p.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(p.readAllStandardOutput());

    //DELETE FROM `pms`.`BackupInfo` WHERE `BackupName`='abc';
    qint32 retCode=0;
    QString errMsg;
    QSqlQuery query(this->m_db);
    query.prepare("DELETE FROM `pms`.`BackupInfo` WHERE `BackupName`=:BackupName");
    query.bindValue(":BackupName",backupName);
    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Backup"));
    tXmlWriter.writeStartElement(QString("Backup"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("delete"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        this->m_opLogMsg=QString("delete backup [%1] failed:[%2].").arg(backupName).arg(errMsg);
    }else{
        this->m_opLogMsg=QString("delete backup [%1] success.").arg(backupName);
    }
    tXmlWriter.writeCharacters(backupName);
    tXmlWriter.writeEndElement();//Backup.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
QString PNetFrmBackup::ZGetFileSystemDataSize(void)
{
    //get File size.
    quint64 pathSize=PGblPara::ZGetInstance()->ZGetPathSize(QDir::currentPath());
    float fSize=0;
    QString strPathSize;
    if(pathSize<1024)
    {
        fSize=pathSize;
        strPathSize=QString::number(fSize,'f',2)+QString("B");
    }else if(pathSize>=1024 && pathSize<=(1024*1024))
    {
        fSize=pathSize/1024.0;
        strPathSize=QString::number(fSize,'f',2)+QString("KB");
    }else{
        fSize=pathSize/1024.0/1024.0;
        strPathSize=QString::number(fSize,'f',2)+QString("MB");
    }
    return strPathSize;
}
QString PNetFrmBackup::ZGetDatabaseDataSize(void)
{
    //get mysql database size.
    //SELECT CONCAT(ROUND(SUM(DATA_LENGTH/1024/1024),2),'MB') AS DATA FROM information_schema.tables WHERE table_schema='pms';
    QSqlQuery query(this->m_db);
    if(!query.exec("SELECT CONCAT(ROUND(SUM(DATA_LENGTH/1024/1024),2),'MB') AS DATA FROM information_schema.tables WHERE table_schema='pms'"))
    {
        return QString("0B");
    }
    while(query.next())
    {
        return query.value(0).toString();
    }
    return QString("0B");
}
