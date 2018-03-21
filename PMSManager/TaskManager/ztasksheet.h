#ifndef ZTASKSHEET_H
#define ZTASKSHEET_H

#include <QTableWidget>
#include <Sheet/zcelldelegate.h>
#include <QTreeWidget>
#include <QToolButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QDialog>
#include <QComboBox>
#include <QMap>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
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

    void ZSetProcessName(QString processName);
    QString ZGetProcessName();

    void ZSetStepName(QString stepName);
    QString ZGetStepName();

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
protected:
    void paintEvent(QPaintEvent *e);
public:
    ZCellDelegate *m_cellDelegate;
private:
    QString m_RefTemplate;
    QString m_TaskName;
    QString m_ProcessName;
    QString m_StepName;

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
class ZCellDataCheckReportDialog:public QDialog
{
    Q_OBJECT
public:
    ZCellDataCheckReportDialog(QWidget *parent=0);
    ~ZCellDataCheckReportDialog();
    void ZAddReportLog(QString reportLog);
private slots:
    void ZSlotCopy2Clipboard();
private:
    QTextEdit *m_te;
    QToolButton *m_tbCopy;
    QToolButton *m_tbOkay;
    QHBoxLayout *m_hLayout;
    QVBoxLayout *m_vLayout;
};
class ZTaskWidget:public QFrame
{
    Q_OBJECT
public:
    ZTaskWidget(QWidget *parent=0);
    ~ZTaskWidget();


    QStringList ZGetTaskAuxData();
    void ZSetTaskAuxData(QStringList auxData);

    void ZSetGeVarBindCellEditable(bool bEditable);

    QString ZGetTaskVarValueXmlData();
    void ZSetVarValueXmlData(QString xmlData);

    bool ZCheckCellDataValidation();

    qint32 ZGetTaskState();
    void ZSetTaskState(qint32 state);
signals:
    void ZSignalLogMsg(QString logMsg);
    void ZSignalDataChanged(QString taskName);
private slots:
    void ZSlotVarDblClicked(QModelIndex index);
    void ZSlotPopupMenu(const QPoint &pt);
    void ZSlotShowLineChart();
    void ZSlotShowBarChart();
public:
    ///////////////////////////
    QHBoxLayout *m_hLayoutTop;
    QLabel *m_llProductLine;
    QComboBox *m_cbProuctLine;
    QLabel *m_llClass;
    QComboBox *m_cbClass;
    QLabel *m_llOrderNo;
    QComboBox *m_cbOrderNo;
    QLabel *m_llProductNo;
    QComboBox *m_cbProductNo;
    ///////////////////////////
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
    QVBoxLayout *m_vLayoutMain;

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
#include <QComboBox>
#include <QDateTimeEdit>
using namespace QtCharts;
class ZLineChartDialog:public QDialog
{
    Q_OBJECT
public:
    ZLineChartDialog(QWidget *parent=0);
    ~ZLineChartDialog();
    void ZSetVariableList(QStringList varList);
protected:
    QSize sizeHint() const;
private:
    QLabel *m_llVarList;
    QComboBox *m_cbVarList;
    QLabel *m_llDEStart;
    QDateTimeEdit *m_deStart;
    QLabel *m_llDEEnd;
    QDateTimeEdit *m_deEnd;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDraw;


    QHBoxLayout *m_hLayout;

    /////////////////////////////////
    QList<QLineSeries*> m_lineSeriesList;
    QChartView *m_chartView;
    QChart *m_chart;
    QValueAxis *m_xAxis;
    QValueAxis *m_yAxis;
    QVBoxLayout *m_vLayout;
};
#include <QBarSet>
#include <QBarSeries>
class ZBarChartDialog:public QDialog
{
    Q_OBJECT
public:
    ZBarChartDialog(QWidget *parent=0);
    ~ZBarChartDialog();
    void ZSetVariableList(QStringList varList);
protected:
    QSize sizeHint() const;
private:
    QLabel *m_llVarList;
    QComboBox *m_cbVarList;
    QLabel *m_llDEStart;
    QDateTimeEdit *m_deStart;
    QLabel *m_llDEEnd;
    QDateTimeEdit *m_deEnd;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDraw;

    QHBoxLayout *m_hLayout;

    /////////////////////////////////
    QList<QBarSet*> m_barSetList;
    QBarSeries *m_barSeries;
    QChartView *m_chartView;
    QChart *m_chart;
    QValueAxis *m_xAxis;
    QValueAxis *m_yAxis;
    QVBoxLayout *m_vLayout;
};
#endif // ZTASKSHEET_H
