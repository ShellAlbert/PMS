#include "zgrpinfodia.h"
#include <QMessageBox>
#include "pgblpara.h"
#include "NetProtocol/pnetframe.h"
#include <QDebug>
#include <QXmlStreamReader>
ZUserManagerPerm::ZUserManagerPerm()
{
    this->m_cbNewGrp=new QCheckBox(tr("创建角色"));
    this->m_cbMdyGrp=new QCheckBox(tr("编辑角色"));
    this->m_cbDelGrp=new QCheckBox(tr("删除角色"));

    this->m_cbNewUser=new QCheckBox(tr("创建用户"));
    this->m_cbMdyUser=new QCheckBox(tr("编辑用户"));
    this->m_cbDelUser=new QCheckBox(tr("删除用户"));

    this->m_cbImport=new QCheckBox(tr("导入"));
    this->m_cbExport=new QCheckBox(tr("导出"));

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_cbNewGrp,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbMdyGrp,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_cbDelGrp,0,2,1,1);

    this->m_gridLayout->addWidget(this->m_cbNewUser,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbMdyUser,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_cbDelUser,1,2,1,1);

    this->m_gridLayout->addWidget(this->m_cbImport,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbExport,2,1,1,1);

    this->setLayout(this->m_gridLayout);
}
ZUserManagerPerm::~ZUserManagerPerm()
{
    delete this->m_cbNewGrp;
    delete this->m_cbMdyGrp;
    delete this->m_cbDelGrp;

    delete this->m_cbNewUser;
    delete this->m_cbMdyUser;
    delete this->m_cbDelUser;

    delete this->m_cbImport;
    delete this->m_cbExport;

    delete this->m_gridLayout;
}

void ZUserManagerPerm::ZSetPermBits(qint32 permBits)
{
    if(permBits&PermBits_UserManager_AddGrp)
    {
        this->m_cbNewGrp->setChecked(true);
    }
    if(permBits&PermBits_UserManager_MdyGrp)
    {
        this->m_cbMdyGrp->setChecked(true);
    }
    if(permBits&PermBits_UserManager_DelGrp)
    {
        this->m_cbDelGrp->setChecked(true);
    }

    if(permBits&PermBits_UserManager_AddUser)
    {
        this->m_cbNewUser->setChecked(true);
    }
    if(permBits&PermBits_UserManager_MdyUser)
    {
        this->m_cbMdyUser->setChecked(true);
    }
    if(permBits&PermBits_UserManager_DelUser)
    {
        this->m_cbDelUser->setChecked(true);
    }

    if(permBits&PermBits_UserManager_Import)
    {
        this->m_cbImport->setChecked(true);
    }
    if(permBits&PermBits_UserManager_Export)
    {
        this->m_cbExport->setChecked(true);
    }
}
qint32 ZUserManagerPerm::ZGetPermBits()
{
    qint32 permBits=0;
    if(this->m_cbNewGrp->isChecked())
    {
        permBits|=PermBits_UserManager_AddGrp;
    }
    if(this->m_cbMdyGrp->isChecked())
    {
        permBits|=PermBits_UserManager_MdyGrp;
    }
    if(this->m_cbDelGrp->isChecked())
    {
        permBits|=PermBits_UserManager_DelGrp;
    }

    if(this->m_cbNewUser->isChecked())
    {
        permBits|=PermBits_UserManager_AddUser;
    }
    if(this->m_cbMdyUser->isChecked())
    {
        permBits|=PermBits_UserManager_MdyUser;
    }
    if(this->m_cbDelUser->isChecked())
    {
        permBits|=PermBits_UserManager_DelUser;
    }

    if(this->m_cbImport->isChecked())
    {
        permBits|=PermBits_UserManager_Import;
    }
    if(this->m_cbExport->isChecked())
    {
        permBits|=PermBits_UserManager_Export;
    }
    return permBits;
}
ZTemplateEditorPerm::ZTemplateEditorPerm()
{
    this->m_cbNewTem=new QCheckBox(tr("创建模板"));
    this->m_cbMdyTem=new QCheckBox(tr("编辑模板"));
    this->m_cbDelTem=new QCheckBox(tr("删除模板"));

    this->m_cbNewVarSrc=new QCheckBox(tr("创建变量源"));
    this->m_cbMdyVarSrc=new QCheckBox(tr("编辑变量源"));
    this->m_cbDelVarSrc=new QCheckBox(tr("删除变量源"));

    this->m_cbImport=new QCheckBox(tr("导入模板"));
    this->m_cbExport=new QCheckBox(tr("导出模板"));

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_cbNewTem,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbMdyTem,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_cbDelTem,0,2,1,1);

    this->m_gridLayout->addWidget(this->m_cbNewVarSrc,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbMdyVarSrc,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_cbDelVarSrc,1,2,1,1);

    this->m_gridLayout->addWidget(this->m_cbImport,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbExport,2,1,1,1);
    this->setLayout(this->m_gridLayout);
}
ZTemplateEditorPerm::~ZTemplateEditorPerm()
{
    delete this->m_cbNewTem;
    delete this->m_cbMdyTem;
    delete this->m_cbDelTem;

    delete this->m_cbNewVarSrc;
    delete this->m_cbMdyVarSrc;
    delete this->m_cbDelVarSrc;

    delete this->m_cbImport;
    delete this->m_cbExport;

    delete this->m_gridLayout;
}
void ZTemplateEditorPerm::ZSetPermBits(qint32 permBits)
{
    if(permBits&PermBits_TemplateEditor_AddTemplate)
    {
        this->m_cbNewTem->setChecked(true);
    }
    if(permBits&PermBits_TemplateEditor_MdyTemplate)
    {
        this->m_cbMdyTem->setChecked(true);
    }
    if(permBits&PermBits_TemplateEditor_DelTemplate)
    {
        this->m_cbDelTem->setChecked(true);
    }

    if(permBits&PermBits_TemplateEditor_AddVarSrc)
    {
        this->m_cbNewVarSrc->setChecked(true);
    }
    if(permBits&PermBits_TemplateEditor_MdyVarSrc)
    {
        this->m_cbMdyVarSrc->setChecked(true);
    }
    if(permBits&PermBits_TemplateEditor_DelVarSrc)
    {
        this->m_cbDelVarSrc->setChecked(true);
    }

    if(permBits&PermBits_TemplateEditor_Import)
    {
        this->m_cbImport->setChecked(true);
    }
    if(permBits&PermBits_TemplateEditor_Export)
    {
        this->m_cbExport->setChecked(true);
    }
}
qint32 ZTemplateEditorPerm::ZGetPermBits()
{
    qint32 permBits=0;
    if(this->m_cbNewTem->isChecked())
    {
        permBits|=PermBits_TemplateEditor_AddTemplate;
    }
    if(this->m_cbMdyTem->isChecked())
    {
        permBits|=PermBits_TemplateEditor_MdyTemplate;
    }
    if(this->m_cbDelTem->isChecked())
    {
        permBits|=PermBits_TemplateEditor_DelTemplate;
    }

    if(this->m_cbNewVarSrc->isChecked())
    {
        permBits|=PermBits_TemplateEditor_AddVarSrc;
    }
    if(this->m_cbMdyVarSrc->isChecked())
    {
        permBits|=PermBits_TemplateEditor_MdyVarSrc;
    }
    if(this->m_cbDelVarSrc->isChecked())
    {
        permBits|=PermBits_TemplateEditor_DelVarSrc;
    }

    if(this->m_cbImport->isChecked())
    {
        permBits|=PermBits_TemplateEditor_Import;
    }
    if(this->m_cbExport->isChecked())
    {
        permBits|=PermBits_TemplateEditor_Export;
    }
    return permBits;
}

ZFileManagerPerm::ZFileManagerPerm()
{
    this->m_cbNewFolder=new QCheckBox(tr("创建文件夹"));
    this->m_cbDelFolder=new QCheckBox(tr("删除文件夹"));

    this->m_cbUploadFile=new QCheckBox(tr("上传文件"));
    this->m_cbDownloadFile=new QCheckBox(tr("下载文件"));
    this->m_cbDelFile=new QCheckBox(tr("删除文件"));


    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_cbNewFolder,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbDelFolder,0,1,1,1);

    this->m_gridLayout->addWidget(this->m_cbUploadFile,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbDownloadFile,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_cbDelFile,1,2,1,1);

    this->setLayout(this->m_gridLayout);
}
ZFileManagerPerm::~ZFileManagerPerm()
{
    delete this->m_cbNewFolder;
    delete this->m_cbDelFolder;

    delete this->m_cbUploadFile;
    delete this->m_cbDownloadFile;
    delete this->m_cbDelFile;

    delete this->m_gridLayout;
}
void ZFileManagerPerm::ZSetPermBits(qint32 permBits)
{
    if(permBits&PermBits_FileManager_NewFolder)
    {
        this->m_cbNewFolder->setChecked(true);
    }
    if(permBits&PermBits_FileManager_DelFolder)
    {
        this->m_cbDelFolder->setChecked(true);
    }

    if(permBits&PermBits_FileManager_UploadFile)
    {
        this->m_cbUploadFile->setChecked(true);
    }
    if(permBits&PermBits_FileManager_DownloadFile)
    {
        this->m_cbDownloadFile->setChecked(true);
    }
    if(permBits&PermBits_FileManager_DelFile)
    {
        this->m_cbDelFile->setChecked(true);
    }
}
qint32 ZFileManagerPerm::ZGetPermBits()
{
    qint32 permBits=0;
    if(this->m_cbNewFolder->isChecked())
    {
        permBits|=PermBits_FileManager_NewFolder;
    }
    if(this->m_cbDelFolder->isChecked())
    {
        permBits|=PermBits_FileManager_DelFolder;
    }

    if(this->m_cbUploadFile->isChecked())
    {
        permBits|=PermBits_FileManager_UploadFile;
    }
    if(this->m_cbDownloadFile->isChecked())
    {
        permBits|=PermBits_FileManager_DownloadFile;
    }
    if(this->m_cbDelFile->isChecked())
    {
        permBits|=PermBits_FileManager_DelFile;
    }
    return permBits;
}
//////////////////////////////////////////////////////////////////////
ZProcessEditorPerm::ZProcessEditorPerm()
{
    this->m_cbNewProcess=new QCheckBox(tr("创建工序"));
    this->m_cbMdyProcess=new QCheckBox(tr("编辑工序"));
    this->m_cbDelProcess=new QCheckBox(tr("删除工序"));


    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_cbNewProcess,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbMdyProcess,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_cbDelProcess,0,2,1,1);

    this->setLayout(this->m_gridLayout);
}
ZProcessEditorPerm::~ZProcessEditorPerm()
{
    delete this->m_cbNewProcess;
    delete this->m_cbMdyProcess;
    delete this->m_cbDelProcess;
    delete this->m_gridLayout;
}
void ZProcessEditorPerm::ZSetPermBits(qint32 permBits)
{
    if(permBits&PermBits_ProcessEditor_NewProcess)
    {
        this->m_cbNewProcess->setChecked(true);
    }
    if(permBits&PermBits_ProcessEditor_MdyProcess)
    {
        this->m_cbMdyProcess->setChecked(true);
    }
    if(permBits&PermBits_ProcessEditor_DelProcess)
    {
        this->m_cbDelProcess->setChecked(true);
    }
}
qint32 ZProcessEditorPerm::ZGetPermBits()
{
    qint32 permBits=0;
    if(this->m_cbNewProcess->isChecked())
    {
        permBits|=PermBits_ProcessEditor_NewProcess;
    }
    if(this->m_cbMdyProcess->isChecked())
    {
        permBits|=PermBits_ProcessEditor_MdyProcess;
    }
    if(this->m_cbDelProcess->isChecked())
    {
        permBits|=PermBits_ProcessEditor_DelProcess;
    }
    return permBits;
}
////////////////////////////////////////////////////////////////
ZTaskManagerPerm::ZTaskManagerPerm()
{
    this->m_cbNewTask=new QCheckBox(tr("创建任务"));
    this->m_cbMdyTask=new QCheckBox(tr("编辑任务"));
    this->m_cbDelTask=new QCheckBox(tr("删除任务"));


    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_cbNewTask,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbMdyTask,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_cbDelTask,0,2,1,1);

    this->setLayout(this->m_gridLayout);
}
ZTaskManagerPerm::~ZTaskManagerPerm()
{
    delete this->m_cbNewTask;
    delete this->m_cbMdyTask;
    delete this->m_cbDelTask;
    delete this->m_gridLayout;
}
void ZTaskManagerPerm::ZSetPermBits(qint32 permBits)
{
    if(permBits&PermBits_TaskManager_NewTask)
    {
        this->m_cbNewTask->setChecked(true);
    }
    if(permBits&PermBits_TaskManager_MdyTask)
    {
        this->m_cbMdyTask->setChecked(true);
    }
    if(permBits&PermBits_TaskManager_DelTask)
    {
        this->m_cbDelTask->setChecked(true);
    }
}
qint32 ZTaskManagerPerm::ZGetPermBits()
{
    qint32 permBits=0;
    if(this->m_cbNewTask->isChecked())
    {
        permBits|=PermBits_TaskManager_NewTask;
    }
    if(this->m_cbMdyTask->isChecked())
    {
        permBits|=PermBits_TaskManager_MdyTask;
    }
    if(this->m_cbDelTask->isChecked())
    {
        permBits|=PermBits_TaskManager_DelTask;
    }
    return permBits;
}
//////////////////////////////////////////////////////
ZFormDesignerPerm::ZFormDesignerPerm()
{
    this->m_cbNewForm=new QCheckBox(tr("创建报表"));
    this->m_cbMdyForm=new QCheckBox(tr("编辑报表"));
    this->m_cbDelForm=new QCheckBox(tr("删除报表"));

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_cbNewForm,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbMdyForm,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_cbDelForm,0,2,1,1);

    this->setLayout(this->m_gridLayout);
}
ZFormDesignerPerm::~ZFormDesignerPerm()
{
    delete this->m_cbNewForm;
    delete this->m_cbMdyForm;
    delete this->m_cbDelForm;
    delete this->m_gridLayout;
}
void ZFormDesignerPerm::ZSetPermBits(qint32 permBits)
{
    if(permBits&PermBits_FormDesigner_NewForm)
    {
        this->m_cbNewForm->setChecked(true);
    }
    if(permBits&PermBits_FormDesigner_MdyForm)
    {
        this->m_cbMdyForm->setChecked(true);
    }
    if(permBits&PermBits_FormDesigner_DelForm)
    {
        this->m_cbDelForm->setChecked(true);
    }
}
qint32 ZFormDesignerPerm::ZGetPermBits()
{
    qint32 permBits=0;
    if(this->m_cbNewForm->isChecked())
    {
        permBits|=PermBits_FormDesigner_NewForm;
    }
    if(this->m_cbMdyForm->isChecked())
    {
        permBits|=PermBits_FormDesigner_MdyForm;
    }
    if(this->m_cbDelForm->isChecked())
    {
        permBits|=PermBits_FormDesigner_DelForm;
    }
    return permBits;
}
/////////////////////////////////////////////////////
ZGrpInfoDia::ZGrpInfoDia(GrpInfoDiaType type,QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setMinimumSize(500,300);
    this->setStyleSheet("QDialog{background-color:#cce5f9;}");

    this->m_lblParentName=new QLabel(tr("父角色名称"));
    this->m_letParentName=new QLineEdit;
    this->m_letParentName->setFocusPolicy(Qt::NoFocus);

    this->m_lblGrpName=new QLabel(tr("角色名称"));
    this->m_letGrpName=new QLineEdit;
    connect(this->m_letGrpName,SIGNAL(returnPressed()),this,SLOT(ZSlotOkay()));

    this->m_listWidget=new QListWidget;
    this->m_listWidget->setMinimumSize(150,100);
    QListWidgetItem *userManagerItem=new QListWidgetItem;
    userManagerItem->setText(tr("用户管理"));
    userManagerItem->setIcon(QIcon(":/TaskBar/images/UserManager.png"));

    QListWidgetItem *templateEditItem=new QListWidgetItem;
    templateEditItem->setText(tr("模板编辑"));
    templateEditItem->setIcon(QIcon(":/TaskBar/images/TemplateEditor.png"));

    QListWidgetItem *fileManagerItem=new QListWidgetItem;
    fileManagerItem->setText(tr("文件管理"));
    fileManagerItem->setIcon(QIcon(":/TaskBar/images/FileManager.png"));

    QListWidgetItem *processEditItem=new QListWidgetItem;
    processEditItem->setText(tr("工序编辑"));
    processEditItem->setIcon(QIcon(":/TaskBar/images/ProcessEditor.png"));

    QListWidgetItem *taskManagerItem=new QListWidgetItem;
    taskManagerItem->setText(tr("任务管理"));
    taskManagerItem->setIcon(QIcon(":/TaskBar/images/TaskManager.png"));

    QListWidgetItem *formDesignerItem=new QListWidgetItem;
    formDesignerItem->setText(tr("报表输出"));
    formDesignerItem->setIcon(QIcon(":/TaskBar/images/ReportDesigner.png"));

    this->m_listWidget->addItem(userManagerItem);
    this->m_listWidget->addItem(templateEditItem);
    this->m_listWidget->addItem(fileManagerItem);
    this->m_listWidget->addItem(processEditItem);
    this->m_listWidget->addItem(taskManagerItem);
    this->m_listWidget->addItem(formDesignerItem);


    this->m_stackedWidget=new QStackedWidget;
    //sub parts.
    this->m_userManagerPerm=new ZUserManagerPerm;
    this->m_templateEditorPerm=new ZTemplateEditorPerm;
    this->m_fileManagerPerm=new ZFileManagerPerm;
    this->m_processEditorPerm=new ZProcessEditorPerm;
    this->m_taskManagerPerm=new ZTaskManagerPerm;
    this->m_formDesignerPerm=new ZFormDesignerPerm;
    this->m_stackedWidget->addWidget(this->m_userManagerPerm);
    this->m_stackedWidget->addWidget(this->m_templateEditorPerm);
    this->m_stackedWidget->addWidget(this->m_fileManagerPerm);
    this->m_stackedWidget->addWidget(this->m_processEditorPerm);
    this->m_stackedWidget->addWidget(this->m_taskManagerPerm);
    this->m_stackedWidget->addWidget(this->m_formDesignerPerm);

    this->m_lblGrpMemo=new QLabel(tr("角色说明"));
    this->m_tetGrpMemo=new QTextEdit;

    this->m_btnOKay=new QToolButton;
    this->m_btnOKay->setText(tr("确认"));
    this->m_btnCancel=new QToolButton;
    this->m_btnCancel->setText(tr("取消"));
    this->m_btnOKay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_btnOKay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_btnCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gridLayout=new QGridLayout;

    this->m_gridLayout->addWidget(this->m_lblParentName,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_letParentName,0,1,1,1);

    this->m_gridLayout->addWidget(this->m_lblGrpName,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_letGrpName,1,1,1,1);

    this->m_gridLayout->addWidget(this->m_listWidget,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_stackedWidget,2,1,1,1);

    this->m_gridLayout->addWidget(this->m_lblGrpMemo,3,0,1,2);
    this->m_gridLayout->addWidget(this->m_tetGrpMemo,4,0,1,2);

    this->m_gridLayout->addWidget(this->m_btnOKay,5,0,1,1);
    this->m_gridLayout->addWidget(this->m_btnCancel,5,1,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_btnOKay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_btnCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
    connect(this->m_listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(ZSlotShowParts(int)));

    this->m_diaType=type;
    switch(type)
    {
    case Type_NewGrp:
        this->setWindowTitle(tr("添加新角色"));
        break;
    case Type_MdyGrp:
        this->setWindowTitle(tr("编辑角色"));
        this->m_letGrpName->setFocusPolicy(Qt::NoFocus);
        break;
    case Type_DelGrp:
        this->setWindowTitle(tr("删除角色"));
        this->m_letGrpName->setFocusPolicy(Qt::NoFocus);
        this->m_tetGrpMemo->setFocusPolicy(Qt::NoFocus);
        break;
    default:
        break;
    }
}
ZGrpInfoDia::~ZGrpInfoDia()
{
    delete this->m_lblParentName;
    delete this->m_letParentName;

    delete this->m_lblGrpName;
    delete this->m_letGrpName;

    delete this->m_userManagerPerm;
    delete this->m_templateEditorPerm;
    delete this->m_fileManagerPerm;
    delete this->m_processEditorPerm;
    delete this->m_taskManagerPerm;
    delete this->m_formDesignerPerm;
    delete this->m_stackedWidget;
    delete this->m_listWidget;

    delete this->m_lblGrpMemo;
    delete this->m_tetGrpMemo;

    delete this->m_btnOKay;
    delete this->m_btnCancel;

    delete this->m_gridLayout;
}
QSize ZGrpInfoDia::sizeHint() const
{
    return QSize(400,600);
}
void ZGrpInfoDia::ZParseAckNetFrmXmlData()
{
    //qDebug()<<"ZGrpInfoDia::ParseAckNetFrm:"<<this->m_ackNetFrmXmlData;

    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Role"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString roleName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(roleName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString parentName=attr.value(QString("parentName")).toString();
                        QString permBits=attr.value(QString("permBits")).toString();
                        QString roleMemo=attr.value(QString("memo")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        paraList.append(parentName);
                        paraList.append(permBits);
                        paraList.append(roleMemo);
                        paraList.append(creator);
                        paraList.append(createTime);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("role","add",paraList,retCode);
                }else if(cmd=="mdy")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString roleName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(roleName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString permBits=attr.value(QString("permBits")).toString();
                        QString roleMemo=attr.value(QString("memo")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        paraList.append(permBits);
                        paraList.append(roleMemo);
                        paraList.append(creator);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("role","mdy",paraList,retCode);
                }else if(cmd=="del")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString roleName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(roleName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{

                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("role","del",paraList,retCode);
                }
            }//Role.
        }//StarElement.
    }//while().
}
void ZGrpInfoDia::ZSlotOkay()
{
    if(MyUserInfo::ZGetInstance()->m_bOnLine==false)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("网络错误,未连接服务器!\n请等待连接服务器成功后再操作!"));
        return;
    }
    if(this->m_letGrpName->text().trimmed().isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("角色名称不能为空!"));
        return;
    }
    PNetFrame_Role *netFrm=new PNetFrame_Role;
    switch(this->m_diaType)
    {
    case Type_NewGrp:
        netFrm->ZAddRole(this->ZGetGrpName(),this->ZGetParentName(),this->ZGetPermBits(),this->ZGetGrpMemo());
        this->m_waitDia->ZSetTipsMsg(tr("正在添加新角色[%1]").arg(this->ZGetGrpName()));
        break;
    case Type_MdyGrp:
        netFrm->ZMdyRole(this->ZGetGrpName(),this->ZGetPermBits(),this->ZGetGrpMemo());
        this->m_waitDia->ZSetTipsMsg(tr("正在修改角色[%1]").arg(this->ZGetGrpName()));
        break;
    case Type_DelGrp:
        netFrm->ZDelRole(this->ZGetGrpName());
        this->m_waitDia->ZSetTipsMsg(tr("正在删除角色[%1]").arg(this->ZGetGrpName()));
        break;
    default:
        break;
    }
    this->m_netFrmQueue.enqueue(netFrm);
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
    this->accept();
}
void ZGrpInfoDia::ZSlotCancel()
{
    this->reject();
}
void ZGrpInfoDia::ZSlotShowParts(qint32 index)
{
    switch(index)
    {
    case 0:
        this->m_stackedWidget->setCurrentWidget(this->m_userManagerPerm);
        break;
    case 1:
        this->m_stackedWidget->setCurrentWidget(this->m_templateEditorPerm);
        break;
    case 2:
        this->m_stackedWidget->setCurrentWidget(this->m_fileManagerPerm);
        break;
    case 3:
        this->m_stackedWidget->setCurrentWidget(this->m_processEditorPerm);
        break;
    case 4:
        this->m_stackedWidget->setCurrentWidget(this->m_taskManagerPerm);
        break;
    case 5:
        this->m_stackedWidget->setCurrentWidget(this->m_formDesignerPerm);
        break;
    default:
        break;
    }
}
QString ZGrpInfoDia::ZGetParentName()
{
    return this->m_letParentName->text();
}
void ZGrpInfoDia::ZSetParentName(QString name)
{
    this->m_letParentName->setText(name);
}
QString ZGrpInfoDia::ZGetGrpName()
{
    return this->m_letGrpName->text().trimmed();
}
void ZGrpInfoDia::ZSetGrpName(QString name)
{
    this->m_letGrpName->setText(name);
}

QString ZGrpInfoDia::ZGetPermBits()
{
    qint32 perm1=this->m_userManagerPerm->ZGetPermBits();
    qint32 perm2=this->m_templateEditorPerm->ZGetPermBits();
    qint32 perm3=this->m_fileManagerPerm->ZGetPermBits();
    qint32 perm4=this->m_processEditorPerm->ZGetPermBits();
    qint32 perm5=this->m_taskManagerPerm->ZGetPermBits();
    qint32 perm6=this->m_formDesignerPerm->ZGetPermBits();
    return QString("%1,%2,%3,%4,%5,%6").arg(perm1).arg(perm2).arg(perm3).arg(perm4).arg(perm5).arg(perm6);
}
void ZGrpInfoDia::ZSetPermBits(QString permBits)
{
    QStringList permBitsList=permBits.split(",");
    if(permBitsList.count()!=6)
    {
        return;
    }
    this->m_userManagerPerm->ZSetPermBits(permBitsList.at(0).toInt());
    this->m_templateEditorPerm->ZSetPermBits(permBitsList.at(1).toInt());
    this->m_fileManagerPerm->ZSetPermBits(permBitsList.at(2).toInt());
    this->m_processEditorPerm->ZSetPermBits(permBitsList.at(3).toInt());
    this->m_taskManagerPerm->ZSetPermBits(permBitsList.at(4).toInt());
    this->m_formDesignerPerm->ZSetPermBits(permBitsList.at(5).toInt());
}

QString ZGrpInfoDia::ZGetGrpMemo()
{
    return this->m_tetGrpMemo->toPlainText().trimmed();
}
void ZGrpInfoDia::ZSetGrpMemo(QString memo)
{
    this->m_tetGrpMemo->setText(memo);
}
