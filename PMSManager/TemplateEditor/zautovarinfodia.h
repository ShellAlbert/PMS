#ifndef ZAUTOVARINFODIA_H
#define ZAUTOVARINFODIA_H

#include <QDialog>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
class ZAutoVarInfoDia : public QDialog
{
    Q_OBJECT
public:
    ZAutoVarInfoDia(QWidget *parent=0);
    ~ZAutoVarInfoDia();

    QString ZGetVarName();
    void ZSetVarName(QString name);

    QString ZGetVarType();
    void ZSetVarType(QString type);

    QString ZGetVarAction();
    void ZSetVarAction(QString act);

    QString ZGetActionValue();
    void ZSetActionValue(QString value);
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
    void ZSlotActionValueChanged(QString text);
private:
    QLabel *m_lblVarName;
    QLineEdit *m_letVarName;

    QLabel *m_lblVarType;
    QComboBox *m_cbbVarType;

    QLabel *m_lblVarAction;
    QComboBox *m_cbbAction;

    QLabel *m_lblVarActValue;
    QComboBox *m_cbbVarActValue;
    QComboBox *m_cbbSysVar;
    QLineEdit *m_letVarActValue;

    QToolButton *m_btnOkay;
    QToolButton *m_btnCancel;

    QGridLayout *m_gridLayout;
};

#endif // ZAUTOVARINFODIA_H
