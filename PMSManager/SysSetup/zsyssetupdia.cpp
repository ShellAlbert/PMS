#include "zsyssetupdia.h"
#include "pgblpara.h"
ZServerSetupWidget::ZServerSetupWidget(QWidget *parent):QWidget(parent)
{
    this->m_llHelp=new QLabel(tr("配置PMS Server的IP地址及端口号"));
    this->m_llHelp->setAlignment(Qt::AlignCenter);
    this->m_llIP=new QLabel(tr("服务器地址"));
    this->m_leIP=new QLineEdit;
    this->m_llPort=new QLabel(tr("端口号"));
    this->m_lePort=new QLineEdit;
    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llHelp,0,0,1,2);
    this->m_gridLayout->addWidget(this->m_llIP,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_leIP,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_llPort,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_lePort,2,1,1,1);
    this->setLayout(this->m_gridLayout);

    this->ZSetServerIP(MyUserInfo::ZGetInstance()->m_PMSIp);
    this->ZSetServerPort(QString("%1").arg(MyUserInfo::ZGetInstance()->m_PMSPort));
}
ZServerSetupWidget::~ZServerSetupWidget()
{
    delete this->m_llHelp;
    delete this->m_llIP;
    delete this->m_leIP;
    delete this->m_llPort;
    delete this->m_lePort;
    delete this->m_gridLayout;
}

void ZServerSetupWidget::ZSetServerIP(QString ip)
{
    this->m_leIP->setText(ip);
}
QString ZServerSetupWidget::ZGetServerIP()
{
    return this->m_leIP->text().trimmed();
}
void ZServerSetupWidget::ZSetServerPort(QString port)
{
    this->m_lePort->setText(port);
}
QString ZServerSetupWidget::ZGetServerPort()
{
    return this->m_lePort->text().trimmed();
}

ZSecurityWidget::ZSecurityWidget(QWidget *parent):QWidget(parent)
{
    this->m_llHelp=new QLabel(tr("更改用户登录密码"));
    this->m_llHelp->setAlignment(Qt::AlignCenter);

    this->m_llOldPassword=new QLabel(tr("旧密码(*)"));
    this->m_leOldPassword=new QLineEdit;
    this->m_llNewPassword1=new QLabel(tr("新密码(*)"));
    this->m_leNewPassword1=new QLineEdit;
    this->m_llNewPassword2=new QLabel(tr("确认新密码(*)"));
    this->m_leNewPassword2=new QLineEdit;
    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llHelp,0,0,1,2);
    this->m_gridLayout->addWidget(this->m_llOldPassword,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_leOldPassword,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_llNewPassword1,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_leNewPassword1,2,1,1,1);
    this->m_gridLayout->addWidget(this->m_llNewPassword2,3,0,1,1);
    this->m_gridLayout->addWidget(this->m_leNewPassword2,3,1,1,1);
    this->setLayout(this->m_gridLayout);
}
ZSecurityWidget::~ZSecurityWidget()
{
    delete this->m_llHelp;
    delete this->m_llOldPassword;
    delete this->m_leOldPassword;
    delete this->m_llNewPassword1;
    delete this->m_leNewPassword1;
    delete this->m_llNewPassword2;
    delete this->m_leNewPassword2;
    delete this->m_gridLayout;
}
ZLocalBufferWidget::ZLocalBufferWidget(QWidget *parent):QFrame(parent)
{
    this->m_llHelp=new QLabel(tr("清除本地缓存文件"));
    this->m_llHelp->setAlignment(Qt::AlignCenter);

    this->m_tbClearUserList=new QToolButton;
    this->m_tbClearUserList->setText(tr("清空用户列表"));
    this->m_tbClearDwnFile=new QToolButton;
    this->m_tbClearDwnFile->setText(tr("清空工艺文件缓存"));

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llHelp,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_tbClearUserList,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_tbClearDwnFile,1,1,1,1);
    this->setLayout(this->m_gridLayout);
}
ZLocalBufferWidget::~ZLocalBufferWidget()
{
    delete this->m_llHelp;
    delete this->m_tbClearUserList;
    delete this->m_tbClearDwnFile;
    delete this->m_gridLayout;
}

ZFileViewWidget::ZFileViewWidget(QWidget *parent):QFrame(parent)
{
    this->m_llHelp=new QLabel(tr(" 设置文件查看方式"));
    this->m_llHelp->setAlignment(Qt::AlignCenter);

    this->m_llPdf=new QLabel(tr("PDF文件查看方式"));
    this->m_rbInnerPdfViewer=new QRadioButton(tr("内置PDF文件查看器"));
    this->m_rbOuterPdfViewer=new QRadioButton(tr("外部PDF文件查看器"));
    this->m_bgPdfViewer=new QButtonGroup;
    this->m_bgPdfViewer->addButton(this->m_rbInnerPdfViewer);
    this->m_bgPdfViewer->addButton(this->m_rbOuterPdfViewer);
    this->m_bgPdfViewer->setExclusive(true);
    this->m_rbInnerPdfViewer->setChecked(true);
    this->m_leOuterPdfViewer=new QLineEdit;
    this->m_tbOuterPdfViewerSelect=new QToolButton;
    this->m_tbOuterPdfViewerSelect->setText(tr("选择..."));

    this->m_llPic=new QLabel(tr("图片文件查看方式"));
    this->m_rbInnerPicViewer=new QRadioButton(tr("内置图片查看器"));
    this->m_rbOuterPicViewer=new QRadioButton(tr("外部图片查看器"));
    this->m_bgPicViewer=new QButtonGroup;
    this->m_bgPicViewer->addButton(this->m_rbInnerPdfViewer);
    this->m_bgPicViewer->addButton(this->m_rbOuterPicViewer);
    this->m_bgPicViewer->setExclusive(true);
    this->m_rbInnerPicViewer->setChecked(true);
    this->m_leOuterPicViewer=new QLineEdit;
    this->m_tbOuterPicViewerSelect=new QToolButton;
    this->m_tbOuterPicViewerSelect->setText(tr("选择..."));

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llHelp,0,0,1,3);

    this->m_gridLayout->addWidget(this->m_llPdf,1,0,1,3);
    this->m_gridLayout->addWidget(this->m_rbInnerPdfViewer,2,0,1,1);

    this->m_gridLayout->addWidget(this->m_rbOuterPdfViewer,3,0,1,1);
    this->m_gridLayout->addWidget(this->m_leOuterPdfViewer,3,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbOuterPdfViewerSelect,3,2,1,1);

    this->m_gridLayout->addWidget(this->m_llPic,4,0,1,3);
    this->m_gridLayout->addWidget(this->m_rbInnerPicViewer,5,0,1,1);

    this->m_gridLayout->addWidget(this->m_rbOuterPicViewer,6,0,1,1);
    this->m_gridLayout->addWidget(this->m_leOuterPicViewer,6,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbOuterPicViewerSelect,6,2,1,1);

    this->setLayout(this->m_gridLayout);
}
ZFileViewWidget::~ZFileViewWidget()
{
    delete this->m_llHelp;

    delete this->m_llPdf;
    delete this->m_rbInnerPdfViewer;
    delete this->m_rbOuterPdfViewer;
    delete this->m_leOuterPdfViewer;
    delete this->m_bgPdfViewer;
    delete this->m_tbOuterPdfViewerSelect;

    delete this->m_llPic;
    delete this->m_rbInnerPicViewer;
    delete this->m_rbOuterPicViewer;
    delete this->m_bgPicViewer;
    delete this->m_leOuterPicViewer;
    delete this->m_tbOuterPicViewerSelect;

    delete this->m_gridLayout;
}
ZSysSetupDia::ZSysSetupDia(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("系统设置"));

    this->m_listWidget=new QListWidget;

    QListWidgetItem *serverItem=new QListWidgetItem;
    serverItem->setText(tr("服务器"));
    serverItem->setIcon(QIcon(":/SystemSetup/images/SystemSetup/Server.png"));
    this->m_listWidget->addItem(serverItem);

    QListWidgetItem *securityItem=new QListWidgetItem;
    securityItem->setText(tr("用户安全"));
    securityItem->setIcon(QIcon(":/SystemSetup/images/SystemSetup/Security.png"));
    this->m_listWidget->addItem(securityItem);

    QListWidgetItem *bufferItem=new QListWidgetItem;
    bufferItem->setText(tr("本地缓存"));
    bufferItem->setIcon(QIcon(":/SystemSetup/images/SystemSetup/Cache.png"));
    this->m_listWidget->addItem(bufferItem);

    QListWidgetItem *fileItem=new QListWidgetItem;
    fileItem->setText(tr("文件查看"));
    fileItem->setIcon(QIcon(":/SystemSetup/images/SystemSetup/FileViewer.png"));
    this->m_listWidget->addItem(fileItem);


    this->m_stackWidget=new QStackedWidget;
    this->m_spliter=new QSplitter(Qt::Horizontal);
    this->m_spliter->addWidget(this->m_listWidget);
    this->m_spliter->addWidget(this->m_stackWidget);
    this->m_spliter->setStretchFactor(0,2);
    this->m_spliter->setStretchFactor(1,8);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));

    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_tbOkay);
    this->m_hLayout->addWidget(this->m_tbCancel);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_spliter);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);

    this->m_serverSetup=new ZServerSetupWidget;
    this->m_security=new ZSecurityWidget;
    this->m_localBuffer=new ZLocalBufferWidget;
    this->m_fileViewer=new ZFileViewWidget;
    this->m_stackWidget->addWidget(this->m_serverSetup);
    this->m_stackWidget->addWidget(this->m_security);
    this->m_stackWidget->addWidget(this->m_localBuffer);
    this->m_stackWidget->addWidget(this->m_fileViewer);

    connect(this->m_listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(ZSlotShowSetupParts(int)));
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
}
ZSysSetupDia::~ZSysSetupDia()
{
    delete this->m_serverSetup;
    delete this->m_security;
    delete this->m_localBuffer;
    delete this->m_fileViewer;

    delete this->m_listWidget;
    delete this->m_stackWidget;
    delete this->m_spliter;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayout;
    delete this->m_vLayout;
}
void ZSysSetupDia::ZSlotOkay()
{
    this->accept();
}
void ZSysSetupDia::ZSlotCancel()
{
    this->reject();
}
void ZSysSetupDia::ZSlotShowSetupParts(qint32 index)
{
    switch(index)
    {
    case 0:
        this->m_stackWidget->setCurrentWidget(this->m_serverSetup);
        break;
    case 1:
        this->m_stackWidget->setCurrentWidget(this->m_security);
        break;
    case 2:
        this->m_stackWidget->setCurrentWidget(this->m_localBuffer);
        break;
    case 3:
        this->m_stackWidget->setCurrentWidget(this->m_fileViewer);
        break;
    default:
        break;
    }
}
