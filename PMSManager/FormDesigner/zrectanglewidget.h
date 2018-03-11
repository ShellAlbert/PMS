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
private slots:
    void ZSlotChangeColor();
private:
    QLabel *m_llColor;
    QLineEdit *m_leColor;
    QToolButton *m_tbChange;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QGridLayout *m_gridLayout;

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
