#include "zfolderinfodia.h"
#include <QMessageBox>
#include <QDebug>
#include <QXmlStreamReader>
ZFolderInfoDia::ZFolderInfoDia(FolderInfoDiaType type,QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->m_llFolderName=new QLabel(tr("文件夹名称"));
    this->m_leFolderName=new QLineEdit;

    this->m_btnOkay=new QToolButton;
    this->m_btnOkay->setText(tr("确认"));
    this->m_btnCancel=new QToolButton;
    this->m_btnCancel->setText(tr("取消"));
    this->m_btnOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_btnOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_btnCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llFolderName,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leFolderName,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_btnOkay,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_btnCancel,1,1,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_btnOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_btnCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));

    this->m_diaType=type;
    switch(type)
    {
    case Type_NewFolder:
        this->setWindowTitle(tr("创建新文件夹"));
        break;
    case Type_DelFolder:
        this->setWindowTitle(tr("删除文件夹"));
        this->m_leFolderName->setEnabled(false);
        break;
    default:
        break;
    }
}
ZFolderInfoDia::~ZFolderInfoDia()
{
    delete this->m_llFolderName;
    delete this->m_leFolderName;

    delete this->m_btnOkay;
    delete this->m_btnCancel;

    delete this->m_gridLayout;
}
void ZFolderInfoDia::ZSetFolderName(QString name)
{
    this->m_leFolderName->setText(name);
}
QString ZFolderInfoDia::ZGetFolderName()
{
    return this->m_leFolderName->text().trimmed();
}
void ZFolderInfoDia::ZParseAckNetFrmXmlData()
{
    qDebug()<<"ZFolderInfoDia::ParseAckNetFrm:"<<this->m_ackNetFrmXmlData;

    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Folder"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString folderName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(folderName);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("folder","add",paraList,retCode);
                }else if(cmd=="del")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString folderName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(folderName);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("folder","del",paraList,retCode);
                }
            }//Folder.
        }//StarElement.
    }//while().
}
void ZFolderInfoDia::ZSlotOkay()
{
    if(MyUserInfo::ZGetInstance()->m_bOnLine==false)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("网络错误,未连接服务器!\n请等待连接服务器成功后再操作!"));
        return;
    }
    if(this->m_leFolderName->text().trimmed().isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("新文件夹名不能为空!"));
        return;
    }
    PNetFrame_Folder *netFrm=new PNetFrame_Folder;
    switch(this->m_diaType)
    {
    case Type_NewFolder:
        netFrm->ZAddFolder(this->ZGetFolderName());
        this->m_waitDia->ZSetTipsMsg(tr("正在添加新文件夹[%1]").arg(this->ZGetFolderName()));
        break;
    case Type_DelFolder:
        netFrm->ZDelFolder(this->ZGetFolderName());
        this->m_waitDia->ZSetTipsMsg(tr("正在删除文件夹[%1]").arg(this->ZGetFolderName()));
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
void ZFolderInfoDia::ZSlotCancel()
{
    this->reject();
}
