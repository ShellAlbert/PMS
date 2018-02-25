#ifndef ZSPINBOXDIA_H
#define ZSPINBOXDIA_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QGridLayout>
class ZSpinBoxDia : public QDialog
{
    Q_OBJECT
public:
    ZSpinBoxDia(QWidget *parent);
    ~ZSpinBoxDia();

    void ZSetMinValue(qint32 val);
    qint32 ZGetMinValue();

    void ZSetMaxValue(qint32 val);
    qint32 ZGetMaxValue();

    void ZSetDefaultValue(qint32 val);
    qint32 ZGetDefaultValue();

private slots:
    void ZSlotOkay();
    void ZSlotCancel();
private:
    QLabel *m_llMinValue;
    QLineEdit *m_leMinValue;

    QLabel *m_llMaxValue;
    QLineEdit *m_leMaxValue;

    QLabel *m_llDefaultValue;
    QLineEdit *m_leDefaultValue;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QGridLayout *m_gridLayout;
};

#endif // ZSPINBOXDIA_H
