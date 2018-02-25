#include "pstepeditor.h"
#include <ProcessEditor/zlinktemplateselectdia.h>
#include <ProcessEditor/zlinkfileselectdia.h>
#include <ProcessEditor/zlinkroleselectdia.h>
#include <QDebug>
PStepEditor::PStepEditor()
{
    this->setStyleSheet("QFrame{border-radius:30px;background-color:#B9B9FF;}"
                        "QListWidget{border-radius:0px;border:1px solid black;}");
    //step name.
    this->m_llStepName=new QLabel(tr("步序名(*)"));
    this->m_leStepName=new QLineEdit;
    this->m_leStepName->setMaxLength(45);


    QString btnQss("QToolButton{border:none;background: transparent;padding: 6px 12px 6px 12p}"
                   "QToolButton::hover{background-color:#eaf7ff;}");
    this->m_tbClose=new QToolButton;
    this->m_tbClose->setStyleSheet(btnQss);
    this->m_tbClose->setIcon(QIcon(":/ProcessEditor/images/ProcessEditor/DelStep.png"));
    //link template.
    this->m_llLinkTemplate=new QLabel(tr("关联\n模板\n列表"));
    this->m_lwLinkTemplate=new QListWidget;
    this->m_btnAddTemplate=new QToolButton;
    this->m_btnAddTemplate->setStyleSheet(btnQss);
    this->m_btnAddTemplate->setIcon(QIcon(":/ProcessEditor/images/ProcessEditor/Add.png"));
    this->m_btnDelTemplate=new QToolButton;
    this->m_btnDelTemplate->setStyleSheet(btnQss);
    this->m_btnDelTemplate->setIcon(QIcon(":/ProcessEditor/images/ProcessEditor/Del.png"));

    //link pdf files.
    this->m_llLinkFiles=new QLabel(tr("关联\n文件\n列表"));
    this->m_lwLinkFiles=new QListWidget;
    this->m_btnAddFiles=new QToolButton;
    this->m_btnAddFiles->setStyleSheet(btnQss);
    this->m_btnAddFiles->setIcon(QIcon(":/ProcessEditor/images/ProcessEditor/Add.png"));
    this->m_btnDelFiles=new QToolButton;
    this->m_btnDelFiles->setStyleSheet(btnQss);
    this->m_btnDelFiles->setIcon(QIcon(":/ProcessEditor/images/ProcessEditor/Del.png"));

    //link roles.
    this->m_lLinkRoles=new QLabel(tr("关联\n角色\n列表"));
    this->m_lwLinkRoles=new QListWidget;
    this->m_btnAddRoles=new QToolButton;
    this->m_btnAddRoles->setStyleSheet(btnQss);
    this->m_btnAddRoles->setIcon(QIcon(":/ProcessEditor/images/ProcessEditor/Add.png"));
    this->m_btnDelRoles=new QToolButton;
    this->m_btnDelRoles->setStyleSheet(btnQss);
    this->m_btnDelRoles->setIcon(QIcon(":/ProcessEditor/images/ProcessEditor/Del.png"));

    //layout.
    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->setMargin(10);
    //step name.row:0.
    this->m_gridLayout->addWidget(this->m_llStepName,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leStepName,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbClose,0,2,1,1);
    //link sheets.row:1,2.
    this->m_gridLayout->addWidget(this->m_llLinkTemplate,1,0,2,1);
    this->m_gridLayout->addWidget(this->m_lwLinkTemplate,1,1,2,1);
    this->m_gridLayout->addWidget(this->m_btnAddTemplate,1,2,1,1);
    this->m_gridLayout->addWidget(this->m_btnDelTemplate,2,2,1,1);
    //link files,row:3,4.
    this->m_gridLayout->addWidget(this->m_llLinkFiles,3,0,2,1);
    this->m_gridLayout->addWidget(this->m_lwLinkFiles,3,1,2,1);
    this->m_gridLayout->addWidget(this->m_btnAddFiles,3,2,1,1);
    this->m_gridLayout->addWidget(this->m_btnDelFiles,4,2,1,1);
    //link roles,:row:5,6.
    this->m_gridLayout->addWidget(this->m_lLinkRoles,5,0,2,1);
    this->m_gridLayout->addWidget(this->m_lwLinkRoles,5,1,2,1);
    this->m_gridLayout->addWidget(this->m_btnAddRoles,5,2,1,1);
    this->m_gridLayout->addWidget(this->m_btnDelRoles,6,2,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_tbClose,SIGNAL(clicked(bool)),this,SLOT(ZSlotCloseMe()));
    connect(this->m_btnAddTemplate,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddLinkTemplate()));
    connect(this->m_btnDelTemplate,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelLinkTemplate()));
    connect(this->m_btnAddFiles,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddLinkFile()));
    connect(this->m_btnDelFiles,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelLinkFile()));
    connect(this->m_btnAddRoles,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddLinkRole()));
    connect(this->m_btnDelRoles,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelLinkRole()));

    connect(this->m_leStepName,SIGNAL(textChanged(QString)),this,SIGNAL(ZSignalDataChanged()));
    connect(this->m_lwLinkTemplate,SIGNAL(currentTextChanged(QString)),this,SIGNAL(ZSignalDataChanged()));
    connect(this->m_lwLinkFiles,SIGNAL(currentTextChanged(QString)),this,SIGNAL(ZSignalDataChanged()));
    connect(this->m_lwLinkRoles,SIGNAL(currentTextChanged(QString)),this,SIGNAL(ZSignalDataChanged()));
}
PStepEditor::~PStepEditor()
{
    //step name.
    delete this->m_llStepName;
    delete this->m_leStepName;
    delete this->m_tbClose;

    //link template.
    delete this->m_llLinkTemplate;
    delete this->m_lwLinkTemplate;
    delete this->m_btnAddTemplate;
    delete this->m_btnDelTemplate;

    //link pdf files.
    delete this->m_llLinkFiles;
    delete this->m_lwLinkFiles;
    delete this->m_btnAddFiles;
    delete this->m_btnDelFiles;

    //link roles.
    delete this->m_lLinkRoles;
    delete this->m_lwLinkRoles;
    delete this->m_btnAddRoles;
    delete this->m_btnDelRoles;

    //layout.
    delete this->m_gridLayout;
}
void PStepEditor::ZSlotCloseMe()
{
    emit this->ZSignalCloseMe(this);
}
QString PStepEditor::ZGetStepName()
{
    return this->m_leStepName->text().trimmed();
}
void PStepEditor::ZSetStepName(QString stepName)
{
    this->m_leStepName->setText(stepName);
}
QStringList PStepEditor::ZGetLinkTemplates()
{
    QStringList templates;
    for(qint32 i=0;i<this->m_lwLinkTemplate->count();i++)
    {
        templates.append(this->m_lwLinkTemplate->item(i)->text());
    }
    return templates;
}
void PStepEditor::ZSetLinkTemplates(QStringList templates)
{
    this->m_lwLinkTemplate->clear();
    for(qint32 i=0;i<templates.count();i++)
    {
        QString templateName=templates.at(i);
        if(!templateName.isEmpty())
        {
            QListWidgetItem *item=new QListWidgetItem;
            item->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/Template.png"));
            item->setText(templateName);
            this->m_lwLinkTemplate->addItem(item);
        }
    }
}
QStringList PStepEditor::ZGetLinkFiles()
{
    QStringList filesList;
    for(qint32 i=0;i<this->m_lwLinkFiles->count();i++)
    {
        filesList.append(this->m_lwLinkFiles->item(i)->text());
    }
    return filesList;
}
void PStepEditor::ZSetLinkFiles(QStringList files)
{
    this->m_lwLinkFiles->clear();
    for(qint32 i=0;i<files.count();i++)
    {
        QString fileName=files.at(i);
        if(!fileName.isEmpty())
        {
            QListWidgetItem *item=new QListWidgetItem;
            item->setIcon(QIcon(":/FileManager/images/FileManager/PdfFile.png"));
            item->setText(fileName);
            this->m_lwLinkFiles->addItem(item);
        }
    }
}
QStringList PStepEditor::ZGetLinkRoles()
{
    QStringList rolesList;
    for(qint32 i=0;i<this->m_lwLinkRoles->count();i++)
    {
        rolesList.append(this->m_lwLinkRoles->item(i)->text());
    }
    return rolesList;
}
void PStepEditor::ZSetLinkRoles(QStringList roles)
{
    this->m_lwLinkRoles->clear();
    for(qint32 i=0;i<roles.count();i++)
    {
        QString roleName=roles.at(i);
        if(!roleName.isEmpty())
        {
            QListWidgetItem *item=new QListWidgetItem;
            item->setIcon(QIcon(":/UserManager/images/UserManager/MdyGrp.png"));
            item->setText(roleName);
            this->m_lwLinkRoles->addItem(item);
        }
    }
}
void PStepEditor::ZSlotAddLinkTemplate()
{
    ZLinkTemplateSelectDia dia(this);
    if(dia.exec()==QDialog::Accepted)
    {
        QStringList list=dia.ZGetSelectedTemplateList();
        for(qint32 i=0;i<list.count();i++)
        {
            QString templateName=list.at(i);
            if(!templateName.isEmpty())
            {
                bool bAdded=false;
                //to avoid multiple add.
                for(qint32 j=0;j<this->m_lwLinkTemplate->count();j++)
                {
                    QListWidgetItem *item=this->m_lwLinkTemplate->item(j);
                    if(item->text()==templateName)
                    {
                        bAdded=true;
                        break;
                    }
                }
                if(bAdded==false)
                {
                    QListWidgetItem *item=new QListWidgetItem;
                    item->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/Template.png"));
                    item->setText(templateName);
                    this->m_lwLinkTemplate->addItem(item);
                }
            }
        }
    }
}
void PStepEditor::ZSlotDelLinkTemplate()
{
    QListWidgetItem *item=this->m_lwLinkTemplate->currentItem();
    if(item)
    {
        this->m_lwLinkTemplate->removeItemWidget(item);
        delete item;
        item=NULL;
    }
}
void PStepEditor::ZSlotAddLinkFile()
{
    ZLinkFileSelectDia dia(this);
    if(dia.exec()==QDialog::Accepted)
    {
        QStringList list=dia.ZGetSelectedFileList();
        for(qint32 i=0;i<list.count();i++)
        {
            QString fileName=list.at(i);
            if(!fileName.isEmpty())
            {
                bool bAdded=false;
                //to avoid multiple add.
                for(qint32 j=0;j<this->m_lwLinkFiles->count();j++)
                {
                    QListWidgetItem *item=this->m_lwLinkFiles->item(j);
                    if(item->text()==fileName)
                    {
                        bAdded=true;
                        break;
                    }
                }
                if(bAdded==false)
                {
                    QListWidgetItem *item=new QListWidgetItem;
                    item->setIcon(QIcon(":/FileManager/images/FileManager/PdfFile.png"));
                    item->setText(fileName);
                    this->m_lwLinkFiles->addItem(item);
                }
            }
        }
    }
}
void PStepEditor::ZSlotDelLinkFile()
{
    QListWidgetItem *item=this->m_lwLinkFiles->currentItem();
    if(item)
    {
        this->m_lwLinkFiles->removeItemWidget(item);
        delete item;
        item=NULL;
    }
}
void PStepEditor::ZSlotAddLinkRole()
{
    ZLinkRoleSelectDia dia(this);
    if(dia.exec()==QDialog::Accepted)
    {
        QStringList list=dia.ZGetSelectedRoleList();
        for(qint32 i=0;i<list.count();i++)
        {
            QString roleName=list.at(i);
            if(!roleName.isEmpty())
            {
                bool bAdded=false;
                //to avoid multiple add.
                for(qint32 j=0;j<this->m_lwLinkRoles->count();j++)
                {
                    QListWidgetItem *item=this->m_lwLinkRoles->item(j);
                    if(item->text()==roleName)
                    {
                        bAdded=true;
                        break;
                    }
                }
                if(bAdded==false)
                {
                    QListWidgetItem *item=new QListWidgetItem;
                    item->setIcon(QIcon(":/UserManager/images/UserManager/MdyGrp.png"));
                    item->setText(roleName);
                    this->m_lwLinkRoles->addItem(item);
                }
            }
        }
    }
}
void PStepEditor::ZSlotDelLinkRole()
{
    QListWidgetItem *item=this->m_lwLinkRoles->currentItem();
    if(item)
    {
        this->m_lwLinkRoles->removeItemWidget(item);
        delete item;
        item=NULL;
    }
}
