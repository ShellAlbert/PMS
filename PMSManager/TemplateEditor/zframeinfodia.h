#ifndef ZFRAMEINFODIA_H
#define ZFRAMEINFODIA_H

#include <QDialog>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QCheckBox>
class ZFrameInfoDia : public QDialog
{
    Q_OBJECT
public:
    ZFrameInfoDia(QWidget *parent=0);
    ~ZFrameInfoDia();

    void ZSetLeftTop(qint32 x,qint32 y);
    void ZSetRightBottom(qint32 x,qint32 y);

    void ZSetFrameColor(QColor frameColor);
    QColor ZGetFrameColor();

    bool ZTopFrameIsSet();
    void ZSetTopFrame(bool bFrame);

    bool ZBottomFrameIsSet();
    void ZSetBottomFrame(bool bFrame);

    bool ZLeftFrameIsSet();
    void ZSetLeftFrame(bool bFrame);

    bool ZRightFrameIsSet();
    void ZSetRightFrame(bool bFrame);

    //frame width.
    void ZSetFrameWidth(qint32 frameWidth);
    qint32 ZGetFrameWidth();

private slots:
    void ZSlotChangeColor();
    void ZSlotOkay();
    void ZSlotCancel();
private:
    void ZUpdateFrameColor(QColor color);
private:
    QLabel *m_llLeftTop;
    QLineEdit *m_leLeftTop;

    QLabel *m_llRightBottom;
    QLineEdit *m_leRightBottom;

    QCheckBox *m_cbTop;
    QCheckBox *m_cbBottom;
    QCheckBox *m_cbLeft;
    QCheckBox *m_cbRight;

    QLabel *m_llFrameColor;
    QLineEdit *m_leFrameColor;
    QToolButton *m_tbSelColor;

    QLabel *m_llFrameWidth;
    QSpinBox *m_sbFrameWidth;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QGridLayout *m_gridLayout;

    QColor m_frameColor;
};

#endif // ZFRAMEINFODIA_H
