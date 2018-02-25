#include "zvarsourceinfodia.h"
#include <QXmlStreamReader>
#include <QDebug>
#include <QMessageBox>
ZVarSourceInfoDia::ZVarSourceInfoDia(VarSourceInfoDiaType type,QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->m_llVarSourceName=new QLabel(tr("变量源名称"));
    this->m_leVarSourceName=new QLineEdit;
    this->m_leVarSourceName->setMaxLength(16);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));

    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));

    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llVarSourceName,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leVarSourceName,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbOkay,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_tbCancel,1,1,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));

    this->m_diaType=type;
    switch(type)
    {
    case Type_NewVarSource:
        this->setWindowTitle(tr("创建新变量源"));
        break;
    case Type_DelVarSource:
        this->setWindowTitle(tr("删除变量源"));
        this->m_leVarSourceName->setEnabled(false);
        break;
    case Type_GetVarSource:
        this->setWindowTitle(tr("获取变量源"));
        this->m_leVarSourceName->setEnabled(false);
        break;
    case Type_SaveVarSource:
        this->setWindowTitle(tr("保存变量源"));
        this->m_leVarSourceName->setEnabled(false);
        break;
    default:
        break;
    }
}
ZVarSourceInfoDia::~ZVarSourceInfoDia()
{
    delete this->m_llVarSourceName;
    delete this->m_leVarSourceName;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gridLayout;
}
void ZVarSourceInfoDia::ZSetVarSourceName(QString name)
{
    this->m_leVarSourceName->setText(name);
}
QString ZVarSourceInfoDia::ZGetVarSourceName()
{
    return this->m_leVarSourceName->text().trimmed();
}
void ZVarSourceInfoDia::ZSetVarSourceXmlData(QString xmlData)
{
    this->m_varSourceXmlData=xmlData;
}
void ZVarSourceInfoDia::ZParseAckNetFrmXmlData()
{
    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("VarSource"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    QString refCount=attr.value(QString("refCount")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString createTime=attr.value(QString("createTime")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString varSourceName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(varSourceName);
                    paraList.append(refCount);
                    paraList.append(creator);
                    paraList.append(createTime);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("varsource","add",paraList,retCode);
                }else if(cmd=="del")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString varSourceName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(varSourceName);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("varsource","del",paraList,retCode);
                }else if(cmd=="get")
                {
                    QString data=attr.value(QString("data")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString varSourceName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(varSourceName);
                    paraList.append(QString(QByteArray::fromBase64(data.toUtf8())));
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("varsource","get",paraList,retCode);
                }else if(cmd=="save")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString varSourceName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(varSourceName);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("varsource","save",paraList,retCode);
                }else if(cmd=="list")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString createTime=attr.value(QString("createTime")).toString();
                    QString varSourceName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(varSourceName);
                    paraList.append(errMsg);
                    paraList.append(creator);
                    paraList.append(createTime);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("varsource","list",paraList,retCode);
                }
            }//VarSource.
        }//StarElement.
    }//while().
}
void ZVarSourceInfoDia::ZSlotOkay()
{
    if(MyUserInfo::ZGetInstance()->m_bOnLine==false)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("网络错误,未连接服务器!\n请等待连接服务器成功后再操作!"));
        return;
    }
    if(this->m_leVarSourceName->text().trimmed().isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("变量源名称不能为空!"));
        return;
    }
    PNetFrame_VarSource *netFrm=new PNetFrame_VarSource;
    switch(this->m_diaType)
    {
    case Type_NewVarSource:
        netFrm->ZAddVarSource(this->ZGetVarSourceName());
        this->m_waitDia->ZSetTipsMsg(tr("正在创建新变量源[%1]").arg(this->ZGetVarSourceName()));
        break;
    case Type_DelVarSource:
        netFrm->ZDelVarSource(this->ZGetVarSourceName());
        this->m_waitDia->ZSetTipsMsg(tr("正在删除变量源[%1]").arg(this->ZGetVarSourceName()));
        break;
    case Type_GetVarSource:
        netFrm->ZGetVarSource(this->ZGetVarSourceName());
        this->m_waitDia->ZSetTipsMsg(tr("正在获取变量源[%1]").arg(this->ZGetVarSourceName()));
        break;
    case Type_SaveVarSource:
        netFrm->ZSaveVarSource(this->ZGetVarSourceName(),this->m_varSourceXmlData);
        this->m_waitDia->ZSetTipsMsg(tr("正在保存变量源[%1]").arg(this->ZGetVarSourceName()));
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
void ZVarSourceInfoDia::ZSlotCancel()
{
    this->reject();
}
