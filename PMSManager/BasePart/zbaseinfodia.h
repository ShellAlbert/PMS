#ifndef ZBASEINFODIA_H
#define ZBASEINFODIA_H

#include <QDialog>
#include <QTextEdit>
#include "pwaitingdia.h"
#include "NetProtocol/pnetframe.h"
#include <QQueue>
#include "pgblpara.h"
class PNetFrame;
class ZBaseInfoDia : public QDialog
{
    Q_OBJECT
public:
    typedef enum{
        Dialog_End_By_Calling_Close=0,
        Dialog_End_By_Emitting_Signal=1,
        Dialog_End_By_Auto_Close=2,
        Dialog_End_By_SubPart=3,
    }ZDialogEndType;
    ZBaseInfoDia(ZDialogEndType type,QWidget *parent=0);
    ~ZBaseInfoDia();
    PWaitingDia* m_waitDia;
    qint32 ZShowWorkingDialog();
    void ZShowWaitingDialog();
    void ZHideAllDialog();

    ZDialogEndType ZGetDialogType();

    void ZSetAckNetFrmXmlData(QString xmlData);
    virtual void ZParseAckNetFrmXmlData();
    QString m_ackNetFrmXmlData;

    QQueue<PNetFrame*> m_netFrmQueue;

    void ZEmitOpFinishedSignal(qint32 retCode);
signals:
    void ZSignalOpFinished(qint32 retCode);
protected:
    QSize sizeHint() const;
    void keyPressEvent(QKeyEvent *e);
public:
    void ZSetAckNetFrmProcessWidget(ZAckNetFrmWidget *widget);
    ZAckNetFrmWidget* ZGetAckNetFrmProcessWidget();
private:
    ZAckNetFrmWidget *m_ackNetFrmProcessWidget;

private:
    ZDialogEndType m_dialogEndType;
};

#endif // ZBASEINFODIA_H
