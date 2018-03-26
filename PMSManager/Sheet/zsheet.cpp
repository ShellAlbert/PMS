#include "zsheet.h"
#include <qlabel.h>
#include <QBuffer>
#include <QPixmap>
#include <QInputDialog>
#include <QMessageBox>
ZSheet::ZSheet(QWidget *parent):QTableWidget(parent)
{
    this->m_cellDelegate=new ZCellDelegate;
    this->setItemDelegate(this->m_cellDelegate);
    this->setRowCount(TABLE_ROW_COUNT);
    this->setColumnCount(TABLE_COL_COUNT);

    //at default,initial all unit to ZCell object.
    for(qint32 i=0;i<this->rowCount();i++)
    {
        for(qint32 j=0;j<this->columnCount();j++)
        {
            ZCell *tCell=new ZCell;
            tCell->ZSetCellWidgetType(ZCell::CellWidget_No);
            this->setItem(i,j,tCell);
        }
    }

    //emit signal when the data was changed.
    connect(this,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(ZSlotItemEntered()));

    this->m_popupMenu=new QMenu(this);

    this->m_actBindVar=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/BindVar.png"),tr("绑定变量"),this);
    connect(this->m_actBindVar,SIGNAL(triggered()),this,SIGNAL(ZSignalBindVar()));
    this->m_actUnbindVar=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/UnbindVar.png"),tr("解绑变量"),this);
    connect(this->m_actUnbindVar,SIGNAL(triggered()),this,SIGNAL(ZSignalUnbindVar()));

    this->m_subMenuAlign=new QMenu(tr("对齐方式"));
    this->m_actionHAlignLeft=new QAction(QIcon(":/alignment/images/alignment/HAlignLeft.png"),tr("左对齐"),this);
    connect(this->m_actionHAlignLeft,SIGNAL(triggered()),this,SLOT(ZSlotHAlignLeft()));

    this->m_actionHAlignCenter=new QAction(QIcon(":/alignment/images/alignment/HAlignCenter.png"),tr("水平居中"),this);
    connect(this->m_actionHAlignCenter,SIGNAL(triggered()),this,SLOT(ZSlotHAlignCenter()));

    this->m_actionHAlignRight=new QAction(QIcon(":/alignment/images/alignment/HAlignRight.png"),tr("右对齐"),this);
    connect(this->m_actionHAlignRight,SIGNAL(triggered()),this,SLOT(ZSlotHAlignRight()));

    this->m_actionVAlignTop=new QAction(QIcon(":/alignment/images/alignment/VAlignTop.png"),tr("上对齐"),this);
    connect(this->m_actionVAlignTop,SIGNAL(triggered()),this,SLOT(ZSlotVAlignTop()));

    this->m_actionVAlignCenter=new QAction(QIcon(":/alignment/images/alignment/VAlignCenter.png"),tr("垂直居中"),this);
    connect(this->m_actionVAlignCenter,SIGNAL(triggered()),this,SLOT(ZSlotVAlignCenter()));

    this->m_actionVAlignBottom=new QAction(QIcon(":/alignment/images/alignment/VAlignBottom.png"),tr("下对齐"),this);
    connect(this->m_actionVAlignBottom,SIGNAL(triggered()),this,SLOT(ZSlotVAlignBottom()));

    this->m_actionMerge=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/Merge.png"),tr("合并"),this);
    connect(this->m_actionMerge,SIGNAL(triggered()),this,SLOT(ZSlotMerge()));
    this->m_actionSplit=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/Split.png"),tr("拆分"),this);
    connect(this->m_actionSplit,SIGNAL(triggered()),this,SLOT(ZSlotSplit()));

    this->m_actFastRemoveWidget=new QAction(QIcon(":/common/images/common/del.png"),tr("快速移除组件"),this);
    connect(this->m_actFastRemoveWidget,SIGNAL(triggered(bool)),this,SLOT(ZSlotFastRemoveWidget()));
    this->m_actRemoveWidget=new QAction(QIcon(":/common/images/common/del.png"),tr("移除组件..."),this);
    connect(this->m_actRemoveWidget,SIGNAL(triggered(bool)),this,SLOT(ZSlotRemoveWidget()));


    this->m_subMenuAlign->addSection(tr("HAlign"));
    this->m_subMenuAlign->addAction(this->m_actionHAlignLeft);
    this->m_subMenuAlign->addAction(this->m_actionHAlignCenter);
    this->m_subMenuAlign->addAction(this->m_actionHAlignRight);
    this->m_subMenuAlign->addSection(tr("VAlign"));
    this->m_subMenuAlign->addAction(this->m_actionVAlignTop);
    this->m_subMenuAlign->addAction(this->m_actionVAlignCenter);
    this->m_subMenuAlign->addAction(this->m_actionVAlignBottom);

    this->m_popupMenu->addSection(tr("BindUnBind"));
    this->m_popupMenu->addAction(this->m_actBindVar);
    this->m_popupMenu->addAction(this->m_actUnbindVar);
    this->m_popupMenu->addSection(tr("Alignment"));
    this->m_popupMenu->addMenu(this->m_subMenuAlign);
    this->m_popupMenu->addSection(tr("Cell Command"));
    this->m_popupMenu->addAction(this->m_actionMerge);
    this->m_popupMenu->addAction(this->m_actionSplit);
    this->m_popupMenu->addAction(this->m_actFastRemoveWidget);
    this->m_popupMenu->addAction(this->m_actRemoveWidget);
}

ZSheet::~ZSheet()
{
    delete this->m_cellDelegate;
    delete this->m_actBindVar;
    delete this->m_actUnbindVar;
    delete this->m_actionHAlignLeft;
    delete this->m_actionHAlignCenter;
    delete this->m_actionHAlignRight;
    delete this->m_actionVAlignTop;
    delete this->m_actionVAlignCenter;
    delete this->m_actionVAlignBottom;
    delete this->m_subMenuAlign;
    delete this->m_actionMerge;
    delete this->m_actionSplit;
    delete this->m_actFastRemoveWidget;
    delete this->m_actRemoveWidget;
    delete this->m_popupMenu;
}
void ZSheet::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton)
    {
        this->m_popupMenu->popup(QCursor::pos());
    }
    QTableWidget::mousePressEvent(event);
}
void ZSheet::ZSlotItemEntered()
{
    emit this->ZSignalSheetChanged(this->ZGetTemplateName());
}
QString ZSheet::ZGetProcessName()
{
    return this->m_processName;
}
void ZSheet::ZSetProcessName(QString processName)
{
    this->m_processName=processName;
}
QString ZSheet::ZGetStepName()
{
    return this->m_stepName;
}
void ZSheet::ZSetStepName(QString stepName)
{
    this->m_stepName=stepName;
}
QString ZSheet::ZGetTemplateName()
{
    return this->m_templateName;
}
void ZSheet::ZSetTemplateName(QString templateName)
{
    this->m_templateName=templateName;
}
QString ZSheet::ZGetSheetName()
{
    return this->m_sheetName;
}
void ZSheet::ZSetSheetName(QString sheetName)
{
    this->m_sheetName=sheetName;
}

ZSheet::ZSheetState ZSheet::ZGetSheetState()
{
    return this->m_sheetState;
}
void ZSheet::ZSetSheetState(ZSheetState sheetState)
{
    this->m_sheetState=sheetState;
}

//cell delegate.
ZCellDelegate* ZSheet::ZGetCellDelegate()
{
    return this->m_cellDelegate;
}

//load template sheet xml.
bool ZSheet::ZLoadTemplateSheetByName(QString templateName)
{
    if(templateName.isEmpty())
    {
        return false;
    }
    return false;
}
void ZSheet::ZSlotHAlignLeft()
{
    qint32 tRow=this->selectedRanges().first().topRow();
    qint32 tColumn=this->selectedRanges().first().leftColumn();
    qint32 tRowCnt=this->selectedRanges().last().bottomRow()-this->selectedRanges().first().topRow() + 1;
    qint32 tColumnCnt=this->selectedRanges().last().rightColumn()-this->selectedRanges().first().leftColumn() + 1;
    for(qint32 i=tRow;i<=tRow+tRowCnt;i++)
    {
        for(qint32 j=tColumn;j<=tColumn+tColumnCnt;j++)
        {
            qint32 tAlignment=this->item(i,j)->textAlignment();
            tAlignment&=~Qt::AlignLeft;
            tAlignment&=~Qt::AlignHCenter;
            tAlignment&=~Qt::AlignRight;
            this->item(i,j)->setTextAlignment(tAlignment|Qt::AlignLeft);
        }
    }
}
void ZSheet::ZSlotHAlignCenter()
{
    qint32 tRow=this->selectedRanges().first().topRow();
    qint32 tColumn=this->selectedRanges().first().leftColumn();
    qint32 tRowCnt=this->selectedRanges().last().bottomRow()-this->selectedRanges().first().topRow() + 1;
    qint32 tColumnCnt=this->selectedRanges().last().rightColumn()-this->selectedRanges().first().leftColumn() + 1;
    for(qint32 i=tRow;i<=tRow+tRowCnt;i++)
    {
        for(qint32 j=tColumn;j<=tColumn+tColumnCnt;j++)
        {
            qint32 tAlignment=this->item(i,j)->textAlignment();
            tAlignment&=~Qt::AlignLeft;
            tAlignment&=~Qt::AlignHCenter;
            tAlignment&=~Qt::AlignRight;
            this->item(i,j)->setTextAlignment(tAlignment|Qt::AlignHCenter);
        }
    }
}
void ZSheet::ZSlotHAlignRight()
{

    qint32 tRow=this->selectedRanges().first().topRow();
    qint32 tColumn=this->selectedRanges().first().leftColumn();
    qint32 tRowCnt=this->selectedRanges().last().bottomRow()-this->selectedRanges().first().topRow() + 1;
    qint32 tColumnCnt=this->selectedRanges().last().rightColumn()-this->selectedRanges().first().leftColumn() + 1;
    for(qint32 i=tRow;i<=tRow+tRowCnt;i++)
    {
        for(qint32 j=tColumn;j<=tColumn+tColumnCnt;j++)
        {
            qint32 tAlignment=this->item(i,j)->textAlignment();
            tAlignment&=~Qt::AlignLeft;
            tAlignment&=~Qt::AlignHCenter;
            tAlignment&=~Qt::AlignRight;
            this->item(i,j)->setTextAlignment(tAlignment|Qt::AlignRight);
        }
    }
}
void ZSheet::ZSlotVAlignTop()
{
    qint32 tRow=this->selectedRanges().first().topRow();
    qint32 tColumn=this->selectedRanges().first().leftColumn();
    qint32 tRowCnt=this->selectedRanges().last().bottomRow()-this->selectedRanges().first().topRow() + 1;
    qint32 tColumnCnt=this->selectedRanges().last().rightColumn()-this->selectedRanges().first().leftColumn() + 1;
    for(qint32 i=tRow;i<=tRow+tRowCnt;i++)
    {
        for(qint32 j=tColumn;j<=tColumn+tColumnCnt;j++)
        {
            qint32 tAlignment=this->item(i,j)->textAlignment();
            tAlignment&=~Qt::AlignTop;
            tAlignment&=~Qt::AlignVCenter;
            tAlignment&=~Qt::AlignBottom;
            this->item(i,j)->setTextAlignment(tAlignment|Qt::AlignTop);
        }
    }
}
void ZSheet::ZSlotVAlignCenter()
{
    qint32 tRow=this->selectedRanges().first().topRow();
    qint32 tColumn=this->selectedRanges().first().leftColumn();
    qint32 tRowCnt=this->selectedRanges().last().bottomRow()-this->selectedRanges().first().topRow() + 1;
    qint32 tColumnCnt=this->selectedRanges().last().rightColumn()-this->selectedRanges().first().leftColumn() + 1;
    for(qint32 i=tRow;i<=tRow+tRowCnt;i++)
    {
        for(qint32 j=tColumn;j<=tColumn+tColumnCnt;j++)
        {
            qint32 tAlignment=this->item(i,j)->textAlignment();
            tAlignment&=~Qt::AlignTop;
            tAlignment&=~Qt::AlignVCenter;
            tAlignment&=~Qt::AlignBottom;
            this->item(i,j)->setTextAlignment(tAlignment|Qt::AlignVCenter);
        }
    }
}
void ZSheet::ZSlotVAlignBottom()
{
    qint32 tRow=this->selectedRanges().first().topRow();
    qint32 tColumn=this->selectedRanges().first().leftColumn();
    qint32 tRowCnt=this->selectedRanges().last().bottomRow()-this->selectedRanges().first().topRow() + 1;
    qint32 tColumnCnt=this->selectedRanges().last().rightColumn()-this->selectedRanges().first().leftColumn() + 1;
    for(qint32 i=tRow;i<=tRow+tRowCnt;i++)
    {
        for(qint32 j=tColumn;j<=tColumn+tColumnCnt;j++)
        {
            qint32 tAlignment=this->item(i,j)->textAlignment();
            tAlignment&=~Qt::AlignTop;
            tAlignment&=~Qt::AlignVCenter;
            tAlignment&=~Qt::AlignBottom;
            this->item(i,j)->setTextAlignment(tAlignment|Qt::AlignBottom);
        }
    }
}
void ZSheet::ZSlotMerge()
{

}
void ZSheet::ZSlotSplit()
{

}
void ZSheet::ZSlotFastRemoveWidget()
{
    ZCell* tCell=static_cast<ZCell*>(this->currentItem());
    if(!tCell)
    {
        return;
    }
    QWidget *oldWidget=this->cellWidget(this->currentIndex().row(),this->currentIndex().column());
    if(oldWidget)
    {
        delete oldWidget;
        oldWidget=NULL;

        ZCell *newCell=new ZCell;
        newCell->ZSetCellWidgetType(ZCell::CellWidget_No);
        this->setItem(this->currentIndex().row(),this->currentIndex().column(),newCell);
    }
}
void ZSheet::ZSlotRemoveWidget()
{
    QString xyText=QInputDialog::getText(this,tr("目标坐标"),tr("请输入要移除组件的单元格坐标(例如: 1,1)"));
    if(xyText.isEmpty())
    {
        return;
    }
    QStringList xyList=xyText.split(",");
    if(2!=xyList.size())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("错误的坐标!"));
        return;
    }
    qint32 x=xyList.at(0).toInt();
    qint32 y=xyList.at(1).toInt();
    if(!(x>=0 && x<=TABLE_ROW_COUNT-1) || !(y>=0 && y<=TABLE_COL_COUNT-1))
    {
        QMessageBox::critical(this,tr("错误提示"),tr("错误的坐标!"));
        return;
    }
    QWidget *oldWidget=this->cellWidget(x-1,y-1);
    if(oldWidget)
    {
        delete oldWidget;
        oldWidget=NULL;

        ZCell *newCell=new ZCell;
        newCell->ZSetCellWidgetType(ZCell::CellWidget_No);
        this->setItem(x-1,y-1,newCell);
    }
}
//for print html.
QString ZSheet::ZGetPrintHtml()
{
    if(!this->selectedRanges().size())
    {
        //this->setCurrentCell(0,0);
        return "";
    }

    qint32 tRow=this->selectedRanges().first().topRow();
    qint32 tColumn=this->selectedRanges().first().leftColumn();
    qint32 tRowCnt=this->selectedRanges().last().bottomRow()-this->selectedRanges().first().topRow() + 1;
    qint32 tColumnCnt=this->selectedRanges().last().rightColumn()-this->selectedRanges().first().leftColumn() + 1;
    //find out the invalid cells.
    QList<QString> tInvalidCellsList;
    for(qint32 i=tRow;i<tRow+tRowCnt;i++)
    {
        for(qint32 j=tColumn;j<tColumn+tColumnCnt;j++)
        {
            QString tKey=QString("%1,%2").arg(i).arg(j);
            if(tInvalidCellsList.contains(tKey))
            {
                continue;
            }
            qint32 tRowSpan=this->rowSpan(i,j);
            qint32 tColSpan=this->columnSpan(i,j);
            if(tRowSpan>1 || tColSpan>1)
            {
                for(qint32 m=i;m<i+tRowSpan;m++)
                {
                    for(qint32 n=j;n<j+tColSpan;n++)
                    {
                        if(m==i && n==j)
                        {
                            //bypass myself.
                            continue;
                        }
                        QString tKey=QString("%1,%2").arg(m).arg(n);
                        tInvalidCellsList.append(tKey);
                    }
                }
            }
        }
    }
    //generate html.
    qreal tColWidth=100.0/tColumnCnt;
    QString tHtml;
    tHtml.append("<html>");
    tHtml.append("<head>");
    tHtml.append("<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\"/>");
    tHtml.append(QString("<style type=\"text/css\">body{font-size:12px;}table td{width:%1%;}table tr td{word-break:break-all;}</style>").arg(tColWidth));
    tHtml.append("</head>");
    tHtml.append("<body>");
    tHtml.append("<table width=\"100%\" height=\"100%\" border=\"1\" cellpadding=\"0\" cellspacing=\"0\">");
    tHtml.append("\n");
    for(qint32 i=tRow;i<tRow+tRowCnt;i++)
    {
        tHtml.append(QString("<tr>"));
        tHtml.append("\n");
        for(qint32 j=tColumn;j<tColumn+tColumnCnt;j++)
        {
            QString tKey=QString("%1,%2").arg(i).arg(j);
            if(tInvalidCellsList.contains(tKey))
            {
                //bypass invalid cells.
                continue;
            }
            qint32 tRowSpan=this->rowSpan(i,j);
            qint32 tColSpan=this->columnSpan(i,j);
            tHtml.append(QString("<td rowspan=\"%1\" colspan=\"%2\" align=\"left\">").arg(tRowSpan).arg(tColSpan));
            ZCell *tCell=static_cast<ZCell*>(this->item(i,j));
            if(tCell)
            {
                if(tCell->ZGetDataType()=="Boolean")
                {
                    tHtml.append("<input type=\"checkbox\" checked=\"checked\">");
                }
                if(tCell->ZGetCellWidgetType()==ZCell::CellWidget_QLabel)
                {
                    QString str = "<image src=\"data:image/png;base64,";
                    QLabel *label = qobject_cast<QLabel*>(this->cellWidget(i,j));
                    if(label)
                    {

                        str+=PixMapToString(*label->pixmap());
                        str+="\"width=100% height=100%>";
                        tHtml.append(str);
                    }
                }
                else
                    tHtml.append(tCell->text());
            }
            tHtml.append("</td>");
            tHtml.append("\n");
        }
        tHtml.append(QString("</tr>"));
        tHtml.append("\n");
    }
    tHtml.append("</table>");
    tHtml.append("\n");
    tHtml.append("</body>");
    tHtml.append("</html>");
    return tHtml;
}
QString ZSheet::PixMapToString(const QPixmap& pixmap)
{
    QByteArray ba,baBase64;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    pixmap.toImage().save(&buffer,"PNG");
    baBase64 = ba.toBase64();
    return QString(baBase64);
}

QPixmap ZSheet::StringToPixMap(const QString& str)
{
    QPixmap pixmap;
    QImage image;
    QByteArray ba,baBase64;
    baBase64 = str.toLatin1();
    ba= QByteArray::fromBase64(baBase64);
    QBuffer buffer(&ba);
    buffer.open(QIODevice::ReadOnly);
    //image.loadFromData(ba);
    image.load(&buffer,"PNG");
    //pixmap.fromImage(image);
    pixmap.convertFromImage(image);
    return pixmap;
}
