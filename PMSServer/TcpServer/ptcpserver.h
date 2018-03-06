#ifndef PTCPSERVER_H
#define PTCPSERVER_H

#include <QtNetwork/QTcpServer>
#include <QTcpSocket>
#include <QtSql/QSqlDatabase>
#include <QTimer>
#include <QMutex>
#include "NetPro/pnetpro.h"
#include <QThread>
class PTcpThread:public QThread
{
    Q_OBJECT
public:
    explicit PTcpThread(qint32 sockFd,QObject *parent = 0);

protected:
    void run();

signals:
    void ZSignalSocketLog(QString socketLogMsg);
    void ZSignalHeartBeat(QString addr,QString userName);
    void ZSignalUserLogin(QString addr,QString userName);
    void ZSignalUserLogout(QString addr,QString userName);

    void ZSignalTxData(QByteArray txData);
private slots:
    void ZSlotReadData();
    void ZSlotDisconnected();

    void ZSlotTimeoutTimer();

    void ZSlotHeartBeat(QString userName);
    void ZSlotUserLogin(QString userName);
    void ZSlotUserLogout(QString userName);
private:
    void ZParseRecvData();
    void ZTxAckNetFrm(QString xmlData,qint32 netFrmSerialNo);
private:
    //tcp socket.
    qint32 m_sockFd;
    QTcpSocket *m_tcpSocket;

    //network protocol.
    QByteArray *m_recvBuffer;
    qint32 m_recvDataSize;
    PNetPro *m_netPro;

    //timeout handler.
    qint32 m_timeoutCnt;
    QString m_IPPort;
    QTimer *m_timeoutTimer;

    //mysql database.
    QSqlDatabase m_mysqlDb;
};
class PTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit PTcpServer(QObject *parent = 0);
    ~PTcpServer();

signals:
    void ZSignalServerLog(QString logMsg);
    void ZSignalHeartBeat(QString addr,QString userName);
    void ZSignalUserLogin(QString addr,QString userName);
    void ZSignalUserLogout(QString addr,QString userName);
protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // PTCPSERVER_H
