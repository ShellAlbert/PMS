#include "ztemplateeditor.h"
ZTemplateEditor::ZTemplateEditor(QWidget *parent):ZBaseWindow(parent)
{
    this->ZGetTitleBar()->ZSetWindowTitle(tr("Template Editor"));
    this->ZGetTitleBar()->ZSetButtonVisible(false,false,true);
    this->ZGetTitleBar()->ZSetWindowIcon(QPixmap(":/images/templateeditor.png"));
    //create tool bar control buttons.
    this->m_btnRefresh=new ZBaseButton;
    this->m_btnRefresh->ZGetToolButton()->setObjectName("ZTemplateEditorRefreshButton");
    this->m_btnRefresh->ZGetLabel()->setText(tr("Refresh"));
    connect(this->m_btnRefresh,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotRefresh()));
    this->ZGetToolBar()->ZAddWidget(this->m_btnRefresh);

    if(gMyUserInfo.PermBits&PermTemplateEditorCreate)
    {
        this->m_btnNewTemplate=new ZBaseButton;
        this->m_btnNewTemplate->ZGetToolButton()->setObjectName("ZTemplateEditorNewTemplateButton");
        this->m_btnNewTemplate->ZGetLabel()->setText(tr("New"));
        connect(this->m_btnNewTemplate,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotNewTemplate()));
        this->ZGetToolBar()->ZAddWidget(this->m_btnNewTemplate);
    }else{
        this->m_btnNewTemplate=NULL;
    }

    if(gMyUserInfo.PermBits&PermTemplateEditorQuery)
    {
        this->m_btnOpenTemplate=new ZBaseButton;
        this->m_btnOpenTemplate->ZGetToolButton()->setObjectName("ZTemplateEditorOpenTemplateButton");
        this->m_btnOpenTemplate->ZGetLabel()->setText(tr("Open"));
        connect(this->m_btnOpenTemplate,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotOpenTemplate()));
        this->ZGetToolBar()->ZAddWidget(this->m_btnOpenTemplate);
    }else{
        this->m_btnOpenTemplate=NULL;
    }

    if(gMyUserInfo.PermBits&PermTemplateEditorModify)
    {
        this->m_btnSaveTemplate=new ZBaseButton;
        this->m_btnSaveTemplate->ZGetToolButton()->setObjectName("ZTemplateEditorSaveTemplateButton");
        this->m_btnSaveTemplate->ZGetLabel()->setText(tr("Save"));
        connect(this->m_btnSaveTemplate,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotSaveTemplate()));
        this->ZGetToolBar()->ZAddWidget(this->m_btnSaveTemplate);

        this->m_btnSaveAsTemplate=new ZBaseButton;
        this->m_btnSaveAsTemplate->ZGetToolButton()->setObjectName("ZTemplateEditorSaveAsTemplateButton");
        this->m_btnSaveAsTemplate->ZGetLabel()->setText(tr("Save As"));
        connect(this->m_btnSaveAsTemplate,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotSaveAsTemplate()));
        this->ZGetToolBar()->ZAddWidget(this->m_btnSaveAsTemplate);
    }else {
        this->m_btnSaveTemplate=NULL;
        this->m_btnSaveAsTemplate=NULL;
    }


    if(gMyUserInfo.PermBits&PermTemplateEditorDelete)
    {
        this->m_btnDeleteTemplate=new ZBaseButton;
        this->m_btnDeleteTemplate->ZGetToolButton()->setObjectName("ZTemplateEditorDeleteTemplateButton");
        this->m_btnDeleteTemplate->ZGetLabel()->setText(tr("Delete"));
        connect(this->m_btnDeleteTemplate,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotDeleteTemplate()));
        this->ZGetToolBar()->ZAddWidget(this->m_btnDeleteTemplate);
    }else{
        this->m_btnDeleteTemplate=NULL;
    }

    //add a stretch.
    this->ZGetToolBar()->ZAddStretch(1);

    this->m_btnExportHtml=new ZBaseButton;
    this->m_btnExportHtml->ZGetToolButton()->setObjectName("ZTemplateEditorExportHtmlButton");
    this->m_btnExportHtml->ZGetLabel()->setText(tr("Export Html"));
    connect(this->m_btnExportHtml,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotExportHtml()));
    this->ZGetToolBar()->ZAddWidget(this->m_btnExportHtml);

    this->m_btnInsertPicture=new ZBaseButton;
    this->m_btnInsertPicture->ZGetToolButton()->setObjectName("ZTemplateEditorInsertPictureButton");
    this->m_btnInsertPicture->ZGetLabel()->setText(tr("Insert Picture"));
    connect(this->m_btnInsertPicture,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotInsertPicture()));
    this->ZGetToolBar()->ZAddWidget(this->m_btnInsertPicture);

    //merge and split.
    this->m_btnMerge=new ZBaseButton;
    this->m_btnMerge->ZGetToolButton()->setObjectName("ZTemplateEditorMergeButton");
    this->m_btnMerge->ZGetLabel()->setText(tr("Merge"));
    connect(this->m_btnMerge,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotMergeCell()));
    this->ZGetToolBar()->ZAddWidget(this->m_btnMerge);

    this->m_btnSplit=new ZBaseButton;
    this->m_btnSplit->ZGetToolButton()->setObjectName("ZTemplateEditorSplitButton");
    this->m_btnSplit->ZGetLabel()->setText(tr("Split"));
    connect(this->m_btnSplit,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotSplitCell()));
    this->ZGetToolBar()->ZAddWidget(this->m_btnSplit);

    this->m_btnImportExcelXML=new ZBaseButton;
    this->m_btnImportExcelXML->ZGetToolButton()->setObjectName("ZTemplateEditorImportExcelXMLButton");
    this->m_btnImportExcelXML->ZGetLabel()->setText(tr("Excel XML"));
    connect(this->m_btnImportExcelXML,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotImportExcelXML()));
    this->ZGetToolBar()->ZAddWidget(this->m_btnImportExcelXML);

    this->m_btnImportTemplate=new ZBaseButton;
    this->m_btnImportTemplate->ZGetToolButton()->setObjectName("ZTemplateEditorImportTemplateButton");
    this->m_btnImportTemplate->ZGetLabel()->setText(tr("Import"));
    connect(this->m_btnImportTemplate,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotImportTemplate()));
    this->ZGetToolBar()->ZAddWidget(this->m_btnImportTemplate);

    this->m_btnExportTemplate=new ZBaseButton;
    this->m_btnExportTemplate->ZGetToolButton()->setObjectName("ZTemplateEditorExportTemplateButton");
    this->m_btnExportTemplate->ZGetLabel()->setText(tr("Export"));
    connect(this->m_btnExportTemplate,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotExportTemplate()));
    this->ZGetToolBar()->ZAddWidget(this->m_btnExportTemplate);

    //set cell information dialog.
    this->m_btnSetCellInfo=new ZBaseButton;
    this->m_btnSetCellInfo->ZGetToolButton()->setObjectName("ZTemplateEditorCellInfoButton");
    this->m_btnSetCellInfo->ZGetLabel()->setText(tr("Style"));
    connect(this->m_btnSetCellInfo,SIGNAL(ZSignalClicked()),this,SLOT(ZSlotSetCellInformation()));
    this->ZGetToolBar()->ZAddWidget(this->m_btnSetCellInfo);

    //template list view.
    this->m_listViewTemplate=new QListView;
    this->m_listViewTemplate->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(this->m_listViewTemplate,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ZSlotDblClickOpenTemplateSheet(QModelIndex)));

    //tab widget.
    this->m_tabWidget=new QTabWidget;
    this->m_tabWidget->setTabsClosable(true);
    connect(this->m_tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(ZSlotRemoveTab(qint32)));

    //spliter.
    this->m_splitter=new QSplitter;
    this->m_splitter->addWidget(this->m_listViewTemplate);
    this->m_splitter->addWidget(this->m_tabWidget);
    this->m_splitter->setStretchFactor(0,0);//left part keep its old size.
    this->m_splitter->setStretchFactor(1,1);//right part change follows the window size.
    this->m_splitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //layout.
    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_splitter);
    //set layout.
    this->ZGetCentralWidget()->setLayout(this->m_hLayout);

    //create database
    //use MVC mode.
    this->m_dataBaseTemplate=new ZDataBase("TemplateEditor");
    this->m_tableModelTemplate=new QSqlTableModel(this,this->m_dataBaseTemplate->ZGetDatabase());
    this->m_tableModelTemplate->setEditStrategy(QSqlTableModel::OnRowChange);
    //set model.
    this->m_listViewTemplate->setModel(this->m_tableModelTemplate);

    //for popup menu.
    this->m_listViewTemplate->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this->m_listViewTemplate,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ZSlotShowTemplatePopupMenu(QPoint)));
    this->m_popupMenu=new QMenu;
    this->m_actionRefresh=new QAction(QIcon(":/images/refresh.png"),tr("Refresh"),this);
    this->m_actionNewTemplate=new QAction(QIcon(":/images/ztemplateeditor_new.png"),tr("New"),this);
    this->m_actionOpenTemplate=new QAction(QIcon(":/images/ztemplateeditor_open.png"),tr("Open"),this);
    this->m_actionSaveTemplate=new QAction(QIcon(":/images/ztemplateeditor_save.png"),tr("Save"),this);
    this->m_actionSaveAsTemplate=new QAction(QIcon(":/images/ztemplateeditor_saveas.png"),tr("Save As"),this);
    this->m_actionDeleteTemplate=new QAction(QIcon(":/images/ztemplateeditor_delete.png"),tr("Delete"),this);
    this->m_popupMenu->addAction(this->m_actionRefresh);
    this->m_popupMenu->addSection(tr("Template Command"));
    this->m_popupMenu->addAction(this->m_actionNewTemplate);
    this->m_popupMenu->addAction(this->m_actionOpenTemplate);
    this->m_popupMenu->addAction(this->m_actionSaveTemplate);
    this->m_popupMenu->addAction(this->m_actionSaveAsTemplate);
    this->m_popupMenu->addAction(this->m_actionDeleteTemplate);

    //waiting dialog.
    this->m_waitingDia=new ZWaitingDialog;
}

ZTemplateEditor::~ZTemplateEditor()
{
    //tool bar control buttons.
    delete this->m_btnRefresh;
    if(this->m_btnNewTemplate)
    {
        delete this->m_btnNewTemplate;
    }
    if(this->m_btnOpenTemplate)
    {
        delete this->m_btnOpenTemplate;
    }
    if(this->m_btnSaveTemplate)
    {
        delete this->m_btnSaveTemplate;
    }
    if(this->m_btnSaveAsTemplate)
    {
        delete this->m_btnSaveAsTemplate;
    }
    if(this->m_btnDeleteTemplate)
    {
        delete this->m_btnDeleteTemplate;
    }

    delete this->m_btnExportHtml;
    delete this->m_btnInsertPicture;
    delete this->m_btnImportExcelXML;
    delete this->m_btnMerge;
    delete this->m_btnSplit;
    delete this->m_btnImportTemplate;
    delete this->m_btnExportTemplate;
    delete this->m_btnSetCellInfo;

    delete this->m_listViewTemplate;
    delete this->m_tabWidget;
    delete this->m_splitter;
    delete this->m_hLayout;

    delete this->m_tableModelTemplate;
    delete this->m_dataBaseTemplate;

    //for popup menu.
    delete this->m_actionRefresh;
    delete this->m_actionNewTemplate;
    delete this->m_actionOpenTemplate;
    delete this->m_actionSaveAsTemplate;
    delete this->m_actionSaveTemplate;
    delete this->m_actionDeleteTemplate;
    delete this->m_popupMenu;

    //waiting dialog.
    delete this->m_waitingDia;
}
void ZTemplateEditor::ZStartInitial()
{
    this->ZSlotRefresh();
    emit this->ZSignalInitialFinish();
}
QSize ZTemplateEditor::sizeHint() const
{
    return QSize(320,480);
}
void ZTemplateEditor::ZSlotRefresh()
{
    if(false==this->ZCheckDatabaseState())
    {
        //lost connection and user cancel the operation.
        return;
    }
    //admin can query all roles.
    //others can only operate its children.
    this->m_tableModelTemplate->setTable("templatetable");
    //0:TemplateName.
    //1:TemplateXml.
    //2.Creator.
    //3.CreateDateTime.
    //this->m_tableModelTemplate->removeColumn(1);
    if(gMyUserInfo.UserName!="admin")
    {
        this->m_tableModelTemplate->setFilter(QString("`Creator`='%1'").arg(gMyUserInfo.UserName));
    }
    if(!this->m_tableModelTemplate->select())
    {
        this->ZGetStatusBar()->ZSetStatusMessage(tr("Error:%1").arg(this->m_tableModelTemplate->lastError().nativeErrorCode()));
    }
}
QString ZTemplateEditor::ZGetUniqueSheetName()
{
    //find the mimimum and unused number.
    QString tTemplateName;
    qint32 tUnusedNum=0;
    while(1)
    {
        bool bNoDuplicate=false;
        tTemplateName=tr("Untitled-%1").arg(tUnusedNum);

        //make sure the name is not duplicate in unsaved tabwidget.
        for(qint32 i=0;i<this->m_tabWidget->count();i++)
        {
            QString tExistsName=this->m_tabWidget->tabText(i);
            if(tExistsName.startsWith("<*>"))
            {
                tExistsName=tExistsName.remove(0,3);
            }
            if(tTemplateName==tExistsName)
            {
                bNoDuplicate=true;
                tUnusedNum++;
                break;
            }
        }
        //make sure the name is not duplicate in exists template table.
        for(qint32 j=0;j<this->m_tableModelTemplate->rowCount();j++)
        {
            QString tExistsName=this->m_tableModelTemplate->data(this->m_tableModelTemplate->index(j,0)).toString();
            if(tTemplateName==tExistsName)
            {
                bNoDuplicate=true;
                tUnusedNum++;
                break;
            }
        }
        if(false==bNoDuplicate)
        {
            break;
        }
    }
    return tTemplateName;
}
void ZTemplateEditor::ZSlotNewTemplate()
{
    QString tTemplateName=this->ZGetUniqueSheetName();
    ZSheet *tSheet=new ZSheet;
    tSheet->ZSetSheetName(tTemplateName);
    tSheet->ZSetSheetState(ZSheet::SheetState_NotSave);
    this->m_tabWidget->addTab(tSheet,QIcon(":/images/templateeditor.png"),tTemplateName);
    this->m_tabWidget->setCurrentWidget(tSheet);
    connect(tSheet,SIGNAL(ZSignalSheetChanged(QString)),this,SLOT(ZSlotTemplateSheetChanged(QString)));
    //status message.
    this->ZGetStatusBar()->ZSetStatusMessage(tr("Create new template sheet <%1> success.").arg(tTemplateName));
}
void ZTemplateEditor::ZSlotOpenTemplate()
{
    qint32 tSelectedRow=this->m_listViewTemplate->currentIndex().row();
    if(tSelectedRow<0)
    {
        this->ZGetStatusBar()->ZSetStatusMessage(tr("Select a template to open."));
        return;
    }
    this->ZOpenTemplateSheetByModelRow(tSelectedRow);
}
void ZTemplateEditor::ZSlotSaveTemplate()
{
    ZSheet *tSheet=qobject_cast<ZSheet*>(this->m_tabWidget->currentWidget());
    if(!tSheet)
    {
        return;
    }
    if(false==this->ZCheckDatabaseState())
    {
        //lost connection and user cancel the operation.
        return;
    }
    QString tTemplateName=tSheet->ZGetSheetName();
    QString tTemplateXml=tSheet->ZGetSheetXml();
    QString tCreator=gMyUserInfo.UserName;
    QString tCreateDateTime=QDateTime::currentDateTime().toString(QString("yyyy-MM-dd HH:mm:ss"));

    //if the sheet was not save,then popup a dialog to receive the sheet name.
    //otherwise save with its old name.
    if(tSheet->ZGetSheetState()==ZSheet::SheetState_NotSave)
    {
        //specify the template name.
        ZFileNameDialog tFileNameDia;
        tFileNameDia.ZSetFileName(tTemplateName);
        if(tFileNameDia.exec()==QDialog::Accepted)
        {
            if(false==this->ZCheckDatabaseState())
            {
                //lost connection and user cancel the operation.
                return;
            }
            //connection is ok,continue to run.
            //get the new template name.
            tTemplateName=tFileNameDia.ZGetFileName();
        }
    }
    this->ZGetStatusBar()->ZSetStatusMessage(tr("Saving,please wait"));
    QThread *tThread=new QThread;
    ZTemplateOperator *tTemplateOperator=new ZTemplateOperator;
    tTemplateOperator->moveToThread(tThread);
    connect(tTemplateOperator,SIGNAL(ZSignalSetTemplateXmlFinish(QString,qint32)),this,SLOT(ZSlotSetTemplateXmlFinish(QString,qint32)),Qt::DirectConnection);
    tThread->start();
    tTemplateOperator->ZSetTemplateXml(tTemplateName,tTemplateXml,tCreator,tCreateDateTime);
}
void ZTemplateEditor::ZSlotSaveAsTemplate()
{
    ZSheet *tSheet=qobject_cast<ZSheet*>(this->m_tabWidget->currentWidget());
    if(!tSheet)
    {
        return;
    }
    QString tTemplateName=tSheet->ZGetSheetName();
    QString tTemplateXml=tSheet->ZGetSheetXml();
    QString tCreator=gMyUserInfo.UserName;
////    QString tTemplateName="中文测试3";
////    QString tTemplateXml="中文测试2";
////    QString tCreator="中文测试2";
//    QString tTemplateName="3";
//    QString tTemplateXml="2";
//    QString tCreator="1";
    QString tCreateDateTime=QDateTime::currentDateTime().toString(QString("yyyy-MM-dd HH:mm:ss"));
    //specify the template name.
    ZFileNameDialog tFileNameDia;
    tFileNameDia.ZSetFileName(tTemplateName);
    if(tFileNameDia.exec()==QDialog::Accepted)
    {
        if(false==this->ZCheckDatabaseState())
        {
            //lose connection and user cancel the reconnecting process.
            return;
        }
        //connection is ok,continue to run.

        //get the new template name.
        tTemplateName=tFileNameDia.ZGetFileName();
        //execute database  flush.
        int tRowCount=this->m_tableModelTemplate->rowCount();
        this->m_tableModelTemplate->insertRow(tRowCount);
        this->m_tableModelTemplate->setData(this->m_tableModelTemplate->index(tRowCount,0),tTemplateName);
        this->m_tableModelTemplate->setData(this->m_tableModelTemplate->index(tRowCount,1),tTemplateXml);
        this->m_tableModelTemplate->setData(this->m_tableModelTemplate->index(tRowCount,2),tCreator);
        this->m_tableModelTemplate->setData(this->m_tableModelTemplate->index(tRowCount,3),tCreateDateTime);
        //transaction to update.
        this->m_tableModelTemplate->database().transaction();
        if(this->m_tableModelTemplate->submitAll())
        {
            this->m_tableModelTemplate->database().commit();
            this->ZGetStatusBar()->ZSetStatusMessage(tr("Save as sheet <%1> success.").arg(tTemplateName));
            tSheet->ZSetSheetName(tTemplateName);
            this->m_tabWidget->setTabText(this->m_tabWidget->indexOf(tSheet),tTemplateName);
        }else{
            this->m_tableModelTemplate->database().rollback();
            this->ZGetStatusBar()->ZSetStatusMessage(tr("Save as sheet <%1> failed:%2.").arg(tTemplateName).arg(this->m_tableModelTemplate->lastError().nativeErrorCode()));
            qDebug()<<this->m_tableModelTemplate->lastError().text();
        }
        //refresh after saving.
        this->m_tableModelTemplate->select();
    }//if.
}
void ZTemplateEditor::ZSlotDeleteTemplate()
{
    qint32 tRow=this->m_listViewTemplate->currentIndex().row();
    QString tTemplateName=this->m_tableModelTemplate->data(this->m_tableModelTemplate->index(tRow,0)).toString();
    if(tTemplateName.isEmpty())
    {
        return;
    }
    ZAskDialog tAskDia;
    tAskDia.ZSetAskText(tr("Are you sure to delete template <%1> ?").arg(tTemplateName));
    if(tAskDia.exec()==QDialog::Accepted)
    {
        if(false==this->ZGetCentralWidget())
        {
            //lose connection and user cancel the reconnecting process.
            return;
        }
        //connection is ok,continue to run.
        this->m_tableModelTemplate->removeRow(tRow);
        this->m_tableModelTemplate->database().transaction();
        if(this->m_tableModelTemplate->submitAll())
        {
            this->m_tableModelTemplate->database().commit();
            this->ZGetStatusBar()->ZSetStatusMessage(tr("Delete template <%1> success.").arg(tTemplateName));
            //remove it from tab widget if it was opened.
            for(qint32 i=0;i<this->m_tabWidget->count();i++)
            {
                QString tExistName=this->m_tabWidget->tabText(i);
                if(tExistName.startsWith("<*>"))
                {
                    tExistName=tExistName.remove(0,3);
                }
                if(tExistName==tTemplateName)
                {
                    ZSheet *tSheet=qobject_cast<ZSheet*>(this->m_tabWidget->widget(i));
                    if(tSheet)
                    {
                        this->m_tabWidget->removeTab(i);
                        delete tSheet;
                    }
                }
            }
        }else{
            this->m_tableModelTemplate->database().rollback();
            this->ZGetStatusBar()->ZSetStatusMessage(tr("Delete template <%1> failed:%2.").arg(tTemplateName).arg(this->m_tableModelTemplate->lastError().nativeErrorCode()));
        }
        //refresh list.
        this->m_tableModelTemplate->select();
    }
}
void ZTemplateEditor::ZSlotExportHtml()
{
    ZSheet *tSheet=qobject_cast<ZSheet*>(this->m_tabWidget->currentWidget());
    if(tSheet)
    {
        QString tExportFilename = QFileDialog::getSaveFileName(this, tr("Specify the file name"),".", "Html Files(*.html)");
        if(tExportFilename.isEmpty())
        {
            return;
        }
        if(!tExportFilename.endsWith(".html"))
        {
            tExportFilename.append(".html");
        }
        QString tPrintHtml=tSheet->ZGetPrintHtml();
        if(tPrintHtml.isEmpty())
        {
            return;
        }
        QFile tFile(tExportFilename);
        if(tFile.open(QIODevice::WriteOnly))
        {
            tFile.write(tPrintHtml.toUtf8());
            tFile.close();
            ZInfoDialog tInfoDia(ZInfoDialog::SuccessDialog);
            tInfoDia.ZSetInfoText(tr("Export sheet to html file success!"));
            tInfoDia.exec();
        }
    }
}
void ZTemplateEditor::ZSlotInsertPicture()
{
    ZSheet *tSheet=qobject_cast<ZSheet*>(this->m_tabWidget->currentWidget());
    if(!tSheet)
    {
        return;
    }
    QList<QTableWidgetItem*> tSelectedItems=tSheet->selectedItems();
    if(tSelectedItems.count()<=0)
    {
        this->ZGetStatusBar()->ZSetStatusMessage(tr("Select a cell to insert a png picture!"));
        return;
    }
    ZCell* tCell=static_cast<ZCell*>(tSelectedItems.at(0));
    if(!tCell)
    {
        return;
    }

    //get local file name.
    QString tPngFile = QFileDialog::getOpenFileName(this, tr("Import Picture File"),".",QString("Picture (*.png)"));
    if(tPngFile.isEmpty())
    {
        return;
    }
    QLabel *tPngLabel=new QLabel;
    tPngLabel->setPixmap(QPixmap(tPngFile));
    tPngLabel->setScaledContents(true);
    tSheet->setCellWidget(tCell->row(),tCell->column(),tPngLabel);
    tCell->ZSetIsPicture(true);
}
void ZTemplateEditor::ZSlotImportExcelXML()
{
    //get local file name.
    QString tExcelXMLFile = QFileDialog::getOpenFileName(this, tr("Import Excel XML File"),".",QString("Excel (*.xml)"));
    if(tExcelXMLFile.isEmpty())
    {
        return;
    }
    ZExcelParser tExcelParser;
    if(tExcelParser.ZParserXmlFile(tExcelXMLFile)<0)
    {
        ZInfoDialog tErrDia(ZInfoDialog::ErrorDialog);
        tErrDia.ZSetInfoText(tr("Wrong Excel XML File Format!"));
        tErrDia.exec();
        return;
    }

    //create a new sheet object here.
    QString tSheetName=this->ZGetUniqueSheetName();
    ZSheet *tSheet=new ZSheet;
    tSheet->ZSetSheetName(tSheetName);
    tSheet->ZSetSheetState(ZSheet::SheetState_NotSave);
    connect(tSheet,SIGNAL(ZSignalSheetChanged(QString)),this,SLOT(ZSlotTemplateSheetChanged(QString)));

    qint32 tRowNo=0;
    qint32 tColNo=0;
    QList<ZExcelTableInfo*> *tTableInfoList=tExcelParser.ZGetTableInfo();
    for(qint32 i=0;i<tTableInfoList->count();i++)
    {
        ZExcelTableInfo *tTableInfo=tTableInfoList->at(i);
        if(tTableInfo->ssExpandedRowCount>64 || tTableInfo->ssExpandedColumnCount>64)
        {
            ZInfoDialog tErrDia(ZInfoDialog::ErrorDialog);
            tErrDia.ZSetInfoText(tr("Max support 64x64  table,but now is %1x%2.").arg(tTableInfo->ssExpandedRowCount).arg(tTableInfo->ssExpandedColumnCount));
            tErrDia.exec();
            return;
        }
        //handle <Row></Row>.
        for(qint32 j=0;j<tTableInfo->rowInfoList.count();j++)
        {
            ZExcelRowInfo *tRowInfo=tTableInfo->rowInfoList.at(j);
            //handle <Cell></Cell>.
            //reset column number.
            tColNo=0;
            for(qint32 k=0;k<tRowInfo->cellInfoList.count();k++)
            {
                ZExcelCellInfo *tCellInfo=tRowInfo->cellInfoList.at(k);
                QString tStyleID=tCellInfo->ssStyleID;
                QString tType=tCellInfo->ssType;
                QString tData=tCellInfo->ssData;
                qint32 tRowSpan=tCellInfo->mergeDown;
                qint32 tColSpan=tCellInfo->mergeAcross;

                //span support.
                if((tRowSpan+1) >1 || (tColSpan+1) >1)
                {
                    tSheet->setSpan(tRowNo,tColNo,tRowSpan+1,tColSpan+1);
                }
                //set sheet data.
                ZCell *tCell=static_cast<ZCell*>(tSheet->item(tRowNo,tColNo));
                if(tCell)
                {
                    tCell->ZSetCellData(tData);
                }
                //next column.
                tColNo++;
            }
            //next row.
            tRowNo++;
        }
    }
    //add it to table widget.
    this->m_tabWidget->addTab(tSheet,QIcon(":/images/templateeditor.png"),tSheetName);
}
void ZTemplateEditor::ZSlotImportTemplate()
{
    //get local file name.
    QString tTemplateFileName = QFileDialog::getOpenFileName(this, tr("Import Template Sheet File"),".",QString("Templates (*.xml)"));
    if(tTemplateFileName.isEmpty())
    {
        return;
    }
    //read file.
    QFile tFile(tTemplateFileName);
    if(!tFile.open(QIODevice::ReadOnly))
    {
        this->ZGetStatusBar()->ZSetStatusMessage(tr("Read file <%1> failed:%2.").arg(tFile.fileName()).arg(tFile.errorString()));
        return;
    }
    ZSheet *tSheet=new ZSheet;
    if(tSheet)
    {
        QString tSheetName=this->ZGetUniqueSheetName();
        connect(tSheet,SIGNAL(ZSignalSheetChanged(QString)),this,SLOT(ZSlotTemplateSheetChanged(QString)));
        tSheet->ZSetSheetName(tSheetName);
        tSheet->ZSetSheetState(ZSheet::SheetState_NotSave);
        QString tTemplateXml(tFile.readAll());
        if(!tTemplateXml.contains("Template") || !tTemplateXml.contains("Cell"))
        {
            ZInfoDialog tErrDia(ZInfoDialog::ErrorDialog);
            tErrDia.ZSetInfoText(tr("Wrong PMS XML File Format!"));
            tErrDia.exec();
            delete tSheet;
            return;
        }
        tSheet->ZSetSheetXml(tTemplateXml);
        //close file.
        tFile.close();
        this->m_tabWidget->addTab(tSheet,QIcon(":/images/templateeditor.png"),tSheetName);
        this->ZGetStatusBar()->ZSetStatusMessage(tr("Import file success."));
    }
}
void ZTemplateEditor::ZSlotExportTemplate()
{
    ZSheet *tSheet=qobject_cast<ZSheet*>(this->m_tabWidget->currentWidget());
    if(!tSheet)
    {
        this->ZGetStatusBar()->ZSetStatusMessage(tr("Create or open a template to import."));
        return;
    }
    QString tFileName=QFileDialog::getSaveFileName(this,tr("Specify the file name"),QString("."),QString("Templates (*.xml)"));
    if(tFileName.isEmpty())
    {
        return;
    }
    if(!tFileName.endsWith(".xml"))
    {
        tFileName.append(".xml");
    }
    QFile tFile(tFileName);
    if(!tFile.open(QIODevice::WriteOnly))
    {
        this->ZGetStatusBar()->ZSetStatusMessage(tr("Save file <%1> failed:%2.").arg(tFile.fileName()).arg(tFile.errorString()));
        return;
    }
    QString tTemplateXml=tSheet->ZGetSheetXml();
    QTextStream tTextStreamFile(&tFile);
    tTextStreamFile.setCodec("UTF-8");
    tTextStreamFile<<tTemplateXml;
    tFile.close();
    this->ZGetStatusBar()->ZSetStatusMessage(tr("Export file <%1> success.").arg(tFile.fileName()));
}
//remove tab.
void ZTemplateEditor::ZSlotRemoveTab(qint32 index)
{
    ZSheet *tSheet=qobject_cast<ZSheet*>(this->m_tabWidget->widget(index));
    if(!tSheet)
    {
        return;
    }
    QString tTemplateName=tSheet->ZGetSheetName();
    QString tTabTemplateName=this->m_tabWidget->tabText(this->m_tabWidget->currentIndex());
    if(tTabTemplateName.startsWith("<*>"))
    {
        ZAskDialog tAskDia;
        tAskDia.ZSetAskText(tr("Template <%1> was changed,but not save,are you sure to close?").arg(tTemplateName));
        if(tAskDia.exec()!=QDialog::Accepted)
        {
            return;
        }
    }
    //delete it to remove it from tab widget.
    this->m_tabWidget->removeTab(index);
    delete tSheet;
}

//double click list view to open.
void ZTemplateEditor::ZSlotDblClickOpenTemplateSheet(QModelIndex index)
{
    qint32 tModelRow=index.row();
    this->ZOpenTemplateSheetByModelRow(tModelRow);
}

//open sheet by selected row.
void ZTemplateEditor::ZOpenTemplateSheetByModelRow(qint32 tModelRow)
{
    if(tModelRow<0)
    {
        return;
    }
    QString tTemplateName=this->m_tableModelTemplate->data(this->m_tableModelTemplate->index(tModelRow,0)).toString();
    if(tTemplateName.isEmpty())
    {
        return;
    }
    //make sure the sheet can only opened once.
    for(qint32 i=0;i<this->m_tabWidget->count();i++)
    {
        QString tExistsName=this->m_tabWidget->tabText(i);
        if(tExistsName.startsWith("<*>"))
        {
            tExistsName=tExistsName.remove(0,3);
        }
        if(tTemplateName==tExistsName)
        {
            this->m_tabWidget->setCurrentIndex(i);
            this->ZGetStatusBar()->ZSetStatusMessage(tr("Sheet <%1> was opened yet.").arg(tTemplateName));
            return;
        }
    }
    QThread *tThread=new QThread;
    ZTemplateOperator *tTemplateOperator=new ZTemplateOperator;
    tTemplateOperator->moveToThread(tThread);
    connect(tTemplateOperator,SIGNAL(ZSignalGetTemplateXmlFinish(QString,QString)),this,SLOT(ZSlotGetTemplateXmlFinish(QString,QString)),Qt::DirectConnection);
    tThread->start();
    tTemplateOperator->ZGetTemplateXml(tTemplateName);
}

void ZTemplateEditor::ZSlotSetCellInformation()
{
    ZSheet *tSheet=qobject_cast<ZSheet*>(this->m_tabWidget->currentWidget());
    if(!tSheet)
    {
        return;
    }
    //only fetch the first cell's attribute.
    QList<QTableWidgetItem*> tSelectedItems=tSheet->selectedItems();
    if(tSelectedItems.count()<=0)
    {
        return;
    }
    ZCell* tCell=static_cast<ZCell*>(tSelectedItems.at(0));
    if(!tCell)
    {
        return;
    }

    ZCellInfoDialog tCellInfoDia;
    //cell font.
    tCellInfoDia.ZGetCellFont()->ZSetFontFamily(tCell->ZGetFont().family());
    tCellInfoDia.ZGetCellFont()->ZSetFontSize(tCell->ZGetFont().pointSize());
    tCellInfoDia.ZGetCellFont()->ZSetFontBold(tCell->ZGetFont().bold());
    tCellInfoDia.ZGetCellFont()->ZSetFontItalic(tCell->ZGetFont().italic());
    //cell color.
    tCellInfoDia.ZGetCellColor()->ZSetForegroundColor(tCell->ZGetForegroundColor());
    tCellInfoDia.ZGetCellColor()->ZSetBackgroundColor(tCell->ZGetBackgroundColor());
    //cell data.
    tCellInfoDia.ZGetCellData()->ZSetCellData(tCell->ZGetCellData());
    tCellInfoDia.ZGetCellData()->ZSetCellDataType(tCell->ZGetDataType());
    tCellInfoDia.ZGetCellData()->ZSetAlignment(tCell->ZGetTextAlignment());
    tCellInfoDia.ZGetCellData()->ZSetMinValue(tCell->ZGetMinValue());
    tCellInfoDia.ZGetCellData()->ZSetMaxValue(tCell->ZGetMaxValue());
    tCellInfoDia.ZGetCellData()->ZSetToleranceValue(tCell->ZGetToleranceValue());
    tCellInfoDia.ZGetCellData()->ZSetLockCell(tCell->ZGetLockCell());
    tCellInfoDia.ZGetCellData()->ZSetCheckedSign(tCell->ZGetCheckedSign());
    //cell frame.
    tCellInfoDia.ZGetCellFrame()->ZSetTopFrame(tCell->ZTopFrameIsSet());
    tCellInfoDia.ZGetCellFrame()->ZSetBottomFrame(tCell->ZBottomFrameIsSet());
    tCellInfoDia.ZGetCellFrame()->ZSetLeftFrame(tCell->ZLeftFrameIsSet());
    tCellInfoDia.ZGetCellFrame()->ZSetRightFrame(tCell->ZRightFrameIsSet());
    tCellInfoDia.ZGetCellFrame()->ZSetFrameColor(tCell->ZGetFrameColor());
    tCellInfoDia.ZGetCellFrame()->ZSetFrameWidth(tCell->ZGetFrameWidth());

    if(tCellInfoDia.exec()==QDialog::Accepted)
    {
        //cell font.
        QString tFontFamily=tCellInfoDia.ZGetCellFont()->ZGetFontFamily();
        qint32 tFontSize=tCellInfoDia.ZGetCellFont()->ZGetFontSize();
        bool bFontBold=tCellInfoDia.ZGetCellFont()->ZGetFontBold();
        bool bFontItalic=tCellInfoDia.ZGetCellFont()->ZGetFontItalic();
        //cell color.
        QColor tFgColor=tCellInfoDia.ZGetCellColor()->ZGetForegroundColor();
        QColor tBgColor=tCellInfoDia.ZGetCellColor()->ZGetBackgroundColor();
        //cell data.
        QString tCellData=tCellInfoDia.ZGetCellData()->ZGetCellData();
        QString tCellDataType=tCellInfoDia.ZGetCellData()->ZGetCellDataType();
        qint32 tCellAlign=tCellInfoDia.ZGetCellData()->ZGetAlignment();
        qint32 tMinValue=tCellInfoDia.ZGetCellData()->ZGetMinValue();
        qint32 tMaxValue=tCellInfoDia.ZGetCellData()->ZGetMaxValue();
        qint32 tToleranceValue=tCellInfoDia.ZGetCellData()->ZGetToleranceValue();
        bool tLockCell=tCellInfoDia.ZGetCellData()->ZGetLockCell();
        bool tCheckSign=tCellInfoDia.ZGetCellData()->ZGetCheckedSign();
        //cell frame.
        bool bTopFrame=tCellInfoDia.ZGetCellFrame()->ZTopFrameIsSet();
        bool bBottomFrame=tCellInfoDia.ZGetCellFrame()->ZBottomFrameIsSet();
        bool bLeftFrame=tCellInfoDia.ZGetCellFrame()->ZLeftFrameIsSet();
        bool bRightFrame=tCellInfoDia.ZGetCellFrame()->ZRightFrameIsSet();
        QColor tFrameColor=tCellInfoDia.ZGetCellFrame()->ZGetFrameColor();
        qint32 tFrameWidth=tCellInfoDia.ZGetCellFrame()->ZGetFrameWidth();

#if 0
        //if the type is boolean,replace QTableWidgetItem with QCheckBox.
        if(tCellDataType=="Boolean")
        {
            for(qint32 i=0;i<tSelectedItems.count();i++)
            {
                QTableWidgetItem *tItem=tSelectedItems.at(i);
                if(tItem)
                {
                    ZCheckBoxCell *tCheckBoxCell=new ZCheckBoxCell;
                    tCheckBoxCell->setText(tItem->text());
                    tSheet->setCellWidget(tItem->row(),tItem->column(),tCheckBoxCell);
                    tSheet->setCurrentCell(tItem->row(),tItem->column(),QItemSelectionModel::Select);
                    delete tItem;
                }
            }
            return;
        }
#endif
        //other types need to reset.
        for(qint32 i=0;i<tSelectedItems.count();i++)
        {
            ZCell* tCell=static_cast<ZCell*>(tSelectedItems.at(i));
            //cell font.
            QFont tFont(tFontFamily,tFontSize);
            tFont.setBold(bFontBold);
            tFont.setItalic(bFontItalic);
            tCell->ZSetFont(tFont);
            //cell color.
            tCell->ZSetForegroundColor(tFgColor);
            tCell->ZSetBackgroundColor(tBgColor);
            //cell data.
            //tCell->ZSetCellData(tCellData);
            tCell->ZSetDataType(tCellDataType);
            tCell->ZSetTextAlignment(tCellAlign);
            tCell->ZSetMinMaxToleranceValue(tMinValue,tMaxValue,tToleranceValue);
            tCell->ZSetLockCell(tLockCell);
            tCell->ZSetCheckedSign(tCheckSign);

            //cell frame.
            tCell->ZSetTopFrame(bTopFrame);
            tCell->ZSetBottomFrame(bBottomFrame);
            tCell->ZSetLeftFrame(bLeftFrame);
            tCell->ZSetRightFrame(bRightFrame);
            tCell->ZSetFrameColor(tFrameColor);
            tCell->ZSetFrameWidth(tFrameWidth);

            //use cell delegate to generate frame.
            if(bTopFrame || bBottomFrame || bLeftFrame || bRightFrame)
            {
                tSheet->ZGetCellDelegate()->ZAddCellBorder(tCell);
            }else{
                tSheet->ZGetCellDelegate()->ZDelCellBorder(tCell);
            }
        }
    }
}
//template sheet was changed.
void ZTemplateEditor::ZSlotTemplateSheetChanged(QString templateName)
{
    //tag the sheet with a <*> prefix.
    for(qint32 i=0;i<this->m_tabWidget->count();i++)
    {
        QString tSheetName=this->m_tabWidget->tabText(i);
        if(tSheetName==templateName)
        {
            ZSheet *tSheet=qobject_cast<ZSheet*>(this->m_tabWidget->widget(i));
            if(tSheet)
            {
                QString tTemplateName=tSheet->ZGetSheetName();
                this->m_tabWidget->setTabText(this->m_tabWidget->indexOf(tSheet),QString("<*>")+tTemplateName);
                //show status message.
                this->ZGetStatusBar()->ZSetStatusMessage(tr("Template <%1> was changed.").arg(tTemplateName));
            }
            break;
        }
    }
}
void ZTemplateEditor::ZSlotMergeCell()
{
    ZSheet *tSheet=qobject_cast<ZSheet*>(this->m_tabWidget->currentWidget());
    if(tSheet)
    {
       tSheet->ZMergeCells();
    }
}
void ZTemplateEditor::ZSlotSplitCell()
{
    ZSheet *tSheet=qobject_cast<ZSheet*>(this->m_tabWidget->currentWidget());
    if(tSheet)
    {
       tSheet->ZSplitCells();
    }
}
bool ZTemplateEditor::ZCheckDatabaseState()
{
    QString tErrorMsg=QObject::tr("Failed to connect server.");
    //be sure the database is opened before operating.
    if(!this->m_dataBaseTemplate->ZIsConnected())
    {
        while(!this->m_dataBaseTemplate->ZOpenDatabase())
        {
            ZDataBaseTester tDBTester;
            if(tDBTester.exec()==QDialog::Accepted)
            {
                //connect success,continue to run.
                continue;
            }else{
                //connect failed and user cancel the operation.
                this->ZGetStatusBar()->ZSetStatusMessage(tErrorMsg);
                return false;
            }
        }
    }
    return true;
}

//for popup menu.
void ZTemplateEditor::ZSlotShowTemplatePopupMenu(QPoint pos)
{
    this->m_popupMenu->popup(QCursor::pos());
}
void ZTemplateEditor::ZSlotGetTemplateXmlFinish(QString templateName,QString templateXml)
{
    qDebug()<<"ZTemplateEditor::threadID:"<<this->thread();
#if 0
    //remove from hash.
    if(this->m_loadingThreadHash.contains(templateName))
    {
        QThread *tThread=this->m_loadingThreadHash.value(templateName);
        if(tThread)
        {
            this->m_loadingThreadHash.remove(templateName);
            delete tThread;
            qDebug()<<"delete from thread hash";
        }
    }
    if(this->m_loadingTemplateOperatorHash.contains(templateName))
    {
        ZTemplateOperator *tOperator=this->m_loadingTemplateOperatorHash.value(templateName);
        if(tOperator)
        {
            this->m_loadingTemplateOperatorHash.remove(templateName);
            qDebug()<<"delete from template operator hash";
                        delete tOperator;
        }
    }
#endif
    //add a new tab widget.
    ZSheet *tSheet=new ZSheet;
    tSheet->ZSetSheetName(templateName);
    tSheet->ZSetSheetXml(templateXml);
    tSheet->ZSetSheetState(ZSheet::SheetState_Saved);
    //notify user when data was changed.
    connect(tSheet,SIGNAL(ZSignalSheetChanged(QString)),this,SLOT(ZSlotTemplateSheetChanged(QString)));
    this->m_tabWidget->addTab(tSheet,QIcon(":/images/templateeditor.png"),templateName);
    this->m_tabWidget->setCurrentWidget(tSheet);
}
void ZTemplateEditor::ZSlotSetTemplateXmlFinish(QString templateName,qint32 retCode)
{
    if(retCode<0)
    {
        this->ZGetStatusBar()->ZSetStatusMessage(tr("Save template %1 failed.").arg(templateName));
        return;
    }
    for(qint32 i=0;i<this->m_tabWidget->count();i++)
    {
        QString tExistName=this->m_tabWidget->tabText(i);
        if(tExistName.startsWith("<*>"))
        {
            tExistName.remove(0,3);
        }
        if(tExistName==templateName)
        {
            this->m_tabWidget->setTabText(i,templateName);
            ZSheet *tSheet=static_cast<ZSheet*>(this->m_tabWidget->widget(i));
            if(tSheet)
            {
                tSheet->ZSetSheetState(ZSheet::SheetState_Saved);
            }
        }
    }
    this->ZGetStatusBar()->ZSetStatusMessage(tr("Save template %1 success.").arg(templateName));
}
