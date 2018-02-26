#include "pnetfrm.h"

PNetFrm::PNetFrm(QSqlDatabase db)
{
    this->m_db=db;
}
QString PNetFrm::ZGetOpLogMsg()
{
    return this->m_opLogMsg;
}
QString PNetFrm::ZGetAckNetFrmXmlData()
{
    return this->m_ackNetFrmXmlData;
}
