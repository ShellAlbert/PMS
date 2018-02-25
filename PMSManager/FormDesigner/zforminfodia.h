#ifndef ZFORMINFODIA_H
#define ZFORMINFODIA_H

#include "BasePart/zbaseinfodia.h"
#include <QToolButton>
#include <QLineEdit>
#include <QGridLayout>
class ZFormInfoDia : public ZBaseInfoDia
{
    Q_OBJECT
public:
    typedef enum{
        Type_NewForm=0,
        Type_DelForm=1,
        Type_GetForm=2,
        Type_SaveForm=3,
    }FormInfoDiaType;
    ZFormInfoDia(FormInfoDiaType type,QWidget *parent=0);
    ~ZFormInfoDia();

    void ZSetFormName(QString name);
    QString ZGetFormName();

    void ZSetFormXmlData(QString data);

    void ZParseAckNetFrmXmlData();
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
private:
    QLabel *m_llFormName;
    QLineEdit *m_leFormName;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QGridLayout *m_gridLayout;
    FormInfoDiaType m_diaType;

    QString m_formXmlData;
};
#endif // ZFORMINFODIA_H
