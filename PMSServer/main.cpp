#include "pmainwin.h"
#include <QApplication>
#include <TcpServer/ptcpserver.h>
#include <QObject>
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


    QApplication a(argc, argv);
    //check its ftp base dir is exist or not.
    QString dataDir=QDir::currentPath()+"/data";
    QString updateDir=QDir::currentPath()+"/update";
    QDir dir;
    dir.mkpath(dataDir);
    dir.mkpath(updateDir);

    PGblPara::ZGetInstance()->ZLoadCfgFile();

    PTcpServer tcpServer;
    if(tcpServer.listen(QHostAddress::Any,6800))
    {
        qDebug()<<"PMSServer listen on 6800...\n";
    }else{
        qDebug()<<"PMSServer start failed:"<<tcpServer.errorString();
    }
    return a.exec();
}
