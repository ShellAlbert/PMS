#include "ptemplateeditor.h"
#include <QMessageBox>
#include <QHeaderView>
#include <TemplateEditor/zgeneralvarinfodia.h>
#include <TemplateEditor/zautovarinfodia.h>
#include <TemplateEditor/zfontinfodia.h>
#include <TemplateEditor/zcolorinfodia.h>
#include <TemplateEditor/zframeinfodia.h>
#include <TemplateEditor/zsyspicdia.h>
#include <TemplateEditor/ztemplateinfodia.h>
#include <TemplateEditor/zlisttemplateinfodia.h>
#include <TemplateEditor/zvarsourceinfodia.h>
#include <TemplateEditor/zvarinfodia.h>
#include <TemplateEditor/zcomboboxdia.h>
#include <TemplateEditor/zspinboxdia.h>
#include <QFileDialog>
#include <QSpinBox>
#include <QXmlStreamWriter>
#include <QDebug>
#include <QBuffer>
#include <QAction>
#include <QMenu>
#include <QInputDialog>
#include <QDateTimeEdit>
#include <QPrinter>
#include <QTextDocument>
#include <QFontDatabase>
#include <QDebug>
#include <QPainter>
#include <QtXlsx/QtXlsx>
#include <QInputDialog>
ZTemplateVarSrcView::ZTemplateVarSrcView(QWidget *parent):QFrame(parent)
{
    this->setStyleSheet("QFrame{background-color:#3F93A8;}");
    this->setMinimumWidth(200);

    QString tbQSS("QToolButton{font-size:20px;font-weight:bold;color:black;}");

    this->m_tbTemplate=new QToolButton;
    this->m_tbTemplate->setVisible(false);
    this->m_tbTemplate->setStyleSheet(tbQSS);
    this->m_tbVarSrc=new QToolButton;
    this->m_tbVarSrc->setVisible(false);
    this->m_tbVarSrc->setStyleSheet(tbQSS);
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_tbTemplate);
    this->m_vLayout->addWidget(this->m_tbVarSrc);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addLayout(this->m_vLayout);
    this->m_hLayout->addStretch(1);
    this->setLayout(this->m_hLayout);
}
ZTemplateVarSrcView::~ZTemplateVarSrcView()
{
    delete this->m_tbTemplate;
    delete this->m_tbVarSrc;
    delete this->m_vLayout;
    delete this->m_hLayout;
}
void ZTemplateVarSrcView::ZSetData(QString templateName,QString varSrcName)
{
    this->m_tbTemplate->setVisible(!templateName.isEmpty());
    this->m_tbVarSrc->setVisible(!varSrcName.isEmpty());
    this->m_tbTemplate->setText(templateName);
    this->m_tbVarSrc->setText(varSrcName);
    this->update();
}
void ZTemplateVarSrcView::paintEvent(QPaintEvent *event)
{
    if(this->m_tbTemplate->isVisible() && this->m_tbVarSrc->isVisible())
    {
        qint32 nTemplateX=this->m_tbTemplate->x()+this->m_tbTemplate->width()/2;
        qint32 nTemplateY=this->m_tbTemplate->y()+this->m_tbTemplate->height();
        qint32 nVarSrcX=this->m_tbVarSrc->x()+this->m_tbVarSrc->width()/2;
        qint32 nVarSrcY=this->m_tbVarSrc->y()+this->m_tbVarSrc->height()/2;

        QPainter painter(this);
        painter.setPen(QPen(Qt::darkGreen,3));
        painter.drawLine(QPoint(nTemplateX,nTemplateY),QPoint(nVarSrcX,nVarSrcY));
    }
    QFrame::paintEvent(event);
}
PTemplateEditor::PTemplateEditor(QWidget *parent) : QFrame(parent)
{
    this->setWindowTitle(tr("模板设计器-Template Designer"));
    this->setWindowIcon(QIcon(":/TaskBar/images/TemplateEditor.png"));
    this->setStyleSheet("QToolButton{background-color:#cce5f9;border:none;font:color #eaf7ff;}"
                        "QToolButton::hover{background-color:#eaf7ff;}"
                        "");
    //left.
    this->m_btnTemplate=new QToolButton;
    this->m_btnTemplate->setToolTip(tr("模板操作"));
    this->m_btnTemplate->setText(tr("模板"));
    this->m_btnTemplate->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/Template.png"));
    this->m_btnTemplate->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_menuTemplate=new QMenu;
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_AddTemplate)
    {
        this->m_actNewTemplate=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/NewTemplate.png"),tr("新建模板"),0);
        this->m_menuTemplate->addAction(this->m_actNewTemplate);
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_MdyTemplate)
    {
        this->m_actOpenTemplate=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/OpenTemplate.png"),tr("打开模板"),0);
        this->m_actSaveTemplate=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/SaveTemplate.png"),tr("保存模板"),0);
        this->m_actSaveAsTemplate=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/SaveAsTemplate.png"),tr("另存为..."),0);
        this->m_actBindVarSource=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/BinVarSource.png"),tr("绑定变量源"),0);
        this->m_actUnbindVarSource=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/UnBindVarSource.png"),tr("解绑变量源"),0);
        this->m_menuTemplate->addAction(this->m_actOpenTemplate);
        this->m_menuTemplate->addAction(this->m_actSaveTemplate);
        this->m_menuTemplate->addAction(this->m_actSaveAsTemplate);
        this->m_menuTemplate->addAction(this->m_actBindVarSource);
        this->m_menuTemplate->addAction(this->m_actUnbindVarSource);
        connect(this->m_actNewTemplate,SIGNAL(triggered(bool)),this,SLOT(ZSlotNewTemplate()));
        connect(this->m_actOpenTemplate,SIGNAL(triggered(bool)),this,SLOT(ZSlotOpenTemplate()));
        connect(this->m_actSaveTemplate,SIGNAL(triggered(bool)),this,SLOT(ZSlotSaveTemplate()));
        connect(this->m_actSaveAsTemplate,SIGNAL(triggered(bool)),this,SLOT(ZSlotSaveAsTemplate()));

        connect(this->m_actBindVarSource,SIGNAL(triggered(bool)),this,SLOT(ZSlotBindVarSource()));
        connect(this->m_actUnbindVarSource,SIGNAL(triggered(bool)),this,SLOT(ZSlotUnbindVarSource()));
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_DelTemplate)
    {
        this->m_actDelTemplate=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/DelTemplate.png"),tr("删除模板"),0);
        this->m_menuTemplate->addAction(this->m_actDelTemplate);
        connect(this->m_actDelTemplate,SIGNAL(triggered(bool)),this,SLOT(ZSlotDelTemplate()));
    }
    this->m_btnTemplate->setMenu(this->m_menuTemplate);
    this->m_btnTemplate->setPopupMode(QToolButton::InstantPopup);

    this->m_btnImExport=new QToolButton;
    this->m_btnImExport->setToolTip(tr("导入导出"));
    this->m_btnImExport->setText(tr("互导"));
    this->m_btnImExport->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/ImExport.png"));
    this->m_btnImExport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_menuImExport=new QMenu;
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_Import)
    {
        this->m_actImportTemplate=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/Import.png"),tr("导入XML..."),0);
        this->m_menuImExport->addAction(this->m_actImportTemplate);
        connect(this->m_actImportTemplate,SIGNAL(triggered(bool)),this,SLOT(ZSlotImportTemplate()));

        this->m_actImportExcel=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/Import.png"),tr("导入Excel..."),0);
        this->m_menuImExport->addAction(this->m_actImportExcel);
        connect(this->m_actImportExcel,SIGNAL(triggered(bool)),this,SLOT(ZSlotImportExcel()));
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_Export)
    {
        this->m_actExportTemplate=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/Export.png"),tr("导出XML..."),0);
        this->m_menuImExport->addAction(this->m_actExportTemplate);
        connect(this->m_actExportTemplate,SIGNAL(triggered(bool)),this,SLOT(ZSlotExportTemplate()));

        this->m_actExportExcel=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/Export.png"),tr("导出Excel..."),0);
        this->m_menuImExport->addAction(this->m_actExportExcel);
        connect(this->m_actExportExcel,SIGNAL(triggered(bool)),this,SLOT(ZSlotExportExcel()));
    }
    this->m_btnImExport->setMenu(this->m_menuImExport);
    this->m_btnImExport->setPopupMode(QToolButton::InstantPopup);


    this->m_btnCell=new QToolButton;
    this->m_btnCell->setToolTip(tr("单元格功能"));
    this->m_btnCell->setText(tr("单元"));
    this->m_btnCell->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/CellOp.png"));
    this->m_btnCell->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_actInsertPic=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/InsertPic.png"),tr("插入图片"),0);
    this->m_actRemovePic=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/RemovePic.png"),tr("移除图片"),0);
    this->m_actMergeCell=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/Merge.png"),tr("合并单元格"),0);
    this->m_actSplitCell=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/Split.png"),tr("拆分单元格"),0);
    this->m_actCellFont=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/Font.png"),tr("单元格字体"),0);
    this->m_actCellColor=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/Color.png"),tr("单元格颜色"),0);
    this->m_actCellFrame=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/Frame.png"),tr("单元格边框"),0);
    this->m_actCellBindVar=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/BindVar.png"),tr("绑定变量"),0);
    this->m_actCellUnbindVar=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/UnbindVar.png"),tr("解绑变量"),0);
    this->m_menuCell=new QMenu;
    this->m_menuCell->addAction(this->m_actInsertPic);
    this->m_menuCell->addAction(this->m_actRemovePic);
    this->m_menuCell->addAction(this->m_actMergeCell);
    this->m_menuCell->addAction(this->m_actSplitCell);
    this->m_menuCell->addAction(this->m_actCellFont);
    this->m_menuCell->addAction(this->m_actCellColor);
    this->m_menuCell->addAction(this->m_actCellFrame);
    this->m_menuCell->addAction(this->m_actCellBindVar);
    this->m_menuCell->addAction(this->m_actCellUnbindVar);
    this->m_btnCell->setMenu(this->m_menuCell);
    this->m_btnCell->setPopupMode(QToolButton::InstantPopup);

    this->m_btnAlign=new QToolButton;
    this->m_btnAlign->setToolTip(tr("对齐方式"));
    this->m_btnAlign->setText(tr("对齐"));
    this->m_btnAlign->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/Alignment.png"));
    this->m_btnAlign->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_actHLeftAlign=new QAction(QIcon(":/alignment/images/alignment/HAlignLeft.png"),tr("左对齐"),0);
    this->m_actHCenterAlign=new QAction(QIcon(":/alignment/images/alignment/HAlignCenter.png"),tr("居中"),0);
    this->m_actHRightAlign=new QAction(QIcon(":/alignment/images/alignment/HAlignRight.png"),tr("右对齐"),0);
    this->m_menuHAlign=new QMenu(tr("水平方向"));
    this->m_menuHAlign->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/Horizontal.png"));
    this->m_menuHAlign->addAction(this->m_actHLeftAlign);
    this->m_menuHAlign->addAction(this->m_actHCenterAlign);
    this->m_menuHAlign->addAction(this->m_actHRightAlign);


    this->m_actVTopAlign=new QAction(QIcon(":/alignment/images/alignment/VAlignTop.png"),tr("上对齐"),0);
    this->m_actVCenterAlign=new QAction(QIcon(":/alignment/images/alignment/VAlignCenter.png"),tr("居中"),0);
    this->m_actVBottomAlign=new QAction(QIcon(":/alignment/images/alignment/VAlignBottom.png"),tr("下对齐"),0);
    this->m_menuVAlign=new QMenu(tr("垂直方向"));
    this->m_menuVAlign->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/Vertical.png"));
    this->m_menuVAlign->addAction(this->m_actVTopAlign);
    this->m_menuVAlign->addAction(this->m_actVCenterAlign);
    this->m_menuVAlign->addAction(this->m_actVBottomAlign);

    this->m_menuAlign=new QMenu;
    this->m_menuAlign->addMenu(this->m_menuHAlign);
    this->m_menuAlign->addMenu(this->m_menuVAlign);
    this->m_btnAlign->setMenu(this->m_menuAlign);
    this->m_btnAlign->setPopupMode(QToolButton::InstantPopup);


    this->m_btnSysPic=new QToolButton;
    this->m_btnSysPic->setToolTip(tr("系统图库"));
    this->m_btnSysPic->setText(tr("图库"));
    this->m_btnSysPic->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/SysPic.png"));
    this->m_btnSysPic->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_actSysPic1=new QAction(tr("常用图库1"),0);
    this->m_actSysPic2=new QAction(tr("常用图库2"),0);
    this->m_actSysPic3=new QAction(tr("常用图库3"),0);
    this->m_menuSysPic=new QMenu;
    this->m_menuSysPic->addAction(this->m_actSysPic1);
    this->m_menuSysPic->addAction(this->m_actSysPic2);
    this->m_menuSysPic->addAction(this->m_actSysPic3);
    this->m_btnSysPic->setMenu(this->m_menuSysPic);
    this->m_btnSysPic->setPopupMode(QToolButton::InstantPopup);


    this->m_btnSysComponent=new QToolButton;
    this->m_btnSysComponent->setToolTip(tr("系统组件"));
    this->m_btnSysComponent->setText(tr("组件"));
    this->m_btnSysComponent->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/SysComponent.png"));
    this->m_btnSysComponent->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_actInsertCheckBox=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/CheckBox.png"),tr("插入复选框"),0);
    this->m_actInsertComboBox=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/ComboBox.png"),tr("插入下拉列表"),0);
    this->m_actInsertSpinBox=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/SpinBox.png"),tr("插入选值框"),0);
    this->m_actInsertDateTimeEdit=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/DateTimeEdit.png"),tr("插入日期时间"),0);
    this->m_menuSysComponent=new QMenu;
    this->m_menuSysComponent->addAction(this->m_actInsertCheckBox);
    this->m_menuSysComponent->addAction(this->m_actInsertComboBox);
    this->m_menuSysComponent->addAction(this->m_actInsertSpinBox);
    this->m_menuSysComponent->addAction(this->m_actInsertDateTimeEdit);
    this->m_btnSysComponent->setMenu(this->m_menuSysComponent);
    this->m_btnSysComponent->setPopupMode(QToolButton::InstantPopup);


    this->m_btnVarSourceOp=new QToolButton;
    this->m_btnVarSourceOp->setToolTip(tr("变量源"));
    this->m_btnVarSourceOp->setText(tr("变量"));
    this->m_btnVarSourceOp->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/VarSource.png"));
    this->m_btnVarSourceOp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_menuVarSourceOp=new QMenu;
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_AddVarSrc)
    {
        this->m_actAddVarSource=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/NewVarSource.png"),tr("新建变量源"),0);
        this->m_menuVarSourceOp->addAction(this->m_actAddVarSource);
        connect(this->m_actAddVarSource,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddVarSource()));
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_DelVarSrc)
    {
        this->m_actDelVarSource=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/DelVarSource.png"),tr("删除变量源"),0);
        this->m_menuVarSourceOp->addAction(this->m_actDelVarSource);
        connect(this->m_actDelVarSource,SIGNAL(triggered(bool)),this,SLOT(ZSlotDelVarSource()));
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_MdyVarSrc)
    {
        this->m_actOpenVarSource=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/MdyVarSource.png"),tr("编辑变量源"),0);
        this->m_menuVarSourceOp->addAction(this->m_actOpenVarSource);
        connect(this->m_actOpenVarSource,SIGNAL(triggered(bool)),this,SLOT(ZSlotOpenVarSource()));
    }

    this->m_actExportVarSourceTemplate=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/MdyVarSource.png"),tr("导出变量源模板"),0);
    this->m_menuVarSourceOp->addAction(this->m_actExportVarSourceTemplate);
    connect(this->m_actExportVarSourceTemplate,SIGNAL(triggered(bool)),this,SLOT(ZSlotExportVarSourceTemplate()));

    this->m_actImportVarSource=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/MdyVarSource.png"),tr("导入变量源模板"),0);
    this->m_menuVarSourceOp->addAction(this->m_actImportVarSource);
    connect(this->m_actImportVarSource,SIGNAL(triggered(bool)),this,SLOT(ZSlotImportVarSource()));

    this->m_btnVarSourceOp->setMenu(this->m_menuVarSourceOp);
    this->m_btnVarSourceOp->setPopupMode(QToolButton::InstantPopup);


    this->m_btnDisplay=new QToolButton;
    this->m_btnDisplay->setToolTip(tr("显示功能"));
    this->m_btnDisplay->setText(tr("显示"));
    this->m_btnDisplay->setIcon(QIcon(":/common/images/common/Display.png"));
    this->m_btnDisplay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnDisplay->setPopupMode(QToolButton::InstantPopup);
    this->m_menuDisplay=new QMenu;
    this->m_btnDisplay->setMenu(this->m_menuDisplay);

    this->m_actDetach=new QAction(QIcon(":/common/images/common/Detach.png"),tr("分离"));
    this->m_menuDisplay->addAction(this->m_actDetach);
    connect(this->m_actDetach,SIGNAL(triggered(bool)),this,SLOT(ZSlotAatchDetach()));

    this->m_actAatch=new QAction(QIcon(":/common/images/common/Attach.png"),tr("附属"));
    this->m_menuDisplay->addAction(this->m_actAatch);
    connect(this->m_actAatch,SIGNAL(triggered(bool)),this,SLOT(ZSlotAatchDetach()));


    /////////////////////////////////////////////////////////
    this->m_tbPrint=new QToolButton;
    this->m_tbPrint->setToolTip(tr("打印功能"));
    this->m_tbPrint->setText(tr("打印"));
    this->m_tbPrint->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/Print.png"));
    this->m_tbPrint->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbPrint->setPopupMode(QToolButton::InstantPopup);
    this->m_menuPrint=new QMenu;
    this->m_tbPrint->setMenu(this->m_menuPrint);

    this->m_actPrint=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/Print.png"),tr("打印..."));
    this->m_menuPrint->addAction(this->m_actPrint);
    connect(this->m_actPrint,SIGNAL(triggered(bool)),this,SLOT(ZSlotPrint()));

    this->m_actPrintHtml=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/PrintHtml.png"),tr("打印Html"));
    this->m_menuPrint->addAction(this->m_actPrintHtml);
    connect(this->m_actPrintHtml,SIGNAL(triggered(bool)),this,SLOT(ZSlotPrintHtml()));

    this->m_actPrintPdf=new QAction(QIcon(":/TemplateEditor/images/TemplateEditor/PrintPdf.png"),tr("打印PDF"));
    this->m_menuPrint->addAction(this->m_actPrintPdf);
    connect(this->m_actPrintPdf,SIGNAL(triggered(bool)),this,SLOT(ZSlotPrintPdf()));


    //help.
    this->m_tbHelp=new QToolButton;
    this->m_tbHelp->setToolTip(tr("获取帮助文档"));
    this->m_tbHelp->setText(tr("帮助"));
    this->m_tbHelp->setIcon(QIcon(":/common/images/common/help.png"));
    this->m_tbHelp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(this->m_tbHelp,SIGNAL(clicked(bool)),this,SLOT(ZSlotHelp()));

    this->m_vLayoutBtns=new QVBoxLayout;
    this->m_vLayoutBtns->addWidget(this->m_btnTemplate);
    this->m_vLayoutBtns->addWidget(this->m_btnImExport);
    this->m_vLayoutBtns->addWidget(this->m_btnCell);
    this->m_vLayoutBtns->addWidget(this->m_btnAlign);
    this->m_vLayoutBtns->addWidget(this->m_btnSysPic);
    this->m_vLayoutBtns->addWidget(this->m_btnSysComponent);
    this->m_vLayoutBtns->addStretch(1);
    this->m_vLayoutBtns->addWidget(this->m_btnVarSourceOp);
    this->m_vLayoutBtns->addWidget(this->m_btnDisplay);
    this->m_vLayoutBtns->addWidget(this->m_tbPrint);
    this->m_vLayoutBtns->addWidget(this->m_tbHelp);

    //right.
    this->m_templateWidget=new ZTemplateWidget;
    this->m_tabWidget=new QTabWidget;
    this->m_tabWidget->setTabsClosable(true);
    this->m_tabWidget->addTab(this->m_templateWidget,QIcon(":/TaskBar/images/TemplateEditor.png"),tr("模板管理"));
    this->m_tabWidget->tabBar()->tabButton(0,QTabBar::RightSide)->hide();

    this->m_templateWidget->m_treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    this->m_templateWidget->m_treeVarSource->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this->m_templateWidget->m_treeWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ZSlotTemplateTreePopupMenu(QPoint)));
    connect(this->m_templateWidget->m_treeVarSource,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ZSlotVarSourceTreePopupMenu(QPoint)));

    //main layout.
    this->m_hLayoutMain=new QHBoxLayout;
    this->m_hLayoutMain->addLayout(this->m_vLayoutBtns);
    this->m_hLayoutMain->addWidget(this->m_tabWidget);
    this->setLayout(this->m_hLayoutMain);

    connect(this->m_actInsertPic,SIGNAL(triggered(bool)),this,SLOT(ZSlotInsertPic()));
    connect(this->m_actRemovePic,SIGNAL(triggered(bool)),this,SLOT(ZSlotRemovePic()));
    connect(this->m_actMergeCell,SIGNAL(triggered(bool)),this,SLOT(ZSlotMergeCell()));
    connect(this->m_actSplitCell,SIGNAL(triggered(bool)),this,SLOT(ZSlotSplitCell()));
    connect(this->m_actCellFont,SIGNAL(triggered(bool)),this,SLOT(ZSlotCellFont()));
    connect(this->m_actCellColor,SIGNAL(triggered(bool)),this,SLOT(ZSlotCellColor()));
    connect(this->m_actCellFrame,SIGNAL(triggered(bool)),this,SLOT(ZSlotCellFrame()));
    connect(this->m_actCellBindVar,SIGNAL(triggered(bool)),this,SLOT(ZSlotCellBindVar()));
    connect(this->m_actCellUnbindVar,SIGNAL(triggered(bool)),this,SLOT(ZSlotCellUnbindVar()));

    connect(this->m_actHLeftAlign,SIGNAL(triggered(bool)),this,SLOT(ZSlotHAlignLeft()));
    connect(this->m_actHCenterAlign,SIGNAL(triggered(bool)),this,SLOT(ZSlotHAlignCenter()));
    connect(this->m_actHRightAlign,SIGNAL(triggered(bool)),this,SLOT(ZSlotHAlignRight()));
    connect(this->m_actVTopAlign,SIGNAL(triggered(bool)),this,SLOT(ZSlotVAlignTop()));
    connect(this->m_actVCenterAlign,SIGNAL(triggered(bool)),this,SLOT(ZSlotVAlignCenter()));
    connect(this->m_actVBottomAlign,SIGNAL(triggered(bool)),this,SLOT(ZSlotVAlignBottom()));

    connect(this->m_actSysPic1,SIGNAL(triggered(bool)),this,SLOT(ZSlotSysPic1()));
    connect(this->m_actSysPic2,SIGNAL(triggered(bool)),this,SLOT(ZSlotSysPic2()));
    connect(this->m_actSysPic3,SIGNAL(triggered(bool)),this,SLOT(ZSlotSysPic3()));

    connect(this->m_actInsertCheckBox,SIGNAL(triggered(bool)),this,SLOT(ZSlotInsertCheckBox()));
    connect(this->m_actInsertComboBox,SIGNAL(triggered(bool)),this,SLOT(ZSlotInsertComboBox()));
    connect(this->m_actInsertSpinBox,SIGNAL(triggered(bool)),this,SLOT(ZSlotInsertSpinBox()));
    connect(this->m_actInsertDateTimeEdit,SIGNAL(triggered(bool)),this,SLOT(ZSlotInsertDateTimeEdit()));

    connect(this->m_tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(ZSlotRemoveTab(qint32)));

    connect(this->m_templateWidget,SIGNAL(ZSignalOpenTemplate(QString)),this,SLOT(ZSlotOpenTemplate(QString)));
    connect(this->m_templateWidget,SIGNAL(ZSignalOpenVarSource(QString)),this,SLOT(ZSlotOpenVarSource(QString)));

    ZListTemplateVarSourceInfoDia *dia=new ZListTemplateVarSourceInfoDia(this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZExecuteListOp();
    dia->ZShowWaitingDialog();
}
PTemplateEditor::~PTemplateEditor()
{
    //left.
    delete this->m_vLayoutBtns;
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_AddTemplate)
    {
        delete this->m_actNewTemplate;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_MdyTemplate)
    {
        delete this->m_actOpenTemplate;
        delete this->m_actSaveTemplate;
        delete this->m_actSaveAsTemplate;
        delete this->m_actBindVarSource;
        delete this->m_actUnbindVarSource;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_DelTemplate)
    {
        delete this->m_actDelTemplate;
    }

    delete this->m_menuTemplate;
    delete this->m_btnTemplate;

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_Import)
    {
        delete this->m_actImportTemplate;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_Export)
    {
        delete this->m_actExportTemplate;
    }
    delete this->m_menuImExport;
    delete this->m_btnImExport;

    delete this->m_actInsertPic;
    delete this->m_actRemovePic;
    delete this->m_actMergeCell;
    delete this->m_actSplitCell;
    delete this->m_actCellFont;
    delete this->m_actCellColor;
    delete this->m_actCellFrame;
    delete this->m_actCellBindVar;
    delete this->m_actCellUnbindVar;
    delete this->m_menuCell;
    delete this->m_btnCell;

    delete this->m_actHLeftAlign;
    delete this->m_actHCenterAlign;
    delete this->m_actHRightAlign;
    delete this->m_actVTopAlign;
    delete this->m_actVCenterAlign;
    delete this->m_actVBottomAlign;
    delete this->m_menuHAlign;
    delete this->m_menuVAlign;
    delete this->m_menuAlign;
    delete this->m_btnAlign;

    delete this->m_actSysPic1;
    delete this->m_actSysPic2;
    delete this->m_actSysPic3;
    delete this->m_menuSysPic;
    delete this->m_btnSysPic;

    delete this->m_actInsertCheckBox;
    delete this->m_actInsertComboBox;
    delete this->m_actInsertSpinBox;
    delete this->m_actInsertDateTimeEdit;
    delete this->m_menuSysComponent;
    delete this->m_btnSysComponent;

    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_AddVarSrc)
    {
        delete this->m_actAddVarSource;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_DelVarSrc)
    {
        delete this->m_actDelVarSource;
    }
    if(MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm&PermBits_TemplateEditor_MdyVarSrc)
    {
        delete this->m_actOpenVarSource;
    }
    delete this->m_actExportVarSourceTemplate;
    delete this->m_actImportVarSource;
    delete this->m_menuVarSourceOp;
    delete this->m_btnVarSourceOp;

    delete this->m_actDetach;
    delete this->m_actAatch;
    delete this->m_menuDisplay;
    delete this->m_btnDisplay;
    delete this->m_actPrint;
    delete this->m_actPrintHtml;
    delete this->m_actPrintPdf;
    delete this->m_menuPrint;
    delete this->m_tbPrint;
    delete this->m_tbHelp;

    //right.
    delete this->m_templateWidget;
    delete this->m_tabWidget;

    //main layout.
    delete this->m_hLayoutMain;
}
void PTemplateEditor::closeEvent(QCloseEvent *event)
{
    emit this->ZSignalCloseEvent("TemplateEditor");
    QFrame::closeEvent(event);
}
void PTemplateEditor::resizeEvent(QResizeEvent *event)
{
    for(qint32 i=0;i<this->m_templateWidget->m_treeWidget->columnCount();i++)
    {
        this->m_templateWidget->m_treeWidget->resizeColumnToContents(i);
    }
    for(qint32 i=0;i<this->m_templateWidget->m_treeVarSource->columnCount();i++)
    {
        this->m_templateWidget->m_treeVarSource->resizeColumnToContents(i);
    }
    QFrame::resizeEvent(event);
}
void PTemplateEditor::ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode)
{
    if(item=="template")
    {
        if(cmd=="add")
        {
            QString templateName=paraList.at(0);
            QString creator=paraList.at(1);
            QString createTime=paraList.at(2);
            QString errMsg=paraList.at(3);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("add template [%1] failed:[%2].").arg(templateName).arg(errMsg));
            }else{
                QTreeWidgetItem *templateItem=new QTreeWidgetItem(0);//type=0 is template.type=1 is step.
                templateItem->setIcon(0,QIcon(":/TemplateEditor/images/TemplateEditor/Template.png"));
                templateItem->setText(0,templateName);//templateName.
                templateItem->setText(1,QString(""));//bindVarSource.
                templateItem->setText(2,QString("0K"));//template xml file size.
                templateItem->setText(3,creator);
                templateItem->setText(4,createTime);
                this->m_templateWidget->m_treeWidget->addTopLevelItem(templateItem);
                this->m_templateWidget->m_treeWidget->setCurrentItem(templateItem);

                //add template in tab.
                ZSheetWidget *sheetWidget=new ZSheetWidget;
                sheetWidget->m_sheet->ZSetTemplateName(templateName);
                this->m_tabWidget->addTab(sheetWidget,QIcon(":/TaskBar/images/Sheet.png"),"<*>"+templateName);
                this->m_tabWidget->setCurrentWidget(sheetWidget);
                connect(sheetWidget,SIGNAL(ZSignalDataChanged(QString)),this,SLOT(ZSlotSheetDataChanged(QString)));
                connect(sheetWidget->m_sheet,SIGNAL(ZSignalBindVar()),this,SLOT(ZSlotCellBindVar()));
                connect(sheetWidget->m_sheet,SIGNAL(ZSignalUnbindVar()),this,SLOT(ZSlotCellUnbindVar()));
                connect(sheetWidget,SIGNAL(ZSignalAlignmentChanged(qint32)),this,SLOT(ZSlotAlignmentChanged(qint32)));
                connect(sheetWidget,SIGNAL(ZSignalMergeCell()),this,SLOT(ZSlotMergeCell()));
                connect(sheetWidget,SIGNAL(ZSignalSplitCell()),this,SLOT(ZSlotSplitCell()));
                this->ZAddLogMsg(tr("add template [%1] success.").arg(templateName));
            }
        }else if(cmd=="del")
        {
            QString templateName=paraList.at(0);
            QString creator=paraList.at(1);
            QString errMsg=paraList.at(2);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("delete template [%1] failed:[%2].").arg(templateName).arg(errMsg));
            }else{
                //delete folderItem from treeWidget.
                for(qint32 i=0;i<this->m_templateWidget->m_treeWidget->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *templateItem=this->m_templateWidget->m_treeWidget->topLevelItem(i);
                    if(templateItem->type()==0 && templateItem->text(0)==templateName)
                    {
                        this->m_templateWidget->m_treeWidget->takeTopLevelItem(i);
                        delete templateItem;
                        templateItem=NULL;
                        break;
                    }
                }
                //close sheet in tab.
                for(qint32 i=1;i<this->m_tabWidget->count();i++)
                {
                    ZSheetWidget *sheetWidget=qobject_cast<ZSheetWidget*>(this->m_tabWidget->widget(i));
                    if(sheetWidget)
                    {
                        if(sheetWidget->m_sheet->ZGetTemplateName()==templateName)
                        {
                            this->m_tabWidget->removeTab(i);
                            delete sheetWidget;
                            sheetWidget=NULL;
                            break;
                        }
                    }
                }
                this->ZAddLogMsg(tr("delete template [%1] success.").arg(templateName));
            }
        }else if(cmd=="get")
        {
            QString templateName=paraList.at(0);
            QString creator=paraList.at(1);
            QString data=paraList.at(2);
            QString fileSize=paraList.at(3);
            QString varSourceData=paraList.at(4);
            QString errMsg=paraList.at(5);
            if(ackNetRetCode<0)
            {
                ZSheetWidget *sheetWidget=new ZSheetWidget;
                sheetWidget->m_sheet->ZSetTemplateName(templateName);
                this->m_tabWidget->addTab(sheetWidget,QIcon(":/TaskBar/images/Sheet.png"),templateName);
                this->m_tabWidget->setCurrentWidget(sheetWidget);
                connect(sheetWidget,SIGNAL(ZSignalDataChanged(QString)),this,SLOT(ZSlotSheetDataChanged(QString)));
                this->ZAddLogMsg(tr("get template [%1] failed:[%2]").arg(templateName).arg(errMsg));
            }else{
                //add template in tab.
                ZSheetWidget *sheetWidget=new ZSheetWidget;
                sheetWidget->m_sheet->ZSetTemplateName(templateName);
                //here must put VarSourceXmlData first.
                //because TemplateXmlData contains VarBindCell information.
                sheetWidget->ZPutVarSourceXmlData(varSourceData);
                sheetWidget->ZPutTemplateXmlData(data);
                this->m_tabWidget->addTab(sheetWidget,QIcon(":/TaskBar/images/Sheet.png"),templateName);
                this->m_tabWidget->setCurrentWidget(sheetWidget);
                connect(sheetWidget,SIGNAL(ZSignalDataChanged(QString)),this,SLOT(ZSlotSheetDataChanged(QString)));
                connect(sheetWidget->m_sheet,SIGNAL(ZSignalBindVar()),this,SLOT(ZSlotCellBindVar()));
                connect(sheetWidget->m_sheet,SIGNAL(ZSignalUnbindVar()),this,SLOT(ZSlotCellUnbindVar()));
                connect(sheetWidget,SIGNAL(ZSignalAlignmentChanged(qint32)),this,SLOT(ZSlotAlignmentChanged(qint32)));
                connect(sheetWidget,SIGNAL(ZSignalMergeCell()),this,SLOT(ZSlotMergeCell()));
                connect(sheetWidget,SIGNAL(ZSignalSplitCell()),this,SLOT(ZSlotSplitCell()));
                this->ZAddLogMsg(tr("get template [%1] success,fileSize:%2.").arg(templateName).arg(fileSize));
            }
        }else if(cmd=="save")
        {
            QString templateName=paraList.at(0);
            QString fileSize=paraList.at(1);
            QString errMsg=paraList.at(2);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("save template [%1] failed:[%2].").arg(templateName).arg(errMsg));
            }else{
                this->ZAddLogMsg(tr("save template [%1] success.").arg(templateName));
                //remove <*> from tab.
                for(qint32 i=1;i<this->m_tabWidget->count();i++)
                {
                    if(this->m_tabWidget->tabText(i)=="<*>"+templateName)
                    {
                        this->m_tabWidget->setTabText(i,templateName);
                        break;
                    }
                }
                //add fileSize on template tree.
                for(qint32 i=0;i<this->m_templateWidget->m_treeWidget->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_templateWidget->m_treeWidget->topLevelItem(i);
                    if(item->text(0)==templateName)
                    {
                        item->setText(2,fileSize+"K");
                        break;
                    }
                }
            }
        }else if(cmd=="list")
        {
            QString templateName=paraList.at(0);
            QString varSourceName=paraList.at(1);
            QString fileSize=paraList.at(2);
            QString creator=paraList.at(3);
            QString createTime=paraList.at(4);
            QString errMsg=paraList.at(5);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("liste template [%1] failed:[%2].").arg(templateName).arg(errMsg));
            }else{
                QTreeWidgetItem *templateItem=new QTreeWidgetItem(0);//type=0 is template.type=1 is step.
                templateItem->setIcon(0,QIcon(":/TemplateEditor/images/TemplateEditor/Template.png"));
                templateItem->setText(0,templateName);
                templateItem->setText(1,varSourceName);
                templateItem->setText(2,fileSize+"K");
                templateItem->setText(3,creator);
                templateItem->setText(4,createTime);
                this->m_templateWidget->m_treeWidget->addTopLevelItem(templateItem);
                this->m_templateWidget->m_treeWidget->setCurrentItem(templateItem);
                this->ZAddLogMsg(tr("list template [%1] success.").arg(templateName));

                for(qint32 i=0;i<this->m_templateWidget->m_treeWidget->columnCount();i++)
                {
                    this->m_templateWidget->m_treeWidget->resizeColumnToContents(i);
                }
            }
        }else if(cmd=="bind")
        {
            QString templateName=paraList.at(0);
            QString varSource=paraList.at(1);
            QString creator=paraList.at(2);
            QString errMsg=paraList.at(3);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("bind VarSource[%1] to Template[%2] failed:[%3].").arg(templateName).arg(varSource).arg(errMsg));
            }else{
                //update template tree.
                for(qint32 i=0;i<this->m_templateWidget->m_treeWidget->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_templateWidget->m_treeWidget->topLevelItem(i);
                    if(item->text(0)==templateName)
                    {
                        item->setText(1,varSource);
                        this->ZAddLogMsg(tr("bind VarSource[%1] to Template[%2] success.").arg(templateName).arg(varSource));
                        break;
                    }
                }
                //VarSource RefCount+1.
                for(qint32 i=0;i<this->m_templateWidget->m_treeVarSource->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_templateWidget->m_treeVarSource->topLevelItem(i);
                    qint32 refCount=item->text(1).toInt();
                    item->setText(1,QString("%1").arg(refCount+1));
                    break;
                }
            }
        }else if(cmd=="unbind")
        {
            QString templateName=paraList.at(0);
            QString varSource=paraList.at(1);
            QString creator=paraList.at(2);
            QString errMsg=paraList.at(3);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("unbind VarSource[%1] from Template[%2] failed:[%3].").arg(templateName).arg(varSource).arg(errMsg));
            }else{
                //update template tree.
                for(qint32 i=0;i<this->m_templateWidget->m_treeWidget->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_templateWidget->m_treeWidget->topLevelItem(i);
                    if(item->text(0)==templateName)
                    {
                        item->setText(1,QString(""));
                        this->ZAddLogMsg(tr("unbind VarSource[%1] from Template[%2] success.").arg(templateName).arg(varSource));
                        break;
                    }
                }
                //VarSource RefCount-1.
                for(qint32 i=0;i<this->m_templateWidget->m_treeVarSource->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_templateWidget->m_treeVarSource->topLevelItem(i);
                    qint32 refCount=item->text(1).toInt();
                    item->setText(1,QString("%1").arg(refCount-1));
                    break;
                }
            }
        }
    }else if(item=="varsource")
    {
        if(cmd=="add")
        {
            QString varSourceName=paraList.at(0);
            QString refCount=paraList.at(1);
            QString creator=paraList.at(2);
            QString createTime=paraList.at(3);
            QString errMsg=paraList.at(4);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("add VarSource [%1] failed:[%2].").arg(varSourceName).arg(errMsg));
                QMessageBox::critical(this,tr("操作失败"),tr("创建变量源[%1]失败!\n[%2]").arg(varSourceName).arg(errMsg));
            }else{
                QTreeWidgetItem *varSourceItem=new QTreeWidgetItem(0);
                varSourceItem->setIcon(0,QIcon(":/TemplateEditor/images/TemplateEditor/VarSource.png"));
                varSourceItem->setText(0,varSourceName);
                varSourceItem->setText(1,refCount);
                varSourceItem->setText(2,creator);
                varSourceItem->setText(3,createTime);
                this->m_templateWidget->m_treeVarSource->addTopLevelItem(varSourceItem);
                this->ZAddLogMsg(tr("add VarSource [%1] success.").arg(varSourceName));
            }
        }else if(cmd=="del")
        {
            QString varSourceName=paraList.at(0);
            QString errMsg=paraList.at(1);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("delete VarSource [%1] failed:[%2].").arg(varSourceName).arg(errMsg));
                QMessageBox::critical(this,tr("操作失败"),tr("删除变量源[%1]失败!\n[%2]").arg(varSourceName).arg(errMsg));
            }else{
                for(qint32 i=0;i<this->m_templateWidget->m_treeVarSource->topLevelItemCount();i++)
                {
                    QTreeWidgetItem *item=this->m_templateWidget->m_treeVarSource->topLevelItem(i);
                    if(item->text(0)==varSourceName)
                    {
                        this->m_templateWidget->m_treeVarSource->takeTopLevelItem(i);
                        delete item;
                        item=NULL;
                        break;
                    }
                }
                this->ZAddLogMsg(tr("delete VarSource [%1] success.").arg(varSourceName));
            }
        }else if(cmd=="get")
        {
            QString varSourceName=paraList.at(0);
            QString xmlData=paraList.at(1);
            QString errMsg=paraList.at(2);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("get VarSource [%1] failed:[%2].").arg(varSourceName).arg(errMsg));
                QMessageBox::critical(this,tr("操作失败"),tr("打开变量源[%1]失败!\n[%2]").arg(varSourceName).arg(errMsg));
                ZVarInfoDia varInfoDia(varSourceName,this);
                if(varInfoDia.exec()==QDialog::Accepted)
                {
                    QString xmlData=varInfoDia.ZGetXmlData();
                    ZVarSourceInfoDia *varSrcInfoDia=new ZVarSourceInfoDia(ZVarSourceInfoDia::Type_SaveVarSource,this);
                    varSrcInfoDia->ZSetAckNetFrmProcessWidget(this);
                    varSrcInfoDia->ZSetVarSourceName(varSourceName);
                    varSrcInfoDia->ZSetVarSourceXmlData(xmlData);
                    if(varSrcInfoDia->exec()==QDialog::Accepted)
                    {
                        varSrcInfoDia->ZShowWaitingDialog();
                    }
                }
            }else{
                this->ZAddLogMsg(tr("get VarSource [%1] success.").arg(varSourceName));
                ZVarInfoDia varInfoDia(varSourceName,this);
                varInfoDia.ZSetXmlData(xmlData);
                if(varInfoDia.exec()==QDialog::Accepted)
                {
                    QString xmlData=varInfoDia.ZGetXmlData();
                    ZVarSourceInfoDia *varSrcInfoDia=new ZVarSourceInfoDia(ZVarSourceInfoDia::Type_SaveVarSource,this);
                    varSrcInfoDia->ZSetAckNetFrmProcessWidget(this);
                    varSrcInfoDia->ZSetVarSourceName(varSourceName);
                    varSrcInfoDia->ZSetVarSourceXmlData(xmlData);
                    if(varSrcInfoDia->exec()==QDialog::Accepted)
                    {
                        varSrcInfoDia->ZShowWaitingDialog();
                    }
                }
            }
        }else if(cmd=="save")
        {

        }else if(cmd=="list")
        {
            QString varSourceName=paraList.at(0);
            QString refCount=paraList.at(1);
            QString creator=paraList.at(2);
            QString createTime=paraList.at(3);
            QString errMsg=paraList.at(4);
            if(ackNetRetCode<0)
            {
                this->ZAddLogMsg(tr("list VarSource [%1] failed:[%2].").arg(varSourceName).arg(errMsg));
            }else{
                QTreeWidgetItem *varSourceItem=new QTreeWidgetItem(0);
                varSourceItem->setIcon(0,QIcon(":/TemplateEditor/images/TemplateEditor/VarSource.png"));
                varSourceItem->setText(0,varSourceName);
                varSourceItem->setText(1,refCount);
                varSourceItem->setText(2,creator);
                varSourceItem->setText(3,createTime);
                this->m_templateWidget->m_treeVarSource->addTopLevelItem(varSourceItem);
                this->ZAddLogMsg(tr("list VarSource [%1] success.").arg(varSourceName));
            }
        }
    }
    QCoreApplication::processEvents();
}
void PTemplateEditor::ZSlotNewTemplate()
{
    ZTemplateInfoDia *dia=new ZTemplateInfoDia(ZTemplateInfoDia::Type_NewTemplate,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PTemplateEditor::ZSlotOpenTemplate()
{
    QTreeWidgetItem *templateItem=this->m_templateWidget->m_treeWidget->currentItem();
    if(templateItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择一个模板再执行打开操作!"));
        return;
    }
    ZTemplateInfoDia *dia=new ZTemplateInfoDia(ZTemplateInfoDia::Type_GetTemplate,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetTemplateName(templateItem->text(0));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PTemplateEditor::ZSlotOpenTemplate(QString templateName)
{
    ZTemplateInfoDia *dia=new ZTemplateInfoDia(ZTemplateInfoDia::Type_GetTemplate,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetTemplateName(templateName);
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PTemplateEditor::ZSlotSaveTemplate()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass tab0.
    }
    ZSheetWidget *sheetWidget=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(sheetWidget)
    {
        ZTemplateInfoDia *dia=new ZTemplateInfoDia(ZTemplateInfoDia::Type_SaveTemplate,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetTemplateName(sheetWidget->m_sheet->ZGetTemplateName());
        dia->ZSetTemplateXmlData(sheetWidget->ZGetTemplateXmlData());
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
void PTemplateEditor::ZSlotSaveAsTemplate()
{

}
void PTemplateEditor::ZSlotDelTemplate()
{
    QTreeWidgetItem *templateItem=this->m_templateWidget->m_treeWidget->currentItem();
    if(templateItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择一个模板再执行删除操作!"));
        return;
    }
    if(!templateItem->text(1).isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("模板已绑定变量源无法删除!\n请先解绑变量源然后执行删除操作!"));
        return;
    }
    if(QMessageBox::question(this,tr("删除确认"),tr("您确认要删除模板[%1]吗?").arg(templateItem->text(0)),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        ZTemplateInfoDia *dia=new ZTemplateInfoDia(ZTemplateInfoDia::Type_DelTemplate,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetTemplateName(templateItem->text(0));
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }
    }
}
void PTemplateEditor::ZSlotBindVarSource()
{
    QTreeWidgetItem *templateItem=this->m_templateWidget->m_treeWidget->currentItem();
    QTreeWidgetItem *varSourceItem=this->m_templateWidget->m_treeVarSource->currentItem();
    if(templateItem==NULL || varSourceItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择一个模板和一个变量源然后进行绑定操作!"));
        return;
    }
    ZTemplateInfoDia *dia=new ZTemplateInfoDia(ZTemplateInfoDia::Type_BindVarSource,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetTemplateName(templateItem->text(0));
    dia->ZSetVarSourceName(varSourceItem->text(0));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PTemplateEditor::ZSlotUnbindVarSource()
{
    QTreeWidgetItem *templateItem=this->m_templateWidget->m_treeWidget->currentItem();
    if(templateItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择一个模板然后进行解除绑定操作!"));
        return;
    }
    if(templateItem->text(1).isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("该模板尚未绑定变量源!\n无需解除绑定!"));
        return;
    }
    ZTemplateInfoDia *dia=new ZTemplateInfoDia(ZTemplateInfoDia::Type_UnbindVarSource,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    dia->ZSetTemplateName(templateItem->text(0));
    dia->ZSetVarSourceName(templateItem->text(1));
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }
}
void PTemplateEditor::ZSlotImportTemplate()
{

}
void PTemplateEditor::ZSlotExportTemplate()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(sheet==NULL)
    {
        return;
    }
    QString fileName=QFileDialog::getSaveFileName(this,tr("导出模板"),sheet->m_sheet->ZGetSheetName(),tr("Template(*.xml)"));
    if(fileName.isEmpty())
    {
        return;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,tr("错误提示"),tr("打开文件%1失败!").arg(fileName));
        return;
    }
    file.write(sheet->ZGetTemplateXmlData().toUtf8());
    file.close();
    QMessageBox::information(this,tr("成功提示"),tr("导出模板文件%1成功!").arg(fileName));
}

void PTemplateEditor::ZSlotImportExcel()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("导入Excel"),".",tr("Microsoft Excel(*.xlsx)"));
    if(fileName.isEmpty())
    {
        return;
    }
    //add template in tab.
    QString templateName=QInputDialog::getText(this,tr("新建模板名称"),tr("请输出模板名称"));
    if(templateName.isEmpty())
    {
        return;
    }
    ZSheetWidget *sheetWidget=new ZSheetWidget;
    sheetWidget->m_sheet->ZSetTemplateName(templateName);
    this->m_tabWidget->addTab(sheetWidget,QIcon(":/TaskBar/images/Sheet.png"),"<*>"+templateName);
    this->m_tabWidget->setCurrentWidget(sheetWidget);
    connect(sheetWidget,SIGNAL(ZSignalDataChanged(QString)),this,SLOT(ZSlotSheetDataChanged(QString)));

    QXlsx::Document xlsx(fileName);
    for(qint32 x=1;x<=100;x++)
    {
        for(qint32 y=1;y<=50;y++)
        {
            QString inData=xlsx.read(x,y).toString();
            if(!inData.isEmpty())
            {
                QTableWidgetItem *item=new QTableWidgetItem;
                item->setTextAlignment(Qt::AlignCenter);
                item->setBackgroundColor(Qt::white);
                item->setText(inData);
                sheetWidget->m_sheet->setItem(x-1,y-1,item);
            }
        }
    }
    this->ZAddLogMsg(tr("import excel [%1] success.").arg(fileName));
    QMessageBox::information(this,tr("成功提示"),tr("模板导入Excel文件成功!\n%1").arg(fileName));
}

void PTemplateEditor::ZSlotExportExcel()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(sheet==NULL)
    {
        return;
    }
    QString fileName=QFileDialog::getSaveFileName(this,tr("导出Excel"),sheet->m_sheet->ZGetSheetName(),tr("Microsoft Excel(*.xlsx)"));
    if(fileName.isEmpty())
    {
        return;
    }
    qint32 rowCount=sheet->m_sheet->rowCount();
    qint32 colCount=sheet->m_sheet->columnCount();
    QXlsx::Document xlsx;
    QXlsx::Format fmt;
    fmt.setBorderColor(Qt::green);
    fmt.setBorderStyle(QXlsx::Format::BorderThin);
    fmt.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    fmt.setVerticalAlignment(QXlsx::Format::AlignVCenter);

    //cell data export.
    for(qint32 x=0;x<rowCount;x++)
    {
        for(qint32 y=0;y<colCount;y++)
        {
            QString text=sheet->m_sheet->item(x,y)->text();
            qint32 rowSpan=sheet->m_sheet->rowSpan(x,y);
            qint32 colSpan=sheet->m_sheet->columnSpan(x,y);

            //because QTableWidget start from (0,0).
            //but Excel start from (1,1)
            //so here we add 1 to x&y.
            xlsx.write(x+1,y+1,text,fmt);
        }
    }
    //merge cell features support.
#if 0
    QList<QXlsx::CellRange> rowColSpanRangeList;
    for(qint32 x=0;x<rowCount;x++)
    {
        for(qint32 y=0;y<colCount;y++)
        {
            QString text=sheet->m_sheet->item(x,y)->text();
            qint32 rowSpan=sheet->m_sheet->rowSpan(x,y);
            qint32 colSpan=sheet->m_sheet->columnSpan(x,y);

            if(rowSpan>1 || colSpan>1)
            {
                for(qint32 i=0;i<rowColSpanRangeList.size();i++)
                {

                }
            }

            if(rowSpan>1 || colSpan>1)
            {
                //because QTableWidget start from (0,0).
                //but Excel start from (1,1)
                //so here we add 1 to x&y.
                bool bBypass=false;
                QXlsx::CellRange cellRange(x+1,y+1,x+1,y+1+colSpan);
                //check if it's merged yet.
                for(qint32 i=0;i<rowColSpanRangeList.size();i++)
                {
                    qint32 rangeX1=rowColSpanRangeList.at(i).topLeft().row();
                    qint32 rangeY1=rowColSpanRangeList.at(i).topLeft().column();
                    qint32 rangeX2=rowColSpanRangeList.at(i).bottomRight().row();
                    qint32 rangeY2=rowColSpanRangeList.at(i).bottomRight().column();

                    qint32 cellX1=x+1;
                    qint32 cellY1=y+1;
                    qint32 cellX2=x+1;
                    qint32 cellY2=y+1+colSpan;
                    if(cellX1<=rangeX1+(rangeX2-rangeX1))
                    {

                    }

                    if(cellRange.topLeft().row()>=leftTopX && cellRange.topLeft().column()>=leftTopY &&
                            cellRange.topRight().row()<=rightBottomX && cellRange.topRight().column()<=rightBottomY)
                    {
                        qDebug()<<"Bypass:("<<x+1<<","<<y+1<<"),("<<x+1<<","<<y+1+colSpan+")";
                        bBypass=true;
                        break;
                    }
                }
                if(!bBypass)
                {
                    rowColSpanRangeList.append(cellRange);
                    xlsx.mergeCells(cellRange);
                    qDebug()<<"mergeCell:("<<x+1<<","<<y+1<<"),("<<x+1<<","<<y+1+colSpan+")";
                }
            }
            //qDebug()<<x<<","<<y<<":rowSpan:"<<rowSpan<<",colSpan:"<<colSpan;
            xlsx.write(x+1,y+1,text,fmt);
        }
    }
#endif
    //add the bottom information.
    QXlsx::Format fmtBottomInfo;
    fmtBottomInfo.setHorizontalAlignment(QXlsx::Format::AlignLeft);
    fmtBottomInfo.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    fmtBottomInfo.setBorderColor(Qt::green);
    fmtBottomInfo.setBorderStyle(QXlsx::Format::BorderThin);
    QString strBottomInfo;
    strBottomInfo+="Template "+sheet->m_sheet->ZGetTemplateName()+",";
    strBottomInfo+=QString("Exported from PMS V%1 by %2,").arg(MyUserInfo::ZGetInstance()->m_appVersion).arg(MyUserInfo::ZGetInstance()->m_UserInfo.m_userName);
    strBottomInfo+="at "+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.");
    //merge cell & print info.
    xlsx.mergeCells(QXlsx::CellRange(rowCount+1,1,rowCount+1,colCount));
    xlsx.write(rowCount+1,1,strBottomInfo,fmtBottomInfo);
    if(!xlsx.saveAs(fileName))
    {
        QMessageBox::information(this,tr("失败提示"),tr("导出模板文件%1失败!").arg(fileName));
        return;
    }
    QMessageBox::information(this,tr("成功提示"),tr("模板导出Excel文件成功!\n%1").arg(fileName));
}
void PTemplateEditor::ZSlotInsertPic()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(!sheet)
    {
        return;
    }
    QList<QTableWidgetItem*> tSelectedItems=sheet->m_sheet->selectedItems();
    if(tSelectedItems.count()<=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择要插入图片的单元格!"));
        return;
    }
    ZCell* tCell=static_cast<ZCell*>(tSelectedItems.at(0));
    if(!tCell)
    {
        return;
    }

    //get local file name.
    QString tPngFile = QFileDialog::getOpenFileName(this, tr("导入png图片文件"),".",QString("PNG (*.png)"));
    if(tPngFile.isEmpty())
    {
        return;
    }
    QLabel *tPngLabel=new QLabel;
    tPngLabel->setPixmap(QPixmap(tPngFile));
    tPngLabel->setScaledContents(true);
    sheet->m_sheet->setCellWidget(tCell->row(),tCell->column(),tPngLabel);
    tCell->ZSetCellWidgetType(ZCell::CellWidget_QLabel);
}
void PTemplateEditor::ZSlotRemovePic()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(!sheet)
    {
        return;
    }
    ZCell *cell=static_cast<ZCell*>(sheet->m_sheet->currentItem());
    if(cell==NULL)
    {
        return;
    }
    if(cell->ZGetCellWidgetType()==ZCell::CellWidget_QLabel)
    {
        QLabel *llPng=static_cast<QLabel*>(sheet->m_sheet->cellWidget(cell->row(),cell->column()));
        if(llPng)
        {
            sheet->m_sheet->setCellWidget(cell->row(),cell->column(),NULL);
            delete llPng;
            llPng=NULL;
            cell->ZSetCellWidgetType(ZCell::CellWidget_No);
        }
    }
}
void PTemplateEditor::ZSlotMergeCell()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass tab0.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(sheet)
    {
        qint32 tRow=sheet->m_sheet->selectedRanges().first().topRow();
        qint32 tColumn=sheet->m_sheet->selectedRanges().first().leftColumn();
        qint32 tRowCnt=sheet->m_sheet->selectedRanges().last().bottomRow()-sheet->m_sheet->selectedRanges().first().topRow() + 1;
        qint32 tColumnCnt=sheet->m_sheet->selectedRanges().last().rightColumn()-sheet->m_sheet->selectedRanges().first().leftColumn() + 1;
        if(tRowCnt>1 || tColumnCnt>1)
        {
            sheet->m_sheet->setSpan(tRow,tColumn,tRowCnt,tColumnCnt);
        }
    }
}
void PTemplateEditor::ZSlotSplitCell()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass tab0.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(sheet)
    {
        qint32 tCurRow=sheet->m_sheet->currentRow();
        qint32 tCurCol=sheet->m_sheet->currentColumn();
        sheet->m_sheet->setSpan(tCurRow,tCurCol,1,1);
    }
}
void PTemplateEditor::ZSlotCellFont()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass tab0.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(sheet)
    {
        //only fetch the first cell's attribute.
        QList<QTableWidgetItem*> tSelectedItems=sheet->m_sheet->selectedItems();
        if(tSelectedItems.count()<=0)
        {
            return;
        }
        ZCell* tLeftTopCell=static_cast<ZCell*>(tSelectedItems.at(0));
        ZCell* tRightBottomCell=static_cast<ZCell*>(tSelectedItems.at(tSelectedItems.count()-1));
        if(!tLeftTopCell || !tRightBottomCell)
        {
            return;
        }
        ZFontInfoDia dia(this);
        dia.ZSetLeftTop(tLeftTopCell->row(),tLeftTopCell->column());
        dia.ZSetRightBottom(tRightBottomCell->row(),tRightBottomCell->column());
        dia.ZSetFontFamily(tLeftTopCell->ZGetFont().family());
        dia.ZSetFontSize(tLeftTopCell->ZGetFont().pointSize());
        dia.ZSetFontBold(tLeftTopCell->ZGetFont().bold());
        dia.ZSetFontItalic(tLeftTopCell->ZGetFont().italic());
        if(dia.exec()==QDialog::Accepted)
        {
            for(qint32 i=0;i<tSelectedItems.count();i++)
            {
                ZCell* tCell=static_cast<ZCell*>(tSelectedItems.at(i));
                //cell font.
                QFont tFont(dia.ZGetFontFamily(),dia.ZGetFontSize());
                tFont.setBold(dia.ZFontIsBold());
                tFont.setItalic(dia.ZFontIsItalic());
                tCell->ZSetFont(tFont);
            }
        }
    }
}
void PTemplateEditor::ZSlotCellColor()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass tab0.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(sheet)
    {
        //only fetch the first cell's attribute.
        QList<QTableWidgetItem*> tSelectedItems=sheet->m_sheet->selectedItems();
        if(tSelectedItems.count()<=0)
        {
            return;
        }
        ZCell* tLeftTopCell=static_cast<ZCell*>(tSelectedItems.at(0));
        ZCell* tRightBottomCell=static_cast<ZCell*>(tSelectedItems.at(tSelectedItems.count()-1));
        if(!tLeftTopCell || !tRightBottomCell)
        {
            return;
        }
        ZColorInfoDia dia(this);
        dia.ZSetLeftTop(tLeftTopCell->row(),tLeftTopCell->column());
        dia.ZSetRightBottom(tRightBottomCell->row(),tRightBottomCell->column());
        dia.ZSetFgColor(tLeftTopCell->ZGetForegroundColor());
        dia.ZSetBgColor(tLeftTopCell->ZGetBackgroundColor());
        if(dia.exec()==QDialog::Accepted)
        {
            for(qint32 i=0;i<tSelectedItems.count();i++)
            {
                ZCell* tCell=static_cast<ZCell*>(tSelectedItems.at(i));
                if(tCell)
                {
                    tCell->ZSetForegroundColor(dia.ZGetFgColor());
                    tCell->ZSetBackgroundColor(dia.ZGetBgColor());
                }
            }
        }
    }
}
void PTemplateEditor::ZSlotCellFrame()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass tab0.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(sheet)
    {
        //only fetch the first cell's attribute.
        QList<QTableWidgetItem*> tSelectedItems=sheet->m_sheet->selectedItems();
        if(tSelectedItems.count()<=0)
        {
            return;
        }
        ZCell* tLeftTopCell=static_cast<ZCell*>(tSelectedItems.at(0));
        ZCell* tRightBottomCell=static_cast<ZCell*>(tSelectedItems.at(tSelectedItems.count()-1));
        if(!tLeftTopCell || !tRightBottomCell)
        {
            return;
        }
        ZFrameInfoDia dia(this);
        dia.ZSetLeftTop(tLeftTopCell->row(),tLeftTopCell->column());
        dia.ZSetRightBottom(tRightBottomCell->row(),tRightBottomCell->column());

        dia.ZSetTopFrame(tLeftTopCell->ZTopFrameIsSet());
        dia.ZSetBottomFrame(tLeftTopCell->ZBottomFrameIsSet());
        dia.ZSetLeftFrame(tLeftTopCell->ZLeftFrameIsSet());
        dia.ZSetRightFrame(tLeftTopCell->ZRightFrameIsSet());
        dia.ZSetFrameColor(tLeftTopCell->ZGetFrameColor());
        dia.ZSetFrameWidth(tLeftTopCell->ZGetFrameWidth());

        if(dia.exec()==QDialog::Accepted)
        {
            for(qint32 i=0;i<tSelectedItems.count();i++)
            {
                ZCell* tCell=static_cast<ZCell*>(tSelectedItems.at(i));
                if(tCell)
                {
                    tCell->ZSetTopFrame(dia.ZTopFrameIsSet());
                    tCell->ZSetBottomFrame(dia.ZBottomFrameIsSet());
                    tCell->ZSetLeftFrame(dia.ZLeftFrameIsSet());
                    tCell->ZSetRightFrame(dia.ZRightFrameIsSet());
                    tCell->ZSetFrameColor(dia.ZGetFrameColor());
                    tCell->ZSetFrameWidth(dia.ZGetFrameWidth());
                    if(dia.ZTopFrameIsSet()||dia.ZBottomFrameIsSet()||dia.ZLeftFrameIsSet()||dia.ZRightFrameIsSet())
                    {
                        sheet->m_sheet->ZGetCellDelegate()->ZAddCellBorder(tCell);
                    }else{
                        sheet->m_sheet->ZGetCellDelegate()->ZDelCellBorder(tCell);
                    }
                }
            }
        }
    }
}
void PTemplateEditor::ZSlotCellBindVar()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass tab0.
        return;
    }
    ZSheetWidget *sheet=static_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(sheet==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请打开一个模板,选中一个单元格和一个变量,然后进行绑定操作!"));
        return;
    }
    ZCell *cell=static_cast<ZCell*>(sheet->m_sheet->currentItem());
    if(cell==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请选中一个单元格!"));
        return;
    }
    QTreeWidgetItem *varItem=sheet->m_treeWidget->currentItem();
    if(varItem==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请选中一个变量!"));
        return;
    }
    if(varItem->parent()!=sheet->m_generalVarItem && varItem->parent()!=sheet->m_autoVarItem)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请选择一个普通变量或自动变量!"));
        return;
    }

    QString bindCell=QString("%1,%2").arg(cell->row()+1).arg(cell->column()+1);
    //one cell only can bind one var.
    //search the tree to cancel the previous binding.
    for(qint32 i=0;i<sheet->m_generalVarItem->childCount();i++)
    {
        QTreeWidgetItem *item=sheet->m_generalVarItem->child(i);
        if(item->text(1)==bindCell)
        {
            item->setText(1,QString(""));
            emit this->ZSignalLogMsg(tr("warning,cancel cell %1 previous bind general var:[%2].").arg(bindCell).arg(item->text(0)));
        }
    }
    for(qint32 i=0;i<sheet->m_autoVarItem->childCount();i++)
    {
        QTreeWidgetItem *item=sheet->m_autoVarItem->child(i);
        if(item->text(1)==bindCell)
        {
            item->setText(1,QString(""));
            emit this->ZSignalLogMsg(tr("warning,cancel cell %1 previous bind auto var:[%2].").arg(bindCell).arg(item->text(0)));
        }
    }
    varItem->setText(1,bindCell);
    emit this->ZSignalLogMsg(tr("bind var [%1] to cell %2.").arg(varItem->text(0)).arg(bindCell));
}
void PTemplateEditor::ZSlotCellUnbindVar()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass tab0.
        return;
    }
    ZSheetWidget *sheet=static_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(sheet==NULL)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请打开一个模板,选中一个变量,然后进行解绑操作!"));
        return;
    }
    QTreeWidgetItem *item=sheet->m_treeWidget->currentItem();
    if(item->parent()==sheet->m_generalVarItem || item->parent()==sheet->m_autoVarItem)
    {
        item->setText(1,QString(""));
        this->ZAddLogMsg(tr("unbind var [%1]").arg(item->text(0)));
    }
}
void PTemplateEditor::ZSlotFontChanged(QString fontFamily,qint32 fontSize,bool bold,bool italic)
{
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(sheet)
    {
        //only fetch the first cell's attribute.
        QList<QTableWidgetItem*> tSelectedItems=sheet->m_sheet->selectedItems();
        if(tSelectedItems.count()<=0)
        {
            return;
        }
        ZCell* tLeftTopCell=static_cast<ZCell*>(tSelectedItems.at(0));
        ZCell* tRightBottomCell=static_cast<ZCell*>(tSelectedItems.at(tSelectedItems.count()-1));
        if(!tLeftTopCell || !tRightBottomCell)
        {
            return;
        }

        for(qint32 i=0;i<tSelectedItems.count();i++)
        {
            qDebug()<<"setFont:"<<fontFamily<<","<<fontSize;
            ZCell* tCell=static_cast<ZCell*>(tSelectedItems.at(i));
            //cell font.
            QFont tFont(fontFamily,fontSize);
            tFont.setBold(bold);
            tFont.setItalic(italic);
            tCell->ZSetFont(tFont);
        }
    }
}
void PTemplateEditor::ZSlotHAlignLeft()
{
    this->ZSetTextAlignment(Qt::AlignLeft);
}
void PTemplateEditor::ZSlotHAlignCenter()
{
    this->ZSetTextAlignment(Qt::AlignHCenter);
}
void PTemplateEditor::ZSlotHAlignRight()
{
    this->ZSetTextAlignment(Qt::AlignRight);
}
void PTemplateEditor::ZSlotVAlignTop()
{
    this->ZSetTextAlignment(Qt::AlignTop);
}
void PTemplateEditor::ZSlotVAlignCenter()
{
    this->ZSetTextAlignment(Qt::AlignVCenter);
}
void PTemplateEditor::ZSlotVAlignBottom()
{
    this->ZSetTextAlignment(Qt::AlignBottom);
}
void PTemplateEditor::ZSlotAlignmentChanged(qint32 alignNo)
{
    switch(alignNo)
    {
    case 0:
        this->ZSlotHAlignCenter();
        this->ZSlotVAlignCenter();
        break;
    case 1:
        this->ZSlotHAlignLeft();
        break;
    case 2:
        this->ZSlotHAlignCenter();
        break;
    case 3:
        this->ZSlotHAlignRight();
        break;
    case 4:
        this->ZSlotVAlignTop();
        break;
    case 5:
        this->ZSlotVAlignCenter();
        break;
    case 6:
        this->ZSlotVAlignBottom();
        break;
    }
}
void PTemplateEditor::ZSlotSysPic1()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(!sheet)
    {
        return;
    }
    QList<QTableWidgetItem*> tSelectedItems=sheet->m_sheet->selectedItems();
    if(tSelectedItems.count()<=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择要插入图片的单元格!"));
        return;
    }
    ZCell* tCell=static_cast<ZCell*>(tSelectedItems.at(0));
    if(!tCell)
    {
        return;
    }
    ZSysPicDia dia("SysPic1",this);
    if(dia.exec()==QDialog::Accepted)
    {
        QLabel *tPngLabel=new QLabel;
        tPngLabel->setPixmap(QPixmap(dia.ZGetSelectedPic()));
        tPngLabel->setScaledContents(true);
        //remove old widget.
        QWidget *oldWidget=sheet->m_sheet->cellWidget(tCell->row(),tCell->column());
        if(oldWidget)
        {
            delete oldWidget;
            oldWidget=NULL;
        }
        //set new widget.
        sheet->m_sheet->setCellWidget(tCell->row(),tCell->column(),tPngLabel);
        tCell->ZSetCellWidgetType(ZCell::CellWidget_QLabel);
    }
}
void PTemplateEditor::ZSlotSysPic2()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(!sheet)
    {
        return;
    }
    QList<QTableWidgetItem*> tSelectedItems=sheet->m_sheet->selectedItems();
    if(tSelectedItems.count()<=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择要插入图片的单元格!"));
        return;
    }
    ZCell* tCell=static_cast<ZCell*>(tSelectedItems.at(0));
    if(!tCell)
    {
        return;
    }
    ZSysPicDia dia("SysPic2",this);
    if(dia.exec()==QDialog::Accepted)
    {
        QLabel *tPngLabel=new QLabel;
        tPngLabel->setPixmap(QPixmap(dia.ZGetSelectedPic()));
        tPngLabel->setScaledContents(true);
        sheet->m_sheet->setCellWidget(tCell->row(),tCell->column(),tPngLabel);
        tCell->ZSetCellWidgetType(ZCell::CellWidget_QLabel);
    }
}
void PTemplateEditor::ZSlotSysPic3()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(!sheet)
    {
        return;
    }
    QList<QTableWidgetItem*> tSelectedItems=sheet->m_sheet->selectedItems();
    if(tSelectedItems.count()<=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请先选择要插入图片的单元格!"));
        return;
    }
    ZCell* tCell=static_cast<ZCell*>(tSelectedItems.at(0));
    if(!tCell)
    {
        return;
    }
    ZSysPicDia dia("SysPic3",this);
    if(dia.exec()==QDialog::Accepted)
    {
        QLabel *tPngLabel=new QLabel;
        tPngLabel->setPixmap(QPixmap(dia.ZGetSelectedPic()));
        tPngLabel->setScaledContents(true);
        sheet->m_sheet->setCellWidget(tCell->row(),tCell->column(),tPngLabel);
        tCell->ZSetCellWidgetType(ZCell::CellWidget_QLabel);
    }
}
void PTemplateEditor::ZSlotInsertCheckBox()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(!sheet)
    {
        return;
    }
    ZCell* tCell=static_cast<ZCell*>(sheet->m_sheet->currentItem());
    if(!tCell)
    {
        return;
    }
    QString name=QInputDialog::getText(this,tr("输入对话框"),tr("请输入复选框名称"));
    if(name.isEmpty())
    {
        return;
    }
    //remove old widget.
    QWidget *oldWidget=sheet->m_sheet->cellWidget(tCell->row(),tCell->column());
    if(oldWidget)
    {
        delete oldWidget;
        oldWidget=NULL;
    }
    //set new widget.
    QCheckBox *checkBox=new QCheckBox;
    checkBox->setText(name);
    sheet->m_sheet->setCellWidget(tCell->row(),tCell->column(),checkBox);
    tCell->ZSetCellWidgetType(ZCell::CellWidget_QCheckBox);
}
void PTemplateEditor::ZSlotInsertComboBox()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(!sheet)
    {
        return;
    }
    ZCell* tCell=static_cast<ZCell*>(sheet->m_sheet->currentItem());
    if(!tCell)
    {
        return;
    }
    ZComboBoxDia dia(this);
    if(dia.exec()==QDialog::Accepted)
    {
        QStringList valList=dia.ZGetValueList();
        //remove old widget.
        QWidget *oldWidget=sheet->m_sheet->cellWidget(tCell->row(),tCell->column());
        if(oldWidget)
        {
            delete oldWidget;
            oldWidget=NULL;
        }
        //set new widget.
        QComboBox *comboBox=new QComboBox;
        for(qint32 i=0;i<valList.count();i++)
        {
            comboBox->addItem(valList.at(i));
        }
        sheet->m_sheet->setCellWidget(tCell->row(),tCell->column(),comboBox);
        tCell->ZSetCellWidgetType(ZCell::CellWidget_QComboBox);
    }
}
void PTemplateEditor::ZSlotInsertSpinBox()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(!sheet)
    {
        return;
    }
    ZCell* tCell=static_cast<ZCell*>(sheet->m_sheet->currentItem());
    if(!tCell)
    {
        return;
    }
    ZSpinBoxDia dia(this);
    if(dia.exec()==QDialog::Accepted)
    {
        qint32 minVal=dia.ZGetMinValue();
        qint32 maxVal=dia.ZGetMaxValue();
        qint32 defaultVal=dia.ZGetDefaultValue();
        //remove old widget.
        QWidget *oldWidget=sheet->m_sheet->cellWidget(tCell->row(),tCell->column());
        if(oldWidget)
        {
            delete oldWidget;
            oldWidget=NULL;
        }
        //set new widget.
        QSpinBox *spinBox=new QSpinBox;
        spinBox->setRange(minVal,maxVal);
        spinBox->setValue(defaultVal);
        sheet->m_sheet->setCellWidget(tCell->row(),tCell->column(),spinBox);
        tCell->ZSetCellWidgetType(ZCell::CellWidget_QSpinBox);
    }
}
void PTemplateEditor::ZSlotInsertDateTimeEdit()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(!sheet)
    {
        return;
    }
    ZCell* tCell=static_cast<ZCell*>(sheet->m_sheet->currentItem());
    if(!tCell)
    {
        return;
    }
    //remove old widget.
    QWidget *oldWidget=sheet->m_sheet->cellWidget(tCell->row(),tCell->column());
    if(oldWidget)
    {
        delete oldWidget;
        oldWidget=NULL;
    }
    //set new widget.
    QDateTimeEdit *dateTimeEdit=new QDateTimeEdit;
    dateTimeEdit->setCalendarPopup(true);
    dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    sheet->m_sheet->setCellWidget(tCell->row(),tCell->column(),dateTimeEdit);
    tCell->ZSetCellWidgetType(ZCell::CellWidget_QDateTimeEdit);
}
void PTemplateEditor::ZSlotAddVarSource()
{
    ZVarSourceInfoDia *dia=new ZVarSourceInfoDia(ZVarSourceInfoDia::Type_NewVarSource,this);
    dia->ZSetAckNetFrmProcessWidget(this);
    if(dia->exec()==QDialog::Accepted)
    {
        dia->ZShowWaitingDialog();
    }else{
        delete dia;
        dia=NULL;
    }
}
void PTemplateEditor::ZSlotDelVarSource()
{
    QTreeWidgetItem *item=this->m_templateWidget->m_treeVarSource->currentItem();
    if(item==NULL)
    {
        return;
    }
    if(item->text(1).toInt()!=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("无法删除变量源!\n变量源[%1]引用计数为[%2]!\n只有当变量源引用计数为0时才可删除!").arg(item->text(0)).arg(item->text(1)));
        return;
    }
    if(QMessageBox::question(this,tr("操作确认"),tr("您确认要删除变量源[%1]吗?").arg(item->text(0)),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        ZVarSourceInfoDia *dia=new ZVarSourceInfoDia(ZVarSourceInfoDia::Type_DelVarSource,this);
        dia->ZSetAckNetFrmProcessWidget(this);
        dia->ZSetVarSourceName(item->text(0));
        if(dia->exec()==QDialog::Accepted)
        {
            dia->ZShowWaitingDialog();
        }else{
            delete dia;
            dia=NULL;
        }
    }
}
void PTemplateEditor::ZSlotOpenVarSource()
{
    QTreeWidgetItem *item=this->m_templateWidget->m_treeVarSource->currentItem();
    if(item==NULL)
    {
        return;
    }
    ZVarInfoDia dia(item->text(0),this);
    if(dia.exec()==QDialog::Accepted)
    {

    }
}
void PTemplateEditor::ZSlotOpenVarSource(QString varSourceName)
{
    ZVarSourceInfoDia *varSrcInfoDia=new ZVarSourceInfoDia(ZVarSourceInfoDia::Type_GetVarSource,this);
    varSrcInfoDia->ZSetAckNetFrmProcessWidget(this);
    varSrcInfoDia->ZSetVarSourceName(varSourceName);
    if(varSrcInfoDia->exec()==QDialog::Accepted)
    {
        varSrcInfoDia->ZShowWaitingDialog();
    }
}
void PTemplateEditor::ZSlotExportVarSourceTemplate()
{
    //导出变量源模板
    //将表格中所有以@开头的变量导出为Excel模板.
    //@username,@sex,@family.
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(sheet==NULL)
    {
        return;
    }
    QString excelTemplateName=this->m_tabWidget->tabText(this->m_tabWidget->currentIndex())+QObject::tr("变量源.xlsx");
    QString fileName=QFileDialog::getSaveFileName(this,tr("导出Excel变量源模板"),excelTemplateName,tr("Microsoft Excel(*.xlsx)"));
    if(fileName.isEmpty())
    {
        return;
    }
    qint32 rowCount=sheet->m_sheet->rowCount();
    qint32 colCount=sheet->m_sheet->columnCount();
    QXlsx::Document xlsx;
    QXlsx::Format fmt;
    fmt.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    fmt.setVerticalAlignment(QXlsx::Format::AlignVCenter);

    //find out all variables.
    QList<ZVarSourceInfo> varList;
    for(qint32 x=0;x<rowCount;x++)
    {
        for(qint32 y=0;y<colCount;y++)
        {
            ZCell *cell=static_cast<ZCell*>(sheet->m_sheet->item(x,y));
            if(cell)
            {
                switch(cell->ZGetCellWidgetType())
                {
                case ZCell::CellWidget_No:
                {
                    QString text=sheet->m_sheet->item(x,y)->text();
                    if(text.startsWith("@"))
                    {
                        ZVarSourceInfo varInfo;
                        varInfo.m_varName=text;
                        varInfo.m_varType="Digital";
                        varInfo.m_rule="X";
                        varInfo.m_refValue="X";
                        varInfo.m_cell=QString("%1,%2").arg(x).arg(y);
                        varList.append(varInfo);
                    }
                }
                    break;
                case ZCell::CellWidget_QLabel:
                    break;
                case ZCell::CellWidget_QCheckBox:
                {
                    QCheckBox *cb = static_cast<QCheckBox*>(sheet->m_sheet->cellWidget(x,y));
                    if(cb)
                    {
                        ZVarSourceInfo varInfo;
                        varInfo.m_varName="@check";
                        varInfo.m_varType="Boolean";
                        varInfo.m_rule="X";
                        varInfo.m_refValue="false";
                        varInfo.m_cell=QString("%1,%2").arg(x).arg(y);
                        varList.append(varInfo);
                    }
                }
                    break;
                case ZCell::CellWidget_QComboBox:
                {
                    QComboBox *cb = static_cast<QComboBox*>(sheet->m_sheet->cellWidget(x,y));
                    if(cb)
                    {
                        ZVarSourceInfo varInfo;
                        varInfo.m_varName="@select";
                        varInfo.m_varType="String";
                        varInfo.m_rule="X";
                        varInfo.m_refValue=cb->currentText();
                        varInfo.m_cell=QString("%1,%2").arg(x).arg(y);
                        varList.append(varInfo);
                    }
                }
                    break;
                case ZCell::CellWidget_QSpinBox:
                {
                    QSpinBox *cb = static_cast<QSpinBox*>(sheet->m_sheet->cellWidget(x,y));
                    if(cb)
                    {
                        ZVarSourceInfo varInfo;
                        varInfo.m_varName="@spin";
                        varInfo.m_varType="Digital";
                        varInfo.m_rule=QString::number(cb->minimum(),10)+"-X-"+QString::number(cb->maximum(),10);
                        varInfo.m_refValue=QString::number(cb->value(),10);
                        varInfo.m_cell=QString("%1,%2").arg(x).arg(y);
                        varList.append(varInfo);
                    }
                }
                    break;
                case ZCell::CellWidget_QLineEdit:
                    break;
                case ZCell::CellWidget_QDateTimeEdit:
                {
                    QDateTimeEdit *dte = static_cast<QDateTimeEdit*>(sheet->m_sheet->cellWidget(x,y));
                    if(dte)
                    {
                        ZVarSourceInfo varInfo;
                        varInfo.m_varName="@datetime";
                        varInfo.m_varType="Datetime";
                        varInfo.m_rule=dte->dateTime().toString("yyyyMMddhhmmss")+"-X-"+dte->dateTime().toString("yyyyMMddhhmmss");
                        varInfo.m_refValue=dte->dateTime().toString("yyyyMMddhhmmss");
                        varInfo.m_cell=QString("%1,%2").arg(x).arg(y);
                        varList.append(varInfo);
                    }
                }
                    break;
                }
            }
        }
    }
    /////////////////////////////////////////////////////
    //Examples                  5
    //VarName   Type   Rule  RefValue    Cell
    //@username String  =    zhangshaoyan 1,1
    //@age  Digital   0-X-100  32        1,2
    //@birth Date     20170903080901-X-20200901120023 20180306121023   1,3
    //@marrage  Boolean       true         1,4
    //Data.


    //row counter.
    qint32 nExcelRows=1;

    //write var number info row 1.
    xlsx.write(nExcelRows,1,"Examples",fmt);
    xlsx.write(nExcelRows,5,QString::number(varList.size(),10),fmt);
    nExcelRows++;
    //write Example data.
    xlsx.write(nExcelRows,1,"VarName",fmt);
    xlsx.write(nExcelRows,2,"Type",fmt);
    xlsx.write(nExcelRows,3,"Rule",fmt);
    xlsx.write(nExcelRows,4,"RefValue",fmt);
    xlsx.write(nExcelRows,5,"Cell",fmt);
    nExcelRows++;
    xlsx.write(nExcelRows,1,"@username",fmt);
    xlsx.write(nExcelRows,2,"String",fmt);
    xlsx.write(nExcelRows,3,"X",fmt);
    xlsx.write(nExcelRows,4,"zhangshaoyan",fmt);
    xlsx.write(nExcelRows,5,"1,1",fmt);
    nExcelRows++;
    xlsx.write(nExcelRows,1,"@age",fmt);
    xlsx.write(nExcelRows,2,"Digital",fmt);
    xlsx.write(nExcelRows,3,"0-X-100",fmt);
    xlsx.write(nExcelRows,4,"32",fmt);
    xlsx.write(nExcelRows,5,"1,2",fmt);
    nExcelRows++;
    xlsx.write(nExcelRows,1,"@birth",fmt);
    xlsx.write(nExcelRows,2,"Datetime",fmt);
    xlsx.write(nExcelRows,3,"20170903080901-X-20200901120023",fmt);
    xlsx.write(nExcelRows,4,"20180306121023",fmt);
    xlsx.write(nExcelRows,5,"1,3",fmt);
    nExcelRows++;
    xlsx.write(nExcelRows,1,"@marrage",fmt);
    xlsx.write(nExcelRows,2,"Boolean",fmt);
    xlsx.write(nExcelRows,3,"X",fmt);
    xlsx.write(nExcelRows,4,"true/false",fmt);
    xlsx.write(nExcelRows,5,"1,4",fmt);
    nExcelRows++;

    //write real data.
    xlsx.write(nExcelRows,1,"Data",fmt);
    nExcelRows++;

    //write excel head in row 7.
    xlsx.write(nExcelRows,1,"VarName",fmt);
    xlsx.write(nExcelRows,2,"Type",fmt);
    xlsx.write(nExcelRows,3,"Rule",fmt);
    xlsx.write(nExcelRows,4,"RefValue",fmt);
    xlsx.write(nExcelRows,5,"Cell",fmt);
    nExcelRows++;

    //write excel data.
    for(qint32 i=0;i<varList.size();i++)
    {
        ZVarSourceInfo varInfo=varList.at(i);
        xlsx.write(nExcelRows,1,varInfo.m_varName,fmt);
        xlsx.write(nExcelRows,2,varInfo.m_varType,fmt);
        xlsx.write(nExcelRows,3,varInfo.m_rule,fmt);
        xlsx.write(nExcelRows,4,varInfo.m_refValue,fmt);
        xlsx.write(nExcelRows,5,varInfo.m_cell,fmt);
        nExcelRows++;
    }
    //save.
    if(!xlsx.saveAs(fileName))
    {
        QMessageBox::information(this,tr("失败提示"),tr("导出变量源模板文件%1失败!").arg(fileName));
        return;
    }
    QMessageBox::information(this,tr("成功提示"),tr("变量源模板导出Excel文件成功!\n%1").arg(fileName));
}
void PTemplateEditor::ZSlotImportVarSource()
{

}
void PTemplateEditor::ZSetTextAlignment(qint32 alignment)
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(!sheet)
    {
        return;
    }

    qint32 tRow=sheet->m_sheet->selectedRanges().first().topRow();
    qint32 tColumn=sheet->m_sheet->selectedRanges().first().leftColumn();
    qint32 tRowCnt=sheet->m_sheet->selectedRanges().last().bottomRow()-sheet->m_sheet->selectedRanges().first().topRow() + 1;
    qint32 tColumnCnt=sheet->m_sheet->selectedRanges().last().rightColumn()-sheet->m_sheet->selectedRanges().first().leftColumn() + 1;
    for(qint32 i=tRow;i<=tRow+tRowCnt;i++)
    {
        for(qint32 j=tColumn;j<=tColumn+tColumnCnt;j++)
        {
            qint32 tAlignment=sheet->m_sheet->item(i,j)->textAlignment();
            switch(alignment)
            {
            case Qt::AlignLeft:
                tAlignment|=Qt::AlignLeft;
                tAlignment&=~Qt::AlignHCenter;
                tAlignment&=~Qt::AlignRight;
                break;
            case Qt::AlignHCenter:
                tAlignment&=~Qt::AlignLeft;
                tAlignment|=Qt::AlignHCenter;
                tAlignment&=~Qt::AlignRight;
                break;
            case Qt::AlignRight:
                tAlignment&=~Qt::AlignLeft;
                tAlignment&=~Qt::AlignHCenter;
                tAlignment|=Qt::AlignRight;
                break;
            case Qt::AlignTop:
                tAlignment|=Qt::AlignTop;
                tAlignment&=~Qt::AlignVCenter;
                tAlignment&=~Qt::AlignBottom;
                break;
            case Qt::AlignVCenter:
                tAlignment&=~Qt::AlignTop;
                tAlignment|=Qt::AlignVCenter;
                tAlignment&=~Qt::AlignBottom;
                break;
            case Qt::AlignBottom:
                tAlignment&=~Qt::AlignTop;
                tAlignment&=~Qt::AlignVCenter;
                tAlignment|=Qt::AlignBottom;
                break;
            default:
                break;
            }
            sheet->m_sheet->item(i,j)->setTextAlignment(tAlignment);
        }
    }
}
//remove tab.
void PTemplateEditor::ZSlotRemoveTab(qint32 index)
{
    if(index==0)
    {
        //make sure the tab0 cannot be closed.
        return;
    }

    if(this->m_tabWidget->tabText(index).startsWith("<*>"))
    {
        if(QMessageBox::question(this,tr("操作提示"),tr("模板被更改,尚未保存!\n您确认要关闭吗?"),QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
        {
            return;
        }
    }

    //delete it to remove it from tab widget.
    this->m_tabWidget->removeTab(index);
    delete this->m_tabWidget->widget(index);
}
void PTemplateEditor::ZSlotSheetDataChanged(QString templateName)
{
    for(qint32 i=1;i<this->m_tabWidget->count();i++)
    {
        if(this->m_tabWidget->tabText(i)==templateName)
        {
            this->m_tabWidget->setTabText(i,"<*>"+templateName);
            break;
        }
    }
}
void PTemplateEditor::ZSlotAatchDetach()
{
    QAction *src=qobject_cast<QAction*>(this->sender());
    if(src==this->m_actDetach)
    {
        emit this->ZSignalDetach("TemplateEditor");
    }else if(src==this->m_actAatch)
    {
        emit this->ZSignalAatch("TemplateEditor");
    }
}
void PTemplateEditor::ZSlotPrintHtml()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(!sheet)
    {
        return;
    }
    QString templateName=sheet->m_sheet->ZGetTemplateName();
    QString creator;
    QString createTime;
    for(qint32 i=0;i<this->m_templateWidget->m_treeWidget->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=this->m_templateWidget->m_treeWidget->topLevelItem(i);
        if(item->text(0)==templateName)
        {
            creator=item->text(3);
            createTime=item->text(4);
            break;
        }
    }
    QString note=QString("创建人:%1,创建时间:%2").arg(creator).arg(createTime);
    QString html;
    qint32 ret=ZGetQTableWidgetHtml(tr("模板:%1").arg(templateName),note,sheet->m_sheet,&html);
    if(ret<0)
    {
        return;
    }
    QString fileName=QFileDialog::getSaveFileName(this,tr("打印html"),tr("./%1.html").arg(templateName),"*.html");
    if(fileName.isEmpty())
    {
        return;
    }
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(html.toUtf8());
        file.close();
        QMessageBox::information(this,tr("操作成功"),tr("打印模板\n%1\n到文件\n%2\n成功!").arg(templateName).arg(fileName));
    }
}
void PTemplateEditor::ZSlotPrintPdf()
{
    if(this->m_tabWidget->currentIndex()==0)
    {
        //bypass template editor tab page.
        return;
    }
    ZSheetWidget *sheet=qobject_cast<ZSheetWidget*>(this->m_tabWidget->currentWidget());
    if(!sheet)
    {
        return;
    }
    QString templateName=sheet->m_sheet->ZGetTemplateName();
    QString creator;
    QString createTime;
    for(qint32 i=0;i<this->m_templateWidget->m_treeWidget->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=this->m_templateWidget->m_treeWidget->topLevelItem(i);
        if(item->text(0)==templateName)
        {
            creator=item->text(3);
            createTime=item->text(4);
            break;
        }
    }
    QString note=QString("创建人:%1,创建时间:%2").arg(creator).arg(createTime);
    QString html;
    qint32 ret=ZGetQTableWidgetPdf(tr("模板:%1").arg(templateName),note,sheet->m_sheet,&html);
    if(ret<0)
    {
        return;
    }
    QString fileName=QFileDialog::getSaveFileName(this,tr("打印Pdf"),tr("./%1.pdf").arg(templateName),"*.pdf");
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
void PTemplateEditor::ZSlotPrint()
{

}
void PTemplateEditor::ZSlotHelp()
{

}
void PTemplateEditor::ZSlotTemplateTreePopupMenu(const QPoint &pt)
{
    Q_UNUSED(pt);
    QTreeWidgetItem *item=this->m_templateWidget->m_treeWidget->currentItem();
    if(NULL==item)
    {
        return;
    }
    QMenu popMenu;
    QAction actNew(QIcon(":/TemplateEditor/images/TemplateEditor/NewTemplate.png"),tr("新建模板"));
    QAction actOpen(QIcon(":/TemplateEditor/images/TemplateEditor/OpenTemplate.png"),tr("打开模板"));
    QAction actDel(QIcon(":/TemplateEditor/images/TemplateEditor/DelTemplate.png"),tr("删除模板"));
    QAction actExport(QIcon(":/UserManager/images/UserManager/Export.png"),tr("导出Excel"));
    connect(&actNew,SIGNAL(triggered(bool)),this,SLOT(ZSlotNewTemplate()));
    connect(&actOpen,SIGNAL(triggered(bool)),this,SLOT(ZSlotOpenTemplate()));
    connect(&actDel,SIGNAL(triggered(bool)),this,SLOT(ZSlotDelTemplate()));
    popMenu.addAction(&actNew);
    popMenu.addAction(&actOpen);
    popMenu.addAction(&actDel);
    popMenu.addAction(&actExport);
    popMenu.exec(QCursor::pos());
}
void PTemplateEditor::ZSlotVarSourceTreePopupMenu(const QPoint &pt)
{
    Q_UNUSED(pt);
    QTreeWidgetItem *item=this->m_templateWidget->m_treeVarSource->currentItem();
    if(NULL==item)
    {
        return;
    }
    QMenu popMenu;
    QAction actNew(QIcon(":/TemplateEditor/images/TemplateEditor/NewTemplate.png"),tr("新建变量源"));
    QAction actOpen(QIcon(":/TemplateEditor/images/TemplateEditor/OpenTemplate.png"),tr("打开变量源"));
    QAction actDel(QIcon(":/TemplateEditor/images/TemplateEditor/DelTemplate.png"),tr("删除变量源"));
    QAction actExport(QIcon(":/UserManager/images/UserManager/Export.png"),tr("导出Excel"));
    connect(&actNew,SIGNAL(triggered(bool)),this,SLOT(ZSlotAddVarSource()));
    connect(&actOpen,SIGNAL(triggered(bool)),this,SLOT(ZSlotOpenVarSource()));
    connect(&actDel,SIGNAL(triggered(bool)),this,SLOT(ZSlotDelVarSource()));
    popMenu.addAction(&actNew);
    popMenu.addAction(&actOpen);
    popMenu.addAction(&actDel);
    popMenu.addAction(&actExport);
    popMenu.exec(QCursor::pos());
}
void PTemplateEditor::ZAddLogMsg(QString logMsg)
{
    emit this->ZSignalLogMsg(QString("<TemplateEditor>:")+logMsg);
}
ZTemplateWidget::ZTemplateWidget()
{
    //left part.
    this->m_splitterV=new QSplitter(Qt::Vertical);
    this->m_treeWidget=new QTreeWidget(this->m_splitterV);
    this->m_treeWidget->setIconSize(QSize(24,24));
    this->m_treeWidget->setColumnCount(5);
    QStringList headerList;
    headerList<<tr("模板名称");
    headerList<<tr("绑定变量源");
    headerList<<tr("占用磁盘");
    headerList<<tr("创建者");
    headerList<<tr("创建时间");
    this->m_treeWidget->setHeaderLabels(headerList);
    this->m_treeVarSource=new QTreeWidget(this->m_splitterV);
    this->m_treeVarSource->setColumnCount(4);
    QStringList varSourceHeaderList;
    varSourceHeaderList<<tr("变量源");
    varSourceHeaderList<<tr("引用计数");
    varSourceHeaderList<<tr("创建者");
    varSourceHeaderList<<tr("创建时间");
    this->m_treeVarSource->setHeaderLabels(varSourceHeaderList);
    this->m_splitterV->setStretchFactor(0,1);
    this->m_splitterV->setStretchFactor(1,1);
    this->m_vLayoutLeft=new QVBoxLayout;
    this->m_vLayoutLeft->addWidget(this->m_splitterV);
    this->m_frmLeft=new QFrame;
    this->m_frmLeft->setLayout(this->m_vLayoutLeft);

    //right part.
    this->m_view=new ZTemplateVarSrcView;
    this->m_splitterH=new QSplitter(Qt::Horizontal);
    this->m_splitterH->addWidget(this->m_frmLeft);
    this->m_splitterH->addWidget(this->m_view);
    this->m_splitterH->setStretchFactor(0,3);
    this->m_splitterH->setStretchFactor(1,2);

    //main layout.
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_splitterH);
    this->setLayout(this->m_vLayout);

    connect(this->m_treeWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ZSlotTemplateTreeDoubleClicked(QModelIndex)));
    connect(this->m_treeVarSource,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ZSlotVarSourceTreeDoubleClicked(QModelIndex)));
    connect(this->m_treeWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(ZSlotUpdateView(QModelIndex)));
}
ZTemplateWidget::~ZTemplateWidget()
{
    delete this->m_treeWidget;
    delete this->m_treeVarSource;
    delete this->m_splitterV;
    delete this->m_vLayoutLeft;
    delete this->m_frmLeft;

    delete this->m_view;
    delete this->m_splitterH;

    delete this->m_vLayout;
}

void ZTemplateWidget::ZSlotTemplateTreeDoubleClicked(QModelIndex index)
{
    QTreeWidgetItem *item=this->m_treeWidget->topLevelItem(index.row());
    if(item)
    {
        emit this->ZSignalOpenTemplate(item->text(0));
    }
}
void ZTemplateWidget::ZSlotVarSourceTreeDoubleClicked(QModelIndex index)
{
    QTreeWidgetItem *item=this->m_treeVarSource->topLevelItem(index.row());
    if(item)
    {
        emit this->ZSignalOpenVarSource(item->text(0));
    }
}
void ZTemplateWidget::ZSlotUpdateView(QModelIndex index)
{
    QTreeWidgetItem *item=this->m_treeWidget->topLevelItem(index.row());
    if(item)
    {
        this->m_view->ZSetData(item->text(0),item->text(1));
    }
}
QString ZTemplateWidget::ZGetWidgetTypeName()
{
    return QString("TemplateWidget");
}

ZSheetWidget::ZSheetWidget()
{
    this->m_sheet=new ZSheet;
    this->m_treeWidget=new QTreeWidget;

    this->m_treeWidget->setColumnCount(5);
    this->m_treeWidget->setStyleSheet("QTreeView::item:hover{background-color:rgb(0,255,0,50)}"
                                      "QTreeView::item:selected{background-color:rgb(255,0,0,100)}"
                                      "");
    this->m_generalVarItem=new QTreeWidgetItem;
    this->m_generalVarItem->setText(0,tr("普通变量"));
    this->m_generalVarItem->setText(1,tr("绑定单元格"));
    this->m_generalVarItem->setText(2,tr("变量类型"));
    this->m_generalVarItem->setText(3,tr("变量规则"));
    this->m_generalVarItem->setText(4,tr("参考值"));
    this->m_autoVarItem=new QTreeWidgetItem;
    this->m_autoVarItem->setText(0,tr("自动变量"));
    this->m_autoVarItem->setText(1,tr("绑定单元格"));
    this->m_autoVarItem->setText(2,tr("变量类型"));
    this->m_autoVarItem->setText(3,tr("触发动作"));
    this->m_autoVarItem->setText(4,tr("预定义值"));
    this->m_treeWidget->addTopLevelItem(this->m_generalVarItem);
    this->m_treeWidget->addTopLevelItem(this->m_autoVarItem);
    this->m_treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this->m_treeWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ZSlotPopMenu(QPoint)));

#define ICON_W  24
#define ICON_H  24

    //line2.
    this->m_tbAlignLeft=new QToolButton;
    this->m_tbAlignLeft->setToolTip(tr("左对齐"));
    this->m_tbAlignLeft->setIconSize(QSize(ICON_W,ICON_H));
    this->m_tbAlignLeft->setIcon(QIcon(":/alignment/images/alignment/HAlignLeft.png"));
    this->m_tbAlignLeft->setToolButtonStyle(Qt::ToolButtonIconOnly);

    this->m_tbAlignHCenter=new QToolButton;
    this->m_tbAlignHCenter->setToolTip(tr("水平居中"));
    this->m_tbAlignHCenter->setIconSize(QSize(ICON_W,ICON_H));
    this->m_tbAlignHCenter->setIcon(QIcon(":/alignment/images/alignment/HAlignCenter.png"));
    this->m_tbAlignHCenter->setToolButtonStyle(Qt::ToolButtonIconOnly);

    this->m_tbAlignRight=new QToolButton;
    this->m_tbAlignRight->setToolTip(tr("右对齐"));
    this->m_tbAlignRight->setIconSize(QSize(ICON_W,ICON_H));
    this->m_tbAlignRight->setIcon(QIcon(":/alignment/images/alignment/HAlignRight.png"));
    this->m_tbAlignRight->setToolButtonStyle(Qt::ToolButtonIconOnly);

    this->m_tbAlignTop=new QToolButton;
    this->m_tbAlignTop->setToolTip(tr("顶部对齐"));
    this->m_tbAlignTop->setIconSize(QSize(ICON_W,ICON_H));
    this->m_tbAlignTop->setIcon(QIcon(":/alignment/images/alignment/VAlignTop.png"));
    this->m_tbAlignTop->setToolButtonStyle(Qt::ToolButtonIconOnly);


    this->m_tbAlignVCenter=new QToolButton;
    this->m_tbAlignVCenter->setToolTip(tr("垂直居中"));
    this->m_tbAlignVCenter->setIconSize(QSize(ICON_W,ICON_H));
    this->m_tbAlignVCenter->setIcon(QIcon(":/alignment/images/alignment/VAlignCenter.png"));
    this->m_tbAlignVCenter->setToolButtonStyle(Qt::ToolButtonIconOnly);


    this->m_tbAlignBottom=new QToolButton;
    this->m_tbAlignBottom->setToolTip(tr("底部对齐"));
    this->m_tbAlignBottom->setIconSize(QSize(ICON_W,ICON_H));
    this->m_tbAlignBottom->setIcon(QIcon(":/alignment/images/alignment/VAlignBottom.png"));
    this->m_tbAlignBottom->setToolButtonStyle(Qt::ToolButtonIconOnly);

    //line3.
    this->m_tbAlignCenter=new QToolButton;
    this->m_tbAlignCenter->setToolTip(tr("水平垂直居中"));
    this->m_tbAlignCenter->setIconSize(QSize(ICON_W,ICON_H));
    this->m_tbAlignCenter->setIcon(QIcon(":/alignment/images/alignment/AlignCenter.png"));
    this->m_tbAlignCenter->setToolButtonStyle(Qt::ToolButtonIconOnly);

    this->m_tbMerge=new QToolButton;
    this->m_tbMerge->setToolTip(tr("合并单元格"));
    this->m_tbMerge->setIconSize(QSize(ICON_W,ICON_H));
    this->m_tbMerge->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/Merge.png"));
    this->m_tbMerge->setToolButtonStyle(Qt::ToolButtonIconOnly);
    this->m_tbSplit=new QToolButton;
    this->m_tbSplit->setToolTip(tr("拆分单元格"));
    this->m_tbSplit->setIconSize(QSize(ICON_W,ICON_H));
    this->m_tbSplit->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/Split.png"));
    this->m_tbSplit->setToolButtonStyle(Qt::ToolButtonIconOnly);
    this->m_tbSplit=new QToolButton;
    this->m_tbSplit->setToolTip(tr("拆分单元格"));
    this->m_tbSplit->setIconSize(QSize(ICON_W,ICON_H));
    this->m_tbSplit->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/Split.png"));
    this->m_tbSplit->setToolButtonStyle(Qt::ToolButtonIconOnly);
    this->m_tbAutoAdjust=new QToolButton;
    this->m_tbAutoAdjust->setToolTip(tr("自动调整列宽和行高"));
    this->m_tbAutoAdjust->setIconSize(QSize(ICON_W,ICON_H));
    this->m_tbAutoAdjust->setIcon(QIcon(":/TemplateEditor/images/TemplateEditor/AutoAdjust.png"));
    this->m_tbAutoAdjust->setToolButtonStyle(Qt::ToolButtonIconOnly);

    this->m_leXY=new QLineEdit;
    this->m_leXY->setFocusPolicy(Qt::NoFocus);
    this->m_leXY->setAlignment(Qt::AlignCenter);
    this->m_leXY->setText(tr("(1,1)"));
    this->m_sheet->setCurrentCell(0,0);

    this->m_gLayoutBtn=new QGridLayout;
    //line2.
    this->m_gLayoutBtn->addWidget(this->m_tbAlignLeft,0,0,1,1);
    this->m_gLayoutBtn->addWidget(this->m_tbAlignHCenter,0,1,1,1);
    this->m_gLayoutBtn->addWidget(this->m_tbAlignRight,0,2,1,1);
    this->m_gLayoutBtn->addWidget(this->m_tbAlignTop,0,3,1,1);
    this->m_gLayoutBtn->addWidget(this->m_tbAlignVCenter,0,4,1,1);
    this->m_gLayoutBtn->addWidget(this->m_tbAlignBottom,0,5,1,1);
    //line3.
    this->m_gLayoutBtn->addWidget(this->m_tbAlignCenter,1,0,1,1);
    this->m_gLayoutBtn->addWidget(this->m_tbMerge,1,1,1,1);
    this->m_gLayoutBtn->addWidget(this->m_tbSplit,1,2,1,1);
    this->m_gLayoutBtn->addWidget(this->m_tbAutoAdjust,1,3,1,1);
    this->m_gLayoutBtn->addWidget(this->m_leXY,1,4,1,2);

    connect(this->m_tbAlignLeft,SIGNAL(clicked(bool)),this,SLOT(ZSlotAlignmentChanged()));
    connect(this->m_tbAlignHCenter,SIGNAL(clicked(bool)),this,SLOT(ZSlotAlignmentChanged()));
    connect(this->m_tbAlignRight,SIGNAL(clicked(bool)),this,SLOT(ZSlotAlignmentChanged()));
    connect(this->m_tbAlignTop,SIGNAL(clicked(bool)),this,SLOT(ZSlotAlignmentChanged()));
    connect(this->m_tbAlignVCenter,SIGNAL(clicked(bool)),this,SLOT(ZSlotAlignmentChanged()));
    connect(this->m_tbAlignBottom,SIGNAL(clicked(bool)),this,SLOT(ZSlotAlignmentChanged()));

    connect(this->m_tbAlignCenter,SIGNAL(clicked(bool)),this,SLOT(ZSlotAlignmentChanged()));
    connect(this->m_tbMerge,SIGNAL(clicked(bool)),this,SLOT(ZSlotMergeSplitCell()));
    connect(this->m_tbSplit,SIGNAL(clicked(bool)),this,SLOT(ZSlotMergeSplitCell()));
    connect(this->m_tbAutoAdjust,SIGNAL(clicked(bool)),this,SLOT(ZSlotCellAutoAdjust()));
    //bottom horizontal layout.
    this->m_hLayoutBottom=new QHBoxLayout;
    this->m_hLayoutBottom->addWidget(this->m_treeWidget);
    this->m_hLayoutBottom->addLayout(this->m_gLayoutBtn);
    this->m_frmBottom=new QFrame;
    this->m_frmBottom->setLayout(this->m_hLayoutBottom);

    //main vertical spliter.
    this->m_spliter=new QSplitter(Qt::Vertical);
    this->m_spliter->addWidget(this->m_sheet);
    this->m_spliter->addWidget(this->m_frmBottom);
    this->m_spliter->setStretchFactor(0,8);
    this->m_spliter->setStretchFactor(1,2);

    //main layout.
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_spliter);
    this->setLayout(this->m_vLayout);

    connect(this->m_sheet,SIGNAL(ZSignalSheetChanged(QString)),this,SIGNAL(ZSignalDataChanged(QString)));
    connect(this->m_sheet,SIGNAL(cellClicked(int,int)),this,SLOT(ZSlotCellActivated(qint32,qint32)));
    connect(this->m_treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(ZSlotVarDblClicked(QTreeWidgetItem*,int)));

}
ZSheetWidget::~ZSheetWidget()
{

    delete this->m_sheet;
    delete this->m_generalVarItem;
    delete this->m_autoVarItem;
    delete this->m_treeWidget;
    //line2.
    delete this->m_tbAlignLeft;
    delete this->m_tbAlignHCenter;
    delete this->m_tbAlignRight;
    delete this->m_tbAlignTop;
    delete this->m_tbAlignVCenter;
    delete this->m_tbAlignBottom;
    delete this->m_gLayoutBtn;
    //line3.
    delete this->m_tbAlignCenter;
    delete this->m_tbMerge;
    delete this->m_tbSplit;
    delete this->m_tbAutoAdjust;
    delete this->m_leXY;

    delete this->m_hLayoutBottom;
    delete this->m_frmBottom;

    delete this->m_spliter;
    delete this->m_vLayout;
}
void ZSheetWidget::ZSlotAlignmentChanged()
{
    QToolButton *srcBtn=qobject_cast<QToolButton*>(this->sender());
    if(srcBtn==this->m_tbAlignCenter)
    {
        emit this->ZSignalAlignmentChanged(0);
    }else if(srcBtn==this->m_tbAlignLeft)
    {
        emit this->ZSignalAlignmentChanged(1);
    }else if(srcBtn==this->m_tbAlignHCenter)
    {
        emit this->ZSignalAlignmentChanged(2);
    }else if(srcBtn==this->m_tbAlignRight)
    {
        emit this->ZSignalAlignmentChanged(3);
    }else if(srcBtn==this->m_tbAlignTop)
    {
        emit this->ZSignalAlignmentChanged(4);
    }else if(srcBtn==this->m_tbAlignVCenter)
    {
        emit this->ZSignalAlignmentChanged(5);
    }else if(srcBtn==this->m_tbAlignBottom)
    {
        emit this->ZSignalAlignmentChanged(6);
    }
}
void ZSheetWidget::ZSlotMergeSplitCell()
{
    QToolButton *srcBtn=qobject_cast<QToolButton*>(this->sender());
    if(srcBtn==this->m_tbMerge)
    {
        emit this->ZSignalMergeCell();
    }else if(srcBtn==this->m_tbSplit)
    {
        emit this->ZSignalSplitCell();
    }
}
QString ZSheetWidget::ZGetWidgetTypeName()
{
    return QString("SheetWidget");
}
void ZSheetWidget::ZSlotVarDblClicked(QTreeWidgetItem*item,int column)
{
    if(item->parent()==this->m_generalVarItem || item->parent()==this->m_autoVarItem)
    {
        if(column==1)
        {
            QString xy=item->text(1);
            QStringList xyList=xy.split(",");
            if(xyList.size()!=2)
            {
                return;
            }
            this->m_sheet->setCurrentCell(xyList.at(0).toInt()-1,xyList.at(1).toInt()-1);
        }
    }
}
QString ZSheetWidget::ZGetTemplateXmlData()
{
    QMap<qint32,QString> tSizeMap;
    QMap<qint32,QString>::iterator tIt;
    qint32 tIdCnt=0;
    QString formatXml;
    QXmlStreamWriter  tXmlWriter(&formatXml);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("PMSTemplate"));
    tXmlWriter.writeAttribute(QString("name"),this->m_sheet->ZGetTemplateName());
    //<row id=x height=xx>a,b,c,d</row>
    for(int i=0;i<this->m_sheet->rowCount();i++)
    {
        qint32 tRowHeight=this->m_sheet->rowHeight(i);
        if(!tSizeMap.contains(tRowHeight))
        {
            tSizeMap.insert(tRowHeight,QString("%1").arg(i));
        }else{
            QString rowList=tSizeMap.value(tRowHeight);
            rowList.append(QString(",%1").arg(i));
            tSizeMap[tRowHeight]=rowList;
        }
    }
    tIdCnt=0;
    for(tIt=tSizeMap.begin();tIt!=tSizeMap.end();tIt++)
    {
        tXmlWriter.writeStartElement(QString("row"));
        tXmlWriter.writeAttribute(QString("id"),QString("%1").arg(tIdCnt++));
        tXmlWriter.writeAttribute(QString("height"),QString("%1").arg(tIt.key()));
        tXmlWriter.writeCharacters(tIt.value());
        tXmlWriter.writeEndElement();//row.
    }
    tSizeMap.clear();

    //<col id=x width=x>a,b,c,d</col>
    for(int i=0;i<this->m_sheet->columnCount();i++)
    {
        qint32 tColWidth=this->m_sheet->columnWidth(i);
        if(!tSizeMap.contains(tColWidth))
        {
            tSizeMap.insert(tColWidth,QString("%1").arg(i));
        }else{
            QString colList=tSizeMap.value(tColWidth);
            colList.append(QString(",%1").arg(i));
            tSizeMap[tColWidth]=colList;
        }
    }
    tIdCnt=0;
    for(tIt=tSizeMap.begin();tIt!=tSizeMap.end();tIt++)
    {
        tXmlWriter.writeStartElement(QString("col"));
        tXmlWriter.writeAttribute(QString("id"),QString("%1").arg(tIdCnt++));
        tXmlWriter.writeAttribute(QString("width"),QString("%1").arg(tIt.key()));
        tXmlWriter.writeCharacters(tIt.value());
        tXmlWriter.writeEndElement();//col.
    }
    tSizeMap.clear();

    //<color id=x>fAlpha,fRed,fGreen,fBlue,bAlpha,bRed,bGreen,bBlue</color>
    //<font id=x>songti,12,yes,yes</font>
    QList<QString> colorIndexTable;
    QList<QString> fontIndexTable;
    for(qint32 i=0;i<this->m_sheet->rowCount();i++)
    {
        for(qint32 j=0;j<this->m_sheet->columnCount();j++)
        {
            ZCell *tCell=static_cast<ZCell*>(this->m_sheet->item(i,j));
            if(tCell)
            {
                //color.
                QColor fgColor=tCell->ZGetForegroundColor();
                QColor bgColor=tCell->ZGetBackgroundColor();
                QString colorStr=QString("%1,%2,%3,%4,%5,%6,%7,%8").arg(fgColor.alpha()).arg(fgColor.red()).arg(fgColor.green()).arg(fgColor.blue()).arg(bgColor.alpha()).arg(bgColor.red()).arg(bgColor.green()).arg(bgColor.blue());
                if(!colorIndexTable.contains(colorStr))
                {
                    colorIndexTable.append(colorStr);
                }
                //font.
                QFont tFont=tCell->ZGetFont();
                QString fontStr=QString("%1,%2,%3,%4").arg(tFont.family()).arg(tFont.pointSize()).arg(tFont.bold()?QString("1"):QString("0")).arg(tFont.italic()?QString("1"):QString("0"));
                if(!fontIndexTable.contains(fontStr))
                {
                    fontIndexTable.append(fontStr);
                }
            }
        }
    }
    //color.
    tIdCnt=0;
    for(qint32 i=0;i<colorIndexTable.count();i++)
    {
        tXmlWriter.writeStartElement(QString("color"));
        tXmlWriter.writeAttribute(QString("id"),QString("%1").arg(tIdCnt++));
        tXmlWriter.writeCharacters(colorIndexTable.at(i));
        tXmlWriter.writeEndElement();//color.
    }
    //font.
    tIdCnt=0;
    for(qint32 i=0;i<fontIndexTable.count();i++)
    {
        tXmlWriter.writeStartElement(QString("font"));
        tXmlWriter.writeAttribute(QString("id"),QString("%1").arg(tIdCnt++));
        tXmlWriter.writeCharacters(fontIndexTable.at(i));
        tXmlWriter.writeEndElement();//font.
    }

    //<fix xy=m,n font=1 color=1 span=1,2 frame=1,1,1,1 frameColor=r,g,b frameWidth=n>data</fix>
    for(qint32 i=0;i<this->m_sheet->rowCount();i++)
    {
        for(qint32 j=0;j<this->m_sheet->columnCount();j++)
        {
            ZCell *tCell=static_cast<ZCell*>(this->m_sheet->item(i,j));
            if(tCell)
            {
                QColor fgColor=tCell->ZGetForegroundColor();
                QColor bgColor=tCell->ZGetBackgroundColor();
                QString colorStr=QString("%1,%2,%3,%4,%5,%6,%7,%8").arg(fgColor.alpha()).arg(fgColor.red()).arg(fgColor.green()).arg(fgColor.blue()).arg(bgColor.alpha()).arg(bgColor.red()).arg(bgColor.green()).arg(bgColor.blue());
                QFont tFont=tCell->ZGetFont();
                QString fontStr=QString("%1,%2,%3,%4").arg(tFont.family()).arg(tFont.pointSize()).arg(tFont.bold()?QString("1"):QString("0")).arg(tFont.italic()?QString("1"):QString("0"));
                tXmlWriter.writeStartElement(QString("fix"));
                tXmlWriter.writeAttribute(QString("xy"),QString("%1,%2").arg(i).arg(j));
                tXmlWriter.writeAttribute(QString("font"),QString("%1").arg(fontIndexTable.indexOf(fontStr)));
                tXmlWriter.writeAttribute(QString("color"),QString("%1").arg(colorIndexTable.indexOf(colorStr)));
                tXmlWriter.writeAttribute(QString("span"),QString("%1,%2").arg(this->m_sheet->rowSpan(i,j)).arg(this->m_sheet->columnSpan(i,j)));
                tXmlWriter.writeAttribute(QString("frame"),QString("%1,%2,%3,%4").arg(tCell->ZTopFrameIsSet()?1:0).arg(tCell->ZBottomFrameIsSet()?1:0).arg(tCell->ZLeftFrameIsSet()?1:0).arg(tCell->ZRightFrameIsSet()?1:0));
                tXmlWriter.writeAttribute(QString("frameColor"),QString("%1,%2,%3").arg(tCell->ZGetFrameColor().red()).arg(tCell->ZGetFrameColor().green()).arg(tCell->ZGetFrameColor().blue()));
                tXmlWriter.writeAttribute(QString("frameWidth"),QString("%1").arg(tCell->ZGetFrameWidth()));
                tXmlWriter.writeAttribute(QString("align"),QString("%1").arg(tCell->ZGetTextAlignment()));
                tXmlWriter.writeCharacters(tCell->ZGetCellData());
                tXmlWriter.writeEndElement();//fix.
            }
        }
    }

    //<pic xy=m,n>xxxxx</pic>
    for(qint32 i=0;i<this->m_sheet->rowCount();i++)
    {
        for(qint32 j=0;j<this->m_sheet->columnCount();j++)
        {
            ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(i,j));
            if(cell)
            {
                if(cell->ZGetCellWidgetType()==ZCell::CellWidget_QLabel)
                {
                    QLabel *label = static_cast<QLabel*>(this->m_sheet->cellWidget(i,j));
                    if(label)
                    {
                        const QPixmap *pixmap=label->pixmap();
                        QByteArray byteArray;
                        QBuffer buffer(&byteArray);
                        buffer.open(QIODevice::WriteOnly);
                        pixmap->save(&buffer,"PNG");
                        tXmlWriter.writeStartElement(QString("pic"));
                        tXmlWriter.writeAttribute(QString("xy"),QString("%1,%2").arg(i).arg(j));
                        tXmlWriter.writeCharacters(byteArray.toBase64());
                        tXmlWriter.writeEndElement();//pic.
                    }
                }
            }
        }
    }
    //checkbox.
    for(qint32 i=0;i<this->m_sheet->rowCount();i++)
    {
        for(qint32 j=0;j<this->m_sheet->columnCount();j++)
        {
            ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(i,j));
            if(cell)
            {
                if(cell->ZGetCellWidgetType()==ZCell::CellWidget_QCheckBox)
                {
                    QCheckBox *cb = static_cast<QCheckBox*>(this->m_sheet->cellWidget(i,j));
                    if(cb)
                    {
                        tXmlWriter.writeStartElement(QString("checkbox"));
                        tXmlWriter.writeAttribute(QString("xy"),QString("%1,%2").arg(i).arg(j));
                        tXmlWriter.writeAttribute(QString("checked"),QString("%1").arg(cb->isChecked()?1:0));
                        tXmlWriter.writeCharacters(cb->text());
                        tXmlWriter.writeEndElement();//checkbox.
                    }
                }
            }
        }
    }
    //combobox
    for(qint32 i=0;i<this->m_sheet->rowCount();i++)
    {
        for(qint32 j=0;j<this->m_sheet->columnCount();j++)
        {
            ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(i,j));
            if(cell)
            {
                if(cell->ZGetCellWidgetType()==ZCell::CellWidget_QComboBox)
                {
                    QComboBox *cb = static_cast<QComboBox*>(this->m_sheet->cellWidget(i,j));
                    if(cb)
                    {
                        tXmlWriter.writeStartElement(QString("combobox"));
                        tXmlWriter.writeAttribute(QString("xy"),QString("%1,%2").arg(i).arg(j));
                        QString val;
                        for(qint32 i=0;i<cb->count();i++)
                        {
                            val.append(cb->itemText(i)+":");
                        }
                        tXmlWriter.writeCharacters(val);
                        tXmlWriter.writeEndElement();//combobox.
                    }
                }
            }
        }
    }

    //spinbox.
    for(qint32 i=0;i<this->m_sheet->rowCount();i++)
    {
        for(qint32 j=0;j<this->m_sheet->columnCount();j++)
        {
            ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(i,j));
            if(cell)
            {
                if(cell->ZGetCellWidgetType()==ZCell::CellWidget_QSpinBox)
                {
                    QSpinBox *sb = static_cast<QSpinBox*>(this->m_sheet->cellWidget(i,j));
                    if(sb)
                    {
                        tXmlWriter.writeStartElement(QString("spinbox"));
                        tXmlWriter.writeAttribute(QString("xy"),QString("%1,%2").arg(i).arg(j));
                        tXmlWriter.writeAttribute(QString("min"),QString("%1").arg(sb->minimum()));
                        tXmlWriter.writeAttribute(QString("max"),QString("%1").arg(sb->maximum()));
                        tXmlWriter.writeCharacters(QString("%1").arg(sb->value()));
                        tXmlWriter.writeEndElement();//spinbox.
                    }
                }
            }
        }
    }
    //datetimeedit.
    for(qint32 i=0;i<this->m_sheet->rowCount();i++)
    {
        for(qint32 j=0;j<this->m_sheet->columnCount();j++)
        {
            ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(i,j));
            if(cell)
            {
                if(cell->ZGetCellWidgetType()==ZCell::CellWidget_QDateTimeEdit)
                {
                    QDateTimeEdit *te = static_cast<QDateTimeEdit*>(this->m_sheet->cellWidget(i,j));
                    if(te)
                    {
                        tXmlWriter.writeStartElement(QString("datetimeedit"));
                        tXmlWriter.writeAttribute(QString("xy"),QString("%1,%2").arg(i).arg(j));
                        tXmlWriter.writeCharacters(QString("sb"));
                        tXmlWriter.writeEndElement();//datetimeedit.
                    }
                }
            }
        }
    }

    //<bindvar xy=m,n type="general" >@var1</geVar>
    for(qint32 i=0;i<this->m_generalVarItem->childCount();i++)
    {
        QTreeWidgetItem *item=this->m_generalVarItem->child(i);
        QString varName=item->text(0);
        QString bindCell=item->text(1);
        QString dataType=item->text(2);
        QString rule=item->text(3);
        QString refVal=item->text(4);
        //only save the bindCell not null.
        if(!bindCell.isEmpty())
        {
            tXmlWriter.writeStartElement(QString("bindvar"));
            tXmlWriter.writeAttribute(QString("xy"),bindCell);
            tXmlWriter.writeAttribute(QString("type"),QString("general"));
            tXmlWriter.writeAttribute(QString("dataType"),dataType);
            tXmlWriter.writeAttribute(QString("rule"),rule);
            tXmlWriter.writeAttribute(QString("refVal"),refVal);
            tXmlWriter.writeCharacters(varName);
            tXmlWriter.writeEndElement();//bindvar.
        }
    }
    //<bindvar xy=m,n type="auto">@var2</autoVar>
    for(qint32 i=0;i<this->m_autoVarItem->childCount();i++)
    {
        QTreeWidgetItem *item=this->m_autoVarItem->child(i);
        QString varName=item->text(0);
        QString bindCell=item->text(1);
        //only save the bindCell is not null.
        if(!bindCell.isEmpty())
        {
            tXmlWriter.writeStartElement(QString("bindvar"));
            tXmlWriter.writeAttribute(QString("xy"),bindCell);
            tXmlWriter.writeAttribute(QString("type"),QString("auto"));
            tXmlWriter.writeCharacters(varName);
            tXmlWriter.writeEndElement();//bindvar.
        }
    }
    tXmlWriter.writeEndElement();//PMSTemplate.
    tXmlWriter.writeEndDocument();
    return formatXml;
}
void ZSheetWidget::ZPutTemplateXmlData(QString xmlData)
{
    QStringList colorList;
    QStringList fontList;
    QXmlStreamReader tXmlReader(xmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("row"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                qint32 height=attr.value(QString("height")).toInt();
                QString rowListStr=tXmlReader.readElementText();
                QStringList rowList=rowListStr.split(",");
                for(qint32 i=0;i<rowList.count();i++)
                {
                    QString rowNo=rowList.at(i);
                    this->m_sheet->setRowHeight(rowNo.toInt(),height);
                }
            }else if(nodeName=="col")
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                qint32 width=attr.value(QString("width")).toInt();
                QString colListStr=tXmlReader.readElementText();
                QStringList colList=colListStr.split(",");
                for(qint32 i=0;i<colList.count();i++)
                {
                    QString colNo=colList.at(i);
                    this->m_sheet->setColumnWidth(colNo.toInt(),width);
                }
            }else if(nodeName=="color")
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString colorStr=tXmlReader.readElementText();
                colorList.append(colorStr);
            }else if(nodeName=="font")
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString fontStr=tXmlReader.readElementText();
                fontList.append(fontStr);
            }else if(nodeName=="fix")
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                QString font=attr.value(QString("font")).toString();
                QString color=attr.value(QString("color")).toString();
                QString span=attr.value(QString("span")).toString();
                QString frame=attr.value(QString("frame")).toString();
                QString frameColor=attr.value(QString("frameColor")).toString();
                QString frameWidth=attr.value(QString("frameWidth")).toString();
                qint32 align=attr.value(QString("align")).toInt();
                QString data=tXmlReader.readElementText();

                QStringList xyList=xy.split(",");
                qint32 x=xyList.at(0).toInt();
                qint32 y=xyList.at(1).toInt();
                QStringList spanList=span.split(",");
                qint32 rowSpan=spanList.at(0).toInt();
                qint32 colSpan=spanList.at(1).toInt();
                ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(x,y));
                if(cell)
                {
                    //font.
                    QString fontStr=fontList.at(font.toInt());
                    QStringList fontParaList=fontStr.split(",");
                    QFont fontObj(fontParaList.at(0),fontParaList.at(1).toInt());
                    fontObj.setBold(fontParaList.at(2).toInt()?true:false);
                    fontObj.setItalic(fontParaList.at(3).toInt()?true:false);
                    cell->ZSetFont(fontObj);
                    //color.
                    QString colorStr=colorList.at(color.toInt());
                    QStringList colorParaList=colorStr.split(",");
                    QColor fgColor(colorParaList.at(1).toInt(),colorParaList.at(2).toInt(),colorParaList.at(3).toInt(),colorParaList.at(0).toInt());
                    QColor bgColor(colorParaList.at(5).toInt(),colorParaList.at(6).toInt(),colorParaList.at(7).toInt(),colorParaList.at(4).toInt());
                    cell->ZSetForegroundColor(fgColor);
                    cell->ZSetBackgroundColor(bgColor);

                    QStringList frameList=frame.split(",");
                    bool bTopFrame=frameList.at(0).toInt()?true:false;
                    bool bBottomFrame=frameList.at(1).toInt()?true:false;
                    bool bLeftFrame=frameList.at(2).toInt()?true:false;
                    bool bRightFrame=frameList.at(3).toInt()?true:false;
                    cell->ZSetTopFrame(bTopFrame);
                    cell->ZSetBottomFrame(bBottomFrame);
                    cell->ZSetLeftFrame(bLeftFrame);
                    cell->ZSetRightFrame(bRightFrame);
                    QStringList frameColorList=frameColor.split(",");
                    cell->ZSetFrameColor(QColor(frameColorList.at(0).toInt(),frameColorList.at(1).toInt(),frameColorList.at(2).toInt()));
                    cell->ZSetFrameWidth(frameWidth.toInt());
                    if(bTopFrame||bBottomFrame||bLeftFrame||bRightFrame)
                    {
                        this->m_sheet->ZGetCellDelegate()->ZAddCellBorder(cell);
                    }else{
                        this->m_sheet->ZGetCellDelegate()->ZDelCellBorder(cell);
                    }
                    //span.
                    if(rowSpan>1 || colSpan>1)
                    {
                        this->m_sheet->setSpan(x,y,rowSpan,colSpan);
                    }
                    //align.
                    cell->ZSetTextAlignment(align);
                    //data.
                    cell->ZSetCellData(data);
                }
            }else if(nodeName==QString("pic"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                QString picData=tXmlReader.readElementText();
                QStringList xyList=xy.split(",");
                qint32 x=xyList.at(0).toInt();
                qint32 y=xyList.at(1).toInt();
                QPixmap pixmap;
                if(pixmap.loadFromData(QByteArray::fromBase64(picData.toUtf8())))
                {
                    QLabel *llPng=new QLabel;
                    llPng->setPixmap(pixmap);
                    llPng->setScaledContents(true);
                    this->m_sheet->setCellWidget(x,y,llPng);
                    ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(x,y));
                    if(cell)
                    {
                        cell->ZSetCellWidgetType(ZCell::CellWidget_QLabel);
                    }
                }
            }else if(nodeName==QString("checkbox"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                qint32 checked=attr.value(QString("checked")).toInt();
                QString name=tXmlReader.readElementText();
                QStringList xyList=xy.split(",");
                qint32 x=xyList.at(0).toInt();
                qint32 y=xyList.at(1).toInt();
                QCheckBox *cb=new QCheckBox;
                cb->setText(name);
                cb->setChecked(checked==1?true:false);
                this->m_sheet->setCellWidget(x,y,cb);
                ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(x,y));
                if(cell)
                {
                    cell->ZSetCellWidgetType(ZCell::CellWidget_QCheckBox);
                }
            }else if(nodeName==QString("combobox"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                QString val=tXmlReader.readElementText();
                QStringList xyList=xy.split(",");
                qint32 x=xyList.at(0).toInt();
                qint32 y=xyList.at(1).toInt();
                QStringList valList=val.split(":");
                QComboBox *cb=new QComboBox;
                for(qint32 i=0;i<valList.count();i++)
                {
                    if(!valList.at(i).isEmpty())
                    {
                        cb->addItem(valList.at(i));
                    }
                }
                this->m_sheet->setCellWidget(x,y,cb);
                ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(x,y));
                if(cell)
                {
                    cell->ZSetCellWidgetType(ZCell::CellWidget_QComboBox);
                }
            }else if(nodeName==QString("spinbox"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                qint32 min=attr.value(QString("min")).toInt();
                qint32 max=attr.value(QString("max")).toInt();
                qint32 val=tXmlReader.readElementText().toInt();
                QStringList xyList=xy.split(",");
                qint32 x=xyList.at(0).toInt();
                qint32 y=xyList.at(1).toInt();
                QSpinBox *sb=new QSpinBox;
                sb->setRange(min,max);
                sb->setValue(val);
                this->m_sheet->setCellWidget(x,y,sb);
                ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(x,y));
                if(cell)
                {
                    cell->ZSetCellWidgetType(ZCell::CellWidget_QSpinBox);
                }
            }else if(nodeName==QString("datetimeedit"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                QString val=tXmlReader.readElementText();
                QStringList xyList=xy.split(",");
                qint32 x=xyList.at(0).toInt();
                qint32 y=xyList.at(1).toInt();
                QDateTimeEdit *te=new QDateTimeEdit;
                te->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
                this->m_sheet->setCellWidget(x,y,te);
                ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(x,y));
                if(cell)
                {
                    cell->ZSetCellWidgetType(ZCell::CellWidget_QDateTimeEdit);
                }
            }
            else if(nodeName==QString("bindvar"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString xy=attr.value(QString("xy")).toString();
                QString type=attr.value(QString("type")).toString();
                QString varName=tXmlReader.readElementText();
                if(type=="general")
                {
                    //search in varList and set bindCell value.
                    for(qint32 i=0;i<this->m_generalVarItem->childCount();i++)
                    {
                        QTreeWidgetItem *item=this->m_generalVarItem->child(i);
                        if(item->text(0)==varName)
                        {
                            item->setText(1,xy);
                            break;
                        }
                    }
                }else if(type=="auto")
                {
                    //search in varList and set bindCell value.
                    for(qint32 i=0;i<this->m_autoVarItem->childCount();i++)
                    {
                        QTreeWidgetItem *item=this->m_autoVarItem->child(i);
                        if(item->text(0)==varName)
                        {
                            item->setText(1,xy);
                            break;
                        }
                    }
                }
            }
        }//StarElement.
    }//while().
}
void ZSheetWidget::ZPutVarSourceXmlData(QString xmlData)
{
    QXmlStreamReader tXmlReader(xmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("GeVar"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString type=attr.value(QString("type")).toString();
                QString rule=attr.value(QString("rule")).toString();
                QString refVal=attr.value(QString("refVal")).toString();
                QString name=tXmlReader.readElementText();
                QTreeWidgetItem *item=new QTreeWidgetItem;
                item->setText(0,name);
                item->setText(2,type);
                item->setText(3,rule);
                item->setText(4,refVal);
                this->m_generalVarItem->addChild(item);
                this->m_treeWidget->expandAll();
            }else if(nodeName=="AutoVar")
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString type=attr.value(QString("type")).toString();
                QString action=attr.value(QString("action")).toString();
                QString value=attr.value(QString("value")).toString();
                QString name=tXmlReader.readElementText();
                QTreeWidgetItem *item=new QTreeWidgetItem;
                item->setText(0,name);
                item->setText(2,type);
                item->setText(3,action);
                item->setText(4,value);
                this->m_autoVarItem->addChild(item);
                this->m_treeWidget->expandAll();
            }
        }//StarElement.
    }//while().
}

void ZSheetWidget::ZSlotCellActivated(qint32 x,qint32 y)
{
    this->m_leXY->setText(QString("(%1,%2)").arg(x+1).arg(y+1));
}
void ZSheetWidget::ZSlotCellAutoAdjust(void)
{
    this->m_sheet->resizeRowsToContents();
    this->m_sheet->resizeColumnsToContents();
}
void ZSheetWidget::ZSlotPopMenu(const QPoint &pt)
{
    if(NULL==this->m_treeWidget->currentItem())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("未选择变量,无法完成绑定!"));
        return;
    }
    QModelIndex modelIndex=this->m_sheet->currentIndex();
    ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(modelIndex.row(),modelIndex.column()));
    if(NULL==cell)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("未选择单元格,无法完成绑定!"));
        return;
    }

    QMenu popMenu;
    QAction actBindCurrentCell(QIcon(":/TemplateEditor/images/TemplateEditor/BindVar.png"),tr("绑定当前单元格"));
    QAction actBindCell(QIcon(":/TemplateEditor/images/TemplateEditor/BindVar.png"),tr("绑定单元格..."));
    QAction actRemoveBind(QIcon(":/TemplateEditor/images/TemplateEditor/UnbindVar.png"),tr("移除绑定"));
    popMenu.addAction(&actBindCurrentCell);
    popMenu.addAction(&actBindCell);
    popMenu.addAction(&actRemoveBind);
    connect(&actBindCurrentCell,SIGNAL(triggered(bool)),this,SLOT(ZSlotBindCurrentCell()));
    connect(&actBindCell,SIGNAL(triggered(bool)),this,SLOT(ZSlotBindCell()));
    connect(&actRemoveBind,SIGNAL(triggered(bool)),this,SLOT(ZSlotRemoveBind()));
    popMenu.exec(QCursor::pos());
}
void ZSheetWidget::ZSlotBindCurrentCell()
{
    QModelIndex modelIndex=this->m_sheet->currentIndex();
    ZCell *cell=static_cast<ZCell*>(this->m_sheet->item(modelIndex.row(),modelIndex.column()));
    if(NULL==cell)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("未选择单元格,无法完成绑定!"));
        return;
    }

    QTreeWidgetItem *itemVar=this->m_treeWidget->currentItem();
    if(NULL==itemVar)
    {
        return;
    }
    itemVar->setText(1,QString("%1,%2").arg(modelIndex.row()+1).arg(modelIndex.column()+1));
}
void ZSheetWidget::ZSlotBindCell()
{
    QTreeWidgetItem *itemVar=this->m_treeWidget->currentItem();
    if(NULL==itemVar)
    {
        return;
    }
    QString xyText=QInputDialog::getText(this,tr("输入单元格坐标"),tr("请输入要绑定的单元格坐标,例如: 1,1"));
    if(xyText.isEmpty())
    {
        return;
    }
    QStringList xyList=xyText.split(",");
    if(2!=xyList.size())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("错误的坐标输入,无法完成绑定!"));
        return;
    }
    qint32 x=xyList.at(0).toInt();
    qint32 y=xyList.at(1).toInt();
    if(!(x>=0 && x<=TABLE_ROW_COUNT) || !(y>=0 && y<=TABLE_COL_COUNT))
    {
        QMessageBox::critical(this,tr("错误提示"),tr("坐标越界,无法完成绑定!"));
        return;
    }
    itemVar->setText(1,QString("%1,%2").arg(x).arg(y));
}
void ZSheetWidget::ZSlotRemoveBind()
{
    QTreeWidgetItem *itemVar=this->m_treeWidget->currentItem();
    if(NULL==itemVar)
    {
        return;
    }
    itemVar->setText(1,"");
}
