#ifndef PUSERMANAGERWIN_H
#define PUSERMANAGERWIN_H

#include <QFrame>
#include <QHBoxLayout>
#include <QToolButton>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTextEdit>
#include <QSplitter>
#include <QLabel>
#include <QComboBox>
#include <QMenu>
#include <QAction>
#include "pgblpara.h"
class PUserManagerWin : public QFrame,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    PUserManagerWin();
    ~PUserManagerWin();
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
    void ZSlotLoadDataFromServer();

    void ZSlotAddGrp();
    void ZSlotMdyGrp();
    void ZSlotDelGrp();
    void ZSlotAddUser();
    void ZSlotMdyUser();
    void ZSlotDelUser();
    void ZSlotBatchSelectAll();
    void ZSlotBatchUnSelectAll();
    void ZSlotBatchDelUser();
    void ZSlotExpandIn();
    void ZSlotExpandOut();

    void ZSlotImport();
    void ZSlotExport();
    void ZSlotSelectAll();
    void ZSlotUnSelectAll();

    void ZSlotExpand();
    void ZSlotImportXML();
    void ZSlotImportExcel();
    void ZSlotExportXML();
    void ZSlotExportExcel();
    void ZSlotPrint();
    void ZSlotHelp();
    void ZSlotTreeDblClicked(QModelIndex index);
    void ZSlotPopupMenu(const QPoint &pt);

    void ZSlotAatchDetch();
private:
    void ZAddLogMsg(QString logMsg);
    void ZUpdateGrpUserInfo(void);
private:
    //left.
    QToolButton *m_btnGrpOp;
    QMenu *m_menuGrp;
    QAction *m_actAddGrp;
    QAction *m_actMdyGrp;
    QAction *m_actDelGrp;

    QToolButton *m_btnUsrOp;
    QMenu *m_menuUsr;
    QAction *m_actAddUser;
    QAction *m_actMdyUser;
    QAction *m_actDelUser;
    QAction *m_actBatchSelectAll;
    QAction *m_actBatchUnSelectAll;
    QAction *m_actBatchDelUser;

    QToolButton *m_btnDisplay;
    QMenu *m_menuDisplay;
    QAction *m_actExpand;
    QAction *m_actDetch;
    QAction *m_actAatch;

    QToolButton *m_btnImport;
    QMenu *m_menuImport;
    QAction *m_actImportXML;
    QAction *m_actImportExcel;

    QToolButton *m_btnExport;
    QMenu *m_menuExport;
    QAction *m_actExportXML;
    QAction *m_actExportExcel;

    QToolButton *m_btnPrint;
    QToolButton *m_btnHelp;
    QVBoxLayout *m_vLayoutBtn;

    //right.
    QHBoxLayout *m_hLayoutRightTop;
    QToolButton *m_tbTurnPage[4];
    QLabel *m_llSummaryInfo;
    QComboBox *m_cbPage;
    QTreeWidget *m_treeWidget;
    QVBoxLayout *m_vLayoutRight;
    //main.
    QHBoxLayout *m_hLayoutMain;

private:
    typedef struct{
        QString permBits;
        QString roleMemo;
    }RolePrivateData;
    QMap<QString,RolePrivateData> m_roleMap;

    QMap<QString,QTreeWidgetItem*> m_roleTreeItemMap;
};

#endif // PUSERMANAGERWIN_H
