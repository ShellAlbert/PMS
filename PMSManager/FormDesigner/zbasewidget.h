#ifndef ZBASEWIDGET_H
#define ZBASEWIDGET_H

#include <QFrame>
#include <QVBoxLayout>
#include <QPaintEvent>
class ZBaseWidget:public QFrame
{
    Q_OBJECT
public:
    ZBaseWidget();
    ~ZBaseWidget();
    void ZSetEditMode(bool edit);
    bool ZGetIsEditMode();
    virtual void ZOpenAttributeDialog();
protected:
    void paintEvent(QPaintEvent *e);
public:
    QVBoxLayout *m_vLayout;
    bool m_editMode;
};

#endif // ZBASEWIDGET_H
