#include "ztasksheet.h"
#include <Sheet/zcell.h>
#include <QXmlStreamReader>
#include <QLabel>
#include <QDateTime>
#include <QDebug>
#include <QPainter>
#include <QCheckBox>
#include <QComboBox>
#include <QMenu>
#include <QAction>
#include <QSpinBox>
#include <QLabel>
#include <QDateTimeEdit>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include "pgblpara.h"
#include <QPaintEvent>
#include "TaskManager/ptaskmanager.h"
class ZProductLinePresetDialog;
class ZClassPresetDialog;
class ZOrderNoPresetDialog;
class ZProductNoPresetDialog;
ZTaskSheet::ZTaskSheet(QTreeWidget *varTree,QWidget *parent):QTableWidget(parent)
{
    //used to hold var.
    this->m_varTree=varTree;

    this->m_cellDelegate=new ZCellDelegate;
    this->setItemDelegate(this->m_cellDelegate);

    this->setRowCount(ROW_COUNT);
    this->setColumnCount(COL_COUNT);
    //all cell were locked except the cells that bind Vars.
    for(qint32 i=0;i<this->rowCount();i++)
    {
        for(qint32 j=0;j<this->columnCount();j++)
        {
            ZCell *tCell=new ZCell;
            tCell->ZSetLockCell(true);
            this->setItem(i,j,tCell);
        }
    }
    //this->setSelectionMode(QAbstractItemView::MultiSelection);

    connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(ZSlotCellChanged(int,int)));
    connect(this,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(ZSlotCellClicked(QTableWidgetItem*)));
}
ZTaskSheet::~ZTaskSheet()
{
    delete this->m_cellDelegate;
    //    for(qint32 i=0;i<this->rowCount();i++)
    //    {
    //        for(qint32 j=0;j<this->columnCount();j++)
    //        {
    //            ZCell *cell=static_cast<ZCell*>(this->item(i,j));
    //            delete cell;
    //            cell=NULL;
    //        }
    //    }
}
void ZTaskSheet::ZSetTaskName(QString taskName)
{
    this->m_TaskName=taskName;
}
QString ZTaskSheet::ZGetTaskName()
{
    return this->m_TaskName;
}
void ZTaskSheet::ZSetRefTemplateName(QString name)
{
    this->m_RefTemplate=name;
}
QString ZTaskSheet::ZGetRefTemplateName()
{
    return this->m_RefTemplate;
}
void ZTaskSheet::ZSetProcessName(QString processName)
{
    this->m_ProcessName=processName;
}
QString ZTaskSheet::ZGetProcessName()
{
    return this->m_ProcessName;
}
void ZTaskSheet::ZSetStepName(QString stepName)
{
    this->m_StepName=stepName;
}
QString ZTaskSheet::ZGetStepName()
{
    return this->m_StepName;
}

void ZTaskSheet::ZSetTemplateXmlDataAndVarSourceXmlData(QString templateXmlData,QString varSourceXmlData)
{
    //parse out template xml data.
    QStringList colorList;
    QStringList fontList;
    QXmlStreamReader tXmlReader(templateXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("row"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                qint32 height=attr.value(QString("height")).toInt();
                QString rowListStr=tXmlReader.readElementText();
                QStringList rowList=rowListStr.split(",");
                for(qint32 i=0;i<rowList.count();i++)
                {
                    QString rowNo=rowList.at(i);
                    this->setRowHeight(rowNo.toInt(),height);
                }
            }else if(nodeName=="col")
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                qint32 width=attr.value(QString("width")).toInt();
                QString colListStr=tXmlReader.readElementText();
                QStringList colList=colListStr.split(",");
                for(qint32 i=0;i<colList.count();i++)
                {
                    QString colNo=colList.at(i);
                    this->setColumnWidth(colNo.toInt(),width);
                }
            }else if(nodeName=="color")
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString colorStr=tXmlReader.readElementText();
                colorList.append(colorStr);
            }else if(nodeName=="font")
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString fontStr=tXmlReader.readElementText();
                fontList.append(fontStr);
            }else if(nodeName=="fix")
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                QString font=attr.value(QString("font")).toString();
                QString color=attr.value(QString("color")).toString();
                QString span=attr.value(QString("span")).toString();
                QString frame=attr.value(QString("frame")).toString();
                QString frameColor=attr.value(QString("frameColor")).toString();
                QString frameWidth=attr.value(QString("frameWidth")).toString();
                qint32 align=attr.value(QString("align")).toInt();
                QString data=tXmlReader.readElementText();

                QStringList xyList=xy.split(",");
                qint32 x=xyList.at(0).toInt();
                qint32 y=xyList.at(1).toInt();
                QStringList spanList=span.split(",");
                qint32 rowSpan=spanList.at(0).toInt();
                qint32 colSpan=spanList.at(1).toInt();
                ZCell *cell=static_cast<ZCell*>(this->item(x,y));
                if(cell)
                {
                    cell->ZSetCellWidgetType(ZCell::CellWidget_No);

                    //font.
                    QString fontStr=fontList.at(font.toInt());
                    QStringList fontParaList=fontStr.split(",");
                    QFont fontObj(fontParaList.at(0),fontParaList.at(1).toInt());
                    fontObj.setBold(fontParaList.at(2).toInt()?true:false);
                    fontObj.setItalic(fontParaList.at(3).toInt()?true:false);
                    cell->ZSetFont(fontObj);
                    //color.
                    QString colorStr=colorList.at(color.toInt());
                    QStringList colorParaList=colorStr.split(",");
                    QColor fgColor(colorParaList.at(1).toInt(),colorParaList.at(2).toInt(),colorParaList.at(3).toInt(),colorParaList.at(0).toInt());
                    QColor bgColor(colorParaList.at(5).toInt(),colorParaList.at(6).toInt(),colorParaList.at(7).toInt(),colorParaList.at(4).toInt());
                    cell->ZSetForegroundColor(fgColor);
                    cell->ZSetBackgroundColor(bgColor);

                    QStringList frameList=frame.split(",");
                    bool bTopFrame=frameList.at(0).toInt()?true:false;
                    bool bBottomFrame=frameList.at(1).toInt()?true:false;
                    bool bLeftFrame=frameList.at(2).toInt()?true:false;
                    bool bRightFrame=frameList.at(3).toInt()?true:false;
                    cell->ZSetTopFrame(bTopFrame);
                    cell->ZSetBottomFrame(bBottomFrame);
                    cell->ZSetLeftFrame(bLeftFrame);
                    cell->ZSetRightFrame(bRightFrame);
                    QStringList frameColorList=frameColor.split(",");
                    cell->ZSetFrameColor(QColor(frameColorList.at(0).toInt(),frameColorList.at(1).toInt(),frameColorList.at(2).toInt()));
                    cell->ZSetFrameWidth(frameWidth.toInt());
                    if(bTopFrame||bBottomFrame||bLeftFrame||bRightFrame)
                    {
                        this->m_cellDelegate->ZAddCellBorder(cell);
                    }else{
                        this->m_cellDelegate->ZDelCellBorder(cell);
                    }
                    //span.
                    if(rowSpan>1 || colSpan>1)
                    {
                        this->setSpan(x,y,rowSpan,colSpan);
                    }
                    //align.
                    cell->ZSetTextAlignment(align);
                    //data.
                    cell->ZSetCellData(data);
                }
            }else if(nodeName==QString("pic"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                QString picData=tXmlReader.readElementText();
                QStringList xyList=xy.split(",");

                QPixmap pixmap;
                if(pixmap.loadFromData(QByteArray::fromBase64(picData.toUtf8())))
                {
                    QLabel *llPng=new QLabel;
                    llPng->setPixmap(pixmap);
                    llPng->setScaledContents(true);
                    this->setCellWidget(xyList.at(0).toInt(),xyList.at(1).toInt(),llPng);
                    ZCell *cell=static_cast<ZCell*>(this->item(xyList.at(0).toInt(),xyList.at(1).toInt()));
                    if(cell)
                    {
                        cell->ZSetCellWidgetType(ZCell::CellWidget_QLabel);
                    }
                }
            }else if(nodeName==QString("checkbox"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                qint32 checked=attr.value(QString("checked")).toInt();
                QString name=tXmlReader.readElementText();
                QStringList xyList=xy.split(",");
                qint32 x=xyList.at(0).toInt();
                qint32 y=xyList.at(1).toInt();
                QCheckBox *cb=new QCheckBox;
                cb->setText(name);
                cb->setChecked(checked==1?true:false);
                this->setCellWidget(x,y,cb);
                ZCell *cell=static_cast<ZCell*>(this->item(x,y));
                if(cell)
                {
                    cell->ZSetCellWidgetType(ZCell::CellWidget_QCheckBox);
                }
            }else if(nodeName==QString("combobox"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                QString val=tXmlReader.readElementText();
                QStringList xyList=xy.split(",");
                qint32 x=xyList.at(0).toInt();
                qint32 y=xyList.at(1).toInt();
                QStringList valList=val.split(":");
                QComboBox *cb=new QComboBox;
                for(qint32 i=0;i<valList.count();i++)
                {
                    cb->addItem(valList.at(i));
                }
                this->setCellWidget(x,y,cb);
                ZCell *cell=static_cast<ZCell*>(this->item(x,y));
                if(cell)
                {
                    cell->ZSetCellWidgetType(ZCell::CellWidget_QComboBox);
                }
            }else if(nodeName==QString("spinbox"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                qint32 min=attr.value(QString("min")).toInt();
                qint32 max=attr.value(QString("max")).toInt();
                qint32 val=tXmlReader.readElementText().toInt();
                QStringList xyList=xy.split(",");
                qint32 x=xyList.at(0).toInt();
                qint32 y=xyList.at(1).toInt();
                QSpinBox *sb=new QSpinBox;
                sb->setRange(min,max);
                sb->setValue(val);
                this->setCellWidget(x,y,sb);
                ZCell *cell=static_cast<ZCell*>(this->item(x,y));
                if(cell)
                {
                    cell->ZSetCellWidgetType(ZCell::CellWidget_QSpinBox);
                }
            }else if(nodeName==QString("datetimeedit"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                QString val=tXmlReader.readElementText();
                QStringList xyList=xy.split(",");
                qint32 x=xyList.at(0).toInt();
                qint32 y=xyList.at(1).toInt();
                QDateTimeEdit *te=new QDateTimeEdit;
                te->setCalendarPopup(true);
                te->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
                this->setCellWidget(x,y,te);
                ZCell *cell=static_cast<ZCell*>(this->item(x,y));
                if(cell)
                {
                    cell->ZSetCellWidgetType(ZCell::CellWidget_QDateTimeEdit);
                    //qDebug()<<"datetimeedit:"<<x<<y;
                }
            }else if(nodeName==QString("bindvar"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                QString type=attr.value(QString("type")).toString();
                QString dataType=attr.value(QString("dataType")).toString();
                QString rule=attr.value(QString("rule")).toString();
                QString refVal=attr.value(QString("refVal")).toString();
                QString varName=tXmlReader.readElementText();
                if(type=="general"){
                    QTreeWidgetItem *item=new QTreeWidgetItem(1);
                    item->setText(0,xy);//cell
                    item->setText(1,varName);//var name.
                    item->setText(2,dataType);//data type.
                    item->setText(3,rule);//rule.
                    item->setText(4,refVal);//refval.
                    this->m_varTree->topLevelItem(0)->addChild(item);
                }else if(type=="auto"){
                    QTreeWidgetItem *item=new QTreeWidgetItem(1);
                    item->setText(0,xy);
                    item->setText(1,varName);
                    this->m_varTree->topLevelItem(1)->addChild(item);
                }
            }
        }//StarElement.
    }//while().

    //parse out varSource xml data.
    QXmlStreamReader varSrcXmlReader(varSourceXmlData);
    while(!varSrcXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=varSrcXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=varSrcXmlReader.name().toString();
            if(nodeName==QString("GeVar"))
            {
                QXmlStreamAttributes attr=varSrcXmlReader.attributes();
                QString dataType=attr.value(QString("type")).toString();
                QString varRule=attr.value(QString("rule")).toString();
                QString varRefVal=attr.value(QString("refVal")).toString();
                QString varName=varSrcXmlReader.readElementText();
                VarInfo info;
                info.varType="general";
                info.dataType=dataType;
                info.varRule=varRule;
                info.value=varRefVal;
                this->m_varMap.insert(varName,info);
            }else if(nodeName=="AutoVar")
            {
                QXmlStreamAttributes attr=varSrcXmlReader.attributes();
                QString dataType=attr.value(QString("type")).toString();
                QString varAction=attr.value(QString("action")).toString();
                QString varValue=attr.value(QString("value")).toString();
                QString varName=varSrcXmlReader.readElementText();
                VarInfo info;
                info.varType="auto";
                info.dataType=dataType;
                info.action=varAction;
                info.value=varValue;
                this->m_varMap.insert(varName,info);
            }
        }//StarElement.
    }//while().

    //emit this->ZSignalDataChanged(this->m_TaskName);
}
void ZTaskSheet::ZExecuteLoadActionBeforeShow()
{
    //search auto var in varMap.
    QTreeWidgetItem *autoItem=this->m_varTree->topLevelItem(1);//0 is generalItem,1 is autoItem.
    for(qint32 i=0;i<autoItem->childCount();i++)
    {
        QTreeWidgetItem *varItem=autoItem->child(i);
        QString cellPos=varItem->text(0);
        QString varName=varItem->text(1);
        QStringList xy=cellPos.split(",");
        qint32 x=xy.at(0).toInt()-1;
        qint32 y=xy.at(1).toInt()-1;
        //search var in map list.
        if(this->m_varMap.contains(varName))
        {
            VarInfo info=this->m_varMap.value(varName);
            if(info.action=="@load")
            {
                ZCell *cell=static_cast<ZCell*>(this->item(x,y));
                if(cell)
                {
                    QString valValue=this->ZGetCellDataByLoadAction(info.value);
                    cell->ZSetCellData(valValue);
                    cell->setToolTip(tr("自动变量 @load事件自动填充"));
                    emit this->ZSignalLogMsg(tr("cell (%1) @load action trigger,value=%2").arg(cellPos).arg(valValue));
                    this->m_cellDelegate->ZAddBindAutoVarLoadEvent(cell);
                }
            }else if(info.action=="@click")
            {
                ZCell *cell=static_cast<ZCell*>(this->item(x,y));
                if(cell)
                {
                    cell->setToolTip(tr("自动变量 @click事件自动填充"));
                    this->m_cellDelegate->ZAddBindAutoVarClickEvent(cell);
                }
            }
        }
    }
}
QString ZTaskSheet::ZGetCellDataByLoadAction(QString action)
{
    QString cellData;
    if(action=="@sysdatetime")
    {
        cellData=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    }else if(action=="@username")
    {
        cellData=MyUserInfo::ZGetInstance()->m_UserInfo.m_userName;
    }else if(action.startsWith("@refcell"))
    {
        cellData=action.mid(action.indexOf(":"));
    }else if(action.startsWith("@selfdef"))
    {
        cellData=action.mid(action.indexOf(":"));
    }else{
        cellData=action;
    }
    return cellData;
}
void ZTaskSheet::ZSetTaskState(qint32 state)
{
    this->m_taskState=state;
}
qint32 ZTaskSheet::ZGetTaskState()
{
    return this->m_taskState;
}
void ZTaskSheet::ZMakeProxyWidgetUnEditable(bool bEditable)
{
    for(qint32 i=0;i<this->rowCount();i++)
    {
        for(qint32 j=0;j<this->columnCount();j++)
        {
            ZCell *cell=static_cast<ZCell*>(this->item(i,j));
            if(cell)
            {
                switch(cell->ZGetCellWidgetType())
                {
                case ZCell::CellWidget_QLabel:
                    break;
                case ZCell::CellWidget_QLineEdit:
                    break;
                case ZCell::CellWidget_QCheckBox:
                {
                    QCheckBox *cb=static_cast<QCheckBox*>(this->cellWidget(i,j));
                    if(cb)
                    {
                        cb->setEnabled(bEditable);
                    }
                }
                    break;
                case ZCell::CellWidget_QComboBox:
                {
                    QComboBox *cb=static_cast<QComboBox*>(this->cellWidget(i,j));
                    if(cb)
                    {
                        cb->setEnabled(bEditable);
                    }
                }
                    break;
                case ZCell::CellWidget_QDateTimeEdit:
                {
                    QDateTimeEdit *dte=static_cast<QDateTimeEdit*>(this->cellWidget(i,j));
                    if(dte)
                    {
                        dte->setEnabled(bEditable);
                    }
                }
                    break;
                case ZCell::CellWidget_QSpinBox:
                {
                    QSpinBox *sb=static_cast<QSpinBox*>(this->cellWidget(i,j));
                    if(sb)
                    {
                        sb->setEnabled(bEditable);
                    }
                }
                    break;
                default:
                    break;
                }
            }
        }
    }
}
void ZTaskSheet::ZSlotCellChanged(int row,int col)
{
    emit this->ZSignalLogMsg(tr("cell changed to (%1,%2)").arg(row).arg(col));
}
void ZTaskSheet::ZSlotCellClicked(QTableWidgetItem*item)
{
    QString cellPos=QString("%1,%2").arg(item->row()+1).arg(item->column()+1);
    emit this->ZSignalLogMsg(tr("cell (%1) clicked").arg(cellPos));

    switch(this->ZGetTaskState())
    {
    case Task_Type_Submit:
    {
        emit this->ZSignalLogMsg(tr("cell (%1) @click action trigger failed due to submit task state!").arg(cellPos));;
        return;
    }
        break;
    case Task_Type_Check_Okay:
    {
        emit this->ZSignalLogMsg(tr("cell (%1) @click action trigger failed due to check okay task state!").arg(cellPos));;
        return;
    }
        break;
    case Task_Type_Archieve:
    {
        emit this->ZSignalLogMsg(tr("cell (%1) @click action trigger failed due to archieve task state!").arg(cellPos));;
        return;
    }
        break;
    default:
        emit this->ZSignalDataChanged(this->m_TaskName);
        break;
    }
    QTreeWidgetItem *autoItem=this->m_varTree->topLevelItem(1);//0 is generalItem,1 is autoItem.
    for(qint32 i=0;i<autoItem->childCount();i++)
    {
        QTreeWidgetItem *varItem=autoItem->child(i);
        if(varItem->text(0)==cellPos)
        {
            QString varName=varItem->text(1);
            //search var in map list.
            if(this->m_varMap.contains(varName))
            {
                VarInfo info=this->m_varMap.value(varName);
                if(info.action=="@click")
                {
                    ZCell *cell=static_cast<ZCell*>(this->item(item->row(),item->column()));
                    if(cell)
                    {
                        QString varValue=this->ZGetCellDataByLoadAction(info.value);
                        cell->ZSetCellData(varValue);
                        emit this->ZSignalLogMsg(tr("cell (%1) @click action trigger,value=%2.").arg(cellPos).arg(varValue));
                    }
                }
            }
        }
    }
}
void ZTaskSheet::paintEvent(QPaintEvent *e)
{
    //    QPainter painter(this);
    //    QFont tFont=painter.font();
    //    tFont.setPointSize(48);
    //    painter.setFont(tFont);
    //    painter.setBrush(QBrush(Qt::red));
    //    painter.drawText(QRectF(0,0,100,100),tr("已审核"));
    //    painter.drawText(QRectF(0,0,100,100),tr("已审核"));
    QTableWidget::paintEvent(e);
}
ZCellDataCheckReportDialog::ZCellDataCheckReportDialog(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("数据检查报告"));
    this->setMinimumSize(400,200);

    this->m_te=new QTextEdit;

    this->m_tbCopy=new QToolButton;
    this->m_tbCopy->setText(tr("复制到剪贴板"));
    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("OKAY"));
    this->m_tbCopy->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbCopy->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_tbCopy);
    this->m_hLayout->addWidget(this->m_tbOkay);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_te);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);

    connect(this->m_tbCopy,SIGNAL(clicked(bool)),this,SLOT(ZSlotCopy2Clipboard()));
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(accept()));
}
ZCellDataCheckReportDialog::~ZCellDataCheckReportDialog()
{
    delete this->m_te;
    delete this->m_tbCopy;
    delete this->m_tbOkay;
    delete this->m_hLayout;
    delete this->m_vLayout;
}
void ZCellDataCheckReportDialog::ZAddReportLog(QString reportLog)
{
    this->m_te->append(reportLog);
}
void ZCellDataCheckReportDialog::ZSlotCopy2Clipboard()
{
    QClipboard *cb=QApplication::clipboard();
    cb->setText(this->m_te->toPlainText());
    QMessageBox::information(this,tr("复制成功"),tr("已经复制到系统剪贴板中."));
}
ZTaskWidget::ZTaskWidget(QWidget *parent):QFrame(parent)
{
    this->m_llProductLine=new QLabel(tr("生产线/机器号"));
    this->m_llProductLine->setAlignment(Qt::AlignCenter);
    this->m_cbProuctLine=new QComboBox;
    this->m_cbProuctLine->setEditable(true);
    this->m_cbProuctLine->setMinimumWidth(160);
    //载入生产线预置值供用户选择，减少操作键盘次数。
    ZProductLinePresetDialog PLDia(this->m_refTemplate);
    QStringList lstPL=PLDia.ZReadList();
    for(qint32 i=0;i<lstPL.size();i++)
    {
        this->m_cbProuctLine->addItem(QIcon(":/TaskManager/images/TaskManager/ProductLine.png"),lstPL.at(i));
    }

    this->m_llClass=new QLabel(tr("班组"));
    this->m_llClass->setAlignment(Qt::AlignCenter);
    this->m_cbClass=new QComboBox;
    this->m_cbClass->setEditable(true);
    this->m_cbClass->setMinimumWidth(160);
    //载入班组预置值供用户选择，减少操作键盘次数。
    ZClassPresetDialog classDia;
    QStringList lstClass=classDia.ZReadList();
    for(qint32 i=0;i<lstClass.size();i++)
    {
        this->m_cbClass->addItem(QIcon(":/TaskManager/images/TaskManager/Class.png"),lstClass.at(i));
    }

    this->m_llOrderNo=new QLabel(tr("订单号"));
    this->m_llOrderNo->setAlignment(Qt::AlignCenter);
    this->m_cbOrderNo=new QComboBox;
    this->m_cbOrderNo->setEditable(true);
    this->m_cbOrderNo->setMinimumWidth(160);
    //载入订单号预置值供用户选择，减少操作键盘次数。
    ZOrderNoPresetDialog orderNoDia;
    QStringList lstOrderNo=orderNoDia.ZReadList();
    for(qint32 i=0;i<lstOrderNo.size();i++)
    {
        this->m_cbOrderNo->addItem(QIcon(":/TaskManager/images/TaskManager/OrderNo.png"),lstOrderNo.at(i));
    }

    this->m_llProductNo=new QLabel(tr("产品号"));
    this->m_llProductNo->setAlignment(Qt::AlignCenter);
    this->m_cbProductNo=new QComboBox;
    this->m_cbProductNo->setEditable(true);
    this->m_cbProductNo->setMinimumWidth(160);
    //载入产品号预置值供用户选择，减少操作键盘次数。
    ZProductNoPresetDialog productNoDia;
    QStringList lstProductNo=productNoDia.ZReadList();
    for(qint32 i=0;i<lstProductNo.size();i++)
    {
        this->m_cbProductNo->addItem(QIcon(":/TaskManager/images/TaskManager/ProductNo.png"),lstProductNo.at(i));
    }

    this->m_tbHideVarList=new QToolButton;
    this->m_tbHideVarList->setIcon(QIcon(":/TaskManager/images/TaskManager/arrow_right.png"));
    this->m_tbHideVarList->setToolButtonStyle(Qt::ToolButtonIconOnly);
    connect(this->m_tbHideVarList,SIGNAL(clicked(bool)),this,SLOT(ZSlotHideVarTree()));
    this->m_bHideVarTree=true;

    this->m_hLayoutTop=new QHBoxLayout;
    this->m_hLayoutTop->addWidget(this->m_llProductLine);
    this->m_hLayoutTop->addWidget(this->m_cbProuctLine);
    this->m_hLayoutTop->addWidget(this->m_llClass);
    this->m_hLayoutTop->addWidget(this->m_cbClass);
    this->m_hLayoutTop->addWidget(this->m_llOrderNo);
    this->m_hLayoutTop->addWidget(this->m_cbOrderNo);
    this->m_hLayoutTop->addWidget(this->m_llProductNo);
    this->m_hLayoutTop->addWidget(this->m_cbProductNo);
    this->m_hLayoutTop->addStretch(1);
    this->m_hLayoutTop->addWidget(this->m_tbHideVarList);

    /////////////////////////////////////////////////
    this->m_treeVar=new QTreeWidget;
    this->m_treeVar->setColumnCount(5);
    QStringList headerList;
    headerList<<tr("绑定单元格");
    headerList<<tr("变量名称");
    headerList<<tr("数据类型");
    headerList<<tr("规则");
    headerList<<tr("参考值");
    this->m_treeVar->setHeaderLabels(headerList);
    this->m_treeVar->setStyleSheet("QTreeWidget{background-color:#5B677A;color:white;}");
    this->m_geVarItem=new QTreeWidgetItem(0);
    this->m_geVarItem->setText(0,tr("普通变量"));
    this->m_autoVarItem=new QTreeWidgetItem(0);
    this->m_autoVarItem->setText(0,tr("自动变量"));
    this->m_treeVar->addTopLevelItem(this->m_geVarItem);
    this->m_treeVar->addTopLevelItem(this->m_autoVarItem);
    this->m_llTaskStateIcon=new QLabel;
    this->m_llTaskStateIcon->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    this->m_llTaskStateText=new QLabel;
    this->m_llTaskStateText->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    this->m_llTaskStateText->setStyleSheet("QLabel{font-size:14px;color:black;}");
    this->m_hLayoutTaskState=new QHBoxLayout;
    this->m_hLayoutTaskState->addWidget(this->m_llTaskStateIcon);
    this->m_hLayoutTaskState->addWidget(this->m_llTaskStateText);
    this->m_widgetTaskState=new QWidget;
    this->m_widgetTaskState->setLayout(this->m_hLayoutTaskState);
    this->m_rightSpliter=new QSplitter(Qt::Vertical);
    this->m_rightSpliter->addWidget(this->m_treeVar);
    this->m_rightSpliter->addWidget(this->m_widgetTaskState);
    this->m_rightSpliter->setStretchFactor(0,8);
    this->m_rightSpliter->setStretchFactor(1,2);

    this->m_sheet=new ZTaskSheet(this->m_treeVar,0);
    this->m_leftSpliter=new QSplitter(Qt::Horizontal);
    this->m_leftSpliter->addWidget(this->m_sheet);
    this->m_leftSpliter->addWidget(this->m_rightSpliter);
    this->m_leftSpliter->setStretchFactor(0,8);
    this->m_leftSpliter->setStretchFactor(1,2);
    this->m_vLayoutMain=new QVBoxLayout;
    this->m_vLayoutMain->addLayout(this->m_hLayoutTop);
    this->m_vLayoutMain->addWidget(this->m_leftSpliter);
    this->setLayout(this->m_vLayoutMain);

    connect(this->m_treeVar,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ZSlotVarDblClicked(QModelIndex)));
    connect(this->m_sheet,SIGNAL(ZSignalDataChanged(QString)),this,SIGNAL(ZSignalDataChanged(QString)));

    this->m_sheet->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this->m_sheet,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ZSlotPopupMenu(QPoint)));
}
ZTaskWidget::~ZTaskWidget()
{
    delete this->m_llProductLine;
    delete this->m_cbProuctLine;
    delete this->m_llClass;
    delete this->m_cbClass;
    delete this->m_llProductNo;
    delete this->m_cbProductNo;
    delete this->m_llOrderNo;
    delete this->m_cbOrderNo;
    delete this->m_tbHideVarList;
    delete this->m_hLayoutTop;
    ///////////////////////////////////
    delete this->m_sheet;
    delete this->m_geVarItem;
    delete this->m_autoVarItem;
    delete this->m_treeVar;
    delete this->m_llTaskStateIcon;
    delete this->m_llTaskStateText;
    delete this->m_hLayoutTaskState;
    delete this->m_widgetTaskState;
    delete this->m_rightSpliter;
    delete this->m_leftSpliter;
    delete this->m_vLayoutMain;
}
void ZTaskWidget::ZSlotHideVarTree()
{
    if(this->m_bHideVarTree) //hide it.
    {
        this->m_leftSpliter->setStretchFactor(0,1);
        this->m_leftSpliter->setStretchFactor(1,0);
        this->m_tbHideVarList->setIcon(QIcon(":/TaskManager/images/TaskManager/arrow_left.png"));
    }else{ //show it.
        this->m_leftSpliter->setStretchFactor(0,8);
        this->m_leftSpliter->setStretchFactor(1,2);
        this->m_tbHideVarList->setIcon(QIcon(":/TaskManager/images/TaskManager/arrow_right.png"));
    }
    this->m_bHideVarTree=!this->m_bHideVarTree;
}
void ZTaskWidget::ZSlotPopupMenu(const QPoint &pt)
{
    Q_UNUSED(pt);
    QMenu popMenu;
    QAction actLineChart(QIcon(":/TaskManager/images/TaskManager/lineChart.png"),tr("折线趋势图"));
    QAction actBarChart(QIcon(":/TaskManager/images/TaskManager/barChart.png"),tr("柱状汇总图"));
    QAction actExportExcel(QIcon(":/UserManager/images/UserManager/Excel.png"),tr("导出Excel..."));
    QAction actReport(QIcon(":/common/images/common/print.png"),tr("导出报表..."));
    popMenu.addAction(&actLineChart);
    popMenu.addAction(&actBarChart);
    popMenu.addAction(&actExportExcel);
    popMenu.addAction(&actReport);
    connect(&actLineChart,SIGNAL(triggered(bool)),this,SLOT(ZSlotShowLineChart()));
    connect(&actBarChart,SIGNAL(triggered(bool)),this,SLOT(ZSlotShowBarChart()));
    popMenu.exec(QCursor::pos());
}
void ZTaskWidget::ZSlotShowLineChart()
{
    QStringList varList;
    for(qint32 i=0;i<this->m_geVarItem->childCount();i++)
    {
        QTreeWidgetItem *item=this->m_geVarItem->child(i);
        if(item->text(2)==QString("Digital"))
        {
            varList.append(item->text(1));
        }
    }
    ZLineChartDialog dia(this);
    dia.ZSetVariableList(varList);
    dia.exec();
}
void ZTaskWidget::ZSlotShowBarChart()
{
    QStringList varList;
    for(qint32 i=0;i<this->m_geVarItem->childCount();i++)
    {
        QTreeWidgetItem *item=this->m_geVarItem->child(i);
        if(item->text(2)==QString("Digital"))
        {
            varList.append(item->text(1));
        }
    }
    ZBarChartDialog dia(this);
    dia.ZSetVariableList(varList);
    dia.exec();
}
void ZTaskWidget::ZSlotVarDblClicked(QModelIndex index)
{
    Q_UNUSED(index);
    QTreeWidgetItem *item=this->m_treeVar->currentItem();
    if(item==NULL)
    {
        return;
    }
    if(item->type()!=1)
    {
        return;
    }
    QString xy=item->text(0);
    QStringList xyList=xy.split(",");
    qint32 x=xyList.at(0).toInt()-1;
    qint32 y=xyList.at(1).toInt()-1;
    this->m_sheet->setCurrentCell(x,y);
    emit this->ZSignalLogMsg(tr("go to cell(%1,%2)").arg(x+1).arg(y+1));
}

QString ZTaskWidget::ZGetTaskVarValueXmlData()
{
    QString valXmlData;
    QXmlStreamWriter  tXmlWriter(&valXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Task"));

    for(qint32 i=0;i<this->m_geVarItem->childCount();i++)
    {
        QTreeWidgetItem *item=this->m_geVarItem->child(i);
        QString xy=item->text(0);
        QString varName=item->text(1);
        QStringList xyList=xy.split(",");
        qint32 x=xyList.at(0).toInt()-1;
        qint32 y=xyList.at(1).toInt()-1;
        ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(x,y));
        if(cell)
        {
            tXmlWriter.writeStartElement(QString("Value"));
            switch(cell->ZGetCellWidgetType())
            {
            case ZCell::CellWidget_No:
                tXmlWriter.writeAttribute(QString("val"),cell->ZGetCellData());
                break;
            case ZCell::CellWidget_QCheckBox:
            {
                QCheckBox *cb=static_cast<QCheckBox*>(this->m_sheet->cellWidget(x,y));
                if(cb)
                {
                    tXmlWriter.writeAttribute(QString("val"),QString("%1").arg(cb->isChecked()?1:0));
                }
            }
                break;
            case ZCell::CellWidget_QComboBox:
            {
                QComboBox *cb=static_cast<QComboBox*>(this->m_sheet->cellWidget(x,y));
                if(cb)
                {
                    tXmlWriter.writeAttribute(QString("val"),cb->currentText());
                }
            }
                break;
            case ZCell::CellWidget_QDateTimeEdit:
            {
                QDateTimeEdit *dte=static_cast<QDateTimeEdit*>(this->m_sheet->cellWidget(x,y));
                if(dte)
                {
                    QString valValue=dte->dateTime().toString("yyyy-MM-dd hh:mm:ss");
                    tXmlWriter.writeAttribute(QString("val"),valValue);
                }
            }
            default:
            case ZCell::CellWidget_QSpinBox:
            {
                QSpinBox *sb=static_cast<QSpinBox*>(this->m_sheet->cellWidget(x,y));
                if(sb)
                {
                    tXmlWriter.writeAttribute(QString("val"),QString::number(sb->value(),10));
                }
            }
                break;
            }
            tXmlWriter.writeCharacters(varName);
            tXmlWriter.writeEndElement();//Structure.
        }
    }
    for(qint32 i=0;i<this->m_autoVarItem->childCount();i++)
    {
        QTreeWidgetItem *item=this->m_autoVarItem->child(i);
        QString xy=item->text(0);
        QString varName=item->text(1);
        QStringList xyList=xy.split(",");
        qint32 x=xyList.at(0).toInt()-1;
        qint32 y=xyList.at(1).toInt()-1;
        ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(x,y));
        if(cell)
        {
            tXmlWriter.writeStartElement(QString("Value"));
            tXmlWriter.writeAttribute(QString("val"),cell->ZGetCellData());
            tXmlWriter.writeCharacters(varName);
            tXmlWriter.writeEndElement();//Structure.
        }
    }
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
    //    qDebug()<<"saveTask:";
    //    qDebug()<<valXmlData;
    return valXmlData;
}
QStringList ZTaskWidget::ZGetTaskAuxData()
{
    QStringList auxList;
    auxList.append(this->m_cbProuctLine->currentText());
    auxList.append(this->m_cbClass->currentText());
    auxList.append(this->m_cbOrderNo->currentText());
    auxList.append(this->m_cbProductNo->currentText());
    return auxList;
}
void ZTaskWidget::ZSetTaskAuxData(QStringList auxData)
{
    if(auxData.size()==4)
    {
        QString lineNoMachineNo=auxData.at(0);
        if(lineNoMachineNo.isEmpty())
        {
            //auto fill preset data @ load event.
            lineNoMachineNo=MyUserInfo::ZGetInstance()->m_lineNoMachineNo;
        }
        this->m_cbProuctLine->setCurrentText(lineNoMachineNo);
        this->m_cbClass->setCurrentText(auxData.at(1));
        this->m_cbOrderNo->setCurrentText(auxData.at(2));
        this->m_cbProductNo->setCurrentText(auxData.at(3));
    }
}


void ZTaskWidget::ZSetGeVarBindCellEditable(bool bEditable)
{
    for(qint32 i=0;i<this->m_geVarItem->childCount();i++)
    {
        QTreeWidgetItem *item=this->m_geVarItem->child(i);
        QString xy=item->text(0);
        QStringList xyList=xy.split(",");
        qint32 x=xyList.at(0).toInt()-1;
        qint32 y=xyList.at(1).toInt()-1;
        ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(x,y));
        if(cell)
        {
            cell->ZSetLockCell(!bEditable);
            cell->setToolTip(tr("普通变量,需要手工填写"));
            this->m_sheet->m_cellDelegate->ZAddBindGeVar(cell);
            switch(cell->ZGetCellWidgetType())
            {
            case ZCell::CellWidget_QCheckBox:
            {
                QCheckBox *cb=qobject_cast<QCheckBox*>(this->m_sheet->cellWidget(x,y));
                if(cb)
                {
                    cb->setEnabled(bEditable);
                }
            }
                break;
            case ZCell::CellWidget_QComboBox:
            {
                QComboBox *cbb=qobject_cast<QComboBox*>(this->m_sheet->cellWidget(x,y));
                if(cbb)
                {
                    cbb->setEnabled(bEditable);
                }
            }
                break;
            case ZCell::CellWidget_QDateTimeEdit:
            {
                QDateTimeEdit *dte=qobject_cast<QDateTimeEdit*>(this->m_sheet->cellWidget(x,y));
                if(dte)
                {
                    dte->setEnabled(bEditable);
                }
            }
                break;
            default:
                break;
            }
        }
    }
}
void ZTaskWidget::ZSetVarValueXmlData(QString xmlData)
{
    QMap<QString,QString> varMap;
    for(qint32 i=0;i<this->m_geVarItem->childCount();i++)
    {
        QTreeWidgetItem *item=this->m_geVarItem->child(i);
        varMap.insert(item->text(1),item->text(0));
    }
    for(qint32 i=0;i<this->m_autoVarItem->childCount();i++)
    {
        QTreeWidgetItem *item=this->m_autoVarItem->child(i);
        varMap.insert(item->text(1),item->text(0));
    }

    QString varXmlData(QByteArray::fromBase64(xmlData.toUtf8()));
    QXmlStreamReader tXmlReader(varXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("VarValue"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="get")
                {
                    QString varValue=attr.value(QString("val")).toString();
                    QString varName=tXmlReader.readElementText();
                    if(varMap.contains(varName))
                    {
                        QString xy=varMap.value(varName);
                        QStringList xyList=xy.split(",");
                        qint32 x=xyList.at(0).toInt()-1;
                        qint32 y=xyList.at(1).toInt()-1;
                        ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(x,y));
                        if(cell)
                        {
                            if(ZCell::CellWidget_No==cell->ZGetCellWidgetType())
                            {
                                cell->ZSetCellData(varValue);
                            }else if(ZCell::CellWidget_QCheckBox==cell->ZGetCellWidgetType())
                            {
                                QCheckBox *cb=static_cast<QCheckBox*>(this->m_sheet->cellWidget(x,y));
                                if(cb)
                                {
                                    cb->setChecked(varValue==QString("1")?true:false);
                                }
                            }else if(ZCell::CellWidget_QComboBox==cell->ZGetCellWidgetType())
                            {
                                QComboBox *cb=static_cast<QComboBox*>(this->m_sheet->cellWidget(x,y));
                                if(cb)
                                {
                                    cb->setCurrentText(varValue);
                                }
                            }else if(ZCell::CellWidget_QDateTimeEdit==cell->ZGetCellWidgetType())
                            {
                                QDateTimeEdit *dte=static_cast<QDateTimeEdit*>(this->m_sheet->cellWidget(x,y));
                                if(dte)
                                {
                                    qDebug()<<"setDateTime:"<<varValue;
                                    dte->setDateTime(QDateTime::fromString(varValue,"yyyy-MM-ddThh:mm:ss"));
                                }
                            }
                        }
                    }
                }
            }//VarValue.
        }//StarElement.
    }//while().
}
bool ZTaskWidget::ZCheckCellDataValidation()
{
    QString checkLog;
    bool bCheckOkay=true;
    for(qint32 i=0;i<this->m_geVarItem->childCount();i++)
    {
        QTreeWidgetItem *item=this->m_geVarItem->child(i);
        QString xy=item->text(0);
        QStringList xyList=xy.split(",");
        qint32 x=xyList.at(0).toInt()-1;
        qint32 y=xyList.at(1).toInt()-1;
        ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(x,y));
        if(cell)
        {
            if(ZCell::CellWidget_No==cell->ZGetCellWidgetType())
            {
                if(cell->ZGetCellData().isEmpty())
                {
                    QString errLog(tr("普通变量单元格(%1,%2)没有填写数据!\n").arg(x+1).arg(y+1));
                    emit this->ZSignalLogMsg(errLog);
                    checkLog.append(errLog);
                    bCheckOkay=false;
                }
            }else if(ZCell::CellWidget_QLabel==cell->ZGetCellWidgetType())
            {
                if(cell->ZGetCellData().isEmpty())
                {
                    QString errLog(tr("Label单元格(%1,%2)没有填写数据!\n").arg(x+1).arg(y+1));
                    emit this->ZSignalLogMsg(errLog);
                    checkLog.append(errLog);
                    bCheckOkay=false;
                }
            }else if(ZCell::CellWidget_QLineEdit==cell->ZGetCellWidgetType())
            {
                if(cell->ZGetCellData().isEmpty())
                {
                    QString errLog(tr("LineEdit单元格(%1,%2)没有填写数据!\n").arg(x+1).arg(y+1));
                    emit this->ZSignalLogMsg(errLog);
                    checkLog.append(errLog);
                    bCheckOkay=false;
                }
            }else if(ZCell::CellWidget_QCheckBox==cell->ZGetCellWidgetType())
            {
                //                if(cell->ZGetCellData().isEmpty())
                //                {
                //                    QString errLog(tr("CheckBox单元格(%1,%2)没有填写数据!\n").arg(x+1).arg(y+1));
                //                    emit this->ZSignalLogMsg(errLog);
                //                    checkLog.append(errLog);
                //                    bCheckOkay=false;
                //                }
            }else if(ZCell::CellWidget_QComboBox==cell->ZGetCellWidgetType())
            {
                //                if(cell->ZGetCellData().isEmpty())
                //                {
                //                    QString errLog(tr("ComboBox单元格(%1,%2)没有填写数据!\n").arg(x+1).arg(y+1));
                //                    emit this->ZSignalLogMsg(errLog);
                //                    checkLog.append(errLog);
                //                    bCheckOkay=false;
                //                }
            }else if(ZCell::CellWidget_QDateTimeEdit==cell->ZGetCellWidgetType())
            {
                //                if(cell->ZGetCellData().isEmpty())
                //                {
                //                    QString errLog(tr("DateTime单元格(%1,%2)没有填写数据!\n").arg(x+1).arg(y+1));
                //                    emit this->ZSignalLogMsg(errLog);
                //                    checkLog.append(errLog);
                //                    bCheckOkay=false;
                //                }
            }else if(ZCell::CellWidget_QSpinBox==cell->ZGetCellWidgetType())
            {
                //                if(cell->ZGetCellData().isEmpty())
                //                {
                //                    QString errLog(tr("SpinBox单元格(%1,%2)没有填写数据!\n").arg(x+1).arg(y+1));
                //                    emit this->ZSignalLogMsg(errLog);
                //                    checkLog.append(errLog);
                //                    bCheckOkay=false;
                //                }
            }
        }
    }
    for(qint32 i=0;i<this->m_autoVarItem->childCount();i++)
    {
        QTreeWidgetItem *item=this->m_autoVarItem->child(i);
        QString xy=item->text(0);
        QStringList xyList=xy.split(",");
        qint32 x=xyList.at(0).toInt()-1;
        qint32 y=xyList.at(1).toInt()-1;
        ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(x,y));
        if(cell)
        {
            if(cell->ZGetCellData().isEmpty())
            {
                emit this->ZSignalLogMsg(tr("自动变量单元格(%1,%2)没有填写数据!\n").arg(x+1).arg(y+1));
                bCheckOkay=false;
            }
        }
    }
    //show cell data check report dialog.
    if(!checkLog.isEmpty())
    {
        ZCellDataCheckReportDialog dia(this);
        dia.ZAddReportLog(checkLog);
        dia.exec();
    }
    return bCheckOkay;
}

void ZTaskWidget::ZSetTaskState(qint32 state)
{
    this->m_sheet->ZSetTaskState(state);
    this->m_TaskState=state;
    this->m_llTaskStateText->setText(ZGetTaskStateString(state));
    this->m_llTaskStateIcon->setPixmap(QPixmap(ZGetTaskStateIconName(state)).scaled(24,24));
    switch(state)
    {
    case Task_Type_New:
    case Task_Type_Save:
    case Task_Type_Check_Failed:
        this->ZSetGeVarBindCellEditable(true);
        //this->m_sheet->setEnabled(true);
        this->m_sheet->setEditTriggers(QAbstractItemView::AllEditTriggers);
        break;
    case Task_Type_Submit:
    case Task_Type_Check_Okay:
    case Task_Type_Archieve:
        this->ZSetGeVarBindCellEditable(false);
        //this->m_sheet->setEnabled(false);
        this->m_sheet->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->m_cbProuctLine->setEnabled(false);
        this->m_cbClass->setEnabled(false);
        this->m_cbOrderNo->setEnabled(false);
        this->m_cbProductNo->setEnabled(false);
        break;
    }
    this->m_autoVarItem->setExpanded(true);
    this->m_geVarItem->setExpanded(true);
}
qint32 ZTaskWidget::ZGetTaskState()
{
    return this->m_TaskState;
}
ZLineChartDialog::ZLineChartDialog(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("折线趋势图"));
    this->m_llVarList=new QLabel(tr("变量列表"));
    this->m_cbVarList=new QComboBox;
    this->m_cbVarList->setEditable(false);
    this->m_llDEStart=new QLabel(tr("起始时间"));
    this->m_deStart=new QDateTimeEdit;
    this->m_deStart->setCalendarPopup(true);
    this->m_llDEEnd=new QLabel(tr("结束时间"));
    this->m_deEnd=new QDateTimeEdit;
    this->m_deEnd->setCalendarPopup(true);
    this->m_tbAdd=new QToolButton;
    this->m_tbAdd->setIcon(QIcon(":/common/images/common/add.png"));
    this->m_tbDraw=new QToolButton;
    this->m_tbDraw->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_llVarList);
    this->m_hLayout->addWidget(this->m_cbVarList);
    this->m_hLayout->addWidget(this->m_llDEStart);
    this->m_hLayout->addWidget(this->m_deStart);
    this->m_hLayout->addWidget(this->m_llDEEnd);
    this->m_hLayout->addWidget(this->m_deEnd);
    this->m_hLayout->addWidget(this->m_tbAdd);
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_tbDraw);
    //////////////////////////////////////////////
    QLineSeries *series1=new QLineSeries;
    series1->setName(tr("宽度值"));
    series1->setPen(QPen(Qt::blue,1,Qt::SolidLine));
    series1->append(QPointF(1,10));
    series1->append(QPointF(2,20));
    series1->append(QPointF(3,15));
    series1->append(QPointF(4,33));
    series1->append(QPointF(5,50));
    series1->append(QPointF(6,31));
    series1->append(QPointF(7,12));

    QLineSeries *series2=new QLineSeries;
    series2->setName(tr("高度值"));
    series2->setPen(QPen(Qt::green,1,Qt::SolidLine));
    series2->append(QPointF(1,53));
    series2->append(QPointF(2,33));
    series2->append(QPointF(3,46));
    series2->append(QPointF(4,80));
    series2->append(QPointF(5,23));
    series2->append(QPointF(6,13));
    series2->append(QPointF(7,25));

    this->m_lineSeriesList.append(series1);
    this->m_lineSeriesList.append(series2);

    this->m_chart=new QChart;
    this->m_chart->setTitle(tr("变量趋势图"));
    //    this->m_chart->setTheme(QChart::ChartThemeBlueCerulean);
    this->m_chart->legend()->setAlignment(Qt::AlignRight);

    //create Y axis.
    this->m_yAxis=new QValueAxis;
    this->m_yAxis->setTitleText(tr("变量取值/Value"));
    this->m_yAxis->setLabelFormat("%d");
    this->m_yAxis->setRange(0,100);
    this->m_yAxis->setTickCount(10);
    this->m_chart->setAxisY(this->m_yAxis);

    this->m_xAxis=new QValueAxis;
    this->m_xAxis->setTitleText(tr("时间点/Time"));
    this->m_xAxis->setLabelFormat("%d");
    this->m_xAxis->setRange(0,100);
    this->m_xAxis->setTickCount((10));
    this->m_chart->setAxisX(this->m_xAxis);

    series1->attachAxis(this->m_yAxis);
    series2->attachAxis(this->m_yAxis);


    this->m_chart->addSeries(series1);
    this->m_chart->addSeries(series2);


    this->m_chartView=new QChartView(this->m_chart);
    this->m_chartView->setRenderHint(QPainter::Antialiasing);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->setContentsMargins(2,2,2,2);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->m_vLayout->addWidget(this->m_chartView);
    this->setLayout(this->m_vLayout);
}
ZLineChartDialog::~ZLineChartDialog()
{
    delete this->m_cbVarList;
    delete this->m_deStart;
    delete this->m_deEnd;
    delete this->m_tbAdd;
    delete this->m_tbDraw;
    delete this->m_hLayout;
    ///////////////////////////////
    delete this->m_xAxis;
    delete this->m_yAxis;
    for(qint32 i=0;i<this->m_lineSeriesList.size();i++)
    {
        delete this->m_lineSeriesList.at(i);
    }
    this->m_lineSeriesList.clear();
    delete this->m_chart;
    delete this->m_chartView;
    delete this->m_vLayout;
}
QSize ZLineChartDialog::sizeHint() const
{
    return QSize(800,500);
}
void ZLineChartDialog::ZSetVariableList(QStringList varList)
{
    this->m_cbVarList->clear();
    for(qint32 i=0;i<varList.size();i++)
    {
        this->m_cbVarList->addItem(varList.at(i));
    }
}
/////////////////////////////
ZBarChartDialog::ZBarChartDialog(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("柱状汇总图"));
    this->m_llVarList=new QLabel(tr("变量列表"));
    this->m_cbVarList=new QComboBox;
    this->m_cbVarList->setEditable(false);
    this->m_llDEStart=new QLabel(tr("起始时间"));
    this->m_deStart=new QDateTimeEdit;
    this->m_deStart->setCalendarPopup(true);
    this->m_llDEEnd=new QLabel(tr("结束时间"));
    this->m_deEnd=new QDateTimeEdit;
    this->m_deEnd->setCalendarPopup(true);
    this->m_tbAdd=new QToolButton;
    this->m_tbAdd->setIcon(QIcon(":/common/images/common/add.png"));
    this->m_tbDraw=new QToolButton;
    this->m_tbDraw->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_llVarList);
    this->m_hLayout->addWidget(this->m_cbVarList);
    this->m_hLayout->addWidget(this->m_llDEStart);
    this->m_hLayout->addWidget(this->m_deStart);
    this->m_hLayout->addWidget(this->m_llDEEnd);
    this->m_hLayout->addWidget(this->m_deEnd);
    this->m_hLayout->addWidget(this->m_tbAdd);
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_tbDraw);
    //////////////////////////////////////////////
    this->m_barSeries=new QBarSeries;
    for(qint32 i=0;i<10;i++)
    {
        QBarSet *set=new QBarSet(tr("变量%1").arg(i));
        set->append(10);
        set->append(20);
        set->append(15.3);
        set->append(33.9);
        set->append(11.2);
        this->m_barSeries->append(set);
        this->m_barSetList.append(set);
    }

    this->m_chart=new QChart;
    this->m_chart->setTitle(tr("变量趋势图"));
    //    this->m_chart->setTheme(QChart::ChartThemeBlueCerulean);
    this->m_chart->legend()->setAlignment(Qt::AlignRight);

    //create Y axis.
    this->m_yAxis=new QValueAxis;
    this->m_yAxis->setTitleText(tr("变量取值/Value"));
    this->m_yAxis->setLabelFormat("%d");
    this->m_yAxis->setRange(0,100);
    this->m_yAxis->setTickCount(10);
    this->m_chart->setAxisY(this->m_yAxis);

    this->m_xAxis=new QValueAxis;
    this->m_xAxis->setTitleText(tr("时间点/Time"));
    this->m_xAxis->setLabelFormat("%d");
    this->m_xAxis->setRange(0,100);
    this->m_xAxis->setTickCount((10));
    this->m_chart->setAxisX(this->m_xAxis);


    this->m_chart->addSeries(this->m_barSeries);

    this->m_chartView=new QChartView(this->m_chart);
    this->m_chartView->setRenderHint(QPainter::Antialiasing);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->setContentsMargins(2,2,2,2);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->m_vLayout->addWidget(this->m_chartView);
    this->setLayout(this->m_vLayout);
}
ZBarChartDialog::~ZBarChartDialog()
{
    delete this->m_cbVarList;
    delete this->m_deStart;
    delete this->m_deEnd;
    delete this->m_tbAdd;
    delete this->m_tbDraw;
    delete this->m_hLayout;
    ///////////////////////////////
    delete this->m_xAxis;
    delete this->m_yAxis;
    for(qint32 i=0;i<this->m_barSetList.size();i++)
    {
        delete this->m_barSetList.at(i);
    }
    this->m_barSetList.clear();
    delete this->m_barSeries;
    delete this->m_chart;
    delete this->m_chartView;
    delete this->m_vLayout;
}
QSize ZBarChartDialog::sizeHint() const
{
    return QSize(800,500);
}
void ZBarChartDialog::ZSetVariableList(QStringList varList)
{
    this->m_cbVarList->clear();
    for(qint32 i=0;i<varList.size();i++)
    {
        this->m_cbVarList->addItem(varList.at(i));
    }
}
