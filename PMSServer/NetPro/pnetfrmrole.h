#ifndef PNETFRMROLE_H
#define PNETFRMROLE_H

#include <QString>
#include <NetPro/pnetfrm.h>
class PNetFrmRole:public PNetFrm
{
public:
    PNetFrmRole(QSqlDatabase db);
    void ZAddRole(QString roleName,QString permBits,QString roleMemo,QString creator);
    void ZMdyRole(QString roleName,QString permBits,QString roleMemo,QString creator);
    void ZDelRole(QString roleName);
    void ZListRole(QString creator);
};

#endif // PNETFRMROLE_H
