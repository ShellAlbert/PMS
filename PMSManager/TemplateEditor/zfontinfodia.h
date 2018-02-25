#ifndef ZFONTINFODIA_H
#define ZFONTINFODIA_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QToolButton>
#include <QLineEdit>
#include <QGridLayout>
class ZFontInfoDia : public QDialog
{
    Q_OBJECT
public:
    ZFontInfoDia(QWidget *parent=0);
    ~ZFontInfoDia();

    QString ZGetFontFamily();
    void ZSetFontFamily(QString fontFamily);

    qint32 ZGetFontSize();
    void ZSetFontSize(qint32 fontSize);

    bool ZFontIsBold();
    void ZSetFontBold(bool bold);

    bool ZFontIsItalic();
    void ZSetFontItalic(bool italic);

    void ZSetLeftTop(qint32 x,qint32 y);
    void ZSetRightBottom(qint32 x,qint32 y);
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
    void ZSlotUpdateFontSize(QString fontFamily);
private:
    QLabel *m_lblLeftTop;
    QLineEdit *m_leLeftTop;
    QLabel *m_lblRightBottom;
    QLineEdit *m_leRightBottom;

    QLabel *m_lblFontFamily;
    QComboBox *m_cbbFontFamily;

    QLabel *m_lblFontSize;
    QComboBox *m_cbbFontSize;

    QCheckBox *m_cbBold;
    QCheckBox *m_cbItalic;

    QToolButton *m_btnOkay;
    QToolButton *m_btnCancel;
    QGridLayout *m_gridLayout;
};

#endif // ZFONTINFODIA_H
