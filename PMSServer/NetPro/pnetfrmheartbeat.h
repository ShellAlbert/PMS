#ifndef PNETFRMHEARTBEAT_H
#define PNETFRMHEARTBEAT_H

#include <QString>
#include <NetPro/pnetfrm.h>
class PNetFrmHeartBeat : public PNetFrm
{
public:
    PNetFrmHeartBeat(QSqlDatabase db);
    qint32 ZHeartBeat(QString userName);
};

#endif // PNETFRMHEARTBEAT_H
