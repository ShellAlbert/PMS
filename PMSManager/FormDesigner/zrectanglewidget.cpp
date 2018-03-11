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
    this->m_tbOkay->setText(tr("OKAY"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("CANCEL"));

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
ZRectangleWidget::ZRectangleWidget()
{
    this->setMinimumSize(60,30);
}
ZRectangleWidget::~ZRectangleWidget()
{

}
void ZRectangleWidget::ZOpenAttributeDialog()
{
    ZRectangleDialog dia;
    dia.ZSetBackgroundColor(this->ZGetColor());
    if(dia.exec()==QDialog::Accepted)
    {
        this->m_color=dia.ZGetBackgroundColor();
        this->update();
    }
}
QColor ZRectangleWidget::ZGetColor()
{
    return this->m_color;
}
void ZRectangleWidget::ZSetColor(QColor color)
{
    this->m_color=color;
    this->update();
}
void ZRectangleWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.fillRect(QRectF(0,0,this->width(),this->height()),QBrush(this->m_color));

    //call the parent's event.
    if(this->m_editMode)
    {
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
