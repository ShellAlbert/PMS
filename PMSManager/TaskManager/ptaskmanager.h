#ifndef PTASKMANAGER_H
#define PTASKMANAGER_H

#include <QFrame>
#include <QHBoxLayout>
#include <QToolButton>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTabWidget>
#include <QComboBox>
#include <QLabel>
#include <QPrinter>
#include <QMenu>
#include <QListWidget>
#include <QAction>
#include "pgblpara.h"
class PTaskList:public QFrame
{
  Q_OBJECT
public:
    PTaskList(QWidget *parent=0);
    ~PTaskList();
signals:
    void ZSignalFilterChanged(qint32 index);
    void ZSignalAdvancedSearch();
public:
    QTreeWidget *m_tree;
    QVBoxLayout *m_vLayout;

private:
    QHBoxLayout *m_hLayoutFilter;
    QLabel *m_llTaskFilter;
    QComboBox *m_cbTaskFilter;
    QToolButton *m_tbSearch;
};
class PTaskManager : public QFrame,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    PTaskManager(QWidget *parent=0);
    ~PTaskManager();

    void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
signals:
    void ZSignalCloseEvent(QString widget);
    void ZSignalLogMsg(QString logMsg);
    void ZSignalAatch(QString moduleName);
    void ZSignalDetch(QString moduleName);
private slots:
    void ZSlotAddTask();
    void ZSlotSaveTask();
    void ZSlotMdyTask();
    void ZSlotDelTask();
    void ZSlotSubmitTask();
    void ZSlotWithdrawTask();
    void ZSlotCheckOkay();
    void ZSlotCheckFailed();
    void ZSlotArchieve();
    void ZSlotPrintHtml();
    void ZSlotPrintPdf();
    void ZSlotPrint();
    void ZSlotHelp();
    void ZSlotTaskDataChanged(QString taskName);
    void ZSlotCloseTabWidget(qint32 index);
    void ZSlotDblClickOpenTask(QModelIndex index);
    void ZSlotRefreshTaskList(qint32 index);

    void ZSlotPopupMenu(const QPoint &pt);

    void ZSlotAatchDetch();

    void ZSlotInputPreset();
private:
    void ZAddLogMsg(QString logMsg);
private:
    //left.
    QToolButton *m_btnAddTask;
    QToolButton *m_btnSaveTask;
    QToolButton *m_btnMdyTask;
    QToolButton *m_btnDelTask;
    QToolButton *m_btnArchieve;

    QToolButton *m_tbTaskManage;
    QMenu *m_menuTaskManage;
    QAction *m_actSubmitTask;
    QAction *m_actWithdrawTask;
    QAction *m_actCheckOkay;
    QAction *m_actCheckFailed;

    QToolButton *m_btnDisplay;
    QMenu *m_menuDisplay;
    QAction *m_actDetch;
    QAction *m_actAatch;

    QToolButton *m_tbOption;
    QMenu *m_menuOption;
    QAction *m_actProductLine;
    QAction *m_actClass;
    QAction *m_actOrderNo;
    QAction *m_actProductNo;

    QToolButton *m_btnPrint;
    QMenu *m_menuPrint;
    QAction *m_actPrintHtml;
    QAction *m_actPrintPdf;

    QToolButton *m_tbHelp;
    QVBoxLayout *m_vLayoutBtn;

    //right.
    QTabWidget *m_tabWidget;
    PTaskList *m_taskList;
    //main.
    QHBoxLayout *m_hLayoutMain;
};
//生产线/机器号 输入预置对话框
class ZProductLinePresetDialog:public QDialog
{
    Q_OBJECT
public:
    ZProductLinePresetDialog(QWidget *parent=0);
    ~ZProductLinePresetDialog();

    QStringList ZReadList();
    QStringList ZGetList();
protected:
    QSize sizeHint() const;
    void closeEvent(QCloseEvent *e);
private slots:
    void ZSlotAdd();
    void ZSlotDel();
    void ZSlotReset();
    void ZSlotImport();
    void ZSlotExport();
private:
    QListWidget *m_list;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDel;
    QToolButton *m_tbReset;
    QToolButton *m_tbImport;
    QToolButton *m_tbExport;
    QVBoxLayout *m_vLayoutBtn;
    QHBoxLayout *m_hLayout;
};
////////////////////////////////
/// \brief The ZProductLinePresetDialog class
//班组输入预置对话框
class ZClassPresetDialog:public QDialog
{
    Q_OBJECT
public:
    ZClassPresetDialog(QWidget *parent=0);
    ~ZClassPresetDialog();

    QStringList ZReadList();
    QStringList ZGetList();
protected:
    QSize sizeHint() const;
    void closeEvent(QCloseEvent *e);
private slots:
    void ZSlotAdd();
    void ZSlotDel();
    void ZSlotReset();
    void ZSlotImport();
    void ZSlotExport();
private:
    QListWidget *m_list;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDel;
    QToolButton *m_tbReset;
    QToolButton *m_tbImport;
    QToolButton *m_tbExport;
    QVBoxLayout *m_vLayoutBtn;
    QHBoxLayout *m_hLayout;
};
//订单号输入预置对话框
class ZOrderNoPresetDialog:public QDialog
{
    Q_OBJECT
public:
    ZOrderNoPresetDialog(QWidget *parent=0);
    ~ZOrderNoPresetDialog();

    QStringList ZReadList();
    QStringList ZGetList();
protected:
    QSize sizeHint() const;
    void closeEvent(QCloseEvent *e);
private slots:
    void ZSlotAdd();
    void ZSlotDel();
    void ZSlotReset();
    void ZSlotImport();
    void ZSlotExport();
private:
    QListWidget *m_list;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDel;
    QToolButton *m_tbReset;
    QToolButton *m_tbImport;
    QToolButton *m_tbExport;
    QVBoxLayout *m_vLayoutBtn;
    QHBoxLayout *m_hLayout;
};
///产品编号预置输入对话框
class ZProductNoPresetDialog:public QDialog
{
    Q_OBJECT
public:
    ZProductNoPresetDialog(QWidget *parent=0);
    ~ZProductNoPresetDialog();

    QStringList ZReadList();
    QStringList ZGetList();
protected:
    QSize sizeHint() const;
    void closeEvent(QCloseEvent *e);
private slots:
    void ZSlotAdd();
    void ZSlotDel();
    void ZSlotReset();
    void ZSlotImport();
    void ZSlotExport();
private:
    QListWidget *m_list;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDel;
    QToolButton *m_tbReset;
    QToolButton *m_tbImport;
    QToolButton *m_tbExport;
    QVBoxLayout *m_vLayoutBtn;
    QHBoxLayout *m_hLayout;
};
#endif // PTASKMANAGER_H
