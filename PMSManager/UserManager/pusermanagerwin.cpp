#include "pusermanagerwin.h"
#include <QHeaderView>
#include <QDateTime>
#include <QMessageBox>
#include "UserManager/zlistroleuserinfodia.h"
#include "UserManager/zgrpinfodia.h"
#include "UserManager/zuserinfodia.h"
#include "UserManager/zimportroleuserinfodia.h"
#include "pgblpara.h"
#include <QXmlStreamWriter>
#include <QFileDialog>
#include "NetProtocol/pnetframe.h"
#include "pwaitingdia.h"
#include <QDebug>
PUserManagerWin::PUserManagerWin()
{
    this->setWindowTitle(tr("用户管理器-User Manager"));
    this->setWindowIcon(QIcon(":/TaskBar/images/UserManager.png"));

    this->setStyleSheet("QToolButton{background-color:#cce5f9;border:none;font:color #eaf7ff;}"
                        "QToolButton::hover{background-color:#eaf7ff;}"
                        "");
    //right.
    this->m_treeWidget=new QTreeWidget;
    this->m_treeWidget->setIconSize(QSize(24,24));
    this->m_treeWidget->setColumnCount(7);
    //this->m_treeWidget->header()->setDefaultAlignment(Qt::AlignCenter);
    QStringList headerList;
    headerList<<tr("用户名");
    headerList<<tr("真实姓名");
    headerList<<tr("性别");
    headerList<<tr("手机号码");
    headerList<<tr("创建者");
    headerList<<tr("创建时间");
    headerList<<tr("末次登录时间");
    this->m_treeWidget->setHeaderLabels(headerList);

    //left.
    this->m_vLayoutBtn=new QVBoxLayout;

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_AddGrp)
    {
        this->m_btnAddGrp=new QToolButton;
        this->m_btnAddGrp->setToolTip(tr("创建角色"));
        this->m_btnAddGrp->setText(tr("创建"));
        this->m_btnAddGrp->setIcon(QIcon(":/UserManager/images/UserManager/AddGrp.png"));
        this->m_btnAddGrp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutBtn->addWidget(this->m_btnAddGrp);
        connect(this->m_btnAddGrp,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddGrp()));
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_MdyGrp)
    {
        this->m_btnMdyGrp=new QToolButton;
        this->m_btnMdyGrp->setToolTip(tr("编辑角色"));
        this->m_btnMdyGrp->setText(tr("编辑"));
        this->m_btnMdyGrp->setIcon(QIcon(":/UserManager/images/UserManager/MdyGrp.png"));
        this->m_btnMdyGrp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutBtn->addWidget(this->m_btnMdyGrp);
        connect(this->m_btnMdyGrp,SIGNAL(clicked(bool)),this,SLOT(ZSlotMdyGrp()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_DelGrp)
    {
        this->m_btnDelGrp=new QToolButton;
        this->m_btnDelGrp->setToolTip(tr("删除角色"));
        this->m_btnDelGrp->setText(tr("删除"));
        this->m_btnDelGrp->setIcon(QIcon(":/UserManager/images/UserManager/DelGrp.png"));
        this->m_btnDelGrp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutBtn->addWidget(this->m_btnDelGrp);
        connect(this->m_btnDelGrp,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelGrp()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_AddUser)
    {
        this->m_btnAddUser=new QToolButton;
        this->m_btnAddUser->setToolTip(tr("创建用户"));
        this->m_btnAddUser->setText(tr("创建"));
        this->m_btnAddUser->setIcon(QIcon(":/UserManager/images/UserManager/AddUser.png"));
        this->m_btnAddUser->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutBtn->addWidget(this->m_btnAddUser);
        connect(this->m_btnAddUser,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddUser()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_MdyUser)
    {
        this->m_btnMdyUser=new QToolButton;
        this->m_btnMdyUser->setToolTip(tr("编辑用户"));
        this->m_btnMdyUser->setText(tr("编辑"));
        this->m_btnMdyUser->setIcon(QIcon(":/UserManager/images/UserManager/MdyUser.png"));
        this->m_btnMdyUser->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutBtn->addWidget(this->m_btnMdyUser);
        connect(this->m_btnMdyUser,SIGNAL(clicked(bool)),this,SLOT(ZSlotMdyUser()));
        connect(this->m_treeWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ZSlotTreeDblClicked(QModelIndex)));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_DelUser)
    {
        this->m_btnDelUser=new QToolButton;
        this->m_btnDelUser->setToolTip(tr("删除用户"));
        this->m_btnDelUser->setText(tr("删除"));
        this->m_btnDelUser->setIcon(QIcon(":/UserManager/images/UserManager/DelUser.png"));
        this->m_btnDelUser->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutBtn->addWidget(this->m_btnDelUser);
        connect(this->m_btnDelUser,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelUser()));
    }

    this->m_btnExpand=new QToolButton;
    this->m_btnExpand->setToolTip(tr("全部展开"));
    this->m_btnExpand->setText(tr("展开"));
    this->m_btnExpand->setIcon(QIcon(":/UserManager/images/UserManager/Expand.png"));
    this->m_btnExpand->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(this->m_btnExpand,SIGNAL(clicked(bool)),this,SLOT(ZSlotExpand()));
    this->m_vLayoutBtn->addStretch(1);
    this->m_vLayoutBtn->addWidget(this->m_btnExpand);

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_Import)
    {
        this->m_btnImport=new QToolButton;
        this->m_btnImport->setToolTip(tr("导入..."));
        this->m_btnImport->setText(tr("导入"));
        this->m_btnImport->setIcon(QIcon(":/UserManager/images/UserManager/Import.png"));
        this->m_btnImport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutBtn->addWidget(this->m_btnImport);
        connect(this->m_btnImport,SIGNAL(clicked(bool)),this,SLOT(ZSlotImport()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_Export)
    {
        this->m_btnExport=new QToolButton;
        this->m_btnExport->setToolTip(tr("导出..."));
        this->m_btnExport->setText(tr("导出"));
        this->m_btnExport->setIcon(QIcon(":/UserManager/images/UserManager/Export.png"));
        this->m_btnExport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutBtn->addWidget(this->m_btnExport);
        connect(this->m_btnExport,SIGNAL(clicked(bool)),this,SLOT(ZSlotExport()));
    }

    //help.
    this->m_btnHelp=new QToolButton;
    this->m_btnHelp->setToolTip(tr("获取帮助文档"));
    this->m_btnHelp->setText(tr("帮助"));
    this->m_btnHelp->setIcon(QIcon(":/common/images/common/help.png"));
    this->m_btnHelp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_vLayoutBtn->addWidget(this->m_btnHelp);
    connect(this->m_btnHelp,SIGNAL(clicked(bool)),this,SLOT(ZSlotHelp()));

    //main.
    this->m_hLayoutMain=new QHBoxLayout;
    this->m_hLayoutMain->addLayout(this->m_vLayoutBtn);
    this->m_hLayoutMain->addWidget(this->m_treeWidget);
    this->m_hLayoutMain->setSpacing(10);
    this->setLayout(this->m_hLayoutMain);

    //list all roles and users.
    ZListRoleUserInfoDia *dia=new ZListRoleUserInfoDia(this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteListOp();
    dia->ZShowWaitingDialog();
}
PUserManagerWin::~PUserManagerWin()
{
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_AddGrp)
    {
        delete this->m_btnAddGrp;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_MdyGrp)
    {
        delete this->m_btnMdyGrp;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_DelGrp)
    {
        delete this->m_btnDelGrp;
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_AddUser)
    {
        delete this->m_btnAddUser;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_MdyUser)
    {
        delete this->m_btnMdyUser;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_DelUser)
    {
        delete this->m_btnDelUser;
    }

    delete this->m_btnExpand;
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_Import)
    {
        delete this->m_btnImport;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_Export)
    {
        delete this->m_btnExport;
    }
    delete this->m_btnHelp;
    delete this->m_vLayoutBtn;

    delete this->m_treeWidget;
    delete this->m_hLayoutMain;
}
void PUserManagerWin::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{
    if(item=="role")
    {
        if(cmd=="add")
        {
            if(ackNetRetCode<0)
            {
                QString roleName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("add role [%1] failed:[%2].").arg(roleName).arg(errMsg));
            }else{
                QString roleName=paraList.at(0);
                QString permBits=paraList.at(1);
                QString roleMemo=paraList.at(2);
                QString creator=paraList.at(3);
                QString createTime=paraList.at(4);
                QTreeWidgetItem *roleItem=new QTreeWidgetItem(0);//type=0 is role.type=1 is user.
                roleItem->setIcon(0,QIcon(":/UserManager/images/UserManager/MdyGrp.png"));
                roleItem->setText(0,roleName);
                roleItem->setText(4,creator);
                roleItem->setIcon(5,QIcon(":/common/images/common/Calendar.png"));
                roleItem->setText(5,createTime);
                this->m_treeWidget->addTopLevelItem(roleItem);
                this->m_treeWidget->setCurrentItem(roleItem);
                //save role private data in roleMap.
                if(!this->m_roleMap.contains(roleName))
                {
                    RolePrivateData rolePriData;
                    rolePriData.permBits=permBits;
                    rolePriData.roleMemo=roleMemo;
                    this->m_roleMap.insert(roleName,rolePriData);
                }
                this->ZAddLogMsg(tr("add role [%1] success.").arg(roleName));
            }
        }else if(cmd=="mdy")
        {
            if(ackNetRetCode<0)
            {
                QString roleName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("modify role [%1] failed:[%2].").arg(roleName).arg(errMsg));
            }else{
                QString roleName=paraList.at(0);
                QString permBits=paraList.at(1);
                QString roleMemo=paraList.at(2);
                QString creator=paraList.at(3);
                //update role private data in roleMap.
                this->m_roleMap.remove(roleName);
                RolePrivateData priData;
                priData.permBits=permBits;
                priData.roleMemo=roleMemo;
                this->m_roleMap.insert(roleName,priData);
                this->ZAddLogMsg(tr("modify role [%1] success.").arg(roleName));
            }
        }else if(cmd=="del")
        {
            if(ackNetRetCode<0)
            {
                QString roleName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("delete role [%1] failed:[%2].").arg(roleName).arg(errMsg));
            }else{
                QString roleName=paraList.at(0);
                //remove role from roleMap.
                this->m_roleMap.remove(roleName);
                //delete roleItem from treeWidget.
                for(qint32 i=0;i<this->m_treeWidget->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *roleItem=this->m_treeWidget->topLevelItem(i);
                    if(roleItem->type()==0 && roleItem->text(0)==roleName)
                    {
                        this->m_treeWidget->takeTopLevelItem(i);
                        delete roleItem;
                        roleItem=NULL;
                    }
                }
                this->ZAddLogMsg(tr("delete role [%1] success.").arg(roleName));
            }
        }else if(cmd=="list")
        {
            QString roleName=paraList.at(0);
            QString permBits=paraList.at(1);
            QString roleMemo=paraList.at(2);
            QString creator=paraList.at(3);
            QString createTime=paraList.at(4);

            QTreeWidgetItem *roleItem=new QTreeWidgetItem(0);//type=0 is role.type=1 is user.
            roleItem->setIcon(0,QIcon(":/UserManager/images/UserManager/MdyGrp.png"));
            roleItem->setText(0,roleName);
            roleItem->setText(4,creator);
            roleItem->setText(5,createTime);
            roleItem->setIcon(5,QIcon(":/common/images/common/Calendar.png"));
            this->m_treeWidget->addTopLevelItem(roleItem);
            this->m_treeWidget->setCurrentItem(roleItem);
            //save role private data in roleMap.
            if(!this->m_roleMap.contains(roleName))
            {
                RolePrivateData rolePriData;
                rolePriData.permBits=permBits;
                rolePriData.roleMemo=roleMemo;
                this->m_roleMap.insert(roleName,rolePriData);
            }
            this->ZAddLogMsg(tr("list role [%1] success.").arg(roleName));
        }
    }else if(item=="user")
    {
        if(cmd=="add")
        {
            if(ackNetRetCode<0)
            {
                QString userName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("add user [%1] failed:[%2].").arg(userName).arg(errMsg));
            }else{
                QString userName=paraList.at(0);
                QString realName=paraList.at(1);
                QString roleName=paraList.at(2);
                QString sex=paraList.at(3);
                QString mobile=paraList.at(4);
                QString password=paraList.at(5);
                QString creator=paraList.at(6);
                QString createTime=paraList.at(7);

                QTreeWidgetItem *userItem=new QTreeWidgetItem(1);//type=0 is role.type=1 is user.
                userItem->setIcon(0,QIcon(":/UserManager/images/UserManager/MdyUser.png"));
                userItem->setText(0,userName);
                userItem->setText(1,realName);
                if(sex=="female")
                {
                    userItem->setIcon(2,QIcon(":/UserManager/images/UserManager/female.png"));
                }else if(sex=="male")
                {
                    userItem->setIcon(2,QIcon(":/UserManager/images/UserManager/male.png"));
                }
                userItem->setText(2,sex);
                userItem->setIcon(3,QIcon(":/UserManager/images/UserManager/mobile.png"));
                userItem->setText(3,mobile);
                userItem->setText(4,creator);
                userItem->setIcon(5,QIcon(":/common/images/common/Calendar.png"));
                userItem->setText(5,createTime);
                //add userItem to specify roleItem.
                for(qint32 i=0;i<this->m_treeWidget->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *roleItem=this->m_treeWidget->topLevelItem(i);
                    if(roleItem->text(0)==roleName)
                    {
                        roleItem->addChild(userItem);
                        this->m_treeWidget->setCurrentItem(userItem);
                        break;
                    }
                }
                this->ZAddLogMsg(tr("add user [%1] to role [%2] success.").arg(userName).arg(roleName));
            }
        }else if(cmd=="mdy")
        {
            if(ackNetRetCode<0)
            {
                QString userName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("modify user [%1] failed:[%2].").arg(userName).arg(errMsg));
            }else{
                QString userName=paraList.at(0);
                QString realName=paraList.at(1);
                QString roleName=paraList.at(2);
                QString sex=paraList.at(3);
                QString mobile=paraList.at(4);
                QString password=paraList.at(5);
                QString creator=paraList.at(6);

                //find userItem and change its value.
                QTreeWidgetItem *userItem=new QTreeWidgetItem(1);//type=0 is role.type=1 is user.
                userItem->setText(0,userName);
                userItem->setText(1,realName);
                userItem->setText(2,sex);
                userItem->setText(3,mobile);
                userItem->setText(4,creator);
                for(qint32 i=0;i<this->m_treeWidget->topLevelItemCount();i++)
                {
                    bool bUpdateOk=false;
                    QTreeWidgetItem *roleItem=this->m_treeWidget->topLevelItem(i);
                    if(roleItem->text(0)==roleName)
                    {
                        for(qint32 j=0;j<roleItem->childCount();j++)
                        {
                            QTreeWidgetItem *userItem=roleItem->child(j);
                            if(userItem->text(0)==userName)
                            {
                                userItem->setText(1,realName);
                                userItem->setText(2,sex);
                                userItem->setText(3,mobile);
                                userItem->setText(4,creator);
                                bUpdateOk=true;
                                break;
                            }
                        }
                    }
                    if(bUpdateOk)
                    {
                        break;
                    }
                }
                this->ZAddLogMsg(tr("modify user [%1] success.").arg(userName));
            }
        }else if(cmd=="del")
        {
            if(ackNetRetCode<0)
            {
                QString userName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("delete user [%1] failed:[%2].").arg(userName).arg(errMsg));
            }else{
                QString userName=paraList.at(0);
                QString roleName=paraList.at(1);

                //delete userItem form roleItem.
                for(qint32 i=0;i<this->m_treeWidget->topLevelItemCount();i++)
                {
                    bool bDeleteOk=false;
                    QTreeWidgetItem *roleItem=this->m_treeWidget->topLevelItem(i);
                    if(roleItem->text(0)==roleName)
                    {
                        for(qint32 j=0;j<roleItem->childCount();j++)
                        {
                            QTreeWidgetItem *userItem=roleItem->child(j);
                            if(userItem->text(0)==userName)
                            {
                                roleItem->removeChild(userItem);
                                delete userItem;
                                userItem=NULL;
                                bDeleteOk=true;
                                break;
                            }
                        }
                    }
                    if(bDeleteOk)
                    {
                        break;
                    }
                }
                this->ZAddLogMsg(tr("delete user [%1] success.").arg(userName));
            }
        }else if(cmd=="list")
        {
            QString userName=paraList.at(0);
            QString roleName=paraList.at(1);
            QString realName=paraList.at(2);
            QString sex=paraList.at(3);
            QString mobile=paraList.at(4);
            QString creator=paraList.at(5);
            QString createTime=paraList.at(6);
            QString lastLoginTime=paraList.at(7);
            QTreeWidgetItem *userItem=new QTreeWidgetItem(1);//type=0 is role.type=1 is user.
            userItem->setIcon(0,QIcon(":/UserManager/images/UserManager/MdyUser.png"));
            userItem->setText(0,userName);
            userItem->setText(1,realName);
            if(sex=="female")
            {
                userItem->setIcon(2,QIcon(":/UserManager/images/UserManager/female.png"));
            }else if(sex=="male")
            {
                userItem->setIcon(2,QIcon(":/UserManager/images/UserManager/male.png"));
            }
            userItem->setText(2,sex);
            userItem->setIcon(3,QIcon(":/UserManager/images/UserManager/mobile.png"));
            userItem->setText(3,mobile);
            userItem->setText(4,creator);
            userItem->setText(5,createTime);
            userItem->setIcon(5,QIcon(":/common/images/common/Calendar.png"));
            userItem->setText(6,lastLoginTime);
            //add userItem to specify roleItem.
            for(qint32 i=0;i<this->m_treeWidget->topLevelItemCount();i++)
            {
                QTreeWidgetItem *roleItem=this->m_treeWidget->topLevelItem(i);
                if(roleItem->text(0)==roleName)
                {
                    roleItem->addChild(userItem);
                    this->m_treeWidget->setCurrentItem(userItem);
                    break;
                }
            }
            for(qint32 i=0;i<this->m_treeWidget->columnCount();i++)
            {
                this->m_treeWidget->resizeColumnToContents(i);
            }
        }
    }
}
void PUserManagerWin::ZSlotAddGrp()
{
    ZGrpInfoDia *dia=new ZGrpInfoDia(ZGrpInfoDia::Type_NewGrp,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PUserManagerWin::ZSlotMdyGrp()
{
    QTreeWidgetItem *grpItem=this->m_treeWidget->currentItem();
    if(grpItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择一个角色再执行编辑操作!"));
        return;
    }
    if(grpItem->type()!=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请选择角色进行编辑!\n当前选择为非角色!"));
        return;
    }
    //get role private data from roleMap.
    RolePrivateData rdata=this->m_roleMap.value(grpItem->text(0));
    ZGrpInfoDia *dia=new ZGrpInfoDia(ZGrpInfoDia::Type_MdyGrp,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetGrpName(grpItem->text(0));
    dia->ZSetPermBits(rdata.permBits);
    dia->ZSetGrpMemo(rdata.roleMemo);
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PUserManagerWin::ZSlotDelGrp()
{
    QTreeWidgetItem *tItem=this->m_treeWidget->currentItem();
    if(tItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择一个角色再执行删除操作!"));
        return;
    }
    if(tItem->type()!=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请选择角色进行删除!\n当前选择为非角色!"));
        return;
    }
    if(tItem->childCount()!=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("当前选择角色下包含用户,不可删除!\n请先删除掉该角色下的所有用户,再删除角色!\n包含用户数目:%1").arg(tItem->childCount()));
        return;
    }
    RolePrivateData rdata=this->m_roleMap.value(tItem->text(0));
    ZGrpInfoDia *dia=new ZGrpInfoDia(ZGrpInfoDia::Type_DelGrp,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetGrpName(tItem->text(0));
    dia->ZSetPermBits(rdata.permBits);
    dia->ZSetGrpMemo(rdata.roleMemo);
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PUserManagerWin::ZSlotAddUser()
{
    QTreeWidgetItem *tGrpItem=this->m_treeWidget->currentItem();
    if(tGrpItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择要在哪个角色下添加用户!"));
        return;
    }
    if(tGrpItem->type()!=0)
    {
        tGrpItem=tGrpItem->parent();
    }

    ZUserInfoDia *dia=new ZUserInfoDia(ZUserInfoDia::Type_NewUser,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetRoleName(tGrpItem->text(0));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PUserManagerWin::ZSlotMdyUser()
{
    QTreeWidgetItem *userItem=this->m_treeWidget->currentItem();
    if(userItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择一个用户再执行编辑操作!"));
        return;
    }
    if(userItem->type()!=1)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("您选择的不是用户!\n无法编辑!"));
        return;
    }

    ZUserInfoDia *dia=new ZUserInfoDia(ZUserInfoDia::Type_MdyUser,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetUserName(userItem->text(0));
    dia->ZSetRealName(userItem->text(1));
    dia->ZSetRoleName(userItem->parent()->text(0));
    dia->ZSetSex(userItem->text(2)==tr("男")?1:0);
    dia->ZSetMobile(userItem->text(3));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PUserManagerWin::ZSlotDelUser()
{
    QTreeWidgetItem *userItem=this->m_treeWidget->currentItem();
    if(userItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择一个用户再执行删除操作!"));
        return;
    }
    if(userItem->type()!=1)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("当前选择的不是用户!"));
        return;
    }
    if(QMessageBox::question(this,tr("操作确认"),tr("您确认要删除用户[%1]吗?").arg(userItem->text(0)),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        ZUserInfoDia *dia=new ZUserInfoDia(ZUserInfoDia::Type_DelUser,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetUserName(userItem->text(0));
        dia->ZSetRealName(userItem->text(1));
        dia->ZSetRoleName(userItem->parent()->text(0));
        dia->ZSetSex(userItem->text(2)==tr("男")?1:0);
        dia->ZSetMobile(userItem->text(3));
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
void PUserManagerWin::ZSlotExpand()
{
    this->m_treeWidget->expandAll();
}
void PUserManagerWin::ZSlotImport()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Import User List"),".",tr("xml(*.xml)"));
    if(fileName.isEmpty())
    {
        return;
    }
    QFile xmlFile(fileName);
    if(!xmlFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,tr("错误提示"),tr("打开文件失败!"));
        return;
    }
    QString xmlData(xmlFile.readAll());
    xmlFile.close();
    if(xmlData.isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("文件为空!"));
        return;
    }

    QList<ZRoleInfo> roleList;
    QList<ZUserInfo> userList;
    QXmlStreamReader tXmlReader(xmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Role"))
            {
                QXmlStreamAttributes tRoleAttr=tXmlReader.attributes();
                QString tPermBits=tRoleAttr.value(QString("perm")).toString();
                QString tRoleMemo=tRoleAttr.value(QString("memo")).toString();
                QString tRoleName=tXmlReader.readElementText();
                //check if list already has this memo.
                if(!this->m_roleMap.contains(tRoleName))
                {
                    RolePrivateData rdata;
                    rdata.permBits=tPermBits;
                    rdata.roleMemo=tRoleMemo;
                    this->m_roleMap.insert(tRoleName,rdata);

                    //add role to role list.
                    ZRoleInfo newRole;
                    newRole.m_roleName=tRoleName;
                    QStringList permBitsList=tPermBits.split(",");
                    if(permBitsList.count()==6)
                    {
                        newRole.m_userManagerPerm=permBitsList.at(0).toInt();
                        newRole.m_templateEditPerm=permBitsList.at(1).toInt();
                        newRole.m_fileManagerPerm=permBitsList.at(2).toInt();
                        newRole.m_processEditPerm=permBitsList.at(3).toInt();
                        newRole.m_taskManagerPerm=permBitsList.at(4).toInt();
                        newRole.m_formDesignerPerm=permBitsList.at(5).toInt();
                    }else{
                        newRole.m_userManagerPerm=0;
                        newRole.m_templateEditPerm=0;
                        newRole.m_fileManagerPerm=0;
                        newRole.m_processEditPerm=0;
                        newRole.m_taskManagerPerm=0;
                        newRole.m_formDesignerPerm=0;
                        this->ZAddLogMsg(tr("Error permission bits,set to 0."));
                    }
                    newRole.m_roleMemo=tRoleMemo;
                    roleList.append(newRole);
                }
            }
            if(nodeName==QString("User"))
            {
                QXmlStreamAttributes tColAttr=tXmlReader.attributes();
                QString roleName=tColAttr.value(QString("roleName")).toString();
                QString realName=tColAttr.value(QString("realName")).toString();
                QString sex=tColAttr.value(QString("sex")).toString();
                QString mobile=tColAttr.value(QString("mobile")).toString();
                QString creator=tColAttr.value(QString("creator")).toString();
                QString createTime=tColAttr.value(QString("createTime")).toString();
                QString tUserName=tXmlReader.readElementText();
                ZUserInfo newUser;
                newUser.m_userName=tUserName;
                newUser.m_roleName=roleName;
                newUser.m_realName=realName;
                newUser.m_sex=sex;
                newUser.m_password="123456";
                newUser.m_mobile=mobile;
                newUser.m_Creator=creator;
                userList.append(newUser);
            }
        }
    }
    ZImportRoleUserInfoDia *dia=new ZImportRoleUserInfoDia(this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteImportOp(roleList,userList);
    dia->ZShowWaitingDialog();
}
void PUserManagerWin::ZSlotExport()
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("Export User List"),".",tr("Xml(*.xml)"));
    if(fileName.isEmpty())
    {
        return;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,tr("错误提示"),tr("打开文件失败!"));
        return;
    }
    qint32 nRoleCnt=0;
    qint32 nUserCnt=0;
    QString tFormatXml;
    QXmlStreamWriter  tXmlWriter(&tFormatXml);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("PMSUser"));
    //export <Role></Role>.
    for(int i=0;i<this->m_treeWidget->topLevelItemCount();i++)
    {
        QTreeWidgetItem *roleItem=this->m_treeWidget->topLevelItem(i);
        tXmlWriter.writeStartElement(QString("Role"));
        if(this->m_roleMap.contains(roleItem->text(0)))
        {
            QMap<QString,RolePrivateData>::iterator it=this->m_roleMap.find(roleItem->text(0));
            tXmlWriter.writeAttribute(QString("perm"),QString("%1").arg(it.value().permBits));
            tXmlWriter.writeAttribute(QString("memo"),it.value().roleMemo);
        }
        tXmlWriter.writeCharacters(roleItem->text(0));
        tXmlWriter.writeEndElement();//Role.
        nRoleCnt++;
    }
    //export <User></User>
    for(int i=0;i<this->m_treeWidget->topLevelItemCount();i++)
    {
        QTreeWidgetItem *roleItem=this->m_treeWidget->topLevelItem(i);
        for(qint32 j=0;j<roleItem->childCount();j++)
        {
            QTreeWidgetItem *userItem=roleItem->child(j);
            tXmlWriter.writeStartElement(QString("User"));
            tXmlWriter.writeAttribute(QString("roleName"),roleItem->text(0));
            tXmlWriter.writeAttribute(QString("realName"),userItem->text(1));
            tXmlWriter.writeAttribute(QString("sex"),userItem->text(2));
            tXmlWriter.writeAttribute(QString("mobile"),userItem->text(3));
            tXmlWriter.writeAttribute(QString("creator"),userItem->text(4));
            tXmlWriter.writeAttribute(QString("createTime"),userItem->text(5));
            tXmlWriter.writeCharacters(userItem->text(0));
            tXmlWriter.writeEndElement();//User.
            nUserCnt++;
        }
    }
    tXmlWriter.writeEndElement();//PMSUser
    tXmlWriter.writeEndDocument();
    file.write(tFormatXml.toUtf8());
    file.close();
    this->ZAddLogMsg(tr("export user list success,[%1] records in total.").arg(nUserCnt));
    QMessageBox::information(this,tr("操作提示"),tr("导出用户成功,总计[%1]个权限组,[%2]个用户!").arg(nRoleCnt).arg(nUserCnt));
}
void PUserManagerWin::ZSlotHelp()
{

}
void PUserManagerWin::closeEvent(QCloseEvent *event)
{
    emit this->ZSignalCloseEvent("UserManager");
    QFrame::closeEvent(event);
}
void PUserManagerWin::ZAddLogMsg(QString logMsg)
{
    emit this->ZSignalLogMsg(QString("<UserManager>:")+logMsg);
}
void PUserManagerWin::ZSlotTreeDblClicked(QModelIndex index)
{
    QTreeWidgetItem *item=this->m_treeWidget->currentItem();
    if(item->type()==0)
    {
        //get role private data from roleMap.
        RolePrivateData rdata=this->m_roleMap.value(item->text(0));
        ZGrpInfoDia *dia=new ZGrpInfoDia(ZGrpInfoDia::Type_MdyGrp,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetGrpName(item->text(0));
        dia->ZSetPermBits(rdata.permBits);
        dia->ZSetGrpMemo(rdata.roleMemo);
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }else if(item->type()==1)
    {
        ZUserInfoDia *dia=new ZUserInfoDia(ZUserInfoDia::Type_MdyUser,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetUserName(item->text(0));
        dia->ZSetRealName(item->text(1));
        dia->ZSetRoleName(item->parent()->text(0));
        dia->ZSetSex(item->text(2)==tr("male")?1:0);
        dia->ZSetMobile(item->text(3));
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
