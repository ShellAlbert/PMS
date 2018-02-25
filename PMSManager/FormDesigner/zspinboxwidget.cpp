#include "zspinboxwidget.h"
ZSpinBoxWidget::ZSpinBoxWidget()
{
    this->m_sb=new QSpinBox;
    this->m_sb->setRange(0,100);
    this->m_sb->setValue(50);
    this->m_vLayout->addWidget(this->m_sb);
}
ZSpinBoxWidget::~ZSpinBoxWidget()
{
    delete this->m_sb;
}
void ZSpinBoxWidget::ZOpenAttributeDialog()
{

}
