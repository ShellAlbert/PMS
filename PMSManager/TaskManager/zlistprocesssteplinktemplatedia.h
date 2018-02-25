#ifndef ZLISTPROCESSSTEPLINKTEMPLATEDIA_H
#define ZLISTPROCESSSTEPLINKTEMPLATEDIA_H

#include "NetProtocol/pnetframe.h"
#include "BasePart/zbaseinfodia.h"
#include <QToolButton>
class ZListProcessStepLinkTemplateDia : public ZBaseInfoDia
{
public:
    ZListProcessStepLinkTemplateDia(QWidget *parent=0);
    ~ZListProcessStepLinkTemplateDia();
    void ZExecuteListOp();
    void ZParseAckNetFrmXmlData();
private:
    QLabel *m_llMsg;
    QToolButton *m_tbOkay;
    QVBoxLayout *m_vLayout;
};

#endif // ZLISTPROCESSSTEPLINKTEMPLATEDIA_H
