#include "zlisttemplateinfodia.h"
#include <QXmlStreamReader>
#include <QDebug>
ZListTemplateVarSourceInfoDia::ZListTemplateVarSourceInfoDia(QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setWindowTitle(tr("获取模板及变量源列表"));
    this->m_llMsg=new QLabel(tr("获取模板及变量源列表失败!\n命令请求超时!\n请检测网络连接状态和服务器状态!"));
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
ZListTemplateVarSourceInfoDia::~ZListTemplateVarSourceInfoDia()
{
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_vLayout;
}
void ZListTemplateVarSourceInfoDia::ZExecuteListOp()
{
    PNetFrame_Template *netFrm=new PNetFrame_Template;
    netFrm->ZListTemplate();
    this->m_waitDia->ZSetTipsMsg(tr("正在获取模板及变量源列表"));
    this->m_netFrmQueue.enqueue(netFrm);

    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
}
void ZListTemplateVarSourceInfoDia::ZParseAckNetFrmXmlData()
{
    //qDebug()<<"ZListTemplateInfoDia::ParseAckNetFrm:"<<this->m_ackNetFrmXmlData;

    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Template"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="list")
                {
                    QString item=attr.value(QString("item")).toString();
                    if(item=="template")
                    {
                        QString fileSize=attr.value(QString("filesize")).toString();
                        QString varSource=attr.value(QString("varsource")).toString();
                        qint32 retCode=attr.value(QString("retCode")).toInt();
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        QString templateName=tXmlReader.readElementText();
                        QStringList paraList;
                        paraList.append(templateName);
                        paraList.append(varSource);
                        paraList.append(fileSize);
                        paraList.append(creator);
                        paraList.append(createTime);
                        paraList.append(errMsg);
                        this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("template","list",paraList,retCode);
                    }else if(item=="varsource")
                    {
                        qint32 retCode=attr.value(QString("retCode")).toInt();
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        QString refCount=attr.value(QString("RefCount")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        QString varSourceName=tXmlReader.readElementText();
                        QStringList paraList;
                        paraList.append(varSourceName);
                        paraList.append(refCount);
                        paraList.append(creator);
                        paraList.append(createTime);
                        paraList.append(errMsg);
                        this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("varsource","list",paraList,retCode);
                    }
                }
            }//Template.
        }//StarElement.
    }//while().
}
