#include "pnetfrmrole.h"
#include <QXmlStreamWriter>
PNetFrmRole::PNetFrmRole(QSqlDatabase db):PNetFrm(db)
{

}
void PNetFrmRole::ZAddRole(QString roleName,QString permBits,QString roleMemo,QString creator)
{
    qint32 retCode=0;
    QString errMsg;
    QString createTime=QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss");
    //INSERT INTO `pms`.`RoleInfo` (`RoleName`, `PermBits`, `RoleMemo`, `Creator`, `CreateTime`) VALUES ('hello', '12', 'memohere', 'root', '2016-12-23 11:00:23');
    QSqlQuery query(this->m_db);
    query.prepare("INSERT INTO `pms`.`RoleInfo` (`RoleName`, `PermBits`, `RoleMemo`, `Creator`, `CreateTime`) VALUES (:RoleName , :PermBits , :RoleMemo, :Creator , :CreateTime)");
    query.bindValue(":RoleName",roleName);
    query.bindValue(":PermBits",permBits);
    query.bindValue(":RoleMemo",roleMemo);
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
    tXmlWriter.writeAttribute(QString("dest"),QString("Role"));
    tXmlWriter.writeStartElement(QString("Role"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        this->m_opLogMsg=QString("add role [%1] failed:[%2].").arg(roleName).arg(errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("permBits"),permBits);
        tXmlWriter.writeAttribute(QString("memo"),roleMemo);
        tXmlWriter.writeAttribute(QString("creator"),creator);
        tXmlWriter.writeAttribute(QString("createTime"),createTime);
        this->m_opLogMsg=QString("add role [%1] success").arg(roleName);
    }
    tXmlWriter.writeCharacters(roleName);
    tXmlWriter.writeEndElement();//Role.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmRole::ZMdyRole(QString roleName,QString permBits,QString roleMemo,QString creator)
{
    qint32 retCode;
    QString errMsg;
    //UPDATE `pms`.`RoleInfo` SET `PermBits`='adfa', `RoleMemo`='safasf', `Creator`='asfas', `CreateTime`='2017-02-07 23:47:32' WHERE `RoleName`='China';
    QSqlQuery query(this->m_db);
    query.prepare("UPDATE `pms`.`RoleInfo` SET `PermBits`=:PermBits, `RoleMemo`=:RoleMemo, `Creator`=:Creator, `CreateTime`=:CreateTime WHERE `RoleName`=:RoleName");
    query.bindValue(":PermBits",permBits);
    query.bindValue(":RoleMemo",roleMemo);
    query.bindValue(":RoleMemo",roleMemo);
    query.bindValue(":Creator",creator);
    query.bindValue(":CreateTime",QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss"));
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
    tXmlWriter.writeAttribute(QString("dest"),QString("Role"));
    tXmlWriter.writeStartElement(QString("Role"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("mdy"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(0));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        this->m_opLogMsg=QString("modify role [%1] failed:[%2].").arg(roleName).arg(errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("permBits"),permBits);
        tXmlWriter.writeAttribute(QString("memo"),roleMemo);
        tXmlWriter.writeAttribute(QString("creator"),creator);
        this->m_opLogMsg=QString("modify role [%1] success").arg(roleName);
    }
    tXmlWriter.writeCharacters(roleName);
    tXmlWriter.writeEndElement();//Role.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmRole::ZDelRole(QString roleName)
{
    qint32 retCode=0;
    QString errMsg;
    //DELETE FROM `pms`.`RoleInfo` WHERE `RoleName`='China';
    QSqlQuery query(this->m_db);
    query.prepare("DELETE FROM `pms`.`RoleInfo` WHERE `RoleName`= :RoleName");
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
    tXmlWriter.writeAttribute(QString("dest"),QString("Role"));
    tXmlWriter.writeStartElement(QString("Role"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        this->m_opLogMsg=QString("delete role [%1] failed:[%2].").arg(roleName).arg(errMsg);
    }else{
        this->m_opLogMsg=QString("delete role [%1] success").arg(roleName);
    }
    tXmlWriter.writeCharacters(roleName);
    tXmlWriter.writeEndElement();//Role.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmRole::ZListRole(QString creator)
{
    //SELECT `RoleName`,`PermBits`,`RoleMemo`,`Creator`,`CreateTime` FROM pms.RoleInfo WHERE `Creator`='root';
    qint32 retCode=0;
    QString errMsg;
    QStringList roleList;
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Role"));

    QSqlQuery roleQuery(this->m_db);
    roleQuery.prepare("SELECT `RoleName`,`PermBits`,`RoleMemo`,`Creator`,`CreateTime` FROM pms.RoleInfo WHERE `Creator`= :creator AND `RoleName`!='admin'");
    roleQuery.bindValue(":creator",creator);
    if(!roleQuery.exec())
    {
        retCode=-1;
        errMsg=roleQuery.lastError().text();
        this->m_opLogMsg=QString("list role attached to creator [%1] failed:[%2].").arg(creator).arg(errMsg);
    }else{
        this->m_opLogMsg=QString("list role attached to creator [%1] success").arg(creator);
        while(roleQuery.next())
        {
            QString roleName=roleQuery.value(0).toString();
            QString permBits=roleQuery.value(1).toString();
            QString roleMemo=roleQuery.value(2).toString();
            QString creator=roleQuery.value(3).toString();
            QString createTime=roleQuery.value(4).toString();
            tXmlWriter.writeStartElement(QString("Role"));
            tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
            tXmlWriter.writeAttribute(QString("item"),QString("role"));
            tXmlWriter.writeAttribute(QString("permBits"),permBits);
            tXmlWriter.writeAttribute(QString("roleMemo"),roleMemo);
            tXmlWriter.writeAttribute(QString("creator"),creator);
            tXmlWriter.writeAttribute(QString("createTime"),createTime);
            tXmlWriter.writeCharacters(roleName);
            tXmlWriter.writeEndElement();//Role.
            roleList.append(roleName);
        }
        //continue to query user.
        for(qint32 i=0;i<roleList.count();i++)
        {
            //SELECT `UserName`,`RoleName`,`RealName`,`Sex`,`Mobile`,`Creator`,`CreateTime`,`LastLoginTime` FROM pms.UserInfo WHERE `Creator`='root';
            QSqlQuery userQuery(this->m_db);
            userQuery.prepare("SELECT `UserName`,`RoleName`,`RealName`,`Sex`,`Mobile`,`Creator`,`CreateTime`,`LastLoginTime` FROM pms.UserInfo WHERE `RoleName`= :RoleName");
            userQuery.bindValue(":RoleName",roleList.at(i));
            if(!userQuery.exec())
            {
                retCode=-1;
                errMsg=userQuery.lastError().text();
                this->m_opLogMsg=QString("list user attached to role [%1] failed:[%2].").arg(roleList.at(i)).arg(errMsg);
            }else{
                this->m_opLogMsg=QString("list user attached to role [%1] success").arg(roleList.at(i));
                while(userQuery.next())
                {
                    QString userName=userQuery.value(0).toString();
                    QString roleName=userQuery.value(1).toString();
                    QString realName=userQuery.value(2).toString();
                    QString sex=userQuery.value(3).toString();
                    QString mobile=userQuery.value(4).toString();
                    QString creator=userQuery.value(5).toString();
                    QString createTime=userQuery.value(6).toString();
                    QString lastLoginTime=userQuery.value(7).toString();
                    tXmlWriter.writeStartElement(QString("Role"));
                    tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
                    tXmlWriter.writeAttribute(QString("item"),QString("user"));
                    tXmlWriter.writeAttribute(QString("roleName"),roleName);
                    tXmlWriter.writeAttribute(QString("realName"),realName);
                    tXmlWriter.writeAttribute(QString("sex"),sex);
                    tXmlWriter.writeAttribute(QString("mobile"),mobile);
                    tXmlWriter.writeAttribute(QString("creator"),creator);
                    tXmlWriter.writeAttribute(QString("createTime"),createTime);
                    tXmlWriter.writeAttribute(QString("lastLoginTime"),lastLoginTime);
                    tXmlWriter.writeCharacters(userName);
                    tXmlWriter.writeEndElement();//Role.
                }
            }
        }
    }
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
