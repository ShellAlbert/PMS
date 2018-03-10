#include "zlistbackupinfodia.h"
#include <QXmlStreamReader>
#include <QDebug>
ZListBackupInfoDia::ZListBackupInfoDia(QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setWindowTitle(tr("获取备份数据列表"));
    this->m_llMsg=new QLabel(tr("获取备份数据列表失败!\n命令请求超时!\n请检测网络连接状态和服务器状态!"));
    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("CLOSE"));
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_llMsg);
    this->m_vLayout->addWidget(this->m_tbOkay);
    this->setLayout(this->m_vLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(reject()));
}
ZListBackupInfoDia::~ZListBackupInfoDia()
{
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_vLayout;
}
void ZListBackupInfoDia::ZExecuteListOp()
{
    PNetFrame_Backup *netFrm=new PNetFrame_Backup;
    netFrm->ZListBackup();
    this->m_waitDia->ZSetTipsMsg(tr("正在获取备份数据列表..."));
    this->m_netFrmQueue.enqueue(netFrm);


    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
}
void ZListBackupInfoDia::ZParseAckNetFrmXmlData()
{
    //qDebug()<<"ZListRoleUserInfoDia::ParseAckNetFrm:"<<this->m_ackNetFrmXmlData;

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
                if(cmd=="list")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QStringList paraList;
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString backupName=attr.value(QString("backupName")).toString();
                        QString fileSize=attr.value(QString("fileSize")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        QString pathSize=tXmlReader.readElementText();
                        paraList.append(backupName);
                        paraList.append(fileSize);
                        paraList.append(creator);
                        paraList.append(createTime);
                        paraList.append(pathSize);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("backup","list",paraList,retCode);
                }//list.
            }//Backup.
        }//StarElement.
    }//while().
}
