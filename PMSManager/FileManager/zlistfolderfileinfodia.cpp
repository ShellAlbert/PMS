#include "zlistfolderfileinfodia.h"
#include <QXmlStreamReader>
#include <QDebug>
ZListFolderFileInfoDia::ZListFolderFileInfoDia(QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setWindowTitle(tr("获取文件夹及文件列表"));
    this->m_llMsg=new QLabel(tr("获取文件夹及文件列表失败!\n命令请求超时!\n请检测网络连接状态和服务器状态!"));
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
ZListFolderFileInfoDia::~ZListFolderFileInfoDia()
{
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_vLayout;
}
void ZListFolderFileInfoDia::ZExecuteListOp()
{
    PNetFrame_Folder *netFrm=new PNetFrame_Folder;
    netFrm->ZListFolder();
    this->m_waitDia->ZSetTipsMsg(tr("正在获取文件夹及文件列表"));
    this->m_netFrmQueue.enqueue(netFrm);


    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
}
void ZListFolderFileInfoDia::ZParseAckNetFrmXmlData()
{
    qDebug()<<"ZListFolderFileInfoDia::ParseAckNetFrm:"<<this->m_ackNetFrmXmlData;

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
                if(cmd=="list")
                {
                    QString item=attr.value(QString("item")).toString();
                    if(item=="folder")
                    {
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        QString folderName=tXmlReader.readElementText();
                        QStringList paraList;
                        paraList.append(folderName);
                        paraList.append(creator);
                        paraList.append(createTime);
                        this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("folder","list",paraList,0);
                    }else if(item=="file")
                    {
                        QString folderName=attr.value(QString("folderName")).toString();
                        QString fileType=attr.value(QString("type")).toString();
                        QString fileSize=attr.value(QString("size")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        QString fileName=tXmlReader.readElementText();
                        QStringList paraList;
                        paraList.append(fileName);
                        paraList.append(folderName);
                        paraList.append(fileType);
                        paraList.append(fileSize);
                        paraList.append(creator);
                        paraList.append(createTime);
                        this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("file","list",paraList,0);
                    }
                }//list.
            }//Role.
        }//StarElement.
    }//while().
}
