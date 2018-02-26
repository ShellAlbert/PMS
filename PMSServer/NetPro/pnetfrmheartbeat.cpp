#include "pnetfrmheartbeat.h"
#include <QXmlStreamWriter>
#include "pgblpara.h"
PNetFrmHeartBeat::PNetFrmHeartBeat(QSqlDatabase db):PNetFrm(db)
{

}
qint32 PNetFrmHeartBeat::ZHeartBeat(QString userName)
{
    qint32 nWaitCheck=0;
    qint32 nSubmit=0;
    qint32 nCheckFailed=0;
    QSqlQuery query(this->m_db);
    query.prepare("SELECT * FROM `pms`.`TaskInfo` WHERE `Checker`=:Checker AND `TaskState`=3");
    query.bindValue(":Checker",userName);
    if(query.exec())
    {
        nWaitCheck=query.size();
    }
    QSqlQuery query2(this->m_db);
    query2.prepare("SELECT * FROM `pms`.`TaskInfo` WHERE `Creator`=:Creator AND `TaskState`=3");
    query2.bindValue(":Creator",userName);
    if(query2.exec())
    {
        nSubmit=query2.size();
    }
    QSqlQuery query3(this->m_db);
    query3.prepare("SELECT * FROM `pms`.`TaskInfo` WHERE `Creator`=:Creator AND `TaskState`=5");
    query3.bindValue(":Creator",userName);
    if(query3.exec())
    {
        nCheckFailed=query3.size();
    }

    QXmlStreamWriter  tXmlWriter(&this->m_ackNetFrmXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("Heart"));
    tXmlWriter.writeStartElement(QString("Heart"));
    tXmlWriter.writeAttribute(QString("cmd"),QString("beat"));
    tXmlWriter.writeAttribute(QString("retCode"),QString("0"));
    tXmlWriter.writeAttribute(QString("waitCheck"),QString("%1").arg(nWaitCheck));
    tXmlWriter.writeAttribute(QString("submit"),QString("%1").arg(nSubmit));
    tXmlWriter.writeAttribute(QString("checkFailed"),QString("%1").arg(nCheckFailed));
    tXmlWriter.writeAttribute(QString("newVersion"),PGblPara::ZGetInstance()->m_newVersionNo);
    tXmlWriter.writeAttribute(QString("totalBlock"),QString("%1").arg(PGblPara::ZGetInstance()->m_totalBlock));
    tXmlWriter.writeAttribute(QString("blockSize"),QString("%1").arg(PGblPara::ZGetInstance()->m_blockSize));
    tXmlWriter.writeAttribute(QString("remainBytes"),QString("%1").arg(PGblPara::ZGetInstance()->m_remainBytes));
    tXmlWriter.writeCharacters(userName);
    tXmlWriter.writeEndElement();//Heart.
    tXmlWriter.writeEndElement();//NetPro.
    tXmlWriter.writeEndDocument();
    return 0;
}
