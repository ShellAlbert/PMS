#ifndef ZLINKTEMPLATESELECTDIA_H
#define ZLINKTEMPLATESELECTDIA_H

#include <QDialog>
#include <QToolButton>
#include <QLabel>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "pgblpara.h"
class ZLinkTemplateSelectDia : public QDialog,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    ZLinkTemplateSelectDia(QWidget *parent=0);
    ~ZLinkTemplateSelectDia();

    void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
    QStringList ZGetSelectedTemplateList();
protected:
    QSize sizeHint() const;
private:
    QTreeWidget *m_tree;
    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayout;
    QVBoxLayout *m_vLayout;
};

#endif // ZLINKTEMPLATESELECTDIA_H
