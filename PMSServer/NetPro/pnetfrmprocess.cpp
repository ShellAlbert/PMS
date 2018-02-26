#include "pnetfrmprocess.h"
#include <QDir>
#include <QFile>
#include <QXmlStreamWriter>
PNetFrmProcess::PNetFrmProcess(QSqlDatabase db):PNetFrm(db)
{

}
void PNetFrmProcess::ZAddProcess(QString processName,QString creator)
{
    //INSERT INTO `pms`.`ProcessInfo` (`ProcessName`, `StepNum`,`Creator`, `CreateTime`) VALUES ('abc', 'root', '2016-12-12 12:12:12');
    qint32 retCode;
    QString errMsg;
    QString createTime=QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss");
    QSqlQuery query(this->m_db);
    query.prepare("INSERT INTO `pms`.`ProcessInfo` (`ProcessName`, `StepNum`,`Creator`, `CreateTime`) VALUES (:ProcessName,:StepNum, :Creator, :CreateTime)");
    query.bindValue(":ProcessName",processName);
    query.bindValue(":StepNum",0);
    query.bindValue(":Creator",creator);
    query.bindValue(":CreateTime",createTime);
    if(query.exec())
    {
        retCode=0;
        errMsg=QString("no");
        this->m_opLogMsg=QString("add process [%1] success").arg(processName);
    }else{
        retCode=-1;
        errMsg=query.lastError().text();
        this->m_opLogMsg=QString("add process [%1] failed:[%2].").arg(processName).arg(errMsg);
    }

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Process"));
    tXmlWriter.writeStartElement(QString("Process"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("creator"),creator);
    tXmlWriter.writeAttribute(QString("createTime"),createTime);
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(processName);
    tXmlWriter.writeEndElement();//Process.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmProcess::ZDelProcess(QString processName,QString creator)
{
    //DELETE FROM `pms`.`ProcessInfo` WHERE `ProcessName`='abc';
    qint32 retCode;
    QString errMsg;
    QSqlQuery query(this->m_db);
    query.prepare("DELETE FROM `pms`.`ProcessInfo` WHERE `ProcessName`= :ProcessName");
    query.bindValue(":ProcessName",processName);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("delete process [%1] success").arg(processName);
    }else{
        retCode=-1;
        errMsg=query.lastError().text();
        this->m_opLogMsg=QString("delete process [%1] failed:[%2].").arg(processName).arg(errMsg);
    }
    //remove local file.
    QFile::remove(QDir::currentPath()+"/data/"+creator+"/process/"+processName+".xml");

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Process"));
    tXmlWriter.writeStartElement(QString("Process"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(processName);
    tXmlWriter.writeEndElement();//Process.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmProcess::ZGetProcess(QString processName,QString creator)
{
    class StepLinkInfo{
    public:
        QStringList linkTemplates;
        QStringList linkFiles;
        QStringList linkRoles;
    };
    qint32 retCode;
    QString errMsg;
    QMap<QString,StepLinkInfo*> linkMap;
    //SELECT `StepName`,`LinkTemplates`,`LinkFiles`,`LinkRoles` FROM pms.StepInfo WHERE `ProcessName`='root';
    QSqlQuery query(this->m_db);
    query.prepare("SELECT `StepName`,`LinkTemplates`,`LinkFiles`,`LinkRoles` FROM pms.StepInfo WHERE `ProcessName`=:ProcessName");
    query.bindValue(":ProcessName",processName);
    if(query.exec())
    {
        while(query.next())
        {
            QString stepName=query.value(0).toString();
            QString linkTemplates=query.value(1).toString();
            QString linkFiles=query.value(2).toString();
            QString linkRoles=query.value(3).toString();
            //link templates.
            if(!linkTemplates.isEmpty())
            {
                if(!linkMap.contains(stepName))
                {
                    StepLinkInfo *info=new StepLinkInfo;
                    info->linkTemplates.append(linkTemplates);
                    linkMap.insert(stepName,info);
                }else{
                    StepLinkInfo *info=linkMap.value(stepName);
                    info->linkTemplates.append(linkTemplates);
                }
            }
            //link files.
            if(!linkFiles.isEmpty())
            {
                if(!linkMap.contains(stepName))
                {
                    StepLinkInfo *info=new StepLinkInfo;
                    info->linkFiles.append(linkFiles);
                    linkMap.insert(stepName,info);
                }else{
                    StepLinkInfo *info=linkMap.value(stepName);
                    info->linkFiles.append(linkFiles);
                }
            }
            //link roles.
            if(!linkRoles.isEmpty())
            {
                if(!linkMap.contains(stepName))
                {
                    StepLinkInfo *info=new StepLinkInfo;
                    info->linkRoles.append(linkRoles);
                    linkMap.insert(stepName,info);
                }else{
                    StepLinkInfo *info=linkMap.value(stepName);
                    info->linkRoles.append(linkRoles);
                }
            }
        }
        retCode=0;
        this->m_opLogMsg=QString("get process [%1] success").arg(processName);
    }else{
        retCode=-1;
        errMsg=query.lastError().text();
        this->m_opLogMsg=QString("get process [%1] failed:[%2].").arg(processName).arg(errMsg);
    }

    //generate step xml data.
    QString stepXmlData;
    QXmlStreamWriter  stepXmlWriter(&stepXmlData);
    stepXmlWriter.setAutoFormatting(true);
    stepXmlWriter.writeStartDocument();
    stepXmlWriter.writeStartElement(QString("NetPro"));
    stepXmlWriter.writeAttribute(QString("dest"),QString("Step"));
    QMap<QString,StepLinkInfo*>::iterator it;
    for(it=linkMap.begin();it!=linkMap.end();it++)
    {
        QString stepName=it.key();
        StepLinkInfo* info=it.value();
        QString linkTemplate;
        QString linkFile;
        QString linkRole;
        for(qint32 i=0;i<info->linkTemplates.count();i++)
        {
            linkTemplate.append(info->linkTemplates.at(i)+":");
        }
        for(qint32 i=0;i<info->linkFiles.count();i++)
        {
            linkFile.append(info->linkFiles.at(i)+":");
        }
        for(qint32 i=0;i<info->linkRoles.count();i++)
        {
            linkRole.append(info->linkRoles.at(i)+":");
        }
        stepXmlWriter.writeStartElement(QString("Step"));
        stepXmlWriter.writeAttribute(QString("linktemplates"),linkTemplate);
        stepXmlWriter.writeAttribute(QString("linkfiles"),linkFile);
        stepXmlWriter.writeAttribute(QString("linkroles"),linkRole);
        stepXmlWriter.writeCharacters(stepName);
        stepXmlWriter.writeEndElement();//Step.
    }
    stepXmlWriter.writeEndElement();//NetPro
    stepXmlWriter.writeEndDocument();

    //generate ack net frame.
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Process"));
    tXmlWriter.writeStartElement(QString("Process"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("data"),QString(stepXmlData.toUtf8().toBase64()));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(processName);
    tXmlWriter.writeEndElement();//Process.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmProcess::ZSaveProcess(QString processName,qint32 stepNum,QString xmlData,QString creator)
{
    qint32 retCode;
    QString errMsg;
    //UPDATE `pms`.`ProcessInfo` SET `StepNum`='1' WHERE `ProcessName`='pro1';
    QSqlQuery query(this->m_db);
    query.prepare("UPDATE `pms`.`ProcessInfo` SET `StepNum`=:StepNum WHERE `ProcessName`= :ProcessName");
    query.bindValue(":ProcessName",processName);
    query.bindValue(":StepNum",stepNum);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("save process [%1] success").arg(processName);
    }else{
        retCode=-1;
        errMsg=query.lastError().text();
        this->m_opLogMsg=QString("save process [%1] failed:[%2].").arg(processName).arg(errMsg);
    }

    //delete previous before write.
    //DELETE FROM `pms`.`StepInfo` WHERE `ProcessName`='123';
    QSqlQuery clearQuery(this->m_db);
    clearQuery.prepare("DELETE FROM `pms`.`StepInfo` WHERE `ProcessName`=:ProcessName");
    clearQuery.bindValue(":ProcessName",processName);
    clearQuery.exec();

    //write to StepInfo table.
    QString stepXmlData(QByteArray::fromBase64(xmlData.toUtf8()));
    QXmlStreamReader tXmlReader(stepXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Step"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString linktemplates=attr.value(QString("linktemplates")).toString();
                QString linkfiles=attr.value(QString("linkfiles")).toString();
                QString linkroles=attr.value(QString("linkroles")).toString();
                QString stepName=tXmlReader.readElementText();
                QStringList linkTemplatesList=linktemplates.split(":");
                QStringList linkFilesList=linkfiles.split(":");
                QStringList linkRolesList=linkroles.split(":");
                //save link templates.
                for(qint32 i=0;i<linkTemplatesList.count();i++)
                {
                    QString linkTemplateName=linkTemplatesList.at(i);
                    if(!linkTemplateName.isEmpty())
                    {
                        //INSERT INTO `pms`.`StepInfo` (`StepName`, `ProcessName`, `LinkTemplates`) VALUES ('ab','a', 'b', 'c');
                        QSqlQuery query(this->m_db);
                        query.prepare("INSERT INTO `pms`.`StepInfo` (`StepName`, `ProcessName`, `LinkTemplates`) VALUES (:StepName, :ProcessName, :LinkTemplates)");
                        query.bindValue(":StepName",stepName);
                        query.bindValue(":ProcessName",processName);
                        query.bindValue(":LinkTemplates",linkTemplateName);
                        query.exec();
                    }
                }
                //save link files.
                for(qint32 i=0;i<linkFilesList.count();i++)
                {
                    QString linkFileName=linkFilesList.at(i);
                    if(!linkFileName.isEmpty())
                    {
                        //INSERT INTO `pms`.`StepInfo` (`StepName`, `ProcessName`, `LinkFiles`) VALUES ('ab','a', 'b', 'c');
                        QSqlQuery query(this->m_db);
                        query.prepare("INSERT INTO `pms`.`StepInfo` (`StepName`, `ProcessName`, `LinkFiles`) VALUES (:StepName, :ProcessName, :LinkFiles)");
                        query.bindValue(":StepName",stepName);
                        query.bindValue(":ProcessName",processName);
                        query.bindValue(":LinkFiles",linkFileName);
                        query.exec();
                    }
                }
                //save link roles.
                for(qint32 i=0;i<linkRolesList.count();i++)
                {
                    QString linkRoleName=linkRolesList.at(i);
                    if(!linkRoleName.isEmpty())
                    {
                        //INSERT INTO `pms`.`StepInfo` (`StepName`, `ProcessName`, `LinkRoles`) VALUES ('ab','a', 'b', 'c');
                        QSqlQuery query(this->m_db);
                        query.prepare("INSERT INTO `pms`.`StepInfo` (`StepName`, `ProcessName`, `LinkRoles`) VALUES (:StepName, :ProcessName, :LinkRoles)");
                        query.bindValue(":StepName",stepName);
                        query.bindValue(":ProcessName",processName);
                        query.bindValue(":LinkRoles",linkRoleName);
                        query.exec();
                    }
                }
            }//Step.
        }//StarElement.
    }//while().

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Process"));
    tXmlWriter.writeStartElement(QString("Process"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("save"));
    tXmlWriter.writeAttribute(QString("stepNum"),QString("%1").arg(stepNum));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(processName);
    tXmlWriter.writeEndElement();//Process.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmProcess::ZListProcess(QString creator)
{
    //SELECT `ProcessName`,`StepNum`,`Creator`,`CreateTime` FROM `pms`.`ProcessInfo` WHERE `Creator`='root';
    qint32 retCode;
    QString errMsg;
    QSqlQuery query(this->m_db);
    query.prepare("SELECT `ProcessName`,`StepNum`, `Creator`,`CreateTime` FROM `pms`.`ProcessInfo` WHERE `Creator`=:Creator ");
    query.bindValue(":Creator",creator);
    if(query.exec())
    {
        retCode=0;
        this->m_opLogMsg=QString("list process attached to creator [%1] success").arg(creator);
    }else{
        retCode=-1;
        errMsg=query.lastError().text();
        this->m_opLogMsg=QString("list process attached to creator [%1] failed:[%2].").arg(creator).arg(errMsg);
    }

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Process"));
    while(query.next())
    {
        QString processName=query.value(0).toString();
        QString stepNum=query.value(1).toString();
        QString creator=query.value(2).toString();
        QString createTime=query.value(3).toString();
        tXmlWriter.writeStartElement(QString("Process"));
        tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
        tXmlWriter.writeAttribute(QString("stepNum"),stepNum);
        tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        tXmlWriter.writeAttribute(QString("creator"),creator);
        tXmlWriter.writeAttribute(QString("createTime"),createTime);
        tXmlWriter.writeCharacters(processName);
        tXmlWriter.writeEndElement();//Process.
    }
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
