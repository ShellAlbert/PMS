#include "pnetfrmform.h"
#include <QXmlStreamWriter>
#include <QFile>
#include <QDir>
PNetFrmForm::PNetFrmForm(QSqlDatabase db):PNetFrm(db)
{

}
void PNetFrmForm::ZNewForm(QString formName,QString creator)
{
    //INSERT INTO `pms`.`FormInfo`  (`FormName`,`FileSize`,`Creator`,`CreateTime`) VALUES ('china',110,'root','2017-02-02 12:12:22');
    qint32 retCode;
    QString createTime=QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss");
    QSqlQuery query(this->m_db);
    query.prepare("INSERT INTO `pms`.`FormInfo`  (`FormName`,`FileSize`,`Creator`,`CreateTime`) VALUES (:FormName,:FileSize,:Creator,:CreateTime)");
    query.bindValue(":FormName",formName);
    query.bindValue(":FileSize",0);
    query.bindValue(":Creator",creator);
    query.bindValue(":CreateTime",createTime);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("add form [%1] success").arg(formName);
    }else{
        retCode=-1;
        this->m_opLogMsg=QString("add form [%1] failed:[%2].").arg(formName).arg(query.lastError().text());
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Form"));
    tXmlWriter.writeStartElement(QString("Form"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),query.lastError().text());
    }else{
        tXmlWriter.writeAttribute(QString("creator"),creator);
        tXmlWriter.writeAttribute(QString("createTime"),createTime);
    }
    tXmlWriter.writeCharacters(formName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmForm::ZDelForm(QString formName,QString creator)
{
    //DELETE FROM `pms`.`FormInfo` WHERE `FormName`='adsfa';
    qint32 retCode;
    QSqlQuery query(this->m_db);
    query.prepare("DELETE FROM `pms`.`FormInfo` WHERE `FormName`=:FormName AND `Creator`=:Creator");
    query.bindValue(":FormName",formName);
    query.bindValue(":Creator",creator);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("delete form [%1] success").arg(formName);
    }else{
        retCode=-1;
        this->m_opLogMsg=QString("delete form [%1] failed:[%2].").arg(formName).arg(query.lastError().text());
    }
    //delete form xml file.
    QFile::remove(QDir::currentPath()+"/data/"+creator+"/form/"+formName+".xml");

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Form"));
    tXmlWriter.writeStartElement(QString("Form"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),query.lastError().text());
    }else{
        tXmlWriter.writeAttribute(QString("creator"),creator);
    }
    tXmlWriter.writeCharacters(formName);
    tXmlWriter.writeEndElement();//Form.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmForm::ZGetForm(QString formName,QString creator)
{
    qint32 retCode;
    QString errMsg;
    //template xml file.
    QByteArray data;
    QFile formFile(QDir::currentPath()+"/data/"+creator+"/form/"+formName+".xml");
    if(formFile.open(QIODevice::ReadOnly))
    {
        retCode=0;
        data=formFile.readAll().toBase64();
        formFile.close();
        this->m_opLogMsg=QString("get form file [%1] success").arg(formName);
    }else{
        retCode=-1;
        errMsg=formFile.errorString();
        this->m_opLogMsg=QString("get form file [%1] failed:[%2].").arg(formName).arg(formFile.errorString());
    }

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Form"));
    tXmlWriter.writeStartElement(QString("Form"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("data"),QString(data));
        tXmlWriter.writeAttribute(QString("creator"),creator);
    }
    tXmlWriter.writeCharacters(formName);
    tXmlWriter.writeEndElement();//Form.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmForm::ZSaveForm(QString formName,QString xmlData,QString creator)
{
    //write data to file at rundir/data/  path.
    qint32 retCode;
    QString errMsg;
    //create user dir if it is not exist.
    QString destDirStr=QDir::currentPath()+"/data/"+creator+"/form";
    QDir dir;
    dir.mkpath(destDirStr);

    QFile formFile(destDirStr+"/"+formName+".xml");
    if(formFile.open(QIODevice::WriteOnly))
    {
        formFile.write(QByteArray::fromBase64(xmlData.toUtf8()));
        formFile.flush();
        formFile.close();
        retCode=0;
    }else{
        retCode=-1;
        errMsg=formFile.errorString();
    }
    //UPDATE `pms`.`FormInfo` SET `FileSize`='10' WHERE `FormName`='abc';
    QSqlQuery query(this->m_db);
    query.prepare("UPDATE `pms`.`FormInfo` SET `FileSize`=:FileSize WHERE `FormName`=:FormName");
    query.bindValue(":FileSize",formFile.size());
    query.bindValue(":FormName",formName);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("save form [%1] success").arg(formName);
    }else{
        retCode=-1;
        errMsg+=query.lastError().text();
        this->m_opLogMsg=QString("save form [%1] failed:[%2].").arg(formName).arg(query.lastError().text());
    }

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Form"));
    tXmlWriter.writeStartElement(QString("Form"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("save"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("fileSize"),QString("%1").arg(formFile.size()/1024));
    }
    tXmlWriter.writeCharacters(formName);
    tXmlWriter.writeEndElement();//Form.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmForm::ZListForm(QString creator)
{
    //SELECT `FormName`,`FileSize`,`Creator`,`CreateTime` FROM `pm`s.`FormInfo`;
    qint32 retCode=0;
    QString errMsg;
    QSqlQuery query(this->m_db);
    query.prepare("SELECT `FormName`,`FileSize`,`Creator`,`CreateTime` FROM `pms`.`FormInfo` WHERE `Creator`=:creator");
    query.bindValue(":creator",creator);
    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();
        this->m_opLogMsg=QString("list form attached to creator [%1] failed:[%2].").arg(creator).arg(errMsg);
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Form"));
    while(query.next())
    {
        QString formName=query.value(0).toString();
        QString fileSize=query.value(1).toString();
        QString creator=query.value(2).toString();
        QString createTime=query.value(3).toString();
        tXmlWriter.writeStartElement(QString("Form"));
        tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
        tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
        tXmlWriter.writeAttribute(QString("fileSize"),fileSize);
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        tXmlWriter.writeAttribute(QString("creator"),creator);
        tXmlWriter.writeAttribute(QString("createTime"),createTime);
        tXmlWriter.writeCharacters(formName);
        tXmlWriter.writeEndElement();//Form.
    }
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
