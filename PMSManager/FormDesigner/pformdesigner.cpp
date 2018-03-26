#include "pformdesigner.h"
#include <QCheckBox>
#include <QSpinBox>
#include <QDateTimeEdit>
#include <QTableWidget>
#include <QPainter>
#include <QFontDatabase>
#include <QDebug>
#include <FormDesigner/zlinewidget.h>
#include <FormDesigner/ztextwidget.h>
#include <FormDesigner/zcheckboxwidget.h>
#include <FormDesigner/zspinboxwidget.h>
#include <FormDesigner/zdatetimewidget.h>
#include <FormDesigner/zrectanglewidget.h>
#include <FormDesigner/ztablewidget.h>
#include <FormDesigner/zforminfodia.h>
#include <FormDesigner/zlistforminfodia.h>
#include <FormDesigner/zbargraphwidget.h>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QGraphicsItem>
#include <KDReports/KDReports.h>
#include <KDReports/KDReportsTableElement.h>
#include <KDReports/KDReportsCell.h>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "pgblpara.h"
ZFormList::ZFormList()
{
    this->m_tree=new QTreeWidget;
    this->m_tree->setColumnCount(4);
    QStringList lables;
    lables<<tr("报表名称");
    lables<<tr("占用磁盘");
    lables<<tr("创建者");
    lables<<tr("创建时间");
    this->m_tree->setHeaderLabels(lables);
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_tree);
    this->setLayout(this->m_vLayout);
}
ZFormList::~ZFormList()
{
    delete this->m_tree;
    delete this->m_vLayout;
}

ZGraphicsView::ZGraphicsView(ZGraphicsView::OpMode mode,QGraphicsScene *parent):QGraphicsView(parent)
{
    this->m_opMode=mode;
    this->m_scene=parent;

    this->m_bLeftButtonPressed=false;
    this->m_moveProxyWidget=NULL;
    this->m_resizeHProxyWidget=NULL;
    this->m_resizeVProxyWidget=NULL;

    //no editable at default.
    this->m_bEditable=false;

    this->m_scaleFactor=30;

    connect(this,SIGNAL(ZSignalZoom(bool)),this,SLOT(ZSlotZoom(bool)));
}
void ZGraphicsView::ZAddRectangle()
{
    this->m_opMode=Mode_Add_Rectangle;
    this->setCursor(QCursor(QPixmap(":/FormDesigner/images/FormDesigner/RectangleItem.png")));
}
void ZGraphicsView::ZAddCheckBox()
{
    this->m_opMode=Mode_Add_CheckBox;
    this->setCursor(QCursor(QPixmap(":/FormDesigner/images/FormDesigner/CheckBoxItem.png")));
}
void ZGraphicsView::ZAddSpinBox()
{
    this->m_opMode=Mode_Add_SpinBox;
    this->setCursor(QCursor(QPixmap(":/FormDesigner/images/FormDesigner/SpinBox.png")));
}
void ZGraphicsView::ZAddDateTimeEdit()
{
    this->m_opMode=Mode_Add_DateTimeEdit;
    this->setCursor(QCursor(QPixmap(":/FormDesigner/images/FormDesigner/DateTimeEdit.png")));
}
void ZGraphicsView::ZAddTable()
{
    this->m_opMode=Mode_Add_Table;
    this->setCursor(QCursor(QPixmap(":/FormDesigner/images/FormDesigner/TableItem.png")));
}
void ZGraphicsView::ZAddText()
{
    this->m_opMode=Mode_Add_Text;
    this->setCursor(QCursor(QPixmap(":/FormDesigner/images/FormDesigner/TextItem.png")));
}
void ZGraphicsView::ZAddLine()
{
    this->m_opMode=Mode_Add_Line;
    this->setCursor(QCursor(QPixmap(":/FormDesigner/images/FormDesigner/LineItem.png")));
}
void ZGraphicsView::ZAddBarGraph()
{
    this->m_opMode=Mode_Add_Bar_Graph;
    this->setCursor(QCursor(QPixmap(":/FormDesigner/images/FormDesigner/LineItem.png")));
}
void ZGraphicsView::ZSlotEditable(bool editable)
{
    this->m_bEditable=editable;
    if(!this->m_bEditable)
    {
        //deSelect all elements.
        QList<QGraphicsItem*> list=this->scene()->items();
        for(qint32 i=0;i<list.count();i++)
        {
            QGraphicsItem* item=list.at(i);
            if(item->type()==QGraphicsProxyWidget::Type)
            {
                QGraphicsProxyWidget *proxyWid=qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
                if(proxyWid)
                {
                    ZBaseWidget *bw=qobject_cast<ZBaseWidget*>(proxyWid->widget());
                    if(bw)
                    {
                        bw->ZSetEditMode(false);
                    }
                }
            }
        }
    }
}
void ZGraphicsView::ZSlotZoom(bool zoom)
{
    if(zoom && this->m_scaleFactor>=0)
    {
        this->m_scaleFactor+=10;
        QMatrix oldMatrix=this->matrix();
        this->resetMatrix();
        this->translate(oldMatrix.dx(),oldMatrix.dy());
        this->scale(this->m_scaleFactor/100.0,this->m_scaleFactor/100.0);
    }else if(!zoom && this->m_scaleFactor>=0)
    {
        this->m_scaleFactor-=10;
        QMatrix oldMatrix=this->matrix();
        this->resetMatrix();
        this->translate(oldMatrix.dx(),oldMatrix.dy());
        this->scale(this->m_scaleFactor/100.0,this->m_scaleFactor/100.0);
    }else if(this->m_scaleFactor<0)
    {
        this->m_scaleFactor=0.0;
    }
}
void ZGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(!this->m_bEditable)
    {
        return;
    }

    switch(this->m_opMode)
    {
    case Mode_Normal:
        if(event->button()==Qt::LeftButton)
        {
            this->m_bLeftButtonPressed=true;
            QGraphicsItem *item=this->itemAt(event->pos());
            this->m_moveProxyWidget=qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
            if(this->m_moveProxyWidget!=NULL)
            {
                //select it.
                ZBaseWidget *bw=qobject_cast<ZBaseWidget*>(this->m_moveProxyWidget->widget());
                if(bw)
                {
                    bw->ZSetEditMode(true);
                }

                //if we choose a element,then move it to new pos.
                this->m_startPos.setX(event->pos().x()-this->m_moveProxyWidget->widget()->x());
                this->m_startPos.setY(event->pos().y()-this->m_moveProxyWidget->widget()->y());
            }else{
                //we click at a empty pos,deselect all elements.
                //set all editable to fix mode.
                QList<QGraphicsItem*> list=this->scene()->items();
                for(qint32 i=0;i<list.count();i++)
                {
                    QGraphicsItem* item=list.at(i);
                    if(item->type()==QGraphicsProxyWidget::Type)
                    {
                        QGraphicsProxyWidget *proxyWid=qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
                        if(proxyWid)
                        {
                            ZBaseWidget *bw=qobject_cast<ZBaseWidget*>(proxyWid->widget());
                            if(bw)
                            {
                                bw->ZSetEditMode(false);
                            }
                        }
                    }
                }
            }
        }
        break;
    case Mode_Add_Line:
    {
        //add a line element to view.
        ZLineWidget *lw=new ZLineWidget;
        QGraphicsProxyWidget  *proxy=this->m_scene->addWidget(lw);
        proxy->setPos(event->pos());
    }
        break;
    case Mode_Add_Rectangle:
    {
        //add a rectange element to view.
        ZRectangleWidget *lw=new ZRectangleWidget;
        QGraphicsProxyWidget  *proxy=this->m_scene->addWidget(lw);
        proxy->setPos(event->pos());
    }
        break;
    case Mode_Add_Text:
    {
        //add a text element to view.
        ZTextWidget *tw=new ZTextWidget;
        QGraphicsProxyWidget  *proxy=this->m_scene->addWidget(tw);
        proxy->setPos(event->pos());
    }
        break;
    case Mode_Add_CheckBox:
    {
        //add a checkbox element to view.
        ZCheckBoxWidget *cbw=new ZCheckBoxWidget;
        QGraphicsProxyWidget  *proxy=this->m_scene->addWidget(cbw);
        proxy->setPos(event->pos());
    }
        break;
    case Mode_Add_SpinBox:
    {
        ZSpinBoxWidget *sbw=new ZSpinBoxWidget;
        QGraphicsProxyWidget  *proxy=this->m_scene->addWidget(sbw);
        proxy->setPos(event->pos());
    }
        break;
    case Mode_Add_DateTimeEdit:
    {
        ZDateTimeWidget *dtw=new ZDateTimeWidget;
        QGraphicsProxyWidget  *proxy=this->m_scene->addWidget(dtw);
        proxy->setPos(event->pos());
    }
        break;
    case Mode_Add_Table:
    {
        ZTableWidget *tw=new ZTableWidget;
        QGraphicsProxyWidget  *proxy=this->m_scene->addWidget(tw);
        proxy->setPos(event->pos());
    }
        break;
    case Mode_Add_Bar_Graph:
    {
        ZBarGraphWidget *bgw=new ZBarGraphWidget;
        QGraphicsProxyWidget  *proxy=this->m_scene->addWidget(bgw);
        proxy->setPos(event->pos());
    }
        break;
    default:
        break;
    }
    emit this->ZSignalDataChanged();
}

void ZGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(!this->m_bEditable)
    {
        return;
    }

    //优先级,优先改变尺寸，然后才是移动。
    if(this->m_bLeftButtonPressed && this->m_resizeHProxyWidget!=NULL)
    {
        qint32 widthInc=event->pos().x()-(this->m_resizeHProxyWidget->widget()->x()+this->m_resizeHProxyWidget->widget()->width());
        this->m_resizeHProxyWidget->widget()->setFixedWidth(this->m_resizeHProxyWidget->widget()->width()+widthInc);
    }else if(this->m_bLeftButtonPressed && this->m_resizeVProxyWidget!=NULL)
    {
        qint32 heightInc=event->pos().y()-(this->m_resizeVProxyWidget->widget()->y()+this->m_resizeVProxyWidget->widget()->height());
        this->m_resizeVProxyWidget->widget()->setFixedHeight(this->m_resizeVProxyWidget->widget()->height()+heightInc);
    }else if(this->m_bLeftButtonPressed && this->m_moveProxyWidget!=NULL)
    {
        this->m_moveProxyWidget->setPos(event->pos()-this->m_startPos);
    }else{
        QGraphicsItem *item=this->itemAt(event->pos());
        QGraphicsProxyWidget *widget=qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
        if(widget)
        {
            //map to scene coordinates.
            QPointF eventPosScene=this->mapToScene(event->pos());
            QPointF widgetPosScene=item->mapToScene(item->pos());
            qDebug()<<"eventPos:"<<eventPosScene<<",itemPos:"<<widgetPosScene;

            qint32 curX=eventPosScene.x();
            qint32 curY=eventPosScene.y();

            qint32 widthRangeXMin=widgetPosScene.x()+widget->geometry().width()-10;
            qint32 widthRangeXMax=widgetPosScene.x()+widget->geometry().width()+10;
            qint32 widthRangeYMin=widgetPosScene.y();
            qint32 widthRangeYMax=widgetPosScene.y()+widget->geometry().height();
            qDebug()<<"x:"<<curX<<widthRangeXMin<<widthRangeXMax;
            qDebug()<<"y:"<<curY<<widthRangeYMin<<widthRangeYMax;

            qint32 heightRangeXMin=widgetPosScene.x();
            qint32 heightRangeXMax=widgetPosScene.x()+widget->geometry().width();
            qint32 heightRangeYMin=widgetPosScene.y()+widget->geometry().height()-10;
            qint32 heightRangeYMax=widgetPosScene.y()+widget->geometry().height()+10;
            if(curX>widthRangeXMin && curX<widthRangeXMax && curY >widthRangeYMin && curY<widthRangeYMax)
            {
                this->setCursor(Qt::SizeHorCursor);
                this->m_resizeHProxyWidget=widget;
            }else if(curX>heightRangeXMin && curX<heightRangeXMax && curY>heightRangeYMin && curY<heightRangeYMax)
            {
                this->setCursor(Qt::SizeVerCursor);
                this->m_resizeVProxyWidget=widget;
            }else{
                this->setCursor(Qt::ArrowCursor);
                this->m_resizeHProxyWidget=NULL;
                this->m_resizeVProxyWidget=NULL;
            }
        }else{
            this->setCursor(Qt::ArrowCursor);
            this->m_resizeHProxyWidget=NULL;
            this->m_resizeVProxyWidget=NULL;
        }
    }
}
void ZGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(!this->m_bEditable)
    {
        return;
    }

    this->m_bLeftButtonPressed=false;
    this->m_moveProxyWidget=NULL;
    this->m_opMode=Mode_Normal;
    this->setCursor(Qt::ArrowCursor);
    return;
}
void ZGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(!this->m_bEditable)
    {
        return;
    }

    QGraphicsItem *item=this->itemAt(event->pos());
    if(item==NULL)
    {
        return;
    }
    QGraphicsProxyWidget *proxy=qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
    if(proxy==NULL)
    {
        return;
    }

    ZBaseWidget *widget=qobject_cast<ZBaseWidget*>(proxy->widget());
    if(widget)
    {
        widget->ZSetEditMode(true);
        widget->ZOpenAttributeDialog();
    }
}
void ZGraphicsView::wheelEvent(QWheelEvent *e)
{
    if(e->delta()>0)
    {
        emit this->ZSignalZoom(true);
    }else{
        emit this->ZSignalZoom(false);
    }
}
void ZGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(!this->m_bEditable)
    {
        return;
    }

    if(event->key()==Qt::Key_Delete)
    {
        QList<QGraphicsItem*> itemList=this->m_scene->selectedItems();
        for(qint32 i=0;i<itemList.size();i++)
        {
            QGraphicsItem *item=itemList.at(i);
            this->m_scene->removeItem(item);
            delete item;
            item=NULL;
        }
        itemList.clear();
    }
}
ZFormWidget::ZFormWidget()
{
    this->m_cbEditable=new QCheckBox;
    this->m_cbEditable->setText(tr("编辑模式"));
    this->m_cbEditable->setChecked(false);

    this->m_llLeftTop[0]=new QLabel;
    this->m_llLeftTop[0]->setFixedSize(10,10);
    this->m_llLeftTop[0]->setStyleSheet("QLabel{background-color:red;}");
    this->m_llLeftTop[1]=new QLabel;
    this->m_llLeftTop[1]->setText(tr("移动位置"));

    this->m_llLeftBottom[0]=new QLabel;
    this->m_llLeftBottom[0]->setFixedSize(10,10);
    this->m_llLeftBottom[0]->setStyleSheet("QLabel{background-color:green;}");
    this->m_llLeftBottom[1]=new QLabel;
    this->m_llLeftBottom[1]->setText(tr("组件属性"));

    this->m_llRightTop[0]=new QLabel;
    this->m_llRightTop[0]->setFixedSize(10,10);
    this->m_llRightTop[0]->setStyleSheet("QLabel{background-color:blue;}");
    this->m_llRightTop[1]=new QLabel;
    this->m_llRightTop[1]->setText(tr("高度调节"));

    this->m_llRightBottom[0]=new QLabel;
    this->m_llRightBottom[0]->setFixedSize(10,10);
    this->m_llRightBottom[0]->setStyleSheet("QLabel{background-color:yellow;}");
    this->m_llRightBottom[1]=new QLabel;
    this->m_llRightBottom[1]->setText(tr("宽度调节"));

    this->m_llPageSize=new QLabel;
    this->m_llPageSize->setText(tr("纸张大小"));
    this->m_cbPageSize=new QComboBox;
    this->m_cbPageSize->setEditable(false);
    this->m_cbPageSize->addItem("A1");
    this->m_cbPageSize->addItem("A2");
    this->m_cbPageSize->addItem("A3");
    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_cbEditable);
    this->m_hLayout->addWidget(this->m_llLeftTop[0]);
    this->m_hLayout->addWidget(this->m_llLeftTop[1]);
    this->m_hLayout->addWidget(this->m_llLeftBottom[0]);
    this->m_hLayout->addWidget(this->m_llLeftBottom[1]);
    this->m_hLayout->addWidget(this->m_llRightTop[0]);
    this->m_hLayout->addWidget(this->m_llRightTop[1]);
    this->m_hLayout->addWidget(this->m_llRightBottom[0]);
    this->m_hLayout->addWidget(this->m_llRightBottom[1]);
    this->m_hLayout->addWidget(this->m_llPageSize);
    this->m_hLayout->addWidget(this->m_cbPageSize);

    this->m_scene=new QGraphicsScene(this);
    this->m_view=new ZGraphicsView(ZGraphicsView::Mode_Normal,this->m_scene);
    this->m_view->show();
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addLayout(this->m_hLayout);
    this->m_vLayout->addWidget(this->m_view);
    this->setLayout(this->m_vLayout);

    connect(this->m_cbEditable,SIGNAL(clicked(bool)),this->m_view,SLOT(ZSlotEditable(bool)));
    connect(this->m_view,SIGNAL(ZSignalDataChanged()),this,SIGNAL(ZSignalDataChanged()));
}
ZFormWidget::~ZFormWidget()
{
    QList<QGraphicsItem*> list=this->m_scene->items();
    for(qint32 i=0;i<list.count();i++)
    {
        QGraphicsItem* item=list.at(i);
        delete item;
        item=NULL;
    }

    delete this->m_cbEditable;
    delete this->m_llLeftTop[0];
    delete this->m_llLeftTop[1];
    delete this->m_llLeftBottom[0];
    delete this->m_llLeftBottom[1];
    delete this->m_llRightTop[0];
    delete this->m_llRightTop[1];
    delete this->m_llRightBottom[0];
    delete this->m_llRightBottom[1];
    delete this->m_llPageSize;
    delete this->m_cbPageSize;
    delete this->m_hLayout;
    delete this->m_scene;
    delete this->m_view;
    delete this->m_vLayout;
}
bool ZFormWidget::ZIsEditable()
{
    return this->m_cbEditable->isChecked();
}
QString ZFormWidget::ZGetFormName()
{
    return this->m_formName;
}
void ZFormWidget::ZSetFormName(QString name)
{
    this->m_formName=name;
}
QString ZFormWidget::ZGetXmlData()
{
    QString formXmlData;
    QXmlStreamWriter  tXmlWriter(&formXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("Form"));
    tXmlWriter.writeAttribute(QString("name"),this->ZGetFormName());
    QList<QGraphicsItem*> list=this->m_scene->items();
    for(qint32 i=0;i<list.count();i++)
    {
        QGraphicsItem* item=list.at(i);
        if(item->type()==QGraphicsProxyWidget::Type)
        {
            QGraphicsProxyWidget *proxyWid=qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
            if(proxyWid)
            {
                ZLineWidget *lw=qobject_cast<ZLineWidget*>(proxyWid->widget());
                if(lw)
                {
                    tXmlWriter.writeStartElement(QString("Line"));
                    tXmlWriter.writeAttribute(QString("x"),QString("%1").arg(lw->x()));
                    tXmlWriter.writeAttribute(QString("y"),QString("%1").arg(lw->y()));
                    tXmlWriter.writeAttribute(QString("width"),QString("%1").arg(lw->rect().width()));
                    tXmlWriter.writeAttribute(QString("height"),QString("%1").arg(lw->rect().height()));
                    tXmlWriter.writeAttribute(QString("lw"),QString("%1").arg(lw->m_lineItem->ZGetWidth()));
                    QColor color=lw->m_lineItem->ZGetColor();
                    tXmlWriter.writeCharacters(QString("%1,%2,%3").arg(color.red()).arg(color.green()).arg(color.blue()));
                    tXmlWriter.writeEndElement();//Line.
                }
                ZRectangleWidget *rw=qobject_cast<ZRectangleWidget*>(proxyWid->widget());
                if(rw)
                {
                    tXmlWriter.writeStartElement(QString("Rectangle"));
                    tXmlWriter.writeAttribute(QString("x"),QString("%1").arg(rw->x()));
                    tXmlWriter.writeAttribute(QString("y"),QString("%1").arg(rw->y()));
                    tXmlWriter.writeAttribute(QString("width"),QString("%1").arg(rw->rect().width()));
                    tXmlWriter.writeAttribute(QString("height"),QString("%1").arg(rw->rect().height()));
                    QColor color=rw->ZGetColor();
                    tXmlWriter.writeCharacters(QString("%1,%2,%3").arg(color.red()).arg(color.green()).arg(color.blue()));
                    tXmlWriter.writeEndElement();//Rectangle.
                }
                ZTextWidget *tw=qobject_cast<ZTextWidget*>(proxyWid->widget());
                if(tw)
                {
                    tXmlWriter.writeStartElement(QString("Text"));
                    tXmlWriter.writeAttribute(QString("x"),QString("%1").arg(tw->x()));
                    tXmlWriter.writeAttribute(QString("y"),QString("%1").arg(tw->y()));
                    tXmlWriter.writeAttribute(QString("width"),QString("%1").arg(tw->rect().width()));
                    tXmlWriter.writeAttribute(QString("height"),QString("%1").arg(tw->rect().height()));
                    tXmlWriter.writeAttribute(QString("fontName"),tw->m_fontName);
                    tXmlWriter.writeAttribute(QString("fontSize"),QString("%1").arg(tw->m_fontSize));
                    tXmlWriter.writeAttribute(QString("bold"),QString("%1").arg(tw->m_fontBold?1:0));
                    tXmlWriter.writeAttribute(QString("italic"),QString("%1").arg(tw->m_fontItalic?1:0));
                    tXmlWriter.writeCharacters(tw->m_llText->text());
                    tXmlWriter.writeEndElement();//Text.
                }
                ZCheckBoxWidget *cbw=qobject_cast<ZCheckBoxWidget*>(proxyWid->widget());
                if(cbw)
                {
                    tXmlWriter.writeStartElement(QString("CheckBox"));
                    tXmlWriter.writeAttribute(QString("x"),QString("%1").arg(cbw->x()));
                    tXmlWriter.writeAttribute(QString("y"),QString("%1").arg(cbw->y()));
                    tXmlWriter.writeAttribute(QString("width"),QString("%1").arg(cbw->rect().width()));
                    tXmlWriter.writeAttribute(QString("height"),QString("%1").arg(cbw->rect().height()));
                    tXmlWriter.writeAttribute(QString("checked"),cbw->m_cb->isChecked()?"1":"0");
                    tXmlWriter.writeCharacters(cbw->m_cb->text());
                    tXmlWriter.writeEndElement();//CheckBox.
                }
                ZBarGraphWidget *bgw=qobject_cast<ZBarGraphWidget*>(proxyWid->widget());
                if(bgw)
                {
                    tXmlWriter.writeStartElement(QString("BarGraph"));
                    tXmlWriter.writeAttribute(QString("x"),QString("%1").arg(bgw->x()));
                    tXmlWriter.writeAttribute(QString("y"),QString("%1").arg(bgw->y()));
                    tXmlWriter.writeAttribute(QString("width"),QString("%1").arg(bgw->rect().width()));
                    tXmlWriter.writeAttribute(QString("height"),QString("%1").arg(bgw->rect().height()));
                    tXmlWriter.writeCharacters("title");
                    tXmlWriter.writeEndElement();//BarGraph.
                }
            }
        }
    }
    tXmlWriter.writeEndElement();//Form.
    tXmlWriter.writeEndDocument();
    return formXmlData;
}
void ZFormWidget::ZPutXmlData(QString formXmlData)
{
    QXmlStreamReader tXmlReader(formXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Text"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                qint32 x=attr.value(QString("x")).toInt();
                qint32 y=attr.value(QString("y")).toInt();
                qint32 width=attr.value(QString("width")).toInt();
                qint32 height=attr.value(QString("height")).toInt();
                QString fontName=attr.value(QString("fontName")).toString();
                qint32 fontSize=attr.value(QString("fontSize")).toInt();
                qint32 bold=attr.value(QString("bold")).toInt();
                qint32 italic=attr.value(QString("italic")).toInt();
                QString text=tXmlReader.readElementText();
                ZTextWidget *tw=new ZTextWidget;
                tw->setFixedSize(width,height);
                QFont font(fontName);
                font.setPixelSize(fontSize);
                font.setBold(bold?true:false);
                font.setItalic(italic?true:false);
                tw->m_llText->setFont(font);
                tw->m_llText->setText(text);
                QGraphicsProxyWidget  *proxy=this->m_scene->addWidget(tw);
                proxy->setPos(x,y);
            }else if(nodeName==QString("Line"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                qint32 x=attr.value(QString("x")).toInt();
                qint32 y=attr.value(QString("y")).toInt();
                qint32 width=attr.value(QString("width")).toInt();
                qint32 height=attr.value(QString("height")).toInt();
                qint32 lineWidth=attr.value(QString("lw")).toInt();
                QString color=tXmlReader.readElementText();
                QStringList colorList=color.split(",");
                qint32 red=colorList.at(0).toInt();
                qint32 green=colorList.at(1).toInt();
                qint32 blue=colorList.at(2).toInt();
                ZLineWidget *lw=new ZLineWidget;
                lw->setFixedSize(width,height);
                lw->m_lineItem->ZSetWidth(lineWidth);
                lw->m_lineItem->ZSetColor(QColor(red,green,blue));
                QGraphicsProxyWidget  *proxy=this->m_scene->addWidget(lw);
                proxy->setPos(x,y);
            }else if(nodeName==QString("Rectangle"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                qint32 x=attr.value(QString("x")).toInt();
                qint32 y=attr.value(QString("y")).toInt();
                qint32 width=attr.value(QString("width")).toInt();
                qint32 height=attr.value(QString("height")).toInt();
                QString color=tXmlReader.readElementText();
                QStringList colorList=color.split(",");
                qint32 red=colorList.at(0).toInt();
                qint32 green=colorList.at(1).toInt();
                qint32 blue=colorList.at(2).toInt();
                ZRectangleWidget *rw=new ZRectangleWidget;
                rw->setFixedSize(width,height);
                rw->ZSetColor(QColor(red,green,blue));
                QGraphicsProxyWidget  *proxy=this->m_scene->addWidget(rw);
                proxy->setPos(x,y);
            }else if(nodeName==QString("CheckBox"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                qint32 x=attr.value(QString("x")).toInt();
                qint32 y=attr.value(QString("y")).toInt();
                qint32 width=attr.value(QString("width")).toInt();
                qint32 height=attr.value(QString("height")).toInt();
                qint32 checked=attr.value(QString("checked")).toInt();
                QString text=tXmlReader.readElementText();
                ZCheckBoxWidget *cbw=new ZCheckBoxWidget;
                cbw->setFixedSize(width,height);
                cbw->m_cb->setText(text);
                cbw->m_cb->setChecked(checked?true:false);
                QGraphicsProxyWidget  *proxy=this->m_scene->addWidget(cbw);
                proxy->setPos(x,y);
            }else if(nodeName==QString("BarGraph"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                qint32 x=attr.value(QString("x")).toInt();
                qint32 y=attr.value(QString("y")).toInt();
                qint32 width=attr.value(QString("width")).toInt();
                qint32 height=attr.value(QString("height")).toInt();
                QString text=tXmlReader.readElementText();
                ZBarGraphWidget *bgw=new ZBarGraphWidget;
                bgw->setFixedSize(width,height);
                QGraphicsProxyWidget  *proxy=this->m_scene->addWidget(bgw);
                proxy->setPos(x,y);
            }//nodeName.
        }//StarElement.
    }//while().
}
void ZFormWidget::resizeEvent(QResizeEvent *event)
{
    this->m_scene->setSceneRect(0,0,this->m_view->size().width(),this->m_view->size().height());
    QFrame::resizeEvent(event);
}
PFormDesigner::PFormDesigner()
{
    this->setWindowTitle(tr("报表生成器-Form Designer"));
    this->setWindowIcon(QIcon(":/TaskBar/images/FormDesigner.png"));
    //    this->setStyleSheet("QToolButton{background-color:#cce5f9;font:color #eaf7ff;padding: 6px 12px 6px 12p}"
    //                        "QToolButton::hover{background-color:#eaf7ff;}"
    //                        "");
    this->setStyleSheet("QToolButton{background-color:#cce5f9;border:none;font:color #eaf7ff;}"
                        "QToolButton::hover{background-color:#eaf7ff;}"
                        "");
    this->m_tbFormOp=new QToolButton;
    this->m_tbFormOp->setToolTip(tr("报表操作"));
    this->m_tbFormOp->setText(tr("报表"));
    this->m_tbFormOp->setIcon(QIcon(":/FormDesigner/images/FormDesigner/FormOp.png"));
    this->m_tbFormOp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_actNewForm=new QAction(QIcon(":/FormDesigner/images/FormDesigner/NewForm.png"),tr("新建报表"),0);
    this->m_actOpenForm=new QAction(QIcon(":/FormDesigner/images/FormDesigner/OpenForm.png"),tr("打开报表"),0);
    this->m_actSaveForm=new QAction(QIcon(":/FormDesigner/images/FormDesigner/SaveForm.png"),tr("保存报表"),0);
    this->m_actDelForm=new QAction(QIcon(":/FormDesigner/images/FormDesigner/DelForm.png"),tr("删除报表"),0);
    connect(this->m_actNewForm,SIGNAL(triggered(bool)),this,SLOT(ZSlotNewForm()));
    connect(this->m_actOpenForm,SIGNAL(triggered(bool)),this,SLOT(ZSlotOpenForm()));
    connect(this->m_actSaveForm,SIGNAL(triggered(bool)),this,SLOT(ZSlotSaveForm()));
    connect(this->m_actDelForm,SIGNAL(triggered(bool)),this,SLOT(ZSlotDelForm()));
    this->m_menuFormOp=new QMenu;
    this->m_menuFormOp->addAction(this->m_actNewForm);
    this->m_menuFormOp->addAction(this->m_actOpenForm);
    this->m_menuFormOp->addAction(this->m_actSaveForm);
    this->m_menuFormOp->addAction(this->m_actDelForm);
    this->m_tbFormOp->setMenu(this->m_menuFormOp);
    this->m_tbFormOp->setPopupMode(QToolButton::InstantPopup);

    this->m_tbFormComponent=new QToolButton;
    this->m_tbFormComponent->setToolTip(tr("系统组件"));
    this->m_tbFormComponent->setText(tr("组件"));
    this->m_tbFormComponent->setIcon(QIcon(":/FormDesigner/images/FormDesigner/ComponentOp.png"));
    this->m_tbFormComponent->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_actAddLine=new QAction(QIcon(":/FormDesigner/images/FormDesigner/LineItem.png"),tr("插入直线"),0);
    this->m_actAddRectangle=new QAction(QIcon(":/FormDesigner/images/FormDesigner/RectangleItem.png"),tr("插入矩形"),0);
    this->m_actAddText=new QAction(QIcon(":/FormDesigner/images/FormDesigner/TextItem.png"),tr("插入文本"),0);
    this->m_actAddCheckBox=new QAction(QIcon(":/FormDesigner/images/FormDesigner/CheckBoxItem.png"),tr("插入复选框"),0);
    this->m_actAddSpinBox=new QAction(QIcon(""),tr("插入选值框"),0);
    this->m_actAddDateTime=new QAction(QIcon(""),tr("插入时间日期框"),0);
    this->m_actAddTable=new QAction(QIcon(":/FormDesigner/images/FormDesigner/TableItem.png"),tr("插入表格"),0);
    connect(this->m_actAddLine,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddLine()));
    connect(this->m_actAddRectangle,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddRectangle()));
    connect(this->m_actAddText,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddText()));
    connect(this->m_actAddCheckBox,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddCheckBox()));
    connect(this->m_actAddSpinBox,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddSpinBox()));
    connect(this->m_actAddDateTime,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddDateTimeEdit()));
    connect(this->m_actAddTable,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddTable()));

    this->m_menuFormComp=new QMenu;
    this->m_menuFormComp->addAction(this->m_actAddLine);
    this->m_menuFormComp->addAction(this->m_actAddRectangle);
    this->m_menuFormComp->addAction(this->m_actAddText);
    this->m_menuFormComp->addAction(this->m_actAddCheckBox);
    this->m_menuFormComp->addAction(this->m_actAddSpinBox);
    this->m_menuFormComp->addAction(this->m_actAddDateTime);
    this->m_menuFormComp->addAction(this->m_actAddTable);
    this->m_tbFormComponent->setMenu(this->m_menuFormComp);
    this->m_tbFormComponent->setPopupMode(QToolButton::InstantPopup);


    this->m_tbSelect=new QToolButton;
    this->m_tbSelect->setToolTip(tr("选择操作"));
    this->m_tbSelect->setText(tr("选择"));
    this->m_tbSelect->setIcon(QIcon(":/FormDesigner/images/FormDesigner/SelectOp.png"));
    this->m_tbSelect->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_actSelectAll=new QAction(QIcon(":/FormDesigner/images/FormDesigner/SelectAll.png"),tr("全部选择"),0);
    this->m_actDeSelectAll=new QAction(QIcon(":/FormDesigner/images/FormDesigner/DeSelectAll.png"),tr("取消选择"),0);
    connect(this->m_actSelectAll,SIGNAL(triggered(bool)),this,SLOT(ZSlotSelectAll()));
    connect(this->m_actDeSelectAll,SIGNAL(triggered(bool)),this,SLOT(ZSlotDeSelectAll()));
    this->m_menuSelect=new QMenu;
    this->m_menuSelect->addAction(this->m_actSelectAll);
    this->m_menuSelect->addAction(this->m_actDeSelectAll);
    this->m_tbSelect->setMenu(this->m_menuSelect);
    this->m_tbSelect->setPopupMode(QToolButton::InstantPopup);

    this->m_tbDiagram=new QToolButton;
    this->m_tbDiagram->setToolTip(tr("汇总图表"));
    this->m_tbDiagram->setText(tr("图表"));
    this->m_tbDiagram->setIcon(QIcon(":/FormDesigner/images/FormDesigner/PrintPreview.png"));
    this->m_tbDiagram->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_actBarGraph=new QAction(QIcon(":/FormDesigner/images/FormDesigner/SelectAll.png"),tr("柱状图"),0);
    this->m_actPieGraph=new QAction(QIcon(":/FormDesigner/images/FormDesigner/DeSelectAll.png"),tr("饼图"),0);
    connect(this->m_actBarGraph,SIGNAL(triggered(bool)),this,SLOT(ZSlotBarGraph()));
    connect(this->m_actPieGraph,SIGNAL(triggered(bool)),this,SLOT(ZSlotPieGraph()));
    this->m_menuDiagram=new QMenu;
    this->m_menuDiagram->addAction(this->m_actBarGraph);
    this->m_menuDiagram->addAction(this->m_actPieGraph);
    this->m_tbDiagram->setMenu(this->m_menuDiagram);
    this->m_tbDiagram->setPopupMode(QToolButton::InstantPopup);

    this->m_tbPrintView=new QToolButton;
    this->m_tbPrintView->setToolTip(tr("打印预览"));
    this->m_tbPrintView->setText(tr("预览"));
    this->m_tbPrintView->setIcon(QIcon(":/FormDesigner/images/FormDesigner/PrintPreview.png"));
    this->m_tbPrintView->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbPrint=new QToolButton;
    this->m_tbPrint->setToolTip(tr("打印..."));
    this->m_tbPrint->setText(tr("打印"));
    this->m_tbPrint->setIcon(QIcon(":/FormDesigner/images/FormDesigner/Print.png"));
    this->m_tbPrint->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(this->m_tbPrintView,SIGNAL(clicked(bool)),this,SLOT(ZSlotPrintView()));
    connect(this->m_tbPrint,SIGNAL(clicked(bool)),this,SLOT(ZSlotPrint()));

    //help.
    this->m_btnHelp=new QToolButton;
    this->m_btnHelp->setToolTip(tr("获取帮助文档"));
    this->m_btnHelp->setText(tr("帮助"));
    this->m_btnHelp->setIcon(QIcon(":/common/images/common/help.png"));
    this->m_btnHelp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(this->m_btnHelp,SIGNAL(clicked(bool)),this,SLOT(ZSlotHelp()));

    this->m_vLayoutTb=new QVBoxLayout;
    this->m_vLayoutTb->addWidget(this->m_tbFormOp);
    this->m_vLayoutTb->addWidget(this->m_tbFormComponent);
    this->m_vLayoutTb->addWidget(this->m_tbSelect);
    this->m_vLayoutTb->addWidget(this->m_tbDiagram);
    this->m_vLayoutTb->addWidget(this->m_tbPrintView);
    this->m_vLayoutTb->addWidget(this->m_tbPrint);
    this->m_vLayoutTb->addStretch(1);
    this->m_vLayoutTb->addWidget(this->m_btnHelp);

    this->m_tabWidget=new QTabWidget;
    this->m_tabWidget->setTabsClosable(true);
    this->m_formList=new ZFormList;
    this->m_tabWidget->addTab(this->m_formList,QIcon(":/FormDesigner/images/FormDesigner/FormOp.png"),tr("报表管理"));
    this->m_tabWidget->tabBar()->tabButton(0,QTabBar::RightSide)->hide();

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addLayout(this->m_vLayoutTb);
    this->m_hLayout->addWidget(this->m_tabWidget);
    this->setLayout(this->m_hLayout);

    connect(this->m_tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(ZSlotCloseTab(qint32)));

    connect(this->m_formList->m_tree,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ZSlotOpenForm(QModelIndex)));
    //list all roles and users.
    ZListFormInfoDia *dia=new ZListFormInfoDia(this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteListOp();
    dia->ZShowWaitingDialog();
}
PFormDesigner::~PFormDesigner()
{
    delete this->m_actNewForm;
    delete this->m_actOpenForm;
    delete this->m_actSaveForm;
    delete this->m_actDelForm;
    delete this->m_tbFormOp;

    delete this->m_actAddLine;
    delete this->m_actAddRectangle;
    delete this->m_actAddText;
    delete this->m_actAddCheckBox;
    delete this->m_actAddDateTime;
    delete this->m_actAddSpinBox;
    delete this->m_actAddTable;
    delete this->m_menuFormComp;
    delete this->m_tbFormComponent;

    delete this->m_actSelectAll;
    delete this->m_actDeSelectAll;
    delete this->m_menuSelect;
    delete this->m_tbSelect;

    delete this->m_actBarGraph;
    delete this->m_actPieGraph;
    delete this->m_menuDiagram;
    delete this->m_tbDiagram;

    delete this->m_tbPrint;
    delete this->m_tbPrintView;
    delete this->m_vLayoutTb;

    delete this->m_formList;
    delete this->m_tabWidget;

    delete this->m_hLayout;
}
void PFormDesigner::ZAddLogMsg(QString logMsg)
{
    emit this->ZSignalLogMsg(QString("<FormDesigner>:")+logMsg);
}
void PFormDesigner::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{
    if(item=="form")
    {
        if(cmd=="add")
        {
            if(ackNetRetCode<0)
            {
                QString formName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("add form [%1] failed:[%2].").arg(formName).arg(errMsg));
            }else{
                QString formName=paraList.at(0);
                QString creator=paraList.at(1);
                QString createTime=paraList.at(2);

                QTreeWidgetItem *formItem=new QTreeWidgetItem(0);
                formItem->setIcon(0,QIcon(":/FormDesigner/images/FormDesigner/FormOp.png"));
                formItem->setText(0,formName);
                formItem->setText(1,QString("0"));
                formItem->setText(2,creator);
                formItem->setText(3,createTime);
                this->m_formList->m_tree->addTopLevelItem(formItem);
                this->m_formList->m_tree->setCurrentItem(formItem);
                this->ZAddLogMsg(tr("add form [%1] success.").arg(formName));
            }
        }else if(cmd=="del")
        {
            if(ackNetRetCode<0)
            {
                QString formName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("delete form [%1] failed:[%2].").arg(formName).arg(errMsg));
            }else{
                //delete formItem from treeWidget.
                QString formName=paraList.at(0);
                QString creator=paraList.at(1);
                for(qint32 i=0;i<this->m_formList->m_tree->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *formItem=this->m_formList->m_tree->topLevelItem(i);
                    if(formItem->text(0)==formName)
                    {
                        this->m_formList->m_tree->takeTopLevelItem(i);
                        delete formItem;
                        formItem=NULL;
                        break;
                    }
                }
                //close sheet in tab.
                for(qint32 i=1;i<this->m_tabWidget->count();i++)
                {
                    ZFormWidget *formWidget=qobject_cast<ZFormWidget*>(this->m_tabWidget->widget(i));
                    if(formWidget)
                    {
                        if(formWidget->ZGetFormName()==formName)
                        {
                            this->m_tabWidget->removeTab(i);
                            delete formWidget;
                            formWidget=NULL;
                            break;
                        }
                    }
                }
                this->ZAddLogMsg(tr("delete form [%1] success.").arg(formName));
            }
        }else if(cmd=="get")
        {
            if(ackNetRetCode<0)
            {
                QString formName=paraList.at(0);
                QString errMsg=paraList.at(1);
                ZFormWidget *formWidget=new ZFormWidget;
                formWidget->ZSetFormName(formName);
                this->m_tabWidget->addTab(formWidget,QIcon(":/FormDesigner/images/FormDesigner/FormOp.png"),formName);
                this->m_tabWidget->setCurrentWidget(formWidget);
                connect(formWidget,SIGNAL(ZSignalDataChanged()),this,SLOT(ZSlotFormChanged()));
                this->ZAddLogMsg(tr("get form [%1] failed:[%2]").arg(formName).arg(errMsg));
            }else{
                QString formName=paraList.at(0);
                QString data=paraList.at(1);
                QString creator=paraList.at(2);
                //add form in tab.
                ZFormWidget *formWidget=new ZFormWidget;
                formWidget->ZSetFormName(formName);
                formWidget->ZPutXmlData(data);
                this->m_tabWidget->addTab(formWidget,QIcon(":/FormDesigner/images/FormDesigner/FormOp.png"),formName);
                this->m_tabWidget->setCurrentWidget(formWidget);
                connect(formWidget,SIGNAL(ZSignalDataChanged()),this,SLOT(ZSlotFormChanged()));
                this->ZAddLogMsg(tr("get form [%1] success,creator:%2.").arg(formName).arg(creator));
            }
        }else if(cmd=="save")
        {
            if(ackNetRetCode<0)
            {
                QString formName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("save form [%1] failed:[%2].").arg(formName).arg(errMsg));
            }else{
                QString formName=paraList.at(0);
                QString fileSize=paraList.at(1);
                this->ZAddLogMsg(tr("save form [%1] success.").arg(formName));
                //remove <*> from tab.
                for(qint32 i=1;i<this->m_tabWidget->count();i++)
                {
                    if(this->m_tabWidget->tabText(i)=="<*>"+formName)
                    {
                        this->m_tabWidget->setTabText(i,formName);
                        break;
                    }
                }
                //add fileSize on form tree.
                for(qint32 i=0;i<this->m_formList->m_tree->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_formList->m_tree->topLevelItem(i);
                    if(item->text(0)==formName)
                    {
                        item->setText(1,fileSize+"K");
                        break;
                    }
                }
            }
        }else if(cmd=="list")
        {
            QString formName=paraList.at(0);
            QString fileSize=paraList.at(1);
            QString creator=paraList.at(2);
            QString createTime=paraList.at(3);
            QTreeWidgetItem *formItem=new QTreeWidgetItem(0);
            formItem->setIcon(0,QIcon(":/FormDesigner/images/FormDesigner/FormOp.png"));
            formItem->setText(0,formName);
            formItem->setText(1,fileSize);
            formItem->setText(2,creator);
            formItem->setText(3,createTime);
            this->m_formList->m_tree->addTopLevelItem(formItem);
            this->m_formList->m_tree->setCurrentItem(formItem);
            this->ZAddLogMsg(tr("list form [%1] success.").arg(formName));
            for(qint32 i=0;i<this->m_formList->m_tree->columnCount();i++)
            {
                this->m_formList->m_tree->resizeColumnToContents(i);
            }
        }
    }
    QCoreApplication::processEvents();
}
void PFormDesigner::closeEvent(QCloseEvent *event)
{
    emit this->ZSignalCloseEvent("FormDesigner");
    QFrame::closeEvent(event);
}
void PFormDesigner::ZSlotNewForm()
{
    ZFormInfoDia *dia=new ZFormInfoDia(ZFormInfoDia::Type_NewForm,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PFormDesigner::ZSlotOpenForm()
{
    if(this->m_tabWidget->currentIndex()!=0)
    {
        return;
    }
    QTreeWidgetItem *item=this->m_formList->m_tree->currentItem();
    if(item==NULL)
    {
        return;
    }
    ZFormInfoDia *dia=new ZFormInfoDia(ZFormInfoDia::Type_GetForm,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetFormName(item->text(0));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PFormDesigner::ZSlotOpenForm(QModelIndex index)
{
    QTreeWidgetItem *item=this->m_formList->m_tree->currentItem();
    if(item==NULL)
    {
        return;
    }
    ZFormInfoDia *dia=new ZFormInfoDia(ZFormInfoDia::Type_GetForm,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetFormName(item->text(0));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PFormDesigner::ZSlotSaveForm()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }
    ZFormInfoDia *dia=new ZFormInfoDia(ZFormInfoDia::Type_SaveForm,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetFormName(widget->ZGetFormName());
    dia->ZSetFormXmlData(widget->ZGetXmlData());
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PFormDesigner::ZSlotDelForm()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    QTreeWidgetItem *item=this->m_formList->m_tree->currentItem();
    if(item==NULL)
    {
        return;
    }
    ZFormInfoDia *dia=new ZFormInfoDia(ZFormInfoDia::Type_DelForm,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetFormName(item->text(0));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PFormDesigner::ZSlotSelectAll()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }
    if(!widget->ZIsEditable())
    {
        return;
    }
    QList<QGraphicsItem*> list=widget->m_scene->items();
    for(qint32 i=0;i<list.count();i++)
    {
        QGraphicsItem* item=list.at(i);
        if(item->type()==QGraphicsProxyWidget::Type)
        {
            QGraphicsProxyWidget *proxyWid=qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
            if(proxyWid)
            {
                ZBaseWidget *bw=qobject_cast<ZBaseWidget*>(proxyWid->widget());
                if(bw)
                {
                    bw->ZSetEditMode(true);
                }
            }
        }
    }
    emit this->ZSignalLogMsg(tr("Select all items,count=%1.").arg(list.count()));
}
void PFormDesigner::ZSlotDeSelectAll()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }
    QList<QGraphicsItem*> list=widget->m_scene->items();
    for(qint32 i=0;i<list.count();i++)
    {
        QGraphicsItem* item=list.at(i);
        if(item->type()==QGraphicsProxyWidget::Type)
        {
            QGraphicsProxyWidget *proxyWid=qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
            if(proxyWid)
            {
                ZBaseWidget *bw=qobject_cast<ZBaseWidget*>(proxyWid->widget());
                if(bw)
                {
                    bw->ZSetEditMode(false);
                }
            }
        }
    }
    emit this->ZSignalLogMsg(tr("DeSelect all items,count=%1.").arg(list.count()));
}
void PFormDesigner::ZSlotAddRectangle()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }
    if(!widget->ZIsEditable())
    {
        return;
    }
    widget->m_view->ZAddRectangle();
    emit this->ZSignalLogMsg(tr("Add new Rectangle item."));
}
void PFormDesigner::ZSlotAddCheckBox()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }
    if(!widget->ZIsEditable())
    {
        return;
    }
    widget->m_view->ZAddCheckBox();
    emit this->ZSignalLogMsg(tr("Add new CheckBox item."));
}
void PFormDesigner::ZSlotAddSpinBox()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }
    if(!widget->ZIsEditable())
    {
        return;
    }
    widget->m_view->ZAddSpinBox();
    emit this->ZSignalLogMsg(tr("Add new SpinBox item."));
}
void PFormDesigner::ZSlotAddDateTimeEdit()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }
    if(!widget->ZIsEditable())
    {
        return;
    }
    widget->m_view->ZAddDateTimeEdit();
    emit this->ZSignalLogMsg(tr("Add new DateTime item."));
}
void PFormDesigner::ZSlotAddTable()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }
    if(!widget->ZIsEditable())
    {
        return;
    }
    widget->m_view->ZAddTable();
    emit this->ZSignalLogMsg(tr("Add new Table item."));
}
void PFormDesigner::ZSlotAddText()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }
    if(!widget->ZIsEditable())
    {
        return;
    }
    widget->m_view->ZAddText();
    emit this->ZSignalLogMsg(tr("Add new Text item."));
}
void PFormDesigner::ZSlotAddLine()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }
    if(!widget->ZIsEditable())
    {
        return;
    }
    widget->m_view->ZAddLine();
    emit this->ZSignalLogMsg(tr("Add new Line item."));
}
void PFormDesigner::ZSlotFormChanged()
{
    qint32 index=this->m_tabWidget->currentIndex();
    if(index==0)
    {
        return;
    }
    if(!this->m_tabWidget->tabText(index).startsWith("<*>"))
    {
        this->m_tabWidget->setTabText(index,"<*>"+this->m_tabWidget->tabText(index));
    }
}
void PFormDesigner::ZSlotCloseTab(qint32 index)
{
    if(index==0)
    {
        return;
    }
    if(this->m_tabWidget->tabText(index).startsWith("<*>"))
    {
        if(QMessageBox::question(this,tr("操作提示"),tr("报表被更改,尚未保存!\n您确认要关闭吗?"),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
        {
            return;
        }
    }

    //delete it to remove it from tab widget.
    this->m_tabWidget->removeTab(index);
    delete this->m_tabWidget->widget(index);
}
void PFormDesigner::ZSlotBarGraph()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }
    if(!widget->ZIsEditable())
    {
        return;
    }
    widget->m_view->ZAddBarGraph();
    emit this->ZSignalLogMsg(tr("Add new barGraph item."));
}
void PFormDesigner::ZSlotPieGraph()
{

}
void PFormDesigner::ZSlotPrint()
{
#if 0
    QPrintDialog dia(this);
    connect(&dia,SIGNAL(accepted(QPrinter*)),this,SLOT(ZSlotDoPrinter(QPrinter*)));
    dia.exec();
#endif
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }

    QImage img(widget->m_view->width(),widget->m_view->height(),QImage::Format_ARGB32);
    img.fill(Qt::white);
    QString pngFileName("report.png");
    QPainter painter(&img);
    painter.setRenderHint(QPainter::Antialiasing);
    widget->m_view->render(&painter);
    img.save(pngFileName);
}
void PFormDesigner::ZSlotHelp()
{

}
void PFormDesigner::ZSlotPrintView()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }
    QString formName=QObject::tr("报表:")+widget->ZGetFormName();

    KDReports::Report report;
    report.setMargins(2,2,2,2);
    report.setHeaderBodySpacing(6); // mm
    report.setFooterBodySpacing(6); // mm
    report.setWatermarkPixmap(QPixmap(":/LoginManager/images/LoginManager/Logo.png"));
    KDReports::Header &header=report.header();
    header.addElement(KDReports::TextElement(formName),Qt::AlignLeft);
    header.addElement(KDReports::TextElement("PMS流水线综合管控系统"),Qt::AlignHCenter);
    header.addElement(KDReports::TextElement("Page "),Qt::AlignRight);
    header.addVariable( KDReports::PageNumber );
    header.addInlineElement( KDReports::TextElement(" / "));
    header.addVariable( KDReports::PageCount );
    report.setHeaderLocation(KDReports::AllPages,&header);

    //    KDReports::Header& header = report.header( KDReports::FirstPage );
    //    header.addElement( KDReports::TextElement( "A tall image made to fit into the page" ) );

    //    KDReports::Header& header2 = report.header( KDReports::EvenPages );
    //    header2.addElement( KDReports::TextElement( "A wide image made to fit into the page" ) );

    //    KDReports::Footer& footer = report.footer();
    //    footer.addElement( KDReports::TextElement( "Page" ), Qt::AlignRight );
    //    footer.addInlineElement( KDReports::TextElement( " " ) );
    //    footer.addVariable( KDReports::PageNumber );
    //    footer.addInlineElement( KDReports::TextElement( "/" ) );
    //    footer.addVariable( KDReports::PageCount );

    //    KDReports::ImageElement imageElement( QPixmap( ":/background/images/background/background_main.png" ) );
    //    imageElement.setFitToPage();
    //    report.addElement( imageElement );

    //    KDReports::ImageElement imageElement2( QPixmap( ":/background/images/background/background_main.png" ) );
    //    imageElement2.setFitToPage();
    //    report.addElement( imageElement2 );

    //    KDReports::PreviewDialog preview( &report );
    //    preview.exec();



    //    KDReports::TextElement titleElement(QObject::tr("Hello world"));
    //    titleElement.setPointSize(20);
    //    report.addElement(titleElement,Qt::AlignHCenter);
    //    report.addVerticalSpacing(20);
    //    KDReports::TextElement textElement(QObject::tr("This is a report generated with KD Report"));
    //    report.addElement(textElement,Qt::AlignLeft);
    //    KDReports::PreviewDialog preview(&report);
    //    preview.exec();

    // open a DB connection to an in-memory database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if( !db.open() ) {
        QMessageBox::critical(0, QObject::tr("Cannot open database"),
                              QObject::tr("Cannot create connection to the requested database. Your Qt is probably lacking the QSQLITE driver. Please check your Qt installation." ), QMessageBox::Cancel );
        return;
    }

    // fill the DB with some test data
    QSqlQuery query;
    query.exec("create table airlines (id int primary key, "
               "name varchar(20), homecountry varchar(2))");
    query.exec("insert into airlines values(1, 'Lufthansa', 'DE')");
    query.exec("insert into airlines values(2, 'SAS', 'SE')");
    query.exec("insert into airlines values(3, 'United', 'US')");
    query.exec("insert into airlines values(4, 'KLM', 'NL')");
    query.exec("insert into airlines values(5, 'Aeroflot', 'RU')");

    // Create a QSqlTableModel, connect to the previously created database, fill
    // the db with some data.
    QSqlTableModel tableModel( 0, db );
    tableModel.setTable( "airlines" );
    tableModel.select();
    tableModel.removeColumn( 0 );
    tableModel.setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
    tableModel.setHeaderData(1, Qt::Horizontal, QObject::tr("Home country"));
    QFont font = this->font();
    font.setBold( true );
    tableModel.setHeaderData( 0, Qt::Horizontal, font, Qt::FontRole );
    tableModel.setHeaderData( 1, Qt::Horizontal, font, Qt::FontRole );

    KDReports::AutoTableElement table1( &tableModel );
    table1.setVerticalHeaderVisible( false );
    report.addElement( table1 );

    report.addPageBreak();
    // To export to an image file:
    //qDebug() << "Exporting to output.png";
    //report.exportToImage( QSize(300, 400), "output.png", "PNG" );

    // ===========================================================================
    // Another kind of table, where the data comes from code and not from a model:
    // ===========================================================================
    KDReports::TableElement tableElement;
    tableElement.setHeaderRowCount( 2 );
    tableElement.setPadding( 3 );
    QColor headerColor( "#DADADA" );
    // Merged header in row 0
    KDReports::Cell& topHeader = tableElement.cell( 0, 0 );
    topHeader.setColumnSpan( 2 );
    topHeader.setBackground( headerColor );
    topHeader.addElement( KDReports::TextElement( "TableElement example" ), Qt::AlignHCenter );

    // Normal header in row 1
    KDReports::Cell& headerCell1 = tableElement.cell( 1, 0 );
    headerCell1.setBackground( headerColor );
    // This would look better if centered vertically. This feature is only available since
    // Qt-4.3 though (QTextCharFormat::AlignMiddle)
    QPixmap systemPixmap( ":/LoginManager/images/LoginManager/User.png" );
    headerCell1.addElement( KDReports::ImageElement( systemPixmap ) );
    headerCell1.addInlineElement( KDReports::TextElement( " Item" ) );
    KDReports::Cell& headerCell2 = tableElement.cell( 1, 1 );
    headerCell2.setBackground( headerColor );
    KDReports::TextElement expected( "Expected" );
    expected.setItalic( true );
    expected.setBackground( QColor("#999999") ); // note that this background only applies to this element
    headerCell2.addElement( expected );
    headerCell2.addInlineElement( KDReports::TextElement( " shipping time" ) );

    // Data in rows 2 and 3
    tableElement.cell( 2, 0 ).addElement( KDReports::TextElement( "Network Peripherals" ) );
    tableElement.cell( 2, 1 ).addElement( KDReports::TextElement( "4 days" ) );
    tableElement.cell( 3, 0 ).addElement( KDReports::TextElement( "Printer Cartridges" ) );
    tableElement.cell( 3, 1 ).addElement( KDReports::TextElement( "3 days" ) );

    report.addElement( tableElement );

    KDReports::PreviewDialog preview( &report );
    preview.exec();
}
void PFormDesigner::ZSlotDoPrinter(QPrinter *printer)
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;
    }
    ZFormWidget *widget=qobject_cast<ZFormWidget*>(this->m_tabWidget->currentWidget());
    if(widget==NULL)
    {
        return;
    }
#if 0
    QPainter painter(printer);
    //print all element in scene.
    QList<QGraphicsItem*> list=widget->m_scene->items();
    for(qint32 i=0;i<list.count();i++)
    {
        QGraphicsItem* item=list.at(i);
        if(item->type()==QGraphicsProxyWidget::Type)
        {
            QGraphicsProxyWidget *proxyWid=qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
            if(proxyWid)
            {
                ZLineWidget *lw=qobject_cast<ZLineWidget*>(proxyWid->widget());
                if(lw)
                {
                    QPen pen;
                    pen.setColor(lw->m_lineItem->ZGetColor());
                    pen.setWidth(lw->m_lineItem->ZGetWidth());
                    painter.setPen(pen);
                    painter.drawLine(QPoint(lw->x(),lw->y()),QPoint(lw->x()+lw->width(),lw->y()));
                }
                ZRectangleWidget *rw=qobject_cast<ZRectangleWidget*>(proxyWid->widget());
                if(rw)
                {
                    painter.fillRect(QRectF(rw->x(),rw->y(),rw->width(),rw->height()),rw->ZGetColor());
                }
                ZTextWidget *tw=qobject_cast<ZTextWidget*>(proxyWid->widget());
                if(tw)
                {
                    painter.drawText(QRectF(tw->x(),tw->y(),tw->width(),tw->height()),tw->m_llText->text());
                }
            }
        }
    }
#endif
}
