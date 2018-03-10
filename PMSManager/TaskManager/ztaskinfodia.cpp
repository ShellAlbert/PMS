#include "ztaskinfodia.h"
#include <QXmlStreamReader>
#include <QMessageBox>
ZTaskInfoDia::ZTaskInfoDia(ZTaskInfoDia::TaskInfoDiaType type,QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setMinimumSize(400,200);

    this->m_llOpTips=new QLabel;

    this->m_llTaskName=new QLabel(tr("任务名称"));
    this->m_leTaskName=new QLineEdit;

    this->m_llRefTemplateName=new QLabel(tr("引用模板"));
    this->m_leRefTemplateName=new QLineEdit;
    this->m_leRefTemplateName->setEnabled(false);

    this->m_llProcessName=new QLabel(tr("引用工序"));
    this->m_leProcessName=new QLineEdit;
    this->m_leProcessName->setEnabled(false);

    this->m_llStepName=new QLabel(tr("引用步序"));
    this->m_leStepName=new QLineEdit;
    this->m_leStepName->setEnabled(false);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("OKAY"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("CANCEL"));
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_hLayoutBtn=new QHBoxLayout;
    this->m_hLayoutBtn->addStretch(1);
    this->m_hLayoutBtn->addWidget(this->m_tbOkay);
    this->m_hLayoutBtn->addWidget(this->m_tbCancel);

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llTaskName,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leTaskName,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_llRefTemplateName,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_leRefTemplateName,1,1,1,1);

    this->m_gridLayout->addWidget(this->m_llProcessName,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_leProcessName,2,1,1,1);
    this->m_gridLayout->addWidget(this->m_llStepName,3,0,1,1);
    this->m_gridLayout->addWidget(this->m_leStepName,3,1,1,1);

    this->m_diaType=type;
    switch(type)
    {
    case Type_NewTask:
        this->setWindowTitle(tr("新建任务"));
        this->m_llOpTips->setText(tr("新任务名称为自动创建,一般不需要修改。"));
        break;
    case Type_OpenTask:
        this->setWindowTitle(tr("打开任务"));
        this->m_llOpTips->setText(tr("即时打开下列任务，确定后打开。"));
        this->m_leTaskName->setEnabled(false);
        break;
    case Type_SaveTask:
        this->setWindowTitle(tr("保存任务"));
        this->m_llOpTips->setText(tr("下列任务将被保存，确定后保存。"));
        this->m_leTaskName->setEnabled(false);
        break;
    case Type_DelTask:
        this->setWindowTitle(tr("删除任务"));
        this->m_llOpTips->setText(tr("下列任务将被删除，删除不可逆，确定后删除。"));
        this->m_leTaskName->setEnabled(false);
        break;
    case Type_SubmitTask:
        this->setWindowTitle(tr("提交审核任务"));
        this->m_llOpTips->setText(tr("下列任务将被提交到您的上级审核。"));
        this->m_leTaskName->setEnabled(false);
        break;
    case Type_WithdrawTask:
        this->setWindowTitle(tr("撤回未审核任务"));
        this->m_llOpTips->setText(tr("下列提交未审核的任务将被撤回。"));
        this->m_leTaskName->setEnabled(false);
        break;
    case Type_CheckOkayTask:
        this->setWindowTitle(tr("审核通过任务"));
        this->m_llOpTips->setText(tr("下列任务将被您审核通过，通过后不可修改。"));
        this->m_leTaskName->setEnabled(false);
        break;
    case Type_CheckFailedTask:
        this->setWindowTitle(tr("审核失败任务"));
        this->m_llOpTips->setText(tr("下列任务将被您审核失败，提交者需要修改再次提交审核。"));
        this->m_leTaskName->setEnabled(false);
        break;
    case Type_ArchieveTask:
        this->setWindowTitle(tr("归档任务"));
        this->m_llOpTips->setText(tr("下列任务将被您归档处理，归档后的任务不可修改。"));
        this->m_leTaskName->setEnabled(false);
        break;
    default:
        break;
    }
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_llOpTips);
    this->m_vLayout->addLayout(this->m_gridLayout);
    this->m_vLayout->addLayout(this->m_hLayoutBtn);
    this->setLayout(this->m_vLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
}
ZTaskInfoDia::~ZTaskInfoDia()
{
    delete this->m_llOpTips;
    delete this->m_llTaskName;
    delete this->m_leTaskName;
    delete this->m_llRefTemplateName;
    delete this->m_leRefTemplateName;
    delete this->m_llProcessName;
    delete this->m_leProcessName;
    delete this->m_llStepName;
    delete this->m_leStepName;
    delete this->m_gridLayout;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayoutBtn;
    delete this->m_vLayout;
}
void ZTaskInfoDia::ZParseAckNetFrmXmlData()
{
    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Task"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString taskName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(taskName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString refTemplate=attr.value(QString("refTemplate")).toString();
                        QString refProcess=attr.value(QString("refProcess")).toString();
                        QString refStep=attr.value(QString("refStep")).toString();
                        QString taskState=attr.value(QString("taskState")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        QString checker=attr.value(QString("checker")).toString();
                        QString checkTime=attr.value(QString("checkTime")).toString();
                        paraList.append(refTemplate);
                        paraList.append(refProcess);
                        paraList.append(refStep);
                        paraList.append(taskState);
                        paraList.append(creator);
                        paraList.append(createTime);
                        paraList.append(checker);
                        paraList.append(checkTime);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("task","add",paraList,retCode);
                }else if(cmd=="get")
                {
                    QString refTemplate=attr.value(QString("refTemplate")).toString();
                    QString refProcess=attr.value(QString("refProcess")).toString();
                    QString refStep=attr.value(QString("refStep")).toString();
                    QString templatedata=attr.value(QString("templatedata")).toString();
                    QString varsrcdata=attr.value(QString("varsrcdata")).toString();
                    QString vardata=attr.value(QString("vardata")).toString();
                    QString taskState=attr.value(QString("taskState")).toString();
                    QString taskName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(taskName);
                    paraList.append(refTemplate);
                    paraList.append(refProcess);
                    paraList.append(refStep);
                    paraList.append(templatedata);
                    paraList.append(varsrcdata);
                    paraList.append(vardata);
                    paraList.append(taskState);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("task","get",paraList,0);
                }else if(cmd=="del")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString taskName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(taskName);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("task","del",paraList,retCode);
                }else if(cmd=="save")
                {
                    QString taskState=attr.value(QString("taskState")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString taskName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(taskName);
                    paraList.append(taskState);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("task","save",paraList,retCode);
                }else if(cmd=="submit")
                {
                    QString taskState=attr.value(QString("taskState")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString taskName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(taskName);
                    paraList.append(taskState);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("task","submit",paraList,retCode);
                }else if(cmd=="withdraw")
                {
                    QString taskState=attr.value(QString("taskState")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString taskName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(taskName);
                    paraList.append(taskState);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("task","withdraw",paraList,retCode);
                }else if(cmd=="checkokay")
                {
                    QString taskState=attr.value(QString("taskState")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString taskName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(taskName);
                    paraList.append(taskState);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("task","checkokay",paraList,retCode);
                }else if(cmd=="checkfailed")
                {
                    QString taskState=attr.value(QString("taskState")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString taskName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(taskName);
                    paraList.append(taskState);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("task","checkfailed",paraList,retCode);
                }else if(cmd=="archieve")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString taskName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(taskName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString taskState=attr.value(QString("taskState")).toString();
                        paraList.append(taskState);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("task","archieve",paraList,retCode);
                }
            }//Task.
        }//StarElement.
    }//while().
}
void ZTaskInfoDia::ZSetTaskName(QString taskName)
{
    this->m_leTaskName->setText(taskName);
}
QString ZTaskInfoDia::ZGetTaskName()
{
    return this->m_leTaskName->text().trimmed();
}
void ZTaskInfoDia::ZSetRefTemplateName(QString templateName)
{
    this->m_leRefTemplateName->setText(templateName);
}
QString ZTaskInfoDia::ZGetRefTemplateName()
{
    return this->m_leRefTemplateName->text().trimmed();
}
void ZTaskInfoDia::ZSetProcessName(QString processName)
{
    this->m_leProcessName->setText(processName);
}
QString ZTaskInfoDia::ZGetProcessName()
{
    return this->m_leProcessName->text();
}
void ZTaskInfoDia::ZSetStepName(QString stepName)
{
    this->m_leStepName->setText(stepName);
}
QString ZTaskInfoDia::ZGetStepName()
{
    return this->m_leStepName->text();
}
void ZTaskInfoDia::ZSlotOkay()
{
    if(MyUserInfo::ZGetInstance()->m_bOnLine==false)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("网络错误,未连接服务器!\n请等待连接服务器成功后再操作!"));
        return;
    }

    PNetFrame_Task *netFrm=new PNetFrame_Task;
    switch(this->m_diaType)
    {
    case Type_NewTask:
        netFrm->ZNewTask(this->ZGetTaskName(),this->ZGetRefTemplateName(),this->ZGetProcessName(),this->ZGetStepName());
        this->m_waitDia->ZSetTipsMsg(tr("正在基于模板[%1]创建新任务[%2]").arg(this->ZGetRefTemplateName()).arg(this->ZGetTaskName()));
        break;
    case Type_OpenTask:
        netFrm->ZOpenTask(this->ZGetTaskName(),this->ZGetRefTemplateName());
        this->m_waitDia->ZSetTipsMsg(tr("正在打开任务[%1]").arg(this->ZGetTaskName()));
        break;
    case Type_SaveTask:
        netFrm->ZSaveTask(this->ZGetTaskName(),this->ZGetRefTemplateName(),this->m_taskValueXmlData);
        this->m_waitDia->ZSetTipsMsg(tr("正在保存任务[%1]").arg(this->ZGetTaskName()));
        break;
    case Type_DelTask:
        netFrm->ZDelTask(this->ZGetTaskName(),this->ZGetRefTemplateName());
        this->m_waitDia->ZSetTipsMsg(tr("正在删除任务[%1]").arg(this->ZGetTaskName()));
        break;
    case Type_SubmitTask:
        netFrm->ZSubmitTask(this->ZGetTaskName(),this->ZGetRefTemplateName());
        this->m_waitDia->ZSetTipsMsg(tr("正在提交审核任务[%1]").arg(this->ZGetTaskName()));
        break;
    case Type_WithdrawTask:
        netFrm->ZWithdrawTask(this->ZGetTaskName(),this->ZGetRefTemplateName());
        this->m_waitDia->ZSetTipsMsg(tr("正在撤回未审核任务[%1]").arg(this->ZGetTaskName()));
        break;
    case Type_CheckOkayTask:
        netFrm->ZCheckOkayTask(this->ZGetTaskName(),this->ZGetRefTemplateName());
        this->m_waitDia->ZSetTipsMsg(tr("正在审核通过任务[%1]").arg(this->ZGetTaskName()));
        break;
    case Type_CheckFailedTask:
        netFrm->ZCheckFailedTask(this->ZGetTaskName(),this->ZGetRefTemplateName());
        this->m_waitDia->ZSetTipsMsg(tr("正在审核失败任务[%1]").arg(this->ZGetTaskName()));
        break;
    case Type_ArchieveTask:
        netFrm->ZArchieveTask(this->ZGetTaskName(),this->ZGetRefTemplateName());
        this->m_waitDia->ZSetTipsMsg(tr("正在归档任务[%1]").arg(this->ZGetTaskName()));
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
void ZTaskInfoDia::ZSlotCancel()
{
    this->reject();
}

void ZTaskInfoDia::ZSetTaskValueXmlData(QString xmlData)
{
    this->m_taskValueXmlData=xmlData;
}
QSize ZTaskInfoDia::sizeHint() const
{
    return QSize(200,100);
}
