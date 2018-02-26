#ifndef PTCPSERVER_H
#define PTCPSERVER_H

#include <QtNetwork/QTcpServer>
#include <QTcpSocket>
#include <QtSql/QSqlDatabase>
#include <QTimer>
#include <QMutex>
#include "NetPro/pnetpro.h"
class PTcpSocket:public QTcpSocket
{
    Q_OBJECT
public:
    explicit PTcpSocket(qint32 sockFd,QObject *parent = 0);
    ~PTcpSocket();
public slots:
    void ZSlotDoInitial();
signals:
    void ZSignalSocketLog(QString socketLogMsg);
    void ZSignalHeartBeat(QString addr,QString userName);
    void ZSignalUserLogin(QString addr,QString userName);
    void ZSignalUserLogout(QString addr,QString userName);
private slots:
    void ZSlotReadData();
    void ZSlotTimeoutTimer();
    void ZSlotHeartBeat(QString userName);
    void ZSlotUserLogin(QString userName);
    void ZSlotUserLogout(QString userName);
private:
    void ZParseRecvData();
    void ZTxAckNetFrm(QString xmlData,qint32 netFrmSerialNo);
private:
    qint32 m_sockFd;
    QByteArray *m_recvBuffer;
    qint32 m_recvDataSize;
    PNetPro *m_netPro;

private:
    QTimer *m_timeoutTimer;
    qint32 m_timeoutCnt;
private:
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
private:
    QMap<QString,PTcpSocket*> m_tcpSocketMap;
};

#endif // PTCPSERVER_H
