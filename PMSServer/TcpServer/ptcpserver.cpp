#include "ptcpserver.h"
#include <QThread>
#include <QDebug>
#include <QPluginLoader>
#include <QSqlError>
#include <QTimer>
#include <NetPro/pnetfrmfile.h>
int QBytes2Int(QByteArray bytes) {
    int addr = bytes[0] & 0x000000FF;
    addr |= ((bytes[1] << 8) & 0x0000FF00);
    addr |= ((bytes[2] << 16) & 0x00FF0000);
    addr |= ((bytes[3] << 24) & 0xFF000000);
    return addr;
}
QByteArray Int2QByte(int number)
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[0] = (uchar)  (0x000000ff & number);
    abyte0[1] = (uchar) ((0x0000ff00 & number) >> 8);
    abyte0[2] = (uchar) ((0x00ff0000 & number) >> 16);
    abyte0[3] = (uchar) ((0xff000000 & number) >> 24);
    return abyte0;
}
PTcpThread::PTcpThread(qint32 sockFd,QObject *parent):QThread(parent)
{
    this->m_sockFd=sockFd;
}

void PTcpThread::run()
{
    //create a new tcp socket.
    this->m_tcpSocket=new QTcpSocket;
    if(!this->m_tcpSocket->setSocketDescriptor(this->m_sockFd))
    {
        emit this->ZSignalSocketLog(this->m_tcpSocket->errorString());
        return;
    }
    connect(this->m_tcpSocket,SIGNAL(readyRead()),this,SLOT(ZSlotReadData()),Qt::DirectConnection);
    connect(this->m_tcpSocket,SIGNAL(disconnected()),this,SLOT(ZSlotDisconnected()));
    qDebug()<<"client connected:"<<this->m_sockFd;
    this->m_IPPort=this->m_tcpSocket->peerAddress().toString()+":"+QString::number(this->m_tcpSocket->peerPort(),10);

    //open database connection.
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        this->m_mysqlDb=QSqlDatabase::database("qt_sql_default_connection");
    }else{
        this->m_mysqlDb=QSqlDatabase::addDatabase("QMYSQL");
    }
    this->m_mysqlDb.setHostName("127.0.0.1");
    this->m_mysqlDb.setPort(3306);
    this->m_mysqlDb.setUserName("root");
    this->m_mysqlDb.setPassword("123456");
    this->m_mysqlDb.setDatabaseName("pms");
    if(this->m_mysqlDb.open())
    {
        qDebug()<<"new client open PMS db ok!";
    }else{
        qDebug()<<"new client open PMS db failed";
        qDebug()<<this->m_mysqlDb.lastError();
        return;
    }

    //prepare network tcp protocols.
    this->m_recvBuffer=new QByteArray;
    this->m_recvBuffer->resize(2*1024*1024);
    this->m_recvDataSize=0;
    this->m_netPro=new PNetPro;
    connect(this->m_netPro,SIGNAL(ZSignalOpLog(QString)),this,SIGNAL(ZSignalSocketLog(QString)));
    connect(this->m_netPro,SIGNAL(ZSignalHeartBeat(QString)),this,SLOT(ZSlotHeartBeat(QString)));
    connect(this->m_netPro,SIGNAL(ZSignalUserLogin(QString)),this,SLOT(ZSlotUserLogin(QString)));
    connect(this->m_netPro,SIGNAL(ZSignalUserLogout(QString)),this,SLOT(ZSlotUserLogout(QString)));

    //create timeout counter.
    this->m_timeoutCnt=60;
    this->m_timeoutTimer=new QTimer;
    connect(this->m_timeoutTimer,SIGNAL(timeout()),this,SLOT(ZSlotTimeoutTimer()));
    this->m_timeoutTimer->start(200);

    //make this thread a event loop.
    this->exec();

    //clean resource after event loop.
    this->m_timeoutTimer->stop();
    delete this->m_timeoutTimer;
    this->m_tcpSocket->close();
    this->m_tcpSocket->deleteLater();

    delete this->m_recvBuffer;
    delete this->m_netPro;
    qDebug()<<"client thread exit:"<<this->m_sockFd;
}
void PTcpThread::ZSlotDisconnected()
{
    qDebug()<<"client disconnected:"<<this->m_sockFd;
    this->m_tcpSocket->deleteLater();
    //cause exec() to exit.
    this->exit(0);
}
void PTcpThread::ZSlotTimeoutTimer()
{
    if(this->m_netPro->ZGetLoginUserName().isEmpty())
    {
        qDebug()<<"No user login,timeout="<<this->m_timeoutCnt;
        if(this->m_timeoutCnt>0)
        {
            this->m_timeoutCnt--;
        }else{
            qDebug()<<"timeout to exit";
            //            emit this->ZSignalSocketLog(tr("client <%1:%2> no user login timeout,shutdown!").arg(this->m_tcpSocket->peerAddress().toString()).arg(this->m_netPro->ZGetLoginUserName()));
            //            emit this->ZSignalUserLogout(this->m_tcpSocket->peerAddress().toString(),"NoUserLogin");
            //cause exec() to exit.
            this->exit(-1);
        }
        return; // no user login.
    }

    if(this->m_timeoutCnt>0)
    {
        this->m_timeoutCnt--;
    }else{
        qDebug()<<"timeout to exit.";
        //timeout.long time to recv heart beat netFrm.
        //maybe socket is dead.close socket.
        //        emit this->ZSignalSocketLog(tr("client <%1:%2> active timeout,shutdown!").arg(this->m_tcpSocket->peerAddress().toString()).arg(this->m_netPro->ZGetLoginUserName()));
        //        emit this->ZSignalUserLogout(this->m_tcpSocket->peerAddress().toString(),this->m_netPro->ZGetLoginUserName());

        //cause exec() to exit.
        this->exit(-1);
    }
}
void PTcpThread::ZSlotUserLogin(QString userName)
{
    emit this->ZSignalUserLogin(this->m_IPPort,userName);
}
void PTcpThread::ZSlotUserLogout(QString userName)
{
    emit this->ZSignalUserLogout(this->m_IPPort,userName);
}
void PTcpThread::ZSlotHeartBeat(QString userName)
{
    emit this->ZSignalHeartBeat(this->m_IPPort,userName);
}
void PTcpThread::ZSlotReadData()
{
    qint32 nCanReadBytes;
    while(this->m_tcpSocket->bytesAvailable()>0)
    {
        //socket alive,reset timeout counter.
        this->m_timeoutCnt=60;

        //read data maximum.
        if((this->m_recvBuffer->size()-this->m_recvDataSize)>this->m_tcpSocket->bytesAvailable())
        {
            nCanReadBytes=this->m_tcpSocket->bytesAvailable();
        }else{
            nCanReadBytes=this->m_recvBuffer->size()-this->m_recvDataSize;
        }
        qint32 nRealReadBytes=this->m_tcpSocket->read(this->m_recvBuffer->data()+this->m_recvDataSize,nCanReadBytes);
        this->m_recvDataSize+=nRealReadBytes;
        //qDebug()<<"read:"<<nRealReadBytes<<",total:"<<this->m_recvDataSize;
        //qDebug()<<this->m_recvBuffer;
        this->ZParseRecvData();
    }
}
void PTcpThread::ZParseRecvData()
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
            qDebug()<<"we need more data:now:"<<this->m_recvDataSize;
            //we need more data.
            break;
        }
        //find sync header.
        index=this->m_recvBuffer->indexOf(arrayFrmSyncHeader,index);
        if(index<0)
        {
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
            index=0;//reset index.
            //qDebug()<<"we need more xml data!";
            break;
        }
        QByteArray arrayFrmXmlData=this->m_recvBuffer->mid(index,frmSize-4);
        //qDebug()<<QString(arrayFrmXmlData);
        index+=frmSize-4;
        //////////////////////////////////////////////////////////
        QString ackNetFrmXmlData=this->m_netPro->ZParseNetFrmXmlData(QString(arrayFrmXmlData),this->m_mysqlDb);
        this->ZTxAckNetFrm(ackNetFrmXmlData,frmSerialNo);
        //sub processed data.
        this->m_recvDataSize-=13+frmSize-4;
    }
    //move rest data.
    if(this->m_recvDataSize>0)
    {
        memmove(this->m_recvBuffer->data(),this->m_recvBuffer->data()+index,this->m_recvDataSize);
    }
}
void PTcpThread::ZTxAckNetFrm(QString xmlData,qint32 netFrmSerialNo)
{
    QString syncHeader("BePMS");//sync header.
    qint32 nfrmSize=0;//frame size.
    //frame serial No.
    //frame xml data.
    QByteArray frmSyncHeader=syncHeader.toUtf8();
    QByteArray frmSize=Int2QByte(nfrmSize);
    QByteArray frmSerialNo=Int2QByte(netFrmSerialNo);
    QByteArray frmXmlData=xmlData.toUtf8();

    nfrmSize=frmSerialNo.size()+frmXmlData.size();
    frmSize=Int2QByte(nfrmSize);

    QByteArray arrayTxData;
    arrayTxData.append(frmSyncHeader);//sync header.
    arrayTxData.append(frmSize);//frame size.
    arrayTxData.append(frmSerialNo);//frame serial no.
    arrayTxData.append(frmXmlData);//frame xml data.
    if(this->m_tcpSocket->isWritable())
    {
        this->m_tcpSocket->write(arrayTxData);
        this->m_tcpSocket->waitForBytesWritten();
    }
    return;
}
//////////////////////////////////////////////////////////////////////
/// \brief PTcpServer::PTcpServer
/// \param parent
//////////////////////////////////////////////////////////////////////////
PTcpServer::PTcpServer(QObject *parent) : QTcpServer(parent)
{
}
PTcpServer::~PTcpServer()
{
}
void PTcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"new connection:"<<socketDescriptor;
    PTcpThread *thread=new PTcpThread(socketDescriptor);
    //log message.
    connect(thread,SIGNAL(ZSignalSocketLog(QString)),this,SIGNAL(ZSignalServerLog(QString)));

    //heartbeat &login &logout signals.
    connect(thread,SIGNAL(ZSignalHeartBeat(QString,QString)),this,SIGNAL(ZSignalHeartBeat(QString,QString)));
    connect(thread,SIGNAL(ZSignalUserLogin(QString,QString)),this,SIGNAL(ZSignalUserLogin(QString,QString)));
    connect(thread,SIGNAL(ZSignalUserLogout(QString,QString)),this,SIGNAL(ZSignalUserLogout(QString,QString)));

    //once a thread is not needed, it will be beleted later
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));

    thread->start();
}

