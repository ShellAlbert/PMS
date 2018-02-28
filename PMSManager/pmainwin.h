#ifndef PMAINWIN_H
#define PMAINWIN_H
#include <QFrame>
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QTimer>
#include <QPoint>
#include <QMdiArea>
#include <QSplitter>
#include "UserManager/pusermanagerwin.h"
#include "TemplateEditor/ptemplateeditor.h"
#include "FileManager/pfilemanager.h"
#include "ProcessEditor/pprocesseditor.h"
#include "TaskManager/ptaskmanager.h"
#include <FormDesigner/pformdesigner.h>
#include <LoginManager/ploginmanager.h>
#include <QMap>
#include <BasePart/zbaseinfodia.h>
#include <Logger/zlogmanager.h>
class ZHeartBeatInfoDia:public ZBaseInfoDia
{
public:
    ZHeartBeatInfoDia(QWidget *parent=0);
    void ZExecuteHeartBeatOp();
    void ZParseAckNetFrmXmlData();
};
class ZMdiArea:public QMdiArea
{
 public:
    ZMdiArea(QWidget *parent=0);
protected:
    void paintEvent(QPaintEvent *event);
};
class ZShowUserInfoDia:public QDialog
{
    Q_OBJECT
public:
    ZShowUserInfoDia(QWidget *parent=0);
    ~ZShowUserInfoDia();
private:
    QLabel *m_llUserName;
    QLineEdit *m_leUserName;

    QLabel *m_llRealName;
    QLineEdit *m_leRealName;

    QLabel *m_llSex;
    QLineEdit *m_leSex;

    QLabel *m_llRoleName;
    QLineEdit *m_leRoleName;

    QLabel *m_llCreator;
    QLineEdit *m_leCreator;

    QLabel *m_llCreateTime;
    QLineEdit *m_leCreateTime;

    QToolButton *m_tbClose;
    QGridLayout *m_gridLayout;
};
class ZTaskInfoWidget:public QFrame
{
    Q_OBJECT
public:
    ZTaskInfoWidget(QWidget *parent=0);
    ~ZTaskInfoWidget();

    void ZSetWaitCheckTaskNum(qint32 num);
    void ZSetSubmitTaskNum(qint32 num);
    void ZSetCheckFailedNum(qint32 num);

    void ZSetHighContrast(bool on1,bool on2,bool on3);
private slots:
    void ZSlotTimerFlush();
public:
    QLabel *m_llNeedCheckByMeTask;
    QLabel *m_llNeedCheckByMeTaskNum;
    QLabel *m_llSubmitTask;
    QLabel *m_llSubmitTaskNum;
    QLabel *m_llCheckFail;
    QLabel *m_llCheckFailNum;
    QGridLayout *m_gridLayout;

    QTimer *m_flashTimer;

    qint32 m_nNotSubmitNum;
    qint32 m_nSubmitNum;
    qint32 m_nCheckFailedNum;

    bool m_bNotSubmitFlag;
    bool m_bSubmitFlag;
    bool m_bCheckFailedFlag;
};

class ZUpdateNotifyDialog:public ZBaseInfoDia,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    ZUpdateNotifyDialog(QWidget *parent=0);
    ~ZUpdateNotifyDialog();
    void ZSetMsg(QString msg);
    void ZSetUpdateInfo(qint32 totalBlock,qint32 blockSize,qint32 remainBytes);

    void ZParseAckNetFrmXmlData();
    void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
private:
    void ZGetNewVersion(qint32 totalBlock,qint32 blockSize,qint32 remainBytes);
private:
    QLabel *m_llIcon;
    QLabel *m_llMsg;
    QToolButton *m_btnOkay;
    QToolButton *m_btnCancel;
    QCheckBox *m_cbNeverNotify;
    QGridLayout *m_gridLayout;
    ////////////////////
    qint32 m_blockSize;
    qint32 m_totalBlock;
    qint32 m_remainBytes;
};
class PMainWin : public QWidget,public ZAckNetFrmWidget
{
    Q_OBJECT
public:
    PMainWin(QWidget *parent = 0);
    ~PMainWin();

    void ZProcessAckNetFrm(QString item,QString cmd,QStringList paraList,qint32 ackNetRetCode);
    void ZUpdateUserInfo();
protected:
    QSize sizeHint() const;
public slots:
    void ZSlotCloseWaitingDialog(qint32 netFrmSerialNo,qint32 retCode);
    void ZSlotShowTaskBar(bool bShow);
    void ZSlotShowLogBar(bool bShow);
private slots:
    void ZSlotUpdateStatusBarTime();
    void ZSlotShowUserManager();
    void ZSlotShowTemplateEditor();
    void ZSlotShowFileManager();
    void ZSlotShowProcessEditor();
    void ZSlotShowTaskManager();
    void ZSlotShowFormDesigner();
    void ZSlotShowSystemLog();
    void ZSlotShowSystemSetup();
    void ZSlotShowDataBackup();
    void ZSlotShowSoftInfo();
    void ZSlotShowUserInfo();
    void ZSlotLockScreen();
    void ZSlotExitSys();
    void ZSlotCloseSubWidget(QString widget);
    void ZSlotHearBeat();
private:
    void ZFuncRefreshStatusBar();
private:
    QFrame *m_taskBarWidget;
    QFrame *m_centerWidget;
    QFrame *m_statusBarWidget;

    //taskbar.
    QLabel *m_lblLogo;
    QLabel *m_lblName;
    QToolButton *m_btnUserManager;
    QToolButton *m_btnTemplateEditor;
    QToolButton *m_btnFileManager;
    QToolButton *m_btnProcessEditor;
    QToolButton *m_btnTaskManager;
    QToolButton *m_btnReportDesigner;
    QToolButton *m_btnSysLog;
    QToolButton *m_btnSysSetup;
    QToolButton *m_btnDataBackup;
    QToolButton *m_btnUpgrade;
    QToolButton *m_btnSoftInfo;
    ZTaskInfoWidget *m_taskInfo;
    QToolButton *m_btnUserInfo;
    QToolButton *m_btnLockScreen;
    QToolButton *m_btnExitSys;
    QHBoxLayout *m_hLayoutTaskBar;

    //center.
    ZMdiArea *m_midArea;
    QSplitter *m_spliter;
    //status bar.
    QHBoxLayout *m_hLayoutStatusBar;
    QLabel *m_lblWelcomeInfo;
    QLabel *m_lblTime;
    QTimer *m_1sTimer;
    qint64 m_runCounter;
    //main.
    QVBoxLayout *m_vLayoutMain;

private:
    ZLogManager *m_logManager;

    PUserManagerWin* m_userManager;
    QMdiSubWindow *m_mdiUserManager;

    PTemplateEditor *m_templateEditor;
    QMdiSubWindow *m_mdiTemplateEditor;

    PFileManager *m_fileManager;
    QMdiSubWindow *m_mdiFileManager;

    PProcessEditor *m_processEdit;
    QMdiSubWindow *m_mdiProcessEdit;

    PTaskManager *m_taskManager;
    QMdiSubWindow *m_mdiTaskManager;

    PFormDesigner *m_formDesigner;
    QMdiSubWindow *m_mdiFormDesigner;
private:
    QTimer *m_timerHeartBeat;

    ZUpdateNotifyDialog *m_updateNotifyDia;
};

class PGuideWin:public QWidget
{
    Q_OBJECT
public:
    PGuideWin(QWidget *parent=0);
    ~PGuideWin();
signals:
    void ZSignalShowTaskBar(bool bShow);
    void ZSignalShowLogBar(bool bShow);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QVBoxLayout *m_vLayout;
    QLabel *m_lblGuide;
    QPoint m_relativePos;
    bool m_bShowTaskBar;
    bool m_bShowLogBar;
};
#endif // PMAINWIN_H
