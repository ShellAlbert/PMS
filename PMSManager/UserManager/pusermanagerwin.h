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
private slots:
    void ZSlotAddGrp();
    void ZSlotMdyGrp();
    void ZSlotDelGrp();
    void ZSlotAddUser();
    void ZSlotMdyUser();
    void ZSlotDelUser();
    void ZSlotExpand();
    void ZSlotImportXML();
    void ZSlotImportExcel();
    void ZSlotExportXML();
    void ZSlotExportExcel();
    void ZSlotPrint();
    void ZSlotHelp();
    void ZSlotTreeDblClicked(QModelIndex index);
    void ZSlotPopupMenu(const QPoint &pt);
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

    QToolButton *m_btnExpand;
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
};

#endif // PUSERMANAGERWIN_H
