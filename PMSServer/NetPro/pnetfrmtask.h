#ifndef PNETFRMTASK_H
#define PNETFRMTASK_H

#include <QString>
#include <NetPro/pnetfrm.h>
#define Task_Type_All           0
#define Task_Type_New           1
#define Task_Type_Save          2
#define Task_Type_Submit        3
#define Task_Type_Check_Okay    4
#define Task_Type_Check_Failed  5
#define Task_Type_Archieve      6
class PNetFrmTask : public PNetFrm
{
public:
    PNetFrmTask(QSqlDatabase db);
    void ZListNewTask(QString roleName);
    void ZListTask(QString creator,qint32 taskState);
    void ZAddTask(QString taskName,QString refTemplate,QString refProcess,QString refStep,QString creator,QString checker);
    void ZOpenTask(QString taskName,QString refTemplate);
    void ZSaveTask(QString taskName,QString refTemplate,QString taskValueXmlData,QStringList auxData);
    void ZDelTask(QString taskName,QString refTemplate);
    void ZSubmitTask(QString taskName,QString refTemplate);
    void ZWithdrawTask(QString taskName,QString refTemplate);
    void ZCheckOkayTask(QString taskName,QString refTemplate);
    void ZCheckFailedTask(QString taskName,QString refTemplate);
    void ZArchieveTask(QString taskName,QString refTemplate);
};

#endif // PNETFRMTASK_H
