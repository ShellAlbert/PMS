#ifndef ZCHECKBOXWIDGET_H
#define ZCHECKBOXWIDGET_H

#include <QPaintEvent>
#include <FormDesigner/zbasewidget.h>
#include <QCheckBox>
class ZCheckBoxWidget : public ZBaseWidget
{
    Q_OBJECT
public:
    ZCheckBoxWidget();
    ~ZCheckBoxWidget();
    void ZOpenAttributeDialog();
public:
    QCheckBox *m_cb;
};
#endif // ZCHECKBOXWIDGET_H
