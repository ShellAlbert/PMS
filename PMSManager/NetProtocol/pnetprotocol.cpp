#include "pnetprotocol.h"
#include "NetProtocol/pnetframe.h"
#include <QDebug>
#include <QHostAddress>
#include "pgblpara.h"
PNetProtocol::PNetProtocol(QObject *parent) : QObject(parent)
{
    this->m_sendBuffer=new QByteArray;
    this->m_sendBuffer->resize(2*1024*1024);

    this->m_recvBuffer=new QByteArray;
    this->m_recvBuffer->resize(2*1024*1024);
    this->m_recvDataSize=0;
}
PNetProtocol::~PNetProtocol()
{
    if(this->m_sendBuffer)
    {
        delete this->m_sendBuffer;
    }
    if(this->m_recvBuffer)
    {
        delete this->m_recvBuffer;
    }
}
void PNetProtocol::ZSlotStart()
{
    this->m_run=true;
    this->m_tcpSocket=new QTcpSocket;
    connect(this->m_tcpSocket,SIGNAL(readyRead()),this,SLOT(ZSlotReadData()));
    this->m_timer=new QTimer;
    connect(this->m_timer,SIGNAL(timeout()),this,SLOT(ZSlotWriteData()));
    this->m_timer->start(100);
}
void PNetProtocol::ZSlotWriteData()
{
    if(MyUserInfo::ZGetInstance()->m_bExitFlag)
    {
        this->m_timer->stop();
        emit this->ZSignalExit();
        return;
    }

    PNetFrame *netFrm=NULL;
    if(MyNetQueue::ZGetInstance()->m_mutexSendQueue.tryLock())
    {
        if(MyNetQueue::ZGetInstance()->m_sendQueue.count()>0)
        {
            netFrm=MyNetQueue::ZGetInstance()->m_sendQueue.dequeue();
        }
        MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    }
    //check network.
    switch(this->m_tcpSocket->state())
    {
    case QAbstractSocket::UnconnectedState:
        MyUserInfo::ZGetInstance()->m_onLine=tr("断线");
        MyUserInfo::ZGetInstance()->m_bOnLine=false;
        this->m_tcpSocket->abort();
        this->m_tcpSocket->connectToHost(QHostAddress(MyUserInfo::ZGetInstance()->m_PMSIp),MyUserInfo::ZGetInstance()->m_PMSPort);
        this->m_tcpSocket->waitForConnected();
        break;
    case QAbstractSocket::HostLookupState:
        MyUserInfo::ZGetInstance()->m_bOnLine=false;
        break;
    case QAbstractSocket::ConnectingState:
        MyUserInfo::ZGetInstance()->m_onLine=tr("正在连接");
        MyUserInfo::ZGetInstance()->m_bOnLine=false;
        break;
    case QAbstractSocket::ConnectedState:
        MyUserInfo::ZGetInstance()->m_onLine=tr("在线");
        MyUserInfo::ZGetInstance()->m_bOnLine=true;
        //send netFrm out.
        if(netFrm)
        {
            qint32 dataSize=netFrm->ZPackNetFrmData(this->m_sendBuffer,this->m_sendBuffer->size());
            qint32 dataIndex=0;
            while(dataSize>0)
            {
                qint32 sendSize=this->m_tcpSocket->write(this->m_sendBuffer->data()+dataIndex,dataSize);
                this->m_tcpSocket->waitForBytesWritten();
                if(sendSize<0)
                {
                    //write error.
                    break;
                }
                dataSize-=sendSize;
                dataIndex+=sendSize;
            }
        }
        break;
    case QAbstractSocket::BoundState:
        MyUserInfo::ZGetInstance()->m_bOnLine=false;
        break;
    case QAbstractSocket::ClosingState:
        MyUserInfo::ZGetInstance()->m_onLine=tr("关闭连接");
        MyUserInfo::ZGetInstance()->m_bOnLine=false;
        break;
    case QAbstractSocket::ListeningState:
        MyUserInfo::ZGetInstance()->m_bOnLine=false;
        break;
    default:
        break;
    }

    //move netFrm from sendQueue to waitAckQueue.
    //for processing normal from the server's ack netfrm.
    //or wait for timeout schedule.
    if(netFrm)
    {
        MyNetQueue::ZGetInstance()->m_mutexWaitAckQueue.lock();
        MyNetQueue::ZGetInstance()->m_waitAckQueue.enqueue(netFrm);
        MyNetQueue::ZGetInstance()->m_mutexWaitAckQueue.unlock();
        MyNetQueue::ZGetInstance()->m_txFrmNum++;
    }
}
void PNetProtocol::ZSlotReadData()
{
    qint32 nCanReadBytes;
    while(this->m_tcpSocket->bytesAvailable()>0)
    {
        if((this->m_recvBuffer->size()-this->m_recvDataSize)>this->m_tcpSocket->bytesAvailable())
        {
            nCanReadBytes=this->m_tcpSocket->bytesAvailable();
        }else{
            nCanReadBytes=this->m_recvBuffer->size()-this->m_recvDataSize;
        }
        qint32 nRealReadBytes=this->m_tcpSocket->read(this->m_recvBuffer->data()+this->m_recvDataSize,nCanReadBytes);
        this->m_recvDataSize+=nRealReadBytes;
        //qDebug()<<"read:"<<nRealReadBytes<<",total:"<<this->m_recvDataSize;
        this->ZParseRecvData();
    }
}
void PNetProtocol::ZParseRecvData()
{
    QString frmSyncHeader("BePMS");
    qint32 frmSize;
    qint32 frmSerialNo;
    qint32 index=0;
    QByteArray arrayFrmSyncHeader=frmSyncHeader.toUtf8();
    while(this->m_recvDataSize>0)
    {
        //check min size.5 sync header+4 frm size+4 frm serial no=13 bytes.
        if(this->m_recvDataSize<13)
        {
            index=0;
            //qDebug()<<"we need more data:now:"<<this->m_recvDataSize;
            //we need more data.
            break;
        }
        //find sync header.
        index=this->m_recvBuffer->indexOf(arrayFrmSyncHeader,index);
        if(index<0)
        {
            index=0;
            //qDebug()<<"not found sync header,reset!";
            this->m_recvDataSize=0;//not found sync header,reset.
            break;
        }
        index+=arrayFrmSyncHeader.size();

        //frame total size.
        QByteArray arrayFrmSize=this->m_recvBuffer->mid(index,4);
        frmSize=QBytes2Int(arrayFrmSize);
        index+=4;
        //qDebug()<<"frmSize:"<<frmSize;

        //frame serial No.
        QByteArray arrayFrmSerialNo=this->m_recvBuffer->mid(index,4);
        frmSerialNo=QBytes2Int(arrayFrmSerialNo);
        index+=4;
        //qDebug()<<"frmSNo:"<<frmSerialNo;

        //frame xml data.
        if(this->m_recvDataSize<(13+frmSize-4))
        {
            index=0;
            //qDebug()<<"we need more xml data!";
            break;
        }
        QByteArray arrayFrmXmlData=this->m_recvBuffer->mid(index,frmSize-4);
        //qDebug()<<QString(arrayFrmXmlData);
        index+=frmSize-4;
        //according serialNo to find tx PNetFrm from waitAckQueue.
        MyNetQueue::ZGetInstance()->m_mutexWaitAckQueue.lock();
        for(qint32 i=0;i<MyNetQueue::ZGetInstance()->m_waitAckQueue.count();i++)
        {
            PNetFrame *netFrm=MyNetQueue::ZGetInstance()->m_waitAckQueue.at(i);
            if(netFrm->ZGetNetFrmSerialNo()==frmSerialNo)
            {
                MyNetQueue::ZGetInstance()->m_waitAckQueue.removeAt(i);
                break;
            }
        }
        MyNetQueue::ZGetInstance()->m_mutexWaitAckQueue.unlock();
        //call PNetFrm callback function to process the ack netFrm.
        if(MyNetQueue::ZGetInstance()->m_waitDiaMap.contains(frmSerialNo))
        {
            ZBaseInfoDia *dia=MyNetQueue::ZGetInstance()->m_waitDiaMap.value(frmSerialNo);
            dia->ZSetAckNetFrmXmlData(arrayFrmXmlData);
            emit this->ZSignalTxNetFrm(frmSerialNo);
        }
        //sub processed data.
        this->m_recvDataSize-=13+frmSize-4;
    }
    //move rest data.
    if(this->m_recvDataSize>0)
    {
        memmove(this->m_recvBuffer->data(),this->m_recvBuffer->data()+index,this->m_recvDataSize);
    }
}
PNetProTimeout::PNetProTimeout(QObject *parent)
{
    this->m_timer=NULL;
}
PNetProTimeout::~PNetProTimeout()
{
    if(this->m_timer)
    {
        delete this->m_timer;
    }
}
void PNetProTimeout::ZSlotStart()
{
    this->m_timer=new QTimer(this);
    connect(this->m_timer,SIGNAL(timeout()),this,SLOT(ZSlotScanWaitAckQueue()));
    this->m_timer->start(1000);
}
void PNetProTimeout::ZSlotScanWaitAckQueue()
{
    QList<qint32> removeIndexList;
    MyNetQueue::ZGetInstance()->m_mutexWaitAckQueue.lock();
    for(qint32 i=0;i<MyNetQueue::ZGetInstance()->m_waitAckQueue.count();i++)
    {
        PNetFrame *netFrm=MyNetQueue::ZGetInstance()->m_waitAckQueue.at(i);
        netFrm->ZIncWaitAckTimeoutCnt();
        qDebug()<<"timeoutCnt:"<<netFrm->ZGetWaitAckTimeoutCnt();
        if(netFrm->ZGetWaitAckTimeoutCnt()>10)
        {
            //call callback to parse ack netFrm.
            //            ZBaseInfoDia *dia=MyNetQueue::ZGetInstance()->m_waitDiaMap.value(netFrm->ZGetNetFrmSerialNo());
            //            dia->ZParseAckNetFrmXmlData(netFrm->ZGetNetFrmXmlData());
            //maybe timeout. should be removed.
            removeIndexList.append(i);
        }
    }
    for(qint32 i=0;i<removeIndexList.count();i++)
    {
        PNetFrame *netFrm=MyNetQueue::ZGetInstance()->m_waitAckQueue.at(i);

        MyNetQueue::ZGetInstance()->m_waitAckQueue.removeAt(i);
        //emit timeout signal to help close waiting dialog.
        emit this->ZSignalTxNetFrmTimeout(netFrm->ZGetNetFrmSerialNo());
        delete netFrm;
        netFrm=NULL;

    }
    MyNetQueue::ZGetInstance()->m_mutexWaitAckQueue.unlock();

    if(MyUserInfo::ZGetInstance()->m_bExitFlag)
    {
        this->m_timer->stop();
        emit this->ZSignalExit();
    }
}

PNetProcessor::PNetProcessor()
{
    this->m_thread=new QThread;
    this->m_netProtocol=new PNetProtocol;
    connect(this->m_thread,SIGNAL(started()),this->m_netProtocol,SLOT(ZSlotStart()));
    connect(this->m_netProtocol,SIGNAL(ZSignalTxNetFrm(qint32)),this,SLOT(ZSlotTxNetFrm(qint32)));
    this->m_netProtocol->moveToThread(this->m_thread);


    this->m_timeoutThread=new QThread;
    this->m_netTimeout=new PNetProTimeout;
    connect(this->m_timeoutThread,SIGNAL(started()),this->m_netTimeout,SLOT(ZSlotStart()));
    connect(this->m_netTimeout,SIGNAL(ZSignalTxNetFrmTimeout(qint32)),this,SLOT(ZSlotTxNetFrmTimeout(qint32)));
    this->m_netTimeout->moveToThread(this->m_timeoutThread);

    this->m_thread->start();
    this->m_timeoutThread->start();
}
PNetProcessor::~PNetProcessor()
{
    this->m_timeoutThread->quit();
    this->m_timeoutThread->wait(1000);
    this->m_thread->quit();
    this->m_thread->wait(1000);

    delete this->m_netProtocol;
    delete this->m_netTimeout;
    delete this->m_timeoutThread;
    delete this->m_thread;
}
void PNetProcessor::ZSlotTxNetFrm(qint32 serialNo)
{
    emit this->ZSignalTxNetFrmFinish(serialNo,0);
}
void PNetProcessor::ZSlotTxNetFrmTimeout(qint32 serialNo)
{
    emit this->ZSignalTxNetFrmFinish(serialNo,-1);
}
