#include "zlistforminfodia.h"
#include <QXmlStreamReader>
#include <QDebug>
ZListFormInfoDia::ZListFormInfoDia(QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setWindowTitle(tr("获取报表列表"));
    this->m_llMsg=new QLabel(tr("获取报表列表失败!\n命令请求超时!\n请检测网络连接状态和服务器状态!"));
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
ZListFormInfoDia::~ZListFormInfoDia()
{
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_vLayout;
}
void ZListFormInfoDia::ZExecuteListOp()
{
    PNetFrame_Form *netFrm=new PNetFrame_Form;
    netFrm->ZListForm();
    this->m_waitDia->ZSetTipsMsg(tr("正在获取报表列表..."));
    this->m_netFrmQueue.enqueue(netFrm);

    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
}
void ZListFormInfoDia::ZParseAckNetFrmXmlData()
{
    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Form"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="list")
                {
                    QString fileSize=attr.value(QString("fileSize")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    QString createTime=attr.value(QString("createTime")).toString();
                    QString formName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(formName);
                    paraList.append(fileSize);
                    paraList.append(creator);
                    paraList.append(createTime);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("form","list",paraList,0);
                }//list.
            }//Role.
        }//StarElement.
    }//while().
}
