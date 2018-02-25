#ifndef PNETPROTOCOL_H
#define PNETPROTOCOL_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QTimer>
#include <QThread>
class PNetProtocol : public QObject
{
    Q_OBJECT
public:
    explicit PNetProtocol(QObject *parent = 0);
    ~PNetProtocol();
signals:
    void ZSignalTxNetFrm(qint32 serialNo);
    void ZSignalExit();
public slots:
    void ZSlotStart();
    void ZSlotReadData();
    void ZSlotWriteData();
private:
    void ZParseRecvData();
private:
    QTcpSocket *m_tcpSocket;
    QTimer *m_timer;

    bool m_run;
    QByteArray *m_sendBuffer;

    QByteArray *m_recvBuffer;
    qint32 m_recvDataSize;
};
class PNetProTimeout:public QObject
{
    Q_OBJECT
public:
    explicit PNetProTimeout(QObject *parent = 0);
    ~PNetProTimeout();
signals:
    void ZSignalTxNetFrmTimeout(qint32 serialNo);
    void ZSignalExit();
public slots:
    void ZSlotStart();
    void ZSlotScanWaitAckQueue();
private:
    QTimer *m_timer;
};
class PNetProcessor:public QObject
{
    Q_OBJECT
public:
    PNetProcessor();
    ~PNetProcessor();
signals:
    void ZSignalTxNetFrmFinish(qint32 serialNo,qint32 retCode);
private slots:
    void ZSlotTxNetFrm(qint32 serialNo);
    void ZSlotTxNetFrmTimeout(qint32 serialNo);
private:
    QThread *m_thread;
    PNetProtocol *m_netProtocol;

    QThread *m_timeoutThread;
    PNetProTimeout *m_netTimeout;
};
#endif // PNETPROTOCOL_H
