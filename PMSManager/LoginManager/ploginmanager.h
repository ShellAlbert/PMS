#ifndef PLOGINMANAGER_H
#define PLOGINMANAGER_H

#include <QDialog>
#include <QToolButton>
#include <QLineEdit>
#include <QResizeEvent>
#include <BasePart/zbaseinfodia.h>
#include <QLabel>
#include <QComboBox>
#include <QMovie>
#include <QGridLayout>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <pgblpara.h>
class ZLoginPart:public QFrame
{
    Q_OBJECT
public:
    ZLoginPart(QWidget *parent=0);
    bool ZDoInit();
    ~ZLoginPart();
signals:
    void ZSignalDoLogin();
    void ZSignalDoExit();
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
public:
    QLabel *m_llLogo;

    QLabel *m_llUserIcon;
    QLabel *m_llUserName;
    QComboBox *m_cbUserName;

    QLabel *m_llPasswordIcon;
    QLabel *m_llPassword;
    QLineEdit *m_lePassword;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayoutBtn;

    QGridLayout *m_gridLayout;
};
class ZWaitingPart:public QFrame
{
public:
    ZWaitingPart(QWidget *parent=0);
    ~ZWaitingPart();
public:
    QLabel *m_llWaitingGif;
    QMovie *m_movie;
    QVBoxLayout *m_vLayout;
};
class ZLoginFailPart:public QFrame
{
    Q_OBJECT
public:
    ZLoginFailPart(QWidget *parent=0);
    ~ZLoginFailPart();
    void ZSetFailMsg(QString msg);
signals:
    void ZSignalReturn();
public:
    QLabel *m_llFailIcon;
    QLabel *m_llFailMsg;
    QToolButton *m_tbReturn;
    QHBoxLayout *m_hLayout;
};
class PLoginManager : public ZBaseInfoDia
{
    Q_OBJECT
public:
    PLoginManager(QWidget *parent=0);
    ~PLoginManager();

    void ZParseAckNetFrmXmlData();
    void ZLockUserName(QString userName);
protected:
    void closeEvent(QCloseEvent *e);
public slots:
    void ZSlotDoLogin();
    void ZSlotDoExit();
    void ZSlotLoginOpFinished(qint32 retCode);
    void ZSlotShowLoginPart();
    void ZSlotDoExitClean();
private:
    void ZLoadUserList();
    void ZSaveUserList();
private:
    QLabel *m_llBanner;
    QMovie *m_movieBanner;
    QStackedWidget *m_stackedWidget;
    QVBoxLayout *m_vLayout;

    //////////////
    ZLoginPart *m_loginPart;
    ZWaitingPart *m_waitingPart;
    ZLoginFailPart *m_loginFailPart;
    QLabel *m_llInfo;
};

#endif // PLOGINMANAGER_H
