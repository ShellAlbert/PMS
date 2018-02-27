#include "pmainwin.h"
#include <QApplication>
#include <TcpServer/ptcpserver.h>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDir>
#include <AES/TAesClass.h>
#include "pgblpara.h"

//RoleInfo:RoleName,PermBits,RoleMemo,CreateTime.
//UserInfo:UserName,RealName,RoleName,Password,Sex,Mobile,Creator,CreateTime.



/*Table structure for table `roleinfo` */

//DROP TABLE IF EXISTS `roleinfo`;

//CREATE TABLE `roleinfo` (
//  `RoleName` varchar(64) NOT NULL,
//  `PermBits` int(11) DEFAULT NULL,
//  `RoleMemo` varchar(512) DEFAULT NULL,
//  `Creator` varchar(64) NOT NULL,
//  `CreateTime` datetime NOT NULL,
//  PRIMARY KEY (`RoleName`)
//) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `roleinfo` */

//insert  into `roleinfo`(`RoleName`,`PermBits`,`RoleMemo`,`Creator`,`CreateTime`) values ('admin',65536,'nothing','admin','2018-02-26 20:32:11');


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

    QApplication a(argc, argv);

#if 0
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("pms");
    if(db.open())
    {
        qDebug()<<"open ok!";
    }else{
        qDebug()<<"open failed";
        qDebug()<<db.lastError();
    }
#endif

    //check its ftp base dir is exist or not.
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

    //load config file.
    PGblPara::ZGetInstance()->ZLoadCfgFile();

    //start TCP Server.
    PTcpServer tcpServer;
    if(tcpServer.listen(QHostAddress::Any,6800))
    {
        qDebug()<<"PMSServer listen on 6800...\n";
    }else{
        qDebug()<<"PMSServer start failed:"<<tcpServer.errorString();
    }
    return a.exec();
}
