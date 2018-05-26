#ifndef ZDATACOMPAREDIALOG_H
#define ZDATACOMPAREDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
class ZMinMaxCompareDialog : public QDialog
{
    Q_OBJECT
public:
    ZMinMaxCompareDialog(QWidget *parent=NULL);
    ~ZMinMaxCompareDialog();

    QStringList ZGetDestMinMaxPair();
    void ZSetDestMinMaxPair(QStringList pair);
signals:
    void ZSigHighlightCell(QString destCell,QString minCell,QString maxCell);
private slots:
    void ZSlotAdd();
    void ZSlotDel();
    void ZSlotOkay();
    void ZSlotCancel();
    void ZSlotDoubleClicked(QModelIndex index);
private:
    QTreeWidget *m_tree;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDel;
    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayout;
    QVBoxLayout *m_vLayout;
};
class ZMinMaxAddDia:public QDialog
{
    Q_OBJECT
public:
    ZMinMaxAddDia(QWidget *parent=NULL);
    ~ZMinMaxAddDia();

    QString ZGetDestXY();
    QString ZGetMinXY();
    QString ZGetMaxXY();
private slots:
    void ZSlotOkay();
    void ZSlotCancel();

private:
    QLabel *m_llDestCell;
    QLineEdit *m_leDestCell;

    QLabel *m_llMinCell;
    QLineEdit *m_leMinCell;

    QLabel *m_llMaxCell;
    QLineEdit *m_leMaxCell;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;

    QGridLayout *m_gLayout;
};
#endif // ZDATACOMPAREDIALOG_H
