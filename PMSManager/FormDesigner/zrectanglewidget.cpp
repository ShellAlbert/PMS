#include "zrectanglewidget.h"
#include <QPainter>
#include <QPen>
#include <QColorDialog>
#include <QDebug>
ZRectangleDialog::ZRectangleDialog(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("矩形属性对话框"));

    this->m_llColor=new QLabel;
    this->m_llColor->setText((tr("颜色")));
    this->m_leColor=new QLineEdit;
    this->m_tbChange=new QToolButton;
    this->m_tbChange->setText(tr("更改..."));

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llColor,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leColor,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbChange,0,2,1,1);

    this->m_gridLayout->addWidget(this->m_tbOkay,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbCancel,1,2,1,1);

    this->setLayout(this->m_gridLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));
    connect(this->m_tbChange,SIGNAL(clicked(bool)),this,SLOT(ZSlotChangeColor()));
}

ZRectangleDialog::~ZRectangleDialog()
{
    delete this->m_llColor;
    delete this->m_leColor;
    delete this->m_tbChange;
    delete this->m_tbCancel;
    delete this->m_tbOkay;
    delete this->m_gridLayout;
}
void ZRectangleDialog::ZSlotChangeColor()
{
    QColor color=QColorDialog::getColor(Qt::black,this,tr("更改矩形背景颜色"));
    this->ZSetBackgroundColor(color);
}
QColor ZRectangleDialog::ZGetBackgroundColor()
{
    return this->m_color;
}
void ZRectangleDialog::ZSetBackgroundColor(QColor color)
{
    this->m_color=color;
    this->m_leColor->setText(tr("%1,%2,%3").arg(color.red()).arg(color.green()).arg(color.blue()));
    this->m_leColor->setStyleSheet(QString("QLineEdit{background-color:rgb(%1,%2,%3);}").arg(color.red()).arg(color.green()).arg(color.blue()));
}
ZRectangleItem::ZRectangleItem()
{
    this->m_color=QColor(0,0,0);
}
QColor ZRectangleItem::ZGetColor()
{
    return this->m_color;
}
void ZRectangleItem::ZSetColor(QColor color)
{
    this->m_color=color;
}
void ZRectangleItem::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(QRect(0,0,this->width(),this->height()),this->m_color);
}
ZRectangleWidget::ZRectangleWidget()
{
    this->m_rectItem=new ZRectangleItem;
    this->m_rectItem->setMinimumSize(50,25);
    this->m_vLayout->addWidget(this->m_rectItem);
}
ZRectangleWidget::~ZRectangleWidget()
{
    delete this->m_rectItem;
}
void ZRectangleWidget::ZOpenAttributeDialog()
{
    ZRectangleDialog dia;
    dia.ZSetBackgroundColor(this->m_rectItem->ZGetColor());
    if(dia.exec()==QDialog::Accepted)
    {
        this->m_rectItem->ZSetColor(dia.ZGetBackgroundColor());
    }
}
