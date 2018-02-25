#include "zprocesssteplinktemplateselectdia.h"
#include <TaskManager/zlistprocesssteplinktemplatedia.h>
#include <QXmlStreamReader>
#include <QMessageBox>
ZProcessStepLinkTemplateSelectDia::ZProcessStepLinkTemplateSelectDia(QWidget *parent):QDialog(parent)
{
    this->setMinimumSize(500,300);

    this->setWindowTitle(tr("请选择创建任务要引用的模板"));
    this->m_tree=new QTreeWidget;
    this->m_tree->setColumnCount(3);
    this->m_tree->setIconSize(QSize(24,24));
    QStringList headerList;
    headerList<<tr("工序");
    headerList<<tr("步序");
    headerList<<tr("关联模板");
    this->m_tree->setHeaderLabels(headerList);
    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_tbOkay);
    this->m_hLayout->addWidget(this->m_tbCancel);
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_tree);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
    //list all tasks.
    ZListProcessStepLinkTemplateDia *dia=new ZListProcessStepLinkTemplateDia;
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteListOp();
    dia->ZShowWaitingDialog();
}
ZProcessStepLinkTemplateSelectDia::~ZProcessStepLinkTemplateSelectDia()
{
    delete this->m_tree;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayout;
    delete this->m_vLayout;
}

void ZProcessStepLinkTemplateSelectDia::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{
    if(item=="process")
    {
        if(cmd=="listnew")
        {
            QString processName=paraList.at(0);
            if(ackNetRetCode<0)
            {
                //list failed.to do something here.
            }else{
                QTreeWidgetItem *item=new QTreeWidgetItem(0);//type:0,process,1,step,2,linktemplate.
                item->setIcon(0,QIcon(":/ProcessEditor/images/ProcessEditor/Process.png"));
                item->setText(0,processName);
                this->m_tree->addTopLevelItem(item);
            }
        }//listnew.
    }else if(item=="step")
    {
        if(cmd=="listnew")
        {
            QString processName=paraList.at(0);
            QString stepName=paraList.at(1);
            QString linkTemplate=paraList.at(2);
            if(ackNetRetCode<0)
            {
                //list failed.to do something here.
            }else{
                for(qint32 i=0;i<this->m_tree->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *processItem=this->m_tree->topLevelItem(i);
                    if(processItem->text(0)==processName)
                    {
                        QTreeWidgetItem *stepItem=new QTreeWidgetItem(1);//type:0,process,1,step,2,linktemplate.
                        stepItem->setIcon(1,QIcon(":/ProcessEditor/images/ProcessEditor/Step.png"));
                        stepItem->setText(1,stepName);
                        processItem->addChild(stepItem);

                        QStringList linkTemplateList=linkTemplate.split(":");
                        for(qint32 j=0;j<linkTemplateList.count();j++)
                        {
                            QString templateName=linkTemplateList.at(j);
                            if(!templateName.isEmpty())
                            {
                                QTreeWidgetItem *templateItem=new QTreeWidgetItem(2);//type:0,process,1,step,2,linktemplate.
                                templateItem->setIcon(2,QIcon(":/TemplateEditor/images/TemplateEditor/Template.png"));
                                templateItem->setText(2,templateName);
                                stepItem->addChild(templateItem);
                            }
                        }
                    }
                }
            }
        }//listnew.
    }
}
QString ZProcessStepLinkTemplateSelectDia::ZGetSelectedTemplate()
{
    QTreeWidgetItem *item=this->m_tree->currentItem();
    return item->text(2);
}
QString ZProcessStepLinkTemplateSelectDia::ZGetSelectedProcess()
{
    QTreeWidgetItem *item=this->m_tree->currentItem();
    return item->parent()->parent()->text(0);
}
QString ZProcessStepLinkTemplateSelectDia::ZGetSelectedStep()
{
    QTreeWidgetItem *item=this->m_tree->currentItem();
    return item->parent()->text(1);
}
QSize ZProcessStepLinkTemplateSelectDia::sizeHint() const
{
    return QSize(500,250);
}
void ZProcessStepLinkTemplateSelectDia::ZSlotOkay()
{
    //type:0,process,1,step,2,linktemplate.
    QTreeWidgetItem *item=this->m_tree->currentItem();
    if(item==NULL)
    {
        return;
    }
    if(item->type()!=2)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请选择想要创建任务的模板!"));
        return;
    }
    this->accept();
}
void ZProcessStepLinkTemplateSelectDia::ZSlotCancel()
{
    this->reject();
}
