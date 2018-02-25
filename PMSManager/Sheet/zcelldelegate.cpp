#include "zcelldelegate.h"
#include <QPen>
#include <QPainter>
#include <QFontMetrics>
#include <QDebug>
ZCellDelegate::ZCellDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}
ZCellDelegate::~ZCellDelegate()
{

}

void ZCellDelegate::ZAddCellBorder(ZCell *tCell)
{
    QString tCellPos=QString("%1,%2").arg(tCell->row()).arg(tCell->column());
    if(!this->m_borderHash.contains(tCellPos))
    {
        this->m_borderHash.insert(tCellPos,tCell);
    }
}
void ZCellDelegate::ZDelCellBorder(ZCell *tCell)
{
    QString tCellPos=QString("%1,%2").arg(tCell->row()).arg(tCell->column());
    if(this->m_borderHash.contains(tCellPos))
    {
        this->m_borderHash.remove(tCellPos);
    }
}
//delegate for bind var.
void ZCellDelegate::ZAddBindGeVar(ZCell *cell)
{
    QString cellPos=QString("%1,%2").arg(cell->row()).arg(cell->column());
    if(!this->m_bindGeVarHash.contains(cellPos))
    {
        this->m_bindGeVarHash.insert(cellPos,cell);
    }
}
void ZCellDelegate::ZDelBindGeVar(ZCell *cell)
{
    QString cellPos=QString("%1,%2").arg(cell->row()).arg(cell->column());
    if(this->m_bindGeVarHash.contains(cellPos))
    {
        this->m_bindGeVarHash.remove(cellPos);
    }
}
void ZCellDelegate::ZAddBindAutoVarLoadEvent(ZCell *cell)
{
    QString cellPos=QString("%1,%2").arg(cell->row()).arg(cell->column());
    if(!this->m_bindAutoVarLoadEventHash.contains(cellPos))
    {
        this->m_bindAutoVarLoadEventHash.insert(cellPos,cell);
    }
}
void ZCellDelegate::ZDelBindAutoVarLoadEvent(ZCell *cell)
{
    QString cellPos=QString("%1,%2").arg(cell->row()).arg(cell->column());
    if(this->m_bindAutoVarLoadEventHash.contains(cellPos))
    {
        this->m_bindAutoVarLoadEventHash.remove(cellPos);
    }
}
void ZCellDelegate::ZAddBindAutoVarClickEvent(ZCell *cell)
{
    QString cellPos=QString("%1,%2").arg(cell->row()).arg(cell->column());
    if(!this->m_bindAutoVarClickEventHash.contains(cellPos))
    {
        this->m_bindAutoVarClickEventHash.insert(cellPos,cell);
    }
}
void ZCellDelegate::ZDelBindAutoVarClickEvent(ZCell *cell)
{
    QString cellPos=QString("%1,%2").arg(cell->row()).arg(cell->column());
    if(this->m_bindAutoVarClickEventHash.contains(cellPos))
    {
        this->m_bindAutoVarClickEventHash.remove(cellPos);
    }
}
void ZCellDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QString tCellPos=QString("%1,%2").arg(index.row()).arg(index.column());

    //delegate for border.
    if(this->m_borderHash.contains(tCellPos))
    {
        ZCell *tCell=this->m_borderHash.value(tCellPos);
        qint32 tFrameWidth=tCell->ZGetFrameWidth();
        qint32 tTextAlign=tCell->ZGetTextAlignment();

        //when user selection draw the background rectangle.
#if 1
        if(option.state&QStyle::State_Selected)
        {
            QRect tHightRect=option.rect;
            tHightRect.setX(tHightRect.x()+tFrameWidth);
            tHightRect.setY(tHightRect.y()+tFrameWidth);
            tHightRect.setWidth(tHightRect.width()-tFrameWidth*2);
            tHightRect.setHeight(tHightRect.height()-tFrameWidth*2);
            painter->fillRect(tHightRect,option.palette.highlight());
        }else{
            //draw back ground color.
            painter->save();
            QBrush tBackgroundBrush(tCell->ZGetBackgroundColor());
            painter->setBrush(tBackgroundBrush);
            painter->fillRect(option.rect,tBackgroundBrush);
            painter->restore();
        }
#endif

#if 1
        //save painter state before draw border.
        painter->save();
        QPen pen(tCell->ZGetFrameColor());
        pen.setWidth(tCell->ZGetFrameWidth());
        pen.setStyle(Qt::SolidLine);
        painter->setPen(pen);
        QRect tRectBorder=option.rect;
        if(tCell->ZTopFrameIsSet() && tCell->ZBottomFrameIsSet() && tCell->ZLeftFrameIsSet() && tCell->ZRightFrameIsSet())
        {
            tRectBorder.setX(tRectBorder.x()+tFrameWidth);
            tRectBorder.setY(tRectBorder.y()+tFrameWidth);
            tRectBorder.setWidth(tRectBorder.width()-tFrameWidth);
            tRectBorder.setHeight(tRectBorder.height()-tFrameWidth);
            painter->drawRect(tRectBorder);
        }else{
            if(tCell->ZTopFrameIsSet())
            {
                qint32 x1=tRectBorder.x()+tFrameWidth;
                qint32 y1=tRectBorder.y()+tFrameWidth;
                qint32 x2=x1+tRectBorder.width()-tFrameWidth;
                qint32 y2=y1;
                painter->drawLine(QPoint(x1,y1),QPoint(x2,y2));
            }
            if(tCell->ZBottomFrameIsSet())
            {
                qint32 x1=tRectBorder.x()+tFrameWidth;
                qint32 y1=tRectBorder.y()+tRectBorder.height();
                qint32 x2=x1+tRectBorder.width()-tFrameWidth;
                qint32 y2=y1;
                painter->drawLine(QPoint(x1,y1),QPoint(x2,y2));
            }
            if(tCell->ZLeftFrameIsSet())
            {
                qint32 x1=tRectBorder.x()+tFrameWidth;
                qint32 y1=tRectBorder.y()+tFrameWidth;
                qint32 x2=x1;
                qint32 y2=y1+tRectBorder.height()-tFrameWidth;
                painter->drawLine(QPoint(x1,y1),QPoint(x2,y2));
            }
            if(tCell->ZRightFrameIsSet())
            {
                qint32 x1=tRectBorder.x()+tRectBorder.width();
                qint32 y1=tRectBorder.y()+tFrameWidth;
                qint32 x2=x1;
                qint32 y2=y1+tRectBorder.height()-tFrameWidth;
                painter->drawLine(QPoint(x1,y1),QPoint(x2,y2));
            }
        }
        //restore painter state after draw border.
        painter->restore();
#endif


        //set font before drawing text.
        painter->save();
        painter->setFont(tCell->ZGetFont());
        QPen tFontPen(tCell->ZGetForegroundColor());
        tFontPen.setStyle(Qt::SolidLine);
        painter->setPen(tFontPen);
        qint32 tTextWidth=painter->fontMetrics().width(index.data().toString());
        qint32 tTextHeight=painter->fontMetrics().height();
        qDebug()<<tTextWidth<<","<<tTextHeight;
#if 1
        //calculate drawing left top point position.
        QRect tTextRect;
        if((tTextAlign&Qt::AlignLeft) && (tTextAlign&Qt::AlignTop))
        {
            qDebug()<<"(left,top)";
            tTextRect.setX(option.rect.x()+tFrameWidth);
            tTextRect.setY(option.rect.y()+tFrameWidth);
        }else if((tTextAlign&Qt::AlignHCenter)&&(tTextAlign&Qt::AlignTop))
        {
            qDebug()<<"(center,top)";
            tTextRect.setX(option.rect.x()+(option.rect.width()-tTextWidth)/2);
            tTextRect.setY(option.rect.y()+tFrameWidth);
        }else if((tTextAlign&Qt::AlignRight)&&(tTextAlign&Qt::AlignTop))
        {
            qDebug()<<"(right,top)";
            tTextRect.setX(option.rect.x()+option.rect.width()-tFrameWidth-tTextWidth);
            tTextRect.setY(option.rect.y()+tFrameWidth);
        }else  if((tTextAlign&Qt::AlignLeft) && (tTextAlign&Qt::AlignVCenter))
        {
            qDebug()<<"(left,center)";
            tTextRect.setX(option.rect.x()+tFrameWidth);
            tTextRect.setY(option.rect.y()+(option.rect.height()-tTextHeight)/2);
        }else if((tTextAlign&Qt::AlignHCenter)&&(tTextAlign&Qt::AlignVCenter))
        {
            qDebug()<<"(center,center)";
            tTextRect.setX(option.rect.x()+(option.rect.width()-tTextWidth)/2);
            tTextRect.setY(option.rect.y()+(option.rect.height()-tTextHeight)/2);
        }else if((tTextAlign&Qt::AlignRight)&&(tTextAlign&Qt::AlignVCenter))
        {
            //(right,center).
            tTextRect.setX(option.rect.x()+option.rect.width()-tTextWidth-tFrameWidth);
            tTextRect.setY(option.rect.y()+(option.rect.height()-tTextHeight)/2);
        }else  if((tTextAlign&Qt::AlignLeft) && (tTextAlign&Qt::AlignBottom))
        {
            //(left,bottom).
            tTextRect.setX(option.rect.x()+tFrameWidth);
            tTextRect.setY(option.rect.y()+(option.rect.height()-tTextHeight-tFrameWidth));
        }else if((tTextAlign&Qt::AlignHCenter)&&(tTextAlign&Qt::AlignBottom))
        {
            //(center,bottom).
            tTextRect.setX(option.rect.x()+(option.rect.width()-tTextWidth)/2);
            tTextRect.setY(option.rect.y()+(option.rect.height()-tTextHeight-tFrameWidth));
        }else if((tTextAlign&Qt::AlignRight)&&(tTextAlign&Qt::AlignBottom))
        {
            //(right,bottom).
            tTextRect.setX(option.rect.x()+option.rect.width()-tTextWidth-tFrameWidth);
            tTextRect.setY(option.rect.y()+(option.rect.height()-tTextHeight-tFrameWidth));
        }else{
            //default is (left,top).
            tTextRect.setX(option.rect.x()+tFrameWidth);
            tTextRect.setY(option.rect.y()+tFrameWidth);
        }
#endif
        tTextRect.setWidth(tTextWidth);
        tTextRect.setHeight(tTextHeight);
        painter->drawText(tTextRect,index.data().toString());
        painter->restore();
    }else{
        QStyledItemDelegate::paint(painter,option,index);
    }

    //delegate for bindVarIndicator.
    if(this->m_bindGeVarHash.contains(tCellPos))
    {
        painter->save();
        QPen pen(Qt::red);
        pen.setWidth(3);
        pen.setStyle(Qt::SolidLine);
        painter->setPen(pen);
        QRect tRect=option.rect;
        QPointF points[3] = {
            QPointF(tRect.x(),tRect.y()),
            QPointF(tRect.x(),tRect.y()+10),
            QPointF(tRect.x()+10,tRect.y()),
        };
        painter->drawPolygon(points, 3);
        painter->restore();
    }

    if(this->m_bindAutoVarLoadEventHash.contains(tCellPos))
    {
        painter->save();
        QPen pen(Qt::blue);
        pen.setWidth(3);
        pen.setStyle(Qt::SolidLine);
        painter->setPen(pen);
        QRect tRect=option.rect;
        QPointF points[3] = {
            QPointF(tRect.x(),tRect.y()),
            QPointF(tRect.x(),tRect.y()+10),
            QPointF(tRect.x()+10,tRect.y()),
        };
        painter->drawPolygon(points, 3);
        painter->restore();
    }

    if(this->m_bindAutoVarClickEventHash.contains(tCellPos))
    {
        painter->save();
        QPen pen(Qt::green);
        pen.setWidth(3);
        pen.setStyle(Qt::SolidLine);
        painter->setPen(pen);
        QRect tRect=option.rect;
        QPointF points[3] = {
            QPointF(tRect.x(),tRect.y()),
            QPointF(tRect.x(),tRect.y()+10),
            QPointF(tRect.x()+10,tRect.y()),
        };
        painter->drawPolygon(points, 3);
        painter->restore();
    }

    //QStyledItemDelegate::paint(painter,option,index);
}
