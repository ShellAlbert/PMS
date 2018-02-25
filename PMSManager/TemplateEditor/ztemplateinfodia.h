#ifndef ZTEMPLATEINFODIA_H
#define ZTEMPLATEINFODIA_H

#include "BasePart/zbaseinfodia.h"
#include <QToolButton>
#include <QLineEdit>
#include <QGridLayout>
class ZTemplateInfoDia : public ZBaseInfoDia
{
    Q_OBJECT
public:
    typedef enum{
        Type_NewTemplate=0,
        Type_DelTemplate=1,
        Type_GetTemplate=2,
        Type_SaveTemplate=3,
        Type_BindVarSource=4,
        Type_UnbindVarSource=5,
    }TemplateInfoDiaType;
    ZTemplateInfoDia(TemplateInfoDiaType type,QWidget *parent=0);
    ~ZTemplateInfoDia();

    void ZSetTemplateName(QString name);
    QString ZGetTemplateName();
    void ZSetTemplateXmlData(QString templateXmlDta);

    void ZSetVarSourceName(QString name);
    QString ZGetVarSourceName();

    void ZParseAckNetFrmXmlData();
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
private:
    QLabel *m_llTemplateName;
    QLineEdit *m_leTempalteName;
    QLabel *m_llVarSourcName;
    QLineEdit *m_leVarSourceName;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QGridLayout *m_gridLayout;
    TemplateInfoDiaType m_diaType;

    QString m_templateXmlData;
};

#endif // ZTEMPLATEINFODIA_H
