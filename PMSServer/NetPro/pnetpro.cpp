#include "pnetpro.h"
#include <QXmlStreamReader>
#include <NetPro/pnetfrmheartbeat.h>
#include <NetPro/pnetfrmrole.h>
#include <NetPro/pnetfrmuser.h>
#include <NetPro/pnetfrmfolder.h>
#include <NetPro/pnetfrmfile.h>
#include <NetPro/pnetfrmtemplate.h>
#include <NetPro/pnetfrmvarsource.h>
#include <NetPro/pnetfrmprocess.h>
#include <NetPro/pnetfrmtask.h>
#include <NetPro/pnetfrmlogin.h>
#include <NetPro/pnetfrmform.h>
#include <NetPro/pnetfrmbackup.h>
#include <QFile>
#include <QDir>
PNetPro::PNetPro(QObject *parent) : QObject(parent)
{
    this->m_proType=ProType_Unknown;
}
QString PNetPro::ZParseNetFrmXmlData(QString xmlData,QSqlDatabase db)
{
    QString ackNetFrmXmlData;
    QXmlStreamReader tXmlReader(xmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Heart"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="beat")
                {
                    this->m_proType=ProType_Heart_Beat;
                    QString userName=tXmlReader.readElementText();
                    PNetFrmHeartBeat netFrm(db);
                    if(netFrm.ZHeartBeat(userName)==0)
                    {
                        emit this->ZSignalHeartBeat(userName);
                    }
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else{
                    this->m_proType=ProType_Unknown;
                }
            }else if(nodeName==QString("Update"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="get")
                {
                    this->m_proType=ProType_Update_Get;
                    QString totalBlock=attr.value(QString("totalBlock")).toString();
                    QString currentBlock=attr.value(QString("currentBlock")).toString();
                    QString readPos=attr.value(QString("readPos")).toString();
                    QString readSize=attr.value(QString("readSize")).toString();
                    QString creator=tXmlReader.readElementText();
                    PNetFrmUpdate netFrm(db);
                    netFrm.ZGetNewVersion(totalBlock,currentBlock,readPos.toInt(),readSize.toInt());
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else{
                    this->m_proType=ProType_Unknown;
                }
            }else if(nodeName==QString("Login"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="login")
                {
                    this->m_proType=ProType_Login_Login;
                    QString password=attr.value(QString("password")).toString();
                    QString userName=tXmlReader.readElementText();
                    this->m_loginUserName=userName;
                    PNetFrmLogin netFrm(db);
                    if(netFrm.ZLogin(userName,password)==0)
                    {
                        emit this->ZSignalUserLogin(userName);
                    }
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="logout")
                {
                    this->m_proType=ProType_Login_Logout;
                    QString userName=tXmlReader.readElementText();
                    PNetFrmLogin netFrm(db);
                    if(netFrm.ZLogout(userName)==0)
                    {
                        emit this->ZSignalUserLogout(userName);
                    }
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else{
                    this->m_proType=ProType_Unknown;
                }
            }else if(nodeName==QString("Role"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    this->m_proType=ProType_Role_Add;
                    QString permBits=attr.value(QString("permBits")).toString();
                    QString roleMemo=attr.value(QString("memo")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString roleName=tXmlReader.readElementText();
                    PNetFrmRole netFrmRole(db);
                    netFrmRole.ZAddRole(roleName,permBits,roleMemo,creator);
                    ackNetFrmXmlData=netFrmRole.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmRole.ZGetOpLogMsg());
                }else if(cmd=="mdy")
                {
                    this->m_proType=ProType_Role_Mdy;
                    QString permBits=attr.value(QString("permBits")).toString();
                    QString roleMemo=attr.value(QString("memo")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString roleName=tXmlReader.readElementText();
                    PNetFrmRole netFrmRole(db);
                    netFrmRole.ZMdyRole(roleName,permBits,roleMemo,creator);
                    ackNetFrmXmlData=netFrmRole.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmRole.ZGetOpLogMsg());
                }else if(cmd=="del")
                {
                    this->m_proType=ProType_Role_Del;
                    QString roleName=tXmlReader.readElementText();
                    PNetFrmRole netFrmRole(db);
                    netFrmRole.ZDelRole(roleName);
                    ackNetFrmXmlData=netFrmRole.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmRole.ZGetOpLogMsg());
                }else if(cmd=="list")
                {
                    QString creator=tXmlReader.readElementText();
                    PNetFrmRole netFrmRole(db);
                    netFrmRole.ZListRole(creator);
                    ackNetFrmXmlData=netFrmRole.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmRole.ZGetOpLogMsg());
                }else{
                    this->m_proType=ProType_Unknown;
                }
            }else if(nodeName==QString("User"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    this->m_proType=ProType_User_Add;
                    QString realName=attr.value(QString("realName")).toString();
                    QString roleName=attr.value(QString("roleName")).toString();
                    QString password=attr.value(QString("password")).toString();
                    QString sex=attr.value(QString("sex")).toString();
                    QString mobile=attr.value(QString("mobile")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString userName=tXmlReader.readElementText();
                    PNetFrmUser netFrmUser(db);
                    netFrmUser.ZAddUser(userName,password,roleName,realName,sex,mobile,creator);
                    ackNetFrmXmlData=netFrmUser.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmUser.ZGetOpLogMsg());
                }else if(cmd=="mdy")
                {
                    this->m_proType=ProType_User_Mdy;
                    QString realName=attr.value(QString("realName")).toString();
                    QString roleName=attr.value(QString("roleName")).toString();
                    QString password=attr.value(QString("password")).toString();
                    QString sex=attr.value(QString("sex")).toString();
                    QString mobile=attr.value(QString("mobile")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString userName=tXmlReader.readElementText();
                    PNetFrmUser netFrmUser(db);
                    netFrmUser.ZMdyUser(userName,password,roleName,realName,sex,mobile,creator);
                    ackNetFrmXmlData=netFrmUser.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmUser.ZGetOpLogMsg());
                }else if(cmd=="del")
                {
                    this->m_proType=ProType_User_Del;
                    QString roleName=attr.value(QString("roleName")).toString();
                    QString userName=tXmlReader.readElementText();
                    PNetFrmUser netFrmUser(db);
                    netFrmUser.ZDelUser(userName,roleName);
                    ackNetFrmXmlData=netFrmUser.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmUser.ZGetOpLogMsg());
                }else{
                    this->m_proType=ProType_Unknown;
                }
            }else if(nodeName==QString("Folder"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    this->m_proType=ProType_Folder_Add;
                    QString creator=attr.value(QString("creator")).toString();
                    QString folderName=tXmlReader.readElementText();
                    PNetFrmFolder netFrmFolder(db);
                    netFrmFolder.ZAddFolder(folderName,creator);
                    ackNetFrmXmlData=netFrmFolder.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmFolder.ZGetOpLogMsg());
                }else if(cmd=="del")
                {
                    this->m_proType=ProType_Folder_Del;
                    QString creator=attr.value(QString("creator")).toString();
                    QString folderName=tXmlReader.readElementText();
                    PNetFrmFolder netFrmFolder(db);
                    netFrmFolder.ZDelFolder(folderName,creator);
                    ackNetFrmXmlData=netFrmFolder.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmFolder.ZGetOpLogMsg());
                }else if(cmd=="list")
                {
                    this->m_proType=ProType_Folder_List;
                    QString creator=tXmlReader.readElementText();
                    PNetFrmFolder netFrmFolder(db);
                    netFrmFolder.ZListFolder(creator);
                    ackNetFrmXmlData=netFrmFolder.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmFolder.ZGetOpLogMsg());
                }else{
                    this->m_proType=ProType_Unknown;
                }
            }else if(nodeName==QString("File"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    this->m_proType=ProType_File_Add;
                    QString folderName=attr.value(QString("folder")).toString();
                    QString fileType=attr.value(QString("type")).toString();
                    qint32 fileSize=attr.value(QString("size")).toInt();
                    QString creator=attr.value(QString("creator")).toString();
                    QString fileName=tXmlReader.readElementText();
                    PNetFrmFile netFrmFile(db);
                    netFrmFile.ZAddFile(folderName,fileName,fileType,fileSize,creator);
                    ackNetFrmXmlData=netFrmFile.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmFile.ZGetOpLogMsg());
                }else if(cmd=="updata"){
                    this->m_proType=ProType_File_UpData;
                    QString folderName=attr.value(QString("folder")).toString();
                    QString totalBlock=attr.value(QString("totalBlock")).toString();
                    QString currentBlock=attr.value(QString("currentBlock")).toString();
                    QString fileData=attr.value(QString("data")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString fileName=tXmlReader.readElementText();
                    PNetFrmFile netFrmFile(db);
                    netFrmFile.ZAddData(folderName,fileName,fileData,totalBlock,currentBlock,creator);
                    ackNetFrmXmlData=netFrmFile.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmFile.ZGetOpLogMsg());
                }else if(cmd=="del")
                {
                    this->m_proType=ProType_File_Del;
                    QString folderName=attr.value(QString("folder")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString fileName=tXmlReader.readElementText();
                    PNetFrmFile netFrmFile(db);
                    netFrmFile.ZDelFile(folderName,fileName,creator);
                    ackNetFrmXmlData=netFrmFile.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmFile.ZGetOpLogMsg());
                }else if(cmd=="get")
                {
                    this->m_proType=ProType_File_Get;
                    QString folderName=attr.value(QString("folder")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString fileName=tXmlReader.readElementText();
                    PNetFrmFile netFrmFile(db);
                    netFrmFile.ZGetFile(folderName,fileName,creator);
                    ackNetFrmXmlData=netFrmFile.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmFile.ZGetOpLogMsg());
                }else if(cmd=="dwndata"){
                    this->m_proType=ProType_File_DwnData;
                    QString folderName=attr.value(QString("folder")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString totalBlock=attr.value(QString("totalBlock")).toString();
                    QString currentBlock=attr.value(QString("currentBlock")).toString();
                    QString readPos=attr.value(QString("readPos")).toString();
                    QString readSize=attr.value(QString("readSize")).toString();
                    QString fileName=tXmlReader.readElementText();
                    PNetFrmFile netFrmFile(db);
                    netFrmFile.ZGetData(folderName,fileName,totalBlock,currentBlock,readPos.toInt(),readSize.toInt(),creator);
                    ackNetFrmXmlData=netFrmFile.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrmFile.ZGetOpLogMsg());
                }else{
                    this->m_proType=ProType_Unknown;
                }
            }else if(nodeName==QString("Template"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    this->m_proType=ProType_Template_Add;
                    QString creator=attr.value(QString("creator")).toString();
                    QString templateName=tXmlReader.readElementText();
                    PNetFrmTemplate netFrm(db);
                    netFrm.ZAddTemplate(templateName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="del")
                {
                    this->m_proType=ProType_Template_Del;
                    QString creator=attr.value(QString("creator")).toString();
                    QString templateName=tXmlReader.readElementText();
                    PNetFrmTemplate netFrm(db);
                    netFrm.ZDelTemplate(templateName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="get")
                {
                    this->m_proType=ProType_Template_Get;
                    QString creator=attr.value(QString("creator")).toString();
                    QString templateName=tXmlReader.readElementText();
                    PNetFrmTemplate netFrm(db);
                    netFrm.ZGetTemplate(templateName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="list")
                {
                    this->m_proType=ProType_Template_List;
                    QString creator=tXmlReader.readElementText();
                    PNetFrmTemplate netFrm(db);
                    netFrm.ZListTemplate(creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="save")
                {
                    this->m_proType=ProType_Template_Save;
                    QString creator=attr.value(QString("creator")).toString();
                    QString xmlData=attr.value(QString("data")).toString();
                    QString templateName=tXmlReader.readElementText();
                    PNetFrmTemplate netFrm(db);
                    netFrm.ZSaveTemplate(templateName,xmlData,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="bind")
                {
                    this->m_proType=ProType_Template_Bind;
                    QString creator=attr.value(QString("creator")).toString();
                    QString varSourceName=attr.value(QString("varsource")).toString();
                    QString templateName=tXmlReader.readElementText();
                    PNetFrmTemplate netFrm(db);
                    netFrm.ZBindVarSource(templateName,varSourceName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="unbind")
                {
                    this->m_proType=ProType_Template_Unbind;
                    QString creator=attr.value(QString("creator")).toString();
                    QString varSourceName=attr.value(QString("varsource")).toString();
                    QString templateName=tXmlReader.readElementText();
                    PNetFrmTemplate netFrm(db);
                    netFrm.ZUnbindVarSource(templateName,varSourceName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else{
                    this->m_proType=ProType_Unknown;
                }
            }else if(nodeName==QString("VarSource"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    this->m_proType=ProType_VarSource_Add;
                    QString creator=attr.value(QString("creator")).toString();
                    QString varSourceName=tXmlReader.readElementText();
                    PNetFrmVarSource netFrm(db);
                    netFrm.ZAddVarSource(varSourceName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="del")
                {
                    this->m_proType=ProType_VarSource_Del;
                    QString creator=attr.value(QString("creator")).toString();
                    QString varSourceName=tXmlReader.readElementText();
                    PNetFrmVarSource netFrm(db);
                    netFrm.ZDelVarSource(varSourceName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="get")
                {
                    this->m_proType=ProType_VarSource_Get;
                    QString creator=attr.value(QString("creator")).toString();
                    QString varSourceName=tXmlReader.readElementText();
                    PNetFrmVarSource netFrm(db);
                    netFrm.ZGetVarSource(varSourceName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="save")
                {
                    this->m_proType=ProType_VarSource_Save;
                    QString creator=attr.value(QString("creator")).toString();
                    QString data=attr.value(QString("data")).toString();
                    QString varSourceName=tXmlReader.readElementText();
                    PNetFrmVarSource netFrm(db);
                    netFrm.ZSaveVarSource(varSourceName,data,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else{
                    this->m_proType=ProType_Unknown;
                }
            }else if(nodeName==QString("Process"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    this->m_proType=ProType_Process_Add;
                    QString creator=attr.value(QString("creator")).toString();
                    QString processName=tXmlReader.readElementText();
                    PNetFrmProcess netFrm(db);
                    netFrm.ZAddProcess(processName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="del")
                {
                    this->m_proType=ProType_Process_Del;
                    QString creator=attr.value(QString("creator")).toString();
                    QString processName=tXmlReader.readElementText();
                    PNetFrmProcess netFrm(db);
                    netFrm.ZDelProcess(processName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="get")
                {
                    this->m_proType=ProType_Process_Get;
                    QString creator=attr.value(QString("creator")).toString();
                    QString processName=tXmlReader.readElementText();
                    PNetFrmProcess netFrm(db);
                    netFrm.ZGetProcess(processName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="save")
                {
                    this->m_proType=ProType_Process_Save;
                    qint32 stepNum=attr.value(QString("stepNum")).toInt();
                    QString data=attr.value(QString("data")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString processName=tXmlReader.readElementText();
                    PNetFrmProcess netFrm(db);
                    netFrm.ZSaveProcess(processName,stepNum,data,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="list")
                {
                    this->m_proType=ProType_Process_List;
                    QString creator=tXmlReader.readElementText();
                    PNetFrmProcess netFrm(db);
                    netFrm.ZListProcess(creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else{
                    this->m_proType=ProType_Unknown;
                }
            }else if(nodeName==QString("Task"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="listnew")
                {
                    this->m_proType=ProType_Task_ListNew;
                    QString roleName=tXmlReader.readElementText();
                    PNetFrmTask netFrm(db);
                    netFrm.ZListNewTask(roleName);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="add")
                {
                    this->m_proType=ProType_Task_Add;
                    QString refTemplate=attr.value(QString("refTemplate")).toString();
                    QString refProcess=attr.value(QString("refProcess")).toString();
                    QString refStep=attr.value(QString("refStep")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString checker=attr.value(QString("checker")).toString();
                    QString taskName=tXmlReader.readElementText();
                    PNetFrmTask netFrm(db);
                    netFrm.ZAddTask(taskName,refTemplate,refProcess,refStep,creator,checker);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="list")
                {
                    this->m_proType=ProType_Task_List;
                    qint32 taskState=attr.value(QString("state")).toInt();
                    QString creator=tXmlReader.readElementText();
                    PNetFrmTask netFrm(db);
                    netFrm.ZListTask(creator,taskState);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="get")
                {
                    this->m_proType=ProType_Task_Get;
                    QString refTemplate=attr.value(QString("refTemplate")).toString();
                    QString taskName=tXmlReader.readElementText();
                    PNetFrmTask netFrm(db);
                    netFrm.ZOpenTask(taskName,refTemplate);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="del")
                {
                    this->m_proType=ProType_Task_Del;
                    QString refTemplate=attr.value(QString("refTemplate")).toString();
                    QString taskName=tXmlReader.readElementText();
                    PNetFrmTask netFrm(db);
                    netFrm.ZDelTask(taskName,refTemplate);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="save")
                {
                    this->m_proType=ProType_Task_Save;
                    QString refTemplate=attr.value(QString("refTemplate")).toString();
                    QString taskData=attr.value(QString("data")).toString();
                    QString taskName=tXmlReader.readElementText();
                    PNetFrmTask netFrm(db);
                    netFrm.ZSaveTask(taskName,refTemplate,taskData);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="submit")
                {
                    this->m_proType=ProType_Task_Submit;
                    QString refTemplate=attr.value(QString("refTemplate")).toString();
                    QString taskName=tXmlReader.readElementText();
                    PNetFrmTask netFrm(db);
                    netFrm.ZSubmitTask(taskName,refTemplate);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="withdraw")
                {
                    this->m_proType=ProType_Task_Withdraw;
                    QString refTemplate=attr.value(QString("refTemplate")).toString();
                    QString taskName=tXmlReader.readElementText();
                    PNetFrmTask netFrm(db);
                    netFrm.ZWithdrawTask(taskName,refTemplate);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="checkokay")
                {
                    this->m_proType=ProType_Task_CheckOkay;
                    QString refTemplate=attr.value(QString("refTemplate")).toString();
                    QString taskName=tXmlReader.readElementText();
                    PNetFrmTask netFrm(db);
                    netFrm.ZCheckOkayTask(taskName,refTemplate);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="checkfailed")
                {
                    this->m_proType=ProType_Task_CheckFailed;
                    QString refTemplate=attr.value(QString("refTemplate")).toString();
                    QString taskName=tXmlReader.readElementText();
                    PNetFrmTask netFrm(db);
                    netFrm.ZCheckFailedTask(taskName,refTemplate);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="archieve")
                {
                    this->m_proType=ProType_Task_Archieve;
                    QString refTemplate=attr.value(QString("refTemplate")).toString();
                    QString taskName=tXmlReader.readElementText();
                    PNetFrmTask netFrm(db);
                    netFrm.ZArchieveTask(taskName,refTemplate);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else{
                    this->m_proType=ProType_Unknown;
                }
            }else if(nodeName==QString("Form"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    this->m_proType=ProType_Form_Add;
                    QString creator=attr.value(QString("creator")).toString();
                    QString formName=tXmlReader.readElementText();
                    PNetFrmForm netFrm(db);
                    netFrm.ZNewForm(formName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="del")
                {
                    this->m_proType=ProType_Form_Del;
                    QString creator=attr.value(QString("creator")).toString();
                    QString formName=tXmlReader.readElementText();
                    PNetFrmForm netFrm(db);
                    netFrm.ZDelForm(formName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="save")
                {
                    this->m_proType=ProType_Form_Save;
                    QString creator=attr.value(QString("creator")).toString();
                    QString formData=attr.value(QString("data")).toString();
                    QString formName=tXmlReader.readElementText();
                    PNetFrmForm netFrm(db);
                    netFrm.ZSaveForm(formName,formData,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="get")
                {
                    this->m_proType=ProType_Form_Get;
                    QString creator=attr.value(QString("creator")).toString();
                    QString formName=tXmlReader.readElementText();
                    PNetFrmForm netFrm(db);
                    netFrm.ZGetForm(formName,creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="list")
                {
                    this->m_proType=ProType_Form_List;
                    QString creator=tXmlReader.readElementText();
                    PNetFrmForm netFrm(db);
                    netFrm.ZListForm(creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else{
                    this->m_proType=ProType_Unknown;
                }
            }else if(nodeName==QString("Backup"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="list")
                {
                    this->m_proType=ProType_Backup_List;
                    QString creator=tXmlReader.readElementText();
                    PNetFrmBackup netFrm(db);
                    netFrm.ZListBackup();
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="backup")
                {
                    this->m_proType=ProType_Backup_Backup;
                    QString creator=tXmlReader.readElementText();
                    PNetFrmBackup netFrm(db);
                    netFrm.ZDoBackup(creator);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="restore")
                {
                    this->m_proType=ProType_Backup_Restore;
                    QString creator=attr.value(QString("creator")).toString();
                    QString backupName=tXmlReader.readElementText();
                    PNetFrmBackup netFrm(db);
                    netFrm.ZDoRestore(backupName);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else if(cmd=="delete")
                {
                    this->m_proType=ProType_Backup_Delete;
                    QString creator=attr.value(QString("creator")).toString();
                    QString backupName=tXmlReader.readElementText();
                    PNetFrmBackup netFrm(db);
                    netFrm.ZDoDelete(backupName);
                    ackNetFrmXmlData=netFrm.ZGetAckNetFrmXmlData();
                    emit this->ZSignalOpLog(netFrm.ZGetOpLogMsg());
                }else{
                    this->m_proType=ProType_Unknown;
                }
            }else{
                this->m_proType=ProType_Unknown;
            }
        }//StarElement.
    }
    return ackNetFrmXmlData;
}
QString PNetPro::ZGetLoginUserName()
{
    return this->m_loginUserName;
}
PNetPro::PNetProType PNetPro::ZGetNetProType()
{
    return this->m_proType;
}
