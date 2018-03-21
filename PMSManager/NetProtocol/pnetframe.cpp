#include "pnetframe.h"
#include <QDebug>
#include <QXmlStreamWriter>
#include "pgblpara.h"

#include <QFileInfo>
MyNetQueue* MyNetQueue::m_pInstance=NULL;
PNetFrame::PNetFrame()
{
    this->m_frmSyncHeader=QString("BePMS");
    this->m_frmSerialNo=MyNetQueue::ZGetInstance()->ZGetRandomNumber();
    this->m_waitAckTimeoutCnt=0;
}
PNetFrame::~PNetFrame()
{
}
void PNetFrame::ZSetNetFrmSerialNo(qint32 no)
{
    this->m_frmSerialNo=no;
}
qint32 PNetFrame::ZGetNetFrmSerialNo()
{
    return this->m_frmSerialNo;
}

qint32 PNetFrame::ZPackNetFrmData(QByteArray *destArray,qint32 arraySize)
{
    //sync header.
    //frame size.
    //frame serial No.
    //frame xml data.
    qint32 index=0;
    QByteArray frmSyncHeader=this->m_frmSyncHeader.toUtf8();
    QByteArray frmSize=Int2QByte(this->m_frmSize);
    QByteArray frmSerialNo=Int2QByte(this->m_frmSerialNo);
    QByteArray frmXmlData=this->m_frmXmlData.toUtf8();

    if((frmSyncHeader.size()+frmSize.size()+frmSerialNo.size()+frmXmlData.size())>arraySize)
    {
        //dest array is not big enough.
        return -1;
    }
    this->m_frmSize=frmSerialNo.size()+frmXmlData.size();
    frmSize=Int2QByte(this->m_frmSize);

    destArray->insert(index,frmSyncHeader);
    index+=frmSyncHeader.size();

    destArray->insert(index,frmSize);
    index+=frmSize.size();

    destArray->insert(index,frmSerialNo);
    index+=frmSerialNo.size();

    destArray->insert(index,frmXmlData);
    index+=frmXmlData.size();

    //qDebug()<<"frmSize:"<<this->m_frmSize<<",frmSerialNo:"<<this->m_frmSerialNo<<",xmlSize:"<<frmXmlData.size();
    return index;
}
qint32 PNetFrame::ZGetWaitAckTimeoutCnt()
{
    return this->m_waitAckTimeoutCnt;
}
void PNetFrame::ZIncWaitAckTimeoutCnt()
{
    this->m_waitAckTimeoutCnt++;
}
QString PNetFrame::ZGetNetFrmXmlData()
{
    return this->m_frmXmlData;
}
void PNetFrame_Login::ZLogin(QString userName,QString password)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Login"));
    tXmlWriter.writeStartElement(QString("Login"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("login"));
    tXmlWriter.writeAttribute(QString("password"),QString(password.toUtf8().toBase64()));
    qDebug()<<"Password:"<<password.toUtf8().toBase64();
    tXmlWriter.writeCharacters(userName);
    tXmlWriter.writeEndElement();//Login.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Login::ZLogout(QString userName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Login"));
    tXmlWriter.writeStartElement(QString("Login"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("logout"));
    tXmlWriter.writeCharacters(userName);
    tXmlWriter.writeEndElement();//Login.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Login::ZHeartBeat(QString userName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Heart"));
    tXmlWriter.writeStartElement(QString("Heart"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("beat"));
    tXmlWriter.writeCharacters(userName);
    tXmlWriter.writeEndElement();//Heart.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Update::ZGetNewVersionData(qint32 totalBlock,qint32 currentBlock,qint32 readPos,qint32 readSize)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Update"));
    tXmlWriter.writeStartElement(QString("Update"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("totalBlock"),QString("%1").arg(totalBlock));
    tXmlWriter.writeAttribute(QString("currentBlock"),QString("%1").arg(currentBlock));
    tXmlWriter.writeAttribute(QString("readPos"),QString("%1").arg(readPos));
    tXmlWriter.writeAttribute(QString("readSize"),QString("%1").arg(readSize));
    tXmlWriter.writeCharacters(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeEndElement();//File.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
//list obj.
//query all roles,all users,all templates,all files,all tasks.
//objName:roles,users,templates,files,tasks.
void PNetFrame_Role::ZListRole()
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Role"));
    tXmlWriter.writeStartElement(QString("Role"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
    tXmlWriter.writeCharacters(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeEndElement();//Role.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Role::ZAddRole(QString roleName,QString permBits,QString roleMemo)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Role"));
    tXmlWriter.writeStartElement(QString("Role"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("permBits"),permBits);
    tXmlWriter.writeAttribute(QString("memo"),roleMemo);
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(roleName);
    tXmlWriter.writeEndElement();//Role.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Role::ZMdyRole(QString roleName,QString permBits,QString roleMemo)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Role"));
    tXmlWriter.writeStartElement(QString("Role"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("mdy"));
    tXmlWriter.writeAttribute(QString("permBits"),permBits);
    tXmlWriter.writeAttribute(QString("memo"),roleMemo);
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(roleName);
    tXmlWriter.writeEndElement();//Role.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Role::ZDelRole(QString roleName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Role"));
    tXmlWriter.writeStartElement(QString("Role"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeCharacters(roleName);
    tXmlWriter.writeEndElement();//Role.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Role::ZGetRole(QString roleName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Role"));
    tXmlWriter.writeStartElement(QString("Role"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeCharacters(roleName);
    tXmlWriter.writeEndElement();//Role.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_User::ZAddUser(QString userName,QString realName,QString roleName,QString password,QString sex,QString mobile)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("User"));
    tXmlWriter.writeStartElement(QString("User"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("realName"),realName);
    tXmlWriter.writeAttribute(QString("roleName"),roleName);
    tXmlWriter.writeAttribute(QString("password"),QString(password.toUtf8().toBase64()));
    tXmlWriter.writeAttribute(QString("sex"),sex);
    tXmlWriter.writeAttribute(QString("mobile"),mobile);
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(userName);
    tXmlWriter.writeEndElement();//User.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_User::ZMdyUser(QString userName,QString realName,QString roleName,QString password,QString sex,QString mobile)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("User"));
    tXmlWriter.writeStartElement(QString("User"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("mdy"));
    tXmlWriter.writeAttribute(QString("realName"),realName);
    tXmlWriter.writeAttribute(QString("roleName"),roleName);
    tXmlWriter.writeAttribute(QString("password"),QString(password.toUtf8().toBase64()));
    tXmlWriter.writeAttribute(QString("sex"),sex);
    tXmlWriter.writeAttribute(QString("mobile"),mobile);
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(userName);
    tXmlWriter.writeEndElement();//User.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_User::ZDelUser(QString userName,QString roleName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("User"));
    tXmlWriter.writeStartElement(QString("User"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("roleName"),roleName);
    tXmlWriter.writeCharacters(userName);
    tXmlWriter.writeEndElement();//User.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_User::ZGetUser(QString userName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("User"));
    tXmlWriter.writeStartElement(QString("User"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeCharacters(userName);
    tXmlWriter.writeEndElement();//User.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Folder::ZAddFolder(QString folderName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Folder"));
    tXmlWriter.writeStartElement(QString("Folder"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(folderName);
    tXmlWriter.writeEndElement();//Folder.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Folder::ZDelFolder(QString folderName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Folder"));
    tXmlWriter.writeStartElement(QString("Folder"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(folderName);
    tXmlWriter.writeEndElement();//Folder.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Folder::ZListFolder()
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Folder"));
    tXmlWriter.writeStartElement(QString("Folder"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
    tXmlWriter.writeCharacters(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeEndElement();//Folder.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_File::ZAddFile(QString filePath,QString folderName,qint32 fileSize)
{
    this->m_frmType=Type_Add_File;

    QString suffix=filePath.right(4).toLower();
    QString fileType;
    if(suffix==QString(".pdf"))
    {
        fileType="pdf";
    }else if(suffix==QString(".png"))
    {
        fileType="png";
    }else if(suffix==QString(".jpg"))
    {
        fileType="jpg";
    }

    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("File"));
    tXmlWriter.writeStartElement(QString("File"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("folder"),folderName);
    tXmlWriter.writeAttribute(QString("type"),fileType);
    tXmlWriter.writeAttribute(QString("size"),QString("%1").arg(fileSize));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(QFileInfo(filePath).fileName());
    tXmlWriter.writeEndElement();//File.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_File::ZAddData(QString filePath,QString folderName,qint32 readPos,qint32 readSize,qint32 totalBlock,qint32 currentBlock)
{
    this->m_frmType=Type_Add_Data;
    this->m_totalBlock=totalBlock;
    this->m_currentBlock=currentBlock;

    this->m_filePath=filePath;
    this->m_folderName=folderName;
    this->m_readPos=readPos;
    this->m_readSize=readSize;

    qDebug()<<"addData:"<<"readPos:"<<readPos<<",readSize:"<<readSize<<",totalBlock="<<totalBlock<<",currentBlock="<<currentBlock;
}
bool PNetFrame_File::ZGetBlockData()
{
    QByteArray fileData;
    QFile file(this->m_filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    if(!file.seek(this->m_readPos))
    {
        return false;
    }
    fileData=file.read(this->m_readSize);
    file.close();

    qDebug()<<"getBlockData:"<<"readSize:"<<fileData.size();
    qDebug()<<"totalBlocK:"<<this->m_totalBlock<<",currentBlocK:"<<this->m_currentBlock;
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("File"));
    tXmlWriter.writeStartElement(QString("File"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("updata"));
    tXmlWriter.writeAttribute(QString("folder"),this->m_folderName);
    tXmlWriter.writeAttribute(QString("totalBlock"),QString("%1").arg(this->m_totalBlock));
    tXmlWriter.writeAttribute(QString("currentBlock"),QString("%1").arg(this->m_currentBlock));
    tXmlWriter.writeAttribute(QString("data"),fileData.toBase64());
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(QFileInfo(this->m_filePath).fileName());
    tXmlWriter.writeEndElement();//File.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
    qDebug()<<"readPos:"<<this->m_readPos<<",readSize:"<<this->m_readSize;
    return true;
}
qint32 PNetFrame_File::ZGetTotalBlock()
{
    return this->m_totalBlock;
}
qint32 PNetFrame_File::ZGetCurrentBlock()
{
    return this->m_currentBlock;
}
void PNetFrame_File::ZDelFile(QString fileName,QString folderName)
{
    this->m_frmType=Type_Del_File;

    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("File"));
    tXmlWriter.writeStartElement(QString("File"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("folder"),folderName);
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(fileName);
    tXmlWriter.writeEndElement();//File.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_File::ZGetFile(QString fileName,QString folderName)
{
    this->m_frmType=Type_Get_File;

    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("File"));
    tXmlWriter.writeStartElement(QString("File"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("folder"),folderName);
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(fileName);
    tXmlWriter.writeEndElement();//File.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_File::ZGetData(QString fileName,QString folderName,qint32 totalBlock,qint32 currentBlock,qint32 readPos,qint32 readSize)
{
    this->m_frmType=Type_Get_DwnData;

    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("File"));
    tXmlWriter.writeStartElement(QString("File"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("dwndata"));
    tXmlWriter.writeAttribute(QString("folder"),folderName);
    tXmlWriter.writeAttribute(QString("totalBlock"),QString("%1").arg(totalBlock));
    tXmlWriter.writeAttribute(QString("currentBlock"),QString("%1").arg(currentBlock));
    tXmlWriter.writeAttribute(QString("readPos"),QString("%1").arg(readPos));
    tXmlWriter.writeAttribute(QString("readSize"),QString("%1").arg(readSize));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(fileName);
    tXmlWriter.writeEndElement();//File.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Template::ZAddTemplate(QString templateName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    tXmlWriter.writeStartElement(QString("Template"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(templateName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Template::ZDelTemplate(QString templateName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    tXmlWriter.writeStartElement(QString("Template"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(templateName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Template::ZGetTemplate(QString templateName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    tXmlWriter.writeStartElement(QString("Template"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(templateName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Template::ZSaveTemplate(QString templateName,QString templateXmlData)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    tXmlWriter.writeStartElement(QString("Template"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("save"));
    tXmlWriter.writeAttribute(QString("data"),QString(templateXmlData.toUtf8().toBase64()));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(templateName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Template::ZBindVarSource(QString templateName,QString varSourceName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    tXmlWriter.writeStartElement(QString("Template"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("bind"));
    tXmlWriter.writeAttribute(QString("varsource"),varSourceName);
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(templateName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Template::ZUnbindVarSource(QString templateName,QString varSourceName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    tXmlWriter.writeStartElement(QString("Template"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("unbind"));
    tXmlWriter.writeAttribute(QString("varsource"),varSourceName);
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(templateName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Template::ZListTemplate()
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Template"));
    tXmlWriter.writeStartElement(QString("Template"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
    tXmlWriter.writeCharacters(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeEndElement();//Template.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_VarSource::ZAddVarSource(QString name)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("VarSource"));
    tXmlWriter.writeStartElement(QString("VarSource"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(name);
    tXmlWriter.writeEndElement();//VarSource.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_VarSource::ZDelVarSource(QString name)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("VarSource"));
    tXmlWriter.writeStartElement(QString("VarSource"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(name);
    tXmlWriter.writeEndElement();//VarSource.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_VarSource::ZGetVarSource(QString name)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("VarSource"));
    tXmlWriter.writeStartElement(QString("VarSource"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(name);
    tXmlWriter.writeEndElement();//VarSource.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_VarSource::ZSaveVarSource(QString name,QString varSourceXmlData)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("VarSource"));
    tXmlWriter.writeStartElement(QString("VarSource"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("save"));
    tXmlWriter.writeAttribute(QString("data"),QString(varSourceXmlData.toUtf8().toBase64()));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(name);
    tXmlWriter.writeEndElement();//VarSource.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Process::ZAddProcess(QString processName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Process"));
    tXmlWriter.writeStartElement(QString("Process"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(processName);
    tXmlWriter.writeEndElement();//Process.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Process::ZDelProcess(QString processName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Process"));
    tXmlWriter.writeStartElement(QString("Process"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(processName);
    tXmlWriter.writeEndElement();//Process.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Process::ZGetProcess(QString processName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Process"));
    tXmlWriter.writeStartElement(QString("Process"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(processName);
    tXmlWriter.writeEndElement();//Process.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Process::ZSaveProcess(QString processName,qint32 stepNum,QString processXmlData)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Process"));
    tXmlWriter.writeStartElement(QString("Process"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("save"));
    tXmlWriter.writeAttribute(QString("stepNum"),QString("%1").arg(stepNum));
    tXmlWriter.writeAttribute(QString("data"),processXmlData.toUtf8().toBase64());
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(processName);
    tXmlWriter.writeEndElement();//Process.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Process::ZListProcess()
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Process"));
    tXmlWriter.writeStartElement(QString("Process"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
    tXmlWriter.writeCharacters(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeEndElement();//Process.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Task::ZListNewTask()
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("listnew"));
    tXmlWriter.writeCharacters(MyUserInfo::ZGetInstance()->m_UserInfo.m_roleName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Task::ZListTask(qint32 taskState)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
    tXmlWriter.writeAttribute(QString("state"),QString("%1").arg(taskState));
    tXmlWriter.writeCharacters(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Task::ZNewTask(QString taskName,QString refTemplateName,QString refProcess,QString refStep)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("refTemplate"),refTemplateName);
    tXmlWriter.writeAttribute(QString("refProcess"),refProcess);
    tXmlWriter.writeAttribute(QString("refStep"),refStep);
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeAttribute(QString("checker"),MyUserInfo::ZGetInstance()->m_UserInfo.m_Creator);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Task::ZOpenTask(QString taskName,QString refTemplateName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("refTemplate"),refTemplateName);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Task::ZSaveTask(QString taskName,QString refTemplateName,QString taskValueXmlData,QStringList auxList)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("save"));
    tXmlWriter.writeAttribute(QString("refTemplate"),refTemplateName);
    //辅助数据，生产线/机器号,班组，订单号，产品号
    tXmlWriter.writeAttribute(QString("machineNo"),auxList.at(0));
    tXmlWriter.writeAttribute(QString("classNo"),auxList.at(1));
    tXmlWriter.writeAttribute(QString("orderNo"),auxList.at(2));
    tXmlWriter.writeAttribute(QString("productNo"),auxList.at(3));
    tXmlWriter.writeAttribute(QString("data"),QString(taskValueXmlData.toUtf8().toBase64()));
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Task::ZDelTask(QString taskName,QString refTemplateName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("refTemplate"),refTemplateName);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Task::ZSubmitTask(QString taskName,QString refTemplateName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("submit"));
    tXmlWriter.writeAttribute(QString("refTemplate"),refTemplateName);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Task::ZWithdrawTask(QString taskName,QString refTemplateName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("withdraw"));
    tXmlWriter.writeAttribute(QString("refTemplate"),refTemplateName);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Task::ZCheckOkayTask(QString taskName,QString refTemplateName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("checkokay"));
    tXmlWriter.writeAttribute(QString("refTemplate"),refTemplateName);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Task::ZCheckFailedTask(QString taskName,QString refTemplateName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("checkfailed"));
    tXmlWriter.writeAttribute(QString("refTemplate"),refTemplateName);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Task::ZArchieveTask(QString taskName,QString refTemplateName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));
    tXmlWriter.writeStartElement(QString("Task"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("archieve"));
    tXmlWriter.writeAttribute(QString("refTemplate"),refTemplateName);
    tXmlWriter.writeCharacters(taskName);
    tXmlWriter.writeEndElement();//Task.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Form::ZListForm()
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Form"));
    tXmlWriter.writeStartElement(QString("Form"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
    tXmlWriter.writeCharacters(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeEndElement();//Form.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Form::ZNewForm(QString formName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Form"));
    tXmlWriter.writeStartElement(QString("Form"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("add"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(formName);
    tXmlWriter.writeEndElement();//Form.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Form::ZGetForm(QString formName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Form"));
    tXmlWriter.writeStartElement(QString("Form"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("get"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(formName);
    tXmlWriter.writeEndElement();//Form.
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Form::ZDelForm(QString formName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Form"));
    tXmlWriter.writeStartElement(QString("Form"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("del"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(formName);
    tXmlWriter.writeEndElement();//Form.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Form::ZSaveForm(QString formName,QString xmlData)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Form"));
    tXmlWriter.writeStartElement(QString("Form"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("save"));
    tXmlWriter.writeAttribute(QString("data"),QString(xmlData.toUtf8().toBase64()));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(formName);
    tXmlWriter.writeEndElement();//Form.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Backup::ZListBackup()
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Backup"));
    tXmlWriter.writeStartElement(QString("Backup"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("list"));
    tXmlWriter.writeCharacters(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeEndElement();//Backup.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Backup::ZDoBackup()
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Backup"));
    tXmlWriter.writeStartElement(QString("Backup"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("backup"));
    tXmlWriter.writeCharacters(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeEndElement();//Backup.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Backup::ZDoRestore(QString backupName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Backup"));
    tXmlWriter.writeStartElement(QString("Backup"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("restore"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(backupName);
    tXmlWriter.writeEndElement();//Backup.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
void PNetFrame_Backup::ZDoDelete(QString backupName)
{
    QXmlStreamWriter  tXmlWriter(&this->m_frmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Backup"));
    tXmlWriter.writeStartElement(QString("Backup"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("delete"));
    tXmlWriter.writeAttribute(QString("creator"),MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    tXmlWriter.writeCharacters(backupName);
    tXmlWriter.writeEndElement();//Backup.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
}
