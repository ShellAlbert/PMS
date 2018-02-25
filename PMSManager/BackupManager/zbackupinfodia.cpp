#include "zbackupinfodia.h"
#include <QMessageBox>
#include <QXmlStreamReader>
ZBackupInfoDia::ZBackupInfoDia(BackupInfoDiaType type,QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setMinimumSize(200,100);

    this->m_llBackupName=new QLabel(tr("备份文件"));
    this->m_leBackupName=new QLineEdit;
    this->m_leBackupName->setEnabled(false);

    this->m_btnOkay=new QToolButton;
    this->m_btnOkay->setText(tr("确认"));
    this->m_btnCancel=new QToolButton;
    this->m_btnCancel->setText(tr("取消"));
    this->m_btnOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_btnOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_btnCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llBackupName,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leBackupName,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_btnOkay,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_btnCancel,1,1,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_btnOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_btnCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));

    this->m_diaType=type;
    switch(type)
    {
    case Type_Backup:
        this->setWindowTitle(tr("备份数据"));
        break;
    case Type_Restore:
        this->setWindowTitle(tr("还原数据"));
        break;
    case Type_Delete:
        this->setWindowTitle(tr("删除备份"));
        break;
    default:
        break;
    }
}
ZBackupInfoDia::~ZBackupInfoDia()
{
    delete this->m_llBackupName;
    delete this->m_leBackupName;
    delete this->m_btnOkay;
    delete this->m_btnCancel;
    delete this->m_gridLayout;
}

QString ZBackupInfoDia::ZGetBackupName()
{
    return this->m_leBackupName->text().trimmed();
}
void ZBackupInfoDia::ZSetBackupName(QString name)
{
    this->m_leBackupName->setText(name);
}

void ZBackupInfoDia::ZParseAckNetFrmXmlData()
{
    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Backup"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="backup")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString backupName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(backupName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString fileSize=attr.value(QString("fileSize")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        paraList.append(fileSize);
                        paraList.append(creator);
                        paraList.append(createTime);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("backup","backup",paraList,retCode);
                }else if(cmd=="restore")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString backupName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(backupName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{

                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("backup","restore",paraList,retCode);
                }else if(cmd=="delete")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString backupName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(backupName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{

                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("backup","delete",paraList,retCode);
                }
            }//Role.
        }//StarElement.
    }//while().
}

void ZBackupInfoDia::ZSlotOkay()
{
    if(MyUserInfo::ZGetInstance()->m_bOnLine==false)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("网络错误,未连接服务器!\n请等待连接服务器成功后再操作!"));
        return;
    }

    switch(this->m_diaType)
    {
    case Type_Backup:
        break;
    case Type_Restore:
        if(this->m_leBackupName->text().isEmpty())
        {
            QMessageBox::critical(this,tr("错误提示"),tr("无法从空文件还原!"));
            return;
        }
        break;
    case Type_Delete:
        if(this->m_leBackupName->text().isEmpty())
        {
            QMessageBox::critical(this,tr("错误提示"),tr("无法删除空的备份!"));
            return;
        }
        break;
    default:
        break;
    }

    PNetFrame_Backup *netFrm=new PNetFrame_Backup;
    switch(this->m_diaType)
    {
    case Type_Backup:
        netFrm->ZDoBackup();
        this->m_waitDia->ZSetTipsMsg(tr("正在备份数据[%1]").arg(this->ZGetBackupName()));
        break;
    case Type_Restore:
        netFrm->ZDoRestore(this->ZGetBackupName());
        this->m_waitDia->ZSetTipsMsg(tr("正在还原[%1]").arg(this->ZGetBackupName()));
        break;
    case Type_Delete:
        netFrm->ZDoDelete(this->ZGetBackupName());
        this->m_waitDia->ZSetTipsMsg(tr("正在删除备份[%1]").arg(this->ZGetBackupName()));
        break;
    default:
        break;
    }
    this->m_netFrmQueue.enqueue(netFrm);
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
    this->accept();
}
void ZBackupInfoDia::ZSlotCancel()
{
    this->reject();
}
