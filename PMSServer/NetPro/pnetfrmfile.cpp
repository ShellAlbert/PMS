#include "pnetfrmfile.h"
#include <QXmlStreamWriter>
#include <QDir>
#include <QFile>
#include <QDebug>
PNetFrmFile::PNetFrmFile(QSqlDatabase db):PNetFrm(db)
{

}
void PNetFrmFile::ZAddFile(QString folderName,QString fileName,QString fileType,qint32 fileSize,QString creator)
{
    qDebug()<<folderName<<fileName<<fileType<<creator;
    QString filePath(QDir::currentPath()+"/data/"+creator+"/file/"+folderName+"/"+fileName);
    QFile::remove(filePath);

    //INSERT INTO `pms`.`FileInfo` (`FileName`, `FolderName`, `FileType`, `FileSize`, `Creator`, `CreateTime`) VALUES ('a.pdf', 'fuck', 'pdf', '10', 'root', '2016-12-12 12:12:12');
    qint32 retCode=0;
    QString errMsg;
    QSqlQuery query(this->m_db);
    query.prepare("INSERT INTO `pms`.`FileInfo` (`FileName`, `FolderName`, `FileType`, `FileSize`, `Creator`, `CreateTime`) VALUES (:FileName, :FolderName, :FileType, :FileSize, :Creator, :CreateTime)");
    query.bindValue(":FileName",fileName);
    query.bindValue(":FolderName",folderName);
    query.bindValue(":FileType",fileType);
    query.bindValue(":FileSize",fileSize);
    query.bindValue(":Creator",creator);
    query.bindValue(":CreateTime",QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss"));
    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();
        this->m_opLogMsg=QString("add file [%1:%2] failed:[%3].").arg(folderName).arg(fileName).arg(errMsg);
    }
    qDebug()<<query.lastQuery();
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("File"));
    tXmlWriter.writeStartElement(QString("File"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("folder"),folderName);
        tXmlWriter.writeAttribute(QString("type"),fileType);
        tXmlWriter.writeAttribute(QString("size"),QString("%1").arg(fileSize));
        tXmlWriter.writeAttribute(QString("creator"),creator);
    }
    tXmlWriter.writeCharacters(fileName);
    tXmlWriter.writeEndElement();//File.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmFile::ZAddData(QString folderName,QString fileName,QString fileData,QString totalBlock,QString currentBlock,QString creator)
{
    qint32 retCode=0;
    QString errMsg;
    //write data to local file.
    QString filePath(QDir::currentPath()+"/data/"+creator+"/file/"+folderName+"/"+fileName);
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        QByteArray fileDataArray=QByteArray::fromBase64(fileData.toUtf8());
        file.write(fileDataArray);
        //qDebug()<<fileData;
        qDebug()<<"PNetFrmFile::ZAddData: totalBlock="<<totalBlock<<",currentBlock="<<currentBlock<<",size="<<fileDataArray.size();
        file.close();
    }else{
        retCode=-1;
        errMsg=file.errorString();
    }

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("File"));
    tXmlWriter.writeStartElement(QString("File"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("updata"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("folder"),folderName);
        tXmlWriter.writeAttribute(QString("creator"),creator);
    }
    tXmlWriter.writeCharacters(fileName);
    tXmlWriter.writeEndElement();//File.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmFile::ZDelFile(QString folderName,QString fileName,QString creator)
{
    //DELETE FROM `pms`.`FileInfo` WHERE `FileName`='a.pdf';
    qint32 retCode;
    QSqlQuery query(this->m_db);
    query.prepare("DELETE FROM `pms`.`FileInfo` WHERE `FileName`= :FileName");
    query.bindValue(":FileName",fileName);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("delete file [%1:%2] success").arg(folderName).arg(fileName);
    }else{
        retCode=-1;
        this->m_opLogMsg=QString("delete file [%1:%2] failed:[%3].").arg(folderName).arg(fileName).arg(query.lastError().text());
    }
    //delete local file.
    QFile::remove(QDir::currentPath()+"/data/"+creator+"/file/"+folderName+"/"+fileName);

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("File"));
    tXmlWriter.writeStartElement(QString("File"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("folder"),folderName);
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),query.lastError().text());
    }else{
        tXmlWriter.writeAttribute(QString("errMsg"),"no");
    }
    tXmlWriter.writeCharacters(fileName);
    tXmlWriter.writeEndElement();//File.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
    this->m_opLogMsg=QString("delete file [%1] success").arg(fileName);
}
void PNetFrmFile::ZGetFile(QString folderName,QString fileName,QString creator)
{
    qint32 retCode=0;
    QString errMsg;
    QString filePath(QDir::currentPath()+"/data/"+creator+"/file/"+folderName+"/"+fileName);
    QFile file(filePath);
    qint32 totalBlock=file.size()/(1*1024*1024);
    qint32 remainBytes=file.size()%(1*1024*1024);

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("File"));
    tXmlWriter.writeStartElement(QString("File"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("folder"),folderName);
        tXmlWriter.writeAttribute(QString("totalBlock"),QString("%1").arg(totalBlock));
        tXmlWriter.writeAttribute(QString("blockSize"),QString("%1").arg(1*1024*1024));
        tXmlWriter.writeAttribute(QString("remainBytes"),QString("%1").arg(remainBytes));
    }
    tXmlWriter.writeCharacters(fileName);
    tXmlWriter.writeEndElement();//File.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmFile::ZGetData(QString folderName,QString fileName,QString totalBlock,QString currentBlock,qint32 readPos,qint32 readSize,QString creator)
{
    qint32 retCode=0;
    QString errMsg;
    QByteArray byteArray;
    QString filePath(QDir::currentPath()+"/data/"+creator+"/file/"+folderName+"/"+fileName);
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        file.seek(readPos);
        byteArray=file.read(readSize);
        file.close();
    }else{
        retCode=-1;
        errMsg=file.errorString();
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("File"));
    tXmlWriter.writeStartElement(QString("File"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("dwndata"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("folder"),folderName);
        tXmlWriter.writeAttribute(QString("totalBlock"),totalBlock);
        tXmlWriter.writeAttribute(QString("currentBlock"),currentBlock);
        tXmlWriter.writeAttribute(QString("data"),byteArray.toBase64());
    }
    tXmlWriter.writeCharacters(fileName);
    tXmlWriter.writeEndElement();//File.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
PNetFrmUpdate::PNetFrmUpdate(QSqlDatabase db):PNetFrm(db)
{

}
void PNetFrmUpdate::ZGetNewVersion(QString totalBlock,QString currentBlock,qint32 readPos,qint32 readSize)
{
    qint32 retCode=0;
    QString errMsg;
    QByteArray byteArray;
    QString filePath(QDir::currentPath()+"/update/PMSManager.exe");
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        file.seek(readPos);
        byteArray=file.read(readSize);
        file.close();
    }else{
        retCode=-1;
        errMsg=file.errorString();
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Update"));
    tXmlWriter.writeStartElement(QString("Update"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("totalBlock"),totalBlock);
        tXmlWriter.writeAttribute(QString("currentBlock"),currentBlock);
        tXmlWriter.writeAttribute(QString("data"),byteArray.toBase64());
    }
    tXmlWriter.writeCharacters("PMSManager.exe");
    tXmlWriter.writeEndElement();//Update.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
