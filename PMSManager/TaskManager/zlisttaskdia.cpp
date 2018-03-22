#include "zlisttaskdia.h"
#include <QXmlStreamReader>
#include <QDebug>
ZListTaskDia::ZListTaskDia(QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setWindowTitle(tr("获取任务列表"));
    this->m_llMsg=new QLabel(tr("获取任务列表失败!\n命令请求超时!\n请检测网络连接状态和服务器状态!"));
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
ZListTaskDia::~ZListTaskDia()
{
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_vLayout;
}
void ZListTaskDia::ZExecuteListOp(qint32 type)
{
    PNetFrame_Task *netFrm=new PNetFrame_Task;
    netFrm->ZListTask(type);
    this->m_waitDia->ZSetTipsMsg(tr("正在获取任务列表"));
    this->m_netFrmQueue.enqueue(netFrm);

    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
}
void ZListTaskDia::ZParseAckNetFrmXmlData()
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
                if(cmd=="list")
                {
                    QString refTemplate=attr.value(QString("refTemplate")).toString();
                    QString refProcess=attr.value(QString("refProcess")).toString();
                    QString refStep=attr.value(QString("refStep")).toString();
                    QString taskState=attr.value(QString("taskState")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString createTime=attr.value(QString("createTime")).toString();
                    QString checker=attr.value(QString("checker")).toString();
                    QString checkTime=attr.value(QString("checkTime")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString taskName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(taskName);
                    paraList.append(refProcess);
                    paraList.append(refStep);
                    paraList.append(refTemplate);
                    paraList.append(taskState);
                    paraList.append(creator);
                    paraList.append(createTime);
                    paraList.append(checker);
                    paraList.append(checkTime);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("task","list",paraList,retCode);
                }
            }
        }//StarElement.
    }//while().
}
////////////////////////////////////////////////////
ZFindTaskDia::ZFindTaskDia(QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setWindowTitle(tr("高级查找"));
    this->m_llMsg=new QLabel(tr("高级查找执行失败!\n命令请求超时!\n请检测网络连接状态和服务器状态!"));
    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("关闭"));
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_llMsg);
    this->m_vLayout->addWidget(this->m_tbOkay);
    this->setLayout(this->m_vLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(reject()));
}
ZFindTaskDia::~ZFindTaskDia()
{
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_vLayout;
}
void ZFindTaskDia::ZExecuteFindOp(QString machineNo,QString classNo,QString orderNo,QString productNo,QString startTime,QString endTime)
{
    PNetFrame_Task *netFrm=new PNetFrame_Task;
    netFrm->ZFindTask(machineNo,classNo,orderNo,productNo,startTime,endTime);
    this->m_waitDia->ZSetTipsMsg(tr("正在执行高级查找..."));
    this->m_netFrmQueue.enqueue(netFrm);

    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
}
void ZFindTaskDia::ZParseAckNetFrmXmlData()
{
    qDebug()<<"ZFindTaskDia:"<<this->m_ackNetFrmXmlData;
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
                if(cmd=="find")
                {
                    QStringList paraList;
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString machineNo=attr.value(QString("machineNo")).toString();
                        QString classNo=attr.value(QString("classNo")).toString();
                        QString orderNo=attr.value(QString("orderNo")).toString();
                        QString productNo=attr.value(QString("productNo")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        QString taskName=tXmlReader.readElementText();

                        paraList.append(taskName);
                        paraList.append(machineNo);
                        paraList.append(classNo);
                        paraList.append(orderNo);
                        paraList.append(productNo);
                        paraList.append(creator);
                        paraList.append(createTime);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("task","find",paraList,retCode);
                }
            }
        }//StarElement.
    }//while().
}
