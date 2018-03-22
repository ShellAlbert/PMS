#include "pnetfrmlogin.h"
#include <QXmlStreamWriter>
#include <AES/TAesClass.h>
#include <QDebug>
PNetFrmLogin::PNetFrmLogin(QSqlDatabase db):PNetFrm(db)
{

}
qint32 PNetFrmLogin::ZLogin(QString userName,QString password)
{
    qint32 retCode=0;
    QString errMsg;
    QString RoleName,UserPassword,RealName,Sex,Mobile,Creator,CreateTime,PermBits;
    //SELECT `UserInfo`.`RoleName`,`UserInfo`.`Password`,`UserInfo`.`RealName`,`UserInfo`.`Sex`,`UserInfo`.`Mobile`,`UserInfo`.`Creator`,`UserInfo`.`CreateTime`, `RoleInfo`.`PermBits` FROM `pms`.`UserInfo`,`pms`.`RoleInfo` WHERE `UserInfo`.`RoleName`=`RoleInfo`.`RoleName` AND `UserInfo`.`UserName`='root';
    QSqlQuery query(this->m_db);
    query.prepare("SELECT `UserInfo`.`RoleName`,`UserInfo`.`Password`,`UserInfo`.`RealName`,`UserInfo`.`Sex`,`UserInfo`.`Mobile`,`UserInfo`.`Creator`,`UserInfo`.`CreateTime`, `RoleInfo`.`PermBits` FROM `pms`.`UserInfo`,`pms`.`RoleInfo` WHERE `UserInfo`.`RoleName`=`RoleInfo`.`RoleName` AND `UserInfo`.`UserName`=:UserName");
    query.bindValue(":UserName",userName);;
    if(query.exec())
    {
            if(query.size()>0)
            {
                query.next();
                RoleName=query.value(0).toString();
                UserPassword=query.value(1).toString();
                RealName=query.value(2).toString();
                Sex=query.value(3).toString();
                Mobile=query.value(4).toString();
                Creator=query.value(5).toString();
                CreateTime=query.value(6).toString();
                PermBits=query.value(7).toString();

                if(password!=UserPassword)
                {
                    retCode=-1;
                    errMsg=QString("密码不正确!");
                }
            }else{
                //no rows returned.it means no such user in table.
                retCode=-1;
                errMsg=QString("系统中不存在用户:%1!").arg(userName);
            }
    }else{
        retCode=-1;
        errMsg=query.lastError().text();
    }


    //generate ack net frm.
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Login"));
    tXmlWriter.writeStartElement(QString("Login"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("login"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        //login failed.
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        this->m_opLogMsg=QString("user <%1> login faield:[%2].").arg(userName).arg(errMsg);
    }else{
        //login success.
        tXmlWriter.writeAttribute(QString("roleName"),RoleName);
        tXmlWriter.writeAttribute(QString("realName"),RealName);
        tXmlWriter.writeAttribute(QString("sex"),Sex);
        tXmlWriter.writeAttribute(QString("mobile"),Mobile);
        tXmlWriter.writeAttribute(QString("creator"),Creator);
        tXmlWriter.writeAttribute(QString("createTime"),CreateTime);
        tXmlWriter.writeAttribute(QString("permBits"),PermBits);
        this->m_opLogMsg=QString("user <%1> login success.").arg(userName);
    }
    tXmlWriter.writeCharacters(userName);
    tXmlWriter.writeEndElement();//Login.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
    //qDebug()<<this->m_ackNetFrmXmlData;
    return retCode;
}
qint32 PNetFrmLogin::ZLogout(QString userName)
{
    //generate ack net frm.
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Login"));
    tXmlWriter.writeStartElement(QString("Login"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("logout"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("0"));
    tXmlWriter.writeCharacters(userName);
    tXmlWriter.writeEndElement();//Login.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
    this->m_opLogMsg=QString("user <%1> logout success.").arg(userName);
    return 0;
}
