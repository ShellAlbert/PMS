#ifndef ZVARSOURCEINFODIA_H
#define ZVARSOURCEINFODIA_H

#include "BasePart/zbaseinfodia.h"
#include <QToolButton>
#include <QLineEdit>
#include <QGridLayout>
class ZVarSourceInfoDia : public ZBaseInfoDia
{
    Q_OBJECT
public:
    typedef enum{
        Type_NewVarSource=0,
        Type_DelVarSource=1,
        Type_GetVarSource=2,
        Type_SaveVarSource=3,
    }VarSourceInfoDiaType;
    ZVarSourceInfoDia(VarSourceInfoDiaType type,QWidget *parent=0);
    ~ZVarSourceInfoDia();

    void ZSetVarSourceName(QString name);
    QString ZGetVarSourceName();
    void ZSetVarSourceXmlData(QString xmlData);

    void ZParseAckNetFrmXmlData();
protected:

private slots:
    void ZSlotOkay();
    void ZSlotCancel();
private:
    QLabel *m_llVarSourceName;
    QLineEdit *m_leVarSourceName;
    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QGridLayout *m_gridLayout;
    VarSourceInfoDiaType m_diaType;

    QString m_varSourceXmlData;
};

#endif // ZVARSOURCEINFODIA_H
