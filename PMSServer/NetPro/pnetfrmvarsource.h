#ifndef PNETFRMVARSOURCE_H
#define PNETFRMVARSOURCE_H

#include <QString>
#include <NetPro/pnetfrm.h>
class PNetFrmVarSource : public PNetFrm
{
public:
    PNetFrmVarSource(QSqlDatabase db);
    void ZAddVarSource(QString name,QString creator);
    void ZDelVarSource(QString name,QString creator);
    void ZSaveVarSource(QString name,QString xmlData,QString creator);
    void ZGetVarSource(QString name,QString creator);
};

#endif // PNETFRMVARSOURCE_H
