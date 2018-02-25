#ifndef ZCOMBOBOXDIA_H
#define ZCOMBOBOXDIA_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QListWidget>
#include <QGridLayout>
class ZComboBoxDia : public QDialog
{
    Q_OBJECT
public:
    ZComboBoxDia(QWidget *parent=0);
    ~ZComboBoxDia();

    QStringList ZGetValueList();
    void ZSetValueList(QStringList valueList);
protected slots:
    void ZSlotAdd();
    void ZSlotDel();
    void ZSlotOkay();
    void ZSlotCancel();

private:
    QLabel *m_llAddValue;
    QLineEdit *m_leAddValue;
    QToolButton *m_tbAdd;
    QToolButton *m_tbDel;

    QListWidget *m_listWidget;
    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QGridLayout *m_gridLayout;
};

#endif // ZCOMBOBOXDIA_H
