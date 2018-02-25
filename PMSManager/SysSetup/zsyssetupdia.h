#ifndef ZSYSSETUPDIA_H
#define ZSYSSETUPDIA_H

#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QSplitter>
#include <QRadioButton>
#include <QButtonGroup>
class ZServerSetupWidget:public QWidget
{
public:
    ZServerSetupWidget(QWidget *parent=0);
    ~ZServerSetupWidget();

    void ZSetServerIP(QString ip);
    QString ZGetServerIP();

    void ZSetServerPort(QString port);
    QString ZGetServerPort();
private:
    QLabel *m_llHelp;
    QLabel *m_llIP;
    QLineEdit *m_leIP;
    QLabel *m_llPort;
    QLineEdit *m_lePort;
    QGridLayout *m_gridLayout;
};
class ZSecurityWidget:public QWidget
{
public:
    ZSecurityWidget(QWidget *parent=0);
    ~ZSecurityWidget();

public:
    QLabel *m_llHelp;
    QLabel *m_llOldPassword;
    QLineEdit *m_leOldPassword;
    QLabel *m_llNewPassword1;
    QLineEdit *m_leNewPassword1;
    QLabel *m_llNewPassword2;
    QLineEdit *m_leNewPassword2;
    QGridLayout *m_gridLayout;
};
class ZLocalBufferWidget:public QFrame
{
public:
    ZLocalBufferWidget(QWidget *parent=0);
    ~ZLocalBufferWidget();
private:
    QLabel *m_llHelp;
    QToolButton *m_tbClearUserList;
    QToolButton *m_tbClearDwnFile;
    QGridLayout *m_gridLayout;
};
class ZFileViewWidget:public QFrame
{
public:
    ZFileViewWidget(QWidget *parent=0);
    ~ZFileViewWidget();
public:
    QLabel *m_llHelp;

    QLabel *m_llPdf;
    QRadioButton *m_rbInnerPdfViewer;
    QRadioButton *m_rbOuterPdfViewer;
    QButtonGroup *m_bgPdfViewer;
    QLineEdit *m_leOuterPdfViewer;
    QToolButton *m_tbOuterPdfViewerSelect;

    QLabel *m_llPic;
    QRadioButton *m_rbInnerPicViewer;
    QRadioButton *m_rbOuterPicViewer;
    QButtonGroup *m_bgPicViewer;
    QLineEdit *m_leOuterPicViewer;
    QToolButton *m_tbOuterPicViewerSelect;

    QGridLayout *m_gridLayout;
};
class ZSysSetupDia : public QDialog
{
    Q_OBJECT
public:
    ZSysSetupDia(QWidget *parent);
    ~ZSysSetupDia();
private slots:
    void ZSlotOkay();
    void ZSlotCancel();
    void ZSlotShowSetupParts(qint32 index);
private:
    QListWidget *m_listWidget;
    QStackedWidget *m_stackWidget;
    QSplitter *m_spliter;

    QToolButton *m_tbOkay;
    QToolButton *m_tbCancel;
    QHBoxLayout *m_hLayout;
    QVBoxLayout *m_vLayout;

    //////////////////////////////
    ZServerSetupWidget *m_serverSetup;
    ZSecurityWidget *m_security;
    ZLocalBufferWidget *m_localBuffer;
    ZFileViewWidget *m_fileViewer;
};

#endif // ZSYSSETUPDIA_H
