#ifndef ZLISTTEMPLATEINFODIA_H
#define ZLISTTEMPLATEINFODIA_H

#include "NetProtocol/pnetframe.h"
#include "BasePart/zbaseinfodia.h"
#include <QToolButton>
class ZListTemplateVarSourceInfoDia : public ZBaseInfoDia
{
public:
    ZListTemplateVarSourceInfoDia(QWidget *parent=0);
    ~ZListTemplateVarSourceInfoDia();
    void ZExecuteListOp();
    void ZParseAckNetFrmXmlData();
private:
    QLabel *m_llMsg;
    QToolButton *m_tbOkay;
    QVBoxLayout *m_vLayout;
};

#endif // ZLISTTEMPLATEINFODIA_H
