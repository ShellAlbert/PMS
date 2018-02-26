#include "pnetfrmtemplate.h"
#include <QXmlStreamWriter>
#include <QDebug>
#include <QDir>
#include <QFile>
PNetFrmTemplate::PNetFrmTemplate(QSqlDatabase db):PNetFrm(db)
{

}
void PNetFrmTemplate::ZAddTemplate(QString templateName,QString creator)
{
    //INSERT INTO `pms`.`TemplateInfo` (`TemplateName`, `VarSourceName`,`FileSize`,`Creator`, `CreateTime`) VALUES ('abc','adsfa', 0,'asdfa', '2016-12-12 12:12:12');
    qint32 retCode;
    QString createTime=QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss");
    QSqlQuery query(this->m_db);
    query.prepare("INSERT INTO `pms`.`TemplateInfo` (`TemplateName`, `VarSourceName`,`FileSize`,`Creator`, `CreateTime`) VALUES (:TemplateName,:VarSourceName,:FileSize,:Creator, :CreateTime)");
    query.bindValue(":TemplateName",templateName);
    query.bindValue(":VarSourceName",QString(""));
    query.bindValue(":FileSize",0);
    query.bindValue(":Creator",creator);
    query.bindValue(":CreateTime",createTime);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("add template [%1] success").arg(templateName);
    }else{
        retCode=-1;
        this->m_opLogMsg=QString("add template [%1] failed:[%2].").arg(templateName).arg(query.lastError().text());
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    tXmlWriter.writeStartElement(QString("Template"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("creator"),creator);
    tXmlWriter.writeAttribute(QString("createTime"),createTime);
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),query.lastError().text());
    }else{
        tXmlWriter.writeAttribute(QString("errMsg"),"no");
    }
    tXmlWriter.writeCharacters(templateName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTemplate::ZDelTemplate(QString templateName,QString creator)
{
    //DELETE FROM `pms`.`TemplateInfo` WHERE `TemplateName`='adsfa';
    qint32 retCode;
    QSqlQuery query(this->m_db);
    query.prepare("DELETE FROM `pms`.`TemplateInfo` WHERE `TemplateName`=:TemplateName");
    query.bindValue(":TemplateName",templateName);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("delete template [%1] success").arg(templateName);
    }else{
        retCode=-1;
        this->m_opLogMsg=QString("delete template [%1] failed:[%2].").arg(templateName).arg(query.lastError().text());
    }
    //delete template xml file.
    QFile::remove(QDir::currentPath()+"/data/"+creator+"/template/"+templateName+".xml");

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    tXmlWriter.writeStartElement(QString("Template"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("creator"),creator);
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),query.lastError().text());
    }else{
        tXmlWriter.writeAttribute(QString("errMsg"),"no");
    }
    tXmlWriter.writeCharacters(templateName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTemplate::ZGetTemplate(QString templateName,QString creator)
{
    qint32 retCode;
    QString errMsg("no");
    //template xml file.
    QByteArray data;
    QFile templateFile(QDir::currentPath()+"/data/"+creator+"/template/"+templateName+".xml");
    if(templateFile.open(QIODevice::ReadOnly))
    {
        retCode=0;
        data=templateFile.readAll().toBase64();
        templateFile.close();
        this->m_opLogMsg=QString("get template file [%1] success").arg(templateName);
    }else{
        retCode=-1;
        errMsg=templateFile.errorString();
        this->m_opLogMsg=QString("get template file [%1] failed:[%2].").arg(templateName).arg(templateFile.errorString());
    }

    //VarSource xml file.
    //SELECT `VarSourceName`,`FileSize` FROM `pms`.`TemplateInfo` WHERE `TemplateName`='abc';
    QString varSourceName;
    qint32 fileSize;
    QByteArray varSourceData;
    QSqlQuery query(this->m_db);
    query.prepare("SELECT `VarSourceName`,`FileSize` FROM `pms`.`TemplateInfo` WHERE `TemplateName`=:TemplateName");
    query.bindValue(":TemplateName",templateName);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("get VarSourceName [%1] success").arg(templateName);
    }else{
        retCode=-1;
        errMsg+=query.lastError().text();
        this->m_opLogMsg=QString("get VarSourceName [%1] failed:[%2].").arg(templateName).arg(query.lastError().text());
    }
    while(query.next())
    {
        varSourceName=query.value(0).toString();
        fileSize=query.value(1).toInt();
    }
    if(!varSourceName.isEmpty())
    {
        QFile varSourceFile(QDir::currentPath()+"/data/"+creator+"/varsource/"+varSourceName+".xml");
        if(varSourceFile.open(QIODevice::ReadOnly))
        {
            retCode=0;
            varSourceData=varSourceFile.readAll().toBase64();
            varSourceFile.close();
        }else{
            retCode=-1;
            errMsg+=varSourceFile.errorString();
            this->m_opLogMsg=QString("open VarSourceFile [%1] failed:[%2].").arg(varSourceName).arg(varSourceFile.errorString());
        }
    }

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    tXmlWriter.writeStartElement(QString("Template"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("data"),QString(data));
    tXmlWriter.writeAttribute(QString("filesize"),QString("%1").arg(fileSize));
    tXmlWriter.writeAttribute(QString("varsource"),QString(varSourceData));
    tXmlWriter.writeAttribute(QString("creator"),creator);
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(templateName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTemplate::ZSaveTemplate(QString templateName,QString templateXmlData,QString creator)
{
    //write data to file at rundir/data/  path.
    qint32 retCode;
    QString errMsg;
    //create user dir if it is not exist.
    QString destDirStr=QDir::currentPath()+"/data/"+creator+"/template";
    QDir dir;
    dir.mkpath(destDirStr);

    QFile templateFile(destDirStr+"/"+templateName+".xml");
    if(templateFile.open(QIODevice::WriteOnly))
    {
        templateFile.write(QByteArray::fromBase64(templateXmlData.toUtf8()));
        templateFile.flush();
        templateFile.close();
        retCode=0;
        errMsg=QString("no");
    }else{
        retCode=-1;
        errMsg=templateFile.errorString();
    }
    //UPDATE `pms`.`TemplateInfo` SET `FileSize`='10' WHERE `TemplateName`='abc';
    QSqlQuery query(this->m_db);
    query.prepare("UPDATE `pms`.`TemplateInfo` SET `FileSize`=:FileSize WHERE `TemplateName`=:TemplateName");
    query.bindValue(":FileSize",templateFile.size()/1024);
    query.bindValue(":TemplateName",templateName);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("save template [%1] success").arg(templateName);
    }else{
        retCode=-1;
        errMsg+=query.lastError().text();
        this->m_opLogMsg=QString("save template [%1] failed:[%2].").arg(templateName).arg(query.lastError().text());
    }


    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    tXmlWriter.writeStartElement(QString("Template"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("save"));
    tXmlWriter.writeAttribute(QString("filesize"),QString("%1").arg(templateFile.size()/1024));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(templateName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTemplate::ZBindVarSource(QString templateName,QString varSourceName,QString creator)
{
    //UPDATE `pms`.`TemplateInfo` SET `VarSourceName`='123' WHERE `TemplateName`='china';
    qint32 retCode;
    QString errMsg;
    QSqlQuery query(this->m_db);
    query.prepare("UPDATE `pms`.`TemplateInfo` SET `VarSourceName`=:VarSourceName WHERE `TemplateName`=:TemplateName");
    query.bindValue(":TemplateName",templateName);
    query.bindValue(":VarSourceName",varSourceName);
    if(query.exec())
    {
        retCode=0;
        errMsg=QString("no");
        this->m_opLogMsg=QString("bind VarSource[%1] to Template[%2] success.").arg(varSourceName).arg(templateName);
    }else{
        retCode=-1;
        errMsg=query.lastError().text();
        this->m_opLogMsg=QString("bind VarSource[%1] to Template[%2] failed:[%3].").arg(varSourceName).arg(templateName).arg(query.lastError().text());
    }
    //UPDATE `pms`.`VarSourceInfo` SET `RefCount`=`RefCount`+1 WHERE `VarSourceName`= 'var';
    QSqlQuery query2(this->m_db);
    query2.prepare("UPDATE `pms`.`VarSourceInfo` SET `RefCount`=`RefCount`+1 WHERE `VarSourceName`= :VarSourceName");
    query2.bindValue(":VarSourceName",varSourceName);
    if(query2.exec())
    {
        retCode=0;
        errMsg=QString("no");
        this->m_opLogMsg=QString("VarSource [%1] RefCount+1 success.").arg(varSourceName);
    }else{
        retCode=-1;
        errMsg=query2.lastError().text();
        this->m_opLogMsg=QString("VarSource [%1] RefCount+1 failed:%2.").arg(varSourceName).arg(query2.lastError().text());
    }

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    tXmlWriter.writeStartElement(QString("Template"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("bind"));
    tXmlWriter.writeAttribute(QString("varsource"),varSourceName);
    tXmlWriter.writeAttribute(QString("creator"),creator);
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(templateName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}

void PNetFrmTemplate::ZUnbindVarSource(QString templateName,QString varSourceName,QString creator)
{
    //UPDATE `pms`.`TemplateInfo` SET `VarSourceName`='' WHERE `TemplateName`='abc';
    qint32 retCode;
    QString errMsg;
    QSqlQuery query(this->m_db);
    query.prepare("UPDATE `pms`.`TemplateInfo` SET `VarSourceName`='' WHERE `TemplateName`=:TemplateName");
    query.bindValue(":TemplateName",templateName);
    if(query.exec())
    {
        retCode=0;
        errMsg=QString("no");
        this->m_opLogMsg=QString("unbind VarSource[%1] from Template[%2] success.").arg(varSourceName).arg(templateName);
    }else{
        retCode=-1;
        errMsg=query.lastError().text();
        this->m_opLogMsg=QString("unbind VarSource[%1] from Template[%2] failed:[%3].").arg(varSourceName).arg(templateName).arg(query.lastError().text());
    }

    //UPDATE `pms`.`VarSourceInfo` SET `RefCount`=`RefCount`-1 WHERE `VarSourceName`= 'var';
    QSqlQuery query2(this->m_db);
    query2.prepare("UPDATE `pms`.`VarSourceInfo` SET `RefCount`=`RefCount`-1 WHERE `VarSourceName`= :VarSourceName");
    query2.bindValue(":VarSourceName",varSourceName);
    if(query2.exec())
    {
        retCode=0;
        errMsg=QString("no");
        this->m_opLogMsg=QString("unbind VarSource[%1] from Template[%2] success.").arg(varSourceName).arg(templateName);
    }else{
        retCode=-1;
        errMsg=query2.lastError().text();
        this->m_opLogMsg=QString("unbind VarSource[%1] from Template[%2] failed:[%3].").arg(varSourceName).arg(templateName).arg(query2.lastError().text());
    }

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    tXmlWriter.writeStartElement(QString("Template"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("unbind"));
    tXmlWriter.writeAttribute(QString("varsource"),varSourceName);
    tXmlWriter.writeAttribute(QString("creator"),creator);
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(templateName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTemplate::ZListTemplate(QString creator)
{
    //SELECT `TemplateName`,`VarSourceName`,`FileSize`,`Creator`,`CreateTime` FROM `pm`s.`TemplateInfo`;
    qint32 retCode;
    QString errMsg;
    QSqlQuery templateQuery(this->m_db);
    templateQuery.prepare("SELECT `TemplateName`,`VarSourceName`,`FileSize`,`Creator`,`CreateTime` FROM `pms`.`TemplateInfo` WHERE `Creator`=:creator");
    templateQuery.bindValue(":creator",creator);
    if(templateQuery.exec())
    {
        retCode=0;
        errMsg=QString("no");
        this->m_opLogMsg=QString("list template attached to creator [%1] success").arg(creator);
    }else{
        retCode=-1;
        errMsg=templateQuery.lastError().text();
        this->m_opLogMsg=QString("list template attached to creator [%1] failed:[%2].").arg(creator).arg(errMsg);
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    while(templateQuery.next())
    {
        QString templateName=templateQuery.value(0).toString();
        QString varSourceName=templateQuery.value(1).toString();
        QString fileSize=templateQuery.value(2).toString();
        QString creator=templateQuery.value(3).toString();
        QString createTime=templateQuery.value(4).toString();
        tXmlWriter.writeStartElement(QString("Template"));
        tXmlWriter.writeAttribute(QString("item"),QString("template"));
        tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
        tXmlWriter.writeAttribute(QString("filesize"),fileSize);
        tXmlWriter.writeAttribute(QString("varsource"),varSourceName);
        tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        tXmlWriter.writeAttribute(QString("creator"),creator);
        tXmlWriter.writeAttribute(QString("createTime"),createTime);
        tXmlWriter.writeCharacters(templateName);
        tXmlWriter.writeEndElement();//Template.
    }
    //SELECT `VarSourceName`,`RefCount`,`Creator`,`CreateTime` FROM `pms`.`VarSourceInfo` WHERE `Creator`='root';
    QSqlQuery varSourceQuery(this->m_db);
    varSourceQuery.prepare("SELECT `VarSourceName`,`RefCount`,`Creator`,`CreateTime` FROM `pms`.`VarSourceInfo` WHERE `Creator`=:creator");
    varSourceQuery.bindValue(":creator",creator);
    if(varSourceQuery.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("list VarSource attached to creator [%1] success").arg(creator);
    }else{
        retCode=-1;
        this->m_opLogMsg=QString("list VarSource attached to creator [%1] failed:[%2].").arg(creator).arg(varSourceQuery.lastError().text());
    }
    while(varSourceQuery.next())
    {
        QString varSourceName=varSourceQuery.value(0).toString();
        QString refCount=varSourceQuery.value(1).toString();
        QString creator=varSourceQuery.value(2).toString();
        QString createTime=varSourceQuery.value(3).toString();
        tXmlWriter.writeStartElement(QString("Template"));
        tXmlWriter.writeAttribute(QString("item"),QString("varsource"));
        tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
        tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
        if(retCode<0)
        {
            tXmlWriter.writeAttribute(QString("errMsg"),varSourceQuery.lastError().text());
        }else{
            tXmlWriter.writeAttribute(QString("errMsg"),"no");
        }
        tXmlWriter.writeAttribute(QString("RefCount"),refCount);
        tXmlWriter.writeAttribute(QString("creator"),creator);
        tXmlWriter.writeAttribute(QString("createTime"),createTime);
        tXmlWriter.writeCharacters(varSourceName);
        tXmlWriter.writeEndElement();//Template.
    }
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
