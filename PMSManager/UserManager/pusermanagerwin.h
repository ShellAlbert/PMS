#ifndef PUSERMANAGERWIN_H
#define PUSERMANAGERWIN_H

#include <QFrame>
#include <QHBoxLayout>
#include <QToolButton>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTextEdit>
#include <QSplitter>
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
    void ZSlotImport();
    void ZSlotExport();
    void ZSlotTreeDblClicked(QModelIndex index);
private:
    void ZAddLogMsg(QString logMsg);
private:
    //left.
    QToolButton *m_btnAddGrp;
    QToolButton *m_btnMdyGrp;
    QToolButton *m_btnDelGrp;

    QToolButton *m_btnAddUser;
    QToolButton *m_btnMdyUser;
    QToolButton *m_btnDelUser;

    QToolButton *m_btnExpand;
    QToolButton *m_btnImport;
    QToolButton *m_btnExport;
    QVBoxLayout *m_vLayoutBtn;

    //right.
    QTreeWidget *m_treeWidget;
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
