#ifndef PNETFRMFORM_H
#define PNETFRMFORM_H

#include <QString>
#include <NetPro/pnetfrm.h>
class PNetFrmForm : public PNetFrm
{
public:
    PNetFrmForm(QSqlDatabase db);
    void ZNewForm(QString formName,QString creator);
    void ZDelForm(QString formName,QString creator);
    void ZGetForm(QString formName,QString creator);
    void ZSaveForm(QString formName,QString xmlData,QString creator);
    void ZListForm(QString creator);
};

#endif // PNETFRMFORM_H
