#include "zvarinfodia.h"
#include <TemplateEditor/zgeneralvarinfodia.h>
#include <TemplateEditor/zautovarinfodia.h>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
ZVarInfoDia::ZVarInfoDia(QString varSourceName,QWidget *parent):QDialog(parent)
{
    this->setMinimumSize(500,300);
    this->setWindowTitle(tr("正在编辑变量源[%1]").arg(varSourceName));
    this->m_varSourceName=varSourceName;

    this->m_llGeneralVar=new QLabel(tr("普通变量列表"));
    this->m_tbAddGeVar=new QToolButton;
    this->m_tbAddGeVar->setText(tr("Add"));
    this->m_tbDelGeVar=new QToolButton;
    this->m_tbDelGeVar->setText("Del");

    this->m_tbAddGeVar->setIcon(QIcon(":/common/images/common/add.png"));
    this->m_tbAddGeVar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbDelGeVar->setIcon(QIcon(":/common/images/common/del.png"));
    this->m_tbDelGeVar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_treeGeVar=new QTreeWidget;
    this->m_treeGeVar->setColumnCount(3);
    QStringList geVarHeaders;
    geVarHeaders<<tr("变量名称");
    geVarHeaders<<tr("数据类型");
    geVarHeaders<<tr("变量规则");
    this->m_treeGeVar->setHeaderLabels(geVarHeaders);


    this->m_llAutoVar=new QLabel(tr("自动变量列表"));
    this->m_tbAddAutoVar=new QToolButton;
    this->m_tbAddAutoVar->setText(tr("Add"));
    this->m_tbDelAutoVar=new QToolButton;
    this->m_tbDelAutoVar->setText(tr("Del"));
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

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llGeneralVar,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_tbAddGeVar,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbDelGeVar,0,2,1,1);
    this->m_gridLayout->addWidget(this->m_treeGeVar,1,0,1,3);

    this->m_gridLayout->addWidget(this->m_llAutoVar,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_tbAddAutoVar,2,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbDelAutoVar,2,2,1,1);
    this->m_gridLayout->addWidget(this->m_treeAutoVar,3,0,1,3);

    this->m_gridLayout->addWidget(this->m_tbOkay,4,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbCancel,4,2,1,1);

    this->setLayout(this->m_gridLayout);


    connect(this->m_tbAddGeVar,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddGeneralVar()));
    connect(this->m_tbDelGeVar,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelGeneralVar()));

    connect(this->m_tbAddAutoVar,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddAutoVar()));
    connect(this->m_tbDelAutoVar,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelAutoVar()));

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

    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gridLayout;
}
void ZVarInfoDia::ZSlotAddGeneralVar()
{
    ZGeneralVarInfoDia dia(this);
    if(dia.exec()==QDialog::Accepted)
    {
        QString varName=dia.ZGetVarName();
        QString varType=dia.ZGetVarType();
        QString varRule=dia.ZGetVarRule();
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

