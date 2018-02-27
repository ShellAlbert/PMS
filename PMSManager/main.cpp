#include "pmainwin.h"
#include <QApplication>
#include <QObject>
#include <QDir>
#include <QTextCodec>
#include "NetProtocol/pnetprotocol.h"
#include "pgblpara.h"
#include <LoginManager/ploginmanager.h>
#include <FormDesigner/pformdesigner.h>
#include <QSettings>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    //check cache dir is exist or not.
    QString cacheDir(QDir::currentPath()+"/cache");
    QDir dir;
    if(!dir.exists(cacheDir))
    {
        dir.mkdir(cacheDir);
    }
    QFile file(":/Skin/DefaultUI.qss");
    if(file.open(QIODevice::ReadOnly))
    {
        a.setStyleSheet(file.readAll());
        file.close();
    }

    //load config file.
    //server ip & port.
    MyUserInfo::ZGetInstance()->ZLoadIniFile();

    //used to process network communication protocols.
    PNetProcessor netProcess;

    //the main windows.
    PMainWin mainWin;
    QObject::connect(&netProcess,SIGNAL(ZSignalTxNetFrmFinish(qint32,qint32)),&mainWin,SLOT(ZSlotCloseWaitingDialog(qint32,qint32)));

    //login manager.
    PLoginManager loginM;
    if(loginM.exec()==QDialog::Accepted)
    {
        mainWin.ZUpdateUserInfo();
        mainWin.showMaximized();
        return a.exec();
    }
    return 0;
}

