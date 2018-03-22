#ifndef PNETPRO_H
#define PNETPRO_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QList>
class PNetPro : public QObject
{
    Q_OBJECT
public:
    explicit PNetPro(QObject *parent = 0);
    QString ZParseNetFrmXmlData(QString xmlData,QSqlDatabase db);
    QString ZGetLoginUserName();

public:
    typedef enum
    {
        ProType_Unknown=0,
        ProType_Heart_Beat,
        ProType_Update_Get,

        ProType_Login_Login,
        ProType_Login_Logout,

        ProType_Role_Add,
        ProType_Role_Mdy,
        ProType_Role_Del,

        ProType_User_Add,
        ProType_User_Mdy,
        ProType_User_Del,

        ProType_Folder_Add,
        ProType_Folder_Del,
        ProType_Folder_List,

        ProType_File_Add,
        ProType_File_UpData,
        ProType_File_Del,
        ProType_File_Get,
        ProType_File_DwnData,

        ProType_Template_Add,
        ProType_Template_Del,
        ProType_Template_Get,
        ProType_Template_List,
        ProType_Template_Save,
        ProType_Template_Bind,
        ProType_Template_Unbind,

        ProType_VarSource_Add,
        ProType_VarSource_Del,
        ProType_VarSource_Get,
        ProType_VarSource_Save,


        ProType_Process_Add,
        ProType_Process_Del,
        ProType_Process_Get,
        ProType_Process_Save,
        ProType_Process_List,

        ProType_Task_ListNew,
        ProType_Task_Add,
        ProType_Task_List,
        ProType_Task_Get,
        ProType_Task_Del,
        ProType_Task_Save,
        ProType_Task_Submit,
        ProType_Task_Withdraw,
        ProType_Task_CheckOkay,
        ProType_Task_CheckFailed,
        ProType_Task_Archieve,
        ProType_Task_Find,

        ProType_Form_Add,
        ProType_Form_Del,
        ProType_Form_Save,
        ProType_Form_Get,
        ProType_Form_List,

        ProType_Backup_List,
        ProType_Backup_Backup,
        ProType_Backup_Restore,
        ProType_Backup_Delete,
    }PNetProType;
    PNetProType ZGetNetProType();
    //for get file.
signals:
    void ZSignalOpLog(QString logMsg);
    void ZSignalHeartBeat(QString userName);
    void ZSignalUserLogin(QString userName);
    void ZSignalUserLogout(QString userName);
public slots:

private:
    QString m_loginUserName;
    PNetProType m_proType;
};

#endif // PNETPRO_H
