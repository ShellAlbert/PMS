#include "pprocesseditor.h"
#include <QMessageBox>
#include <QDateTime>
#include "pgblpara.h"
#include <ProcessEditor/zprocessinfodia.h>
#include <ProcessEditor/zlistprocessinfodia.h>
#include <QXmlStreamWriter>
#include <QInputDialog>
ZProcessManager::ZProcessManager()
{
    this->m_treeWidget=new QTreeWidget;
    this->m_treeWidget->setIconSize(QSize(24,24));
    this->m_treeWidget->setColumnCount(4);
    QStringList headerList;
    headerList<<tr("工序名称");
    headerList<<tr("步序数目");
    headerList<<tr("创建者");
    headerList<<tr("创建时间");
    this->m_treeWidget->setHeaderLabels(headerList);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_treeWidget);
    this->setLayout(this->m_vLayout);

    connect(this->m_treeWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ZSlotDblClickProcess(QModelIndex)));
}
ZProcessManager::~ZProcessManager()
{
    delete this->m_treeWidget;
    delete this->m_vLayout;
}
void ZProcessManager::ZSlotDblClickProcess(QModelIndex index)
{
    QTreeWidgetItem *item=this->m_treeWidget->topLevelItem(index.row());
    if(item)
    {
        emit this->ZSignalOpenProcess(item->text(0));
    }
}
ZProcessEditor::ZProcessEditor()
{
    this->setStyleSheet("QFrame{background-color:#D2A2CC;}");
    this->m_scrollWidget=new QFrame;
    this->m_scrollWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->m_scrollArea=new QScrollArea;
    this->m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->m_scrollArea->setWidgetResizable(true);
    this->m_scrollArea->setWidget(this->m_scrollWidget);
    this->m_gridLayout=new QGridLayout;
    this->m_scrollWidget->setLayout(this->m_gridLayout);
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_scrollArea);
    this->setLayout(this->m_vLayout);
}
ZProcessEditor::~ZProcessEditor()
{
    for(qint32 i=0;i<this->m_stepEditList.count();i++)
    {
        PStepEditor *edit=this->m_stepEditList.at(i);
        delete edit;
        edit=NULL;
    }
    delete this->m_gridLayout;
    delete this->m_scrollWidget;
    delete this->m_scrollArea;
    delete this->m_vLayout;
}
void ZProcessEditor::ZSetProcessName(QString name)
{
    this->m_processName=name;
}
QString ZProcessEditor::ZGetProcessName()
{
    return this->m_processName;
}
qint32 ZProcessEditor::ZGetStepCount()
{
    return this->m_stepEditList.count();
}
bool ZProcessEditor::ZIsAllStepsValidate()
{
    QList<QString> stepNameLst;
    for(qint32 i=0;i<this->m_stepEditList.count();i++)
    {
        PStepEditor *stepEdit=this->m_stepEditList.at(i);
        if(stepNameLst.contains(stepEdit->ZGetStepName()))
        {
            QMessageBox::critical(this,tr("错误提示"),tr("步序名必须唯一!\n发现重复的步序名[%1]!").arg(stepEdit->ZGetStepName()));
            return false;
        }else{
            stepNameLst.append(stepEdit->ZGetStepName());
        }
    }
    return true;
}
PStepEditor* ZProcessEditor::ZGetStepEditor(qint32 index)
{
    return this->m_stepEditList.at(index);
}
QString ZProcessEditor::ZGetProcessXmlData()
{
    QString xmlData;
    QXmlStreamWriter  tXmlWriter(&xmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Step"));
    for(qint32 i=0;i<this->m_stepEditList.count();i++)
    {
        PStepEditor *edit=this->m_stepEditList.at(i);
        QString stepName=edit->ZGetStepName();
        QStringList linkTemplates=edit->ZGetLinkTemplates();
        QStringList linkFiles=edit->ZGetLinkFiles();
        QStringList linkRoles=edit->ZGetLinkRoles();
        QString linkTemplatesStr;
        QString linkFilesStr;
        QString linkRolesStr;
        for(qint32 j=0;j<linkTemplates.count();j++)
        {
            linkTemplatesStr.append(linkTemplates.at(j)+":");
        }
        for(qint32 j=0;j<linkFiles.count();j++)
        {
            linkFilesStr.append(linkFiles.at(j)+":");
        }
        for(qint32 j=0;j<linkRoles.count();j++)
        {
            linkRolesStr.append(linkRoles.at(j)+":");
        }
        tXmlWriter.writeStartElement(QString("Step"));
        tXmlWriter.writeAttribute(QString("linktemplates"),linkTemplatesStr);
        tXmlWriter.writeAttribute(QString("linkfiles"),linkFilesStr);
        tXmlWriter.writeAttribute(QString("linkroles"),linkRolesStr);
        tXmlWriter.writeCharacters(stepName);
        tXmlWriter.writeEndElement();//Step.
    }
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
    return xmlData;
}
void ZProcessEditor::ZSetProcessXmlData(QString xmlData)
{
    QXmlStreamReader tXmlReader(xmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Step"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString linkTemplates=attr.value(QString("linktemplates")).toString();
                QString linkFiles=attr.value(QString("linkfiles")).toString();
                QString linkRoles=attr.value(QString("linkroles")).toString();
                QString stepName=tXmlReader.readElementText();
                PStepEditor* edit=this->ZAddStep();
                edit->ZSetStepName(stepName);
                QStringList linkTemplatesList=linkTemplates.split(":");
                QStringList linkFilesList=linkFiles.split(":");
                QStringList linkRolesList=linkRoles.split(":");
                edit->ZSetLinkTemplates(linkTemplatesList);
                edit->ZSetLinkFiles(linkFilesList);
                edit->ZSetLinkRoles(linkRolesList);
            }
        }
    }
}
void ZProcessEditor::ZSlotDataChanged()
{
    emit this->ZSignalDataChanged(this->m_processName);
}
PStepEditor* ZProcessEditor::ZAddStep()
{
    PStepEditor *edit=new PStepEditor;
    connect(edit,SIGNAL(ZSignalCloseMe(PStepEditor*)),this,SLOT(ZSlotRemoveStepEditor(PStepEditor*)));
    connect(edit,SIGNAL(ZSignalDataChanged()),this,SLOT(ZSlotDataChanged()));
    this->m_stepEditList.append(edit);
    edit->ZSetStepName(tr("step-%1").arg(this->m_stepEditList.count()));
    this->ZAutoRelayout();
    emit this->ZSignalLogMsg(tr("工序[%1]添加步序[%2],总步序数目:[%3]").arg(this->ZGetProcessName()).arg(edit->ZGetStepName()).arg(this->m_stepEditList.count()));
    emit this->ZSignalDataChanged(this->m_processName);
    return edit;
}
void ZProcessEditor::ZAutoRelayout()
{
    //re-layout.
    for(qint32 i=0;i<(this->m_stepEditList.count());i++)
    {
        this->m_gridLayout->removeItem(this->m_vLayout->itemAt(i));
        this->m_gridLayout->setRowStretch(i,0);
    }

    //re-layout.
    qint32 tColCount=0;
    qint32 tRowCount=0;
    for(qint32 i=0;i<this->m_stepEditList.count();i++)
    {
        PStepEditor *stepEdit=this->m_stepEditList.at(i);
        this->m_gridLayout->addWidget(stepEdit,tRowCount,tColCount);
        tColCount++;//move to next column.
        if(tColCount%6==0)
        {
            tRowCount++;//move to next row.
            tColCount=0;//reset the column to 0.
        }
    }
}
void ZProcessEditor::ZSlotRemoveStepEditor(PStepEditor* edit)
{
    if(QMessageBox::question(this,tr("操作确认"),tr("您确认要删除步序吗?"),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
    {
        return;
    }
    for(qint32 i=0;i<this->m_stepEditList.count();i++)
    {
        if(this->m_stepEditList.at(i)==edit)
        {
            this->m_stepEditList.removeAt(i);
            emit this->ZSignalLogMsg(tr("删除工序[%1]中的步序[%2]").arg(this->ZGetProcessName()));
            delete edit;
            edit=NULL;
            //re-layout.
            this->ZAutoRelayout();
            break;
        }
    }
    emit this->ZSignalDataChanged(this->m_processName);
}


PProcessEditor::PProcessEditor()
{
    this->setWindowTitle(tr("工序管理器-Process Editor"));
    this->setWindowIcon(QIcon(":/TaskBar/images/ProcessEditor.png"));
//    this->setStyleSheet("QToolButton{background-color:#cce5f9;font:color #eaf7ff;padding: 6px 12px 6px 12p}"
//                        "QToolButton::hover{background-color:#eaf7ff;}"
//                        "");
    this->setStyleSheet("QToolButton{background-color:#cce5f9;border:none;font:color #eaf7ff;}"
                        "QToolButton::hover{background-color:#eaf7ff;}"
                        "");
    this->m_vLayoutTb=new QVBoxLayout;
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_processEditPerm&PermBits_ProcessEditor_NewProcess)
    {
        this->m_tbNewProcess=new QToolButton;
        this->m_tbNewProcess->setToolTip(tr("新建工序"));
        this->m_tbNewProcess->setText(tr("新建"));
        this->m_tbNewProcess->setIcon(QIcon(":/ProcessEditor/images/ProcessEditor/AddProcess.png"));
        this->m_tbNewProcess->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutTb->addWidget(this->m_tbNewProcess);
        connect(this->m_tbNewProcess,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddProcess()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_processEditPerm&PermBits_ProcessEditor_MdyProcess)
    {
        this->m_tbOpenProcess=new QToolButton;
        this->m_tbOpenProcess->setToolTip(tr("打开工序"));
        this->m_tbOpenProcess->setText(tr("打开"));
        this->m_tbOpenProcess->setIcon(QIcon(":/ProcessEditor/images/ProcessEditor/OpenProcess.png"));
        this->m_tbOpenProcess->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        this->m_tbSaveProcess=new QToolButton;
        this->m_tbSaveProcess->setToolTip(tr("保存工序"));
        this->m_tbSaveProcess->setText(tr("保存"));
        this->m_tbSaveProcess->setIcon(QIcon(":/ProcessEditor/images/ProcessEditor/SaveProcess.png"));
        this->m_tbSaveProcess->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        this->m_tbSaveAsProcess=new QToolButton;
        this->m_tbSaveAsProcess->setToolTip(tr("另存为..."));
        this->m_tbSaveAsProcess->setText(tr("另存"));
        this->m_tbSaveAsProcess->setIcon(QIcon(":/ProcessEditor/images/ProcessEditor/SaveAsProcess.png"));
        this->m_tbSaveAsProcess->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        this->m_tbNewStep=new QToolButton;
        this->m_tbNewStep->setToolTip(tr("添加步序"));
        this->m_tbNewStep->setText(tr("步序"));
        this->m_tbNewStep->setIcon(QIcon(":/ProcessEditor/images/ProcessEditor/AddStep.png"));
        this->m_tbNewStep->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutTb->addWidget(this->m_tbOpenProcess);
        this->m_vLayoutTb->addWidget(this->m_tbSaveProcess);
        this->m_vLayoutTb->addWidget(this->m_tbSaveAsProcess);
        this->m_vLayoutTb->addWidget(this->m_tbNewStep);

        connect(this->m_tbOpenProcess,SIGNAL(clicked(bool)),this,SLOT(ZSlotOpenProcess()));
        connect(this->m_tbSaveProcess,SIGNAL(clicked(bool)),this,SLOT(ZSlotSaveProcess()));
        connect(this->m_tbSaveAsProcess,SIGNAL(clicked(bool)),this,SLOT(ZSlotSaveAsProcess()));
        connect(this->m_tbNewStep,SIGNAL(clicked(bool)),this,SLOT(ZSlotAddStep()));
    }

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_processEditPerm&PermBits_ProcessEditor_DelProcess)
    {
        this->m_tbDelProcess=new QToolButton;
        this->m_tbDelProcess->setToolTip(tr("删除工序"));
        this->m_tbDelProcess->setText(tr("删除"));
        this->m_tbDelProcess->setIcon(QIcon(":/ProcessEditor/images/ProcessEditor/DelProcess.png"));
        this->m_tbDelProcess->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        this->m_vLayoutTb->addWidget(this->m_tbDelProcess);
        connect(this->m_tbDelProcess,SIGNAL(clicked(bool)),this,SLOT(ZSlotDelProcess()));
    }
    this->m_vLayoutTb->addStretch(1);

    //help.
    this->m_tbHelp=new QToolButton;
    this->m_tbHelp->setToolTip(tr("获取帮助文档"));
    this->m_tbHelp->setText(tr("帮助"));
    this->m_tbHelp->setIcon(QIcon(":/common/images/common/help.png"));
    this->m_tbHelp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(this->m_tbHelp,SIGNAL(clicked(bool)),this,SLOT(ZSlotHelp()));
    this->m_vLayoutTb->addWidget(this->m_tbHelp);

    //right.
    this->m_tabWidget=new QTabWidget;
    this->m_tabWidget->setTabsClosable(true);
    this->m_processManager=new ZProcessManager;
    this->m_tabWidget->addTab(this->m_processManager,QIcon(":/ProcessEditor/images/ProcessEditor/Process.png"),tr("工序管理"));
    //main.
    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addLayout(this->m_vLayoutTb);
    this->m_hLayout->addWidget(this->m_tabWidget);
    this->setLayout(this->m_hLayout);

    connect(this->m_tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(ZSlotRemoveTab(qint32)));
    connect(this->m_processManager,SIGNAL(ZSignalOpenProcess(QString)),this,SLOT(ZSlotOpenProcess(QString)));

    ZListProcessInfoDia *dia=new ZListProcessInfoDia;
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteListOp();
    dia->ZShowWaitingDialog();
}
PProcessEditor::~PProcessEditor()
{
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_processEditPerm&PermBits_ProcessEditor_NewProcess)
    {
        delete this->m_tbNewProcess;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_processEditPerm&PermBits_ProcessEditor_MdyProcess)
    {
        delete this->m_tbOpenProcess;
        delete this->m_tbSaveProcess;
        delete this->m_tbSaveAsProcess;
        delete this->m_tbNewStep;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_processEditPerm&PermBits_ProcessEditor_DelProcess)
    {
        delete this->m_tbDelProcess;
    }
    delete this->m_tbHelp;
    delete this->m_vLayoutTb;
    //right.
    delete this->m_processManager;
    for(qint32 i=1;i<this->m_tabWidget->count();i++)
    {
        delete this->m_tabWidget->widget(i);
    }
    delete this->m_tabWidget;
    //main.
    delete this->m_hLayout;
}
void PProcessEditor::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{
    if(item=="process")
    {
        if(cmd=="add")
        {
            QString processName=paraList.at(0);
            QString creator=paraList.at(1);
            QString createTime=paraList.at(2);
            QString errMsg=paraList.at(3);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("add process [%1] failed:[%2].").arg(processName).arg(errMsg));
            }else{
                //add new item in tree.
                QTreeWidgetItem *processItem=new QTreeWidgetItem(0);//type,0 is process,1 is step.
                processItem->setIcon(0,QIcon(":/ProcessEditor/images/ProcessEditor/Process.png"));
                processItem->setText(0,processName);
                processItem->setText(1,QString("0"));
                processItem->setText(2,creator);
                processItem->setText(3,createTime);
                this->m_processManager->m_treeWidget->addTopLevelItem(processItem);

                //open for editing.
                ZProcessEditor *edit=new ZProcessEditor;
                edit->ZSetProcessName(processName);
                connect(edit,SIGNAL(ZSignalDataChanged(QString)),this,SLOT(ZSlotDataChanged(QString)));
                this->m_tabWidget->addTab(edit,QIcon(":/ProcessEditor/images/ProcessEditor/Process.png"),processName);
                this->m_tabWidget->setCurrentWidget(edit);
                this->ZAddLogMsg(tr("add process [%1] success.").arg(processName));
            }
        }else if(cmd=="del")
        {
            QString processName=paraList.at(0);
            QString errMsg=paraList.at(1);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("delete process [%1] failed:[%2].").arg(processName).arg(errMsg));
            }else{
                //close it if it is open.
                for(qint32 i=1;i<this->m_tabWidget->count();i++)
                {
                    if(this->m_tabWidget->tabText(i)==processName)
                    {
                        QWidget *widget=this->m_tabWidget->widget(i);
                        this->m_tabWidget->removeTab(i);
                        delete widget;
                        widget=NULL;
                        break;
                    }
                }
                //search the tree and delete item.
                for(qint32 i=0;i<this->m_processManager->m_treeWidget->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_processManager->m_treeWidget->topLevelItem(i);
                    if(item->type()==0 && item->text(0)==processName)
                    {
                        this->m_processManager->m_treeWidget->takeTopLevelItem(i);
                        delete item;
                        item=NULL;
                        break;
                    }
                }
                this->ZAddLogMsg(tr("delete process [%1] success.").arg(processName));
            }
        }else if(cmd=="save")
        {
            QString processName=paraList.at(0);
            QString stepNum=paraList.at(1);
            QString errMsg=paraList.at(2);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("save process [%1] failed:[%2].").arg(processName).arg(errMsg));
            }else{
                //update stepNum in the tree.
                for(qint32 i=0;i<this->m_processManager->m_treeWidget->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_processManager->m_treeWidget->topLevelItem(i);
                    if(item->text(0)==processName)
                    {
                        item->setText(1,stepNum);
                        break;
                    }
                }
                //remove <*> from the tab.
                for(qint32 i=1;i<this->m_tabWidget->count();i++)
                {
                    QString name=this->m_tabWidget->tabText(i);
                    if(name.startsWith("<*>"))
                    {\
                        this->m_tabWidget->setTabText(i,name.mid(3));
                        break;
                    }
                }
                this->ZAddLogMsg(tr("save process [%1] success.").arg(processName));
            }
        }else if(cmd=="get")
        {
            QString processName=paraList.at(0);
            QString data=paraList.at(1);
            QString errMsg=paraList.at(2);
            if(ackNetRetCode<0)
            {
                //open a empty processedit for editing.
                ZProcessEditor *edit=new ZProcessEditor;
                edit->ZSetProcessName(processName);
                connect(edit,SIGNAL(ZSignalDataChanged(QString)),this,SLOT(ZSlotDataChanged(QString)));
                this->m_tabWidget->addTab(edit,QIcon(":/ProcessEditor/images/ProcessEditor/Process.png"),processName);
                this->m_tabWidget->setCurrentWidget(edit);

                this->ZAddLogMsg(tr("get process [%1] failed:[%2].").arg(processName).arg(errMsg));
            }else{
                ZProcessEditor *edit=new ZProcessEditor;
                edit->ZSetProcessName(processName);
                edit->ZSetProcessXmlData(QString(QByteArray::fromBase64(data.toUtf8())));
                connect(edit,SIGNAL(ZSignalDataChanged(QString)),this,SLOT(ZSlotDataChanged(QString)));
                this->m_tabWidget->addTab(edit,QIcon(":/ProcessEditor/images/ProcessEditor/Process.png"),processName);
                this->m_tabWidget->setCurrentWidget(edit);
                this->ZAddLogMsg(tr("get process [%1] success.").arg(processName));
            }
        }else if(cmd=="list")
        {
            QString processName=paraList.at(0);
            QString stepNum=paraList.at(1);
            QString errMsg=paraList.at(2);
            QString creator=paraList.at(3);
            QString createTime=paraList.at(4);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("list process [%1] failed:[%2].").arg(processName).arg(errMsg));
            }else{
                //add item to tree.
                QTreeWidgetItem *item=new QTreeWidgetItem;
                item->setIcon(0,QIcon(":/ProcessEditor/images/ProcessEditor/Process.png"));
                item->setText(0,processName);
                item->setText(1,stepNum);
                item->setText(2,creator);
                item->setText(3,createTime);
                this->m_processManager->m_treeWidget->addTopLevelItem(item);
                this->m_processManager->m_treeWidget->setCurrentItem(item);
                this->ZAddLogMsg(tr("list process [%1] success.").arg(processName));
                for(qint32 i=0;i<this->m_processManager->m_treeWidget->columnCount();i++)
                {
                    this->m_processManager->m_treeWidget->resizeColumnToContents(i);
                }
            }
        }
    }
}
void PProcessEditor::closeEvent(QCloseEvent *event)
{
    emit this->ZSignalCloseEvent("ProcessEditor");
    QFrame::closeEvent(event);
}
void PProcessEditor::ZSlotAddProcess()
{
    ZProcessInfoDia *dia=new ZProcessInfoDia(ZProcessInfoDia::Type_NewProcess,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PProcessEditor::ZSlotOpenProcess()
{
    QTreeWidgetItem *item=this->m_processManager->m_treeWidget->currentItem();
    if(item==NULL)
    {
        return;
    }
    ZProcessInfoDia *dia=new ZProcessInfoDia(ZProcessInfoDia::Type_GetProcess,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetProcessName(item->text(0));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PProcessEditor::ZSlotSaveProcess()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass tab0 page.
        return;
    }
    ZProcessEditor *processEdit=qobject_cast<ZProcessEditor*>(this->m_tabWidget->currentWidget());
    if(processEdit==NULL)
    {
        return;
    }
    if(processEdit->ZGetStepCount()<=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("当前工序包含的步序数目为0,无需保存!"));
        return;
    }
    if(!processEdit->ZIsAllStepsValidate())
    {
        return;
    }
    //save process.
    ZProcessInfoDia *dia=new ZProcessInfoDia(ZProcessInfoDia::Type_SaveProcess,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetProcessName(processEdit->ZGetProcessName());
    dia->ZSetProcessXmlData(processEdit->ZGetProcessXmlData());
    dia->ZSetStepNum(processEdit->ZGetStepCount());
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PProcessEditor::ZSlotSaveAsProcess()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass tab0 page.
        return;
    }
    ZProcessEditor *processEdit=qobject_cast<ZProcessEditor*>(this->m_tabWidget->currentWidget());
    if(processEdit==NULL)
    {
        return;
    }
    if(processEdit->ZGetStepCount()<=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("当前工序包含的步序数目为0,无需保存!"));
        return;
    }
    if(!processEdit->ZIsAllStepsValidate())
    {
        return;
    }

    QString processName=QInputDialog::getText(this,tr("工序另存为"),tr("新的工序名称"));
    if(processName.isEmpty())
    {
        return;
    }

}
void PProcessEditor::ZSlotDelProcess()
{
    //bypass tab0.
    if(this->m_tabWidget->currentIndex()!=0)
    {
        return;
    }
    QTreeWidgetItem *processItem=this->m_processManager->m_treeWidget->currentItem();
    if(processItem==NULL)
    {
        return;
    }
    if(processItem->type()!=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请选择要删除的工序!\n当前选择为步序!"));
        return;
    }
    QString processName=processItem->text(0);
    if(QMessageBox::question(this,tr("操作确认"),tr("您确认要删除工序[%1]吗?").arg(processName),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        ZProcessInfoDia *dia=new ZProcessInfoDia(ZProcessInfoDia::Type_DelProcess,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetProcessName(processName);
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
void PProcessEditor::ZSlotAddStep()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass tab0,tab0 is processManager.
        return;
    }
    ZProcessEditor *edit=qobject_cast<ZProcessEditor*>(this->m_tabWidget->currentWidget());
    if(edit==NULL)
    {
        return;
    }
    edit->ZAddStep();
    this->ZAddLogMsg(tr("process [%1] add a new step").arg(edit->ZGetProcessName()));
}
void PProcessEditor::ZSlotRemoveTab(qint32 index)
{
    if(index==0)
    {
        //make sure the tab0 cannot be closed.
        return;
    }

    if(this->m_tabWidget->tabText(index).startsWith("<*>"))
    {
        if(QMessageBox::question(this,tr("操作提示"),tr("模板已被修改,但未保存!\n您确认要关闭吗?"),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
        {
            return;
        }
    }

    ZProcessEditor *edit=qobject_cast<ZProcessEditor*>(this->m_tabWidget->widget(index));
    if(!edit)
    {
        return;
    }
    //delete it to remove it from tab widget.
    this->m_tabWidget->removeTab(index);
    delete this->m_tabWidget->widget(index);
}
void PProcessEditor::ZSlotDataChanged(QString processName)
{
    for(qint32 i=0;i<this->m_tabWidget->count();i++)
    {
        if(this->m_tabWidget->tabText(i)==processName)
        {
            this->m_tabWidget->setTabText(i,"<*>"+processName);
            break;
        }
    }
}
void PProcessEditor::ZSlotOpenProcess(QString processName)
{
    ZProcessInfoDia *dia=new ZProcessInfoDia(ZProcessInfoDia::Type_GetProcess,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetProcessName(processName);
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PProcessEditor::ZSlotHelp()
{

}
void PProcessEditor::ZAddLogMsg(QString logMsg)
{
    emit this->ZSignalLogMsg(QString("<ProcessEditor>:")+logMsg);
}

