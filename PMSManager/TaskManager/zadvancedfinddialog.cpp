#include "zadvancedfinddialog.h"
#include "TaskManager/zlisttaskdia.h"
#include "TaskManager/ptaskmanager.h"
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QTimer>
ZAdvancedFindDialog::ZAdvancedFindDialog()
{
    this->setWindowTitle(tr("高级任务查找"));

    this->m_checkMachineNo=new QCheckBox(tr("根据生产线/机器号"));
    this->m_cbMachineNo=new QComboBox;
    this->m_cbMachineNo->setEditable(true);
    this->m_cbMachineNo->setMinimumWidth(150);

    this->m_checkClass=new QCheckBox(tr("根据班组"));
    this->m_cbClass=new QComboBox;
    this->m_cbClass->setEditable(true);
    this->m_cbClass->setMinimumWidth(150);

    this->m_checkOrderNo=new QCheckBox(tr("根据订单号"));
    this->m_cbOrderNo=new QComboBox;
    this->m_cbOrderNo->setEditable(true);
    this->m_cbOrderNo->setMinimumWidth(150);

    this->m_checkProductNo=new QCheckBox(tr("根据产品号"));
    this->m_cbProductNo=new QComboBox;
    this->m_cbProductNo->setEditable(true);
    this->m_cbProductNo->setMinimumWidth(150);

    this->m_checkStartEndTime=new QCheckBox(tr("根据时间段"));
    this->m_deStart=new QDateTimeEdit;
    this->m_deStart->setCalendarPopup(true);
    this->m_deStart->setDateTime(QDateTime::currentDateTime());
    this->m_deEnd=new QDateTimeEdit;
    this->m_deEnd->setCalendarPopup(true);
    this->m_deEnd->setDateTime(QDateTime::currentDateTime());

    this->m_tbFind=new QToolButton;
    this->m_tbFind->setText(tr("查找"));
    this->m_tbFind->setIcon(QIcon(":/TaskManager/images/TaskManager/search.png"));
    this->m_tbFind->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(this->m_tbFind,SIGNAL(clicked(bool)),this,SLOT(ZSlotFind()));

    this->m_gLayout=new QGridLayout;
    this->m_gLayout->addWidget(this->m_checkMachineNo,0,0,1,1);
    this->m_gLayout->addWidget(this->m_cbMachineNo,0,1,1,1);

    this->m_gLayout->addWidget(this->m_checkClass,0,2,1,1);
    this->m_gLayout->addWidget(this->m_cbClass,0,3,1,1);

    this->m_gLayout->addWidget(this->m_checkOrderNo,0,4,1,1);
    this->m_gLayout->addWidget(this->m_cbOrderNo,0,5,1,1);

    this->m_gLayout->addWidget(this->m_checkProductNo,0,6,1,1);
    this->m_gLayout->addWidget(this->m_cbProductNo,0,7,1,1);

    this->m_gLayout->addWidget(this->m_checkStartEndTime,1,0,1,1);
    this->m_gLayout->addWidget(this->m_deStart,1,1,1,1);
    this->m_gLayout->addWidget(this->m_deEnd,1,2,1,1);
    this->m_gLayout->addWidget(this->m_tbFind,1,7,1,1,Qt::AlignRight);
    this->m_grpBox=new QGroupBox(tr("查找依据"));
    this->m_grpBox->setLayout(this->m_gLayout);

    this->m_tree=new QTreeWidget;
    this->m_tree->setContextMenuPolicy(Qt::CustomContextMenu);
    this->m_tree->setColumnCount(8);
    QStringList labels;
    labels<<tr("序号");
    labels<<tr("任务名");
    labels<<tr("生产线/机器号");
    labels<<tr("班组");
    labels<<tr("订单号");
    labels<<tr("产品号");
    labels<<tr("创建者");
    labels<<tr("创建时间");
    this->m_tree->setHeaderLabels(labels);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_grpBox);
    this->m_vLayout->addWidget(this->m_tree);
    this->setLayout(this->m_vLayout);

    connect(this->m_tree,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ZSlotPopupMenu(QPoint)));


    QTimer::singleShot(1000,this,SLOT(ZSlotLoadPresetValues()));
}
ZAdvancedFindDialog::~ZAdvancedFindDialog()
{
    delete this->m_checkMachineNo;
    delete this->m_cbMachineNo;

    delete this->m_checkClass;
    delete this->m_cbClass;

    delete this->m_checkOrderNo;
    delete this->m_cbOrderNo;

    delete this->m_checkProductNo;
    delete this->m_cbProductNo;

    delete this->m_checkStartEndTime;
    delete this->m_deStart;
    delete this->m_deEnd;
    delete this->m_tbFind;

    delete this->m_gLayout;
    delete this->m_grpBox;

    delete this->m_tree;
    delete this->m_vLayout;
}
void ZAdvancedFindDialog::ZSlotLoadPresetValues()
{
    //载入预置输入项，减少用户操作键盘。
    ZProductLinePresetDialog PLDia;
    QStringList lstPL=PLDia.ZReadList();
    for(qint32 i=0;i<lstPL.size();i++)
    {
        this->m_cbMachineNo->addItem(QIcon(":/TaskManager/images/TaskManager/ProductLine.png"),lstPL.at(i));
    }
    //载入预置输入项，减少用户操作键盘。
    ZClassPresetDialog classDia;
    QStringList lstClass=classDia.ZReadList();
    for(qint32 i=0;i<lstClass.size();i++)
    {
        this->m_cbClass->addItem(QIcon(":/TaskManager/images/TaskManager/Class.png"),lstClass.at(i));
    }
    //载入预置输入项，减少用户操作键盘。
    ZOrderNoPresetDialog orderNoDia;
    QStringList lstOrderNo=orderNoDia.ZReadList();
    for(qint32 i=0;i<lstOrderNo.size();i++)
    {
        this->m_cbOrderNo->addItem(QIcon(":/TaskManager/images/TaskManager/OrderNo.png"),lstOrderNo.at(i));
    }
    //载入预置输入项，减少用户操作键盘。
    ZProductNoPresetDialog productNoDia;
    QStringList lstProductNo=productNoDia.ZReadList();
    for(qint32 i=0;i<lstProductNo.size();i++)
    {
        this->m_cbProductNo->addItem(QIcon(":/TaskManager/images/TaskManager/ProductNo.png"),lstProductNo.at(i));
    }
}
QSize ZAdvancedFindDialog::sizeHint() const
{
    return QSize(1000,400);
}
void ZAdvancedFindDialog::ZProcessAckNetFrm(QString item, QString cmd, QStringList paraList, qint32 ackNetRetCode)
{
    if(item=="task")
    {
        if(cmd=="find")
        {
            if(ackNetRetCode<0)
            {
                QString errMsg=paraList.at(0);
                QMessageBox::critical(this,tr("错误提示"),errMsg);
            }else{
                QString taskName=paraList.at(0);
                QString machineNo=paraList.at(1);
                QString classNo=paraList.at(2);
                QString orderNo=paraList.at(3);
                QString productNo=paraList.at(4);
                QString creator=paraList.at(5);
                QString createTime=paraList.at(6);
                QTreeWidgetItem *item=new QTreeWidgetItem;
                item->setText(0,QString::number(this->m_tree->topLevelItemCount()+1));
                item->setText(1,taskName);
                item->setText(2,machineNo);
                item->setText(3,classNo);
                item->setText(4,orderNo);
                item->setText(5,productNo);
                item->setText(6,creator);
                item->setText(7,createTime);
                this->m_tree->addTopLevelItem(item);
            }
        }
    }
}
void ZAdvancedFindDialog::ZSlotFind()
{
    QString machineNo;
    QString classNo;
    QString orderNo;
    QString productNo;
    QString startTime;
    QString endTime;

    if(!this->m_checkMachineNo->isChecked() && !this->m_checkClass->isChecked() && !this->m_checkOrderNo->isChecked() && !this->m_checkProductNo->isChecked())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("根据什么进行查询呀? 无查找条件!"));
        return;
    }

    if(this->m_checkMachineNo->isChecked())
    {
        machineNo=this->m_cbMachineNo->currentText();
        if(machineNo.isEmpty())
        {
            QMessageBox::critical(this,tr("错误提示"),tr("根据生产线/机器号查询，无查找条件!"));
            return;
        }
    }
    if(this->m_checkClass->isChecked())
    {
        classNo=this->m_cbClass->currentText();
        if(classNo.isEmpty())
        {
            QMessageBox::critical(this,tr("错误提示"),tr("根据班组查询，无查找条件!"));
            return;
        }
    }
    if(this->m_checkOrderNo->isChecked())
    {
        orderNo=this->m_cbOrderNo->currentText();
        if(orderNo.isEmpty())
        {
            QMessageBox::critical(this,tr("错误提示"),tr("根据订单号查询，无查找条件!"));
            return;
        }
    }
    if(this->m_checkProductNo->isChecked())
    {
        productNo=this->m_cbProductNo->currentText();
        if(productNo.isEmpty())
        {
            QMessageBox::critical(this,tr("错误提示"),tr("根据产品号查询，无查找条件!"));
            return;
        }
    }
    if(this->m_checkStartEndTime->isChecked())
    {
        startTime=this->m_deStart->dateTime().toString("yyyyMMddhhmm");
        endTime=this->m_deEnd->dateTime().toString("yyyyMMddhhmm");
    }

    this->m_tree->clear();

    ZFindTaskDia *dia=new ZFindTaskDia(this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteFindOp(machineNo,classNo,orderNo,productNo,startTime,endTime);
    dia->ZShowWaitingDialog();
}
void ZAdvancedFindDialog::ZSlotPopupMenu(const QPoint &pt)
{
    Q_UNUSED(pt);
    QMenu popMenu;
    QAction actOpen(QIcon(":/TaskManager/images/TaskManager/MdyTask.png"),tr("查看任务"));
    QAction actExport(QIcon(":/UserManager/images/UserManager/Export.png"),tr("导出Excel"));
    QAction actRefresh(QIcon(":/TaskManager/images/TaskManager/search.png"),tr("刷新"));
    popMenu.addAction(&actOpen);
    popMenu.addAction(&actExport);
    popMenu.addAction(&actRefresh);
    popMenu.exec(QCursor::pos());
}
