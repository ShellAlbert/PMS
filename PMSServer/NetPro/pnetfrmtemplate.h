#ifndef PNETFRMTEMPLATE_H
#define PNETFRMTEMPLATE_H

#include <QString>
#include <NetPro/pnetfrm.h>
class PNetFrmTemplate : public PNetFrm
{
public:
    PNetFrmTemplate(QSqlDatabase db);
    void ZAddTemplate(QString templateName,QString creator);
    void ZDelTemplate(QString templateName,QString creator);
    void ZGetTemplate(QString templateName,QString creator);
    void ZSaveTemplate(QString templateName,QString templateXmlData,QString creator);
    void ZBindVarSource(QString templateName,QString varSourceName,QString creator);
    void ZUnbindVarSource(QString templateName,QString varSourceName,QString creator);
    void ZListTemplate(QString creator);
};

#endif // PNETFRMTEMPLATE_H
