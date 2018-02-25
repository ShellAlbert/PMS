#ifndef ZSPINBOXWIDGET_H
#define ZSPINBOXWIDGET_H

#include <QPaintEvent>
#include <FormDesigner/zbasewidget.h>
#include <QSpinBox>
class ZSpinBoxWidget : public ZBaseWidget
{
    Q_OBJECT
public:
    ZSpinBoxWidget();
    ~ZSpinBoxWidget();
    void ZOpenAttributeDialog();
private:
    QSpinBox *m_sb;
};
#endif // ZSPINBOXWIDGET_H
