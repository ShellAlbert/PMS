#ifndef ZRECTANGLEWIDGET_H
#define ZRECTANGLEWIDGET_H

#include <QPaintEvent>
#include <FormDesigner/zbasewidget.h>
#include <QToolButton>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGraphicsRectItem>
class ZRectangleDialog:public QDialog
{
    Q_OBJECT
public:
    ZRectangleDialog(QWidget *parent=0);
    ~ZRectangleDialog();

    QColor ZGetBackgroundColor();
    void ZSetBackgroundColor(QColor color);

    void ZSetXYSize(qint32 x,qint32 y,qint32 width,qint32 height);
    void ZGetXYSize(qint32 *x,qint32 *y,qint32 *width,qint32 *height);
private slots:
    void ZSlotChangeColor();
private:
    QLabel *m_llColor;
    QLineEdit *m_leColor;
    QToolButton *m_tbChange;

    QLabel *m_llX;
    QLineEdit *m_leX;
    QLabel *m_llY;
    QLineEdit *m_leY;
    QLabel *m_llWidth;
    QLineEdit *m_leWidth;
    QLabel *m_llHeight;
    QLineEdit *m_leHeight;
    QGridLayout *m_gridLayout;


    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayout;
    QVBoxLayout *m_vLayout;

    QColor m_color;
};
class ZRectangleWidget : public ZBaseWidget
{
    Q_OBJECT
public:
    ZRectangleWidget();
    ~ZRectangleWidget();
    void ZOpenAttributeDialog();
    QColor ZGetColor();
    void ZSetColor(QColor color);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QColor m_color;
};
#endif // ZRECTANGLEWIDGET_H
