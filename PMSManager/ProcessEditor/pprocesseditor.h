#ifndef PPROCESSEDITOR_H
#define PPROCESSEDITOR_H

#include <QFrame>
#include <QToolButton>
#include <QTabWidget>
#include <QTreeWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QSplitter>
#include <QScrollArea>
#include "ProcessEditor/pstepeditor.h"
#include "pgblpara.h"
class ZProcessManager:public QFrame
{
    Q_OBJECT
public:
    ZProcessManager();
    ~ZProcessManager();
signals:
    void ZSignalOpenProcess(QString processName);
private slots:
    void ZSlotDblClickProcess(QModelIndex index);
public:
    QTreeWidget *m_treeWidget;
    QVBoxLayout *m_vLayout;
};
class ZProcessEditor:public QFrame
{
    Q_OBJECT
public:
    ZProcessEditor();
    ~ZProcessEditor();
    PStepEditor* ZAddStep();
    void ZSetProcessName(QString name);
    QString ZGetProcessName();
    qint32 ZGetStepCount();
    bool ZIsAllStepsValidate();
    PStepEditor* ZGetStepEditor(qint32 index);

    QString ZGetProcessXmlData();
    void ZSetProcessXmlData(QString xmlData);
public slots:
    void ZSlotDataChanged();
private:
    void ZAutoRelayout();
signals:
    void ZSignalLogMsg(QString logInfo);
    void ZSignalDataChanged(QString processName);
private slots:
    void ZSlotRemoveStepEditor(PStepEditor* edit);
private:
    QFrame *m_scrollWidget;
    QScrollArea *m_scrollArea;
    QGridLayout *m_gridLayout;
    QVBoxLayout *m_vLayout;
    QList<PStepEditor*> m_stepEditList;
    QString m_processName;
};
class PProcessEditor : public QFrame,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    PProcessEditor();
    ~PProcessEditor();

    void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
signals:
    void ZSignalCloseEvent(QString widget);
    void ZSignalLogMsg(QString logMsg);

private slots:
    void ZSlotAddProcess();
    void ZSlotOpenProcess();
    void ZSlotSaveProcess();
    void ZSlotSaveAsProcess();
    void ZSlotDelProcess();
    void ZSlotAddStep();
    void ZSlotRemoveTab(qint32 index);
    void ZSlotDataChanged(QString processName);
    void ZSlotOpenProcess(QString processName);
    void ZSlotHelp();

    void ZSlotPopupMenu(const QPoint &pt);
private:
    void ZAddLogMsg(QString logInfo);
private:
    //left.
    QToolButton *m_tbNewProcess;
    QToolButton *m_tbOpenProcess;
    QToolButton *m_tbSaveProcess;
    QToolButton *m_tbSaveAsProcess;
    QToolButton *m_tbDelProcess;

    QToolButton *m_tbNewStep;
    QToolButton *m_tbHelp;
    QVBoxLayout *m_vLayoutTb;
    //right.
    QTabWidget *m_tabWidget;
    ZProcessManager *m_processManager;
    //main.
    QHBoxLayout *m_hLayout;
};

#endif // PPROCESSEDITOR_H
