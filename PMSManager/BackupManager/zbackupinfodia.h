#ifndef ZBACKUPINFODIA_H
#define ZBACKUPINFODIA_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QToolButton>
#include <QGridLayout>
#include "NetProtocol/pnetframe.h"
#include "BasePart/zbaseinfodia.h"
class ZBackupInfoDia : public ZBaseInfoDia
{
    Q_OBJECT
public:
    typedef enum{
        Type_Backup=0,
        Type_Restore=1,
        Type_Delete=2,
    }BackupInfoDiaType;

    ZBackupInfoDia(BackupInfoDiaType type,QWidget *parent=0);
    ~ZBackupInfoDia();

    QString ZGetBackupName();
    void ZSetBackupName(QString name);

    void ZParseAckNetFrmXmlData();
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
private:

    QLabel *m_llBackupName;
    QLineEdit *m_leBackupName;

    QToolButton *m_btnOkay;
    QToolButton *m_btnCancel;

    QGridLayout *m_gridLayout;

    BackupInfoDiaType m_diaType;
};
#endif // ZBACKUPINFODIA_H
