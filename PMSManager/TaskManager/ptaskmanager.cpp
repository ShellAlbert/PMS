#include "ptaskmanager.h"
#include <TaskManager/zprocesssteplinktemplateselectdia.h>
#include <TemplateEditor/ztemplateinfodia.h>
#include <TaskManager/ztasksheet.h>
#include <TaskManager/ztaskinfodia.h>
#include <TaskManager/zlisttaskdia.h>
#include <TaskManager/ztasksheet.h>
#include <QMessageBox>
#include <QDebug>
#include <QPrinter>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <QHeaderView>
#include <QBuffer>
#include <QFileDialog>
#include <QMenu>
#include <QAction>
PTaskList::PTaskList(QWidget *parent):QFrame(parent)
{
    this->m_llTaskFilter=new QLabel(tr("过滤条件"));
    this->m_cbTaskFilter=new QComboBox;
    this->m_cbTaskFilter->setEditable(false);
    this->m_cbTaskFilter->addItem(QIcon(":/TaskManager/images/TaskManager/star_blue.png"),tr("所有任务"));
    this->m_cbTaskFilter->addItem(QIcon(":/TaskManager/images/TaskManager/star_orange.png"),tr("未提交任务"));
    this->m_cbTaskFilter->addItem(QIcon(":/TaskManager/images/TaskManager/star_pink.png"),tr("未审核任务"));
    this->m_cbTaskFilter->addItem(QIcon(":/TaskManager/images/TaskManager/star_green.png"),tr("审核通过任务"));
    this->m_cbTaskFilter->addItem(QIcon(":/TaskManager/images/TaskManager/star_red.png"),tr("审核失败任务"));
    this->m_cbTaskFilter->addItem(QIcon(":/TaskManager/images/TaskManager/star_yellow.png"),tr("已归档任务"));
    this->m_cbTaskFilter->addItem(QIcon(":/TaskManager/images/TaskManager/star_yellow.png"),tr("需要我审核的任务"));
    this->m_cbTaskFilter->addItem(QIcon(":/TaskManager/images/TaskManager/star_yellow.png"),tr("我审核通过的任务"));
    this->m_cbTaskFilter->addItem(QIcon(":/TaskManager/images/TaskManager/star_yellow.png"),tr("我审核驳回的任务"));
    connect(this->m_cbTaskFilter,SIGNAL(currentIndexChanged(int)),this,SIGNAL(ZSignalFilterChanged(qint32)));
    this->m_hLayoutFilter=new QHBoxLayout;
    this->m_hLayoutFilter->addStretch(1);
    this->m_hLayoutFilter->addWidget(this->m_llTaskFilter);
    this->m_hLayoutFilter->addWidget(this->m_cbTaskFilter);

    this->m_tree=new QTreeWidget;
    this->m_tree->setColumnCount(9);
    QStringList headerList;
    headerList<<tr("任务名称");
    headerList<<tr("引用工序");
    headerList<<tr("引用步序");
    headerList<<tr("引用模板");
    headerList<<tr("当前状态");
    headerList<<tr("创建者");
    headerList<<tr("创建时间");
    headerList<<tr("审核者");
    headerList<<tr("审核时间");
    this->m_tree->setHeaderLabels(headerList);
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addLayout(this->m_hLayoutFilter);
    this->m_vLayout->addWidget(this->m_tree);
    this->setLayout(this->m_vLayout);
}
PTaskList::~PTaskList()
{
    delete this->m_llTaskFilter;
    delete this->m_cbTaskFilter;
    delete this->m_hLayoutFilter;
    delete this->m_tree;
    delete this->m_vLayout;
}
PTaskManager::PTaskManager(QWidget *parent):QFrame(parent)
{
    this->setWindowTitle(tr("任务管理器-Task Manager"));
    this->setWindowIcon(QIcon(":/TaskBar/images/TaskManager.png"));
    this->setStyleSheet("QToolButton{background-color:#cce5f9;border:none;font:color #eaf7ff;}"
                        "QToolButton::hover{background-color:#eaf7ff;}"
                        "");

    this->m_vLayoutBtn=new QVBoxLayout;

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_taskManagerPerm&PermBits_TaskManager_NewTask)
    {
        this->m_btnAddTask=new QToolButton;
        this->m_btnAddTask->setToolTip(tr("创建任务"));
        this->m_btnAddTask->setText(tr("创建"));
        this->m_btnAddTask->setIcon(QIcon(":/TaskManager/images/TaskManager/AddTask.png"));
        this->m_btnAddTask->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutBtn->addWidget(this->m_btnAddTask);
        connect(this->m_btnAddTask,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddTask()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_taskManagerPerm&PermBits_TaskManager_MdyTask)
    {
        this->m_btnMdyTask=new QToolButton;
        this->m_btnMdyTask->setToolTip(tr("打开任务"));
        this->m_btnMdyTask->setText(tr("打开"));
        this->m_btnMdyTask->setIcon(QIcon(":/TaskManager/images/TaskManager/MdyTask.png"));
        this->m_btnMdyTask->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        this->m_btnSaveTask=new QToolButton;
        this->m_btnSaveTask->setToolTip(tr("保存任务"));
        this->m_btnSaveTask->setText(tr("保存"));
        this->m_btnSaveTask->setIcon(QIcon(":/TaskManager/images/TaskManager/SaveTask.png"));
        this->m_btnSaveTask->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        this->m_vLayoutBtn->addWidget(this->m_btnMdyTask);
        this->m_vLayoutBtn->addWidget(this->m_btnSaveTask);

        connect(this->m_btnMdyTask,SIGNAL(clicked(bool)),this,SLOT(ZSlotMdyTask()));
        connect(this->m_btnSaveTask,SIGNAL(clicked(bool)),this,SLOT(ZSlotSaveTask()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_taskManagerPerm&PermBits_TaskManager_DelTask)
    {
        this->m_btnDelTask=new QToolButton;
        this->m_btnDelTask->setToolTip(tr("删除任务"));
        this->m_btnDelTask->setText(tr("删除"));
        this->m_btnDelTask->setIcon(QIcon(":/TaskManager/images/TaskManager/DelTask.png"));
        this->m_btnDelTask->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        this->m_vLayoutBtn->addWidget(this->m_btnDelTask);
        connect(this->m_btnDelTask,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelTask()));
    }

    this->m_btnArchieve=new QToolButton;
    this->m_btnArchieve->setToolTip(tr("归档任务"));
    this->m_btnArchieve->setText(tr("归档"));
    this->m_btnArchieve->setIcon(QIcon(":/TaskManager/images/TaskManager/WithdrawTask.png"));
    this->m_btnArchieve->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    this->m_tbTaskManage=new QToolButton;
    this->m_tbTaskManage->setToolTip((tr("审核管理")));
    this->m_tbTaskManage->setText((tr("审核")));
    this->m_tbTaskManage->setIcon(QIcon(":/TaskManager/images/TaskManager/SubmitTask.png"));
    this->m_tbTaskManage->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_actSubmitTask=new QAction(QIcon(":/TaskManager/images/TaskManager/SubmitTask.png"),tr("提交审核"),0);
    this->m_actWithdrawTask=new QAction(QIcon(":/TaskManager/images/TaskManager/WithdrawTask.png"),tr("撤回审核"),0);
    this->m_actCheckOkay=new QAction(QIcon(":/TaskManager/images/TaskManager/SubmitTask.png"),tr("审核通过"),0);
    this->m_actCheckFailed=new QAction(QIcon(":/TaskManager/images/TaskManager/WithdrawTask.png"),tr("审核驳回"),0);
    this->m_menuTaskManage=new QMenu;
    this->m_menuTaskManage->addAction(this->m_actSubmitTask);
    this->m_menuTaskManage->addAction(this->m_actWithdrawTask);
    this->m_menuTaskManage->addAction(this->m_actCheckOkay);
    this->m_menuTaskManage->addAction(this->m_actCheckFailed);
    this->m_tbTaskManage->setMenu(this->m_menuTaskManage);
    this->m_tbTaskManage->setPopupMode(QToolButton::InstantPopup);

    this->m_btnPrint=new QToolButton;
    this->m_btnPrint->setToolTip(tr("打印..."));
    this->m_btnPrint->setText(tr("打印"));
    this->m_btnPrint->setIcon(QIcon(":/TaskManager/images/TaskManager/Print.png"));
    this->m_btnPrint->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_actPrintHtml=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/PrintHtml.png"),tr("打印Html"),0);
    connect(this->m_actPrintHtml,SIGNAL(triggered(bool)),this,SLOT(ZSlotPrintHtml()));
    this->m_actPrintPdf=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/PrintPdf.png"),tr("打印Pdf"),0);
    connect(this->m_actPrintPdf,SIGNAL(triggered(bool)),this,SLOT(ZSlotPrintPdf()));
    this->m_menuPrint=new QMenu;
    this->m_menuPrint->addAction(this->m_actPrintHtml);
    this->m_menuPrint->addAction(this->m_actPrintPdf);
    this->m_btnPrint->setMenu(this->m_menuPrint);
    this->m_btnPrint->setPopupMode(QToolButton::InstantPopup);

    //help.
    this->m_tbHelp=new QToolButton;
    this->m_tbHelp->setToolTip(tr("获取帮助文档"));
    this->m_tbHelp->setText(tr("帮助"));
    this->m_tbHelp->setIcon(QIcon(":/common/images/common/help.png"));
    this->m_tbHelp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(this->m_tbHelp,SIGNAL(clicked(bool)),this,SLOT(ZSlotHelp()));

    this->m_vLayoutBtn->addWidget(this->m_btnArchieve);
    this->m_vLayoutBtn->addWidget(this->m_tbTaskManage);
    this->m_vLayoutBtn->addStretch(1);
    this->m_vLayoutBtn->addWidget(this->m_btnPrint);
    this->m_vLayoutBtn->addWidget(this->m_tbHelp);

    //right.
    this->m_tabWidget=new QTabWidget;
    this->m_tabWidget->setTabsClosable(true);
    this->m_taskList=new PTaskList;
    connect(this->m_taskList,SIGNAL(ZSignalFilterChanged(qint32)),this,SLOT(ZSlotRefreshTaskList(qint32)));
    this->m_tabWidget->addTab(this->m_taskList,QIcon(":/TaskBar/images/TaskManager.png"),tr("任务管理 "));
    this->m_tabWidget->tabBar()->tabButton(0,QTabBar::RightSide)->hide();
    this->m_taskList->m_tree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this->m_taskList->m_tree,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ZSlotPopupMenu(QPoint)));

    //main.
    this->m_hLayoutMain=new QHBoxLayout;
    this->m_hLayoutMain->addLayout(this->m_vLayoutBtn);
    this->m_hLayoutMain->addWidget(this->m_tabWidget);
    this->m_hLayoutMain->setSpacing(10);
    this->setLayout(this->m_hLayoutMain);

    connect(this->m_actSubmitTask,SIGNAL(triggered(bool)),this,SLOT(ZSlotSubmitTask()));
    connect(this->m_actWithdrawTask,SIGNAL(triggered(bool)),this,SLOT(ZSlotWithdrawTask()));
    connect(this->m_actCheckOkay,SIGNAL(triggered(bool)),this,SLOT(ZSlotCheckOkay()));
    connect(this->m_actCheckFailed,SIGNAL(triggered(bool)),this,SLOT(ZSlotCheckFailed()));
    connect(this->m_btnArchieve,SIGNAL(clicked(bool)),this,SLOT(ZSlotArchieve()));
    connect(this->m_btnPrint,SIGNAL(clicked(bool)),this,SLOT(ZSlotPrint()));

    connect(this->m_tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(ZSlotCloseTabWidget(qint32)));

    connect(this->m_taskList->m_tree,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ZSlotDblClickOpenTask(QModelIndex)));

    ZListTaskDia *dia=new ZListTaskDia(this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteListOp(Task_Type_All);
    dia->ZShowWaitingDialog();
}
PTaskManager::~PTaskManager()
{
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_taskManagerPerm&PermBits_TaskManager_NewTask)
    {
        delete this->m_btnAddTask;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_taskManagerPerm&PermBits_TaskManager_MdyTask)
    {
        delete this->m_btnSaveTask;
        delete this->m_btnMdyTask;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_taskManagerPerm&PermBits_TaskManager_DelTask)
    {
        delete this->m_btnDelTask;
    }
    delete this->m_actSubmitTask;
    delete this->m_actWithdrawTask;
    delete this->m_actCheckOkay;
    delete this->m_actCheckFailed;
    delete this->m_menuTaskManage;
    delete this->m_tbTaskManage;
    delete this->m_btnArchieve;
    delete this->m_actPrintHtml;
    delete this->m_actPrintPdf;
    delete this->m_menuPrint;
    delete this->m_btnPrint;
    delete this->m_tbHelp;
    delete this->m_vLayoutBtn;

    //right.
    for(qint32 i=1;i<this->m_tabWidget->count();i++)
    {
        QWidget *widget=this->m_tabWidget->widget(i);
        this->m_tabWidget->removeTab(i);
        delete widget;
        widget=NULL;
    }
    delete this->m_tabWidget;
    delete this->m_hLayoutMain;
}
void PTaskManager::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{
    if(item=="task")
    {
        if(cmd=="add")
        {
            if(ackNetRetCode<0)
            {
                QString taskName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("create task [%1] failed:%2.").arg(taskName).arg(errMsg));
            }else{
                QString taskName=paraList.at(0);
                QString refTemplate=paraList.at(1);
                QString refProcess=paraList.at(2);
                QString refStep=paraList.at(3);
                QString taskState=paraList.at(4);
                QString creator=paraList.at(5);
                QString createTime=paraList.at(6);
                QString checker=paraList.at(7);
                QString checkTime=paraList.at(8);

                QTreeWidgetItem *item=new QTreeWidgetItem;
                item->setIcon(0,QIcon(":/TaskManager/images/TaskManager/MdyTask.png"));
                item->setText(0,taskName);
                item->setText(1,refProcess);
                item->setText(2,refStep);
                item->setText(3,refTemplate);
                item->setText(4,ZGetTaskStateString(taskState.toInt()));
                item->setIcon(4,QIcon(ZGetTaskStateIconName(taskState.toInt())));
                item->setText(5,creator);
                item->setText(6,createTime);
                item->setIcon(6,QIcon(":/common/images/common/Calendar.png"));
                item->setText(7,checker);
                item->setText(8,checkTime);
                item->setIcon(8,QIcon(":/common/images/common/Calendar.png"));
                this->m_taskList->m_tree->addTopLevelItem(item);
                this->m_taskList->m_tree->setCurrentItem(item);
                this->ZAddLogMsg(tr("create task [%1] from template [%2] success.").arg(taskName).arg(refTemplate));
            }
        }else if(cmd=="list")
        {
            QString taskName=paraList.at(0);
            QString refProcess=paraList.at(1);
            QString refStep=paraList.at(2);
            QString refTemplate=paraList.at(3);
            QString taskState=paraList.at(4);
            QString creator=paraList.at(5);
            QString createTime=paraList.at(6);
            QString checker=paraList.at(7);
            QString checkTime=paraList.at(8);
            QString errMsg=paraList.at(9);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("list task attach with state [%1] failed:%2.").arg(taskState).arg(errMsg));
            }else{
                QTreeWidgetItem *item=new QTreeWidgetItem;
                item->setIcon(0,QIcon(":/TaskManager/images/TaskManager/MdyTask.png"));
                item->setText(0,taskName);
                item->setText(1,refProcess);
                item->setText(2,refStep);
                item->setText(3,refTemplate);
                item->setText(4,ZGetTaskStateString(taskState.toInt()));
                item->setIcon(4,QIcon(ZGetTaskStateIconName(taskState.toInt())));
                item->setText(5,creator);
                item->setText(6,createTime);
                item->setIcon(6,QIcon(":/common/images/common/Calendar.png"));
                item->setText(7,checker);
                item->setText(8,checkTime);
                item->setIcon(8,QIcon(":/common/images/common/Calendar.png"));
                this->m_taskList->m_tree->addTopLevelItem(item);
                this->m_taskList->m_tree->setCurrentItem(item);
                this->ZAddLogMsg(tr("list task [%1] with task state [%2] success.").arg(taskName).arg(taskState));
                for(qint32 i=0;i<this->m_taskList->m_tree->columnCount();i++)
                {
                    this->m_taskList->m_tree->resizeColumnToContents(i);
                }
            }
        }else if(cmd=="get")
        {
            QString taskName=paraList.at(0);
            QString refTemplate=paraList.at(1);
            QString refProcess=paraList.at(2);
            QString refStep=paraList.at(3);
            QString templatedata=paraList.at(4);
            QString varsrcdata=paraList.at(5);
            QString vardata=paraList.at(6);
            qint32 taskState=paraList.at(7).toInt();
            ZTaskWidget *task=new ZTaskWidget;
            task->m_sheet->ZSetTaskName(taskName);
            task->m_sheet->ZSetRefTemplateName(refTemplate);
            task->m_sheet->ZSetProcessName(refProcess);
            task->m_sheet->ZSetStepName(refStep);
            QString templateXmlData=QString(QByteArray::fromBase64(templatedata.toUtf8()));
            QString varSrcData=QString(QByteArray::fromBase64(varsrcdata.toUtf8()));
            task->m_sheet->ZSetTemplateXmlDataAndVarSourceXmlData(templateXmlData,varSrcData);
            connect(task,SIGNAL(ZSignalLogMsg(QString)),this,SIGNAL(ZSignalLogMsg(QString)));
            connect(task->m_sheet,SIGNAL(ZSignalLogMsg(QString)),this,SIGNAL(ZSignalLogMsg(QString)));
            connect(task->m_sheet,SIGNAL(ZSignalDataChanged(QString)),this,SLOT(ZSlotTaskDataChanged(QString)));
            task->m_sheet->ZExecuteLoadActionBeforeShow();
            task->ZSetTaskState(taskState);
            task->ZSetVarValueXmlData(vardata);

            this->m_tabWidget->addTab(task,QIcon(":/TaskBar/images/Sheet.png"),taskName);
            this->m_tabWidget->setCurrentWidget(task);

            for(qint32 i=0;i<this->m_taskList->m_tree->topLevelItemCount();i++)
            {
                QTreeWidgetItem *item=this->m_taskList->m_tree->topLevelItem(i);
                if(item->text(0)==taskName)
                {
                    task->m_refProcess=item->text(1);
                    task->m_refStep=item->text(2);
                    task->m_refTemplate=item->text(3);
                    task->m_creator=item->text(5);
                    task->m_createTime=item->text(6);
                    task->m_checker=item->text(7);
                    task->m_checkTime=item->text(8);
                    break;
                }
            }
            this->ZAddLogMsg(tr("open task [%1] success,reference template:[%2],var source:[%3].").arg(taskName).arg(refTemplate));

        }else if(cmd=="del")
        {
            QString taskName=paraList.at(0);
            QString errMsg=paraList.at(1);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("delete task [%1] failed:[%2].").arg(taskName).arg(errMsg));
            }else{
                for(qint32 i=0;i<this->m_taskList->m_tree->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_taskList->m_tree->topLevelItem(i);
                    if(item->text(0)==taskName)
                    {
                        this->m_taskList->m_tree->takeTopLevelItem(i);
                        delete item;
                        item=NULL;
                        break;
                    }
                }
                this->ZAddLogMsg(tr("delete task [%1] success.").arg(taskName));
            }
        }else if(cmd=="save")
        {
            QString taskName=paraList.at(0);
            qint32 taskState=paraList.at(1).toInt();
            QString errMsg=paraList.at(2);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("save task [%1] failed:[%2].").arg(taskName).arg(errMsg));
            }else{
                //remove <*> from tab text.
                for(qint32 i=0;i<this->m_tabWidget->count();i++)
                {
                    if(this->m_tabWidget->tabText(i)=="<*>"+taskName)
                    {
                        this->m_tabWidget->setTabText(i,taskName);
                        ZTaskWidget *widget=qobject_cast<ZTaskWidget*>(this->m_tabWidget->widget(i));
                        if(widget)
                        {
                            widget->ZSetTaskState(Task_Type_Save);
                        }
                        break;
                    }
                }
                //change taskState from New to Save.
                for(qint32 i=0;i<this->m_taskList->m_tree->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_taskList->m_tree->topLevelItem(i);
                    if(item->text(0)==taskName)
                    {
                        item->setText(4,ZGetTaskStateString(taskState));
                        item->setIcon(4,QIcon(ZGetTaskStateIconName(taskState)));
                        break;
                    }
                }
                this->ZAddLogMsg(tr("save task [%1] success,state:[%2].").arg(taskName).arg(ZGetTaskStateString(taskState)));
            }
        }else if(cmd=="submit")
        {
            QString taskName=paraList.at(0);
            qint32 taskState=paraList.at(1).toInt();
            QString errMsg=paraList.at(2);

            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("submit task [%1] failed:[%2].").arg(taskName).arg(errMsg));
            }else{
                //change taskState from Save to Submit.
                for(qint32 i=0;i<this->m_taskList->m_tree->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_taskList->m_tree->topLevelItem(i);
                    if(item->text(0)==taskName)
                    {
                        item->setText(4,ZGetTaskStateString(taskState));
                        item->setIcon(4,QIcon(ZGetTaskStateIconName(taskState)));
                        break;
                    }
                }

                ZTaskWidget *widget=qobject_cast<ZTaskWidget*>(this->m_tabWidget->currentWidget());
                if(widget)
                {
                    if(widget->m_sheet->ZGetTaskName()==taskName)
                    {
                        widget->ZSetTaskState(Task_Type_Submit);
                    }
                }
                this->ZAddLogMsg(tr("submit task [%1] success,state:[%2].").arg(taskName).arg(ZGetTaskStateString(taskState)));
            }
        }else if(cmd=="withdraw")
        {
            QString taskName=paraList.at(0);
            qint32 taskState=paraList.at(1).toInt();
            QString errMsg=paraList.at(2);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("withdraw task [%1] failed:[%2].").arg(taskName).arg(errMsg));
            }else{
                //change taskState from Submit to Save.
                for(qint32 i=0;i<this->m_taskList->m_tree->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_taskList->m_tree->topLevelItem(i);
                    if(item->text(0)==taskName)
                    {
                        item->setText(4,ZGetTaskStateString(taskState));
                        item->setIcon(4,QIcon(ZGetTaskStateIconName(taskState)));
                        break;
                    }
                }
                ZTaskWidget *widget=qobject_cast<ZTaskWidget*>(this->m_tabWidget->currentWidget());
                if(widget)
                {
                    if(widget->m_sheet->ZGetTaskName()==taskName)
                    {
                        widget->ZSetTaskState(Task_Type_Save);
                    }
                }
                this->ZAddLogMsg(tr("withdraw task [%1] success,state:[%2].").arg(taskName).arg(ZGetTaskStateString(taskState)));
            }
        }else if(cmd=="checkokay")
        {
            QString taskName=paraList.at(0);
            qint32 taskState=paraList.at(1).toInt();
            QString errMsg=paraList.at(2);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("check okay task [%1] failed:[%2].").arg(taskName).arg(errMsg));
            }else{
                //change taskState from Submit to CheckOkay.
                for(qint32 i=0;i<this->m_taskList->m_tree->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_taskList->m_tree->topLevelItem(i);
                    if(item->text(0)==taskName)
                    {
                        item->setText(4,ZGetTaskStateString(taskState));
                        item->setIcon(4,QIcon(ZGetTaskStateIconName(taskState)));
                        break;
                    }
                }
                ZTaskWidget *widget=qobject_cast<ZTaskWidget*>(this->m_tabWidget->currentWidget());
                if(widget)
                {
                    if(widget->m_sheet->ZGetTaskName()==taskName)
                    {
                        widget->ZSetTaskState(Task_Type_Check_Okay);
                    }
                }
                this->ZAddLogMsg(tr("check okay task [%1] success,state:[%2].").arg(taskName).arg(ZGetTaskStateString(taskState)));
            }
        }else if(cmd=="checkfailed")
        {
            QString taskName=paraList.at(0);
            qint32 taskState=paraList.at(1).toInt();
            QString errMsg=paraList.at(2);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("check failed task [%1] failed:[%2].").arg(taskName).arg(errMsg));
            }else{
                //change taskState from Submit to CheckFailed.
                for(qint32 i=0;i<this->m_taskList->m_tree->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_taskList->m_tree->topLevelItem(i);
                    if(item->text(0)==taskName)
                    {
                        item->setText(4,ZGetTaskStateString(taskState));
                        item->setIcon(4,QIcon(ZGetTaskStateIconName(taskState)));
                        break;
                    }
                }
                ZTaskWidget *widget=qobject_cast<ZTaskWidget*>(this->m_tabWidget->currentWidget());
                if(widget)
                {
                    if(widget->m_sheet->ZGetTaskName()==taskName)
                    {
                        widget->ZSetTaskState(Task_Type_Check_Failed);
                    }
                }
                this->ZAddLogMsg(tr("check failed task [%1] success,state:[%2].").arg(taskName).arg(ZGetTaskStateString(taskState)));
            }
        }else if(cmd=="archieve")
        {
            if(ackNetRetCode<0)
            {
                QString taskName=paraList.at(0);
                QString errMsg=paraList.at(1);
                this->ZAddLogMsg(tr("Archieve task [%1] failed:%2.").arg(taskName).arg(errMsg));
            }else{
                QString taskName=paraList.at(0);
                qint32 taskState=paraList.at(1).toInt();
                //change taskState from CheckOkay to Archieve.
                for(qint32 i=0;i<this->m_taskList->m_tree->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_taskList->m_tree->topLevelItem(i);
                    if(item->text(0)==taskName)
                    {
                        item->setText(4,ZGetTaskStateString(taskState));
                        item->setIcon(4,QIcon(ZGetTaskStateIconName(taskState)));
                        break;
                    }
                }
                ZTaskWidget *widget=qobject_cast<ZTaskWidget*>(this->m_tabWidget->currentWidget());
                if(widget)
                {
                    if(widget->m_sheet->ZGetTaskName()==taskName)
                    {
                        widget->ZSetTaskState(Task_Type_Archieve);
                    }
                }
                this->ZAddLogMsg(tr("Archiev task [%1] success.").arg(taskName));
            }
        }
    }
}
void PTaskManager::closeEvent(QCloseEvent *event)
{
    emit this->ZSignalCloseEvent("TaskManager");
    QFrame::closeEvent(event);
}
void PTaskManager::ZSlotAddTask()
{
    ZProcessStepLinkTemplateSelectDia selectDia;
    if(selectDia.exec()==QDialog::Accepted)
    {
        QString templateName=selectDia.ZGetSelectedTemplate();
        QString processName=selectDia.ZGetSelectedProcess();
        QString stepName=selectDia.ZGetSelectedStep();
        if(templateName.isEmpty()||processName.isEmpty()||stepName.isEmpty())
        {
            return;
        }
        ZTaskInfoDia *dia=new ZTaskInfoDia(ZTaskInfoDia::Type_NewTask,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetTaskName(QString("%1-%2-%3").arg(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName).arg(templateName).arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss")));
        dia->ZSetRefTemplateName(templateName);
        dia->ZSetProcessName(processName);
        dia->ZSetStepName(stepName);
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
void PTaskManager::ZSlotSaveTask()
{
    qint32 index=this->m_tabWidget->currentIndex();
    if(index==0)
    {
        return;//bypass tab0.
    }
    if(!this->m_tabWidget->tabText(index).startsWith("<*>"))
    {
        return;//no need to save.
    }
    ZTaskWidget *task=qobject_cast<ZTaskWidget*>(this->m_tabWidget->widget(index));
    if(task)
    {
        if(!task->ZCheckCellDataValidation())
        {
            QMessageBox::critical(this,tr("错误提示"),tr("数据校验错误!\n请按规则填写任务数据!"));
            return;
        }
        ZTaskInfoDia *dia=new ZTaskInfoDia(ZTaskInfoDia::Type_SaveTask,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetTaskName(task->m_sheet->ZGetTaskName());
        dia->ZSetRefTemplateName(task->m_sheet->ZGetRefTemplateName());
        dia->ZSetTaskValueXmlData(task->ZGetTaskVarValueXmlData());
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
void PTaskManager::ZSlotMdyTask()
{
    QTreeWidgetItem *item=this->m_taskList->m_tree->currentItem();
    if(item==NULL)
    {
        return;
    }
    for(qint32 i=0;i<this->m_tabWidget->count();i++)
    {
        QString tabName=this->m_tabWidget->tabText(i);
        if(tabName==item->text(0) || tabName==QString("<*>")+item->text(0))
        {
            this->m_tabWidget->setCurrentIndex(i);
            return;
        }
    }
    ZTaskInfoDia *dia=new ZTaskInfoDia(ZTaskInfoDia::Type_OpenTask,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetTaskName(item->text(0));
    dia->ZSetProcessName(item->text(1));
    dia->ZSetStepName(item->text(2));
    dia->ZSetRefTemplateName(item->text(3));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PTaskManager::ZSlotDelTask()
{
    QTreeWidgetItem *item=this->m_taskList->m_tree->currentItem();
    if(item==NULL)
    {
        return;
    }
    if(item->text(5)!=MyUserInfo::ZGetInstance()->m_UserInfo.m_userName)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("删除任务[%1]失败!\n您不是该任务的创建者!\n只有该任务的创建者[%2]或管理员才有权限删除!").arg(item->text(0)).arg(item->text(3)));
        return;
    }
    QString taskState=item->text(4);
    if(taskState==tr("审核通过")||taskState==tr("已提交审核")||taskState==tr("已归档"))
    {
        QMessageBox::critical(this,tr("错误提示"),tr("删除任务[%1]失败!\n只有新建任务,已保存,审核失败的任务才可以删除!\n当前任务状态:[%2]!").arg(item->text(0)).arg(taskState));
        return;
    }
    if(QMessageBox::question(this,tr("删除确认"),tr("您确认要删除任务[%1]吗?").arg(item->text(0)),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
    {
        return;
    }
    ZTaskInfoDia *dia=new ZTaskInfoDia(ZTaskInfoDia::Type_DelTask,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetTaskName(item->text(0));
    dia->ZSetProcessName(item->text(1));
    dia->ZSetStepName(item->text(2));
    dia->ZSetRefTemplateName(item->text(3));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PTaskManager::ZSlotSubmitTask()
{
    qint32 index=this->m_tabWidget->currentIndex();
    if(index==0)
    {
        return;//bypass tab0.
    }
    if(this->m_tabWidget->tabText(index).startsWith("<*>"))
    {
        if(QMessageBox::question(this,tr("保存提示"),tr("任务被修改,需保存后再提交审核!\n是否继续保存?"),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
        {
            return;
        }
        this->ZSlotSaveTask();
    }
    ZTaskWidget *task=qobject_cast<ZTaskWidget*>(this->m_tabWidget->widget(index));
    if(task)
    {
        if(task->ZGetTaskState()!=Task_Type_Save)
        {
            QMessageBox::critical(this,tr("错误提示"),tr("当前任务不可提交审核!\n只有保存状态下的任务可以提交审核!"));
            return;
        }
        if(QMessageBox::question(this,tr("提示确认"),tr("您确认要提交审核吗?\n\n任务名:[%1]\n将被提交给\n审核者:[%2]\n审核.\n\n提交审核后任务将不可编辑!").arg(task->m_sheet->ZGetTaskName()).arg(MyUserInfo::ZGetInstance()->m_UserInfo.m_Creator),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
        {
            return;
        }
        ZTaskInfoDia *dia=new ZTaskInfoDia(ZTaskInfoDia::Type_SubmitTask,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetTaskName(task->m_sheet->ZGetTaskName());
        dia->ZSetRefTemplateName(task->m_sheet->ZGetRefTemplateName());
        dia->ZSetProcessName(task->m_sheet->ZGetProcessName());
        dia->ZSetStepName(task->m_sheet->ZGetStepName());
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
void PTaskManager::ZSlotWithdrawTask()
{
    qint32 index=this->m_tabWidget->currentIndex();
    if(index==0)
    {
        return;//bypass tab0.
    }
    ZTaskWidget *task=qobject_cast<ZTaskWidget*>(this->m_tabWidget->widget(index));
    if(task)
    {
        if(task->ZGetTaskState()!=Task_Type_Submit)
        {
            QMessageBox::critical(this,tr("错误提示"),tr("当前任务不可撤回!\n只有已提交审核状态下的任务可以撤回!"));
            return;
        }
        if(QMessageBox::question(this,tr("提示确认"),tr("您确认要撤回审核吗?\n任务名:[%1]\n撤回审核的任务可再次编辑并提交审核!").arg(task->m_sheet->ZGetTaskName()),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
        {
            return;
        }
        ZTaskInfoDia *dia=new ZTaskInfoDia(ZTaskInfoDia::Type_WithdrawTask,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetTaskName(task->m_sheet->ZGetTaskName());
        dia->ZSetRefTemplateName(task->m_sheet->ZGetRefTemplateName());
        dia->ZSetProcessName(task->m_sheet->ZGetProcessName());
        dia->ZSetStepName(task->m_sheet->ZGetStepName());
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
void PTaskManager::ZSlotCheckOkay()
{
    qint32 index=this->m_tabWidget->currentIndex();
    if(index==0)
    {
        return;//bypass tab0.
    }
    ZTaskWidget *task=qobject_cast<ZTaskWidget*>(this->m_tabWidget->widget(index));
    if(task)
    {
        if(task->ZGetTaskState()!=Task_Type_Submit)
        {
            QMessageBox::critical(this,tr("错误提示"),tr("当前任务无法审核通过!\n只有已提交审核状态下的任务可以审核通过!"));
            return;
        }
        if(QMessageBox::question(this,tr("提示确认"),tr("您确认要审核通过该任务吗?\n任务名:[%1].").arg(task->m_sheet->ZGetTaskName()),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
        {
            return;
        }
        ZTaskInfoDia *dia=new ZTaskInfoDia(ZTaskInfoDia::Type_CheckOkayTask,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetTaskName(task->m_sheet->ZGetTaskName());
        dia->ZSetRefTemplateName(task->m_sheet->ZGetRefTemplateName());
        dia->ZSetProcessName(task->m_sheet->ZGetProcessName());
        dia->ZSetStepName(task->m_sheet->ZGetStepName());
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
void PTaskManager::ZSlotCheckFailed()
{
    qint32 index=this->m_tabWidget->currentIndex();
    if(index==0)
    {
        return;//bypass tab0.
    }
    ZTaskWidget *task=qobject_cast<ZTaskWidget*>(this->m_tabWidget->widget(index));
    if(task)
    {
        if(task->ZGetTaskState()!=Task_Type_Submit)
        {
            QMessageBox::critical(this,tr("错误提示"),tr("当前任务无法审核通过!\n只有已提交审核状态下的任务可以审核失败!"));
            return;
        }

        if(QMessageBox::question(this,tr("提示确认"),tr("您确认要审核失败该任务吗?\n任务名:[%1].").arg(task->m_sheet->ZGetTaskName()),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
        {
            return;
        }
        ZTaskInfoDia *dia=new ZTaskInfoDia(ZTaskInfoDia::Type_CheckFailedTask,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetTaskName(task->m_sheet->ZGetTaskName());
        dia->ZSetRefTemplateName(task->m_sheet->ZGetRefTemplateName());
        dia->ZSetProcessName(task->m_sheet->ZGetProcessName());
        dia->ZSetStepName(task->m_sheet->ZGetStepName());
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
void PTaskManager::ZSlotArchieve()
{
    qint32 index=this->m_tabWidget->currentIndex();
    if(index==0)
    {
        return;//bypass tab0.
    }
    ZTaskWidget *task=qobject_cast<ZTaskWidget*>(this->m_tabWidget->widget(index));
    if(task)
    {
        if(task->ZGetTaskState()!=Task_Type_Check_Okay)
        {
            QMessageBox::critical(this,tr("错误提示"),tr("当前任务无法归档!\n只有提交通过状态下的任务可以归档!"));
            return;
        }

        if(QMessageBox::question(this,tr("提示确认"),tr("您确认要归档该任务吗?\n任务名:[%1].").arg(task->m_sheet->ZGetTaskName()),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
        {
            return;
        }
        ZTaskInfoDia *dia=new ZTaskInfoDia(ZTaskInfoDia::Type_ArchieveTask,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetTaskName(task->m_sheet->ZGetTaskName());
        dia->ZSetRefTemplateName(task->m_sheet->ZGetRefTemplateName());
        dia->ZSetProcessName(task->m_sheet->ZGetProcessName());
        dia->ZSetStepName(task->m_sheet->ZGetStepName());
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
void PTaskManager::ZSlotTaskDataChanged(QString taskName)
{
    for(qint32 i=1;i<this->m_tabWidget->count();i++)
    {
        QString tabName=this->m_tabWidget->tabText(i);
        if(tabName==taskName)
        {
            this->m_tabWidget->setTabText(i,"<*>"+tabName);
            break;
        }
    }
}
void PTaskManager::ZAddLogMsg(QString logMsg)
{
    emit this->ZSignalLogMsg("<TaskManager>:"+logMsg);
}
void PTaskManager::ZSlotCloseTabWidget(qint32 index)
{
    //tab0 is never close.
    if(index==0)
    {
        return;
    }
    if(this->m_tabWidget->tabText(index).startsWith("<*>"))
    {
        if(QMessageBox::question(this,tr("操作提示"),tr("任务被更改,尚未保存!\n您确认要关闭吗?"),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
        {
            return;
        }
    }

    //delete it to remove it from tab widget.
    this->m_tabWidget->removeTab(index);
    delete this->m_tabWidget->widget(index);
}
void PTaskManager::ZSlotDblClickOpenTask(QModelIndex index)
{
    (void)(index);
    this->ZSlotMdyTask();
}
void PTaskManager::ZSlotRefreshTaskList(qint32 index)
{
    this->m_taskList->m_tree->clear();
    ZListTaskDia *dia=new ZListTaskDia(this);
    dia->ZSetAckNetFrmProcessWidget(this);
    switch(index)
    {
    case 0:
        dia->ZExecuteListOp(Task_Type_All);
        break;
    case 1:
        dia->ZExecuteListOp(Task_Type_Save);
        break;
    case 2:
        dia->ZExecuteListOp(Task_Type_Submit);
        break;
    case 3:
        dia->ZExecuteListOp(Task_Type_Check_Okay);
        break;
    case 4:
        dia->ZExecuteListOp(Task_Type_Check_Failed);
        break;
    case 5:
        dia->ZExecuteListOp(Task_Type_Archieve);
        break;
    case 6:
        dia->ZExecuteListOp(Task_Type_Need_My_Check);
        break;
    case 7:
        dia->ZExecuteListOp(Task_Type_My_Check_Okay);
        break;
    case 8:
        dia->ZExecuteListOp(Task_Type_My_Check_Failed);
        break;
    default:
        break;
    }
    dia->ZShowWaitingDialog();
}
void PTaskManager::ZSlotPrintHtml()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;//bypass tab0.
    }
    ZTaskWidget *task=qobject_cast<ZTaskWidget*>(this->m_tabWidget->currentWidget());
    if(task==NULL)
    {
        return;
    }
    QString taskName=task->m_sheet->ZGetTaskName();
    QString creator;
    QString createTime;
    for(qint32 i=0;i<this->m_taskList->m_tree->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=this->m_taskList->m_tree->topLevelItem(i);
        if(item->text(0)==taskName)
        {
            creator=item->text(5);
            createTime=item->text(6);
            break;
        }
    }
    QString note=QString("创建人:%1,创建时间:%2").arg(creator).arg(createTime);
    QString html;
    qint32 ret=ZGetQTableWidgetHtml(tr("任务:%1").arg(taskName),note,task->m_sheet,&html);
    if(ret<0)
    {
        return;
    }
    QString fileName=QFileDialog::getSaveFileName(this,tr("打印html"),tr("./%1.html").arg(taskName),"*.html");
    if(fileName.isEmpty())
    {
        return;
    }
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(html.toUtf8());
        file.close();
        QMessageBox::information(this,tr("操作成功"),tr("打印任务\n%1\n到文件\n%2\n成功!").arg(taskName).arg(fileName));
    }
}
void PTaskManager::ZSlotPrintPdf()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        return;//bypass tab0.
    }
    ZTaskWidget *task=qobject_cast<ZTaskWidget*>(this->m_tabWidget->currentWidget());
    if(task==NULL)
    {
        return;
    }
    QString taskName=task->m_sheet->ZGetTaskName();
    QString creator;
    QString createTime;
    for(qint32 i=0;i<this->m_taskList->m_tree->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=this->m_taskList->m_tree->topLevelItem(i);
        if(item->text(0)==taskName)
        {
            creator=item->text(5);
            createTime=item->text(6);
            break;
        }
    }
    QString note=QString("创建人:%1,创建时间:%2").arg(creator).arg(createTime);
    QString html;
    qint32 ret=ZGetQTableWidgetPdf(tr("任务:%1").arg(taskName),note,task->m_sheet,&html);
    if(ret<0)
    {
        return;
    }
    QString fileName=QFileDialog::getSaveFileName(this,tr("打印Pdf"),tr("./%1.pdf").arg(taskName),"*.pdf");
    if(fileName.isEmpty())
    {
        return;
    }

    QPrinter  printer;
    printer.setPageSize(QPrinter::A4);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument textDocument;
    textDocument.setHtml(html);
    textDocument.print(&printer);
}
void PTaskManager::ZSlotPrint()
{

}

void PTaskManager::ZSlotHelp()
{

}
void PTaskManager::ZSlotPopupMenu(const QPoint &pt)
{
    Q_UNUSED(pt);

    QMenu popMenu;
    QAction actNew(QIcon(":/TaskManager/images/TaskManager/AddTask.png"),tr("新建任务"));
    QAction actOpen(QIcon(":/TaskManager/images/TaskManager/MdyTask.png"),tr("打开任务"));
    QAction actDel(QIcon(":/TaskManager/images/TaskManager/DelTask.png"),tr("删除任务"));
    QAction actArchive(QIcon(":/TaskManager/images/TaskManager/DelTask.png"),tr("归档"));
    popMenu.addAction(&actNew);
    popMenu.addAction(&actOpen);
    popMenu.addAction(&actDel);
    popMenu.addSeparator();
    popMenu.addAction(&actArchive);
    connect(&actNew,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddTask()));
    connect(&actOpen,SIGNAL(triggered(bool)),this,SLOT(ZSlotMdyTask()));
    connect(&actDel,SIGNAL(triggered(bool)),this,SLOT(ZSlotDelTask()));
    connect(&actArchive,SIGNAL(triggered(bool)),this,SLOT(ZSlotArchieve()));


    QMenu subMenu(tr("审核"));
    QAction actSubmit(QIcon(":/TaskManager/images/TaskManager/SubmitTask.png"),tr("提交审核"));
    QAction actWithdraw(QIcon(":/TaskManager/images/TaskManager/WithdrawTask.png"),tr("撤回审核"));
    QAction actPass(QIcon(":/TaskManager/images/TaskManager/SubmitTask.png"),tr("审核通过"));
    QAction actFailed(QIcon(":/TaskManager/images/TaskManager/WithdrawTask.png"),tr("审核驳回"));
    subMenu.addAction(&actSubmit);
    subMenu.addAction(&actWithdraw);
    subMenu.addAction(&actPass);
    subMenu.addAction(&actFailed);
    connect(&actSubmit,SIGNAL(triggered(bool)),this,SLOT(ZSlotSubmitTask()));
    connect(&actWithdraw,SIGNAL(triggered(bool)),this,SLOT(ZSlotWithdrawTask()));
    connect(&actPass,SIGNAL(triggered(bool)),this,SLOT(ZSlotCheckOkay()));
    connect(&actFailed,SIGNAL(triggered(bool)),this,SLOT(ZSlotCheckFailed()));

    popMenu.addSeparator();
    popMenu.addMenu(&subMenu);
    popMenu.exec(QCursor::pos());
}
