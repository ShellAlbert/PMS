#include "ptcpserver.h"
#include <QThread>
#include <QDebug>
#include <QPluginLoader>
#include <QSqlError>
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
PTcpSocket::PTcpSocket(qint32 sockFd,QObject *parent):QTcpSocket(parent)
{
    this->m_recvBuffer=new QByteArray;
    this->m_recvBuffer->resize(2*1024*1024);
    this->m_recvDataSize=0;
    this->m_netPro=new PNetPro;
    connect(this->m_netPro,SIGNAL(ZSignalOpLog(QString)),this,SIGNAL(ZSignalSocketLog(QString)));
    connect(this->m_netPro,SIGNAL(ZSignalHeartBeat(QString)),this,SLOT(ZSlotHeartBeat(QString)));
    connect(this->m_netPro,SIGNAL(ZSignalUserLogin(QString)),this,SLOT(ZSlotUserLogin(QString)));
    connect(this->m_netPro,SIGNAL(ZSignalUserLogout(QString)),this,SLOT(ZSlotUserLogout(QString)));

    this->m_mysqlDb=QSqlDatabase::addDatabase("QMYSQL");
    this->m_mysqlDb.setHostName("127.0.0.1");
    this->m_mysqlDb.setPort(3306);
    this->m_mysqlDb.setUserName("root");
    this->m_mysqlDb.setPassword("123456");
    this->m_mysqlDb.setDatabaseName("pms");
    if(this->m_mysqlDb.open())
    {
        qDebug()<<"open ok!";
    }else{
        qDebug()<<"open failed";
        qDebug()<<this->m_mysqlDb.lastError();
    }

    this->m_sockFd=sockFd;
    this->setSocketDescriptor(sockFd);
    connect(this,SIGNAL(readyRead()),this,SLOT(ZSlotReadData()));

    this->m_timeoutCnt=60;
}
PTcpSocket::~PTcpSocket()
{
    delete this->m_timeoutTimer;
    delete this->m_recvBuffer;
    delete this->m_netPro;
}
void PTcpSocket::ZSlotDoInitial()
{
    this->m_timeoutCnt=120;
    this->m_timeoutTimer=new QTimer;
    connect(this->m_timeoutTimer,SIGNAL(timeout()),this,SLOT(ZSlotTimeoutTimer()));
    this->m_timeoutTimer->start(1000);
}
void PTcpSocket::ZSlotTimeoutTimer()
{
    if(this->m_netPro->ZGetLoginUserName().isEmpty())
    {
        return; // no user login.
    }

    if(this->m_timeoutCnt>0)
    {
        this->m_timeoutCnt--;
    }else{
        //timeout.long time to recv heart beat netFrm.
        //maybe socket is dead.close socket.
        emit this->ZSignalSocketLog(tr("client <%1:%2> active timeout,shutdown!").arg(this->peerAddress().toString()).arg(this->m_netPro->ZGetLoginUserName()));
        emit this->ZSignalUserLogout(this->peerAddress().toString(),this->m_netPro->ZGetLoginUserName());
        this->close();
    }
}
void PTcpSocket::ZSlotUserLogin(QString userName)
{
    emit this->ZSignalUserLogin(this->peerAddress().toString(),userName);
}
void PTcpSocket::ZSlotUserLogout(QString userName)
{
    emit this->ZSignalUserLogout(this->peerAddress().toString(),userName);
}
void PTcpSocket::ZSlotHeartBeat(QString userName)
{
    emit this->ZSignalHeartBeat(this->peerAddress().toString(),userName);
}
void PTcpSocket::ZSlotReadData()
{
    qint32 nCanReadBytes;
    while(this->bytesAvailable()>0)
    {
        //socket alive,reset timeout counter.
        this->m_timeoutCnt=120;

        //read data maximum.
        if((this->m_recvBuffer->size()-this->m_recvDataSize)>this->bytesAvailable())
        {
            nCanReadBytes=this->bytesAvailable();
        }else{
            nCanReadBytes=this->m_recvBuffer->size()-this->m_recvDataSize;
        }
        qint32 nRealReadBytes=this->read(this->m_recvBuffer->data()+this->m_recvDataSize,nCanReadBytes);
        this->m_recvDataSize+=nRealReadBytes;
        //qDebug()<<"read:"<<nRealReadBytes<<",total:"<<this->m_recvDataSize;
        //qDebug()<<this->m_recvBuffer;
        this->ZParseRecvData();
    }
}
void PTcpSocket::ZParseRecvData()
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
void PTcpSocket::ZTxAckNetFrm(QString xmlData,qint32 netFrmSerialNo)
{
    QString syncHeader("BePMS");//sync header.
    qint32 nfrmSize;//frame size.
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
    this->write(arrayTxData);
    this->waitForBytesWritten();
}

PTcpServer::PTcpServer(QObject *parent) : QTcpServer(parent)
{
}
PTcpServer::~PTcpServer()
{
}
void PTcpServer::incomingConnection(qintptr socketDescriptor)
{
    //qDebug()<<"new connection:"<<socketDescriptor;
    PTcpSocket *tcpSocket=new PTcpSocket(socketDescriptor);
    connect(tcpSocket,SIGNAL(ZSignalSocketLog(QString)),this,SIGNAL(ZSignalServerLog(QString)));
    connect(tcpSocket,SIGNAL(ZSignalHeartBeat(QString,QString)),this,SIGNAL(ZSignalHeartBeat(QString,QString)));
    connect(tcpSocket,SIGNAL(ZSignalUserLogin(QString,QString)),this,SIGNAL(ZSignalUserLogin(QString,QString)));
    connect(tcpSocket,SIGNAL(ZSignalUserLogout(QString,QString)),this,SIGNAL(ZSignalUserLogout(QString,QString)));

    QThread *tcpThread=new QThread;
    connect(tcpThread,SIGNAL(started()),tcpSocket,SLOT(ZSlotDoInitial()));
    connect(tcpSocket,SIGNAL(disconnected()),tcpThread,SLOT(terminate()));
    connect(tcpThread,SIGNAL(finished()),tcpThread,SLOT(deleteLater()));
    connect(tcpThread,SIGNAL(finished()),tcpSocket,SLOT(deleteLater()));
    tcpSocket->moveToThread(tcpThread);
    tcpThread->start();
}
