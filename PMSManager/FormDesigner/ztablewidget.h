#ifndef ZTABLEWIDGET_H
#define ZTABLEWIDGET_H

#include <QTableWidget>
#include <FormDesigner/zbasewidget.h>
#include <BasePart/zbaseinfodia.h>
#include <QTreeWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
class ZTableDialog:public ZBaseInfoDia
{
Q_OBJECT
public:
    ZTableDialog(QWidget *parent=0);
    ~ZTableDialog();
private:
    QTreeWidget *m_tree;
    QToolButton *m_tbAddCol;
    QToolButton *m_tbMdyCol;
    QToolButton *m_tbDelCol;
    QToolButton *m_tbOkayCol;
    QToolButton *m_tbCancelCol;
    QHBoxLayout *m_hLayout;
    QVBoxLayout *m_vLayout;
};
class ZTableWidget:public ZBaseWidget
{
    Q_OBJECT
public:
    ZTableWidget();
    ~ZTableWidget();
    void ZOpenAttributeDialog();
public:
    QTableWidget *m_tableWidget;
};
#endif // ZTABLEWIDGET_H
