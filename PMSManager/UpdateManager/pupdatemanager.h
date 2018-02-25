#ifndef PUPDATEMANAGER_H
#define PUPDATEMANAGER_H

#include <QDialog>
#include <QTcpSocket>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QLabel>
class PUpdateManager : public QDialog
{
    Q_OBJECT
public:
    PUpdateManager(QWidget *parent=0);
    ~PUpdateManager();
private slots:
    void ZSlotDisconnect();
    void ZSlotCommunicate();
private:
    QString m_version;
    QString m_versionS;

    QTcpSocket *m_tcpSocket;
    quint64 m_nextBlockSize;
    qint32 m_byteWritten;

    QProgressBar *m_bar;
    QLabel *m_llInfo;
    QVBoxLayout *m_vLayout;
};

#endif // PUPDATEMANAGER_H
