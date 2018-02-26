#ifndef PNETFRMFOLDER_H
#define PNETFRMFOLDER_H

#include <QString>
#include <NetPro/pnetfrm.h>
class PNetFrmFolder : public PNetFrm
{
public:
    PNetFrmFolder(QSqlDatabase db);
    void ZAddFolder(QString folderName,QString creator);
    void ZDelFolder(QString folderName,QString creator);
    void ZListFolder(QString creator);
};

#endif // PNETFRMFOLDER_H
