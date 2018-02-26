#include "pnetfrmfolder.h"
#include <QXmlStreamWriter>
#include <QDir>
PNetFrmFolder::PNetFrmFolder(QSqlDatabase db):PNetFrm(db)
{

}
void PNetFrmFolder::ZAddFolder(QString folderName,QString creator)
{
    //INSERT INTO `pms`.`FolderInfo` (`FolderName`, `Creator`, `CreateTime`) VALUES ('yantai', 'zhangshaoyan', '2016-12-29 12:12:12');
    qint32 retCode;
    QSqlQuery query(this->m_db);
    query.prepare("INSERT INTO `pms`.`FolderInfo` (`FolderName`, `Creator`, `CreateTime`) VALUES (:FolderName, :Creator, :CreateTime)");
    query.bindValue(":FolderName",folderName);
    query.bindValue(":Creator",creator);
    query.bindValue(":CreateTime",QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss"));
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("add folder [%1] success").arg(folderName);
    }else{
        retCode=-1;
        this->m_opLogMsg=QString("add folder [%1] failed:[%2].").arg(folderName).arg(query.lastError().text());
    }
    //mkdir local dir.
    QDir dir;
    dir.mkpath(QDir::currentPath()+"/data/"+creator+"/file/"+folderName);


    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Folder"));
    tXmlWriter.writeStartElement(QString("Folder"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),query.lastError().text());
    }else{
        tXmlWriter.writeAttribute(QString("errMsg"),"no");
    }
    tXmlWriter.writeCharacters(folderName);
    tXmlWriter.writeEndElement();//Folder.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmFolder::ZDelFolder(QString folderName,QString creator)
{
    //DELETE FROM `pms`.`FolderInfo` WHERE `FolderName`='yantai';
    qint32 retCode;
    QSqlQuery query(this->m_db);
    query.prepare("DELETE FROM `pms`.`FolderInfo` WHERE `FolderName`=:FolderName");
    query.bindValue(":FolderName",folderName);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("delete folder [%1] success").arg(folderName);
    }else{
        retCode=-1;
        this->m_opLogMsg=QString("delete folder [%1] failed:[%2].").arg(folderName).arg(query.lastError().text());
    }

    //delete local dir.
    QDir dir;
    dir.rmdir(QDir::currentPath()+"/data/"+creator+"/file/"+folderName);

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Folder"));
    tXmlWriter.writeStartElement(QString("Folder"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),query.lastError().text());
    }else{
        tXmlWriter.writeAttribute(QString("errMsg"),"no");
    }
    tXmlWriter.writeCharacters(folderName);
    tXmlWriter.writeEndElement();//Folder.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmFolder::ZListFolder(QString creator)
{
    //SELECT `FolderName`,`Creator`,`CreateTime` FROM `pms`.`FolderInfo` WHERE `Creator`='root';
    qint32 retCode;
    QStringList folderList;
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Folder"));

    QSqlQuery folderQuery(this->m_db);
    folderQuery.prepare("SELECT `FolderName`,`Creator`,`CreateTime` FROM `pms`.`FolderInfo` WHERE `Creator`=:creator ");
    folderQuery.bindValue(":creator",creator);
    if(folderQuery.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("list folder attached to creator [%1] success").arg(creator);
    }else{
        retCode=-1;
        this->m_opLogMsg=QString("list folder attached to creator [%1] failed:[%2].").arg(creator).arg(folderQuery.lastError().text());
    }
    while(folderQuery.next())
    {
        QString folderName=folderQuery.value(0).toString();
        QString creator=folderQuery.value(1).toString();
        QString createTime=folderQuery.value(2).toString();
        tXmlWriter.writeStartElement(QString("Folder"));
        tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
        tXmlWriter.writeAttribute(QString("item"),QString("folder"));
        tXmlWriter.writeAttribute(QString("creator"),creator);
        tXmlWriter.writeAttribute(QString("createTime"),createTime);
        tXmlWriter.writeCharacters(folderName);
        tXmlWriter.writeEndElement();//Folder.
        folderList.append(folderName);
    }
    for(qint32 i=0;i<folderList.count();i++)
    {
        //continue to query file.
        //SELECT `FileName`,`FolderName`,`FileType`,`FileSize`,`Creator`,`CreateTime` FROM pms.FileInfo WHERE `FolderName`='1111';
        QSqlQuery fileQuery(this->m_db);
        fileQuery.prepare("SELECT `FileName`,`FolderName`,`FileType`,`FileSize`,`Creator`,`CreateTime` FROM pms.FileInfo WHERE `FolderName`= :FolderName ");
        fileQuery.bindValue(":FolderName",folderList.at(i));
        if(fileQuery.exec())
        {
            retCode=0;
            this->m_opLogMsg=QString("list file attached to folder [%1] success").arg(folderList.at(i));
        }else{
            retCode=-1;
            this->m_opLogMsg=QString("list file attached to folder [%1] failed:[%2].").arg(folderList.at(i)).arg(fileQuery.lastError().text());
        }
        while(fileQuery.next())
        {
            QString fileName=fileQuery.value(0).toString();
            QString folderName=fileQuery.value(1).toString();
            QString fileType=fileQuery.value(2).toString();
            QString fileSize=fileQuery.value(3).toString();
            QString creator=fileQuery.value(4).toString();
            QString createTime=fileQuery.value(5).toString();
            tXmlWriter.writeStartElement(QString("Folder"));
            tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
            tXmlWriter.writeAttribute(QString("item"),QString("file"));
            tXmlWriter.writeAttribute(QString("folderName"),folderName);
            tXmlWriter.writeAttribute(QString("type"),fileType);
            tXmlWriter.writeAttribute(QString("size"),fileSize);
            tXmlWriter.writeAttribute(QString("creator"),creator);
            tXmlWriter.writeAttribute(QString("createTime"),createTime);
            tXmlWriter.writeCharacters(fileName);
            tXmlWriter.writeEndElement();//Folder.
        }
    }
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
