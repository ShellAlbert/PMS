#ifndef PNETFRMFILE_H
#define PNETFRMFILE_H

#include <QString>
#include <NetPro/pnetfrm.h>
class PNetFrmFile : public PNetFrm
{
public:
    PNetFrmFile(QSqlDatabase db);
    void ZAddFile(QString folderName,QString fileName,QString fileType,qint32 fileSize,QString creator);
    void ZAddData(QString folderName,QString fileName,QString fileData,QString totalBlock,QString currentBlock,QString creator);
    void ZDelFile(QString folderName,QString fileName,QString creator);
    void ZGetFile(QString folderName,QString fileName,QString creator);
    void ZGetData(QString folderName,QString fileName,QString totalBlock,QString currentBlock,qint32 readPos,qint32 readSize,QString creator);
};
class PNetFrmUpdate:public PNetFrm
{
public:
    PNetFrmUpdate(QSqlDatabase db);
    void ZGetNewVersion(QString totalBlock,QString currentBlock,qint32 readPos,qint32 readSize);
};
#endif // PNETFRMFILE_H
