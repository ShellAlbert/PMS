#ifndef ZLINKFILESELECTDIA_H
#define ZLINKFILESELECTDIA_H

#include <QDialog>
#include <QToolButton>
#include <QLabel>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "pgblpara.h"
class ZLinkFileSelectDia : public QDialog,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    ZLinkFileSelectDia(QWidget *parent=0);
    ~ZLinkFileSelectDia();

    void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
    QStringList ZGetSelectedFileList();
protected:
    QSize sizeHint() const;
private:
    QTreeWidget *m_tree;
    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayout;
    QVBoxLayout *m_vLayout;
};

#endif // ZLINKFILESELECTDIA_H
