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
#include <QAction>
#include <QMenu>
#include "NetProtocol/pnetframe.h"
#include "pwaitingdia.h"
#include <QDebug>
#include <KDReports/KDReports.h>
#include <QtXlsx/QtXlsx>
#include <QInputDialog>
PUserManagerWin::PUserManagerWin()
{
    this->setWindowTitle(tr("用户管理器-User Manager"));
    this->setWindowIcon(QIcon(":/TaskBar/images/UserManager.png"));

    this->setStyleSheet("QToolButton{background-color:#cce5f9;border:none;font:color #eaf7ff;}"
                        "QToolButton::hover{background-color:#eaf7ff;}"
                        "");
    //right.
    this->m_tbTurnPage[0]=new QToolButton;
    this->m_tbTurnPage[0]->setText(tr("<<"));
    this->m_tbTurnPage[0]->setToolTip(tr("第一页"));

    this->m_tbTurnPage[1]=new QToolButton;
    this->m_tbTurnPage[1]->setText(tr("<"));
    this->m_tbTurnPage[1]->setToolTip(tr("前一页"));

    this->m_tbTurnPage[2]=new QToolButton;
    this->m_tbTurnPage[2]->setText(tr(">"));
    this->m_tbTurnPage[2]->setToolTip(tr("后一页"));

    this->m_tbTurnPage[3]=new QToolButton;
    this->m_tbTurnPage[3]->setText(tr(">>"));
    this->m_tbTurnPage[3]->setToolTip(tr("最后一页"));

    this->m_llSummaryInfo=new QLabel;
    this->m_cbPage=new QComboBox;
    this->m_hLayoutRightTop=new QHBoxLayout;
    this->m_hLayoutRightTop->addStretch(1);
    this->m_hLayoutRightTop->addWidget(this->m_llSummaryInfo);
    this->m_hLayoutRightTop->addStretch(1);
    this->m_hLayoutRightTop->addWidget(this->m_tbTurnPage[0]);
    this->m_hLayoutRightTop->addWidget(this->m_tbTurnPage[1]);
    this->m_hLayoutRightTop->addWidget(this->m_cbPage);
    this->m_hLayoutRightTop->addWidget(this->m_tbTurnPage[2]);
    this->m_hLayoutRightTop->addWidget(this->m_tbTurnPage[3]);

    this->m_treeWidget=new QTreeWidget;
    this->m_treeWidget->setIconSize(QSize(24,24));
    this->m_treeWidget->setColumnCount(7);
    this->m_treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this->m_treeWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ZSlotPopupMenu(QPoint)));
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

    this->m_vLayoutRight=new QVBoxLayout;
    this->m_vLayoutRight->addWidget(this->m_treeWidget);
    this->m_vLayoutRight->addLayout(this->m_hLayoutRightTop);


    //left.
    this->m_vLayoutBtn=new QVBoxLayout;

    this->m_btnGrpOp=new QToolButton;
    this->m_btnGrpOp->setToolTip(tr("角色管理"));
    this->m_btnGrpOp->setText(tr("角色"));
    this->m_btnGrpOp->setIcon(QIcon(":/UserManager/images/UserManager/AddGrp.png"));
    this->m_btnGrpOp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnGrpOp->setPopupMode(QToolButton::InstantPopup);
    this->m_menuGrp=new QMenu;
    this->m_btnGrpOp->setMenu(this->m_menuGrp);
    this->m_vLayoutBtn->addWidget(this->m_btnGrpOp);
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_AddGrp)
    {
        this->m_actAddGrp=new QAction(QIcon(":/UserManager/images/UserManager/AddGrp.png"),tr("创建角色"));
        this->m_menuGrp->addAction(this->m_actAddGrp);
        connect(this->m_actAddGrp,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddGrp()));
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_MdyGrp)
    {
        this->m_actMdyGrp=new QAction(QIcon(":/UserManager/images/UserManager/MdyGrp.png"),tr("编辑角色"));
        this->m_menuGrp->addAction(this->m_actMdyGrp);
        connect(this->m_actMdyGrp,SIGNAL(triggered(bool)),this,SLOT(ZSlotMdyGrp()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_DelGrp)
    {
        this->m_actDelGrp=new QAction(QIcon(":/UserManager/images/UserManager/DelGrp.png"),tr("删除角色"));
        this->m_menuGrp->addAction(this->m_actDelGrp);
        connect(this->m_actDelGrp,SIGNAL(triggered(bool)),this,SLOT(ZSlotDelGrp()));
    }

    this->m_btnUsrOp=new QToolButton;
    this->m_btnUsrOp->setToolTip(tr("用户管理"));
    this->m_btnUsrOp->setText(tr("用户"));
    this->m_btnUsrOp->setIcon(QIcon(":/UserManager/images/UserManager/AddUser.png"));
    this->m_btnUsrOp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnUsrOp->setPopupMode(QToolButton::InstantPopup);
    this->m_menuUsr=new QMenu;
    this->m_btnUsrOp->setMenu(this->m_menuUsr);
    this->m_vLayoutBtn->addWidget(this->m_btnUsrOp);

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_AddUser)
    {
        this->m_actAddUser=new QAction(QIcon(":/UserManager/images/UserManager/AddUser.png"),tr("创建用户"));
        this->m_menuUsr->addAction(this->m_actAddUser);
        connect(this->m_actAddUser,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddUser()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_MdyUser)
    {
        this->m_actMdyUser=new QAction(QIcon(":/UserManager/images/UserManager/MdyUser.png"),tr("编辑用户"));
        this->m_menuUsr->addAction(this->m_actMdyUser);
        connect(this->m_actMdyUser,SIGNAL(triggered(bool)),this,SLOT(ZSlotMdyUser()));
        connect(this->m_treeWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ZSlotTreeDblClicked(QModelIndex)));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_DelUser)
    {
        this->m_actDelUser=new QAction(QIcon(":/UserManager/images/UserManager/DelUser.png"),tr("删除用户"));
        this->m_menuUsr->addAction(this->m_actDelUser);
        connect(this->m_actDelUser,SIGNAL(triggered(bool)),this,SLOT(ZSlotDelUser()));
    }


    this->m_btnDisplay=new QToolButton;
    this->m_btnDisplay->setToolTip(tr("显示功能"));
    this->m_btnDisplay->setText(tr("显示"));
    this->m_btnDisplay->setIcon(QIcon(":/common/images/common/Display.png"));
    this->m_btnDisplay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnDisplay->setPopupMode(QToolButton::InstantPopup);
    this->m_menuDisplay=new QMenu;
    this->m_btnDisplay->setMenu(this->m_menuDisplay);

    this->m_actExpand=new QAction(QIcon(":/UserManager/images/UserManager/Expand.png"),tr("展开列表"));
    this->m_menuDisplay->addAction(this->m_actExpand);
    connect(this->m_actExpand,SIGNAL(triggered(bool)),this,SLOT(ZSlotExpand()));

    this->m_actDetch=new QAction(QIcon(":/common/images/common/Detach.png"),tr("分离"));
    this->m_menuDisplay->addAction(this->m_actDetch);
    connect(this->m_actDetch,SIGNAL(triggered(bool)),this,SLOT(ZSlotAatchDetch()));

    this->m_actAatch=new QAction(QIcon(":/common/images/common/Attach.png"),tr("附属"));
    this->m_menuDisplay->addAction(this->m_actAatch);
    connect(this->m_actAatch,SIGNAL(triggered(bool)),this,SLOT(ZSlotAatchDetch()));

    this->m_vLayoutBtn->addStretch(1);
    this->m_vLayoutBtn->addWidget(this->m_btnDisplay);

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_Import)
    {
        this->m_btnImport=new QToolButton;
        this->m_btnImport->setToolTip(tr("导入..."));
        this->m_btnImport->setText(tr("导入"));
        this->m_btnImport->setIcon(QIcon(":/UserManager/images/UserManager/Import.png"));
        this->m_btnImport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        this->m_menuImport=new QMenu;
        this->m_actImportXML=new QAction(QIcon(":/UserManager/images/UserManager/XML.png"),tr("导入XML..."));
        this->m_actImportExcel=new QAction(QIcon(":/UserManager/images/UserManager/Excel.png"),tr("导入Excel..."));
        this->m_menuImport->addAction(this->m_actImportXML);
        this->m_menuImport->addAction(this->m_actImportExcel);
        this->m_btnImport->setMenu(this->m_menuImport);
        this->m_btnImport->setPopupMode(QToolButton::InstantPopup);

        connect(this->m_actImportXML,SIGNAL(triggered(bool)),this,SLOT(ZSlotImportXML()));
        connect(this->m_actImportExcel,SIGNAL(triggered(bool)),this,SLOT(ZSlotImportExcel()));

        this->m_vLayoutBtn->addWidget(this->m_btnImport);
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_Export)
    {
        this->m_btnExport=new QToolButton;
        this->m_btnExport->setToolTip(tr("导出..."));
        this->m_btnExport->setText(tr("导出"));
        this->m_btnExport->setIcon(QIcon(":/UserManager/images/UserManager/Export.png"));
        this->m_btnExport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        this->m_menuExport=new QMenu;
        this->m_actExportXML=new QAction(QIcon(":/UserManager/images/UserManager/XML.png"),tr("导出XML..."));
        this->m_actExportExcel=new QAction(QIcon(":/UserManager/images/UserManager/Excel.png"),tr("导出Excel..."));
        this->m_menuExport->addAction(this->m_actExportXML);
        this->m_menuExport->addAction(this->m_actExportExcel);
        this->m_btnExport->setMenu(this->m_menuExport);
        this->m_btnExport->setPopupMode(QToolButton::InstantPopup);

        connect(this->m_actExportXML,SIGNAL(triggered(bool)),this,SLOT(ZSlotExportXML()));
        connect(this->m_actExportExcel,SIGNAL(triggered(bool)),this,SLOT(ZSlotExportExcel()));

        this->m_vLayoutBtn->addWidget(this->m_btnExport);
    }

    //print.
    this->m_btnPrint=new QToolButton;
    this->m_btnPrint->setToolTip(tr("打印用户列表"));
    this->m_btnPrint->setText(tr("打印"));
    this->m_btnPrint->setIcon(QIcon(":/common/images/common/print.png"));
    this->m_btnPrint->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_vLayoutBtn->addWidget(this->m_btnPrint);
    connect(this->m_btnPrint,SIGNAL(clicked(bool)),this,SLOT(ZSlotPrint()));

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
    this->m_hLayoutMain->addLayout(this->m_vLayoutRight);
    this->m_hLayoutMain->setSpacing(2);
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
        delete this->m_actAddGrp;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_MdyGrp)
    {
        delete this->m_actMdyGrp;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_DelGrp)
    {
        delete this->m_actDelGrp;
    }
    delete this->m_menuGrp;
    delete this->m_btnGrpOp;

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_AddUser)
    {
        delete this->m_actAddUser;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_MdyUser)
    {
        delete this->m_actMdyUser;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_DelUser)
    {
        delete this->m_actDelUser;
    }
    delete this->m_menuUsr;
    delete this->m_btnUsrOp;

    delete this->m_actExpand;
    delete this->m_actAatch;
    delete this->m_actDetch;
    delete this->m_menuDisplay;
    delete this->m_btnDisplay;
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_Import)
    {
        delete this->m_actImportExcel;
        delete this->m_actImportXML;
        delete this->m_menuImport;
        delete this->m_btnImport;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm&PermBits_UserManager_Export)
    {
        delete this->m_actExportExcel;
        delete this->m_actExportXML;
        delete this->m_menuExport;
        delete this->m_btnExport;
    }
    delete this->m_btnPrint;
    delete this->m_btnHelp;
    delete this->m_vLayoutBtn;

    delete this->m_llSummaryInfo;
    delete this->m_tbTurnPage[0];
    delete this->m_tbTurnPage[1];
    delete this->m_tbTurnPage[2];
    delete this->m_tbTurnPage[3];
    delete this->m_cbPage;
    delete this->m_hLayoutRightTop;
    delete this->m_treeWidget;
    delete this->m_vLayoutRight;
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
            //update the summary info.
            this->ZUpdateGrpUserInfo();
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
                //update the summary info.
                this->ZUpdateGrpUserInfo();
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
            //update the summary info.
            this->ZUpdateGrpUserInfo();
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
                //update the summary info.
                this->ZUpdateGrpUserInfo();
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
                //update the summary info.
                this->ZUpdateGrpUserInfo();
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
            //update the summary info.
            this->ZUpdateGrpUserInfo();
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
void PUserManagerWin::ZSlotImportXML()
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
void PUserManagerWin::ZSlotImportExcel()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("从Excel导入用户列表"),".",tr("Microsoft Excel(*.xlsx)"));
    if(fileName.isEmpty())
    {
        return;
    }
    QFile xlsxFile(fileName);
    if(!xlsxFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,tr("错误提示"),tr("打开文件失败!"));
        return;
    }
    xlsxFile.close();

    QXlsx::Document xlsx(fileName);
    qint32 nTotalRow=xlsx.read(1,2).toInt();
    if(nTotalRow<=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("读取总行数出错!"));
        return;
    }else if(nTotalRow>1000)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("单次最大支持1000条记录!"));
        return;
    }
    //read user data.
    QList<ZRoleInfo> roleList;
    QList<ZUserInfo> userList;
    qint32 nRowIndex=3;
    for(qint32 i=0;i<nTotalRow;i++)
    {
        ZUserInfo newUser;
        newUser.m_userName=xlsx.read(nRowIndex,1).toString();
        newUser.m_realName=xlsx.read(nRowIndex,2).toString();
        newUser.m_sex=xlsx.read(nRowIndex,3).toString();
        newUser.m_mobile=xlsx.read(nRowIndex,4).toString();
        newUser.m_Creator=xlsx.read(nRowIndex,5).toString();
        QString roleName=xlsx.read(nRowIndex,8).toString();
        newUser.m_roleName=roleName;
        newUser.m_password="123456";
        userList.append(newUser);

        //add role to list.
        bool bExist=false;
        for(qint32 k=0;k<roleList.size();k++)
        {
            if(roleList.at(k).m_roleName==roleName)
            {
                bExist=true;
                break;
            }
        }
        if(!bExist)
        {
            ZRoleInfo newRole;
            newRole.m_roleName=roleName;
            newRole.m_userManagerPerm=0;
            newRole.m_templateEditPerm=0;
            newRole.m_fileManagerPerm=0;
            newRole.m_processEditPerm=0;
            newRole.m_taskManagerPerm=0;
            newRole.m_formDesignerPerm=0;
            newRole.m_roleMemo="";
            roleList.append(newRole);
        }
        nRowIndex++;//next row.
    }

    ZImportRoleUserInfoDia *dia=new ZImportRoleUserInfoDia(this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteImportOp(roleList,userList);
    dia->ZShowWaitingDialog();
}
void PUserManagerWin::ZSlotExportXML()
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
void PUserManagerWin::ZSlotExportExcel()
{
    QString excelFileName="PMSUserList"+QDateTime::currentDateTime().toString("yyyyMMdd")+".xlsx";
    QString fileName=QFileDialog::getSaveFileName(this,tr("导出用户列表到Excel文件"),excelFileName,tr("Microsoft Excel(*.xlsx)"));
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
    //export to excel.
    qint32 nX=0,nY=0;
    //
    QXlsx::Document xlsx;
    QXlsx::Format fmt;
    fmt.setBorderStyle(QXlsx::Format::BorderThin);
    fmt.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    fmt.setVerticalAlignment(QXlsx::Format::AlignVCenter);

    //write count.
    xlsx.write(nX+1,nY+1,tr("总行数"),fmt);//总行数
    xlsx.write(nX+1,nY+2,tr("0"),fmt);//数量
    nX++;//next row.


    //write header.
    xlsx.write(nX+1,nY+1,tr("用户名"),fmt);//用户名
    xlsx.write(nX+1,nY+2,tr("真实姓名"),fmt);//真实姓名
    xlsx.write(nX+1,nY+3,tr("性别"),fmt);//性别
    xlsx.write(nX+1,nY+4,tr("手机号码"),fmt);//手机号码
    xlsx.write(nX+1,nY+5,tr("创建者"),fmt);//创建者
    xlsx.write(nX+1,nY+6,tr("创建时间"),fmt);//末次登录时间
    xlsx.write(nX+1,nY+7,tr("末次登录时间"),fmt);//末次登录时间
    xlsx.write(nX+1,nY+8,tr("所属组"),fmt);//所属组
    nX++;//next row.

    //total row counter.
    qint32 nRowCounter=0;

    //write data.
    for(qint32 i=0;i<this->m_treeWidget->topLevelItemCount();i++)
    {
        QTreeWidgetItem *grpItem=this->m_treeWidget->topLevelItem(i);
        for(qint32 j=0;j<grpItem->childCount();j++)
        {
            QTreeWidgetItem *userItem=grpItem->child(j);
            //because QTableWidget start from (0,0).
            //but Excel start from (1,1)
            //so here we add 1 to x&y.
            xlsx.write(nX+1,nY+1,userItem->text(0),fmt);//用户名
            xlsx.write(nX+1,nY+2,userItem->text(1),fmt);//真实姓名
            xlsx.write(nX+1,nY+3,userItem->text(2),fmt);//性别
            xlsx.write(nX+1,nY+4,userItem->text(3),fmt);//手机号码
            xlsx.write(nX+1,nY+5,userItem->text(4),fmt);//创建者
            xlsx.write(nX+1,nY+6,userItem->text(5),fmt);//创建时间
            xlsx.write(nX+1,nY+7,userItem->text(6),fmt);//末次登录时间
            xlsx.write(nX+1,nY+8,grpItem->text(0),fmt);//所属组
            nX++;//next row.
            nRowCounter++;//row counter.
        }
    }
    xlsx.write(1,2,QString::number(nRowCounter,10),fmt);//数量
    if(!xlsx.saveAs(fileName))
    {
        QMessageBox::information(this,tr("失败提示"),tr("用户列表导出Excel文件%1失败!").arg(fileName));
        return;
    }
    QMessageBox::information(this,tr("成功提示"),tr("用户列表导出Excel文件成功!\n%1").arg(fileName));
}
void PUserManagerWin::ZSlotPrint()
{
    KDReports::Report report;
    report.setMargins(2,2,2,2);
    report.setHeaderBodySpacing(2); // mm
    report.setFooterBodySpacing(2); // mm
    report.setWatermarkPixmap(QPixmap(":/LoginManager/images/LoginManager/Logo.png"));

    //set header.
    KDReports::Header &header=report.header();
    header.addElement(KDReports::TextElement(QObject::tr("用户列表清单")),Qt::AlignLeft);
    header.addElement(KDReports::TextElement("PMS流水线综合管控系统"),Qt::AlignHCenter);
    header.addElement(KDReports::TextElement("Page "),Qt::AlignRight);
    header.addVariable( KDReports::PageNumber );
    header.addInlineElement( KDReports::TextElement(" / "));
    header.addVariable( KDReports::PageCount );
    report.setHeaderLocation(KDReports::AllPages,&header);

    //the user table.
    KDReports::TableElement tableElement;
    tableElement.setHeaderRowCount(1);
    tableElement.setPadding(3);
    QColor headerColor("#DADADA");
    //序号,用户名,真实姓名,性别，手机号码，创建者，创建时间，末次登录时间,所属组
    qint32 nRow=0;
    // Merged header in row 0
    KDReports::Cell& topHeader = tableElement.cell(nRow,0);
    topHeader.setColumnSpan(9);
    topHeader.setBackground(headerColor);
    topHeader.addElement( KDReports::TextElement(tr("PMS系统用户列表清单")), Qt::AlignHCenter );
    nRow++;//next row.
    //the table header.
    for(qint32 i=0;i<9;i++)
    {
        KDReports::Cell& headerCell=tableElement.cell(nRow,i);
        headerCell.setBackground(headerColor);
        switch(i)
        {
        case 0:
            headerCell.addElement(KDReports::TextElement(tr("序号")),Qt::AlignHCenter);
            break;
        case 1:
            headerCell.addElement(KDReports::TextElement(tr("用户名")),Qt::AlignHCenter);
            break;
        case 2:
            headerCell.addElement(KDReports::TextElement(tr("真实姓名")),Qt::AlignHCenter);
            break;
        case 3:
            headerCell.addElement(KDReports::TextElement(tr("性别")),Qt::AlignHCenter);
            break;
        case 4:
            headerCell.addElement(KDReports::TextElement(tr("手机号码")),Qt::AlignHCenter);
            break;
        case 5:
            headerCell.addElement(KDReports::TextElement(tr("创建者")),Qt::AlignHCenter);
            break;
        case 6:
            headerCell.addElement(KDReports::TextElement(tr("创建时间")),Qt::AlignHCenter);
            break;
        case 7:
            headerCell.addElement(KDReports::TextElement(tr("末次登录时间")),Qt::AlignHCenter);
            break;
        case 8:
            headerCell.addElement(KDReports::TextElement(tr("所属组")),Qt::AlignHCenter);
            break;
        }
    }
    nRow++;//next row.

    qint32 nIndexNo=1;
    for(qint32 i=0;i<this->m_treeWidget->topLevelItemCount();i++)
    {
        QTreeWidgetItem *grpItem=this->m_treeWidget->topLevelItem(i);
        for(qint32 j=0;j<grpItem->childCount();j++)
        {
            QTreeWidgetItem *userItem=grpItem->child(j);
            tableElement.cell(nRow,0).addElement(KDReports::TextElement(QString::number(nIndexNo,10)),Qt::AlignHCenter);
            tableElement.cell(nRow,1).addElement(KDReports::TextElement(userItem->text(0)),Qt::AlignHCenter);
            tableElement.cell(nRow,2).addElement(KDReports::TextElement(userItem->text(1)),Qt::AlignHCenter);
            tableElement.cell(nRow,3).addElement(KDReports::TextElement(userItem->text(2)),Qt::AlignHCenter);
            tableElement.cell(nRow,4).addElement(KDReports::TextElement(userItem->text(3)),Qt::AlignHCenter);
            tableElement.cell(nRow,5).addElement(KDReports::TextElement(userItem->text(4)),Qt::AlignHCenter);
            tableElement.cell(nRow,6).addElement(KDReports::TextElement(userItem->text(5)),Qt::AlignHCenter);
            tableElement.cell(nRow,7).addElement(KDReports::TextElement(userItem->text(6)),Qt::AlignHCenter);
            tableElement.cell(nRow,8).addElement(KDReports::TextElement(grpItem->text(0)),Qt::AlignHCenter);
            nRow++;//next row.
            nIndexNo++;//next index.
        }
    }
    //    // Normal header in row 1

    //    // This would look better if centered vertically. This feature is only available since
    //    // Qt-4.3 though (QTextCharFormat::AlignMiddle)
    //    QPixmap systemPixmap( ":/LoginManager/images/LoginManager/User.png" );
    //    headerCell1.addElement( KDReports::ImageElement( systemPixmap ) );
    //    headerCell1.addInlineElement( KDReports::TextElement( " Item" ) );
    //    KDReports::Cell& headerCell2 = tableElement.cell( 1, 1 );
    //    headerCell2.setBackground( headerColor );
    //    KDReports::TextElement expected( "Expected" );
    //    expected.setItalic( true );
    //    expected.setBackground( QColor("#999999") ); // note that this background only applies to this element
    //    headerCell2.addElement( expected );
    //    headerCell2.addInlineElement( KDReports::TextElement( " shipping time" ) );

    //set footer.
    QString footerString;
    footerString+=QObject::tr("制表人:");
    footerString+=MyUserInfo::ZGetInstance()->m_UserInfo.m_realName;
    footerString+=QString("   ");
    footerString+=QObject::tr("制表日期:");
    footerString+=QDateTime::currentDateTime().toString("yyyy年MM月dd日 hh时mm分ss秒");

    KDReports::Footer &footer=report.footer();
    footer.addElement(KDReports::TextElement(footerString),Qt::AlignHCenter);
    report.setFooterLocation(KDReports::AllPages,&footer);

    report.addElement( tableElement );
    KDReports::PreviewDialog preview( &report );
    preview.exec();
}
void PUserManagerWin::ZSlotHelp()
{

}
void PUserManagerWin::closeEvent(QCloseEvent *event)
{
    emit this->ZSignalCloseEvent("UserManager");
    QFrame::closeEvent(event);
}
void PUserManagerWin::resizeEvent(QResizeEvent *event)
{
    for(qint32 i=0;i<this->m_treeWidget->columnCount();i++)
    {
        this->m_treeWidget->resizeColumnToContents(i);
    }
    QFrame::resizeEvent(event);
}
void PUserManagerWin::ZAddLogMsg(QString logMsg)
{
    emit this->ZSignalLogMsg(QString("<UserManager>:")+logMsg);
}
void PUserManagerWin::ZUpdateGrpUserInfo(void)
{
    qint32 nRoleNum=this->m_treeWidget->topLevelItemCount();
    qint32 nUserNum=0;
    for(qint32 i=0;i<this->m_treeWidget->topLevelItemCount();i++)
    {
        QTreeWidgetItem *grpItem=this->m_treeWidget->topLevelItem(i);
        nUserNum+=grpItem->childCount();
    }
    this->m_llSummaryInfo->setText(tr("共有%1个角色  共有%2个用户").arg(nRoleNum).arg(nUserNum));
    this->m_cbPage->clear();
    this->m_cbPage->addItem(tr("1/1"));
}
void PUserManagerWin::ZSlotTreeDblClicked(QModelIndex index)
{
    Q_UNUSED(index);
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
void PUserManagerWin::ZSlotPopupMenu(const QPoint &pt)
{
    Q_UNUSED(pt);
    QTreeWidgetItem *item=this->m_treeWidget->currentItem();
    if(NULL==item)
    {
        return;
    }
    QMenu popMenu(this->m_treeWidget);
    QAction actAddGrp(QIcon(":/UserManager/images/UserManager/AddGrp.png"),tr("创建组"));
    QAction actDelGrp(QIcon(":/UserManager/images/UserManager/DelGrp.png"),tr("删除组"));
    QAction actAddUser(QIcon(":/UserManager/images/UserManager/AddUser.png"),tr("创建用户"));
    QAction actDelUser(QIcon(":/UserManager/images/UserManager/DelUser.png"),tr("删除用户"));
    QAction actImport(QIcon(":/UserManager/images/UserManager/Import.png"),tr("导入..."));
    QAction actExport(QIcon(":/UserManager/images/UserManager/Export.png"),tr("导出..."));
    connect(&actAddGrp,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddGrp()));
    connect(&actDelGrp,SIGNAL(triggered(bool)),this,SLOT(ZSlotDelGrp()));
    connect(&actAddUser,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddUser()));
    connect(&actDelUser,SIGNAL(triggered(bool)),this,SLOT(ZSlotDelUser()));
    connect(&actImport,SIGNAL(triggered(bool)),this,SLOT(ZSlotImport()));
    connect(&actExport,SIGNAL(triggered(bool)),this,SLOT(ZSlotExport()));
    if(item->type()==0)//group.
    {
        popMenu.addAction(&actAddGrp);
        popMenu.addAction(&actDelGrp);
        popMenu.addSeparator();
    }else if(item->type()==1) //user.
    {
        popMenu.addAction(&actAddUser);
        popMenu.addAction(&actDelUser);
        popMenu.addSeparator();
    }
    popMenu.addAction(&actImport);
    popMenu.addAction(&actExport);
    popMenu.exec(QCursor::pos());
}
void PUserManagerWin::ZSlotAatchDetch()
{
    QAction *src=qobject_cast<QAction*>(this->sender());
    if(src)
    {
        if(src==this->m_actDetch)
        {
            emit this->ZSignalDetch("UserManager");
        }else if(src==this->m_actAatch)
        {
            emit this->ZSignalAatch("UserManager");
        }
    }
}
