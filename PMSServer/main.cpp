#include "pmainwin.h"
#include <QApplication>
#include <TcpServer/ptcpserver.h>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextCodec>
#include <QDir>
#include <AES/TAesClass.h>
#include "pgblpara.h"
#include <QDateTime>
#include <QMutex>
#include <QTextStream>
#include <iostream>
QMutex gMutexLogFile;
void gDumpLog2File(QtMsgType type,const QMessageLogContext &context,const QString &msg)
{
    Q_UNUSED(context);

    gMutexLogFile.lock();
    bool bAbort2Exit=false;
    QString logString;
    switch(type)
    {
    case QtDebugMsg://dump to console.
        std::cout<<"<Debug>:"<<msg.toStdString()<<endl;
        break;
    case QtWarningMsg://dump to file.
        logString="<"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+">,"+msg;
        break;
    case QtCriticalMsg:
        logString=QString("<Critical>:%1").arg(msg);
        break;
    case QtFatalMsg:
        logString=QString("<Fatal>:%1").arg(msg);
        bAbort2Exit=true;
        break;
    case QtInfoMsg:
        logString=QString("<Info>:%1").arg(msg);
        break;
    default:
        break;
    }
    if(!logString.isEmpty())
    {
        QString logFileName;
        logFileName+=QDir::currentPath()+"/log/PMS-";
        logFileName+=QDateTime::currentDateTime().toString("yyyy-MM-dd");
        logFileName+=".log";
        QFile logFile(logFileName);
        if(logFile.open(QIODevice::WriteOnly|QIODevice::Append))
        {
            QTextStream ts(&logFile);
            ts<<logString<<endl;
        }
        logFile.close();
    }
    //abort when fatal error occured.
    if(bAbort2Exit)
    {
        abort();
    }
    gMutexLogFile.unlock();
}
//type:0,encrypt,1:decrypt.
QString AesEncryptBase64(int type,char *inData,int inDataSize)
{
    QString AesProcessedData;
    UCHAR AesKey[]="iloveyantai";
    char buffer[1024];

    TAesClass aesObj;
    aesObj.InitializePrivateKey(16,AesKey);
    memset(buffer,0,sizeof(buffer));
    if(!type)
    {
        if(aesObj.OnAesEncrypt(inData,inDataSize,buffer)>0)
        {
            //encrypt okay.
            AesProcessedData=QString(QString(buffer).toUtf8().toBase64());
        }else{
            //encrypt failed.
            AesProcessedData=QString(QString(inData).toUtf8().toBase64());
        }
    }else{
        if(aesObj.OnAesUncrypt(inData,inDataSize,buffer)>0)
        {
            //decrypt okay.
            AesProcessedData=QString(QString(buffer).toUtf8().toBase64());
        }else{
            //decrypt failed.
            AesProcessedData=QString(QString(inData).toUtf8().toBase64());
        }
    }
    return AesProcessedData;
}
int main(int argc, char *argv[])
{

    //    QString data("12345678");
    //    QByteArray baData=data.toLatin1();
    //    QString dd=AesEncryptBase64(0,baData.data(),baData.size());
    //    qDebug()<<dd.size()<<dd;
    //    baData=QByteArray::fromBase64(dd.toLatin1());
    //    QString ff=AesEncryptBase64(1,baData.data(),baData.size());
    //    qDebug()<<ff.size()<<ff;
    //    return 0;

    QApplication app(argc, argv);

    //check its ftp base dir is exist or not.
    QString dataDir=QDir::currentPath()+"/data";
    QString updateDir=QDir::currentPath()+"/update";
    QString logDir=QDir::currentPath()+"/log";
    QDir dir;
    if(!QDir(dataDir).exists())
    {
        dir.mkpath(dataDir);
    }
    if(!QDir(updateDir).exists())
    {
        dir.mkpath(updateDir);
    }
    if(!QDir(logDir).exists())
    {
        dir.mkpath(logDir);
    }

    //dump critical msg to file.
    //qInstallMessageHandler(gDumpLog2File);

    qDebug()<<"PMS Server "<<PMSSERVER_VERSION<<" build on "<<QString(__DATE__)<<QString(__TIME__);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    //load config file.
    qDebug()<<"loading config file...";
    PGblPara::ZGetInstance()->ZLoadCfgFile();

    //mysql info.
    qDebug()<<"MySQL Server ["<<PGblPara::ZGetInstance()->m_mysqlIP<<":"<<PGblPara::ZGetInstance()->m_mysqlPort<<"],USER:"<<PGblPara::ZGetInstance()->m_mysqlUser;
    //try to connect mysql.
    QSqlDatabase testDB=QSqlDatabase::addDatabase("QMYSQL");
    testDB.setHostName(PGblPara::ZGetInstance()->m_mysqlIP);
    testDB.setPort(PGblPara::ZGetInstance()->m_mysqlPort.toInt());
    testDB.setUserName(PGblPara::ZGetInstance()->m_mysqlUser);
    testDB.setPassword(PGblPara::ZGetInstance()->m_mysqlPass);
    testDB.setDatabaseName("mysql");
    if(testDB.open())
    {
        qDebug()<<"test connection to MySQL okay.";
    }else{
        qDebug()<<"failed to connect to MySQL:"<<testDB.lastError();
        return -1;
    }

    //check database &tables before running.
    QSqlQuery query(testDB);
    QString strCheckDB("create database if not exists pms Character set UTF8");
    if(!query.exec(strCheckDB))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }
    qDebug()<<"check database PMS is okay.";
    //check roleinfo table.
    QString strCheckRoleInfoTable(
                "CREATE TABLE IF NOT EXISTS `pms`.`roleinfo` ("
                "`RoleName` varchar(64) NOT NULL,"
                "`PermBits` varchar(64) NOT NULL,"
                "`RoleMemo` varchar(512) DEFAULT NULL,"
                "`Creator` varchar(64) NOT NULL,"
                " `CreateTime` datetime NOT NULL,"
                " PRIMARY KEY (`RoleName`)"
                ") ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    if(!query.exec(strCheckRoleInfoTable))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }
    qDebug()<<"check RoleInfo table is okay.";

    //if admin role is not exist then create it.
    QString strCheckAdminRole("SELECT * FROM `pms`.`roleinfo` WHERE `RoleName`='admin'");
    if(!query.exec(strCheckAdminRole))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }else{
        if(query.next())
        {
            qDebug()<<"check Admin role is okay.";
        }else{
            //admin role is not exist.create it now.
            query.prepare("INSERT  INTO `pms`.`roleinfo`(`RoleName`,`PermBits`,`RoleMemo`,`Creator`,`CreateTime`) VALUES ('admin','255,255,255,255,255,255','PMS Initial Created','admin',:CreateTime)");
            query.bindValue(":CreateTime",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            if(!query.exec())
            {
                qDebug()<<query.lastError().text();
                return -1;
            }else{
                qDebug()<<"create admin role okay.";
            }
        }
    }

    //check userinfo table.
    QString strCheckUserInfoTable(
                "CREATE TABLE IF NOT EXISTS `pms`.`userinfo` ("
                " `UserName` VARCHAR(64) NOT NULL,"
                " `RealName` VARCHAR(256) DEFAULT NULL,"
                " `RoleName` VARCHAR(64) NOT NULL,"
                " `Sex` VARCHAR(16) DEFAULT NULL,"
                " `LockBit` INT(1) DEFAULT NULL,"
                " `Password` VARCHAR(64) NOT NULL,"
                " `Mobile` VARCHAR(64) DEFAULT NULL,"
                " `Creator` VARCHAR(64) DEFAULT NULL,"
                " `CreateTime` DATETIME DEFAULT NULL,"
                " `LastLoginTime` DATETIME DEFAULT NULL,"
                " PRIMARY KEY (`UserName`)"
                ") ENGINE=INNODB DEFAULT CHARSET=utf8;");
    if(!query.exec(strCheckUserInfoTable))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }
    qDebug()<<"check UserInfo table is okay.";

    //if admin user is not exist then create it.
    QString strCheckAdminUser("SELECT *FROM `pms`.`userinfo` WHERE `UserName`='admin'");
    if(!query.exec(strCheckAdminUser))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }else{
        if(query.next())
        {
            qDebug()<<"check Admin user is okay.";
        }else{
            //admin user is not exist.create it now.
            query.prepare("INSERT  INTO `pms`.`userinfo`(`UserName`,`RealName`,`RoleName`,`Sex`,`LockBit`,`Password`,`Mobile`,`Creator`,`CreateTime`,`LastLoginTime`) VALUES ('admin','超级管理员','admin','male',0,'MTIzNDU2','13522296239','PMS',:CreateTime,:LastLoginTime)");
            query.bindValue(":CreateTime",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query.bindValue(":LastLoginTime",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            if(!query.exec())
            {
                qDebug()<<query.lastError().text();
                return -1;
            }else{
                qDebug()<<"create admin user okay.";
            }
        }
    }
    //check templateinfo table.
    QString strCheckTemplateInfoTable(
                "CREATE TABLE IF NOT EXISTS `pms`.`templateinfo` ("
                "  `TemplateName` varchar(64) NOT NULL,"
                "  `VarSourceName` varchar(64) NOT NULL,"
                "   `FileSize` int(11) DEFAULT NULL,"
                "    `Creator` varchar(64) DEFAULT NULL,"
                "    `CreateTime` datetime DEFAULT NULL,"
                "    PRIMARY KEY (`TemplateName`)"
                "  ) ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    if(!query.exec(strCheckTemplateInfoTable))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }
    qDebug()<<"check TemplateInfo table is okay.";

    //check varsourceinfo table.
    QString strCheckVarSourceInfoTable(
                "  CREATE TABLE IF NOT EXISTS `pms`.`varsourceinfo` ("
                "   `VarSourceName` varchar(64) NOT NULL,"
                "   `RefCount` int(11) DEFAULT NULL,"
                "  `Creator` varchar(64) DEFAULT NULL,"
                "  `CreateTime` datetime DEFAULT NULL,"
                "  PRIMARY KEY (`VarSourceName`)"
                "  ) ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    if(!query.exec(strCheckVarSourceInfoTable))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }
    qDebug()<<"check VarSourceInfo table is okay.";

    //check folderinfo table.
    QString strCheckFolderInfoTable(
                " CREATE TABLE IF NOT EXISTS `pms`.`folderinfo` ("
                "  `FolderName` varchar(64) NOT NULL,"
                "  `Creator` varchar(64) DEFAULT NULL,"
                "  `CreateTime` datetime DEFAULT NULL,"
                "   PRIMARY KEY (`FolderName`)"
                " ) ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    if(!query.exec(strCheckFolderInfoTable))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }
    qDebug()<<"check FolderInfo table is okay.";

    //check fileinfo table.
    QString strCheckFileInfoTable(
                " CREATE TABLE IF NOT EXISTS `pms`.`fileinfo` ("
                " `FileName` varchar(64) NOT NULL,"
                " `FolderName` varchar(64) DEFAULT NULL,"
                "  `FileType` varchar(8) DEFAULT NULL,"
                "   `FileSize` int(11) DEFAULT NULL,"
                "   `Creator` varchar(64) DEFAULT NULL,"
                "   `CreateTime` datetime DEFAULT NULL,"
                "  PRIMARY KEY (`FileName`)"
                "  ) ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    if(!query.exec(strCheckFileInfoTable))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }
    qDebug()<<"check FileInfo table is okay.";

    //check processinfo table.
    QString strCheckProcessInfoTable(
                " CREATE TABLE IF NOT EXISTS `pms`.`processinfo` ("
                "  `ProcessName` varchar(64) NOT NULL,"
                "  `StepNum` int(11) DEFAULT NULL,"
                "  `Creator` varchar(64) DEFAULT NULL,"
                "  `CreateTime` datetime DEFAULT NULL,"
                "  PRIMARY KEY (`ProcessName`)"
                " ) ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    if(!query.exec(strCheckProcessInfoTable))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }
    qDebug()<<"check ProcessInfo table is okay.";

    //check stepinfo table.
    QString strCheckStepInfoTable(
                "CREATE TABLE IF NOT EXISTS `pms`.`stepinfo` ("
                " `No` int(11) NOT NULL AUTO_INCREMENT,"
                "  `StepName` varchar(64) DEFAULT NULL,"
                "  `ProcessName` varchar(64) DEFAULT NULL,"
                "  `LinkTemplates` varchar(256) DEFAULT NULL,"
                "  `LinkFiles` varchar(256) DEFAULT NULL,"
                "  `LinkRoles` varchar(256) DEFAULT NULL,"
                "  PRIMARY KEY (`No`)"
                " ) ENGINE=InnoDB AUTO_INCREMENT=41 DEFAULT CHARSET=utf8;");
    if(!query.exec(strCheckStepInfoTable))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }
    qDebug()<<"check StepInfo table is okay.";

    //check taskinfo table.
    QString strCheckTaskInfoTable(
                " CREATE TABLE IF NOT EXISTS `pms`.`taskinfo` ("
                "  `TaskName` varchar(64) NOT NULL,"
                "  `RefProcess` varchar(64) DEFAULT NULL,"
                "  `RefStep` varchar(64) DEFAULT NULL,"
                "  `RefTemplate` varchar(64) DEFAULT NULL,"
                " `TaskState` int(11) DEFAULT NULL,"
                "  `Creator` varchar(64) DEFAULT NULL,"
                "  `CreateTime` datetime DEFAULT NULL,"
                "  `Checker` varchar(64) DEFAULT NULL,"
                "  `CheckTime` datetime DEFAULT NULL,"
                " `MachineNo` varchar(64) DEFAULT NULL,"
                "  `ClassNo` varchar(64) DEFAULT NULL,"
                "  `OrderNo` varchar(64) DEFAULT NULL,"
                "  `ProductNo` varchar(64) DEFAULT NULL,"
                "  PRIMARY KEY (`TaskName`)"
                ") ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    if(!query.exec(strCheckTaskInfoTable))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }
    qDebug()<<"check TaskInfo table is okay.";

    //check forminfo table.
    QString strCheckFormInfoTable(
                "   CREATE TABLE IF NOT EXISTS `pms`.`forminfo` ("
                "   `FormName` varchar(64) NOT NULL,"
                "   `FileSize` int(11) DEFAULT NULL,"
                "   `Creator` varchar(64) DEFAULT NULL,"
                "   `CreateTime` datetime DEFAULT NULL,"
                "   PRIMARY KEY (`FormName`)"
                " ) ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    if(!query.exec(strCheckFormInfoTable))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }
    qDebug()<<"check FormInfo table is okay.";

    //check backupinfo table.
    QString strCheckBackupInfoTable(
                "CREATE TABLE IF NOT EXISTS `pms`.`backupinfo` ("
                "`BackupName` varchar(64) NOT NULL,"
                "`FileSize` int(11) DEFAULT NULL,"
                " `Creator` varchar(64) DEFAULT NULL,"
                " `CreateTime` datetime DEFAULT NULL,"
                " PRIMARY KEY (`BackupName`)"
                " ) ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    if(!query.exec(strCheckBackupInfoTable))
    {
        qDebug()<<query.lastError().text();
        return -1;
    }
    qDebug()<<"check BackupInfo table is okay.";

    //start TCP Server.
    PTcpServer tcpServer;
    if(tcpServer.listen(QHostAddress::Any,PGblPara::ZGetInstance()->m_tcpPort.toInt()))
    {
        qDebug()<<"listening on "<<PGblPara::ZGetInstance()->m_tcpPort<<"...";
    }else{
        qDebug()<<"start failed:"<<tcpServer.errorString();
        return -1;
    }
    return app.exec();
}
