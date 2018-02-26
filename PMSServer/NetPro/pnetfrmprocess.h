#ifndef PNETFRMPROCESS_H
#define PNETFRMPROCESS_H

#include <QString>
#include <NetPro/pnetfrm.h>
class PNetFrmProcess : public PNetFrm
{
public:
    PNetFrmProcess(QSqlDatabase db);
    void ZAddProcess(QString processName,QString creator);
    void ZDelProcess(QString processName,QString creator);
    void ZGetProcess(QString processName,QString creator);
    void ZSaveProcess(QString processName,qint32 stepNum,QString xmlData,QString creator);
    void ZListProcess(QString creator);
};

#endif // PNETFRMPROCESS_H
