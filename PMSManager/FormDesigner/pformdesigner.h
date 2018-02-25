#ifndef PFORMDESIGNER_H
#define PFORMDESIGNER_H
#include <QLineEdit>
#include <QFrame>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTabWidget>
#include <QToolButton>
#include <QTableWidget>
#include <QCheckBox>
#include <QDialog>
#include <QMenu>
#include <QAction>
#include <QComboBox>
#include <QLabel>
#include <QtPrintSupport/QPrinter>
#include <FormDesigner/zbasewidget.h>
#include <pgblpara.h>
class ZFormList:public QFrame
{
    Q_OBJECT
public:
    ZFormList();
    ~ZFormList();
public:
    QTreeWidget *m_tree;
    QVBoxLayout *m_vLayout;
};
class ZGraphicsView:public QGraphicsView
{
    Q_OBJECT
public:
    typedef enum{
        Mode_Normal=0,
        Mode_Add_CheckBox=1,
        Mode_Add_SpinBox=2,
        Mode_Add_DateTimeEdit=3,
        Mode_Add_Table=4,
        Mode_Add_Text=5,
        Mode_Add_Line=6,
        Mode_Add_Rectangle=7,
    }OpMode;

    ZGraphicsView(OpMode mode=Mode_Normal,QGraphicsScene *parent=0);

    void ZAddCheckBox();
    void ZAddRectangle();
    void ZAddSpinBox();
    void ZAddDateTimeEdit();
    void ZAddTable();
    void ZAddText();
    void ZAddLine();
signals:
    void ZSignalDataChanged();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
private:
    OpMode m_opMode;
    QGraphicsScene *m_scene;

    bool m_bLeftButtonPressed;
    QGraphicsProxyWidget *m_moveProxyWidget;
    QPoint m_startPos;
    QGraphicsProxyWidget *m_resizeHProxyWidget;
    QGraphicsProxyWidget *m_resizeVProxyWidget;
};
class ZFormWidget:public QFrame
{
    Q_OBJECT
public:
    ZFormWidget();
    ~ZFormWidget();

    QString ZGetFormName();
    void ZSetFormName(QString name);

    QString ZGetXmlData();
    void ZPutXmlData(QString formXmlData);
signals:
    void ZSignalDataChanged();
protected:
    void resizeEvent(QResizeEvent *event);
public:
    QHBoxLayout *m_hLayout;
    QLabel *m_llLeftTop[2];
    QLabel *m_llLeftBottom[2];
    QLabel *m_llRightTop[2];
    QLabel *m_llRightBottom[2];
    QLabel *m_llPageSize;
    QComboBox *m_cbPageSize;
    QGraphicsScene *m_scene;
    ZGraphicsView *m_view;
    QList<QGraphicsProxyWidget*> m_proxyList;
    QVBoxLayout *m_vLayout;

    QString m_formName;
};
class PFormDesigner : public QFrame,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    PFormDesigner();
    ~PFormDesigner();

    void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void ZSignalCloseEvent(QString widget);
    void ZSignalLogMsg(QString logMsg);


private slots:
    void ZSlotNewForm();
    void ZSlotOpenForm();
    void ZSlotSaveForm();
    void ZSlotDelForm();

    void ZSlotAddLine();
    void ZSlotAddRectangle();
    void ZSlotAddCheckBox();
    void ZSlotAddSpinBox();
    void ZSlotAddDateTimeEdit();
    void ZSlotAddTable();
    void ZSlotAddText();

    void ZSlotSelectAll();
    void ZSlotDeSelectAll();

    void ZSlotPrint();
    void ZSlotPrintView();
    void ZSlotDoPrinter(QPrinter *printer);

    void ZSlotFormChanged();
    void ZSlotCloseTab(qint32 index);
    void ZSlotOpenForm(QModelIndex index);
private:
    void ZAddLogMsg(QString logMsg);
private:
    //left.
    QToolButton *m_tbFormOp;
    QMenu *m_menuFormOp;
    QAction *m_actNewForm;
    QAction *m_actOpenForm;
    QAction *m_actSaveForm;
    QAction *m_actDelForm;

    QToolButton *m_tbFormComponent;
    QMenu *m_menuFormComp;
    QAction *m_actAddLine;
    QAction *m_actAddRectangle;
    QAction *m_actAddText;
    QAction *m_actAddCheckBox;
    QAction *m_actAddSpinBox;
    QAction *m_actAddDateTime;
    QAction *m_actAddTable;

    QToolButton *m_tbSelect;
    QMenu *m_menuSelect;
    QAction *m_actSelectAll;
    QAction *m_actDeSelectAll;

    QToolButton *m_tbPrintView;
    QToolButton *m_tbPrint;

    QVBoxLayout *m_vLayoutTb;
    //right.
    QTabWidget *m_tabWidget;
    ZFormList *m_formList;
    QHBoxLayout *m_hLayout;
};

#endif // PFORMDESIGNER_H
