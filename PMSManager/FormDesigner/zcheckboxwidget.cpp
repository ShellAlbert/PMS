#include "zcheckboxwidget.h"

ZCheckBoxWidget::ZCheckBoxWidget()
{
    this->m_cb=new QCheckBox;
    this->m_cb->setChecked(true);
    this->m_cb->setText(tr("复选框"));
    this->m_vLayout->addWidget(this->m_cb);
}
ZCheckBoxWidget::~ZCheckBoxWidget()
{
    delete this->m_cb;
}
void ZCheckBoxWidget::ZOpenAttributeDialog()
{

}
