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
        Type_SaveAsTemplate=6,
    }TemplateInfoDiaType;
    ZTemplateInfoDia(TemplateInfoDiaType type,QWidget *parent=0);
    ~ZTemplateInfoDia();

    void ZSetTemplateName(QString name);
    QString ZGetTemplateName();
    void ZSetTemplateXmlData(QString templateXmlDta);
    void ZSetDestMinMaxCmpXmlData(QString destMinMaxXml);
    void ZSetPreSetProductNo(QString productNoXml);
    void ZSetAutoFillProductNo(QString productNoXml);

    QString ZGetSaveAsTemplateName();

    void ZSetVarSourceName(QString name);
    QString ZGetVarSourceName();

    void ZParseAckNetFrmXmlData();
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
private:
    QLabel *m_llOpTips;

    QLabel *m_llTemplateName;
    QLineEdit *m_leTempalteName;
    QLabel *m_llSaveAsTemplateName;
    QLineEdit *m_leSaveAsTempalteName;
    QLabel *m_llVarSourcName;
    QLineEdit *m_leVarSourceName;
    QGridLayout *m_gridLayout;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayoutBtn;

    QVBoxLayout *m_vLayout;
    //dialog type.
    TemplateInfoDiaType m_diaType;
    QString m_templateXmlData;
    QString m_destMinMaxXmlData;
    QString m_productNoXmlData;
    QString m_productNoAutoFill;
};

#endif // ZTEMPLATEINFODIA_H
