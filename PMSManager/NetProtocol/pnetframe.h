#ifndef PNETFRAME_H
#define PNETFRAME_H

#include <QByteArray>
#include <QList>
#include <QMutex>
#include <QQueue>
#include <QWaitCondition>
#include <QtGlobal>
#include <QTime>
#include <QMap>
#include <QTextEdit>
#include "BasePart/zbaseinfodia.h"
class ZBaseInfoDia;
class PNetFrame
{
public:
    PNetFrame();
    virtual ~PNetFrame();

    void ZSetNetFrmSerialNo(qint32 no);
    qint32 ZGetNetFrmSerialNo();

    qint32 ZPackNetFrmData(QByteArray *destArray,qint32 arraySize);

    qint32 ZGetWaitAckTimeoutCnt();
    void ZIncWaitAckTimeoutCnt();

    QString ZGetNetFrmXmlData();
public:
    QString m_frmSyncHeader;//BePMS.
    qint32 m_frmSize; //frame total size.
    qint32 m_frmSerialNo;//serial No.
    QString m_frmXmlData;//frame xml data.
private:
    qint32 m_waitAckTimeoutCnt;//wait ack timeout counter.
};
class PNetFrame_Login:public PNetFrame
{
public:
    void ZLogin(QString userName,QString password);
    void ZLogout(QString userName);
    void ZHeartBeat(QString userName);
};
class PNetFrame_Update:public PNetFrame
{
public:
    void ZGetNewVersionData(qint32 totalBlock,qint32 currentBlock,qint32 readPos,qint32 readSize);
};
class PNetFrame_Role:public PNetFrame
{
public:
    void ZAddRole(QString roleName,QString parentName,QString permBits,QString roleMemo);
    void ZMdyRole(QString roleName,QString permBits,QString roleMemo);
    void ZDelRole(QString roleName);
    void ZGetRole(QString roleName);
    void ZListRole();
};
class PNetFrame_User:public PNetFrame
{
public:
    void ZAddUser(QString userName,QString realName,QString roleName,QString password,QString sex,QString mobile);
    void ZMdyUser(QString userName,QString realName,QString roleName,QString password,QString sex,QString mobile);
    void ZDelUser(QString userName,QString roleName);
    void ZDelUserList(QStringList userNameRoleNameList);
    void ZGetUser(QString userName);
};
class PNetFrame_Folder:public PNetFrame
{
public:
    void ZAddFolder(QString folderName);
    void ZDelFolder(QString folderName);
    void ZListFolder();
};
class PNetFrame_File:public PNetFrame
{
public:
    typedef enum{
        Type_Add_File=1,
        Type_Add_Data=2,
        Type_Del_File=3,
        Type_Get_File=4,
        Type_Get_DwnData=5,
    }FileFrameType;
    void ZAddFile(QString filePath,QString folderName,qint32 fileSize);
    void ZAddData(QString filePath,QString folderName,qint32 readPos,qint32 readSize,qint32 totalBlock,qint32 currentBlock);
    bool ZGetBlockData();
    qint32 ZGetTotalBlock();
    qint32 ZGetCurrentBlock();

    void ZDelFile(QString fileName,QString folderName);
    void ZGetFile(QString fileName,QString folderName);
    void ZGetData(QString fileName,QString folderName,qint32 totalBlock,qint32 currentBlock,qint32 readPos,qint32 readSize);

    FileFrameType m_frmType;
private:
    QString m_filePath;
    QString m_folderName;

    qint32 m_readPos;
    qint32 m_readSize;

    qint32 m_totalBlock;
    qint32 m_currentBlock;
};

class PNetFrame_Template:public PNetFrame
{
public:
    void ZAddTemplate(QString templateName);
    void ZDelTemplate(QString templateName);
    void ZGetTemplate(QString templateName);
    void ZSaveTemplate(QString templateName,QString templateXmlData);
    void ZSaveAsTemplate(QString templateName,QString templateXmlData);
    void ZBindVarSource(QString templateName,QString varSourceName);
    void ZUnbindVarSource(QString templateName,QString varSourceName);
    void ZListTemplate();
};
class PNetFrame_VarSource:public PNetFrame
{
public:
    void ZAddVarSource(QString name);
    void ZDelVarSource(QString name);
    void ZGetVarSource(QString name);
    void ZSaveVarSource(QString name,QString varSourceXmlData);
};
class PNetFrame_Process:public PNetFrame
{
public:
    void ZAddProcess(QString processName);
    void ZDelProcess(QString processName);
    void ZGetProcess(QString processName);
    void ZSaveProcess(QString processName,qint32 stepNum,QString processXmlData);
    void ZListProcess();
};
class PNetFrame_Task:public PNetFrame
{
public:
    void ZListNewTask();
    void ZListTask(qint32 taskState);
    void ZNewTask(QString taskName,QString refTemplateName,QString refProcess,QString refStep);
    void ZOpenTask(QString taskName,QString refTemplateName);
    void ZSaveTask(QString taskName,QString refTemplateName,QString taskValueXmlData,QStringList auxList);
    void ZDelTask(QString taskName,QString refTemplateName);
    void ZSubmitTask(QString taskName,QString refTemplateName);
    void ZWithdrawTask(QString taskName,QString refTemplateName);
    void ZCheckOkayTask(QString taskName,QString refTemplateName);
    void ZCheckFailedTask(QString taskName,QString refTemplateName);
    void ZArchieveTask(QString taskName,QString refTemplateName);

    void ZFindTask(QString machineNo,QString classNo,QString orderNo,QString productNo,QString startTime,QString endTime);
};
class PNetFrame_Form:public PNetFrame
{
public:
    void ZListForm();
    void ZNewForm(QString formName);
    void ZGetForm(QString formName);
    void ZDelForm(QString formName);
    void ZSaveForm(QString formName,QString xmlData);
};
class PNetFrame_Backup:public PNetFrame
{
public:
    void ZListBackup();
    void ZDoBackup();
    void ZDoRestore(QString backupName);
    void ZDoDelete(QString backupName);
};
class MyNetQueue
{
private:
    MyNetQueue()
    {
        this->m_txFrmNum=0;
        this->m_rxFrmNum=0;
    }
    static MyNetQueue *m_pInstance;
public:
    static MyNetQueue* ZGetInstance()
    {
        if(m_pInstance==NULL)
        {
            m_pInstance=new MyNetQueue;
        }
        return m_pInstance;
    }
    qint32 ZGetRandomNumber()
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        qint32 randomNum;
        while(1)
        {
            randomNum=qrand()%4096;
            if(!m_serialNoList.contains(randomNum))
            {
                m_serialNoList.append(randomNum);
                break;
            }
        }
        return randomNum;
    }
    void ZDelRandomNumber(qint32 num)
    {
        qint32 index=m_serialNoList.indexOf(num);
        m_serialNoList.removeAt(index);
    }
public:
    QQueue<PNetFrame*> m_sendQueue;
    QMutex m_mutexSendQueue;
    QQueue<PNetFrame*> m_waitAckQueue;
    QMutex m_mutexWaitAckQueue;

    QList<qint32> m_serialNoList;
    QMap<qint32,ZBaseInfoDia*> m_waitDiaMap;
public:
    qint64 m_txFrmNum;
    qint64 m_rxFrmNum;
};
#endif // PNETFRAME_H
