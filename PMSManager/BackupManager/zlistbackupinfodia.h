#ifndef ZLISTBACKUPINFODIA_H
#define ZLISTBACKUPINFODIA_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextEdit>
#include <QToolButton>
#include "NetProtocol/pnetframe.h"
#include "BasePart/zbaseinfodia.h"
class ZListBackupInfoDia : public ZBaseInfoDia
{
public:
    ZListBackupInfoDia(QWidget *parent=0);
    ~ZListBackupInfoDia();
    void ZExecuteListOp();
    void ZParseAckNetFrmXmlData();

private:
    QLabel *m_llMsg;
    QToolButton *m_tbOkay;
    QVBoxLayout *m_vLayout;
};
#endif // ZLISTBACKUPINFODIA_H
