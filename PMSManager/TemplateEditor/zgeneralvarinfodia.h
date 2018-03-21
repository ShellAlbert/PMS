#ifndef ZGENERALVARINFODIA_H
#define ZGENERALVARINFODIA_H

#include <QDialog>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QDateTimeEdit>
class ZGeneralVarInfoDia : public QDialog
{
    Q_OBJECT
public:
    ZGeneralVarInfoDia(QWidget *parent=0);
    ~ZGeneralVarInfoDia();

    QString ZGetVarName();
    void ZSetVarName(QString name);

    QString ZGetVarType();
    void ZSetVarType(QString type);

    QString ZGetVarRule();
    void ZSetVarRule(QString rule);

    QString ZGetRefValue();
    void ZSetRefValue(QString val);
private slots:
    void ZSlotDataTypeChanged(QString type);
    void ZSlotOkay();
    void ZSlotCancel();
private:
    QLabel *m_lblVarName;
    QLineEdit *m_letVarName;

    QLabel *m_lblVarType;
    QComboBox *m_cbbVarType;

    //for String.
    QLabel *m_lblRefValue;
    QLineEdit *m_leRefValue;

    //for Digital
    QLabel *m_lblVarRange;
    QLabel *m_lblVarMin;
    QLineEdit *m_letVarMin;
    QLabel *m_lblVarMax;
    QLineEdit *m_letVarMax;
    QLabel *m_lblDigitalRefVal;
    QLineEdit *m_leDigitalRefVal;

    //for Datetime.
    QLabel *m_lblStartTime;
    QDateTimeEdit *m_dtStart;
    QLabel *m_lblEndTime;
    QDateTimeEdit *m_dtEnd;
    QDateTimeEdit *m_dtRefVal;

    //for boolean.
    QLabel *m_lblBoolean;
    QComboBox *m_cbBoolean;

    QToolButton *m_btnOkay;
    QToolButton *m_btnCancel;

    QGridLayout *m_gridLayout;
};

#endif // ZGENERALVARINFODIA_H
