#ifndef ZTASKSHEET_H
#define ZTASKSHEET_H

#include <QTableWidget>
#include <Sheet/zcelldelegate.h>
#include <QTreeWidget>
#include <QHBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QMap>
class ZTaskSheet : public QTableWidget
{
    Q_OBJECT
public:
    ZTaskSheet(QTreeWidget *varTree,QWidget *parent=0);
    ~ZTaskSheet();

    void ZSetTaskName(QString taskName);
    QString ZGetTaskName();

    void ZSetRefTemplateName(QString name);
    QString ZGetRefTemplateName();

    void ZSetTemplateXmlDataAndVarSourceXmlData(QString templateXmlData,QString varSourceXmlData);

    void ZExecuteLoadActionBeforeShow();

    QString ZGetCellDataByLoadAction(QString action);

    void ZSetTaskState(qint32 state);
    qint32 ZGetTaskState();
signals:
    void ZSignalLogMsg(QString logMsg);
    void ZSignalDataChanged(QString taskName);
private slots:
    void ZSlotCellChanged(int row,int col);
    void ZSlotCellClicked(QTableWidgetItem*);

public:
    ZCellDelegate *m_cellDelegate;
private:
    QString m_RefTemplate;
    QString m_TaskName;

    QTreeWidget *m_varTree;
    class VarInfo
    {
    public:
        QString varType;
        QString dataType;
        QString varRule;
        QString action;
        QString value;
    };
    QMap<QString,VarInfo> m_varMap;

    qint32 m_taskState;
};
class ZTaskWidget:public QFrame
{
    Q_OBJECT
public:
    ZTaskWidget(QWidget *parent=0);
    ~ZTaskWidget();

    QString ZGetTaskVarValueXmlData();
    void ZSetGeVarBindCellEditable(bool bEditable);
    void ZSetVarValueXmlData(QString xmlData);
    bool ZCheckCellDataValidation();

    qint32 ZGetTaskState();
    void ZSetTaskState(qint32 state);
signals:
    void ZSignalLogMsg(QString logMsg);
    void ZSignalDataChanged(QString taskName);
private slots:
    void ZSlotVarDblClicked(QModelIndex index);
public:
    ZTaskSheet* m_sheet;
    QTreeWidget *m_treeVar;
    QTreeWidgetItem *m_geVarItem;
    QTreeWidgetItem *m_autoVarItem;
    QLabel *m_llTaskStateIcon;
    QLabel *m_llTaskStateText;
    QHBoxLayout *m_hLayoutTaskState;
    QWidget *m_widgetTaskState;
    QSplitter *m_rightSpliter;
    QSplitter *m_leftSpliter;
    QHBoxLayout *m_hLayout;

    qint32 m_TaskState;
    ////////////////////////////////
public:
    QString m_refProcess;
    QString m_refStep;
    QString m_refTemplate;
    QString m_creator;
    QString m_createTime;
    QString m_checker;
    QString m_checkTime;
};
#endif // ZTASKSHEET_H
