#ifndef ZCOLORINFODIA_H
#define ZCOLORINFODIA_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QToolButton>
#include <QLineEdit>
#include <QGridLayout>
class ZColorInfoDia : public QDialog
{
    Q_OBJECT
public:
    ZColorInfoDia(QWidget *parent=0);
    ~ZColorInfoDia();

    void ZSetLeftTop(qint32 x,qint32 y);
    void ZSetRightBottom(qint32 x,qint32 y);

    QColor ZGetFgColor();
    void ZSetFgColor(QColor color);
    QColor ZGetBgColor();
    void ZSetBgColor(QColor color);

private slots:
    void ZSlotSelFgColor();
    void ZSlotSelBgColor();

    void ZSlotOkay();
    void ZSlotCancel();
private:

private:
    QLabel *m_llLeftTop;
    QLineEdit *m_leLeftTop;
    QLabel *m_llRightBottom;
    QLineEdit *m_leRightBottom;

    QLabel *m_llFgColor;
    QLineEdit *m_leFgColor;
    QToolButton *m_btnSelFgColor;

    QLabel *m_llBgColor;
    QLineEdit *m_leBgColor;
    QToolButton *m_btnSelBgColor;

    QToolButton *m_btnOkay;
    QToolButton *m_btnCancel;
    QGridLayout *m_gridLayout;

    QColor m_fgColor;
    QColor m_bgColor;
};

#endif // ZCOLORINFODIA_H
