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

    qDebug()<<"PMS Server "<<PMSSERVER_VERSION<<" build on "<<QString(__DATE__)<<QString(__TIME__);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    //check its ftp base dir is exist or not.
    qDebug()<<"Working Dir:"<<QDir::currentPath();
    QString dataDir=QDir::currentPath()+"/data";
    QString updateDir=QDir::currentPath()+"/update";
    QDir dir;
    if(!QDir(dataDir).exists())
    {
        dir.mkpath(dataDir);
    }
    if(!QDir(updateDir).exists())
    {
        dir.mkpath(updateDir);
    }

    //mysql info.
    qDebug()<<"MySQL Server ["<<MYSQL_IP<<":"<<MYSQL_PORT<<"],DB:"<<MYSQL_DB<<",USER:"<<MYSQL_USER;
    //try to connect mysql.
    QSqlDatabase testDB=QSqlDatabase::addDatabase("QMYSQL");
    testDB.setHostName(MYSQL_IP);
    testDB.setPort(MYSQL_PORT);
    testDB.setUserName(MYSQL_USER);
    testDB.setPassword(MYSQL_PASS);
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

    //load config file.
    qDebug()<<"loading config file...";
    PGblPara::ZGetInstance()->ZLoadCfgFile();

    //start TCP Server.
    PTcpServer tcpServer;
    if(tcpServer.listen(QHostAddress::Any,TCP_PORT))
    {
        qDebug()<<"listening on "<<TCP_PORT<<"...";
    }else{
        qDebug()<<"start failed:"<<tcpServer.errorString();
        return -1;
    }
    return app.exec();
}
