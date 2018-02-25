#ifndef ZTEXTWIDGET_H
#define ZTEXTWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QToolButton>
#include <QGridLayout>
#include <QLineEdit>
#include <FormDesigner/zbasewidget.h>
class ZTextAttributeDialog:public QDialog
{
    Q_OBJECT
public:
    ZTextAttributeDialog(QWidget *parent=0);
    ~ZTextAttributeDialog();


    void ZSetText(QString text);
    QString ZGetText();

    void ZSetFontName(QString fontName);
    QString ZGetFontName();

    void ZSetFontSize(qint32 fontSize);
    qint32 ZGetFontSize();

    bool ZGetFontBold();
    void ZSetFontBold(bool bold);

    bool ZGetFontItalic();
    void ZSetFontItalic(bool italic);
private slots:
    void ZSlotUpdateFontSize(QString fontFamily);
private:
    QLabel *m_lblFontFamily;
    QComboBox *m_cbbFontFamily;

    QLabel *m_lblFontSize;
    QComboBox *m_cbbFontSize;

    QCheckBox *m_cbBold;
    QCheckBox *m_cbItalic;

    QLabel *m_llText;
    QLineEdit *m_leText;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QGridLayout *m_gridLayout;
};
class ZTextWidget:public ZBaseWidget
{
    Q_OBJECT
public:
    ZTextWidget();
    ~ZTextWidget();
    void ZOpenAttributeDialog();
public:
    QLabel *m_llText;
    QString m_fontName;
    qint32 m_fontSize;
    bool m_fontBold;
    bool m_fontItalic;
};
#endif // ZTEXTWIDGET_H
