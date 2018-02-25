#include "zfileinfodia.h"
#include <QDebug>
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>
ZFileInfoDia::ZFileInfoDia(FileInfoDiaType type,QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->m_llFolderName=new QLabel(tr("文件夹名称"));
    this->m_leFolderName=new QLineEdit;
    this->m_leFolderName->setEnabled(false);

    this->m_llFileName=new QLabel(tr("文件名称"));
    this->m_leFileName=new QLineEdit;
    this->m_leFileName->setEnabled(false);

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
    this->m_gridLayout->addWidget(this->m_llFileName,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_leFileName,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_btnOkay,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_btnCancel,2,1,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_btnOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_btnCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));

    this->m_diaType=type;
    switch(this->m_diaType)
    {
    case Type_AddFile:
        this->setWindowTitle(tr("上传文件"));
        break;
    case Type_DelFile:
        this->setWindowTitle(tr("删除文件"));
        break;
    case Type_GetFile:
        this->setWindowTitle(tr("下载文件"));
        break;
    default:
        break;
    }
}
ZFileInfoDia::~ZFileInfoDia()
{
    delete this->m_llFolderName;
    delete this->m_leFolderName;
    delete this->m_llFileName;
    delete this->m_leFileName;
    delete this->m_btnOkay;
    delete this->m_btnCancel;
    delete this->m_gridLayout;
}
void ZFileInfoDia::ZSetFolderName(QString folderName)
{
    this->m_leFolderName->setText(folderName);
}
QString ZFileInfoDia::ZGetFolderName()
{
    return this->m_leFolderName->text().trimmed();
}
void ZFileInfoDia::ZSetFileName(QString fileName)
{
    this->m_leFileName->setText(fileName);
}
QString ZFileInfoDia::ZGetFileName()
{
    return this->m_leFileName->text().trimmed();
}

void ZFileInfoDia::ZParseAckNetFrmXmlData()
{
    //    qDebug()<<"ZFileInfoDia::ParseAckNetFrm:"<<this->m_ackNetFrmXmlData;

    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("File"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString fileName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(fileName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString folderName=attr.value(QString("folder")).toString();
                        QString fileType=attr.value(QString("type")).toString();
                        QString fileSize=attr.value(QString("size")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        paraList.append(folderName);
                        paraList.append(fileType);
                        paraList.append(fileSize);
                        paraList.append(creator);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("file","add",paraList,retCode);
                }else if(cmd=="updata")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString fileName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(fileName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString folderName=attr.value(QString("folder")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        paraList.append(folderName);
                        paraList.append(creator);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("file","updata",paraList,retCode);
                }else if(cmd=="del")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString folderName=attr.value(QString("folder")).toString();
                    QString fileName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(folderName);
                    paraList.append(fileName);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("file","del",paraList,retCode);
                }else if(cmd=="get")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString fileName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(fileName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString folderName=attr.value(QString("folder")).toString();
                        QString fileType=attr.value(QString("type")).toString();
                        QString totalBlock=attr.value(QString("totalBlock")).toString();
                        QString blockSize=attr.value(QString("blockSize")).toString();
                        QString remainBytes=attr.value(QString("remainBytes")).toString();
                        paraList.append(folderName);
                        paraList.append(fileType);
                        paraList.append(totalBlock);
                        paraList.append(blockSize);
                        paraList.append(remainBytes);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("file","get",paraList,retCode);
                }else if(cmd=="dwndata")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString folderName=attr.value(QString("folder")).toString();
                    QString totalBlock=attr.value(QString("totalBlock")).toString();
                    QString currentBlock=attr.value(QString("currentBlock")).toString();
                    QString data=attr.value(QString("data")).toString();
                    QString fileName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(fileName);
                    paraList.append(folderName);
                    paraList.append(totalBlock);
                    paraList.append(currentBlock);
                    paraList.append(data);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("file","dwndata",paraList,retCode);
                }
            }//Folder.
        }//StarElement.
    }//while().
}
void ZFileInfoDia::ZSlotOkay()
{
    switch(this->m_diaType)
    {
    case Type_AddFile:
    {
        qint32 totalBlock;
        qint32 remainBytes;
        QFile file(this->ZGetFileName());
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this,tr("错误提示"),tr("打开文件[%1]失败!\n%2.").arg(this->ZGetFileName()).arg(file.errorString()));
            this->reject();
        }
        if(file.size()<=0)
        {
            QMessageBox::critical(this,tr("错误提示"),tr("无法上传空文件[%1].").arg(this->ZGetFileName()));
            this->reject();
        }
        totalBlock=file.size()/(1*1024*1024);
        remainBytes=file.size()%(1*1024*1024);
        file.close();
        qDebug()<<"fileName:"<<this->ZGetFileName();
        qDebug()<<"fileSize:"<<file.size()/(1*1024*1024)<<" MB";
        qDebug()<<"totalblock:"<<totalBlock<<"remainBytes:"<<remainBytes;
        PNetFrame_File *netFrm=new PNetFrame_File;
        netFrm->ZAddFile(this->ZGetFileName(),this->ZGetFolderName(),file.size());
        this->m_waitDia->ZSetTipsMsg(tr("正在上传文件[%1]").arg(this->ZGetFileName()));
        this->m_netFrmQueue.enqueue(netFrm);
        MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);

        for(qint32 i=0;i<totalBlock;i++)
        {
            qint32 readPos=i*(1*1024*1024);
            PNetFrame_File *netFrm=new PNetFrame_File;
            if(remainBytes>0)
            {
                netFrm->ZAddData(this->ZGetFileName(),this->ZGetFolderName(),readPos,1*1024*1024,totalBlock+1,i+1);
            }else{
                netFrm->ZAddData(this->ZGetFileName(),this->ZGetFolderName(),readPos,1*1024*1024,totalBlock,i+1);
            }
            this->m_netFrmQueue.enqueue(netFrm);
        }
        if(remainBytes>0)
        {
            qint32 readPos=totalBlock*(1*1024*1024);
            PNetFrame_File *netFrm=new PNetFrame_File;
            netFrm->ZAddData(this->ZGetFileName(),this->ZGetFolderName(),readPos,remainBytes,totalBlock+1,totalBlock+1);
            this->m_netFrmQueue.enqueue(netFrm);
        }
        MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
        MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
        MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    }
        break;
    case Type_DelFile:
    {
        PNetFrame_File *netFrm=new PNetFrame_File;
        netFrm->ZDelFile(this->ZGetFileName(),this->ZGetFolderName());
        this->m_waitDia->ZSetTipsMsg(tr("正在删除文件[%1]").arg(this->ZGetFileName()));
        this->m_netFrmQueue.enqueue(netFrm);
        MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
        MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
        MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
        MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
    }
        break;
    case Type_GetFile:
    {
        QString filePath(QDir::currentPath()+"/cache/file/"+this->ZGetFolderName()+"/"+this->ZGetFileName());
        QFile::remove(filePath);

        PNetFrame_File *netFrm=new PNetFrame_File;
        netFrm->ZGetFile(this->ZGetFileName(),this->ZGetFolderName());
        this->m_waitDia->ZSetTipsMsg(tr("正在下载文件[%1]").arg(this->ZGetFileName()));
        this->m_netFrmQueue.enqueue(netFrm);
        MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
        MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
        MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
        MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
    }
        break;
    default:
        break;
    }
    this->accept();
}
void ZFileInfoDia::ZSlotCancel()
{
    this->reject();
}
void ZFileInfoDia::ZDwnData(QString fileName,QString folderName,qint32 totalBlock,qint32 blockSize,qint32 remainBytes)
{
    this->m_waitDia->ZSetTipsMsg(tr("正在下载文件[%1]").arg(totalBlock));
    for(qint32 i=0;i<totalBlock;i++)
    {
        PNetFrame_File *netFrm=new PNetFrame_File;
        if(remainBytes>0)
        {
            netFrm->ZGetData(fileName,folderName,totalBlock+1,i+1,i*blockSize,blockSize);
        }else{
            netFrm->ZGetData(fileName,folderName,totalBlock,i+1,i*blockSize,blockSize);
        }
        this->m_netFrmQueue.enqueue(netFrm);
        if(i==0)
        {
            MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
        }
    }
    if(remainBytes>0)
    {
        PNetFrame_File *netFrm=new PNetFrame_File;
        netFrm->ZGetData(fileName,folderName,totalBlock+1,totalBlock+1,totalBlock*blockSize,remainBytes);
        this->m_netFrmQueue.enqueue(netFrm);
        if(totalBlock==0)
        {
            MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
        }
    }
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
}
