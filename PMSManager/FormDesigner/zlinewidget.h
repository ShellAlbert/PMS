#ifndef ZLINEWIDGET_H
#define ZLINEWIDGET_H

#include <QPaintEvent>
#include <FormDesigner/zbasewidget.h>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QGridLayout>
#include <QDialog>
class ZLineDialog:public QDialog
{
    Q_OBJECT
public:
    ZLineDialog(QWidget *parent=0);
    ~ZLineDialog();

    qint32 ZGetWidth();
    void ZSetWidth(qint32 width);

    QColor ZGetColor();
    void ZSetColor(QColor color);
private slots:
    void ZSlotChangeColor();
private:
    QLabel *m_llWidth;
    QSpinBox *m_sbWidth;
    QLabel *m_llColor;
    QLineEdit *m_leColor;
    QToolButton *m_tbChange;
    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QGridLayout *m_gridLayout;

    QColor m_color;
};
class ZLineItem:public QWidget
{
public:
    ZLineItem();

    void ZSetWidth(qint32 width);
    qint32 ZGetWidth();

    void ZSetColor(QColor color);
    QColor ZGetColor();
protected:
    void paintEvent(QPaintEvent *e);
private:
    QColor m_color;
    qint32 m_width;
};
class ZLineWidget : public ZBaseWidget
{
    Q_OBJECT
public:
    ZLineWidget();
    ~ZLineWidget();
    void ZOpenAttributeDialog();
public:
    ZLineItem *m_lineItem;
};

#endif // ZLINEWIDGET_H
