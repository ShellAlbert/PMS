#include "zprocessinfodia.h"
#include <QMessageBox>
#include <QDebug>
#include <QXmlStreamReader>
ZProcessInfoDia::ZProcessInfoDia(ProcessInfoDiaType type,QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->m_llProcessName=new QLabel(tr("工序名称"));
    this->m_leProcessName=new QLineEdit;

    this->m_btnOkay=new QToolButton;
    this->m_btnOkay->setText(tr("确认"));
    this->m_btnCancel=new QToolButton;
    this->m_btnCancel->setText(tr("取消"));
    this->m_btnOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_btnOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_btnCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llProcessName,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leProcessName,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_btnOkay,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_btnCancel,1,1,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_btnOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_btnCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));

    this->m_diaType=type;
    switch(type)
    {
    case Type_NewProcess:
        this->setWindowTitle(tr("创建新工序"));
        break;
    case Type_DelProcess:
        this->setWindowTitle(tr("删除工序"));
        this->m_leProcessName->setEnabled(false);
        break;
    case Type_SaveProcess:
        this->setWindowTitle(tr("保存工序"));
        this->m_leProcessName->setEnabled(false);
        break;
    case Type_GetProcess:
        this->setWindowTitle(tr("获取工序"));
        this->m_leProcessName->setEnabled(false);
        break;
    default:
        break;
    }
}
ZProcessInfoDia::~ZProcessInfoDia()
{
    delete this->m_llProcessName;
    delete this->m_leProcessName;

    delete this->m_btnOkay;
    delete this->m_btnCancel;

    delete this->m_gridLayout;
}
void ZProcessInfoDia::ZSetProcessName(QString name)
{
    this->m_leProcessName->setText(name);
}
QString ZProcessInfoDia::ZGetProcessName()
{
    return this->m_leProcessName->text().trimmed();
}
void ZProcessInfoDia::ZSetProcessXmlData(QString xmlData)
{
    this->m_processXmlData=xmlData;
}
QString ZProcessInfoDia::ZGetProcessXmlData()
{
    return this->m_processXmlData;
}
void ZProcessInfoDia::ZSetStepNum(qint32 stepNum)
{
    this->m_stepNum=stepNum;
}
qint32 ZProcessInfoDia::ZGetStepNum()
{
    return this->m_stepNum;
}
void ZProcessInfoDia::ZParseAckNetFrmXmlData()
{
    qDebug()<<"ZProcessInfoDia::ParseAckNetFrm:"<<this->m_ackNetFrmXmlData;

    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Process"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    QString creator=attr.value(QString("creator")).toString();
                    QString createTime=attr.value(QString("createTime")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString processName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(processName);
                    paraList.append(creator);
                    paraList.append(createTime);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("process","add",paraList,retCode);
                }else if(cmd=="del")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString processName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(processName);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("process","del",paraList,retCode);
                }else if(cmd=="get")
                {
                    QString data=attr.value(QString("data")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString processName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(processName);
                    paraList.append(data);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("process","get",paraList,retCode);
                }else if(cmd=="save")
                {
                    QString stepNum=attr.value(QString("stepNum")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString processName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(processName);
                    paraList.append(stepNum);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("process","save",paraList,retCode);
                }
            }//Process.
        }//StarElement.
    }//while().
}
void ZProcessInfoDia::ZSlotOkay()
{
    if(MyUserInfo::ZGetInstance()->m_bOnLine==false)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("网络错误,未连接服务器!\n请等待连接服务器成功后再操作!"));
        return;
    }
    if(this->m_leProcessName->text().trimmed().isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("工序名不能为空!"));
        return;
    }
    PNetFrame_Process *netFrm=new PNetFrame_Process;
    switch(this->m_diaType)
    {
    case Type_NewProcess:
        netFrm->ZAddProcess(this->ZGetProcessName());
        this->m_waitDia->ZSetTipsMsg(tr("正在创建新工序[%1]").arg(this->ZGetProcessName()));
        break;
    case Type_DelProcess:
        netFrm->ZDelProcess(this->ZGetProcessName());
        this->m_waitDia->ZSetTipsMsg(tr("正在删除工序[%1]").arg(this->ZGetProcessName()));
        break;
    case Type_GetProcess:
        netFrm->ZGetProcess(this->ZGetProcessName());
        this->m_waitDia->ZSetTipsMsg(tr("正在获取工序[%1]").arg(this->ZGetProcessName()));
        break;
    case Type_SaveProcess:
        netFrm->ZSaveProcess(this->ZGetProcessName(),this->ZGetStepNum(),this->ZGetProcessXmlData());
        this->m_waitDia->ZSetTipsMsg(tr("正在保存工序[%1]").arg(this->ZGetProcessName()));
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
void ZProcessInfoDia::ZSlotCancel()
{
    this->reject();
}
