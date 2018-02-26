#ifndef PNETFRMUSER_H
#define PNETFRMUSER_H

#include <QString>
#include <NetPro/pnetfrm.h>
class PNetFrmUser:public PNetFrm
{
public:
    PNetFrmUser(QSqlDatabase db);
    void ZAddUser(QString userName,QString password,QString roleName,QString realName,QString sex,QString mobile,QString creator);
    void ZMdyUser(QString userName,QString password,QString roleName,QString realName,QString sex,QString mobile,QString creator);
    void ZDelUser(QString userName,QString roleName);
};

#endif // PNETFRMUSER_H
