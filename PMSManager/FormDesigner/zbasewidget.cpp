#include "zbasewidget.h"
#include <QPainter>
ZBaseWidget::ZBaseWidget()
{
    this->setStyleSheet("QFrame{background-color:transparent;}");
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->setContentsMargins(0,0,0,0);
    this->setLayout(this->m_vLayout);
    this->m_editMode=false;
}
ZBaseWidget::~ZBaseWidget()
{
    delete this->m_vLayout;
}
void ZBaseWidget::ZSetEditMode(bool edit)
{
    this->m_editMode=edit;
    this->update();
}
bool ZBaseWidget::ZGetIsEditMode()
{
    return this->m_editMode;
}
void ZBaseWidget::ZOpenAttributeDialog()
{

}
void ZBaseWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    if(this->m_editMode)
    {
        QPainter painter(this);
        QRect LeftTop(0,0,10,10);
        painter.fillRect(LeftTop,Qt::red);

        QRect RightTop(this->width()-10,0,10,10);
        painter.fillRect(RightTop,Qt::blue);

        QRect LeftBottom(0,this->height()-10,10,10);
        painter.fillRect(LeftBottom,Qt::green);

        QRect RightBottom(this->width()-10,this->height()-10,10,10);
        painter.fillRect(RightBottom,Qt::yellow);
    }
}
