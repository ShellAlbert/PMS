#include "zlistprocesssteplinktemplatedia.h"
#include <QXmlStreamReader>
ZListProcessStepLinkTemplateDia::ZListProcessStepLinkTemplateDia(QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setWindowTitle(tr("获取可用任务列表"));
    this->m_llMsg=new QLabel(tr("获取可用任务列表失败!\n命令请求超时!\n请检测网络连接状态和服务器状态!"));
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
ZListProcessStepLinkTemplateDia::~ZListProcessStepLinkTemplateDia()
{
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_vLayout;
}
void ZListProcessStepLinkTemplateDia::ZExecuteListOp()
{
    PNetFrame_Task *netFrm=new PNetFrame_Task;
    netFrm->ZListNewTask();
    this->m_waitDia->ZSetTipsMsg(tr("正在获取可用任务列表"));
    this->m_netFrmQueue.enqueue(netFrm);

    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
}
void ZListProcessStepLinkTemplateDia::ZParseAckNetFrmXmlData()
{
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
                if(cmd=="listnew")
                {
                    QString processName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(processName);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("process","listnew",paraList,0);
                }
            }else if(nodeName==QString("Step"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="listnew")
                {
                    QString processName=attr.value(QString("process")).toString();
                    QString linkTemplate=attr.value(QString("linktemplate")).toString();
                    QString stepName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(processName);
                    paraList.append(stepName);
                    paraList.append(linkTemplate);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("step","listnew",paraList,0);
                }
            }
        }//StarElement.
    }//while().
}
