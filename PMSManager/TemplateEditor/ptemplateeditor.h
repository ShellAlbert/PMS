#ifndef PTEMPLATEEDITOR_H
#define PTEMPLATEEDITOR_H

#include <QWidget>
#include <QToolButton>
#include <QTreeWidget>
#include <QSplitter>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMenu>
#include <QTabWidget>
#include <QComboBox>
#include "Sheet/zsheet.h"
#include "pgblpara.h"
//#include <QtXlsx/QtXlsx>
class ZTabWidget:public QFrame
{
    Q_OBJECT
public:
    virtual QString ZGetWidgetTypeName()=0;
};
class ZTemplateVarSrcView:public QFrame
{
    Q_OBJECT
public:
    ZTemplateVarSrcView(QWidget *parent=0);
    ~ZTemplateVarSrcView();

    void ZSetData(QString templateName,QString varSrcName);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QToolButton *m_tbTemplate;
    QToolButton *m_tbVarSrc;
    QVBoxLayout *m_vLayout;
    QHBoxLayout *m_hLayout;
};
class ZTemplateWidget:public ZTabWidget
{
    Q_OBJECT
public:
    ZTemplateWidget();
    ~ZTemplateWidget();
    QString ZGetWidgetTypeName();

signals:
    void ZSignalOpenTemplate(QString templateName);
    void ZSignalOpenVarSource(QString varSourceName);
private slots:
    void ZSlotTemplateTreeDoubleClicked(QModelIndex index);
    void ZSlotVarSourceTreeDoubleClicked(QModelIndex index);

    void ZSlotUpdateView(QModelIndex index);
public:
    QTreeWidget *m_treeWidget;
    QTreeWidget *m_treeVarSource;
    QSplitter *m_splitterV;
    QVBoxLayout *m_vLayoutLeft;
    QFrame *m_frmLeft;


    ZTemplateVarSrcView *m_view;
    QSplitter *m_splitterH;
    QVBoxLayout *m_vLayout;
};

class ZSheetWidget:public ZTabWidget
{
    Q_OBJECT
public:
    ZSheetWidget();
    ~ZSheetWidget();
    QString ZGetWidgetTypeName();

    //get or put template xml data on qtablewidget.
    QString ZGetTemplateXmlData();
    void ZPutTemplateXmlData(QString xmlData);

    void ZPutVarSourceXmlData(QString xmlData);
signals:
    void ZSignalDataChanged(QString templateName);
    void ZSignalAlignmentChanged(qint32 alignNo);
    void ZSignalMergeCell();
    void ZSignalSplitCell();
private slots:
    void ZSlotVarDblClicked(QTreeWidgetItem*item,int column);
    void ZSlotAlignmentChanged();
    void ZSlotMergeSplitCell();
    void ZSlotCellActivated(qint32 x,qint32 y);
    void ZSlotCellAutoAdjust(void);

    void ZSlotPopMenu(const QPoint &pt);
    void ZSlotBindCurrentCell();
    void ZSlotBindCell();
    void ZSlotRemoveBind();
    void ZSlotAutoBindPreCell();

private slots:
    //adjust (x,y) when add col/add row/del col/del row actions occured.
    void ZSlotIncXWhenAddRow(qint32 rowNo);
    void ZSlotIncYWhenAddCol(qint32 colNo);
    void ZSlotDecXWhenDelRow(qint32 rowNo);
    void ZSlotDecYWhenDelCol(qint32 colNo);
public:

    ZSheet *m_sheet;
    //////////////////////////
    QTreeWidget *m_treeWidget;

    //line 2.
    QToolButton *m_tbAlignLeft;
    QToolButton *m_tbAlignHCenter;
    QToolButton *m_tbAlignRight;
    QToolButton *m_tbAlignTop;
    QToolButton *m_tbAlignVCenter;
    QToolButton *m_tbAlignBottom;
    //line3.
    QToolButton *m_tbAlignCenter;
    QToolButton *m_tbMerge;
    QToolButton *m_tbSplit;
    QToolButton *m_tbAutoAdjust;
    QLineEdit *m_leXY;

    QGridLayout *m_gLayoutBtn;

    QFrame *m_frmBottom;
    QHBoxLayout *m_hLayoutBottom;
    QSplitter *m_spliter;
    QVBoxLayout *m_vLayout;

    QTreeWidgetItem *m_generalVarItem;
    QTreeWidgetItem *m_autoVarItem;
};

class PTemplateEditor : public QFrame,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    explicit PTemplateEditor(QWidget *parent = 0);
    ~PTemplateEditor();

    void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
signals:
    void ZSignalCloseEvent(QString widget);
    void ZSignalLogMsg(QString logMsg);
    void ZSignalDetach(QString mdlName);
    void ZSignalAatch(QString mdlName);
public slots:
    void ZSlotNewTemplate();
    void ZSlotOpenTemplate();
    void ZSlotOpenTemplate(QString templateName);
    void ZSlotSaveTemplate();
    void ZSlotSaveAsTemplate();
    void ZSlotDelTemplate();
    void ZSlotBindVarSource();
    void ZSlotUnbindVarSource();

    void ZSlotImportTemplate();
    void ZSlotExportTemplate();
    void ZSlotImportExcel();
    void ZSlotExportExcel();

    void ZSlotInsertPic();
    void ZSlotRemovePic();
    void ZSlotMergeCell();
    void ZSlotSplitCell();
    void ZSlotCellFont();
    void ZSlotCellColor();
    void ZSlotCellFrame();
    void ZSlotCellBindVar();
    void ZSlotCellUnbindVar();
    void ZSlotFontChanged(QString fontFamily,qint32 fontSize,bool bold,bool italic);

    void ZSlotHAlignLeft();
    void ZSlotHAlignCenter();
    void ZSlotHAlignRight();
    void ZSlotVAlignTop();
    void ZSlotVAlignCenter();
    void ZSlotVAlignBottom();
    void ZSlotAlignmentChanged(qint32 alignNo);

    void ZSlotSysPic1();
    void ZSlotSysPic2();
    void ZSlotSysPic3();

    void ZSlotInsertCheckBox();
    void ZSlotInsertComboBox();
    void ZSlotInsertSpinBox();
    void ZSlotInsertDateTimeEdit();

    void ZSlotAddVarSource();
    void ZSlotDelVarSource();
    void ZSlotOpenVarSource();
    void ZSlotOpenVarSource(QString varSourceName);
    void ZSlotExportVarSourceTemplate();
    void ZSlotImportVarSource();

    void ZSlotRemoveTab(qint32 index);
    void ZSlotSheetDataChanged(QString templateName);

    void ZSlotAatchDetach();
    void ZSlotPrintHtml();
    void ZSlotPrintPdf();
    void ZSlotPrint();

    void ZSlotHelp();

    void ZSlotTemplateTreePopupMenu(const QPoint &pt);
    void ZSlotVarSourceTreePopupMenu(const QPoint &pt);
private:
    void ZSetTextAlignment(qint32 alignment);
    void ZAddLogMsg(QString logMsg);
private:
    //left.
    QVBoxLayout *m_vLayoutBtns;

    QToolButton *m_btnTemplate;
    QMenu *m_menuTemplate;
    QAction *m_actNewTemplate;
    QAction *m_actOpenTemplate;
    QAction *m_actSaveTemplate;
    QAction *m_actSaveAsTemplate;
    QAction *m_actDelTemplate;
    QAction *m_actBindVarSource;
    QAction *m_actUnbindVarSource;

    QToolButton *m_btnImExport;
    QMenu *m_menuImExport;
    QAction *m_actImportTemplate;
    QAction *m_actExportTemplate;
    QAction *m_actImportExcel;
    QAction *m_actExportExcel;

    QToolButton *m_btnCell;
    QMenu *m_menuCell;
    QAction *m_actInsertPic;
    QAction *m_actRemovePic;
    QAction *m_actMergeCell;
    QAction *m_actSplitCell;
    QAction *m_actCellFont;
    QAction *m_actCellColor;
    QAction *m_actCellFrame;
    QAction *m_actCellBindVar;
    QAction *m_actCellUnbindVar;

    QToolButton *m_btnAlign;
    QMenu *m_menuAlign;
    QMenu *m_menuHAlign;
    QMenu *m_menuVAlign;
    QAction *m_actHLeftAlign;
    QAction *m_actHCenterAlign;
    QAction *m_actHRightAlign;
    QAction *m_actVTopAlign;
    QAction *m_actVCenterAlign;
    QAction *m_actVBottomAlign;

    QToolButton *m_btnSysComponent;
    QMenu *m_menuSysComponent;
    QAction *m_actInsertCheckBox;
    QAction *m_actInsertComboBox;
    QAction *m_actInsertSpinBox;
    QAction *m_actInsertDateTimeEdit;

    QToolButton *m_btnSysPic;
    QMenu *m_menuSysPic;
    QAction *m_actSysPic1;
    QAction *m_actSysPic2;
    QAction *m_actSysPic3;

    QToolButton *m_btnVarSourceOp;
    QMenu *m_menuVarSourceOp;
    QAction *m_actOpenVarSource;
    QAction *m_actAddVarSource;
    QAction *m_actDelVarSource;
    QAction *m_actExportVarSourceTemplate;
    QAction *m_actImportVarSource;

    QToolButton *m_btnDisplay;
    QMenu *m_menuDisplay;
    QAction *m_actDetach;
    QAction *m_actAatch;

    QToolButton *m_tbPrint;
    QMenu *m_menuPrint;
    QAction *m_actPrint;
    QAction *m_actPrintHtml;
    QAction *m_actPrintPdf;

    QToolButton *m_tbHelp;

    //right.
    ZTemplateWidget *m_templateWidget;
    QTabWidget* m_tabWidget;

    //main layout.
    QHBoxLayout *m_hLayoutMain;
};
#endif // PTEMPLATEEDITOR_H
