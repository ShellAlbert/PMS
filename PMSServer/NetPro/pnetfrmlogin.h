#ifndef PNETFRMLOGIN_H
#define PNETFRMLOGIN_H

#include <QString>
#include <NetPro/pnetfrm.h>
class PNetFrmLogin : public PNetFrm
{
public:
    PNetFrmLogin(QSqlDatabase db);
    qint32 ZLogin(QString userName,QString password);
    qint32 ZLogout(QString userName);
};

#endif // PNETFRMLOGIN_H
