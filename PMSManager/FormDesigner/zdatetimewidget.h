#ifndef ZDATETIMEWIDGET_H
#define ZDATETIMEWIDGET_H
#include <QPaintEvent>
#include <FormDesigner/zbasewidget.h>
#include <QDateTimeEdit>
class ZDateTimeWidget : public ZBaseWidget
{
    Q_OBJECT
public:
    ZDateTimeWidget();
    ~ZDateTimeWidget();
    void ZOpenAttributeDialog();
private:
    QDateTimeEdit *m_dte;
};
#endif // ZDATETIMEWIDGET_H
