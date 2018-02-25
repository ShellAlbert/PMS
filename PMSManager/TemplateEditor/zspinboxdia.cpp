#include "zspinboxdia.h"

ZSpinBoxDia::ZSpinBoxDia(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("选值框对话框"));

    this->m_llMinValue=new QLabel(tr("最小值"));
    this->m_leMinValue=new QLineEdit;

    this->m_llMaxValue=new QLabel(tr("最大值"));
    this->m_leMaxValue=new QLineEdit;

    this->m_llDefaultValue=new QLabel(tr("默认值"));
    this->m_leDefaultValue=new QLineEdit;

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llMinValue,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leMinValue,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_llMaxValue,0,2,1,1);
    this->m_gridLayout->addWidget(this->m_leMaxValue,0,3,1,1);

    this->m_gridLayout->addWidget(this->m_llDefaultValue,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_leDefaultValue,1,1,1,1);

    this->m_gridLayout->addWidget(this->m_tbOkay,2,2,1,1);
    this->m_gridLayout->addWidget(this->m_tbCancel,2,3,1,1);

    this->setLayout(this->m_gridLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
}
ZSpinBoxDia::~ZSpinBoxDia()
{
    delete this->m_llMinValue;
    delete this->m_leMinValue;

    delete this->m_llMaxValue;
    delete this->m_leMaxValue;

    delete this->m_llDefaultValue;
    delete this->m_leDefaultValue;

    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gridLayout;
}
void ZSpinBoxDia::ZSlotOkay()
{
    this->accept();
}
void ZSpinBoxDia::ZSlotCancel()
{
    this->reject();
}
void ZSpinBoxDia::ZSetMinValue(qint32 val)
{
    this->m_leMinValue->setText(QString("%1").arg(val));
}
qint32 ZSpinBoxDia::ZGetMinValue()
{
    return this->m_leMinValue->text().trimmed().toInt();
}

void ZSpinBoxDia::ZSetMaxValue(qint32 val)
{
    this->m_leMaxValue->setText(QString("%1").arg(val));
}
qint32 ZSpinBoxDia::ZGetMaxValue()
{
    return this->m_leMaxValue->text().trimmed().toInt();
}

void ZSpinBoxDia::ZSetDefaultValue(qint32 val)
{
    this->m_leDefaultValue->setText(QString("%1").arg(val));
}
qint32 ZSpinBoxDia::ZGetDefaultValue()
{
    return this->m_leDefaultValue->text().trimmed().toInt();
}
