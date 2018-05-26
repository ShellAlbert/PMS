#ifndef ZVARINFODIA_H
#define ZVARINFODIA_H

#include <QDialog>
#include <QLabel>
#include <QTreeWidget>
#include <QToolButton>
#include <QGridLayout>
class ZVarSourceInfo
{
public:
    QString m_varName;//变量名称
    QString m_varType;//数据类型
    QString m_rule; //规则
    QString m_refValue;//参考值
    QString m_cell;//绑定单元格
    QString m_varDesc;//变量描述信息
};
class ZVarInfoDia : public QDialog
{
    Q_OBJECT
public:
    ZVarInfoDia(QString varSourceName,QWidget *parent=0);
    ~ZVarInfoDia();

    void ZSetXmlData(QString xmlData);
    QString ZGetXmlData();
protected:
    QSize sizeHint() const;
private slots:
    void ZSlotAddGeneralVar();
    void ZSlotDelGeneralVar();

    void ZSlotAddAutoVar();
    void ZSlotDelAutoVar();

    void ZSlotImport();
    void ZSlotOkay();
    void ZSlotCancel();
private:
    QLabel *m_llGeneralVar;
    QToolButton *m_tbAddGeVar;
    QToolButton *m_tbDelGeVar;
    QTreeWidget *m_treeGeVar;

    QLabel *m_llAutoVar;
    QToolButton *m_tbAddAutoVar;
    QToolButton *m_tbDelAutoVar;
    QTreeWidget *m_treeAutoVar;

    QToolButton *m_tbImport;
    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;

    QHBoxLayout *m_hLayoutGeVar;
    QHBoxLayout *m_hLayoutAutoVar;
    QHBoxLayout *m_hLayoutBtn;
    QVBoxLayout *m_vLayoutMain;
private:
    QString m_varSourceName;
};

#endif // ZVARINFODIA_H
