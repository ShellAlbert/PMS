#include "zcell.h"
#include <QDebug>
ZCell::ZCell()
{
    //default value.
    this->ZSetFont(QFont("Serif"));
    this->ZSetDataType(QString("String"));
    this->ZSetMinMaxToleranceValue(0,0,0);
    //default background color:white.
    this->ZSetBackgroundColor(QColor(255,255,255,255));
    //default foreground color:black.
    this->ZSetForegroundColor(QColor(0,0,0,255));

    //border frame,default is no.
    this->ZSetTopFrame(false);
    this->ZSetBottomFrame(false);
    this->ZSetLeftFrame(false);
    this->ZSetRightFrame(false);
    this->ZSetFrameColor(QColor(0,0,0,255));
    this->ZSetFrameWidth(1);
    this->ZSetTextAlignment(Qt::AlignVCenter|Qt::AlignHCenter);

    this->m_cellWidgetType=CellWidget_No;
}
void ZCell::ZSetFont(QFont tFont)
{
    QTableWidgetItem::setFont(tFont);
}
QFont ZCell::ZGetFont()
{
    QFont font=QTableWidgetItem::font();
    return font;
}
void ZCell::ZSetForegroundColor(QColor fgColor)
{
    this->setForeground(QBrush(fgColor));
}
QColor ZCell::ZGetForegroundColor()
{
    return this->foreground().color();
}
void ZCell::ZSetBackgroundColor(QColor bgColor)
{
    this->setBackground(QBrush(bgColor));
}
QColor ZCell::ZGetBackgroundColor()
{
    return this->background().color();
}
void ZCell::ZSetDataType(QString dataType)
{
    if(dataType==QString("Boolean"))
    {
        this->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        this->setCheckState(Qt::Unchecked);
    }else{
        this->setData(Qt::CheckStateRole, QVariant());
    }
    this->m_dataType=dataType;
}
QString ZCell::ZGetDataType()
{
    return this->m_dataType;
}
void ZCell::ZSetMinMaxToleranceValue(qint32 minValue,qint32 maxValue,qint32 toleranceValue)
{
    this->m_minValue=minValue;
    this->m_maxValue=maxValue;
    this->m_toleranceValue=toleranceValue;
}
qint32 ZCell::ZGetMinValue()
{
    return this->m_minValue;
}
qint32 ZCell::ZGetMaxValue()
{
    return this->m_maxValue;
}
qint32 ZCell::ZGetToleranceValue()
{
    return this->m_toleranceValue;
}
void ZCell::ZSetCellData(QString data)
{
    this->setText(data);
}
QString ZCell::ZGetCellData()
{
    return this->text();
}
//border frame.
void ZCell::ZSetTopFrame(bool bFrame)
{
    this->m_bTopFrame=bFrame;
}
bool ZCell::ZTopFrameIsSet()
{
    return this->m_bTopFrame;
}

void ZCell::ZSetBottomFrame(bool bFrame)
{
    this->m_bBottomFrame=bFrame;
}
bool ZCell::ZBottomFrameIsSet()
{
    return this->m_bBottomFrame;
}

void ZCell::ZSetLeftFrame(bool bFrame)
{
    this->m_bLeftFrame=bFrame;
}
bool ZCell::ZLeftFrameIsSet()
{
    return this->m_bLeftFrame;
}

void ZCell::ZSetRightFrame(bool bFrame)
{
    this->m_bRightFrame=bFrame;
}
bool ZCell::ZRightFrameIsSet()
{
    return this->m_bRightFrame;
}
void ZCell::ZSetFrameColor(QColor frameColor)
{
    this->m_frameColor=frameColor;
}
QColor ZCell::ZGetFrameColor()
{
    return this->m_frameColor;
}
void ZCell::ZSetFrameWidth(qint32 width)
{
    this->m_frameWidth=width;
}
qint32 ZCell::ZGetFrameWidth()
{
    return this->m_frameWidth;
}
void ZCell::ZSetTextAlignment(qint32 textAlignment)
{
    this->setTextAlignment(textAlignment);
}
qint32 ZCell::ZGetTextAlignment()
{
    return this->textAlignment();
}
void ZCell::ZSetLockCell(bool bLock)
{
    if(bLock)
    {
        this->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    }else{
        this->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    }
}
bool ZCell::ZGetLockCell()
{
    if(this->flags()&Qt::ItemIsEditable)
    {
        return false;
    }else{
        return true;
    }
}
//sign
void ZCell::ZSetCheckedSign(bool bLock)
{
    this->m_bIsCheckedSign = bLock;
}

bool ZCell::ZGetCheckedSign()
{
    return this->m_bIsCheckedSign;
}
void ZCell::ZSetCellWidgetType(CellWidgetType type)
{
    this->m_cellWidgetType=type;
}
ZCell::CellWidgetType ZCell::ZGetCellWidgetType()
{
    return this->m_cellWidgetType;
}
void ZCell::ZSetBindVarName(QString varName)
{
    this->m_bindVarName=varName;
}
QString ZCell::ZGetBindVarName()
{
    return this->m_bindVarName;
}
