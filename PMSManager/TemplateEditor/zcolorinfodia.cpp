#include "zcolorinfodia.h"
#include <QColorDialog>
ZColorInfoDia::ZColorInfoDia(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("颜色对话框"));

    this->m_llLeftTop=new QLabel(tr("左上角"));
    this->m_leLeftTop=new QLineEdit;
    this->m_leLeftTop->setEnabled(false);
    this->m_llRightBottom=new QLabel(tr("右下角"));
    this->m_leRightBottom=new QLineEdit;
    this->m_leRightBottom->setEnabled(false);

    this->m_llFgColor=new QLabel(tr("前景色"));
    this->m_leFgColor=new QLineEdit;
    this->m_btnSelFgColor=new QToolButton;
    this->m_btnSelFgColor->setText(tr("更改..."));

    this->m_llBgColor=new QLabel(tr("背景色"));
    this->m_leBgColor=new QLineEdit;
    this->m_btnSelBgColor=new QToolButton;
    this->m_btnSelBgColor->setText(tr("更改..."));

    this->m_btnOkay=new QToolButton;
    this->m_btnOkay->setText(tr("确认"));
    this->m_btnCancel=new QToolButton;
    this->m_btnCancel->setText(tr("取消"));
    this->m_btnOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_btnOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_btnCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llLeftTop,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leLeftTop,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_llRightBottom,0,2,1,1);
    this->m_gridLayout->addWidget(this->m_leRightBottom,0,3,1,1);

    this->m_gridLayout->addWidget(this->m_llFgColor,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_leFgColor,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_btnSelFgColor,1,3,1,1);

    this->m_gridLayout->addWidget(this->m_llBgColor,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_leBgColor,2,1,1,1);
    this->m_gridLayout->addWidget(this->m_btnSelBgColor,2,3,1,1);

    this->m_gridLayout->addWidget(this->m_btnOkay,3,2,1,1);
    this->m_gridLayout->addWidget(this->m_btnCancel,3,3,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_btnSelFgColor,SIGNAL(clicked(bool)),this,SLOT(ZSlotSelFgColor()));
    connect(this->m_btnSelBgColor,SIGNAL(clicked(bool)),this,SLOT(ZSlotSelBgColor()));
    connect(this->m_btnOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_btnCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
}
ZColorInfoDia::~ZColorInfoDia()
{
    delete this->m_llLeftTop;
    delete this->m_leLeftTop;
    delete this->m_llRightBottom;
    delete this->m_leRightBottom;

    delete this->m_llFgColor;
    delete this->m_leFgColor;
    delete this->m_btnSelFgColor;

    delete this->m_llBgColor;
    delete this->m_leBgColor;
    delete this->m_btnSelBgColor;

    delete this->m_btnOkay;
    delete this->m_btnCancel;
    delete this->m_gridLayout;
}
void ZColorInfoDia::ZSetLeftTop(qint32 x,qint32 y)
{
    this->m_leLeftTop->setText(QString("(%1,%2)").arg(x).arg(y));
}
void ZColorInfoDia::ZSetRightBottom(qint32 x,qint32 y)
{
    this->m_leRightBottom->setText(QString("(%1,%2)").arg(x).arg(y));
}
void ZColorInfoDia::ZSlotOkay()
{
    this->accept();
}
void ZColorInfoDia::ZSlotCancel()
{
    this->reject();
}
void ZColorInfoDia::ZSlotSelFgColor()
{
    QColor color=QColorDialog::getColor(Qt::black,this,QString("选择前景色"),QColorDialog::ShowAlphaChannel);
    this->ZSetFgColor(color);
}
void ZColorInfoDia::ZSlotSelBgColor()
{
    QColor color=QColorDialog::getColor(Qt::white,this,QString("选择背景色"),QColorDialog::ShowAlphaChannel);
    this->ZSetBgColor(color);
}
QColor ZColorInfoDia::ZGetFgColor()
{
    return this->m_fgColor;
}
void ZColorInfoDia::ZSetFgColor(QColor color)
{
    QString tStyleSheet;
    tStyleSheet.sprintf("background-color:rgba(%d,%d,%d,%d)",color.red(),color.green(),color.blue(),color.alpha());
    this->m_leFgColor->setStyleSheet(tStyleSheet);
    this->m_leFgColor->setText(QString("rgba(%1,%2,%3,%4)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()));
    this->m_fgColor=color;
}
QColor ZColorInfoDia::ZGetBgColor()
{
    return this->m_bgColor;
}
void ZColorInfoDia::ZSetBgColor(QColor color)
{
    QString tStyleSheet;
    tStyleSheet.sprintf("background-color:rgba(%d,%d,%d,%d)",color.red(),color.green(),color.blue(),color.alpha());
    this->m_leBgColor->setStyleSheet(tStyleSheet);
    this->m_leBgColor->setText(QString("rgba(%1,%2,%3,%4)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()));
    this->m_bgColor=color;
}
