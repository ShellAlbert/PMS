#ifndef ZADVANCEDFINDDIALOG_H
#define ZADVANCEDFINDDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QToolButton>
#include <QDateTimeEdit>
#include <QTreeWidget>
#include <QGroupBox>
#include "pgblpara.h"
class ZAdvancedFindDialog : public QDialog,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    ZAdvancedFindDialog();
    ~ZAdvancedFindDialog();

    void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
protected:
    QSize sizeHint() const;
private slots:
    void ZSlotFind();
    void ZSlotPopupMenu(const QPoint &pt);
    void ZSlotLoadPresetValues();
private:
    QGroupBox *m_grpBox;
    QGridLayout *m_gLayout;
    QCheckBox *m_checkMachineNo;
    QComboBox *m_cbMachineNo;

    QCheckBox *m_checkClass;
    QComboBox *m_cbClass;

    QCheckBox *m_checkOrderNo;
    QComboBox *m_cbOrderNo;

    QCheckBox *m_checkProductNo;
    QComboBox *m_cbProductNo;

    QCheckBox *m_checkStartEndTime;
    QDateTimeEdit *m_deStart;
    QDateTimeEdit *m_deEnd;

    QToolButton *m_tbFind;

    QTreeWidget *m_tree;
    QVBoxLayout *m_vLayout;
};

#endif // ZADVANCEDFINDDIALOG_H
