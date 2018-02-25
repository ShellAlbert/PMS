#ifndef ZPROCESSSTEPLINKTEMPLATESELECTDIA_H
#define ZPROCESSSTEPLINKTEMPLATESELECTDIA_H

#include <QDialog>
#include <QTreeWidget>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "pgblpara.h"
class ZProcessStepLinkTemplateSelectDia : public QDialog,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    ZProcessStepLinkTemplateSelectDia(QWidget *parent=0);
    ~ZProcessStepLinkTemplateSelectDia();

    void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
    QString ZGetSelectedTemplate();
    QString ZGetSelectedProcess();
    QString ZGetSelectedStep();
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
protected:
    QSize sizeHint() const;
private:
    QTreeWidget *m_tree;
    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayout;
    QVBoxLayout *m_vLayout;
};

#endif // ZPROCESSSTEPLINKTEMPLATESELECTDIA_H
