#ifndef ZLINKROLESELECTDIA_H
#define ZLINKROLESELECTDIA_H

#include <QDialog>
#include <QToolButton>
#include <QLabel>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "pgblpara.h"
class ZLinkRoleSelectDia : public QDialog,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    ZLinkRoleSelectDia(QWidget *parent=0);
    ~ZLinkRoleSelectDia();

    void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
    QStringList ZGetSelectedRoleList();
protected:
    QSize sizeHint() const;
private:
    QTreeWidget *m_tree;
    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayout;
    QVBoxLayout *m_vLayout;
};

#endif // ZLINKROLESELECTDIA_H
