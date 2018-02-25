#include "zbaseinfodia.h"
#include <QDateTime>
#include <QDebug>
ZBaseInfoDia::ZBaseInfoDia(ZDialogEndType type,QWidget *parent):QDialog(parent)
{
    this->m_dialogEndType=type;
    this->m_waitDia=new PWaitingDia;
    this->m_ackNetFrmProcessWidget=NULL;
}
ZBaseInfoDia::~ZBaseInfoDia()
{
    delete this->m_waitDia;
}
QSize ZBaseInfoDia::sizeHint() const
{
    return QSize(200,100);
}
void ZBaseInfoDia::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(e);
        break;
    }
}
void ZBaseInfoDia::ZHideAllDialog()
{
    this->m_waitDia->hide();
    this->hide();
}
ZBaseInfoDia::ZDialogEndType ZBaseInfoDia::ZGetDialogType()
{
    return this->m_dialogEndType;
}
void ZBaseInfoDia::ZSetAckNetFrmXmlData(QString xmlData)
{
    this->m_ackNetFrmXmlData=xmlData;
}
void ZBaseInfoDia::ZParseAckNetFrmXmlData()
{

}
void ZBaseInfoDia::ZShowWaitingDialog()
{
    this->hide();
    this->m_waitDia->setModal(true);
    this->m_waitDia->show();
}
qint32 ZBaseInfoDia::ZShowWorkingDialog()
{
    qint32 ret=0;
    qint32 retCode;
    this->m_waitDia->hide();
    this->show();
    retCode=this->exec();
    switch(retCode)
    {
    case QDialog::Accepted:
        this->ZShowWaitingDialog();
        ret=0;
        break;
    case QDialog::Rejected:
        ret=-1;
        break;
    }
    return ret;
}
void ZBaseInfoDia::ZSetAckNetFrmProcessWidget(ZAckNetFrmWidget *widget)
{
    this->m_ackNetFrmProcessWidget=widget;
}
ZAckNetFrmWidget* ZBaseInfoDia::ZGetAckNetFrmProcessWidget()
{
    return this->m_ackNetFrmProcessWidget;
}
void ZBaseInfoDia::ZEmitOpFinishedSignal(qint32 retCode)
{
    emit this->ZSignalOpFinished(retCode);
}
