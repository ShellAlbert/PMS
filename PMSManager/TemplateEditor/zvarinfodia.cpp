#include "zvarinfodia.h"
#include <TemplateEditor/zgeneralvarinfodia.h>
#include <TemplateEditor/zautovarinfodia.h>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QtXlsx/QtXlsx>
#include <QInputDialog>
#include <QFileDialog>
ZVarInfoDia::ZVarInfoDia(QString varSourceName,QWidget *parent):QDialog(parent)
{
    this->setMinimumSize(600,400);
    this->setWindowTitle(tr("正在编辑变量源[%1]").arg(varSourceName));
    this->m_varSourceName=varSourceName;

    this->m_llGeneralVar=new QLabel(tr("普通变量列表"));
    this->m_tbAddGeVar=new QToolButton;
    this->m_tbAddGeVar->setText(tr("新增"));
    this->m_tbDelGeVar=new QToolButton;
    this->m_tbDelGeVar->setText("移除");

    this->m_tbAddGeVar->setIcon(QIcon(":/common/images/common/add.png"));
    this->m_tbAddGeVar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbDelGeVar->setIcon(QIcon(":/common/images/common/del.png"));
    this->m_tbDelGeVar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_treeGeVar=new QTreeWidget;
    this->m_treeGeVar->setColumnCount(4);
    QStringList geVarHeaders;
    geVarHeaders<<tr("变量名称");
    geVarHeaders<<tr("数据类型");
    geVarHeaders<<tr("变量规则");
    geVarHeaders<<tr("参考值");
    this->m_treeGeVar->setHeaderLabels(geVarHeaders);


    this->m_llAutoVar=new QLabel(tr("自动变量列表"));
    this->m_tbAddAutoVar=new QToolButton;
    this->m_tbAddAutoVar->setText(tr("新增"));
    this->m_tbDelAutoVar=new QToolButton;
    this->m_tbDelAutoVar->setText(tr("移除"));
    this->m_tbAddAutoVar->setIcon(QIcon(":/common/images/common/add.png"));
    this->m_tbAddAutoVar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbDelAutoVar->setIcon(QIcon(":/common/images/common/del.png"));
    this->m_tbDelAutoVar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_treeAutoVar=new QTreeWidget;
    this->m_treeAutoVar->setColumnCount(4);
    QStringList autoVarHeaders;
    autoVarHeaders<<tr("变量名称");
    autoVarHeaders<<tr("数据类型");
    autoVarHeaders<<tr("触发动作");
    autoVarHeaders<<tr("预定义值");
    this->m_treeAutoVar->setHeaderLabels(autoVarHeaders);

    this->m_tbImport=new QToolButton;
    this->m_tbImport->setText(tr("导入..."));
    this->m_tbImport->setIcon(QIcon(":/UserManager/images/UserManager/Import.png"));
    this->m_tbImport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("OKAY"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("CANCEL"));
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_hLayoutGeVar=new QHBoxLayout;
    this->m_hLayoutGeVar->addWidget(this->m_llGeneralVar);
    this->m_hLayoutGeVar->addStretch(1);
    this->m_hLayoutGeVar->addWidget(this->m_tbAddGeVar);
    this->m_hLayoutGeVar->addWidget(this->m_tbDelGeVar);

    this->m_hLayoutAutoVar=new QHBoxLayout;
    this->m_hLayoutAutoVar->addWidget(this->m_llAutoVar);
    this->m_hLayoutAutoVar->addStretch(1);
    this->m_hLayoutAutoVar->addWidget(this->m_tbAddAutoVar);
    this->m_hLayoutAutoVar->addWidget(this->m_tbDelAutoVar);

    this->m_hLayoutBtn=new QHBoxLayout;
    this->m_hLayoutBtn->addWidget(this->m_tbImport);
    this->m_hLayoutBtn->addStretch(1);
    this->m_hLayoutBtn->addWidget(this->m_tbOkay);
    this->m_hLayoutBtn->addWidget(this->m_tbCancel);

    this->m_vLayoutMain=new QVBoxLayout;
    this->m_vLayoutMain->addLayout(this->m_hLayoutGeVar);
    this->m_vLayoutMain->addWidget(this->m_treeGeVar);
    this->m_vLayoutMain->addLayout(this->m_hLayoutAutoVar);
    this->m_vLayoutMain->addWidget(this->m_treeAutoVar);
    this->m_vLayoutMain->addLayout(this->m_hLayoutBtn);

    this->setLayout(this->m_vLayoutMain);


    connect(this->m_tbAddGeVar,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddGeneralVar()));
    connect(this->m_tbDelGeVar,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelGeneralVar()));

    connect(this->m_tbAddAutoVar,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddAutoVar()));
    connect(this->m_tbDelAutoVar,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelAutoVar()));

    connect(this->m_tbImport,SIGNAL(clicked(bool)),this,SLOT(ZSlotImport()));
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
}
ZVarInfoDia::~ZVarInfoDia()
{
    delete this->m_llGeneralVar;
    delete this->m_tbAddGeVar;
    delete this->m_tbDelGeVar;
    delete this->m_treeGeVar;

    delete this->m_llAutoVar;
    delete this->m_tbAddAutoVar;
    delete this->m_tbDelAutoVar;
    delete this->m_treeAutoVar;

    delete this->m_tbImport;
    delete this->m_tbOkay;
    delete this->m_tbCancel;

    delete this->m_hLayoutGeVar;
    delete this->m_hLayoutAutoVar;
    delete this->m_hLayoutBtn;
    delete this->m_vLayoutMain;
}
void ZVarInfoDia::ZSlotAddGeneralVar()
{
    ZGeneralVarInfoDia dia(this);
    if(dia.exec()==QDialog::Accepted)
    {
        QString varName=dia.ZGetVarName();
        QString varType=dia.ZGetVarType();
        QString varRule=dia.ZGetVarRule();
        QString valRef=dia.ZGetRefValue();
        //search all exists varName to avoid the same name.
        for(qint32 i=0;i<this->m_treeGeVar->topLevelItemCount();i++)
        {
            QTreeWidgetItem *item=this->m_treeGeVar->topLevelItem(i);
            if(item->text(0)==varName)
            {
                QMessageBox::critical(this,tr("错误提示"),tr("变量名已经存在!"));
                return;
            }
        }
        QTreeWidgetItem *item=new QTreeWidgetItem;
        item->setText(0,varName);
        item->setText(1,varType);
        item->setText(2,varRule);
        item->setText(3,valRef);
        this->m_treeGeVar->addTopLevelItem(item);
    }
}
void ZVarInfoDia::ZSlotDelGeneralVar()
{
    QTreeWidgetItem *item=this->m_treeGeVar->currentItem();
    if(item==NULL)
    {
        return;
    }
    this->m_treeGeVar->takeTopLevelItem(item->indexOfChild(item));
    delete item;
    item=NULL;
}

void ZVarInfoDia::ZSlotAddAutoVar()
{
    ZAutoVarInfoDia dia(this);
    if(dia.exec()==QDialog::Accepted)
    {
        QString varName=dia.ZGetVarName();
        QString varType=dia.ZGetVarType();
        QString varAction=dia.ZGetVarAction();
        QString actValue=dia.ZGetActionValue();
        //search all exists varName to avoid the same name.
        for(qint32 i=0;i<this->m_treeAutoVar->topLevelItemCount();i++)
        {
            QTreeWidgetItem *item=this->m_treeAutoVar->topLevelItem(i);
            if(item->text(0)==varName)
            {
                QMessageBox::critical(this,tr("错误提示"),tr("变量名已经存在!"));
                return;
            }
        }
        QTreeWidgetItem *item=new QTreeWidgetItem;
        item->setText(0,varName);
        item->setText(1,varType);
        item->setText(2,varAction);
        item->setText(3,actValue);
        this->m_treeAutoVar->addTopLevelItem(item);
    }
}
void ZVarInfoDia::ZSlotDelAutoVar()
{
    QTreeWidgetItem *item=this->m_treeAutoVar->currentItem();
    if(item==NULL)
    {
        return;
    }
    this->m_treeAutoVar->takeTopLevelItem(item->indexOfChild(item));
    delete item;
    item=NULL;
}
void ZVarInfoDia::ZSlotImport()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("导入Excel"),".",tr("Microsoft Excel(*.xlsx)"));
    if(fileName.isEmpty())
    {
        return;
    }

    //read excel.
    QList<ZVarSourceInfo> varList;
    QXlsx::Document xlsx(fileName);
    qint32 nRowCnt=xlsx.read(1,5).toInt();
    if(nRowCnt<=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("读取Excel行数出错!"));
        return;
    }
    qint32 nRowNo=1;
    //bypass the Examples(1)+Example Data(5)+Data(2).
    nRowNo+=8;
    //start to read data.
    for(qint32 i=0;i<nRowCnt;i++)
    {
        ZVarSourceInfo varInfo;
        varInfo.m_varName=xlsx.read(nRowNo+i,1).toString();
        varInfo.m_varType=xlsx.read(nRowNo+i,2).toString();
        varInfo.m_rule=xlsx.read(nRowNo+i,3).toString();
        varInfo.m_refValue=xlsx.read(nRowNo+i,4).toString();
        varInfo.m_cell=xlsx.read(nRowNo+i,5).toString();
        varList.append(varInfo);
    }

    for(qint32 i=0;i<varList.size();i++)
    {
        ZVarSourceInfo varInfo;
        varInfo=varList.at(i);
        qDebug()<<varInfo.m_varName<<","<<varInfo.m_varType<<","<<varInfo.m_rule<<","<<varInfo.m_refValue<<","<<varInfo.m_cell;

        //search all exists varName to avoid the same name.
        bool bExist=false;
        for(qint32 i=0;i<this->m_treeGeVar->topLevelItemCount();i++)
        {
            QTreeWidgetItem *item=this->m_treeGeVar->topLevelItem(i);
            if(item->text(0)==varInfo.m_varName.right(varInfo.m_varName.length()-1))
            {
                bExist=true;
                break;
            }
        }
        if(bExist)
        {
            QMessageBox::critical(this,tr("错误提示"),tr("变量名%1已经存在,自动跳过!").arg(varInfo.m_varName));
            continue;
        }
        //check VarType.
        if(varInfo.m_varType!="String"&&varInfo.m_varType!="Digital"&&varInfo.m_varType!="Datetime"&&varInfo.m_varType!="Boolean")
        {
            QMessageBox::critical(this,tr("错误提示"),tr("变量名%1数据类型%2不可识别!").arg(varInfo.m_varName).arg(varInfo.m_varType));
            continue;
        }
        QTreeWidgetItem *item=new QTreeWidgetItem;
        item->setText(0,varInfo.m_varName.right(varInfo.m_varName.length()-1));//remove the first '@' prefix.
        item->setText(1,varInfo.m_varType);
        item->setText(2,varInfo.m_rule);
        item->setText(3,varInfo.m_refValue);
        this->m_treeGeVar->addTopLevelItem(item);
    }
    QMessageBox::information(this,tr("成功提示"),tr("Excel变量源模板导入成功!\n共导入变量%1个.").arg(QString::number(varList.size(),10)));
}
void ZVarInfoDia::ZSlotOkay()
{
    this->accept();
}
void ZVarInfoDia::ZSlotCancel()
{
    this->reject();
}
void ZVarInfoDia::ZSetXmlData(QString xmlData)
{
    QXmlStreamReader tXmlReader(xmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("GeVar"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString type=attr.value(QString("type")).toString();
                QString rule=attr.value(QString("rule")).toString();
                QString geVarName=tXmlReader.readElementText();
                QTreeWidgetItem *item=new QTreeWidgetItem;
                item->setText(0,geVarName);
                item->setText(1,type);
                item->setText(2,rule);
                this->m_treeGeVar->addTopLevelItem(item);
            }else if(nodeName==QString("AutoVar"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString type=attr.value(QString("type")).toString();
                QString action=attr.value(QString("action")).toString();
                QString value=attr.value(QString("value")).toString();
                QString autoVarName=tXmlReader.readElementText();
                QTreeWidgetItem *item=new QTreeWidgetItem;
                item->setText(0,autoVarName);
                item->setText(1,type);
                item->setText(2,action);
                item->setText(3,value);
                this->m_treeAutoVar->addTopLevelItem(item);
            }
        }//StarElement.
    }//while().
}
QString ZVarInfoDia::ZGetXmlData()
{
    QString xmlData;
    QXmlStreamWriter  tXmlWriter(&xmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("VarSource"));
    for(qint32 i=0;i<this->m_treeGeVar->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=this->m_treeGeVar->topLevelItem(i);
        QString geVarName=item->text(0);
        QString geVarType=item->text(1);
        QString geVarRule=item->text(2);
        tXmlWriter.writeStartElement(QString("GeVar"));
        tXmlWriter.writeAttribute(QString("type"),geVarType);
        tXmlWriter.writeAttribute(QString("rule"),geVarRule);
        tXmlWriter.writeCharacters(geVarName);
        tXmlWriter.writeEndElement();//GeVar.
    }
    for(qint32 i=0;i<this->m_treeAutoVar->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=this->m_treeAutoVar->topLevelItem(i);
        QString autoVarName=item->text(0);
        QString autoVarType=item->text(1);
        QString autoAction=item->text(2);
        QString autoValue=item->text(3);
        tXmlWriter.writeStartElement(QString("AutoVar"));
        tXmlWriter.writeAttribute(QString("type"),autoVarType);
        tXmlWriter.writeAttribute(QString("action"),autoAction);
        tXmlWriter.writeAttribute(QString("value"),autoValue);
        tXmlWriter.writeCharacters(autoVarName);
        tXmlWriter.writeEndElement();//AutoVar.
    }
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
    return xmlData;
}

