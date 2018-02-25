#ifndef ZIMPORTROLEUSERINFODIA_H
#define ZIMPORTROLEUSERINFODIA_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextEdit>
#include <QToolButton>
#include "NetProtocol/pnetframe.h"
#include "BasePart/zbaseinfodia.h"
class ZImportRoleUserInfoDia : public ZBaseInfoDia
{
public:
    ZImportRoleUserInfoDia(QWidget *parent=0);
    ~ZImportRoleUserInfoDia();
    void ZExecuteImportOp(QList<ZRoleInfo> roleList,QList<ZUserInfo> userList);
    void ZParseAckNetFrmXmlData();
private:
    QLabel *m_llMsg;
    QToolButton *m_tbOkay;
    QVBoxLayout *m_vLayout;
};

#endif // ZIMPORTROLEUSERINFODIA_H
