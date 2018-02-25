#ifndef ZLISTPROCESSINFODIA_H
#define ZLISTPROCESSINFODIA_H

#include "NetProtocol/pnetframe.h"
#include "BasePart/zbaseinfodia.h"
#include <QToolButton>
class ZListProcessInfoDia : public ZBaseInfoDia
{
public:
    ZListProcessInfoDia(QWidget *parent=0);
    ~ZListProcessInfoDia();
    void ZExecuteListOp();
    void ZParseAckNetFrmXmlData();
private:
    QLabel *m_llMsg;
    QToolButton *m_tbOkay;
    QVBoxLayout *m_vLayout;
};

#endif // ZLISTPROCESSINFODIA_H
