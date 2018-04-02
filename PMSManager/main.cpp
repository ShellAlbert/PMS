#include "pmainwin.h"
#include <QApplication>
#include <QObject>
#include <QDir>
#include <QTextCodec>
#include "NetProtocol/pnetprotocol.h"
#include "pgblpara.h"
#include <QSplashScreen>
#include <LoginManager/ploginmanager.h>
#include <FormDesigner/pformdesigner.h>
#include <QSettings>
#include <QDesktopWidget>

//the administrator username is admin,not root!!!

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    CuteDesigner::Core  * core = new CuteDesigner::Core();
//    int result = app.exec();
//    delete core;
//    return result;

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QSplashScreen *splash=new QSplashScreen;
    splash->setPixmap(QPixmap(":/LoginManager/images/LoginManager/Splash.png"));
//    QFont splashFont=splash->font();
//    splashFont.setPointSize(32);
//    splash->setFont(splashFont);
    splash->show();

    //check cache dir is exist or not.
    splash->showMessage(QObject::tr("PMS正在检查资源文件..."),Qt::AlignLeft|Qt::AlignBottom,Qt::black);
    QDir dir;
    QString cacheDir(QDir::currentPath()+"/cache");
    if(!dir.exists(cacheDir))
    {
        dir.mkdir(cacheDir);
    }
    QString cfgDir(QDir::currentPath()+"/cfg");
    if(!dir.exists(cfgDir))
    {
        dir.mkdir(cfgDir);
    }
    QThread::usleep(5000);

    //load skin file.
    splash->showMessage(QObject::tr("PMS正在载入UI文件..."),Qt::AlignLeft|Qt::AlignBottom,Qt::black);
    QFile file(":/Skin/DefaultUI.qss");
    if(file.open(QIODevice::ReadOnly))
    {
        app.setStyleSheet(file.readAll());
        file.close();
    }
    QThread::usleep(8000);

    //load config file.
    //server ip & port.
    splash->showMessage(QObject::tr("PMS正在载入配置文件..."),Qt::AlignLeft|Qt::AlignBottom,Qt::black);
    MyUserInfo::ZGetInstance()->ZLoadIniFile();
    QThread::usleep(8000);

    //used to process network communication protocols.
    splash->showMessage(QObject::tr("PMS正在创建通讯线程..."),Qt::AlignLeft|Qt::AlignBottom,Qt::black);
    PNetProcessor netProcess;
    QThread::usleep(8000);

    //the main windows.
    splash->showMessage(QObject::tr("PMS正在创建主窗体..."),Qt::AlignLeft|Qt::AlignBottom,Qt::black);
    PMainWin mainWin;
    QThread::sleep(3);

    //show guide window.
    PGuideWin guideWin(&mainWin);

    QObject::connect(&netProcess,SIGNAL(ZSignalTxNetFrmFinish(qint32,qint32)),&mainWin,SLOT(ZSlotCloseWaitingDialog(qint32,qint32)));
    QObject::connect(&guideWin,SIGNAL(ZSignalShowTaskBar(bool)),&mainWin,SLOT(ZSlotShowTaskBar(bool)));
    QObject::connect(&guideWin,SIGNAL(ZSignalShowLogBar(bool)),&mainWin,SLOT(ZSlotShowLogBar(bool)));
    QObject::connect(&guideWin,SIGNAL(ZSignalLatchModule(qint32)),&mainWin,SLOT(ZSlotLatchModule(qint32)));

    //login manager.
    PLoginManager loginM;
    splash->finish(&loginM);
    if(loginM.exec()==QDialog::Accepted)
    {
        delete splash;

        mainWin.ZUpdateUserInfo();
        mainWin.showMaximized();
        guideWin.show();
        QDesktopWidget *desktop=app.desktop();
        qint32 nX=desktop->screenGeometry().width()-guideWin.width()*4;
        qint32 nY=(desktop->screenGeometry().height()-guideWin.height())/2;
        guideWin.move(nX,nY);

        return app.exec();
    }
    delete splash;
    return 0;
}

