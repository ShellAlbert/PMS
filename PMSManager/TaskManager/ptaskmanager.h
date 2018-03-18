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
public:
    QTreeWidget *m_tree;
    QVBoxLayout *m_vLayout;

private:
    QHBoxLayout *m_hLayoutFilter;
    QLabel *m_llTaskFilter;
    QComboBox *m_cbTaskFilter;
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

#endif // PTASKMANAGER_H
