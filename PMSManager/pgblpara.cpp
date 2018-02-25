#include "pgblpara.h"
#include <QObject>
#include <QMessageBox>
#include <Sheet/zcell.h>
#include <QDebug>
#include <QLabel>
#include <QBuffer>
#include <QDateTime>
#include <QTextCodec>
#include <QCheckBox>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QSpinBox>
MyUserInfo* MyUserInfo::m_pInstance=NULL;
int QBytes2Int(QByteArray bytes) {
    int addr = bytes[0] & 0x000000FF;
    addr |= ((bytes[1] << 8) & 0x0000FF00);
    addr |= ((bytes[2] << 16) & 0x00FF0000);
    addr |= ((bytes[3] << 24) & 0xFF000000);
    return addr;
}
QByteArray Int2QByte(int number)
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[0] = (uchar)  (0x000000ff & number);
    abyte0[1] = (uchar) ((0x0000ff00 & number) >> 8);
    abyte0[2] = (uchar) ((0x00ff0000 & number) >> 16);
    abyte0[3] = (uchar) ((0xff000000 & number) >> 24);
    return abyte0;
}
void ZAckNetFrmWidget::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{

}

QString ZGetTaskStateString(qint32 type)
{
    QString typeStr;
    switch(type)
    {
    case Task_Type_All:
        typeStr=QString("所有任务");
        break;
    case Task_Type_New:
        typeStr=QString("新建任务");
        break;
    case Task_Type_Save:
        typeStr=QString("已保存");
        break;
    case Task_Type_Submit:
        typeStr=QString("已提交审核");
        break;
    case Task_Type_Check_Okay:
        typeStr=QString("审核通过");
        break;
    case Task_Type_Check_Failed:
        typeStr=QString("审核未通过");
        break;
    case Task_Type_Archieve:
        typeStr=QString("已归档");
        break;
    }
    return typeStr;
}
QString ZGetTaskStateIconName(qint32 type)
{
    QString typeStr;
    switch(type)
    {
    case Task_Type_All:
        typeStr=QString(":/TaskManager/images/TaskManager/star_blue.png");
        break;
    case Task_Type_New:
        typeStr=QString(":/TaskManager/images/TaskManager/star_blue.png");
        break;
    case Task_Type_Save:
        typeStr=QString(":/TaskManager/images/TaskManager/star_orange.png");
        break;
    case Task_Type_Submit:
        typeStr=QString(":/TaskManager/images/TaskManager/star_pink.png");
        break;
    case Task_Type_Check_Okay:
        typeStr=QString(":/TaskManager/images/TaskManager/star_green.png");
        break;
    case Task_Type_Check_Failed:
        typeStr=QString(":/TaskManager/images/TaskManager/star_red.png");
        break;
    case Task_Type_Archieve:
        typeStr=QString(":/TaskManager/images/TaskManager/star_yellow.png");
        break;
    }
    return typeStr;
}

qint32 ZGetQTableWidgetHtml(QString title,QString note,QTableWidget *table,QString *html)
{
    QList<QTableWidgetSelectionRange> ranges=table->selectedRanges();
    if(ranges.count()<=0)
    {
        QMessageBox::critical(0,QObject::tr("错误提示"),QObject::tr("请选择一个区域!"));
        return -1;
    }
    QVector<qint32> rowVec;
    QVector<qint32> colVec;
    for(int i=0;i<ranges.count();i++)
    {
        qint32 row=ranges.at(i).topRow(); //bottomRow.
        int col=ranges.at(i).leftColumn(); //rightColumn.
        if(!rowVec.contains(row))
        {
            rowVec.append(row);
        }
        if(!colVec.contains(col))
        {
            colVec.append(col);
        }
    }
    if(rowVec.size()<=0 || colVec.size()<=0)
    {
        return -1;
    }

    for(qint32 i=0;i<rowVec.size();i++)
    {
        for(qint32 j=0;j<colVec.size();j++)
        {
            qDebug()<<"("<<rowVec.at(i)<<","<<colVec.at(j)<<")";
        }
    }
    qint32 totalWidth=0;
    for(qint32 i=0;i<colVec.size();i++)
    {
        totalWidth+=table->columnWidth(colVec.at(i));
    }

    QTextStream out(html);
    out.setCodec(QTextCodec::codecForName("UTF-8"));
    out<<"<html>";
    out<<"<head>";
    out<<"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">";
    out<<"<style type=\"text/css\">";
    out<<".td{border:solid #add9c0; border-width:0px 1px 1px 0px; padding:10px 0px;}";
    out<<".table{border:solid #add9c0; border-width:1px 0px 0px 1px;}";
    out<<"</style>";
    out<<"</head>";

    out<<"<body border=\"0\" bordercolor=\"#cce5f9\">";
    out<<QString("<p align=\"center\"><b>%1</b></p>").arg(title);
    out<<"<hr></hr>";
    out<<QString("<p align=\"left\">%1</p>").arg(note);
    out<<QString("<table width=\"100%\" border=\"1\" bordercolor=\"#0000FF\" bgcolor=\"#cce5f9\">");
    for(qint32 i=0;i<rowVec.size();i++)
    {
        out<<"<tr>";
        QVector<int> colSpanVec;
        for(qint32 j=0;j<colVec.size();j++)
        {
            ZCell *cell=static_cast<ZCell*>(table->item(i,j));
            if(cell)
            {
                if(colSpanVec.contains(j))
                {
                    qDebug()<<j<<" was span! bypass it";
                    continue;
                }
                //add span column to vector.
                qint32 colSpan=table->columnSpan(i,j);
                qDebug()<<"("<<i<<","<<j<<")"<<",span="<<colSpan;
                if(colSpan>0)
                {
                    for(qint32 k=0;k<colSpan;k++)
                    {
                        colSpanVec.append(j+k);
                    }
                    qDebug()<<"colSpanVec:"<<colSpanVec;
                }
                switch(cell->ZGetCellWidgetType())
                {
                case ZCell::CellWidget_No:
                {
                    QFont tFont=cell->ZGetFont();
                    out<<QString("<td align=\"center\" colspan=\"%2\">%3</td>")///<
                         .arg(colSpan)///<
                         .arg(cell->ZGetCellData());
                }
                    break;
                case ZCell::CellWidget_QLabel:
                {
                    QLabel *label = qobject_cast<QLabel*>(table->cellWidget(i,j));
                    if(label)
                    {
                        const QPixmap *pixmap=label->pixmap();
                        QByteArray byteArray;
                        QBuffer buffer(&byteArray);
                        buffer.open(QIODevice::WriteOnly);
                        pixmap->save(&buffer,"PNG");
                        out<<QString("<td align=\"center\" colspan=\"%2\"><img src=\"data:image/png;base64,%3\"></img></td>")///<
                             .arg(colSpan)///<
                             .arg(QString(byteArray.toBase64()));
                    }
                }
                    break;
                case ZCell::CellWidget_QCheckBox:
                {
                    QCheckBox *cb=qobject_cast<QCheckBox*>(table->cellWidget(i,j));
                    if(cb)
                    {
                        if(cb->isChecked())
                        {
                            out<<QString("<td align=\"center\"><input name=\"checkbox\" type=\"checkbox\" checked>%1</td>").arg(cb->text());
                        }else
                        {
                            out<<QString("<td align=\"center\"><input name=\"checkbox\" type=\"checkbox\">%1</td>").arg(cb->text());
                        }
                    }
                }
                    break;
                case ZCell::CellWidget_QComboBox:
                {
                    QComboBox *cb=qobject_cast<QComboBox*>(table->cellWidget(i,j));
                    if(cb)
                    {
                        out<<QString("<td align=\"center\">%1</td>").arg(cb->currentText());
                    }
                }
                    break;
                case ZCell::CellWidget_QDateTimeEdit:
                {
                    QDateTimeEdit *dt=qobject_cast<QDateTimeEdit*>(table->cellWidget(i,j));
                    if(dt)
                    {
                        out<<QString("<td align=\"center\">%1</td>").arg(dt->dateTime().toString("yyyy-MM-dd_hh:mm:ss"));
                    }
                }
                    break;
                case ZCell::CellWidget_QSpinBox:
                {
                    QSpinBox *sb=qobject_cast<QSpinBox*>(table->cellWidget(i,j));
                    if(sb)
                    {
                        out<<QString("<td align=\"center\">%1</td>").arg(sb->value());
                    }
                }
                    break;
                default:
                    break;
                }
            }
        }
        out<<"</tr>";
    }
    out<<"</table>";
    out<<QString("<p align=\"right\">PMS流水线综合管控系统-%1 %2 %3</p>")///<
         .arg(MyUserInfo::ZGetInstance()->m_appVersion)///<
         .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss"))///<
         .arg(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    out<<"</body>";
    out<<"</html>";
}
qint32 ZGetQTableWidgetPdf(QString title,QString note,QTableWidget *table,QString *html)
{
    QList<QTableWidgetSelectionRange> ranges=table->selectedRanges();
    if(ranges.count()<=0)
    {
        QMessageBox::critical(0,QObject::tr("错误提示"),QObject::tr("请选择一个区域!"));
        return -1;
    }
    QVector<qint32> rowVec;
    QVector<qint32> colVec;
    for(int i=0;i<ranges.count();i++)
    {
        qint32 row=ranges.at(i).topRow(); //bottomRow.
        int col=ranges.at(i).leftColumn(); //rightColumn.
        if(!rowVec.contains(row))
        {
            rowVec.append(row);
        }
        if(!colVec.contains(col))
        {
            colVec.append(col);
        }
    }
    if(rowVec.size()<=0 || colVec.size()<=0)
    {
        return -1;
    }

    for(qint32 i=0;i<rowVec.size();i++)
    {
        for(qint32 j=0;j<colVec.size();j++)
        {
            qDebug()<<"("<<rowVec.at(i)<<","<<colVec.at(j)<<")";
        }
    }
    qint32 totalWidth=0;
    for(qint32 i=0;i<colVec.size();i++)
    {
        totalWidth+=table->columnWidth(colVec.at(i));
    }

    QTextStream out(html);
    out.setCodec(QTextCodec::codecForName("UTF-8"));
    out<<"<html>";
    out<<"<head>";
    out<<"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">";
    out<<"<style type=\"text/css\">";
    out<<".td{border:solid #add9c0; border-width:0px 1px 1px 0px; padding:10px 0px;}";
    out<<".table{border:solid #add9c0; border-width:1px 0px 0px 1px;}";
    out<<"</style>";
    out<<"</head>";

    out<<"<body border=\"0\" bordercolor=\"#cce5f9\">";
    out<<QString("<p align=\"center\"><b>%1</b></p>").arg(title);
    out<<"<hr></hr>";
    out<<QString("<p align=\"left\">%1</p>").arg(note);
    out<<QString("<table width=\"100%\" border=\"1\" bordercolor=\"#0000FF\" bgcolor=\"#cce5f9\">");
    for(qint32 i=0;i<rowVec.size();i++)
    {
        out<<"<tr>";
        QVector<int> colSpanVec;
        for(qint32 j=0;j<colVec.size();j++)
        {
            ZCell *cell=static_cast<ZCell*>(table->item(i,j));
            if(cell)
            {
                if(colSpanVec.contains(j))
                {
                    qDebug()<<j<<" was span! bypass it";
                    continue;
                }
                //add span column to vector.
                qint32 colSpan=table->columnSpan(i,j);
                qDebug()<<"("<<i<<","<<j<<")"<<",span="<<colSpan;
                if(colSpan>0)
                {
                    for(qint32 k=0;k<colSpan;k++)
                    {
                        colSpanVec.append(j+k);
                    }
                    qDebug()<<"colSpanVec:"<<colSpanVec;
                }
                switch(cell->ZGetCellWidgetType())
                {
                case ZCell::CellWidget_No:
                {
                    QFont tFont=cell->ZGetFont();
                    out<<QString("<td align=\"center\" colspan=\"%2\">%3</td>")///<
                         .arg(colSpan)///<
                         .arg(cell->ZGetCellData());
                }
                    break;
                case ZCell::CellWidget_QLabel:
                {
                    QLabel *label = qobject_cast<QLabel*>(table->cellWidget(i,j));
                    if(label)
                    {
                        const QPixmap *pixmap=label->pixmap();
                        QByteArray byteArray;
                        QBuffer buffer(&byteArray);
                        buffer.open(QIODevice::WriteOnly);
                        pixmap->save(&buffer,"PNG");
                        out<<QString("<td align=\"center\" colspan=\"%2\"><img src=\"data:image/png;base64,%3\"></img></td>")///<
                             .arg(colSpan)///<
                             .arg(QString(byteArray.toBase64()));
                    }
                }
                    break;
                case ZCell::CellWidget_QCheckBox:
                {
                    QCheckBox *cb=qobject_cast<QCheckBox*>(table->cellWidget(i,j));
                    if(cb)
                    {
                        if(cb->isChecked())
                        {
                            out<<QString("<td align=\"center\">%1</td>").arg(cb->text()+"√");
                        }else
                        {
                            out<<QString("<td align=\"center\">%1</td>").arg(cb->text()+"X");
                        }
                    }
                }
                    break;
                case ZCell::CellWidget_QComboBox:
                {
                    QComboBox *cb=qobject_cast<QComboBox*>(table->cellWidget(i,j));
                    if(cb)
                    {
                        out<<QString("<td align=\"center\">%1</td>").arg(cb->currentText());
                    }
                }
                    break;
                case ZCell::CellWidget_QDateTimeEdit:
                {
                    QDateTimeEdit *dt=qobject_cast<QDateTimeEdit*>(table->cellWidget(i,j));
                    if(dt)
                    {
                        out<<QString("<td align=\"center\">%1</td>").arg(dt->dateTime().toString("yyyy-MM-dd_hh:mm:ss"));
                    }
                }
                    break;
                case ZCell::CellWidget_QSpinBox:
                {
                    QSpinBox *sb=qobject_cast<QSpinBox*>(table->cellWidget(i,j));
                    if(sb)
                    {
                        out<<QString("<td align=\"center\">%1</td>").arg(sb->value());
                    }
                }
                    break;
                default:
                    break;
                }
            }
        }
        out<<"</tr>";
    }
    out<<"</table>";
    out<<QString("<p align=\"right\">PMS流水线综合管控系统-V%1 %2 %3</p>")///<
         .arg(MyUserInfo::ZGetInstance()->m_appVersion)///<
         .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss"))///<
         .arg(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    out<<"</body>";
    out<<"</html>";
}
