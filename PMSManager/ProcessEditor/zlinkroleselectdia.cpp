#include "zlinkroleselectdia.h"
#include <UserManager/zlistroleuserinfodia.h>
#include <QMessageBox>
ZLinkRoleSelectDia::ZLinkRoleSelectDia(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("请选择需要关联的角色"));
    this->setMinimumSize(600,300);

    this->m_tree=new QTreeWidget;
    this->m_tree->setColumnCount(4);
    QStringList headerList;
    headerList<<tr("角色名称");
    headerList<<tr("角色描述");
    headerList<<tr("创建者");
    headerList<<tr("创建时间");
    this->m_tree->setHeaderLabels(headerList);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("OKAY"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("CANCEL"));
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

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    //list all roles and users.
    ZListRoleUserInfoDia *dia=new ZListRoleUserInfoDia(this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteListOp();
    dia->ZShowWaitingDialog();
}
ZLinkRoleSelectDia::~ZLinkRoleSelectDia()
{
    delete this->m_tree;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayout;
    delete this->m_vLayout;
}
void ZLinkRoleSelectDia::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{
    if(item=="role")
    {
        if(cmd=="list")
        {
            QString roleName=paraList.at(0);
            QString permBits=paraList.at(1);
            QString roleMemo=paraList.at(2);
            QString creator=paraList.at(3);
            QString createTime=paraList.at(4);
            if(ackNetRetCode<0)
            {
                //failed to list folder.
            }else{
                QTreeWidgetItem *roleItem=new QTreeWidgetItem(0);
                roleItem->setIcon(0,QIcon(":/UserManager/images/UserManager/MdyGrp.png"));
                roleItem->setCheckState(0,Qt::Unchecked);
                roleItem->setText(0,roleName);
                roleItem->setText(1,roleMemo);
                roleItem->setText(2,creator);
                roleItem->setText(3,createTime);
                this->m_tree->addTopLevelItem(roleItem);
                this->m_tree->setCurrentItem(roleItem);
            }
        }//list.
    }
}
QStringList ZLinkRoleSelectDia::ZGetSelectedRoleList()
{
    QStringList selectList;
    for(qint32 i=0;i<this->m_tree->topLevelItemCount();i++)
    {
        QTreeWidgetItem *roleItem=this->m_tree->topLevelItem(i);
        if(roleItem->checkState(0)==Qt::Checked)
        {
            selectList.append(roleItem->text(0));
        }
    }
    return selectList;
}
