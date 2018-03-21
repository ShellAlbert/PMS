#ifndef ZTASKINFODIA_H
#define ZTASKINFODIA_H
#include "BasePart/zbaseinfodia.h"
#include <QToolButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
class ZTaskInfoDia : public ZBaseInfoDia
{
    Q_OBJECT
public:
    typedef enum{
        Type_NewTask=0,
        Type_OpenTask=1,
        Type_SaveTask=2,
        Type_DelTask=3,
        Type_SubmitTask=4,
        Type_WithdrawTask=5,
        Type_CheckOkayTask=6,
        Type_CheckFailedTask=7,
        Type_ArchieveTask=8,
    }TaskInfoDiaType;
    ZTaskInfoDia(TaskInfoDiaType type,QWidget *parent=0);
    ~ZTaskInfoDia();

    void ZSetTaskName(QString taskName);
    QString ZGetTaskName();

    void ZSetRefTemplateName(QString templateName);
    QString ZGetRefTemplateName();

    void ZSetProcessName(QString processName);
    QString ZGetProcessName();

    void ZSetStepName(QString stepName);
    QString ZGetStepName();

    void ZSetTaskValueXmlData(QString xmlData);

    void ZSetTaskAuxData(QStringList auxList);

    void ZParseAckNetFrmXmlData();
protected:
    QSize sizeHint() const;
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
private:

    QLabel *m_llOpTips;

    QLabel *m_llTaskName;
    QLineEdit *m_leTaskName;
    QLabel *m_llRefTemplateName;
    QLineEdit *m_leRefTemplateName;
    QLabel *m_llProcessName;
    QLineEdit *m_leProcessName;
    QLabel *m_llStepName;
    QLineEdit *m_leStepName;
    QGridLayout *m_gridLayout;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayoutBtn;

    //main layout
    QVBoxLayout *m_vLayout;

    //task dialog type.
    TaskInfoDiaType m_diaType;

    QString m_taskValueXmlData;
    QStringList m_auxList;
};

#endif // ZTASKINFODIA_H
