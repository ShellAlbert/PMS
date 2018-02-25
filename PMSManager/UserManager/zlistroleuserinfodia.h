#ifndef ZLISTROLEUSERINFODIA_H
#define ZLISTROLEUSERINFODIA_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextEdit>
#include <QToolButton>
#include "NetProtocol/pnetframe.h"
#include "BasePart/zbaseinfodia.h"
class ZListRoleUserInfoDia : public ZBaseInfoDia
{
public:
    ZListRoleUserInfoDia(QWidget *parent=0);
    ~ZListRoleUserInfoDia();
    void ZExecuteListOp();
    void ZParseAckNetFrmXmlData();

private:
    QLabel *m_llMsg;
    QToolButton *m_tbOkay;
    QVBoxLayout *m_vLayout;
};

#endif // ZLISTROLEUSERINFODIA_H
