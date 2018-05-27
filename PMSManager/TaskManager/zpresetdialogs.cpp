#include "zpresetdialogs.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFile>
#include <QDir>
ZProductLinePresetDialog::ZProductLinePresetDialog(QString refTemplateName,QWidget *parent)
    :m_refTemplateName(refTemplateName),QDialog(parent)
{
    this->setWindowTitle(tr("生产线/机器号-输入预置列表"));

    this->m_tbAdd=new QToolButton;
    this->m_tbAdd->setText(tr("增加"));
    this->m_tbAdd->setIcon(QIcon(":/common/images/common/add.png"));
    this->m_tbAdd->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbDel=new QToolButton;
    this->m_tbDel->setText(tr("移除"));
    this->m_tbDel->setIcon(QIcon(":/common/images/common/del.png"));
    this->m_tbDel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbReset=new QToolButton;
    this->m_tbReset->setText(tr("清空"));
    this->m_tbReset->setIcon(QIcon(":/common/images/common/Clear.png"));
    this->m_tbReset->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbImport=new QToolButton;
    this->m_tbImport->setText(tr("导入"));
    this->m_tbImport->setIcon(QIcon(":/UserManager/images/UserManager/Import.png"));
    this->m_tbImport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbExport=new QToolButton;
    this->m_tbExport->setText(tr("导出"));
    this->m_tbExport->setIcon(QIcon(":/UserManager/images/UserManager/Export.png"));
    this->m_tbExport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbClickFill=new QToolButton;
    this->m_tbClickFill->setText(tr("自动"));
    this->m_tbClickFill->setIcon(QIcon(":/UserManager/images/UserManager/Export.png"));
    this->m_tbClickFill->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_vLayoutBtn=new QVBoxLayout;
    this->m_vLayoutBtn->addWidget(this->m_tbAdd);
    this->m_vLayoutBtn->addWidget(this->m_tbDel);
    this->m_vLayoutBtn->addWidget(this->m_tbReset);
    this->m_vLayoutBtn->addWidget(this->m_tbImport);
    this->m_vLayoutBtn->addWidget(this->m_tbExport);
    this->m_vLayoutBtn->addWidget(this->m_tbClickFill);
    this->m_vLayoutBtn->addStretch(1);
    ///////////////////////////////////////
    this->m_list=new QListWidget;
    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_list);
    this->m_hLayout->addLayout(this->m_vLayoutBtn);
    this->setLayout(this->m_hLayout);

    connect(this->m_tbAdd,SIGNAL(clicked(bool)),this,SLOT(ZSlotAdd()));
    connect(this->m_tbDel,SIGNAL(clicked(bool)),this,SLOT(ZSlotDel()));
    connect(this->m_tbReset,SIGNAL(clicked(bool)),this,SLOT(ZSlotReset()));
    connect(this->m_tbImport,SIGNAL(clicked(bool)),this,SLOT(ZSlotImport()));
    connect(this->m_tbExport,SIGNAL(clicked(bool)),this,SLOT(ZSlotExport()));
    connect(this->m_tbClickFill,SIGNAL(clicked(bool)),this,SLOT(ZSlotClickFill()));

    //read exist file data.
    QStringList itemList=this->ZReadList();
    for(qint32 i=0;i<itemList.count();i++)
    {
        QString itemText=itemList.at(i);
        QListWidgetItem *newItem=new QListWidgetItem(QIcon(":/TaskManager/images/TaskManager/ProductLine.png"),itemText);
        this->m_list->addItem(newItem);
    }
}
ZProductLinePresetDialog::~ZProductLinePresetDialog()
{
    delete this->m_tbAdd;
    delete this->m_tbDel;
    delete this->m_tbReset;
    delete this->m_tbImport;
    delete this->m_tbExport;
    delete this->m_vLayoutBtn;
    delete this->m_list;
    delete this->m_hLayout;
}
QSize ZProductLinePresetDialog::sizeHint() const
{
    return QSize(600,300);
}
QStringList ZProductLinePresetDialog::ZReadList()
{
    QStringList itemList;
    QFile productLineFile(QDir::currentPath()+"/cfg/PL.dat");
    if(productLineFile.open(QFile::ReadOnly|QIODevice::Text))
    {
        while(!productLineFile.atEnd())
        {
            QByteArray baLine=productLineFile.readLine();
            if(!baLine.isEmpty())
            {
                QString newText(baLine);
                newText.remove("\n");
                if(!newText.isEmpty())
                {
                    itemList.append(newText);
                }
            }
        }
        productLineFile.close();
    }
    return itemList;
}
QStringList ZProductLinePresetDialog::ZGetList()
{
    QStringList itemList;
    for(qint32 i=0;i<this->m_list->count();i++)
    {
        itemList.append(this->m_list->item(i)->text());
    }
    return itemList;
}
void ZProductLinePresetDialog::closeEvent(QCloseEvent *e)
{
    //write to dat file.
    QFile productLineFile(QDir::currentPath()+"/cfg/PL.dat");
    if(productLineFile.open(QFile::WriteOnly|QIODevice::Truncate|QIODevice::Text))
    {
        for(qint32 i=0;i<this->m_list->count();i++)
        {
            QByteArray baWrite=this->m_list->item(i)->text().toLatin1();
            baWrite.append("\n");
            productLineFile.write(baWrite);
        }
        productLineFile.close();
    }
    /////////////////
    e->accept();
}
void ZProductLinePresetDialog::ZSlotAdd()
{
    QString newText=QInputDialog::getText(this,tr("新增项"),tr("请输入新项目"));
    if(newText.isEmpty())
    {
        return;
    }
    QListWidgetItem *newItem=new QListWidgetItem(QIcon(":/TaskManager/images/TaskManager/ProductLine.png"),newText);
    this->m_list->addItem(newItem);
}
void ZProductLinePresetDialog::ZSlotDel()
{
    QListWidgetItem *item=this->m_list->currentItem();
    if(item)
    {
        this->m_list->removeItemWidget(item);
        delete item;
    }
}
void ZProductLinePresetDialog::ZSlotReset()
{
    this->m_list->clear();
}
void ZProductLinePresetDialog::ZSlotImport()
{

}
void ZProductLinePresetDialog::ZSlotExport()
{

}
void ZProductLinePresetDialog::ZSlotClickFill()
{
    if(this->m_refTemplateName.isEmpty())
    {
        return;
    }
    ZProductLinePresetDialogXYList xyListDia(this->m_refTemplateName);
    xyListDia.exec();
}
ZProductLinePresetDialogXYList::ZProductLinePresetDialogXYList(QString refTemplateName,QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("自动填写单元格坐标列表"));
    //明天晚上从这里继续修改。
    this->m_llNotes=new QLabel;
    this->m_llNotes->setText(tr("当创建基于模板 <%1> 的任务时，单击以下单元格时，将在单元格中自动填写 <生产机/机器号>。").arg(refTemplateName));
    this->m_lstXY=new QListWidget;
    this->m_tbAdd=new QToolButton;
    this->m_tbAdd->setText(tr("增加"));
    this->m_tbAdd->setIcon(QIcon(":/common/images/common/add.png"));
    this->m_tbAdd->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbDel=new QToolButton;
    this->m_tbDel->setText(tr("移除"));
    this->m_tbDel->setIcon(QIcon(":/common/images/common/del.png"));
    this->m_tbDel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_vLayoutBtn=new QVBoxLayout;
    this->m_vLayoutBtn->addWidget(this->m_tbAdd);
    this->m_vLayoutBtn->addWidget(this->m_tbDel);
    this->m_vLayoutBtn->addStretch(1);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_lstXY);
    this->m_hLayout->addLayout(this->m_vLayoutBtn);

    this->m_vLayoutMain=new QVBoxLayout;
    this->m_vLayoutMain->addWidget(this->m_llNotes);
    this->m_vLayoutMain->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayoutMain);

    connect(this->m_tbAdd,SIGNAL(clicked(bool)),this,SLOT(ZSlotAdd()));
    connect(this->m_tbDel,SIGNAL(clicked(bool)),this,SLOT(ZSlotDel()));
}
ZProductLinePresetDialogXYList::~ZProductLinePresetDialogXYList()
{
    delete this->m_llNotes;
    delete this->m_tbAdd;
    delete this->m_tbDel;
    delete this->m_vLayoutBtn;
    delete this->m_lstXY;
    delete this->m_hLayout;
    delete this->m_vLayoutMain;
}

void ZProductLinePresetDialogXYList::ZPutList(QStringList xyList)
{

}
QStringList ZProductLinePresetDialogXYList::ZGetList()
{
    QStringList xyList;
    return xyList;
}

void ZProductLinePresetDialogXYList::ZSlotAdd()
{
    QString newXY=QInputDialog::getText(this,tr("新增项"),tr("请输入新项目：x,y"));
    QStringList xyList=newXY.split(",");
    if(xyList.size()!=2)
    {
        QMessageBox::critical(this,tr("错误"),tr("您输入格式不正确!"));
        return;
    }
    this->m_lstXY->addItem(newXY);
}
void ZProductLinePresetDialogXYList::ZSlotDel()
{
    QListWidgetItem *item=this->m_lstXY->currentItem();
    if(item)
    {
        this->m_lstXY->removeItemWidget(item);
        delete item;
    }
}



////////////////////////////////////////////
ZClassPresetDialog::ZClassPresetDialog(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("班组-输入预置列表"));

    this->m_tbAdd=new QToolButton;
    this->m_tbAdd->setText(tr("增加"));
    this->m_tbAdd->setIcon(QIcon(":/common/images/common/add.png"));
    this->m_tbAdd->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbDel=new QToolButton;
    this->m_tbDel->setText(tr("移除"));
    this->m_tbDel->setIcon(QIcon(":/common/images/common/del.png"));
    this->m_tbDel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbReset=new QToolButton;
    this->m_tbReset->setText(tr("清空"));
    this->m_tbReset->setIcon(QIcon(":/common/images/common/Clear.png"));
    this->m_tbReset->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbImport=new QToolButton;
    this->m_tbImport->setText(tr("导入"));
    this->m_tbImport->setIcon(QIcon(":/UserManager/images/UserManager/Import.png"));
    this->m_tbImport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbExport=new QToolButton;
    this->m_tbExport->setText(tr("导出"));
    this->m_tbExport->setIcon(QIcon(":/UserManager/images/UserManager/Export.png"));
    this->m_tbExport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_vLayoutBtn=new QVBoxLayout;
    this->m_vLayoutBtn->addWidget(this->m_tbAdd);
    this->m_vLayoutBtn->addWidget(this->m_tbDel);
    this->m_vLayoutBtn->addWidget(this->m_tbReset);
    this->m_vLayoutBtn->addWidget(this->m_tbImport);
    this->m_vLayoutBtn->addWidget(this->m_tbExport);
    this->m_vLayoutBtn->addStretch(1);
    ///////////////////////////////////////
    this->m_list=new QListWidget;
    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_list);
    this->m_hLayout->addLayout(this->m_vLayoutBtn);
    this->setLayout(this->m_hLayout);

    connect(this->m_tbAdd,SIGNAL(clicked(bool)),this,SLOT(ZSlotAdd()));
    connect(this->m_tbDel,SIGNAL(clicked(bool)),this,SLOT(ZSlotDel()));
    connect(this->m_tbReset,SIGNAL(clicked(bool)),this,SLOT(ZSlotReset()));
    connect(this->m_tbImport,SIGNAL(clicked(bool)),this,SLOT(ZSlotImport()));
    connect(this->m_tbExport,SIGNAL(clicked(bool)),this,SLOT(ZSlotExport()));

    //read exist file data.
    QStringList itemList=this->ZReadList();
    for(qint32 i=0;i<itemList.count();i++)
    {
        QString itemText=itemList.at(i);
        QListWidgetItem *newItem=new QListWidgetItem(QIcon(":/TaskManager/images/TaskManager/Class.png"),itemText);
        this->m_list->addItem(newItem);
    }
}
ZClassPresetDialog::~ZClassPresetDialog()
{
    delete this->m_tbAdd;
    delete this->m_tbDel;
    delete this->m_tbReset;
    delete this->m_tbImport;
    delete this->m_tbExport;
    delete this->m_vLayoutBtn;
    delete this->m_list;
    delete this->m_hLayout;
}
QSize ZClassPresetDialog::sizeHint() const
{
    return QSize(600,300);
}
QStringList ZClassPresetDialog::ZReadList()
{
    QStringList itemList;
    QFile productLineFile(QDir::currentPath()+"/cfg/CLASS.dat");
    if(productLineFile.open(QFile::ReadOnly|QIODevice::Text))
    {
        while(!productLineFile.atEnd())
        {
            QByteArray baLine=productLineFile.readLine();
            if(!baLine.isEmpty())
            {
                QString newText(baLine);
                newText.remove("\n");
                if(!newText.isEmpty())
                {
                    itemList.append(newText);
                }
            }
        }
        productLineFile.close();
    }
    return itemList;
}
QStringList ZClassPresetDialog::ZGetList()
{
    QStringList itemList;
    for(qint32 i=0;i<this->m_list->count();i++)
    {
        itemList.append(this->m_list->item(i)->text());
    }
    return itemList;
}
void ZClassPresetDialog::closeEvent(QCloseEvent *e)
{
    //write to dat file.
    QFile productLineFile(QDir::currentPath()+"/cfg/CLASS.dat");
    if(productLineFile.open(QFile::WriteOnly|QIODevice::Truncate|QIODevice::Text))
    {
        for(qint32 i=0;i<this->m_list->count();i++)
        {
            QByteArray baWrite=this->m_list->item(i)->text().toLatin1();
            baWrite.append("\n");
            productLineFile.write(baWrite);
        }
        productLineFile.close();
    }
    /////////////////
    e->accept();
}
void ZClassPresetDialog::ZSlotAdd()
{
    QString newText=QInputDialog::getText(this,tr("新增项"),tr("请输入新项目"));
    if(newText.isEmpty())
    {
        return;
    }
    QListWidgetItem *newItem=new QListWidgetItem(QIcon(":/TaskManager/images/TaskManager/Class.png"),newText);
    this->m_list->addItem(newItem);
}
void ZClassPresetDialog::ZSlotDel()
{
    QListWidgetItem *item=this->m_list->currentItem();
    if(item)
    {
        this->m_list->removeItemWidget(item);
        delete item;
    }
}
void ZClassPresetDialog::ZSlotReset()
{
    this->m_list->clear();
}
void ZClassPresetDialog::ZSlotImport()
{

}
void ZClassPresetDialog::ZSlotExport()
{

}
//订单号输入预置对话框
ZOrderNoPresetDialog::ZOrderNoPresetDialog(QString templateName,QWidget *parent):QDialog(parent)
{
    this->m_relatedTemplate=templateName;

    this->setWindowTitle(tr("订单号-输入预置列表"));

    this->m_tbAdd=new QToolButton;
    this->m_tbAdd->setText(tr("增加"));
    this->m_tbAdd->setIcon(QIcon(":/common/images/common/add.png"));
    this->m_tbAdd->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbDel=new QToolButton;
    this->m_tbDel->setText(tr("移除"));
    this->m_tbDel->setIcon(QIcon(":/common/images/common/del.png"));
    this->m_tbDel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbReset=new QToolButton;
    this->m_tbReset->setText(tr("清空"));
    this->m_tbReset->setIcon(QIcon(":/common/images/common/Clear.png"));
    this->m_tbReset->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbImport=new QToolButton;
    this->m_tbImport->setText(tr("导入"));
    this->m_tbImport->setIcon(QIcon(":/UserManager/images/UserManager/Import.png"));
    this->m_tbImport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbExport=new QToolButton;
    this->m_tbExport->setText(tr("导出"));
    this->m_tbExport->setIcon(QIcon(":/UserManager/images/UserManager/Export.png"));
    this->m_tbExport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_vLayoutBtn=new QVBoxLayout;
    this->m_vLayoutBtn->addWidget(this->m_tbAdd);
    this->m_vLayoutBtn->addWidget(this->m_tbDel);
    this->m_vLayoutBtn->addWidget(this->m_tbReset);
    this->m_vLayoutBtn->addWidget(this->m_tbImport);
    this->m_vLayoutBtn->addWidget(this->m_tbExport);
    this->m_vLayoutBtn->addStretch(1);

    this->m_list=new QListWidget;
    this->m_grpPreVal=new QGroupBox(tr("预输入列表"));
    this->m_hLayoutGrp=new QHBoxLayout;
    this->m_hLayoutGrp->addWidget(this->m_list);
    this->m_hLayoutGrp->addLayout(this->m_vLayoutBtn);
    this->m_grpPreVal->setLayout(this->m_hLayoutGrp);


    /////////////////////////////////////////////////


    this->m_xyList=new QListWidget;
    this->m_tbAddXY=new QToolButton;
    this->m_tbAddXY->setText(tr("增加"));
    this->m_tbAddXY->setIcon(QIcon(":/common/images/common/add.png"));
    this->m_tbAddXY->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbDelXY=new QToolButton;
    this->m_tbDelXY->setText(tr("移除"));
    this->m_tbDelXY->setIcon(QIcon(":/common/images/common/del.png"));
    this->m_tbDelXY->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbResetXY=new QToolButton;
    this->m_tbResetXY->setText(tr("清空"));
    this->m_tbResetXY->setIcon(QIcon(":/common/images/common/Clear.png"));
    this->m_tbResetXY->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_vLayoutBtnXY=new QVBoxLayout;
    this->m_vLayoutBtnXY->addWidget(this->m_tbAddXY);
    this->m_vLayoutBtnXY->addWidget(this->m_tbDelXY);
    this->m_vLayoutBtnXY->addWidget(this->m_tbResetXY);
    this->m_vLayoutBtnXY->addStretch(1);

    this->m_grpFillXY=new QGroupBox(tr("自动复制到单元格(%1)").arg(this->m_relatedTemplate));
    this->m_hLayoutGrpXY=new QHBoxLayout;
    this->m_hLayoutGrpXY->addWidget(this->m_xyList);
    this->m_hLayoutGrpXY->addLayout(this->m_vLayoutBtnXY);
    this->m_grpFillXY->setLayout(this->m_hLayoutGrpXY);

    /////////////////////////////////////////////////////

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_grpPreVal);
    this->m_hLayout->addWidget(this->m_grpFillXY);
    this->setLayout(this->m_hLayout);

    connect(this->m_tbAdd,SIGNAL(clicked(bool)),this,SLOT(ZSlotAdd()));
    connect(this->m_tbDel,SIGNAL(clicked(bool)),this,SLOT(ZSlotDel()));
    connect(this->m_tbReset,SIGNAL(clicked(bool)),this,SLOT(ZSlotReset()));
    connect(this->m_tbImport,SIGNAL(clicked(bool)),this,SLOT(ZSlotImport()));
    connect(this->m_tbExport,SIGNAL(clicked(bool)),this,SLOT(ZSlotExport()));

    ////////////////////////////////////////////////////////////////////////
    connect(this->m_tbAddXY,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddXY()));
    connect(this->m_tbDelXY,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelXY()));
    connect(this->m_tbResetXY,SIGNAL(clicked(bool)),this,SLOT(ZSlotResetXY()));

    //read exist file data.
    QStringList itemList=this->ZReadList();
    for(qint32 i=0;i<itemList.count();i++)
    {
        QString itemText=itemList.at(i);
        QListWidgetItem *newItem=new QListWidgetItem(QIcon(":/TaskManager/images/TaskManager/ProductNo.png"),itemText);
        this->m_list->addItem(newItem);
    }

    //read xy file.
    QStringList xyList=this->ZReadXYList();
    for(qint32 i=0;i<xyList.count();i++)
    {
        this->m_xyList->addItem(xyList.at(i));
    }

    //disable xy auto fill cell feature when the reftemplate is empty.
    if(this->m_relatedTemplate.isEmpty())
    {
        this->m_grpFillXY->setEnabled(false);
    }
}
ZOrderNoPresetDialog::~ZOrderNoPresetDialog()
{
    delete this->m_tbAdd;
    delete this->m_tbDel;
    delete this->m_tbReset;
    delete this->m_tbImport;
    delete this->m_tbExport;
    delete this->m_vLayoutBtn;
    delete this->m_list;
    delete this->m_hLayoutGrp;
    delete this->m_grpPreVal;

    delete this->m_tbAddXY;
    delete this->m_tbDelXY;
    delete this->m_tbResetXY;
    delete this->m_vLayoutBtnXY;
    delete this->m_xyList;
    delete this->m_hLayoutGrpXY;
    delete this->m_grpFillXY;

    delete this->m_hLayout;
}
QSize ZOrderNoPresetDialog::sizeHint() const
{
    return QSize(600,300);
}
QStringList ZOrderNoPresetDialog::ZReadList()
{
    QStringList itemList;
    QFile orderNoFile(QDir::currentPath()+"/cfg/ORDER.dat");
    if(orderNoFile.open(QFile::ReadOnly|QIODevice::Text))
    {
        while(!orderNoFile.atEnd())
        {
            QByteArray baLine=orderNoFile.readLine();
            if(!baLine.isEmpty())
            {
                QString newText(baLine);
                newText.remove("\n");
                if(!newText.isEmpty())
                {
                    itemList.append(newText);
                }
            }
        }
        orderNoFile.close();
    }
    return itemList;
}
QStringList ZOrderNoPresetDialog::ZReadXYList()
{
    QStringList itemList;
    if(!this->m_relatedTemplate.isEmpty())
    {
        QString fileAutoXYFillName(QDir::currentPath()+"/cfg/"+this->m_relatedTemplate+".ORDER.XY");
        qDebug()<<"ORDER.XY.File:"<<fileAutoXYFillName;
        QFile fileAutoXYFill(fileAutoXYFillName);
        if(fileAutoXYFill.open(QFile::ReadOnly|QIODevice::Text))
        {
            while(!fileAutoXYFill.atEnd())
            {
                QByteArray baLine=fileAutoXYFill.readLine();
                if(!baLine.isEmpty())
                {
                    QString newText(baLine);
                    newText.remove("\n");
                    if(!newText.isEmpty())
                    {
                        itemList.append(newText);
                    }
                }
            }
            fileAutoXYFill.close();
        }
    }
    return itemList;
}
QStringList ZOrderNoPresetDialog::ZGetList()
{
    QStringList itemList;
    for(qint32 i=0;i<this->m_list->count();i++)
    {
        itemList.append(this->m_list->item(i)->text());
    }
    return itemList;
}
QStringList ZOrderNoPresetDialog::ZGetXYList()
{
    QStringList itemList;
    for(qint32 i=0;i<this->m_xyList->count();i++)
    {
        itemList.append(this->m_xyList->item(i)->text());
    }
    return itemList;
}
void ZOrderNoPresetDialog::closeEvent(QCloseEvent *e)
{
    //write to dat file.
    QString orderNoFileName(QDir::currentPath()+"/cfg/ORDER.dat");
    QFile orderNoFile(orderNoFileName);
    if(orderNoFile.open(QFile::WriteOnly|QIODevice::Truncate|QIODevice::Text))
    {
        for(qint32 i=0;i<this->m_list->count();i++)
        {
            QByteArray baWrite=this->m_list->item(i)->text().toLatin1();
            baWrite.append("\n");
            orderNoFile.write(baWrite);
        }
        orderNoFile.close();
    }else{
        QMessageBox::critical(this,tr("错误提示"),tr("写文件%1失败!").arg(orderNoFileName));
    }
    //write to xy file.
    if(!this->m_relatedTemplate.isEmpty())
    {
        QString fileAutoXYFillName(QDir::currentPath()+"/cfg/"+this->m_relatedTemplate+".ORDER.XY");
        QFile fileAutoXYFill(fileAutoXYFillName);
        if(fileAutoXYFill.open(QFile::WriteOnly|QIODevice::Truncate|QIODevice::Text))
        {
            for(qint32 i=0;i<this->m_xyList->count();i++)
            {
                QByteArray baWrite=this->m_xyList->item(i)->text().toLatin1();
                baWrite.append("\n");
                fileAutoXYFill.write(baWrite);
            }
            fileAutoXYFill.close();
        }else{
            QMessageBox::critical(this,tr("错误提示"),tr("写文件%1失败!").arg(fileAutoXYFillName));
        }
    }
    /////////////////
    e->accept();
}
void ZOrderNoPresetDialog::ZSlotAdd()
{
    QString newText=QInputDialog::getText(this,tr("新增项"),tr("请输入新项目"));
    if(newText.isEmpty())
    {
        return;
    }
    QListWidgetItem *newItem=new QListWidgetItem(QIcon(":/TaskManager/images/TaskManager/ProductNo.png"),newText);
    this->m_list->addItem(newItem);
}
void ZOrderNoPresetDialog::ZSlotDel()
{
    QListWidgetItem *item=this->m_list->currentItem();
    if(item)
    {
        this->m_list->removeItemWidget(item);
        delete item;
    }
}
void ZOrderNoPresetDialog::ZSlotReset()
{
    this->m_list->clear();
}
void ZOrderNoPresetDialog::ZSlotImport()
{

}
void ZOrderNoPresetDialog::ZSlotExport()
{

}
void ZOrderNoPresetDialog::ZSlotAddXY()
{
    QString xyCell=QInputDialog::getText(this,tr("请输入坐标"),tr("请输入单元格坐标,格式: x,y\n例如： 2,2"));
    if(xyCell.isEmpty())
    {
        return;
    }
    QStringList xyCellList=xyCell.split(",");
    if(xyCellList.size()!=2)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("输入单元格坐标格式不正确!"));
        return;
    }
    bool bOkX=false;
    bool bOkY=false;
    QString x=xyCellList.at(0);
    QString y=xyCellList.at(1);
    x.toInt(&bOkX);
    y.toInt(&bOkY);
    if(!bOkX || !bOkY)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请输入数值型的单元格坐标!"));
        return;
    }
    this->m_xyList->addItem(xyCell);
}
void ZOrderNoPresetDialog::ZSlotDelXY()
{
    QListWidgetItem *item=this->m_xyList->currentItem();
    if(item)
    {
        this->m_xyList->removeItemWidget(item);
        delete item;
    }
}
void ZOrderNoPresetDialog::ZSlotResetXY()
{
    this->m_xyList->clear();
}

///产品编号预置输入对话框
ZProductNoPresetDialog::ZProductNoPresetDialog(QString templateName,QWidget *parent):QDialog(parent)
{
    this->m_relatedTemplate=templateName;

    this->setWindowTitle(tr("产品号-输入预置列表"));

    this->m_tbAdd=new QToolButton;
    this->m_tbAdd->setText(tr("增加"));
    this->m_tbAdd->setIcon(QIcon(":/common/images/common/add.png"));
    this->m_tbAdd->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbDel=new QToolButton;
    this->m_tbDel->setText(tr("移除"));
    this->m_tbDel->setIcon(QIcon(":/common/images/common/del.png"));
    this->m_tbDel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbReset=new QToolButton;
    this->m_tbReset->setText(tr("清空"));
    this->m_tbReset->setIcon(QIcon(":/common/images/common/Clear.png"));
    this->m_tbReset->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbImport=new QToolButton;
    this->m_tbImport->setText(tr("导入"));
    this->m_tbImport->setIcon(QIcon(":/UserManager/images/UserManager/Import.png"));
    this->m_tbImport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbExport=new QToolButton;
    this->m_tbExport->setText(tr("导出"));
    this->m_tbExport->setIcon(QIcon(":/UserManager/images/UserManager/Export.png"));
    this->m_tbExport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_vLayoutBtn=new QVBoxLayout;
    this->m_vLayoutBtn->addWidget(this->m_tbAdd);
    this->m_vLayoutBtn->addWidget(this->m_tbDel);
    this->m_vLayoutBtn->addWidget(this->m_tbReset);
    this->m_vLayoutBtn->addWidget(this->m_tbImport);
    this->m_vLayoutBtn->addWidget(this->m_tbExport);
    this->m_vLayoutBtn->addStretch(1);

    this->m_list=new QListWidget;
    this->m_grpPreVal=new QGroupBox(tr("预输入列表"));
    this->m_hLayoutGrp=new QHBoxLayout;
    this->m_hLayoutGrp->addWidget(this->m_list);
    this->m_hLayoutGrp->addLayout(this->m_vLayoutBtn);
    this->m_grpPreVal->setLayout(this->m_hLayoutGrp);


    /////////////////////////////////////////////////


    this->m_xyList=new QListWidget;
    this->m_tbAddXY=new QToolButton;
    this->m_tbAddXY->setText(tr("增加"));
    this->m_tbAddXY->setIcon(QIcon(":/common/images/common/add.png"));
    this->m_tbAddXY->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbDelXY=new QToolButton;
    this->m_tbDelXY->setText(tr("移除"));
    this->m_tbDelXY->setIcon(QIcon(":/common/images/common/del.png"));
    this->m_tbDelXY->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbResetXY=new QToolButton;
    this->m_tbResetXY->setText(tr("清空"));
    this->m_tbResetXY->setIcon(QIcon(":/common/images/common/Clear.png"));
    this->m_tbResetXY->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_vLayoutBtnXY=new QVBoxLayout;
    this->m_vLayoutBtnXY->addWidget(this->m_tbAddXY);
    this->m_vLayoutBtnXY->addWidget(this->m_tbDelXY);
    this->m_vLayoutBtnXY->addWidget(this->m_tbResetXY);
    this->m_vLayoutBtnXY->addStretch(1);

    this->m_grpFillXY=new QGroupBox(tr("自动复制到单元格(%1)").arg(this->m_relatedTemplate));
    this->m_hLayoutGrpXY=new QHBoxLayout;
    this->m_hLayoutGrpXY->addWidget(this->m_xyList);
    this->m_hLayoutGrpXY->addLayout(this->m_vLayoutBtnXY);
    this->m_grpFillXY->setLayout(this->m_hLayoutGrpXY);

    /////////////////////////////////////////////////////

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_grpPreVal);
    this->m_hLayout->addWidget(this->m_grpFillXY);
    this->setLayout(this->m_hLayout);

    connect(this->m_tbAdd,SIGNAL(clicked(bool)),this,SLOT(ZSlotAdd()));
    connect(this->m_tbDel,SIGNAL(clicked(bool)),this,SLOT(ZSlotDel()));
    connect(this->m_tbReset,SIGNAL(clicked(bool)),this,SLOT(ZSlotReset()));
    connect(this->m_tbImport,SIGNAL(clicked(bool)),this,SLOT(ZSlotImport()));
    connect(this->m_tbExport,SIGNAL(clicked(bool)),this,SLOT(ZSlotExport()));

    ////////////////////////////////////////////////////////////////////////
    connect(this->m_tbAddXY,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddXY()));
    connect(this->m_tbDelXY,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelXY()));
    connect(this->m_tbResetXY,SIGNAL(clicked(bool)),this,SLOT(ZSlotResetXY()));
}
ZProductNoPresetDialog::~ZProductNoPresetDialog()
{
    delete this->m_tbAdd;
    delete this->m_tbDel;
    delete this->m_tbReset;
    delete this->m_tbImport;
    delete this->m_tbExport;
    delete this->m_vLayoutBtn;
    delete this->m_list;
    delete this->m_hLayoutGrp;
    delete this->m_grpPreVal;

    delete this->m_tbAddXY;
    delete this->m_tbDelXY;
    delete this->m_tbResetXY;
    delete this->m_vLayoutBtnXY;
    delete this->m_xyList;
    delete this->m_hLayoutGrpXY;
    delete this->m_grpFillXY;

    delete this->m_hLayout;
}
QSize ZProductNoPresetDialog::sizeHint() const
{
    return QSize(600,300);
}

void ZProductNoPresetDialog::ZSetPreVal_XY_List(const QStringList &preValList,const QStringList &xyList)
{
    this->m_list->clear();
    for(qint32 i=0;i<preValList.size();i++)
    {
        QString preVal=preValList.at(i);
        if(preVal.isEmpty())
        {
            continue;
        }
        this->m_list->addItem(preVal);
    }
    this->m_xyList->clear();
    for(qint32 i=0;i<xyList.size();i++)
    {
        QString xy=xyList.at(i);
        if(xy.isEmpty())
        {
            continue;
        }
        this->m_xyList->addItem(xy);
    }
}
void ZProductNoPresetDialog::ZGetPreVal_XY_List(QStringList &preValList,QStringList &xyList)
{
    preValList.clear();
    for(qint32 i=0;i<this->m_list->count();i++)
    {
        preValList.append(this->m_list->item(i)->text());
    }
    xyList.clear();
    for(qint32 i=0;i<this->m_xyList->count();i++)
    {
        xyList.append(this->m_xyList->item(i)->text());
    }
}

void ZProductNoPresetDialog::ZSlotAdd()
{
    QString newText=QInputDialog::getText(this,tr("新增项"),tr("请输入新项目"));
    if(newText.isEmpty())
    {
        return;
    }
    QListWidgetItem *newItem=new QListWidgetItem(QIcon(":/TaskManager/images/TaskManager/ProductNo.png"),newText);
    this->m_list->addItem(newItem);
}
void ZProductNoPresetDialog::ZSlotDel()
{
    QListWidgetItem *item=this->m_list->currentItem();
    if(item)
    {
        this->m_list->removeItemWidget(item);
        delete item;
    }
}
void ZProductNoPresetDialog::ZSlotReset()
{
    this->m_list->clear();
}
void ZProductNoPresetDialog::ZSlotImport()
{

}
void ZProductNoPresetDialog::ZSlotExport()
{

}
void ZProductNoPresetDialog::ZSlotAddXY()
{
    QString xyCell=QInputDialog::getText(this,tr("请输入坐标"),tr("请输入单元格坐标,格式: x,y\n例如： 2,2"));
    if(xyCell.isEmpty())
    {
        return;
    }
    QStringList xyCellList=xyCell.split(",");
    if(xyCellList.size()!=2)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("输入单元格坐标格式不正确!"));
        return;
    }
    bool bOkX=false;
    bool bOkY=false;
    QString x=xyCellList.at(0);
    QString y=xyCellList.at(1);
    x.toInt(&bOkX);
    y.toInt(&bOkY);
    if(!bOkX || !bOkY)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请输入数值型的单元格坐标!"));
        return;
    }
    this->m_xyList->addItem(xyCell);
}
void ZProductNoPresetDialog::ZSlotDelXY()
{
    QListWidgetItem *item=this->m_xyList->currentItem();
    if(item)
    {
        this->m_xyList->removeItemWidget(item);
        delete item;
    }
}
void ZProductNoPresetDialog::ZSlotResetXY()
{
    this->m_xyList->clear();
}
