#include "pwaitingdia.h"

PWaitingDia::PWaitingDia(QWidget *parent):QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("QDialog{background-color:#cce5f9;}");
    this->m_movie=new QMovie(":/gifs/images/gifs/loading.gif");
    this->m_llWaitGif=new QLabel;
    this->m_llWaitGif->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    this->m_llWaitGif->setMovie(this->m_movie);
    this->m_llMsg=new QLabel;
    this->m_llMsg->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_llWaitGif);
    this->m_vLayout->addWidget(this->m_llMsg);
    this->setLayout(this->m_vLayout);

    this->m_movie->start();
    this->m_refCount=1;

    this->m_timeoutEscape=0;
    this->m_timer=new QTimer;
    connect(this->m_timer,SIGNAL(timeout()),this,SLOT(ZSlotTimeout()));
    this->m_timer->start(1000);
}
PWaitingDia::~PWaitingDia()
{
    delete this->m_timer;
    delete this->m_movie;
    delete this->m_llWaitGif;
    delete this->m_llMsg;
    delete this->m_vLayout;
}
void PWaitingDia::ZSetTipsMsg(QString msg)
{
    this->m_tipsMsg=msg;
    this->ZSlotTimeout();
}
void PWaitingDia::ZSetRefCount(qint32 refCount)
{
    this->m_refCount=refCount;
}
qint32 PWaitingDia::ZGetRefCount()
{
    return this->m_refCount;
}
qint32 PWaitingDia::ZDecRefCount()
{
    this->m_refCount--;
    return this->m_refCount;
}
void PWaitingDia::ZStopMovie()
{
    this->m_movie->stop();
}
void PWaitingDia::ZSlotTimeout()
{
    this->m_timeoutEscape++;
    this->m_llMsg->setText(this->m_tipsMsg+QString("%1").arg(this->m_timeoutEscape));
}
