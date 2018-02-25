#ifndef ZPROCESSINFODIA_H
#define ZPROCESSINFODIA_H

#include "BasePart/zbaseinfodia.h"
#include <QToolButton>
#include <QLineEdit>
class ZProcessInfoDia : public ZBaseInfoDia
{
    Q_OBJECT
public:
    typedef enum{
        Type_NewProcess=0,
        Type_DelProcess=1,
        Type_GetProcess=2,
        Type_SaveProcess=3,
    }ProcessInfoDiaType;
    ZProcessInfoDia(ProcessInfoDiaType type,QWidget *parent=0);
    ~ZProcessInfoDia();

    void ZSetProcessName(QString name);
    QString ZGetProcessName();

    void ZSetProcessXmlData(QString xmlData);
    QString ZGetProcessXmlData();
    void ZSetStepNum(qint32 stepNum);
    qint32 ZGetStepNum();

    void ZParseAckNetFrmXmlData();
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
private:
    QLabel *m_llProcessName;
    QLineEdit *m_leProcessName;

    QToolButton *m_btnOkay;
    QToolButton *m_btnCancel;

    QGridLayout *m_gridLayout;

    ProcessInfoDiaType m_diaType;

    //////////////////////
    QString m_processXmlData;
    qint32 m_stepNum;
};
#endif // ZPROCESSINFODIA_H
