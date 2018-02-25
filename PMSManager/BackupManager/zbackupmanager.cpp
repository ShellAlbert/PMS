#include "zbackupmanager.h"
#include <BackupManager/zbackupinfodia.h>
#include <BackupManager/zlistbackupinfodia.h>
#include <QMessageBox>
ZBackupManager::ZBackupManager(QWidget *parent):QDialog(parent)
{
    this->setMinimumSize(600,300);
    this->setWindowTitle(tr("备份管理器-Backup Manager"));

    this->m_tree=new QTreeWidget;
    this->m_tree->setColumnCount(4);
    QStringList header;
    header<<tr("备份文件");
    header<<tr("数据大小");
    header<<tr("备份人");
    header<<tr("备份时间");
    this->m_tree->setHeaderLabels(header);
    this->m_tbBackup=new QToolButton;
    this->m_tbBackup->setText(tr("备份"));
    this->m_tbBackup->setIcon(QIcon(":/BackupManager/images/BackupManager/Backup.png"));
    this->m_tbBackup->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbDelete=new QToolButton;
    this->m_tbDelete->setText(tr("删除"));
    this->m_tbDelete->setIcon(QIcon(":/BackupManager/images/BackupManager/Backup.png"));
    this->m_tbDelete->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbRestore=new QToolButton;
    this->m_tbRestore->setText(tr("还原"));
    this->m_tbRestore->setIcon(QIcon(":/BackupManager/images/BackupManager/Restore.png"));
    this->m_tbRestore->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbClose=new QToolButton;
    this->m_tbClose->setText(tr("关闭"));
    this->m_tbClose->setIcon(QIcon(":/BackupManager/images/BackupManager/Close.png"));
    this->m_tbClose->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_tbBackup);
    this->m_hLayout->addWidget(this->m_tbDelete);
    this->m_hLayout->addWidget(this->m_tbRestore);
    this->m_hLayout->addWidget(this->m_tbClose);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_tree);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);

    connect(this->m_tbBackup,SIGNAL(clicked(bool)),this,SLOT(ZSlotBackup()));
    connect(this->m_tbDelete,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelete()));
    connect(this->m_tbRestore,SIGNAL(clicked(bool)),this,SLOT(ZSlotRestore()));
    connect(this->m_tbClose,SIGNAL(clicked(bool)),this,SLOT(accept()));

    //list all backups.
    ZListBackupInfoDia *dia=new ZListBackupInfoDia(this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteListOp();
    dia->ZShowWaitingDialog();
}
ZBackupManager::~ZBackupManager()
{
    delete this->m_tree;
    delete this->m_tbBackup;
    delete this->m_tbRestore;
    delete this->m_tbClose;
    delete this->m_hLayout;
    delete this->m_vLayout;
}
void ZBackupManager::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{
    if(item=="backup")
    {
        if(cmd=="list")
        {
            if(ackNetRetCode<0)
            {
                QString errMsg=paraList.at(0);
                QMessageBox::critical(this,tr("刷新失败"),tr("刷新备份列表失败!\n%1.").arg(errMsg));
            }else{
                QString backupName=paraList.at(0);
                qint32 fileSize=paraList.at(1).toInt();
                QString creator=paraList.at(2);
                QString createTime=paraList.at(3);
                QTreeWidgetItem *item=new QTreeWidgetItem;
                item->setText(0,backupName);
                item->setText(1,QString("%1 KB").arg(fileSize/1024));
                item->setText(2,creator);
                item->setText(3,createTime);
                this->m_tree->addTopLevelItem(item);
                this->m_tree->setCurrentItem(item);
                for(qint32 i=0;i<this->m_tree->columnCount();i++)
                {
                    this->m_tree->resizeColumnToContents(i);
                }
            }
        }else if(cmd=="backup")
        {
            if(ackNetRetCode<0)
            {
                QString backupName=paraList.at(0);
                QString errMsg=paraList.at(1);
                QMessageBox::critical(this,tr("备份失败"),tr("备份[%1]失败!\n%2.").arg(backupName).arg(errMsg));
            }else{
                QString backupName=paraList.at(0);
                qint32 fileSize=paraList.at(1).toInt();
                QString creator=paraList.at(2);
                QString createTime=paraList.at(3);
                QTreeWidgetItem *item=new QTreeWidgetItem;
                item->setText(0,backupName);
                item->setText(1,QString("%1 KB").arg(fileSize/1024));
                item->setText(2,creator);
                item->setText(3,createTime);
                this->m_tree->addTopLevelItem(item);
                this->m_tree->setCurrentItem(item);
            }
        }else if(cmd=="restore")
        {
            if(ackNetRetCode<0)
            {
                QString backupName=paraList.at(0);
                QString errMsg=paraList.at(1);
                QMessageBox::critical(this,tr("还原失败"),tr("还原备份[%1]失败!\n%2.").arg(backupName).arg(errMsg));
            }else{
                QString backupName=paraList.at(0);
                QMessageBox::information(this,tr("还原成功"),tr("PMS系统还原至备份[%1]成功!\n因数据库还原,故请重新登录!").arg(backupName));
                qApp->quit();
            }
        }else if(cmd=="delete")
        {
            if(ackNetRetCode<0)
            {
                QString backupName=paraList.at(0);
                QString errMsg=paraList.at(1);
                QMessageBox::critical(this,tr("删除备份失败"),tr("删除备份[%1]失败!\n%2.").arg(backupName).arg(errMsg));
            }else{
                QString backupName=paraList.at(0);
                for(qint32 i=0;i<this->m_tree->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_tree->topLevelItem(i);
                    if(item->text(0)==backupName)
                    {
                        this->m_tree->takeTopLevelItem(i);
                        delete item;
                        item=NULL;
                        break;
                    }
                }
            }
        }
    }
}
void ZBackupManager::ZSlotBackup()
{
    ZBackupInfoDia *dia=new ZBackupInfoDia(ZBackupInfoDia::Type_Backup,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetBackupName(tr("服务器端自动生成"));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void ZBackupManager::ZSlotRestore()
{
    QTreeWidgetItem *item=this->m_tree->currentItem();
    if(item==NULL)
    {
        return;
    }
    if(QMessageBox::question(this,tr("还原确认"),tr("您确认要还原备份[%1]吗?\n还原后当前数据都将被覆盖!").arg(item->text(0)),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
    {
        return;
    }
    ZBackupInfoDia *dia=new ZBackupInfoDia(ZBackupInfoDia::Type_Restore,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetBackupName(item->text(0));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void ZBackupManager::ZSlotDelete()
{
    QTreeWidgetItem *item=this->m_tree->currentItem();
    if(item==NULL)
    {
        return;
    }
    if(QMessageBox::question(this,tr("删除确认"),tr("您确认要删除备份[%1]吗?\n删除不可恢复!").arg(item->text(0)),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
    {
        return;
    }
    ZBackupInfoDia *dia=new ZBackupInfoDia(ZBackupInfoDia::Type_Delete,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetBackupName(item->text(0));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
