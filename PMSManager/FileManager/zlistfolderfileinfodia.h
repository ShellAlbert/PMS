#ifndef ZLISTFOLDERFILEINFODIA_H
#define ZLISTFOLDERFILEINFODIA_H

#include "NetProtocol/pnetframe.h"
#include "BasePart/zbaseinfodia.h"
#include <QToolButton>
class ZListFolderFileInfoDia : public ZBaseInfoDia
{
public:
    ZListFolderFileInfoDia(QWidget *parent=0);
    ~ZListFolderFileInfoDia();
    void ZExecuteListOp();
    void ZParseAckNetFrmXmlData();
private:
    QLabel *m_llMsg;
    QToolButton *m_tbOkay;
    QVBoxLayout *m_vLayout;
};

#endif // ZLISTFOLDERFILEINFODIA_H
