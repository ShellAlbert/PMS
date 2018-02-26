#ifndef PNETFRM_H
#define PNETFRM_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QVariant>
#include <QDateTime>
class PNetFrm
{
public:
    PNetFrm(QSqlDatabase db);
    //operation log message.
    QString ZGetOpLogMsg();
    QString m_opLogMsg;

    //ackNetFrmXmlData.
    QString ZGetAckNetFrmXmlData();
    QString m_ackNetFrmXmlData;

    //database.
    QSqlDatabase m_db;
};

#endif // PNETFRM_H
