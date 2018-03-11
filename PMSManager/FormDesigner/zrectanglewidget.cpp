#include "zrectanglewidget.h"
#include <QPainter>
#include <QPen>
#include <QColorDialog>
#include <QDebug>
ZRectangleDialog::ZRectangleDialog(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("矩形属性对话框"));

    this->m_llX=new QLabel(tr("X坐标"));
    this->m_leX=new QLineEdit;
    this->m_llY=new QLabel(tr("Y坐标"));
    this->m_leY=new QLineEdit;
    this->m_llWidth=new QLabel(tr("宽度"));
    this->m_leWidth=new QLineEdit;
    this->m_llHeight=new QLabel(tr("高度"));
    this->m_leHeight=new QLineEdit;

    this->m_llColor=new QLabel;
    this->m_llColor->setText((tr("颜色")));
    this->m_leColor=new QLineEdit;
    this->m_tbChange=new QToolButton;
    this->m_tbChange->setText(tr("更改..."));


    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("OKAY"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("CANCEL"));
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llX,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leX,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_llY,0,2,1,1);
    this->m_gridLayout->addWidget(this->m_leY,0,3,1,1);

    this->m_gridLayout->addWidget(this->m_llWidth,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_leWidth,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_llHeight,1,2,1,1);
    this->m_gridLayout->addWidget(this->m_leHeight,1,3,1,1);

    this->m_gridLayout->addWidget(this->m_llColor,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_leColor,2,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbChange,2,2,1,1);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_tbOkay);
    this->m_hLayout->addWidget(this->m_tbCancel);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addLayout(this->m_gridLayout);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));
    connect(this->m_tbChange,SIGNAL(clicked(bool)),this,SLOT(ZSlotChangeColor()));
}

ZRectangleDialog::~ZRectangleDialog()
{
    delete this->m_llX;
    delete this->m_leX;
    delete this->m_llY;
    delete this->m_leY;
    delete this->m_llWidth;
    delete this->m_leWidth;
    delete this->m_llHeight;
    delete this->m_leHeight;

    delete this->m_llColor;
    delete this->m_leColor;
    delete this->m_tbChange;
    delete this->m_gridLayout;

    delete this->m_tbCancel;
    delete this->m_tbOkay;
    delete this->m_hLayout;

    delete this->m_vLayout;
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
void ZRectangleDialog::ZSetXYSize(qint32 x,qint32 y,qint32 width,qint32 height)
{
    this->m_leX->setText(QString::number(x,10));
    this->m_leY->setText(QString::number(y,10));
    this->m_leWidth->setText(QString::number(width,10));
    this->m_leHeight->setText(QString::number(height,10));
}
void ZRectangleDialog::ZGetXYSize(qint32 *x,qint32 *y,qint32 *width,qint32 *height)
{
    *x=this->m_leX->text().toInt();
    *y=this->m_leY->text().toInt();
    *width=this->m_leWidth->text().toInt();
    *height=this->m_leHeight->text().toInt();
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
    dia.ZSetXYSize(this->x(),this->y(),this->width(),this->height());
    if(dia.exec()==QDialog::Accepted)
    {
        this->m_color=dia.ZGetBackgroundColor();
        qint32 x,y,width,height;
        dia.ZGetXYSize(&x,&y,&width,&height);
        this->setGeometry(x,y,width,height);
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
