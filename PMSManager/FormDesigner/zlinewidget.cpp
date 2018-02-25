#include "zlinewidget.h"
#include <QPainter>
#include <QPen>
#include <QColorDialog>
ZLineDialog::ZLineDialog(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("直线属性对话框"));

    this->m_llWidth=new QLabel(tr("线宽"));
    this->m_sbWidth=new QSpinBox;
    this->m_sbWidth->setRange(1,100);

    this->m_llColor=new QLabel(tr("颜色"));
    this->m_leColor=new QLineEdit;
    this->m_tbChange=new QToolButton;
    this->m_tbChange->setText(tr("更改..."));

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llWidth,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_sbWidth,0,1,1,1);

    this->m_gridLayout->addWidget(this->m_llColor,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_leColor,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbChange,1,2,1,1);

    this->m_gridLayout->addWidget(this->m_tbOkay,2,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbCancel,2,2,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_tbChange,SIGNAL(clicked(bool)),this,SLOT(ZSlotChangeColor()));
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));
}
ZLineDialog::~ZLineDialog()
{
    delete this->m_llWidth;
    delete this->m_sbWidth;
    delete this->m_llColor;
    delete this->m_leColor;
    delete this->m_tbChange;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gridLayout;
}
void ZLineDialog::ZSlotChangeColor()
{
    QColor color=QColorDialog::getColor(Qt::black,this,tr("线条颜色"));
    this->ZSetColor(color);
}
qint32 ZLineDialog::ZGetWidth()
{
    return this->m_sbWidth->value();
}
void ZLineDialog::ZSetWidth(qint32 width)
{
    this->m_sbWidth->setValue(width);
}

QColor ZLineDialog::ZGetColor()
{
    return this->m_color;
}
void ZLineDialog::ZSetColor(QColor color)
{
    this->m_color=color;
    this->m_leColor->setStyleSheet(QString("QLineEdit{background-color:rgb(%1,%2,%3);}").arg(color.red()).arg(color.green()).arg(color.blue()));
    this->m_leColor->setText(QString("%1,%2,%3").arg(color.red()).arg(color.green()).arg(color.blue()));
}
ZLineItem::ZLineItem()
{
    this->m_color=QColor(0,0,0);
    this->m_width=3;
}

void ZLineItem::ZSetWidth(qint32 width)
{
    this->m_width=width;
}
qint32 ZLineItem::ZGetWidth()
{
    return this->m_width;
}
void ZLineItem::ZSetColor(QColor color)
{
    this->m_color=color;
}
QColor ZLineItem::ZGetColor()
{
    return this->m_color;
}
void ZLineItem::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen pen(this->m_color);
    pen.setWidth(this->m_width);
    painter.setPen(pen);
    painter.drawLine(QPointF(0,0),QPointF(this->width(),0));
}
ZLineWidget::ZLineWidget()
{
    this->m_lineItem=new ZLineItem;
    this->m_vLayout->addWidget(this->m_lineItem);
    this->setFixedSize(100,40);
}
ZLineWidget::~ZLineWidget()
{
    delete this->m_lineItem;
}
void ZLineWidget::ZOpenAttributeDialog()
{
    ZLineDialog dia;
    dia.ZSetWidth(this->m_lineItem->ZGetWidth());
    dia.ZSetColor(this->m_lineItem->ZGetColor());
    if(dia.exec()==QDialog::Accepted)
    {
        this->m_lineItem->ZSetWidth(dia.ZGetWidth());
        this->m_lineItem->ZSetColor(dia.ZGetColor());
    }
}
