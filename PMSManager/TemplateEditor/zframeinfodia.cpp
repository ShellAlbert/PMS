#include "zframeinfodia.h"
#include <QColorDialog>
ZFrameInfoDia::ZFrameInfoDia(QWidget *parent):QDialog(parent)
{
    this->m_llLeftTop=new QLabel(tr("左上角"));
    this->m_leLeftTop=new QLineEdit;
    this->m_leLeftTop->setEnabled(false);

    this->m_llRightBottom=new QLabel(tr("右下角"));
    this->m_leRightBottom=new QLineEdit;
    this->m_leRightBottom->setEnabled(false);

    this->m_cbTop=new QCheckBox(tr("上边框"));
    this->m_cbBottom=new QCheckBox(tr("下边框"));
    this->m_cbLeft=new QCheckBox(tr("左边框"));
    this->m_cbRight=new QCheckBox(tr("右边框"));

    this->m_llFrameColor=new QLabel(tr("线条颜色"));
    this->m_leFrameColor=new QLineEdit;
    this->m_tbSelColor=new QToolButton;
    this->m_tbSelColor->setText(tr("更改..."));

    this->m_llFrameWidth=new QLabel(tr("线条宽度"));
    this->m_sbFrameWidth=new QSpinBox;
    this->m_sbFrameWidth->setRange(1,100);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));

    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));

    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llLeftTop,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leLeftTop,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_llRightBottom,0,3,1,1);
    this->m_gridLayout->addWidget(this->m_leRightBottom,0,4,1,1);

    this->m_gridLayout->addWidget(this->m_cbTop,1,2,1,1);
    this->m_gridLayout->addWidget(this->m_cbLeft,2,1,1,1);
    this->m_gridLayout->addWidget(this->m_cbRight,2,3,1,1);
    this->m_gridLayout->addWidget(this->m_cbBottom,3,2,1,1);

    this->m_gridLayout->addWidget(this->m_llFrameColor,4,0,1,1);
    this->m_gridLayout->addWidget(this->m_leFrameColor,4,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbSelColor,4,4,1,1);

    this->m_gridLayout->addWidget(this->m_llFrameWidth,5,0,1,1);
    this->m_gridLayout->addWidget(this->m_sbFrameWidth,5,1,1,1);

    this->m_gridLayout->addWidget(this->m_tbOkay,6,3,1,1);
    this->m_gridLayout->addWidget(this->m_tbCancel,6,4,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_tbSelColor,SIGNAL(clicked(bool)),this,SLOT(ZSlotChangeColor()));
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));

    //default value.
    this->ZSetTopFrame(false);
    this->ZSetBottomFrame(false);
    this->ZSetLeftFrame(false);
    this->ZSetRightFrame(false);
    this->ZSetFrameColor(QColor(255,255,255,255));
    this->ZSetFrameWidth(1);
}
ZFrameInfoDia::~ZFrameInfoDia()
{
    delete this->m_llLeftTop;
    delete this->m_leLeftTop;

    delete this->m_llRightBottom;
    delete this->m_leRightBottom;

    delete this->m_cbTop;
    delete this->m_cbBottom;
    delete this->m_cbLeft;
    delete this->m_cbRight;

    delete this->m_llFrameColor;
    delete this->m_leFrameColor;
    delete this->m_tbSelColor;

    delete this->m_llFrameWidth;
    delete this->m_sbFrameWidth;

    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gridLayout;
}
void ZFrameInfoDia::ZSlotChangeColor()
{
    this->m_frameColor=QColorDialog::getColor(this->m_frameColor,this,QString("Choose frame color"));
    this->ZUpdateFrameColor(this->m_frameColor);
}
void ZFrameInfoDia::ZSlotOkay()
{
    this->accept();
}
void ZFrameInfoDia::ZSlotCancel()
{
    this->reject();
}
void ZFrameInfoDia::ZUpdateFrameColor(QColor color)
{
    QString tStyleSheet;
    tStyleSheet.sprintf("background-color:rgba(%d,%d,%d,%d)",color.red(),color.green(),color.blue(),color.alpha());
    this->m_leFrameColor->setStyleSheet(tStyleSheet);
}
void ZFrameInfoDia::ZSetFrameColor(QColor frameColor)
{
    this->m_frameColor=frameColor;
    this->ZUpdateFrameColor(this->m_frameColor);
}
QColor ZFrameInfoDia::ZGetFrameColor()
{
    return this->m_frameColor;
}

bool ZFrameInfoDia::ZTopFrameIsSet()
{
    return this->m_cbTop->isChecked();
}
void ZFrameInfoDia::ZSetTopFrame(bool bFrame)
{
    this->m_cbTop->setChecked(bFrame);
}
bool ZFrameInfoDia::ZBottomFrameIsSet()
{
    return this->m_cbBottom->isChecked();
}
void ZFrameInfoDia::ZSetBottomFrame(bool bFrame)
{
    this->m_cbBottom->setChecked(bFrame);
}
bool ZFrameInfoDia::ZLeftFrameIsSet()
{
    return this->m_cbLeft->isChecked();
}
void ZFrameInfoDia::ZSetLeftFrame(bool bFrame)
{
    this->m_cbLeft->setChecked(bFrame);
}
bool ZFrameInfoDia::ZRightFrameIsSet()
{
    return this->m_cbRight->isChecked();
}
void ZFrameInfoDia::ZSetRightFrame(bool bFrame)
{
    this->m_cbRight->setChecked(bFrame);
}

//frame width.
void ZFrameInfoDia::ZSetFrameWidth(qint32 frameWidth)
{
    this->m_sbFrameWidth->setValue(frameWidth);
}
qint32 ZFrameInfoDia::ZGetFrameWidth()
{
    return this->m_sbFrameWidth->value();
}
void ZFrameInfoDia::ZSetLeftTop(qint32 x,qint32 y)
{
    this->m_leLeftTop->setText(QString("(%1,%2)").arg(x).arg(y));
}
void ZFrameInfoDia::ZSetRightBottom(qint32 x,qint32 y)
{
    this->m_leRightBottom->setText(QString("(%1,%2)").arg(x).arg(y));
}
