#include "pmainwin.h"
#include <QApplication>
#include <TcpServer/ptcpserver.h>
#include <QObject>
#include <QSqlDatabase>
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
