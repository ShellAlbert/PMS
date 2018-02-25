#include "zlinktemplateselectdia.h"
#include <TemplateEditor/zlisttemplateinfodia.h>
#include <QMessageBox>
ZLinkTemplateSelectDia::ZLinkTemplateSelectDia(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("请选择需要关联的模板"));

    this->m_tree=new QTreeWidget;
    this->m_tree->setColumnCount(5);
    QStringList headerList;
    headerList<<tr("模板名称");
    headerList<<tr("绑定变量源");
    headerList<<tr("占用磁盘");
    headerList<<tr("创建者");
    headerList<<tr("创建时间");
    this->m_tree->setHeaderLabels(headerList);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));

    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_tbOkay);
    this->m_hLayout->addWidget(this->m_tbCancel);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_tree);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    ZListTemplateVarSourceInfoDia *dia=new ZListTemplateVarSourceInfoDia(this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteListOp();
    dia->ZShowWaitingDialog();
}
ZLinkTemplateSelectDia::~ZLinkTemplateSelectDia()
{
    delete this->m_tree;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayout;
    delete this->m_vLayout;
}
 QSize ZLinkTemplateSelectDia::sizeHint() const
 {
     return QSize(500,250);
 }
void ZLinkTemplateSelectDia::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{
    if(item=="template")
    {
        if(cmd=="list")
        {
            QString templateName=paraList.at(0);
            QString varSourceName=paraList.at(1);
            QString fileSize=paraList.at(2);
            QString creator=paraList.at(3);
            QString createTime=paraList.at(4);
            QString errMsg=paraList.at(5);
            if(ackNetRetCode<0)
            {
                //failed to list templates.
                QMessageBox::critical(this,tr("错误提示"),errMsg);
            }else{
                QTreeWidgetItem *item=new QTreeWidgetItem(0);
                item->setCheckState(0,Qt::Unchecked);
                item->setIcon(0,QIcon(":/TemplateEditor/images/TemplateEditor/Template.png"));
                item->setText(0,templateName);
                item->setText(1,varSourceName);
                item->setText(2,fileSize+"K");
                item->setText(3,creator);
                item->setText(4,createTime);
                this->m_tree->addTopLevelItem(item);
                this->m_tree->setCurrentItem(item);
            }
        }//list.
    }//template.
}
QStringList ZLinkTemplateSelectDia::ZGetSelectedTemplateList()
{
    QStringList selectList;
    for(qint32 i=0;i<this->m_tree->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=this->m_tree->topLevelItem(i);
        if(item->checkState(0)==Qt::Checked)
        {
            selectList.append(item->text(0));
        }
    }
    return selectList;
}
