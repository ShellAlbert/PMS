#include "pnetfrmtask.h"
#include <QXmlStreamWriter>
#include <QDebug>
#include <QDir>
#include <QFile>
PNetFrmTask::PNetFrmTask(QSqlDatabase db):PNetFrm(db)
{

}
void PNetFrmTask::ZListNewTask(QString roleName)
{
    class StepInfo
    {
    public:
        QString stepName;
        QStringList linkTemplates;
        QStringList linkFiles;
    };
    QMap<QString,QList<StepInfo*>*> processMap;
    //SELECT `StepName`,`ProcessName`,`LinkTemplates`,`LinkFiles` FROM `pms`.`StepInfo` WHERE ProcessName IN (SELECT ProcessName FROM `pms`.`StepInfo` WHERE LinkRoles='FuckJapanWoman' GROUP BY ProcessName);
    QSqlQuery query(this->m_db);
    if(roleName==QString("admin"))
    {
        query.prepare("SELECT `StepName`,`ProcessName`,`LinkTemplates`,`LinkFiles` FROM `pms`.`StepInfo` WHERE ProcessName IN (SELECT ProcessName FROM `pms`.`StepInfo` GROUP BY ProcessName)");
    }else{
        query.prepare("SELECT `StepName`,`ProcessName`,`LinkTemplates`,`LinkFiles` FROM `pms`.`StepInfo` WHERE ProcessName IN (SELECT ProcessName FROM `pms`.`StepInfo` WHERE LinkRoles=:LinkRoles GROUP BY ProcessName)");
        query.bindValue(":LinkRoles",roleName);
    }
    if(query.exec())
    {
        while(query.next())
        {
            QString stepName=query.value(0).toString();
            QString processName=query.value(1).toString();
            QString linkTemplate=query.value(2).toString();
            QString linkFile=query.value(3).toString();
            if(!processMap.contains(processName))
            {
                QList<StepInfo*> *list=new QList<StepInfo*>;
                StepInfo *info=new StepInfo;
                info->stepName=stepName;
                if(!linkTemplate.isEmpty())
                {
                    info->linkTemplates.append(linkTemplate);
                }
                if(!linkFile.isEmpty())
                {
                    info->linkFiles.append(linkFile);
                }
                list->append(info);
                processMap.insert(processName,list);
            }else{
                QList<StepInfo*> *list=processMap.value(processName);
                bool bAdded=false;
                //to find previous added step.
                for(qint32 i=0;i<list->count();i++)
                {
                    StepInfo *info=list->at(i);
                    if(info->stepName==stepName)
                    {
                        bAdded=true;
                        if(!linkTemplate.isEmpty())
                        {
                            info->linkTemplates.append(linkTemplate);
                        }
                        if(!linkFile.isEmpty())
                        {
                            info->linkFiles.append(linkFile);
                        }
                    }
                }
                //if not add this step.
                if(!bAdded)
                {
                    StepInfo *info=new StepInfo;
                    info->stepName=stepName;
                    if(!linkTemplate.isEmpty())
                    {
                        info->linkTemplates.append(linkTemplate);
                    }
                    if(!linkFile.isEmpty())
                    {
                        info->linkFiles.append(linkFile);
                    }
                    list->append(info);
                }
            }
        }
    }else{
        //query failed.
    }


    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    //write processName.
    QMap<QString,QList<StepInfo*>*>::iterator processIt;
    for(processIt=processMap.begin();processIt!=processMap.end();processIt++)
    {
        tXmlWriter.writeStartElement(QString("Process"));
        tXmlWriter.writeAttribute(QString("cmd"),QString("listnew"));
        tXmlWriter.writeCharacters(processIt.key());
        tXmlWriter.writeEndElement();//Process.
    }
    //write stepName.
    QMap<QString,QList<StepInfo*>*>::iterator stepIt;
    for(stepIt=processMap.begin();stepIt!=processMap.end();stepIt++)
    {
        QString processName=stepIt.key();
        QList<StepInfo*>* list=stepIt.value();
        for(qint32 i=0;i<list->count();i++)
        {
            StepInfo* info=list->at(i);
            QString linkTemplate;
            for(qint32 j=0;j<info->linkTemplates.count();j++)
            {
                linkTemplate.append(info->linkTemplates.at(j)+":");
            }
            tXmlWriter.writeStartElement(QString("Step"));
            tXmlWriter.writeAttribute(QString("cmd"),QString("listnew"));
            tXmlWriter.writeAttribute(QString("process"),processName);
            tXmlWriter.writeAttribute(QString("linktemplate"),linkTemplate);
            tXmlWriter.writeCharacters(info->stepName);
            tXmlWriter.writeEndElement();//Step.
        }
    }
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();

    //clear map.
    QMap<QString,QList<StepInfo*>*>::iterator it;
    for(it=processMap.begin();it!=processMap.end();it++)
    {
        QList<StepInfo*>* list=it.value();
        for(qint32 i=0;i<list->count();i++)
        {
            StepInfo* info=list->at(i);
            delete info;
            info=NULL;
        }
        list->clear();
        delete list;
        list=NULL;
    }
    processMap.clear();

    //qDebug()<<this->m_ackNetFrmXmlData;
}
void PNetFrmTask::ZListTask(QString creator,qint32 taskState)
{
    //SELECT `TaskName`,`RefTemplate`,`TaskState`,`Creator`,`CreateTime`,`Checker`,`CheckTime` FROM pms.TaskInfo WHERE `Creator`='root' AND TaskState=0;
    qint32 retCode=0;
    QString errMsg;
    QSqlQuery query(this->m_db);
    switch(taskState)
    {
    case 0://Task_Type_All.
        query.prepare("SELECT `TaskName`,`RefProcess`,`RefStep`,`RefTemplate`,`TaskState`,`Creator`,`CreateTime`,`Checker`,`CheckTime` FROM pms.TaskInfo WHERE `Creator`=:Creator AND `TaskState`!=:TaskState");
        query.bindValue(":Creator",creator);
        query.bindValue(":TaskState",6);
        break;
    case 1://Task_Type_New.
    case 2://Task_Type_Save.
    case 3://Task_Type_Submit.
    case 4://Task_Type_CheckOkay.
    case 5://Task_Type_CheckFailed.
    case 6://Task_Type_Archieve.
        query.prepare("SELECT `TaskName`,`RefProcess`,`RefStep`,`RefTemplate`,`TaskState`,`Creator`,`CreateTime`,`Checker`,`CheckTime` FROM pms.TaskInfo WHERE `Creator`=:Creator AND TaskState=:TaskState");
        query.bindValue(":Creator",creator);
        query.bindValue(":TaskState",taskState);
        break;
    case 7://Task_Type_Need_My_Check.
        query.prepare("SELECT `TaskName`,`RefProcess`,`RefStep`,`RefTemplate`,`TaskState`,`Creator`,`CreateTime`,`Checker`,`CheckTime` FROM pms.TaskInfo WHERE `Checker`=:Checker AND TaskState=:TaskState");
        query.bindValue(":Checker",creator);
        query.bindValue(":TaskState",3);
        break;
    case 8://Task_Type_My_Check_Okay.
        query.prepare("SELECT `TaskName`,`RefProcess`,`RefStep`,`RefTemplate`,`TaskState`,`Creator`,`CreateTime`,`Checker`,`CheckTime` FROM pms.TaskInfo WHERE `Checker`=:Checker AND TaskState=:TaskState");
        query.bindValue(":Checker",creator);
        query.bindValue(":TaskState",4);
        break;
    case 9://Task_Type_My_Check_Failed.
        query.prepare("SELECT `TaskName`,`RefProcess`,`RefStep`,`RefTemplate`,`TaskState`,`Creator`,`CreateTime`,`Checker`,`CheckTime` FROM pms.TaskInfo WHERE `Checker`=:Checker AND TaskState=:TaskState");
        query.bindValue(":Checker",creator);
        query.bindValue(":TaskState",5);
        break;
    default:
        break;
    }
    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();
        this->m_opLogMsg=QString("list task attached to creator [%1] with taskState[%2] failed:%3.").arg(creator).arg(taskState).arg(errMsg);
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    while(query.next())
    {
        QString taskName=query.value(0).toString();
        QString refProcess=query.value(1).toString();
        QString refStep=query.value(2).toString();
        QString refTemplate=query.value(3).toString();
        QString taskState=query.value(4).toString();
        QString creator=query.value(5).toString();
        QString createTime=query.value(6).toString();
        QString checker=query.value(7).toString();
        QString checkTime=query.value(8).toString();
        tXmlWriter.writeStartElement(QString("Task"));
        tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
        tXmlWriter.writeAttribute(QString("refTemplate"),refTemplate);
        tXmlWriter.writeAttribute(QString("refProcess"),refProcess);
        tXmlWriter.writeAttribute(QString("refStep"),refStep);
        tXmlWriter.writeAttribute(QString("taskState"),taskState);
        tXmlWriter.writeAttribute(QString("creator"),creator);
        tXmlWriter.writeAttribute(QString("createTime"),createTime);
        tXmlWriter.writeAttribute(QString("checker"),checker);
        tXmlWriter.writeAttribute(QString("checkTime"),checkTime);
        tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
        tXmlWriter.writeCharacters(taskName);
        tXmlWriter.writeEndElement();//Task.
    }
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTask::ZAddTask(QString taskName,QString refTemplate,QString refProcess,QString refStep,QString creator,QString checker)
{
    //INSERT INTO `pms`.`TaskInfo` (`TaskName`, `RefTemplate`, `TaskState`, `Creator`, `CreateTime`, `Checker`, `CheckTime`) VALUES ('yantai', 'shandong', '1', 'zhangshaoyan', '2017-01-13 13:29:39', 'jingyankeji', '2017-01-14 19:12:23');
    qint32 retCode=0;
    QString errMsg;
    qint32 taskState=1;//new task.
    QString createTime=QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss");
    QString checkTime=QString("0000-00-00 00:00:00");
    QSqlQuery query(this->m_db);
    query.prepare("INSERT INTO `pms`.`TaskInfo` (`TaskName`, `RefProcess`,`RefStep`,`RefTemplate`, `TaskState`, `Creator`, `CreateTime`, `Checker`, `CheckTime`) VALUES (:TaskName, :RefProcess,:RefStep,:RefTemplate, :TaskState, :Creator, :CreateTime, :Checker, :CheckTime)");
    query.bindValue(":TaskName",taskName);
    query.bindValue(":RefProcess",refProcess);
    query.bindValue(":RefStep",refStep);
    query.bindValue(":RefTemplate",refTemplate);
    query.bindValue(":TaskState",taskState);
    query.bindValue(":Creator",creator);
    query.bindValue(":CreateTime",createTime);
    query.bindValue(":Checker",checker);
    query.bindValue(":CheckTime",checkTime);
    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();
        this->m_opLogMsg=QString("add task [%1] failed:[%2].").arg(taskName).arg(errMsg);
    }
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("refTemplate"),refTemplate);
        tXmlWriter.writeAttribute(QString("refProcess"),refProcess);
        tXmlWriter.writeAttribute(QString("refStep"),refStep);
        tXmlWriter.writeAttribute(QString("taskState"),QString("%1").arg(taskState));
        tXmlWriter.writeAttribute(QString("creator"),creator);
        tXmlWriter.writeAttribute(QString("createTime"),createTime);
        tXmlWriter.writeAttribute(QString("checker"),checker);
        tXmlWriter.writeAttribute(QString("checkTime"),checkTime);
    }
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTask::ZOpenTask(QString taskName,QString refTemplate)
{
    qint32 retCode;
    QString errMsg;

    QString templateCreator;
    QString varSrcName;
    QString varSrcCreator;

    qint32 taskState=0;

    QString refProcess,refStep;

    QString machineNo,classNo,orderNo,productNo;

    //SELECT `TaskState`,`MachineNo`,`ClassNo`,`OrderNo`,`ProductNo` FROM pms.TaskInfo WHERE `TaskName`='abc';
    QSqlQuery queryTaskState(this->m_db);
    queryTaskState.prepare("SELECT `RefProcess`,`RefStep`,`TaskState`,`MachineNo`,`ClassNo`,`OrderNo`,`ProductNo` FROM `pms`.`TaskInfo` WHERE `TaskName`=:TaskName");
    queryTaskState.bindValue(":TaskName",taskName);
    if(queryTaskState.exec())
    {
        while(queryTaskState.next())
        {
            refProcess=queryTaskState.value(0).toString();
            refStep=queryTaskState.value(1).toString();
            taskState=queryTaskState.value(2).toInt();
            machineNo=queryTaskState.value(3).toString();
            classNo=queryTaskState.value(4).toString();
            orderNo=queryTaskState.value(5).toString();
            productNo=queryTaskState.value(6).toString();
        }
        retCode=0;
    }else{
        retCode=-1;
        errMsg=queryTaskState.lastError().text();
        qDebug()<<"queryTaskState:"<<queryTaskState.lastError().text();
    }

    //step1: find out the template's creator.
    //to find the template xml file.
    //currentPath/data/templateCreator/template/templateName.xml.
    //SELECT `Creator` FROM pms.TemplateInfo WHERE `TemplateName`='Template1';
    QSqlQuery query(this->m_db);
    query.prepare("SELECT `Creator` FROM pms.TemplateInfo WHERE `TemplateName`=:TemplateName");
    query.bindValue(":TemplateName",refTemplate);
    if(query.exec())
    {
        while(query.next())
        {
            templateCreator=query.value(0).toString();
        }
        retCode=0;
    }else{
        retCode=-1;
        errMsg=query.lastError().text();
        qDebug()<<"error:"<<errMsg;
    }
    //step2: find out the bind var source according the templateName.
    //to find the varSrc xml file.
    //currentPath/data/varSrcCreator/varsource/varSrcName.xml.
    //SELECT `VarSourceName`,`Creator` FROM `pms`.`VarSourceInfo` WHERE `VarSourceName`=(SELECT `VarSourceName` FROM `pms`.`TemplateInfo` WHERE `TemplateName`='Template1');
    QSqlQuery query2(this->m_db);
    query2.prepare("SELECT `VarSourceName`,`Creator` FROM `pms`.`VarSourceInfo` WHERE `VarSourceName`=(SELECT `VarSourceName` FROM `pms`.`TemplateInfo` WHERE `TemplateName`=:TemplateName)");
    query2.bindValue(":TemplateName",refTemplate);
    if(query2.exec())
    {
        while(query2.next())
        {
            varSrcName=query2.value(0).toString();
            varSrcCreator=query2.value(1).toString();
        }
        retCode=0;
    }else{
        retCode=-1;
        errMsg=query2.lastError().text();
        qDebug()<<"error:"<<errMsg;
    }

    //step3.fetch the row data from the varSrcName_Data table.
    QString templateXmlData;
    QString varSrcXmlData;
    QString varValXmlData;
    if(!templateCreator.isEmpty() && !varSrcName.isEmpty() && !varSrcCreator.isEmpty())
    {
        QFile templateFile(QDir::currentPath()+"/data/"+templateCreator+"/template/"+refTemplate+".xml");
        if(templateFile.open(QIODevice::ReadOnly))
        {
            templateXmlData=QString(templateFile.readAll());
            templateFile.close();
        }else{
            retCode=-1;
            errMsg=templateFile.errorString();
        }
        QFile varSrcFile(QDir::currentPath()+"/data/"+varSrcCreator+"/varsource/"+varSrcName+".xml");
        if(varSrcFile.open(QIODevice::ReadOnly))
        {
            varSrcXmlData=QString(varSrcFile.readAll());
            varSrcFile.close();
        }else{
            retCode=-1;
            errMsg=varSrcFile.errorString();
        }
        //SELECT * FROM pms.VarSrc1_Data WHERE `TaskName`='varSrc';
        //parse out the table structure.
        QStringList colNameList;
        QStringList colValueList;
        colNameList.append(QString("TaskName"));
        QXmlStreamReader tXmlReader(varSrcXmlData);
        while(!tXmlReader.atEnd())
        {
            QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
            if(tTokenType==QXmlStreamReader::StartElement)
            {
                QString nodeName=tXmlReader.name().toString();
                if(nodeName==QString("GeVar"))
                {
                    QString colName=tXmlReader.readElementText();
                    colNameList.append(colName);
                }else if(nodeName==QString("AutoVar"))
                {
                    QString colName=tXmlReader.readElementText();
                    colNameList.append(colName);
                }
            }//StarElement.
        }//while().
        QString queryTaskDataSql;
        queryTaskDataSql.append("SELECT ");
        for(qint32 i=0;i<colNameList.count();i++)
        {
            queryTaskDataSql.append(QString("`%1`,").arg(colNameList.at(i)));
        }
        //remove the last ',' character.
        queryTaskDataSql=queryTaskDataSql.mid(0,queryTaskDataSql.size()-1);
        queryTaskDataSql.append(QString(" FROM `pms`.`%1_Data` WHERE `TaskName`='%2'").arg(varSrcName).arg(taskName));
        qDebug()<<"querySql:";
        qDebug()<<queryTaskDataSql;
        QSqlQuery query3(this->m_db);
        if(query3.exec(queryTaskDataSql))
        {
            while(query3.next())
            {
                for(qint32 i=0;i<colNameList.count();i++)
                {
                    colValueList.append(query3.value(i).toString());
                }
            }
            retCode=0;
        }else{
            retCode=-1;
            errMsg=query3.lastError().text();
            qDebug()<<"error:"<<errMsg;
        }
        //generate var xml data.
        QXmlStreamWriter  tXmlWriter(&varValXmlData);
        tXmlWriter.setAutoFormatting(true);
        tXmlWriter.writeStartDocument();
        tXmlWriter.writeStartElement(QString("NetPro"));
        tXmlWriter.writeAttribute(QString("dest"),QString("VarValue"));
        if(colValueList.count()>0)
        {
            for(qint32 i=0;i<colNameList.count();i++)
            {
                tXmlWriter.writeStartElement(QString("VarValue"));
                tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
                tXmlWriter.writeAttribute(QString("val"),colValueList.at(i));
                tXmlWriter.writeCharacters(colNameList.at(i));
                tXmlWriter.writeEndElement();//VarValue.
            }
        }
        tXmlWriter.writeEndElement();//NetPro
        tXmlWriter.writeEndDocument();
    }

    //generate the ack net frame xml data.
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("refTemplate"),refTemplate);
    tXmlWriter.writeAttribute(QString("refProcess"),refProcess);
    tXmlWriter.writeAttribute(QString("refStep"),refStep);
    tXmlWriter.writeAttribute(QString("machineNo"),machineNo);
    tXmlWriter.writeAttribute(QString("classNo"),classNo);
    tXmlWriter.writeAttribute(QString("orderNo"),orderNo);
    tXmlWriter.writeAttribute(QString("productNo"),productNo);
    tXmlWriter.writeAttribute(QString("templatedata"),QString(templateXmlData.toUtf8().toBase64()));
    tXmlWriter.writeAttribute(QString("varsrcdata"),QString(varSrcXmlData.toUtf8().toBase64()));
    tXmlWriter.writeAttribute(QString("vardata"),QString(varValXmlData.toUtf8().toBase64()));
    tXmlWriter.writeAttribute(QString("taskState"),QString("%1").arg(taskState));
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTask::ZSaveTask(QString taskName,QString refTemplate,QString taskValueXmlData,QStringList auxData)
{
    //find out RefTemplate bind varSource to make sure the table varSource_Data.
    //then write data into varSource_Data table.
    qint32 retCode;
    QString errMsg;
    //SELECT `VarSourceName` FROM `pms`.`TemplateInfo` WHERE `TemplateName`='Template1';
    QString varSourceName;
    QSqlQuery query(this->m_db);
    query.prepare("SELECT `VarSourceName` FROM `pms`.`TemplateInfo` WHERE `TemplateName`=:TemplateName");
    query.bindValue(":TemplateName",refTemplate);
    if(query.exec())
    {
        while(query.next())
        {
            varSourceName=query.value(0).toString();
        }
    }else{
        retCode=-1;
        errMsg=query.lastError().text();
        qDebug()<<"error:"<<errMsg;
    }

    QString xmlData=QString(QByteArray::fromBase64(taskValueXmlData.toUtf8()));
    QMap<QString,QString> varList;
    QXmlStreamReader tXmlReader(xmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Value"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString varVal=attr.value(QString("val")).toString();
                QString varName=tXmlReader.readElementText();
                if(!varList.contains(varName))
                {
                    varList.insert(varName,varVal);
                }
            }
        }//StarElement.
    }//while().

    //delete before insert.
    QSqlQuery query2(this->m_db);
    query2.exec(QString("DELETE FROM `%1_Data` WHERE `TaskName`='%2'").arg(varSourceName).arg(taskName));

    //generate insert sql.
    //INSERT INTO `pms`.`VarSrc1_Data` (`TaskName`, `LineNo`, `ShiftNo`, `CurrentDateTime`, `UserName`, `CurTime`, `CurDate`, `Fuck`) VALUES ('abc', '123', 'abd', '2015-12-12 12:12:12', 'yuu', '2016-6-8 12:12:12', '2016-8-8', 'china');
    QString insertSql;
    insertSql.append(QString("INSERT INTO `pms`.`%1_Data` (`TaskName`,").arg(varSourceName));
    QMap<QString,QString>::iterator it;
    for(it=varList.begin();it!=varList.end();it++)
    {
        insertSql.append(QString("`%1`,").arg(it.key()));
    }
    //remove the last ',' character.
    insertSql=insertSql.mid(0,insertSql.size()-1);
    insertSql.append(QString(" ) VALUES ( '%1',").arg(taskName));
    for(it=varList.begin();it!=varList.end();it++)
    {
        insertSql.append(QString("'%1',").arg(it.value()));
    }
    //remove the last ',' character.
    insertSql=insertSql.mid(0,insertSql.size()-1);
    insertSql.append(" )");
    qDebug()<<"sql:"<<insertSql;

    QSqlQuery query3(this->m_db);
    if(query3.exec(insertSql))
    {
        //insert success.
        retCode=0;
    }else{
        retCode=-1;
        errMsg=query3.lastError().text();
        qDebug()<<"error:"<<errMsg;
    }

    //update taskState from NewTask to SaveTask.
    //UPDATE `pms`.`TaskInfo` SET `TaskState`='2' WHERE `TaskName`='root-烟台璟言科技在职员工表-20170116213709';
    QSqlQuery query4(this->m_db);
    query4.prepare("UPDATE `pms`.`TaskInfo` SET `TaskState`=:TaskState,`MachineNo`=:MachineNo,`ClassNo`=:ClassNo,`OrderNo`=:OrderNo,`ProductNo`=:ProductNo WHERE `TaskName`=:TaskName");
    query4.bindValue(":TaskState",Task_Type_Save);
    query4.bindValue(":TaskName",taskName);
    query4.bindValue(":MachineNo",auxData.at(0));
    query4.bindValue(":ClassNo",auxData.at(1));
    query4.bindValue(":OrderNo",auxData.at(2));
    query4.bindValue(":ProductNo",auxData.at(3));
    if(!query4.exec())
    {
        retCode=-1;
        errMsg=query4.lastError().text();
        qDebug()<<"error:"<<errMsg;
    }

    //generate the ack net frame xml data.
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("save"));
    tXmlWriter.writeAttribute(QString("taskState"),QString("%1").arg(Task_Type_Save));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTask::ZDelTask(QString taskName,QString refTemplate)
{
    qint32 retCode;
    QString errMsg;
    //step1:delete task data.
    //SELECT `VarSourceName` FROM pms.TemplateInfo WHERE TemplateName='Template1';
    QString varSrcName;
    QSqlQuery query(this->m_db);
    query.prepare("SELECT `VarSourceName` FROM pms.TemplateInfo WHERE TemplateName=:TemplateName");
    query.bindValue(":TemplateName",refTemplate);
    if(query.exec())
    {
        while(query.next())
        {
            varSrcName=query.value(0).toString();
        }
        retCode=0;
    }else{
        retCode=-1;
        errMsg=query.lastError().text();
        qDebug()<<"error:"<<errMsg;
    }
    //DELETE FROM `pms`.`VarSrc1_Data` WHERE `TaskName`='root-Template1-20170101121209';
    QString query2Sql=QString("DELETE FROM `pms`.`%1` WHERE `TaskName`='%2'").arg(varSrcName+"_Data").arg(taskName);
    QSqlQuery query2(this->m_db);
    if(query2.exec(query2Sql))
    {
        //delete success here.
        retCode=0;
    }else{
        retCode=-1;
        errMsg=query2.lastError().text();
        qDebug()<<"error:"<<errMsg;
    }

    //DELETE FROM `pms`.`TaskInfo` WHERE `TaskName`='task' AND `RefTemplate`='template1';
    QSqlQuery query3(this->m_db);
    query3.prepare("DELETE FROM `pms`.`TaskInfo` WHERE `TaskName`=:TaskName AND `RefTemplate`=:TemplateName");
    query3.bindValue(":TaskName",taskName);
    query3.bindValue(":TemplateName",refTemplate);
    if(query3.exec())
    {
        //delete success here.
        retCode=0;
    }else{
        retCode=-1;
        errMsg=query3.lastError().text();
        qDebug()<<"error:"<<errMsg;
    }

    //generate the ack net frame xml data.
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTask::ZSubmitTask(QString taskName,QString refTemplate)
{
    qint32 retCode=0;
    QString errMsg;
    //UPDATE `pms`.`TaskInfo` SET `TaskState`='3' WHERE `TaskName`='root-烟台璟言科技在职员工表-20170116213709';
    QSqlQuery query(this->m_db);
    query.prepare("UPDATE `pms`.`TaskInfo` SET `TaskState`=:TaskStateNew WHERE `TaskName`=:TaskName AND `RefTemplate`=:RefTemplate AND `TaskState`=:TaskStateOld");
    query.bindValue(":TaskStateNew",Task_Type_Submit);
    query.bindValue(":TaskName",taskName);
    query.bindValue(":RefTemplate",refTemplate);
    query.bindValue(":TaskStateOld",Task_Type_Save);
    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();
        qDebug()<<"submit task error:"<<errMsg;
    }
    //generate the ack net frame xml data.
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("submit"));
    tXmlWriter.writeAttribute(QString("taskState"),QString("%1").arg(Task_Type_Submit));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTask::ZWithdrawTask(QString taskName,QString refTemplate)
{
    qint32 retCode=0;
    QString errMsg;
    //UPDATE `pms`.`TaskInfo` SET `TaskState`='1' WHERE `TaskName`='root-烟台璟言科技在职员工表-20170116213709';
    QSqlQuery query(this->m_db);
    query.prepare("UPDATE `pms`.`TaskInfo` SET `TaskState`=:TaskStateNew WHERE `TaskName`=:TaskName AND `TaskState`=:TaskStateOld AND `RefTemplate`=:RefTemplate");
    query.bindValue(":TaskStateNew",Task_Type_Save);
    query.bindValue(":TaskName",taskName);
    query.bindValue(":TaskStateOld",Task_Type_Submit);
    query.bindValue(":RefTemplate",refTemplate);
    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();
        qDebug()<<"withdraw task error:"<<errMsg;
    }
    //generate the ack net frame xml data.
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("withdraw"));
    tXmlWriter.writeAttribute(QString("taskState"),QString("%1").arg(Task_Type_Save));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTask::ZCheckOkayTask(QString taskName,QString refTemplate)
{
    qint32 retCode=0;
    QString errMsg;
    //UPDATE `pms`.`TaskInfo` SET `TaskState`='1' WHERE `TaskName`='root-烟台璟言科技在职员工表-20170116213709';
    QSqlQuery query(this->m_db);
    query.prepare("UPDATE `pms`.`TaskInfo` SET `TaskState`=:TaskStateNew , `CheckTime`=:CheckTime WHERE `TaskName`=:TaskName AND `TaskState`=:TaskStateOld AND `RefTemplate`=:RefTemplate");
    query.bindValue(":TaskStateNew",Task_Type_Check_Okay);
    query.bindValue(":CheckTime",QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss"));
    query.bindValue(":TaskName",taskName);
    query.bindValue(":TaskStateOld",Task_Type_Submit);
    query.bindValue(":RefTemplate",refTemplate);
    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();
        qDebug()<<"check okay task error:"<<errMsg;
    }
    //generate the ack net frame xml data.
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("checkokay"));
    tXmlWriter.writeAttribute(QString("taskState"),QString("%1").arg(Task_Type_Check_Okay));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTask::ZCheckFailedTask(QString taskName,QString refTemplate)
{
    qint32 retCode=0;
    QString errMsg;
    //UPDATE `pms`.`TaskInfo` SET `TaskState`='1' WHERE `TaskName`='root-烟台璟言科技在职员工表-20170116213709';
    QSqlQuery query(this->m_db);
    query.prepare("UPDATE `pms`.`TaskInfo` SET `TaskState`=:TaskStateNew , `CheckTime`=:CheckTime WHERE `TaskName`=:TaskName AND `TaskState`=:TaskStateOld AND `RefTemplate`=:RefTemplate");
    query.bindValue(":TaskStateNew",Task_Type_Check_Failed);
    query.bindValue(":CheckTime",QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss"));
    query.bindValue(":TaskName",taskName);
    query.bindValue(":TaskStateOld",Task_Type_Submit);
    query.bindValue(":RefTemplate",refTemplate);
    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();
        qDebug()<<"check failed task error:"<<errMsg;
    }
    //generate the ack net frame xml data.
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("checkfailed"));
    tXmlWriter.writeAttribute(QString("taskState"),QString("%1").arg(Task_Type_Check_Failed));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrmTask::ZArchieveTask(QString taskName,QString refTemplate)
{
    qint32 retCode=0;
    QString errMsg;
    //UPDATE `pms`.`TaskInfo` SET `TaskState`='6' WHERE `TaskName`='root-烟台璟言科技在职员工表-20170116213709';
    QSqlQuery query(this->m_db);
    query.prepare("UPDATE `pms`.`TaskInfo` SET `TaskState`=:TaskStateNew WHERE `TaskName`=:TaskName AND `TaskState`=:TaskStateOld AND `RefTemplate`=:RefTemplate");
    query.bindValue(":TaskStateNew",Task_Type_Archieve);
    query.bindValue(":TaskName",taskName);
    query.bindValue(":TaskStateOld",Task_Type_Check_Okay);
    query.bindValue(":RefTemplate",refTemplate);
    if(!query.exec())
    {
        retCode=-1;
        errMsg=query.lastError().text();
        this->m_opLogMsg=QString("archieve task [%1] failed:%2.").arg(taskName).arg(errMsg);
    }
    //generate the ack net frame xml data.
    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("archieve"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("%1").arg(retCode));
    if(retCode<0)
    {
        tXmlWriter.writeAttribute(QString("errMsg"),errMsg);
    }else{
        tXmlWriter.writeAttribute(QString("taskState"),QString("%1").arg(Task_Type_Archieve));
    }
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
