#ifndef ZBACKUPMANAGER_H
#define ZBACKUPMANAGER_H

#include <QDialog>
#include <QTreeWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "pgblpara.h"
class ZBackupManager : public QDialog,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    ZBackupManager(QWidget *parent=0);
    ~ZBackupManager();

    void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
private slots:
    void ZSlotBackup();
    void ZSlotRestore();
    void ZSlotDelete();
private:
    QTreeWidget *m_tree;
    QToolButton *m_tbBackup;
    QToolButton *m_tbDelete;
    QToolButton *m_tbRestore;
    QToolButton *m_tbClose;
    QHBoxLayout *m_hLayout;
    QVBoxLayout *m_vLayout;
};

#endif // ZBACKUPMANAGER_H
