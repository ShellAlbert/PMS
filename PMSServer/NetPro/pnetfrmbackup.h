#ifndef PNETFRMBACKUP_H
#define PNETFRMBACKUP_H

#include <QString>
#include <NetPro/pnetfrm.h>
class PNetFrmBackup : public PNetFrm
{
public:
    PNetFrmBackup(QSqlDatabase db);
    void ZListBackup();
    void ZDoBackup(QString creator);
    void ZDoRestore(QString backupName);
    void ZDoDelete(QString backupName);

private:
    QString ZGetFileSystemDataSize(void);
    QString ZGetDatabaseDataSize(void);
};

#endif // PNETFRMBACKUP_H
