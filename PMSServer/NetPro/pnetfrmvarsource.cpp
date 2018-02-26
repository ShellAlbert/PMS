#include "pnetfrmvarsource.h"
#include <QXmlStreamWriter>
#include <QDir>
#include <QFile>
#include <QDebug>
PNetFrmVarSource::PNetFrmVarSource(QSqlDatabase db):PNetFrm(db)
{

}
void PNetFrmVarSource::ZAddVarSource(QString name,QString creator)
{
    //INSERT INTO `pms`.`VarSourceInfo` (`VarSourceName`, `RefCount`,`Creator`, `CreateTime`) VALUES ('yantai', 0, 'zhangshaoyan', '2017-01-10 12:12:12');
    qint32 retCode;
    QString errMsg;
    QString createTime=QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss");
    QSqlQuery query(this->m_db);
    query.prepare("INSERT INTO `pms`.`VarSourceInfo` (`VarSourceName`, `RefCount`, `Creator`, `CreateTime`) VALUES (:VarSourceName, :RefCount, :Creator, :CreateTime)");
    query.bindValue(":VarSourceName",name);
    query.bindValue(":RefCount",0);
    query.bindValue(":Creator",creator);
    query.bindValue(":CreateTime",createTime);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("add VarSource [%1] success").arg(name);
    }else{
        retCode=-1;
        errMsg=query.lastError().text();
        this->m_opLogMsg=QString("add VarSource [%1] failed:[%2].").arg(name).arg(errMsg);
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("VarSource"));
    tXmlWriter.writeStartElement(QString("VarSource"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("refCount"),QString("0"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeAttribute(QString("creator"),creator);
    tXmlWriter.writeAttribute(QString("createTime"),createTime);
    tXmlWriter.writeCharacters(name);
    tXmlWriter.writeEndElement();//VarSource.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmVarSource::ZDelVarSource(QString name,QString creator)
{
    //DELETE FROM `pms`.`VarSourceInfo` WHERE `VarSourceName`='yantai';
    qint32 retCode;
    QSqlQuery query(this->m_db);
    query.prepare("DELETE FROM `pms`.`VarSourceInfo` WHERE `VarSourceName`=:VarSourceName AND `Creator`=:Creator");
    query.bindValue(":VarSourceName",name);
    query.bindValue(":Creator",creator);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("delete VarSource [%1] success").arg(name);
    }else{
        retCode=-1;
        this->m_opLogMsg=QString("delete VarSource [%1] failed:[%2].").arg(name).arg(query.lastError().text());
    }

    //remove file.
    QFile::remove(QDir::currentPath()+"/data/"+creator+"/varsource/"+name+".xml");

    //drop table.
    QSqlQuery query2(this->m_db);
    if(query2.exec(QString("DROP TABLE `pms`.`%1_Data`").arg(name)))
    {
        qDebug()<<"drop table okay";
    }else{
        qDebug()<<"drop table failed:"<<query2.lastError().text();
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("VarSource"));
    tXmlWriter.writeStartElement(QString("VarSource"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),query.lastError().text());
    }else{
        tXmlWriter.writeAttribute(QString("errMsg"),"no");
    }
    tXmlWriter.writeCharacters(name);
    tXmlWriter.writeEndElement();//VarSource.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmVarSource::ZSaveVarSource(QString name,QString xmlData,QString creator)
{
    //write data to file at rundir/data/user/varsource/ path.
    qint32 retCode;
    QString errMsg;
    QString varSrcXmlData=QString(QByteArray::fromBase64(xmlData.toUtf8()));
    //create user dir if it is not exist.
    QString destDirStr=QDir::currentPath()+"/data/"+creator+"/varsource";
    QDir destDir;
    if(!destDir.exists(destDirStr))
    {
        destDir.mkpath(destDirStr);
    }
    QFile varSourceFile(destDirStr+"/"+name+".xml");
    if(varSourceFile.open(QIODevice::WriteOnly))
    {
        varSourceFile.write(varSrcXmlData.toUtf8());
        varSourceFile.flush();
        varSourceFile.close();
        retCode=0;
    }else{
        retCode=-1;
        errMsg=varSourceFile.errorString();
    }

    //parse out table structure and create a new table.
    //    CREATE TABLE IF NOT EXISTS `pms`.`Template1_Data` (
    //      `TaskName` VARCHAR(45) NOT NULL COMMENT '',
    //      `CurDate` DATETIME NULL COMMENT '',
    //      `LineNo` VARCHAR(45) NULL COMMENT '',
    //      PRIMARY KEY (`TaskName`)  COMMENT '');
    QSqlQuery query(this->m_db);
    if(query.exec(QString("DROP TABLE `pms`.`%1_Data`").arg(name)))
    {
        qDebug()<<"drop table okay";
    }else{
        qDebug()<<"drop table failed:"<<query.lastError().text();
    }

    QString sql;
    sql.append(QString("CREATE TABLE IF NOT EXISTS `pms`.`%1` (").arg(name+"_Data"));
    sql.append("`TaskName` VARCHAR(45) NOT NULL COMMENT '',");
    QXmlStreamReader tXmlReader(varSrcXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("GeVar"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString type=attr.value(QString("type")).toString();
                QString name=tXmlReader.readElementText();
                if(type=="String")
                {
                    sql.append(QString("`%1` VARCHAR(45) NULL COMMENT '',").arg(name));
                }else if(type=="Digital")
                {
                    sql.append(QString("`%1` INT NULL COMMENT '',").arg(name));
                }else if(type=="Boolean")
                {
                    sql.append(QString("`%1` INT NULL COMMENT '',").arg(name));
                }else if(type=="Datetime")
                {
                    sql.append(QString("`%1` DATETIME NULL COMMENT '',").arg(name));
                }
            }else if(nodeName==QString("AutoVar"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString type=attr.value(QString("type")).toString();
                QString name=tXmlReader.readElementText();
                if(type=="String")
                {
                    sql.append(QString("`%1` VARCHAR(45) NULL COMMENT '',").arg(name));
                }else if(type=="Digital")
                {
                    sql.append(QString("`%1` INT NULL COMMENT '',").arg(name));
                }else if(type=="Boolean")
                {
                    sql.append(QString("`%1` INT NULL COMMENT '',").arg(name));
                }else if(type=="Datetime")
                {
                    sql.append(QString("`%1` DATETIME NULL COMMENT '',").arg(name));
                }
            }
        }//StarElement.
    }//while().
    sql.append("PRIMARY KEY (`TaskName`)  COMMENT '')");
    qDebug()<<sql;
    QSqlQuery query2(this->m_db);
    if(query2.exec(sql))
    {
        qDebug()<<"create varsrc data table okay";
    }else{
        qDebug()<<"failed to create varsrc data table";
    }

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("VarSource"));
    tXmlWriter.writeStartElement(QString("VarSource"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("save"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(name);
    tXmlWriter.writeEndElement();//VarSource.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmVarSource::ZGetVarSource(QString name,QString creator)
{
    qint32 retCode;
    QString errMsg;
    QByteArray data;
    QFile varSourceFile(QDir::currentPath()+"/data/"+creator+"/varsource/"+name+".xml");
    if(varSourceFile.open(QIODevice::ReadOnly))
    {
        retCode=0;
        data=varSourceFile.readAll().toBase64();
        varSourceFile.close();
        this->m_opLogMsg=QString("get VarSource file [%1] success").arg(name);
        errMsg=QString("no");
    }else{
        retCode=-1;
        this->m_opLogMsg=QString("get VarSource file [%1] failed:[%2].").arg(name).arg(varSourceFile.errorString());
        errMsg=varSourceFile.errorString();
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("VarSource"));
    tXmlWriter.writeStartElement(QString("VarSource"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("data"),QString(data));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(name);
    tXmlWriter.writeEndElement();//VarSource.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
