#ifndef PWAITINGDIA_H
#define PWAITINGDIA_H

#include <QDialog>
#include <QLabel>
#include <QMovie>
#include <QTimer>
#include <QVBoxLayout>
class PWaitingDia : public QDialog
{
    Q_OBJECT
public:
    PWaitingDia(QWidget *parent=0);
    ~PWaitingDia();
    void ZSetTipsMsg(QString msg);
    void ZSetRefCount(qint32 refCount);
    qint32 ZGetRefCount();
    qint32 ZDecRefCount();
    void ZStopMovie();
private slots:
    void ZSlotTimeout();
private:
    QMovie *m_movie;
    QLabel *m_llWaitGif;
    QLabel *m_llMsg;
    QVBoxLayout *m_vLayout;
    qint32 m_refCount;

    QString m_tipsMsg;
    QTimer *m_timer;
    qint32 m_timeoutEscape;
};

#endif // PWAITINGDIA_H
