#include "pnetfrmuser.h"
#include <QXmlStreamWriter>
#include <AES/TAesClass.h>
#include <QDebug>
PNetFrmUser::PNetFrmUser(QSqlDatabase db):PNetFrm(db)
{

}
void PNetFrmUser::ZAddUser(QString userName,QString password,QString roleName,QString realName,QString sex,QString mobile,QString creator)
{
    //INSERT INTO `pms`.`UserInfo` (`UserName`, `RoleName`, `Password`,`RealName`, `Sex`, `Mobile`, `Creator`, `CreateTime`, `LastLoginTime`) VALUES ('23', 'asdfa', '132', 'asdfa', 'asdfa', 'asdfa', 'asdfa', '2016-12-23 11:11:11', '2017-1-1 1:1:1');
    qint32 retCode=0;
    QString errMsg;
    QString createTime=QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss");
    QSqlQuery query(this->m_db);
    query.prepare("INSERT INTO `pms`.`UserInfo` (`UserName`, `RoleName`, `Password`,`RealName`, `Sex`, `Mobile`, `Creator`, `CreateTime`, `LastLoginTime`) VALUES (:UserName, :RoleName, :Password, :RealName, :Sex, :Mobile, :Creator, :CreateTime, :LastLoginTime)");
    query.bindValue(":UserName",userName);
    query.bindValue(":RoleName",roleName);
    query.bindValue(":Password",password);
    query.bindValue(":RealName",realName);
    query.bindValue(":Sex",sex);
    query.bindValue(":Mobile",mobile);
    query.bindValue(":Creator",creator);
    query.bindValue(":CreateTime",createTime);
    query.bindValue(":LastLoginTime",QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss"));
    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();
    }

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("User"));
    tXmlWriter.writeStartElement(QString("User"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        this->m_opLogMsg=QString("add user [%1] failed:[%2].").arg(userName).arg(errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("realName"),realName);
        tXmlWriter.writeAttribute(QString("roleName"),roleName);
        tXmlWriter.writeAttribute(QString("sex"),sex);
        tXmlWriter.writeAttribute(QString("mobile"),mobile);
        tXmlWriter.writeAttribute(QString("password"),password);
        tXmlWriter.writeAttribute(QString("creator"),creator);
        tXmlWriter.writeAttribute(QString("createTime"),createTime);
        this->m_opLogMsg=QString("add user [%1] success").arg(userName);
    }
    tXmlWriter.writeCharacters(userName);
    tXmlWriter.writeEndElement();//User.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmUser::ZMdyUser(QString userName,QString password,QString roleName,QString realName,QString sex,QString mobile,QString creator)
{
    //UPDATE `pms`.`UserInfo` SET `RoleName`='456', `Password`='456', `RealName`='456', `Sex`='a', `Mobile`='f' WHERE `UserName`='asdf';
    qint32 retCode=0;
    QString errMsg;
    QSqlQuery query(this->m_db);
    query.prepare("UPDATE `pms`.`UserInfo` SET `RoleName`= :RoleName , `Password`= :Password, `RealName`= :RealName, `Sex`= :Sex, `Mobile`= :Mobile  WHERE `UserName`= :UserName");
    query.bindValue(":RoleName",roleName);
    query.bindValue(":Password",password);
    query.bindValue(":RealName",realName);
    query.bindValue(":Sex",sex);
    query.bindValue(":Mobile",mobile);
    query.bindValue(":UserName",userName);

    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();
    }

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("User"));
    tXmlWriter.writeStartElement(QString("User"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("mdy"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        this->m_opLogMsg=QString("modify user [%1:%2] failed:[%3].").arg(roleName).arg(userName).arg(errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("realName"),realName);
        tXmlWriter.writeAttribute(QString("roleName"),roleName);
        tXmlWriter.writeAttribute(QString("sex"),sex);
        tXmlWriter.writeAttribute(QString("mobile"),mobile);
        tXmlWriter.writeAttribute(QString("creator"),creator);
        this->m_opLogMsg=QString("modify user [%1:%2] success").arg(roleName).arg(userName);
    }
    tXmlWriter.writeCharacters(userName);
    tXmlWriter.writeEndElement();//User.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmUser::ZDelUser(QString userName,QString roleName)
{
    //DELETE FROM `pms`.`UserInfo` WHERE `UserName`='abc' and `RoleName`='China';
    qint32 retCode=0;
    QString errMsg;
    QSqlQuery query(this->m_db);
    query.prepare("DELETE FROM `pms`.`UserInfo` WHERE `UserName`= :UserName and `RoleName`= :RoleName ");
    query.bindValue(":UserName",userName);
    query.bindValue(":RoleName",roleName);
    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();

    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("User"));
    tXmlWriter.writeStartElement(QString("User"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),query.lastError().text());
        this->m_opLogMsg=QString("delete user [%1:%2] failed:[%3].").arg(roleName).arg(userName).arg(errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("roleName"),roleName);
        this->m_opLogMsg=QString("delete user [%1:%2] success").arg(roleName).arg(userName);
    }
    tXmlWriter.writeCharacters(userName);
    tXmlWriter.writeEndElement();//User.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
