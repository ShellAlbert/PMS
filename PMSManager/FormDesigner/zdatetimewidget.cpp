#include "zdatetimewidget.h"

ZDateTimeWidget::ZDateTimeWidget()
{
    this->m_dte=new QDateTimeEdit;
    this->m_dte->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    this->m_vLayout->addWidget(this->m_dte);
}
ZDateTimeWidget::~ZDateTimeWidget()
{
    delete this->m_dte;
}
void ZDateTimeWidget::ZOpenAttributeDialog()
{

}
