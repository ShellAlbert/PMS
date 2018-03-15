#include "pmainwin.h"
#include <QDateTime>
#include "pgblpara.h"
#include "NetProtocol/pnetframe.h"
#include <QMessageBox>
#include <QXmlStreamReader>
#include <SoftInfo/zsoftinfodia.h>
#include <QPainter>
#include <QDir>
#include <QThread>
#include <SysSetup/zsyssetupdia.h>
#include <BackupManager/zbackupmanager.h>
ZHeartBeatInfoDia::ZHeartBeatInfoDia(QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Auto_Close,parent)
{

}
void ZHeartBeatInfoDia::ZExecuteHeartBeatOp()
{
    PNetFrame_Login *netFrm=new PNetFrame_Login;
    netFrm->ZHeartBeat(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    this->m_waitDia->ZSetTipsMsg(tr("发送心跳包"));
    this->m_netFrmQueue.enqueue(netFrm);

    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
}
void ZHeartBeatInfoDia::ZParseAckNetFrmXmlData()
{
    //qDebug()<<"ZHeartBeatInfoDia::ParseAckNetFrm:"<<this->m_ackNetFrmXmlData;
    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
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
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString nWaitCheck=attr.value(QString("waitCheck")).toString();
                    QString nSubmit=attr.value(QString("submit")).toString();
                    QString nCheckFailed=attr.value(QString("checkFailed")).toString();
                    QString newVersion=attr.value(QString("newVersion")).toString();
                    QString totalBlock=attr.value(QString("totalBlock")).toString();
                    QString blockSize=attr.value(QString("blockSize")).toString();
                    QString remainBytes=attr.value(QString("remainBytes")).toString();
                    QString userName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(userName);
                    paraList.append(nWaitCheck);
                    paraList.append(nSubmit);
                    paraList.append(nCheckFailed);
                    paraList.append(newVersion);
                    paraList.append(totalBlock);
                    paraList.append(blockSize);
                    paraList.append(remainBytes);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("heart","beat",paraList,retCode);
                }//beat.
            }//Heart.
        }//StarElement.
    }//while().
}
ZMdiArea::ZMdiArea(QWidget *parent):QMdiArea(parent)
{

}
void ZMdiArea::paintEvent(QPaintEvent *event)
{
    QMdiArea::paintEvent(event);
    QWidget *widget=this->viewport();
    QPainter painter(widget);
    // Calculate the logo position - the bottom right corner of the mdi area.
    QPixmap pixmap(":/background/images/background/background_main.png");
    painter.drawPixmap(QRect(0,0,widget->width(),widget->height()),pixmap);
}
ZShowUserInfoDia::ZShowUserInfoDia(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("用户信息"));
    this->m_llUserName=new QLabel(tr("用户名:"));
    this->m_leUserName=new QLineEdit;
    this->m_leUserName->setEnabled(false);
    this->m_leUserName->setText(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);

    this->m_llRealName=new QLabel(tr("真实姓名:"));
    this->m_leRealName=new QLineEdit;
    this->m_leRealName->setEnabled(false);
    this->m_leRealName->setText(MyUserInfo::ZGetInstance()->m_UserInfo.m_realName);

    this->m_llSex=new QLabel(tr("性别:"));
    this->m_leSex=new QLineEdit;
    this->m_leSex->setEnabled(false);
    this->m_leSex->setText(MyUserInfo::ZGetInstance()->m_UserInfo.m_sex);

    this->m_llRoleName=new QLabel(tr("所属角色:"));
    this->m_leRoleName=new QLineEdit;
    this->m_leRoleName->setEnabled(false);
    this->m_leRoleName->setText(MyUserInfo::ZGetInstance()->m_UserInfo.m_roleName);


    this->m_llCreator=new QLabel(tr("创建者:"));
    this->m_leCreator=new QLineEdit;
    this->m_leCreator->setEnabled(false);
    this->m_leCreator->setText(MyUserInfo::ZGetInstance()->m_UserInfo.m_Creator);

    this->m_llCreateTime=new QLabel(tr("创建时间:"));
    this->m_leCreateTime=new QLineEdit;
    this->m_leCreateTime->setEnabled(false);
    this->m_leCreateTime->setText(MyUserInfo::ZGetInstance()->m_UserInfo.m_CreateTime);

    this->m_tbClose=new QToolButton;
    this->m_tbClose->setText(tr("Close"));
    connect(this->m_tbClose,SIGNAL(clicked(bool)),this,SLOT(accept()));

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llUserName,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leUserName,0,1,1,1);

    this->m_gridLayout->addWidget(this->m_llRealName,0,2,1,1);
    this->m_gridLayout->addWidget(this->m_leRealName,0,3,1,1);

    this->m_gridLayout->addWidget(this->m_llSex,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_leSex,1,1,1,1);

    this->m_gridLayout->addWidget(this->m_llRoleName,1,2,1,1);
    this->m_gridLayout->addWidget(this->m_leRoleName,1,3,1,1);

    this->m_gridLayout->addWidget(this->m_llCreator,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_leCreator,2,1,1,1);

    this->m_gridLayout->addWidget(this->m_llCreateTime,2,2,1,1);
    this->m_gridLayout->addWidget(this->m_leCreateTime,2,3,1,1);

    this->m_gridLayout->addWidget(this->m_tbClose,3,3,1,1);
    this->setLayout(this->m_gridLayout);

}
ZShowUserInfoDia::~ZShowUserInfoDia()
{
    delete this->m_llUserName;
    delete this->m_leUserName;

    delete this->m_llRealName;
    delete this->m_leRealName;

    delete this->m_llSex;
    delete this->m_leSex;

    delete this->m_llRoleName;
    delete this->m_leRoleName;

    delete this->m_llCreator;
    delete this->m_leCreator;

    delete this->m_llCreateTime;
    delete this->m_leCreateTime;

    delete this->m_tbClose;

    delete this->m_gridLayout;
}

ZTaskInfoWidget::ZTaskInfoWidget(QWidget *parent):QFrame(parent)
{
    this->m_llNeedCheckByMeTask=new QLabel(tr("等待被审核:"));
    this->m_llNeedCheckByMeTaskNum=new QLabel(tr("0"));
    //this->m_llSaveTaskNum->setStyleSheet("QLabel{background-color:green;color:white;font-weight:bold;padding:2px 10px 2px 10px;}");

    this->m_llSubmitTask=new QLabel(tr("已提交审核:"));
    this->m_llSubmitTaskNum=new QLabel(tr("0"));
    //this->m_llSubmitTaskNum->setStyleSheet("QLabel{background-color:yellow;color:blue;font-weight:bold;padding:2px 10px 2px 10px;}");

    this->m_llCheckFail=new QLabel(tr("审核被驳回:"));
    this->m_llCheckFailNum=new QLabel(tr("0"));
    //this->m_llCheckFailNum->setStyleSheet("QLabel{background-color:red;color:black;font-weight:bold;padding:2px 10px 2px 10px;}");

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llNeedCheckByMeTask,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_llNeedCheckByMeTaskNum,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_llSubmitTask,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_llSubmitTaskNum,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_llCheckFail,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_llCheckFailNum,2,1,1,1);
    this->setLayout(this->m_gridLayout);

    this->m_bCheckFailedFlag=false;
    this->m_bNotSubmitFlag=false;
    this->m_bSubmitFlag=false;
    this->m_nCheckFailedNum=0;
    this->m_nNotSubmitNum=0;
    this->m_nSubmitNum=0;
    this->ZSetHighContrast(false,false,false);
    this->m_flashTimer=new QTimer;
    connect(this->m_flashTimer,SIGNAL(timeout()),this,SLOT(ZSlotTimerFlush()));
}
ZTaskInfoWidget::~ZTaskInfoWidget()
{
    delete this->m_flashTimer;
    delete this->m_llNeedCheckByMeTask;
    delete this->m_llNeedCheckByMeTaskNum;
    delete this->m_llSubmitTask;
    delete this->m_llSubmitTaskNum;
    delete this->m_llCheckFail;
    delete this->m_llCheckFailNum;
    delete this->m_gridLayout;
}
void ZTaskInfoWidget::ZSetWaitCheckTaskNum(qint32 num)
{
    this->m_llNeedCheckByMeTaskNum->setText(QString("%1").arg(num));
    this->m_nNotSubmitNum=num;
    if(num>0)
    {
        this->m_flashTimer->start(1000);
    }
}
void ZTaskInfoWidget::ZSetSubmitTaskNum(qint32 num)
{
    this->m_llSubmitTaskNum->setText(QString("%1").arg(num));
    this->m_nSubmitNum=num;
    if(num>0)
    {
        this->m_flashTimer->start(1000);
    }
}
void ZTaskInfoWidget::ZSetCheckFailedNum(qint32 num)
{
    this->m_llCheckFailNum->setText(QString("%1").arg(num));
    this->m_nCheckFailedNum=num;
    if(num>0)
    {
        this->m_flashTimer->start(1000);
    }
}
void ZTaskInfoWidget::ZSetHighContrast(bool on1,bool on2,bool on3)
{
    if(on1)
    {
        this->m_llNeedCheckByMeTaskNum->setStyleSheet("QLabel{background-color:green;color:white;font-weight:bold;padding:2px 10px 2px 10px;}");
    }else{
        this->m_llNeedCheckByMeTaskNum->setStyleSheet("QLabel{background-color:transparent;color:black;font-weight:bold;padding:2px 10px 2px 10px;}");
    }
    if(on2)
    {
        this->m_llSubmitTaskNum->setStyleSheet("QLabel{background-color:yellow;color:blue;font-weight:bold;padding:2px 10px 2px 10px;}");
    }else{
        this->m_llSubmitTaskNum->setStyleSheet("QLabel{background-color:transparent;color:black;font-weight:bold;padding:2px 10px 2px 10px;}");
    }
    if(on3)
    {
        this->m_llCheckFailNum->setStyleSheet("QLabel{background-color:red;color:gray;font-weight:bold;padding:2px 10px 2px 10px;}");
    }else{
        this->m_llCheckFailNum->setStyleSheet("QLabel{background-color:transparent;color:black;font-weight:bold;padding:2px 10px 2px 10px;}");
    }
}
void ZTaskInfoWidget::ZSlotTimerFlush()
{
    if(this->m_nNotSubmitNum)
    {
        this->m_bNotSubmitFlag=!this->m_bNotSubmitFlag;
    }else{
        this->m_bNotSubmitFlag=false;
    }
    if(this->m_nSubmitNum)
    {
        this->m_bSubmitFlag=!this->m_bSubmitFlag;
    }else{
        this->m_bSubmitFlag=false;
    }
    if(this->m_nCheckFailedNum)
    {
        this->m_bCheckFailedFlag=!this->m_bCheckFailedFlag;
    }else{
        this->m_bCheckFailedFlag=false;
    }
    this->ZSetHighContrast(this->m_bNotSubmitFlag,this->m_bSubmitFlag,this->m_bCheckFailedFlag);
    if(!this->m_nNotSubmitNum && this->m_nSubmitNum && this->m_nCheckFailedNum)
    {
        this->m_flashTimer->stop();
    }
}

ZUpdateNotifyDialog::ZUpdateNotifyDialog(QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setWindowTitle(tr("自动升级检测"));
    this->setMinimumSize(300,150);


    this->m_cbNeverNotify=new QCheckBox;
    this->m_cbNeverNotify->setText(tr("不再提醒"));

    this->m_llIcon=new QLabel;
    this->m_llIcon->setPixmap(QPixmap(":/TaskBar/images/Update.png"));
    this->m_llMsg=new QLabel;
    this->m_btnOkay=new QToolButton;
    this->m_btnOkay->setText(tr("升级"));
    this->m_btnCancel=new QToolButton;
    this->m_btnCancel->setText(tr("取消"));

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llIcon,0,0,3,1);
    this->m_gridLayout->addWidget(this->m_llMsg,0,1,1,2);
    this->m_gridLayout->addWidget(this->m_cbNeverNotify,1,1,1,2);
    this->m_gridLayout->addWidget(this->m_btnOkay,2,1,1,1);
    this->m_gridLayout->addWidget(this->m_btnCancel,2,2,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_btnOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_btnCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
}
ZUpdateNotifyDialog::~ZUpdateNotifyDialog()
{
    delete this->m_llIcon;
    delete this->m_llMsg;
    delete this->m_btnOkay;
    delete this->m_btnCancel;
    delete this->m_cbNeverNotify;
    delete this->m_gridLayout;
}
void ZUpdateNotifyDialog::ZParseAckNetFrmXmlData()
{
    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Update"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="get")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString totalBlock=attr.value(QString("totalBlock")).toString();
                    QString currentBlock=attr.value(QString("currentBlock")).toString();
                    QString data=attr.value(QString("data")).toString();
                    QString fileName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(fileName);
                    paraList.append(totalBlock);
                    paraList.append(currentBlock);
                    paraList.append(data);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("update","get",paraList,retCode);
                }
            }//Update.
        }//StarElement.
    }//while().
}
void ZUpdateNotifyDialog::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{
    if(item=="update")
    {
        if(cmd=="get")
        {
            QString fileName=paraList.at(0);
            qint32 totalBlock=paraList.at(1).toInt();
            qint32 currentBlock=paraList.at(2).toInt();
            QString data=paraList.at(3);
            QString filePath=QDir::homePath()+"/"+fileName;
            QFile file(filePath);
            if(file.open(QIODevice::WriteOnly|QIODevice::Append))
            {
                QByteArray fileDataArray=QByteArray::fromBase64(data.toUtf8());
                qDebug()<<"recv file data:"<<fileDataArray.size();
                qDebug()<<filePath;
                file.write(fileDataArray);
                file.flush();
                file.close();
            }
            if(currentBlock==totalBlock)
            {
                if(QProcess::startDetached(filePath))
                {
                    qApp->quit();
                }
            }
        }
    }
}
void ZUpdateNotifyDialog::ZSetMsg(QString msg)
{
    this->m_llMsg->setText(msg);
}
void ZUpdateNotifyDialog::ZSetUpdateInfo(qint32 totalBlock,qint32 blockSize,qint32 remainBytes)
{
    this->m_totalBlock=totalBlock;
    this->m_blockSize=blockSize;
    this->m_remainBytes=remainBytes;
}
void ZUpdateNotifyDialog::ZSlotOkay()
{
    qDebug()<<this->m_totalBlock<<this->m_blockSize<<this->m_remainBytes;
    if(this->m_totalBlock<=0 && this->m_blockSize<=0 &&this->m_remainBytes<=0)
    {
        QMessageBox::critical(this,tr("升级错误"),tr("获取新版本文件信息出错!\n请检查服务器上的新版本文件是否完整!"));
        this->reject();
    }
    QFile::remove(QDir::homePath()+"/PMSManager.exe");
    this->ZSetAckNetFrmProcessWidget(this);
    this->ZGetNewVersion(this->m_totalBlock,this->m_blockSize,this->m_remainBytes);
    this->ZShowWaitingDialog();
}
void ZUpdateNotifyDialog::ZSlotCancel()
{
    if(this->m_cbNeverNotify->isChecked())
    {
        MyUserInfo::ZGetInstance()->m_bCheckNewVersion=false;
    }
    this->reject();
}
void ZUpdateNotifyDialog::ZGetNewVersion(qint32 totalBlock,qint32 blockSize,qint32 remainBytes)
{
    this->m_waitDia->ZSetTipsMsg(tr("正在下载新版本文件..."));
    for(qint32 i=0;i<totalBlock;i++)
    {
        PNetFrame_Update *netFrm=new PNetFrame_Update;
        if(remainBytes>0)
        {
            netFrm->ZGetNewVersionData(totalBlock+1,i+1,i*blockSize,blockSize);
        }else{
            netFrm->ZGetNewVersionData(totalBlock,i+1,i*blockSize,blockSize);
        }
        this->m_netFrmQueue.enqueue(netFrm);
        if(i==0)
        {
            MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
        }
    }
    if(remainBytes>0)
    {
        PNetFrame_Update *netFrm=new PNetFrame_Update;
        netFrm->ZGetNewVersionData(totalBlock+1,totalBlock+1,totalBlock*blockSize,remainBytes);
        this->m_netFrmQueue.enqueue(netFrm);
        if(totalBlock==0)
        {
            MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
        }
    }
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
}
PMainWin::PMainWin(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle(tr("BePMS流水线综合管控系统-V%1").arg(MyUserInfo::ZGetInstance()->m_appVersion));
    this->setWindowIcon(QIcon(":/TaskBar/images/PMS.png"));
    this->m_taskBarWidget=new QFrame;
    this->m_taskBarWidget->setStyleSheet("QFrame{background-color:#cce5f9;}"
                                         "QToolButton{background-color:#cce5f9;border:none;font:color #eaf7ff;}"
                                         "QToolButton::hover{background-color:#eaf7ff;}"
                                         "QLabel{color:#386487;}"
                                         "");
    this->m_centerWidget=new QFrame;
    this->m_centerWidget->setStyleSheet("QFrame{background-color:#eaf7ff;}");

    this->m_statusBarWidget=new QFrame;
    this->m_statusBarWidget->setStyleSheet("QFrame{background-color:#cce5f9;}"
                                           "QLabel{color:#386487;}"
                                           "");
    //task bar.
//    this->m_lblLogo=new QLabel;
//    this->m_lblLogo->setPixmap(QPixmap(":/TaskBar/images/PMS.png").scaled(TOPBAR_ICON_W*2,TOPBAR_ICON_H));
    this->m_btnUserManager=new QToolButton;
    this->m_btnUserManager->setText(tr("用户管理"));
    this->m_btnUserManager->setIcon(QIcon(":/TaskBar/images/UserManager.png"));
    this->m_btnUserManager->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnUserManager->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_btnTemplateEditor=new QToolButton;
    this->m_btnTemplateEditor->setText(tr("模板设计"));
    this->m_btnTemplateEditor->setIcon(QIcon(":/TaskBar/images/TemplateEditor.png"));
    this->m_btnTemplateEditor->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnTemplateEditor->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_btnFileManager=new QToolButton;
    this->m_btnFileManager->setText(tr("工艺文件"));
    this->m_btnFileManager->setIcon(QIcon(":/TaskBar/images/FileManager.png"));
    this->m_btnFileManager->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnFileManager->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_btnProcessEditor=new QToolButton;
    this->m_btnProcessEditor->setText(tr("工序编辑"));
    this->m_btnProcessEditor->setIcon(QIcon(":/TaskBar/images/ProcessEditor.png"));
    this->m_btnProcessEditor->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnProcessEditor->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_btnTaskManager=new QToolButton;
    this->m_btnTaskManager->setText(tr("任务管理"));
    this->m_btnTaskManager->setIcon(QIcon(":/TaskBar/images/TaskManager.png"));
    this->m_btnTaskManager->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnTaskManager->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_btnReportDesigner=new QToolButton;
    this->m_btnReportDesigner->setText(tr("报表生成"));
    this->m_btnReportDesigner->setIcon(QIcon(":/TaskBar/images/ReportDesigner.png"));
    this->m_btnReportDesigner->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnReportDesigner->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_btnSysLog=new QToolButton;
    this->m_btnSysLog->setText(tr("系统日志"));
    this->m_btnSysLog->setIcon(QIcon(":/TaskBar/images/SysLog.png"));
    this->m_btnSysLog->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnSysLog->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_btnSysSetup=new QToolButton;
    this->m_btnSysSetup->setText(tr("系统设置"));
    this->m_btnSysSetup->setIcon(QIcon(":/TaskBar/images/SystemSetup.png"));
    this->m_btnSysSetup->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnSysSetup->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_btnDataBackup=new QToolButton;
    this->m_btnDataBackup->setText(tr("备份还原"));
    this->m_btnDataBackup->setIcon(QIcon(":/TaskBar/images/BackupRestore.png"));
    this->m_btnDataBackup->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnDataBackup->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_btnUpgrade=new QToolButton;
    this->m_btnUpgrade->setText(tr("远程升级"));
    this->m_btnUpgrade->setIcon(QIcon(":/TaskBar/images/Upgrade.png"));
    this->m_btnUpgrade->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnUpgrade->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_btnSoftInfo=new QToolButton;
    this->m_btnSoftInfo->setText(tr("软件信息"));
    this->m_btnSoftInfo->setIcon(QIcon(":/TaskBar/images/SoftInfo.png"));
    this->m_btnSoftInfo->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnSoftInfo->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    this->m_taskInfo=new ZTaskInfoWidget;

    this->m_btnUserInfo=new QToolButton;
    this->m_btnUserInfo->setText(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    if(MyUserInfo::ZGetInstance()->m_UserInfo.m_sex==QString("male"))
    {
        this->m_btnUserInfo->setIcon(QIcon(":/TaskBar/images/Male.png"));
    }else{
        this->m_btnUserInfo->setIcon(QIcon(":/TaskBar/images/Female.png"));
    }
    this->m_btnUserInfo->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnUserInfo->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    this->m_btnLockScreen=new QToolButton;
    this->m_btnLockScreen->setText(tr("锁定屏幕"));
    this->m_btnLockScreen->setIcon(QIcon(":/TaskBar/images/Logout.png"));
    this->m_btnLockScreen->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnLockScreen->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    this->m_btnExitSys=new QToolButton;
    this->m_btnExitSys->setText(tr("退出系统"));
    this->m_btnExitSys->setIcon(QIcon(":/TaskBar/images/ExitSys.png"));
    this->m_btnExitSys->setIconSize(QSize(TOPBAR_ICON_W,TOPBAR_ICON_H));
    this->m_btnExitSys->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->m_hLayoutTaskBar=new QHBoxLayout;
//    this->m_hLayoutTaskBar->addWidget(this->m_lblLogo);
    this->m_hLayoutTaskBar->addWidget(this->m_btnUserManager);
    this->m_hLayoutTaskBar->addWidget(this->m_btnTemplateEditor);
    this->m_hLayoutTaskBar->addWidget(this->m_btnFileManager);
    this->m_hLayoutTaskBar->addWidget(this->m_btnProcessEditor);
    this->m_hLayoutTaskBar->addWidget(this->m_btnTaskManager);
    this->m_hLayoutTaskBar->addWidget(this->m_btnReportDesigner);
    this->m_hLayoutTaskBar->addWidget(this->m_btnSysLog);
    this->m_hLayoutTaskBar->addWidget(this->m_btnSysSetup);
    this->m_hLayoutTaskBar->addWidget(this->m_btnDataBackup);
    this->m_hLayoutTaskBar->addWidget(this->m_btnUpgrade);
    this->m_hLayoutTaskBar->addWidget(this->m_btnSoftInfo);
    this->m_hLayoutTaskBar->addStretch(1);
    this->m_hLayoutTaskBar->addWidget(this->m_btnUserInfo);
    this->m_hLayoutTaskBar->addWidget(this->m_btnLockScreen);
    this->m_hLayoutTaskBar->addWidget(this->m_btnExitSys);
    this->m_hLayoutTaskBar->addWidget(this->m_taskInfo);
    this->m_hLayoutTaskBar->setMargin(0);
    this->m_hLayoutTaskBar->setSpacing(6);
    this->m_taskBarWidget->setLayout(this->m_hLayoutTaskBar);
    //center.
    this->m_spliter=new QSplitter(Qt::Vertical);
    this->m_midArea=new ZMdiArea(this->m_spliter);
    this->m_logManager=new ZLogManager(this->m_spliter);
    this->m_spliter->setStretchFactor(0,8);
    this->m_spliter->setStretchFactor(1,2);
    this->m_userManager=NULL;
    this->m_templateEditor=NULL;
    this->m_fileManager=NULL;
    this->m_processEdit=NULL;
    this->m_taskManager=NULL;
    this->m_formDesigner=NULL;

    //status bar.
    this->m_lblTime=new QLabel;
    this->m_hLayoutStatusBar=new QHBoxLayout;
    this->m_hLayoutStatusBar->addWidget(this->m_lblTime);
    this->m_hLayoutStatusBar->setMargin(0);
    this->m_statusBarWidget->setLayout(this->m_hLayoutStatusBar);
    this->m_runCounter=0;
    this->ZFuncRefreshStatusBar();

    this->m_1sTimer=new QTimer;
    connect(this->m_1sTimer,SIGNAL(timeout()),this,SLOT(ZSlotUpdateStatusBarTime()));
    this->m_1sTimer->start(1000);
    //main.
    this->m_vLayoutMain=new QVBoxLayout;
    this->m_vLayoutMain->setSpacing(0);
    this->m_vLayoutMain->setMargin(0);
    this->m_vLayoutMain->addWidget(this->m_taskBarWidget);
    this->m_vLayoutMain->addWidget(this->m_spliter);
    this->m_vLayoutMain->addWidget(this->m_statusBarWidget);
    this->setLayout(this->m_vLayoutMain);

    connect(this->m_btnUserManager,SIGNAL(clicked(bool)),this,SLOT(ZSlotShowUserManager()));
    connect(this->m_btnTemplateEditor,SIGNAL(clicked(bool)),this,SLOT(ZSlotShowTemplateEditor()));
    connect(this->m_btnFileManager,SIGNAL(clicked(bool)),this,SLOT(ZSlotShowFileManager()));
    connect(this->m_btnProcessEditor,SIGNAL(clicked(bool)),this,SLOT(ZSlotShowProcessEditor()));
    connect(this->m_btnTaskManager,SIGNAL(clicked(bool)),this,SLOT(ZSlotShowTaskManager()));
    connect(this->m_btnReportDesigner,SIGNAL(clicked(bool)),this,SLOT(ZSlotShowFormDesigner()));
    connect(this->m_btnSysLog,SIGNAL(clicked(bool)),this,SLOT(ZSlotShowSystemLog()));
    connect(this->m_btnSysSetup,SIGNAL(clicked(bool)),this,SLOT(ZSlotShowSystemSetup()));
    connect(this->m_btnDataBackup,SIGNAL(clicked(bool)),this,SLOT(ZSlotShowDataBackup()));
    connect(this->m_btnSoftInfo,SIGNAL(clicked(bool)),this,SLOT(ZSlotShowSoftInfo()));

    connect(this->m_btnUserInfo,SIGNAL(clicked(bool)),this,SLOT(ZSlotShowUserInfo()));
    connect(this->m_btnLockScreen,SIGNAL(clicked(bool)),this,SLOT(ZSlotLockScreen()));
    connect(this->m_btnExitSys,SIGNAL(clicked(bool)),this,SLOT(ZSlotExitSys()));

    this->m_updateNotifyDia=new ZUpdateNotifyDialog(this);

    this->m_timerHeartBeat=new QTimer;
    connect(this->m_timerHeartBeat,SIGNAL(timeout()),this,SLOT(ZSlotHearBeat()));
    this->m_timerHeartBeat->start(1000*6);
}

PMainWin::~PMainWin()
{
    //taskbar.
    delete this->m_lblLogo;
    delete this->m_btnUserManager;
    delete this->m_btnTemplateEditor;
    delete this->m_btnFileManager;
    delete this->m_btnProcessEditor;
    delete this->m_btnTaskManager;
    delete this->m_btnReportDesigner;
    delete this->m_btnSysLog;
    delete this->m_btnSysSetup;
    delete this->m_btnDataBackup;
    delete this->m_btnUpgrade;
    delete this->m_btnSoftInfo;
    delete this->m_taskInfo;
    delete this->m_btnUserInfo;
    delete this->m_btnLockScreen;
    delete this->m_btnExitSys;
    delete this->m_hLayoutTaskBar;
    //center.
    if(this->m_userManager)
    {
        delete this->m_userManager;
    }
    if(this->m_templateEditor)
    {
        delete this->m_templateEditor;
    }
    if(this->m_fileManager)
    {
        delete this->m_fileManager;
    }
    if(this->m_processEdit)
    {
        delete this->m_processEdit;
    }
    if(this->m_taskManager)
    {
        delete this->m_taskManager;
    }
    if(this->m_formDesigner)
    {
        delete this->m_formDesigner;
    }
    delete this->m_midArea;
    delete this->m_logManager;
    delete this->m_spliter;
    //status bar.
    delete this->m_1sTimer;
    delete this->m_lblTime;
    delete this->m_hLayoutStatusBar;
    //main.
    delete this->m_taskBarWidget;
    delete this->m_centerWidget;
    delete this->m_statusBarWidget;
    delete this->m_vLayoutMain;

    delete this->m_timerHeartBeat;
    delete this->m_updateNotifyDia;
}
QSize PMainWin::sizeHint() const
{
    return QSize(800,600);
}
void PMainWin::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{
    if(item=="heart")
    {
        if(cmd=="beat")
        {
            QString userName=paraList.at(0);
            qint32 nWaitCheck=paraList.at(1).toInt();
            qint32 nSubmit=paraList.at(2).toInt();
            qint32 nCheckFailed=paraList.at(3).toInt();
            QString newVersion=paraList.at(4);
            qint32 totalBlock=paraList.at(5).toInt();
            qint32 blockSize=paraList.at(6).toInt();
            qint32 remainBytes=paraList.at(7).toInt();
            if(ackNetRetCode<0)
            {
                qDebug()<<"heart beat failed!";
            }else{
                //qDebug()<<"heart beat okay!";
                this->m_taskInfo->ZSetWaitCheckTaskNum(nWaitCheck);
                this->m_taskInfo->ZSetSubmitTaskNum(nSubmit);
                this->m_taskInfo->ZSetCheckFailedNum(nCheckFailed);
                if(MyUserInfo::ZGetInstance()->m_bCheckNewVersion)
                {
                    if(this->isVisible() && !this->m_updateNotifyDia->isVisible())
                    {
                        this->m_updateNotifyDia->ZSetMsg(tr("PMS检测到新版本:V%1.\n是否需要进行升级操作?\n当前版本:V%2.").arg(newVersion).arg(MyUserInfo::ZGetInstance()->m_appVersion));
                        this->m_updateNotifyDia->ZSetUpdateInfo(totalBlock,blockSize,remainBytes);
                        this->m_updateNotifyDia->exec();
                    }
                }
            }
        }
    }
}
void PMainWin::ZSlotCloseWaitingDialog(qint32 netFrmSerialNo,qint32 retCode)
{
    if(!MyNetQueue::ZGetInstance()->m_waitDiaMap.contains(netFrmSerialNo))
    {
        return;
    }
    ZBaseInfoDia *dia=MyNetQueue::ZGetInstance()->m_waitDiaMap.value(netFrmSerialNo);
    MyNetQueue::ZGetInstance()->m_waitDiaMap.remove(netFrmSerialNo);
    MyNetQueue::ZGetInstance()->m_serialNoList.removeAt(MyNetQueue::ZGetInstance()->m_serialNoList.indexOf(netFrmSerialNo));
    dia->ZParseAckNetFrmXmlData();

    if(dia->m_netFrmQueue.count()>0)
    {
        //continue to post another netFrm.
        PNetFrame *netFrm=dia->m_netFrmQueue.dequeue();
        PNetFrame_File *netFrmFile=dynamic_cast<PNetFrame_File*>(netFrm);
        if(netFrmFile)
        {
            if(netFrmFile->m_frmType==PNetFrame_File::Type_Add_Data)
            {
                qDebug()<<"post next block data";
                netFrmFile->ZGetBlockData();
                dia->m_waitDia->ZSetTipsMsg(tr("正在上传文件块[%1-%2]...").arg(netFrmFile->ZGetTotalBlock()).arg(netFrmFile->ZGetCurrentBlock()));
            }
        }
        MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
        MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(netFrm);
        MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
        MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),dia);
        return;
    }else{
        //all netFrm had been sent out.
        if(retCode<0)
        {
            if(dia->ZGetDialogType()==ZBaseInfoDia::Dialog_End_By_Calling_Close)
            {
                dia->ZHideAllDialog();
                //QMessageBox::critical(this,tr("错误提示"),tr("请求超时!\n请检查网络连接!"));
                if(dia->ZShowWorkingDialog()<0)
                {
                    dia->close(); //user cancelled operation.
                    delete dia;
                    dia=NULL;
                }
            }else if(dia->ZGetDialogType()==ZBaseInfoDia::Dialog_End_By_Emitting_Signal){
                //should not auto close. LoginDialog.
                dia->ZEmitOpFinishedSignal(-1);
            }else if(dia->ZGetDialogType()==ZBaseInfoDia::Dialog_End_By_Auto_Close)
            {
                //auto close.  HeartBeat.
                dia->close();
                delete dia;
                dia=NULL;
            }
        }else{ //retCode=0,success.
            if(dia->ZGetDialogType()==ZBaseInfoDia::Dialog_End_By_Calling_Close)
            {
                dia->close();
                delete dia;
                dia=NULL;
            }else if(dia->ZGetDialogType()==ZBaseInfoDia::Dialog_End_By_Emitting_Signal){
                //should not auto close. LoginDialog.
                dia->ZEmitOpFinishedSignal(0);
            }else if(dia->ZGetDialogType()==ZBaseInfoDia::Dialog_End_By_Auto_Close)
            {
                //auto close. HeartBeat.
                dia->close();
                delete dia;
                dia=NULL;
            }
        }
    }
}
void PMainWin::ZSlotShowTaskBar(bool bShow)
{
    this->m_taskBarWidget->setVisible(bShow);
}
void PMainWin::ZSlotShowLogBar(bool bShow)
{
    this->m_statusBarWidget->setVisible(bShow);
}
void PMainWin::ZSlotLatchModule(qint32 moduleNo)
{
    switch(moduleNo)
    {
    case 1:
        this->ZSlotShowUserManager();
        break;
    case 2:
        this->ZSlotShowTemplateEditor();
        break;
    case 3:
        this->ZSlotShowFileManager();
        break;
    case 4:
        this->ZSlotShowProcessEditor();
        break;
    case 5:
        this->ZSlotShowTaskManager();
        break;
    case 6:
        this->ZSlotShowFormDesigner();
        break;
    default:
        break;
    }
}
void PMainWin::ZSlotUpdateStatusBarTime()
{
    this->m_runCounter++;
    this->ZFuncRefreshStatusBar();
}
void PMainWin::ZFuncRefreshStatusBar()
{
    //seoncds to x days x hours x minutes x seconds.
    qint32 tAllSecs,tDays,tHours,tMins,tSecs;
    tAllSecs=this->m_runCounter;
    tDays=tAllSecs/86400; //60*60*24.
    tAllSecs=tAllSecs%86400;

    tHours=tAllSecs/3600;//60*60.
    tAllSecs=tAllSecs%3600;

    tMins=tAllSecs/60; //60.
    tAllSecs=tAllSecs%60;

    tSecs=tAllSecs;//1.

    QString tDisplayStr;
    tDisplayStr.append(tr("欢迎使用PMS流水线综合管控系统 V%1").arg(MyUserInfo::ZGetInstance()->m_appVersion));
    tDisplayStr.append(" | ");
    tDisplayStr.append(tr("版权所有 柘园生物"));
    tDisplayStr.append(" | ");
    tDisplayStr.append(tr("当前用户:[%1]").arg(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName));
    tDisplayStr.append(" | ");
    tDisplayStr.append(tr("服务器:[%1]").arg(MyUserInfo::ZGetInstance()->m_onLine));
    tDisplayStr.append(" | ");
    tDisplayStr.append(tr("Tx:%1,Rx:%2").arg(MyNetQueue::ZGetInstance()->m_txFrmNum).arg(MyNetQueue::ZGetInstance()->m_rxFrmNum));
    tDisplayStr.append(" | ");
    tDisplayStr.append(tr("已运行:")+QString("%1天%2时%3分%4秒").arg(tDays).arg(tHours).arg(tMins).arg(tSecs));
    tDisplayStr.append(" | ");
    tDisplayStr.append(tr("当前时间:")+QDateTime::currentDateTime().toString("yyyy年MM月dd日hh时mm分ss秒"));
    this->m_lblTime->setText(tDisplayStr);
}
void PMainWin::ZSlotShowUserManager()
{
    if(!MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("您无权限访问<用户管理器>功能模块!\n请联系您的创建者:[%1].").arg(MyUserInfo::ZGetInstance()->m_UserInfo.m_Creator));
        return;
    }
    if(this->m_userManager==NULL)
    {
        this->m_userManager=new PUserManagerWin;
        connect(this->m_userManager,SIGNAL(ZSignalLogMsg(QString)),this->m_logManager,SLOT(ZSlotAddLogMsg(QString)));
        connect(this->m_userManager,SIGNAL(ZSignalCloseEvent(QString)),this,SLOT(ZSlotCloseSubWidget(QString)));
        this->m_mdiUserManager=this->m_midArea->addSubWindow(this->m_userManager);
    }else{
        this->m_midArea->setActiveSubWindow(this->m_mdiUserManager);
    }
    this->m_userManager->showNormal();
}
void PMainWin::ZSlotShowTemplateEditor()
{
    if(!MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("您无权限访问<模板设计器>功能模块!\n请联系您的创建者:[%1].").arg(MyUserInfo::ZGetInstance()->m_UserInfo.m_Creator));
        return;
    }
    if(this->m_templateEditor==NULL)
    {
        this->m_templateEditor=new PTemplateEditor;
        connect(this->m_templateEditor,SIGNAL(ZSignalLogMsg(QString)),this->m_logManager,SLOT(ZSlotAddLogMsg(QString)));
        connect(this->m_templateEditor,SIGNAL(ZSignalCloseEvent(QString)),this,SLOT(ZSlotCloseSubWidget(QString)));
        this->m_mdiTemplateEditor=this->m_midArea->addSubWindow(this->m_templateEditor);
    }else{
        this->m_midArea->setActiveSubWindow(this->m_mdiTemplateEditor);
    }
    this->m_templateEditor->showNormal();
}
void PMainWin::ZSlotShowFileManager()
{
    if(!MyUserInfo::ZGetInstance()->m_RoleInfo.m_fileManagerPerm)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("您无权限访问<工艺文件管理器>功能模块!\n请联系您的创建者:[%1].").arg(MyUserInfo::ZGetInstance()->m_UserInfo.m_Creator));
        return;
    }
    if(this->m_fileManager==NULL)
    {
        this->m_fileManager=new PFileManager;
        connect(this->m_fileManager,SIGNAL(ZSignalLogMsg(QString)),this->m_logManager,SLOT(ZSlotAddLogMsg(QString)));
        connect(this->m_fileManager,SIGNAL(ZSignalCloseEvent(QString)),this,SLOT(ZSlotCloseSubWidget(QString)));
        this->m_mdiFileManager=this->m_midArea->addSubWindow(this->m_fileManager);
    }else{
        this->m_midArea->setActiveSubWindow(this->m_mdiFileManager);
    }
    this->m_fileManager->showNormal();
}
void PMainWin::ZSlotShowProcessEditor()
{
    if(!MyUserInfo::ZGetInstance()->m_RoleInfo.m_processEditPerm)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("您无权限访问<工序编辑器>功能模块!\n请联系您的创建者:[%1].").arg(MyUserInfo::ZGetInstance()->m_UserInfo.m_Creator));
        return;
    }
    if(this->m_processEdit==NULL)
    {
        this->m_processEdit=new PProcessEditor;
        connect(this->m_processEdit,SIGNAL(ZSignalLogMsg(QString)),this->m_logManager,SLOT(ZSlotAddLogMsg(QString)));
        connect(this->m_processEdit,SIGNAL(ZSignalCloseEvent(QString)),this,SLOT(ZSlotCloseSubWidget(QString)));
        this->m_mdiProcessEdit=this->m_midArea->addSubWindow(this->m_processEdit);
    }else{
        this->m_midArea->setActiveSubWindow(this->m_mdiProcessEdit);
    }
    this->m_processEdit->showNormal();
}
void PMainWin::ZSlotShowTaskManager()
{
    if(!MyUserInfo::ZGetInstance()->m_RoleInfo.m_taskManagerPerm)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("您无权限访问<任务管理器>功能模块!\n请联系您的创建者:[%1].").arg(MyUserInfo::ZGetInstance()->m_UserInfo.m_Creator));
        return;
    }
    if(this->m_taskManager==NULL)
    {
        this->m_taskManager=new PTaskManager;
        connect(this->m_taskManager,SIGNAL(ZSignalLogMsg(QString)),this->m_logManager,SLOT(ZSlotAddLogMsg(QString)));
        connect(this->m_taskManager,SIGNAL(ZSignalCloseEvent(QString)),this,SLOT(ZSlotCloseSubWidget(QString)));
        this->m_mdiTaskManager=this->m_midArea->addSubWindow(this->m_taskManager);
    }else{
        this->m_midArea->setActiveSubWindow(this->m_mdiTaskManager);
    }
    this->m_taskManager->showNormal();
}
void PMainWin::ZSlotShowFormDesigner()
{
    if(!MyUserInfo::ZGetInstance()->m_RoleInfo.m_formDesignerPerm)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("您无权限访问<报表生成器>功能模块!\n请联系您的创建者:[%1].").arg(MyUserInfo::ZGetInstance()->m_UserInfo.m_Creator));
        return;
    }
    if(this->m_formDesigner==NULL)
    {
        this->m_formDesigner=new PFormDesigner;
        connect(this->m_formDesigner,SIGNAL(ZSignalLogMsg(QString)),this->m_logManager,SLOT(ZSlotAddLogMsg(QString)));
        connect(this->m_formDesigner,SIGNAL(ZSignalCloseEvent(QString)),this,SLOT(ZSlotCloseSubWidget(QString)));
        this->m_mdiFormDesigner=this->m_midArea->addSubWindow(this->m_formDesigner);
    }else{
        this->m_midArea->setActiveSubWindow(this->m_mdiFormDesigner);
    }
    this->m_formDesigner->showNormal();
}
void PMainWin::ZSlotShowSystemLog()
{
    if(this->m_logManager->isVisible())
    {
        this->m_logManager->setVisible(false);
    }else{
        this->m_logManager->setVisible(true);
    }
}
void PMainWin::ZSlotShowDataBackup()
{
    if(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName!="admin")
    {
        QMessageBox::critical(this,tr("错误提示"),tr("您无权限访问<备份还原>功能模块!\n只有admin用户才有权限访问该功能模块!"));
        return;
    }
    ZBackupManager dia(this);
    dia.exec();
}
void PMainWin::ZSlotShowSystemSetup()
{
    ZSysSetupDia dia(this);
    if(dia.exec()==QDialog::Accepted)
    {

    }
}
void PMainWin::ZSlotShowSoftInfo()
{
    ZSoftInfoDia dia(this);
    dia.exec();
}
void PMainWin::ZSlotShowUserInfo()
{
    ZShowUserInfoDia dia;
    dia.exec();
}
void PMainWin::ZSlotLockScreen()
{
    PLoginManager dia(this);
    dia.ZLockUserName(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    dia.exec();
}
void PMainWin::ZSlotExitSys()
{
    if(QMessageBox::question(this,tr("操作确认"),tr("您确认要退出PMS系统吗?"),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        MyUserInfo::ZGetInstance()->m_bExitFlag=true;
        qApp->exit(0);
    }
}
void PMainWin::ZSlotCloseSubWidget(QString widget)
{
    if(widget==QString("UserManager"))
    {
        delete this->m_userManager;
        this->m_userManager=NULL;
        this->m_mdiUserManager=NULL;
    }else if(widget==QString("TemplateEditor"))
    {
        delete this->m_templateEditor;
        this->m_templateEditor=NULL;
        this->m_mdiTemplateEditor=NULL;
    }else if(widget==QString("FileManager"))
    {
        delete this->m_fileManager;
        this->m_fileManager=NULL;
        this->m_mdiFileManager=NULL;
    }else if(widget==QString("ProcessEditor"))
    {
        delete this->m_processEdit;
        this->m_processEdit=NULL;
        this->m_mdiProcessEdit=NULL;
    }else if(widget==QString("TaskManager"))
    {
        delete this->m_taskManager;
        this->m_taskManager=NULL;
        this->m_mdiTaskManager=NULL;
    }else if(widget==QString("FormDesigner"))
    {
        delete this->m_formDesigner;
        this->m_formDesigner=NULL;
        this->m_mdiFormDesigner=NULL;
    }
}
void PMainWin::ZSlotHearBeat()
{
    if(MyUserInfo::ZGetInstance()->m_bOnLine)
    {
        ZHeartBeatInfoDia *dia=new ZHeartBeatInfoDia;
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZExecuteHeartBeatOp();
    }
}
void PMainWin::ZUpdateUserInfo()
{
    this->m_btnUserInfo->setText(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    if(MyUserInfo::ZGetInstance()->m_UserInfo.m_sex==QString("male"))
    {
        this->m_btnUserInfo->setIcon(QIcon(":/TaskBar/images/Male.png"));
    }else{
        this->m_btnUserInfo->setIcon(QIcon(":/TaskBar/images/Female.png"));
    }
}
PGuideWin::PGuideWin(QWidget *parent):QWidget(parent)
{
    this->setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(0);
    this->m_lblGuide=new QLabel;
    this->m_lblGuide->setStyleSheet("background:transparent");
    this->m_movie=new QMovie(":/gifs/images/gifs/guide.gif");
    this->m_lblGuide->setMovie(this->m_movie);
    this->m_movie->start();
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->setContentsMargins(0,0,0,0);
    this->m_vLayout->addWidget(this->m_lblGuide);
    this->setLayout(this->m_vLayout);

    this->m_bShowTaskBar=false;
    this->m_bShowLogBar=false;
    this->resize(64,64);



    this->m_actShowTopBar=new QAction(QIcon(":/GuideWin/images/GuideWin/Top.png"),tr("工具栏"));
    this->m_actShowTopBar->setCheckable(true);
    this->m_actShowBottomBar=new QAction(QIcon(":/GuideWin/images/GuideWin/Bottom.png"),tr("状态栏"));
    this->m_actShowBottomBar->setCheckable(true);
    connect(this->m_actShowTopBar,SIGNAL(toggled(bool)),this,SIGNAL(ZSignalShowTaskBar(bool)));
    connect(this->m_actShowBottomBar,SIGNAL(toggled(bool)),this,SIGNAL(ZSignalShowLogBar(bool)));

    this->m_actUserManager=new QAction(QIcon(":/TaskBar/images/UserManager.png"),tr("用户管理"));
    this->m_actTemplateEdit=new QAction(QIcon(":/TaskBar/images/TemplateEditor.png"),tr("模板编辑"));
    this->m_actFileManager=new QAction(QIcon(":/TaskBar/images/FileManager.png"),tr("文件管理"));
    this->m_actProcessEdit=new QAction(QIcon(":/TaskBar/images/ProcessEditor.png"),tr("工序编辑"));
    this->m_actTaskManage=new QAction(QIcon(":/TaskBar/images/TaskManager.png"),tr("任务管理"));
    this->m_actFormDesign=new QAction(QIcon(":/TaskBar/images/ReportDesigner.png"),tr("报表生成"));
    connect(this->m_actUserManager,SIGNAL(toggled(bool)),this,SLOT(ZSlotLatchModule()));
    connect(this->m_actTemplateEdit,SIGNAL(toggled(bool)),this,SLOT(ZSlotLatchModule()));
    connect(this->m_actFileManager,SIGNAL(toggled(bool)),this,SLOT(ZSlotLatchModule()));
    connect(this->m_actProcessEdit,SIGNAL(toggled(bool)),this,SLOT(ZSlotLatchModule()));
    connect(this->m_actTaskManage,SIGNAL(toggled(bool)),this,SLOT(ZSlotLatchModule()));
    connect(this->m_actFormDesign,SIGNAL(toggled(bool)),this,SLOT(ZSlotLatchModule()));

    this->m_subMenu=new QMenu(tr("功能模块"));
    this->m_subMenu->addAction(this->m_actUserManager);
    this->m_subMenu->addAction(this->m_actTemplateEdit);
    this->m_subMenu->addAction(this->m_actFileManager);
    this->m_subMenu->addAction(this->m_actProcessEdit);
    this->m_subMenu->addAction(this->m_actTaskManage);
    this->m_subMenu->addAction(this->m_actFormDesign);

    this->m_menu=new QMenu;
    this->m_menu->addAction(this->m_actShowTopBar);
    this->m_menu->addAction(this->m_actShowBottomBar);
    this->m_menu->addSeparator();
    this->m_menu->addMenu(this->m_subMenu);
}
PGuideWin::~PGuideWin()
{

    delete this->m_actUserManager;
    delete this->m_actTemplateEdit;
    delete this->m_actFileManager;
    delete this->m_actProcessEdit;
    delete this->m_actTaskManage;
    delete this->m_actFormDesign;
    delete this->m_subMenu;
    delete this->m_actShowTopBar;
    delete this->m_actShowBottomBar;
    delete this->m_menu;

    this->m_movie->stop();
    delete this->m_movie;
    delete this->m_lblGuide;
    delete this->m_vLayout;
}
void PGuideWin::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
    case Qt::LeftButton:
        this->m_relativePos=this->pos()-event->globalPos();
        break;
    case Qt::MidButton:
        break;
    case Qt::RightButton:
        break;
    default:
        break;
    }
}
void PGuideWin::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos()+this->m_relativePos);
}
void PGuideWin::contextMenuEvent(QContextMenuEvent *event)
{
    this->m_menu->exec(event->globalPos());
}
void PGuideWin::ZSlotLatchModule()
{
    QAction *sender=qobject_cast<QAction*>(this->sender());
    if(sender==this->m_actUserManager)
    {
        emit this->ZSignalLatchModule(1);
    }else if(sender==this->m_actTemplateEdit)
    {
        emit this->ZSignalLatchModule(2);
    }else if(sender==this->m_actFileManager)
    {
        emit this->ZSignalLatchModule(3);
    }else if(sender==this->m_actProcessEdit)
    {
        emit this->ZSignalLatchModule(4);
    }else if(sender==this->m_actTaskManage)
    {
        emit this->ZSignalLatchModule(5);
    }else if(sender==this->m_actFormDesign)
    {
        emit this->ZSignalLatchModule(6);
    }
}
