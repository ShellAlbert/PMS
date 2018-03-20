#ifndef PGBLPARA_H
#define PGBLPARA_H
#include <QString>
#include <QStringList>
#include <QSettings>
#include <QDir>
#include <QDialog>
#include <QKeyEvent>
#include <QTableWidget>

//icon size of main window top bar.
#define TOPBAR_ICON_W   32
#define TOPBAR_ICON_H   32

//UserManager permBits.
#define PermBits_UserManager_AddGrp (0x1<<0)
#define PermBits_UserManager_MdyGrp (0x1<<1)
#define PermBits_UserManager_DelGrp (0x1<<2)

#define PermBits_UserManager_AddUser (0x1<<3)
#define PermBits_UserManager_MdyUser (0x1<<4)
#define PermBits_UserManager_DelUser (0x1<<5)

#define PermBits_UserManager_Import (0x1<<6)
#define PermBits_UserManager_Export (0x1<<7)

//TemplateEditor permBits.
#define PermBits_TemplateEditor_AddTemplate     (0x1<<0)
#define PermBits_TemplateEditor_MdyTemplate     (0x1<<1)
#define PermBits_TemplateEditor_DelTemplate     (0x1<<2)

#define PermBits_TemplateEditor_AddVarSrc       (0x1<<3)
#define PermBits_TemplateEditor_MdyVarSrc       (0x1<<4)
#define PermBits_TemplateEditor_DelVarSrc       (0x1<<5)

#define PermBits_TemplateEditor_Import          (0x1<<6)
#define PermBits_TemplateEditor_Export          (0x1<<7)

//FileManager permBits.
#define PermBits_FileManager_NewFolder      (0x1<<0)
#define PermBits_FileManager_DelFolder      (0x1<<1)

#define PermBits_FileManager_UploadFile     (0x1<<2)
#define PermBits_FileManager_DownloadFile   (0x1<<3)
#define PermBits_FileManager_DelFile        (0x1<<4)

//ProcessEditor permBits.
#define PermBits_ProcessEditor_NewProcess      (0x1<<0)
#define PermBits_ProcessEditor_MdyProcess      (0x1<<1)
#define PermBits_ProcessEditor_DelProcess      (0x1<<2)

//TaskManager permBits.
#define PermBits_TaskManager_NewTask      (0x1<<0)
#define PermBits_TaskManager_MdyTask      (0x1<<1)
#define PermBits_TaskManager_DelTask      (0x1<<2)

//FormDesigner permBits.
#define PermBits_FormDesigner_NewForm      (0x1<<0)
#define PermBits_FormDesigner_MdyForm      (0x1<<1)
#define PermBits_FormDesigner_DelForm      (0x1<<2)

//task type.
#define Task_Type_All           0
#define Task_Type_New           1
#define Task_Type_Save          2
#define Task_Type_Submit        3
#define Task_Type_Check_Okay    4
#define Task_Type_Check_Failed  5
#define Task_Type_Archieve      6
#define Task_Type_Need_My_Check     7
#define Task_Type_My_Check_Okay     8
#define Task_Type_My_Check_Failed   9
extern QString ZGetTaskStateString(qint32 type);
extern QString ZGetTaskStateIconName(qint32 type);

class ZRoleInfo
{
public:
    QString m_roleName;
    qint32 m_userManagerPerm;
    qint32 m_templateEditPerm;
    qint32 m_fileManagerPerm;
    qint32 m_processEditPerm;
    qint32 m_taskManagerPerm;
    qint32 m_formDesignerPerm;
    QString m_roleMemo;
};
class ZUserInfo
{
public:
    QString m_userName;
    QString m_roleName;
    QString m_realName;
    QString m_password;
    QString m_sex;
    QString m_mobile;
    QString m_Creator;
    QString m_CreateTime;
};

class MyUserInfo
{
private:
    MyUserInfo()
    {
        this->m_bOnLine=false;
        this->m_bCheckNewVersion=true;
        this->m_bExitFlag=false;
        this->m_bPNetProtocolExitFlag=false;
        this->m_bPNetTimeoutExitFlag=false;
    }
    static MyUserInfo* m_pInstance;
public:
    static MyUserInfo* ZGetInstance()
    {
        if(m_pInstance==NULL)
        {
            m_pInstance=new MyUserInfo();
        }
        return m_pInstance;
    }
    void ZLoadIniFile()
    {
        //read ini file.
        QSettings iniFile(QDir::currentPath()+"/PMS.ini",QSettings::IniFormat);
        iniFile.beginGroup("Server");
        this->m_appVersion=QString("3.0.0");
        this->m_PMSIp=iniFile.value("IP","127.0.0.1").toString();
        this->m_PMSPort=iniFile.value("Port",6800).toInt();
        iniFile.endGroup();

        iniFile.beginGroup("PDF");
        this->m_pdfViewType=iniFile.value("ViewType","inner").toString();
        this->m_outPdfViewer=iniFile.value("OutViewer","C:\\Foxit\\pdfview.exe").toString();
        iniFile.endGroup();
    }
    QString m_appVersion;
    QString m_onLine;
    qreal m_bOnLine;

    ZRoleInfo m_RoleInfo;
    ZUserInfo m_UserInfo;
    //pms server information.
    QString m_PMSIp;
    qint32 m_PMSPort;

    QString m_pdfViewType;
    QString m_outPdfViewer;

public:
    bool m_bCheckNewVersion;

public:
    bool m_bExitFlag;
    bool m_bPNetProtocolExitFlag;
    bool m_bPNetTimeoutExitFlag;
};

extern int QBytes2Int(QByteArray bytes);
extern QByteArray Int2QByte(int number);

class ZAckNetFrmWidget
{
public:
    virtual void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
};

extern qint32 ZGetQTableWidgetHtml(QString title,QString note,QTableWidget *table,QString *html);
extern qint32 ZGetQTableWidgetPdf(QString title,QString note,QTableWidget *table,QString *html);
#endif // PGBLPARA_H
