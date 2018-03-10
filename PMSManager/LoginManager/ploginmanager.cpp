#include "ploginmanager.h"
#include <NetProtocol/pnetframe.h>
#include <QXmlStreamReader>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
ZLoginPart::ZLoginPart(QWidget *parent):QFrame(parent)
{
    this->setStyleSheet("QFrame{background-color:white;}");
    if(!this->ZDoInit())
    {
        QMessageBox::critical(this,tr("Error"),tr("Initial failed due to low memory!"));
        qApp->exit(-1);
    }
}
bool ZLoginPart::ZDoInit()
{
    try{
        this->m_llLogo=new QLabel;
    }catch(...)
    {
        qDebug()<<"new Logo label failed!";
        return false;
    }
    this->m_llLogo->setPixmap(QPixmap(":/LoginManager/images/LoginManager/Logo.png"));

    try{
        this->m_llUserIcon=new QLabel;
    }catch(...)
    {
        qDebug()<<"new UserIcon label failed!";
        return false;
    }
    this->m_llUserIcon->setPixmap(QPixmap(":/LoginManager/images/LoginManager/User.png"));


    try{
        this->m_llUserName=new QLabel(tr("用户名:"));
    }catch(...)
    {
        qDebug()<<"new UserName label failed!";
        return false;
    }

    try{
        this->m_cbUserName=new QComboBox;
    }catch(...)
    {
        qDebug()<<"new UserName comboBox failed!";
        return false;
    }
    this->m_cbUserName->setEditable(true);
    this->m_cbUserName->setFixedWidth(150);

    try{
        this->m_llPasswordIcon=new QLabel;
    }catch(...)
    {
        qDebug()<<"new PasswordIcon label failed!";
        return false;
    }
    this->m_llPasswordIcon->setPixmap(QPixmap(":/LoginManager/images/LoginManager/Lock.png"));

    try{
        this->m_llPassword=new QLabel(tr("密码:"));
    }catch(...)
    {
        qDebug()<<"new Password label failed!";
        return false;
    }

    try{
        this->m_lePassword=new QLineEdit;
    }catch(...)
    {
        qDebug()<<"new Password lineedit failed!";
        return false;
    }
    this->m_lePassword->setFixedWidth(150);
    this->m_lePassword->setMaxLength(45);
    this->m_lePassword->setEchoMode(QLineEdit::Password);

    try{
        this->m_tbOkay=new QToolButton;
    }catch(...)
    {
        qDebug()<<"new okay button failed!";
        return false;
    }
    this->m_tbOkay->setText(tr(" 登录"));

    try{
        this->m_tbCancel=new QToolButton;
    }catch(...)
    {
        qDebug()<<"new cancel button failed!";
        return false;
    }
    this->m_tbCancel->setText(tr(" 退出"));

    try{
        this->m_hLayoutBtn=new QHBoxLayout;
        this->m_hLayoutBtn->setSpacing(10);
        this->m_hLayoutBtn->addStretch(1);
        this->m_hLayoutBtn->addWidget(this->m_tbOkay);
        this->m_hLayoutBtn->addWidget(this->m_tbCancel);
    }catch(...)
    {
        qDebug()<<"new hlayout failed!";
        return false;
    }

    try{
        this->m_gridLayout=new QGridLayout;
    }catch(...)
    {
        qDebug()<<"new grid layout failed!";
        return false;
    }
    this->m_gridLayout->addWidget(this->m_llLogo,0,0,3,1);
    this->m_gridLayout->addWidget(this->m_llUserIcon,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_llUserName,0,2,1,1);
    this->m_gridLayout->addWidget(this->m_cbUserName,0,3,1,1);
    this->m_gridLayout->addWidget(this->m_llPasswordIcon,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_llPassword,1,2,1,1);
    this->m_gridLayout->addWidget(this->m_lePassword,1,3,1,1);
    this->m_gridLayout->addLayout(this->m_hLayoutBtn,2,2,1,2);
    this->m_gridLayout->setColumnStretch(0,6);
    this->m_gridLayout->setColumnStretch(1,1);
    this->m_gridLayout->setColumnStretch(2,1);
    this->m_gridLayout->setColumnStretch(3,1);

    this->setLayout(this->m_gridLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
    return true;
}
ZLoginPart::~ZLoginPart()
{
    delete this->m_llLogo;
    delete this->m_llUserIcon;
    delete this->m_llUserName;
    delete this->m_cbUserName;
    delete this->m_llPasswordIcon;
    delete this->m_llPassword;
    delete this->m_lePassword;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayoutBtn;
    delete this->m_gridLayout;
}
void ZLoginPart::ZSlotOkay()
{
    if(this->m_cbUserName->currentText().isEmpty())
    {
        this->m_cbUserName->setFocus();
        return;
    }
    if(this->m_lePassword->text().isEmpty())
    {
        this->m_lePassword->setFocus();
        return;
    }
    emit this->ZSignalDoLogin();
}
void ZLoginPart::ZSlotCancel()
{
    emit this->ZSignalDoExit();
}
ZWaitingPart::ZWaitingPart(QWidget *parent):QFrame(parent)
{
    this->m_llWaitingGif=new QLabel;
    this->m_llWaitingGif->setAlignment(Qt::AlignCenter);
    this->m_movie=new QMovie(":/gifs/images/gifs/logining.gif");
    this->m_llWaitingGif->setMovie(this->m_movie);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_llWaitingGif);
    this->setLayout(this->m_vLayout);

    this->m_movie->start();
}
ZWaitingPart::~ZWaitingPart()
{
    this->m_movie->stop();
    delete this->m_movie;
    delete this->m_llWaitingGif;
    delete this->m_vLayout;
}
ZLoginFailPart::ZLoginFailPart(QWidget *parent):QFrame(parent)
{
    this->m_llFailIcon=new QLabel;
    this->m_llFailIcon->setAlignment(Qt::AlignCenter);
    this->m_llFailIcon->setPixmap(QPixmap(":/LoginManager/images/LoginManager/Error.png"));
    this->m_llFailMsg=new QLabel;
    this->m_llFailMsg->setAlignment(Qt::AlignCenter);
    this->m_tbReturn=new QToolButton;
    this->m_tbReturn->setText(tr("返回"));
    this->m_tbReturn->setIcon(QIcon(":/LoginManager/images/LoginManager/Return.png"));
    this->m_tbReturn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(m_llFailIcon);
    this->m_hLayout->addWidget(m_llFailMsg);
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(m_tbReturn);
    this->setLayout(this->m_hLayout);

    connect(this->m_tbReturn,SIGNAL(clicked(bool)),this,SIGNAL(ZSignalReturn()));
}
ZLoginFailPart::~ZLoginFailPart()
{
    delete this->m_llFailIcon;
    delete this->m_llFailMsg;
    delete this->m_tbReturn;
    delete this->m_hLayout;
}
void ZLoginFailPart::ZSetFailMsg(QString msg)
{
    this->m_llFailMsg->setText(msg);
}

PLoginManager::PLoginManager(QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Emitting_Signal,parent)
{
    this->setWindowTitle(tr("BePMS管控系统登录-V%1").arg(MyUserInfo::ZGetInstance()->m_appVersion));
    this->setWindowIcon(QIcon(":/TaskBar/images/PMS.png"));

    this->m_llBanner=new QLabel;
    this->m_llBanner->setPixmap(QPixmap(":/LoginManager/images/LoginManager/Banner.png"));

    this->m_loginPart=new ZLoginPart;
    this->m_waitingPart=new ZWaitingPart;
    this->m_loginFailPart=new ZLoginFailPart;
    this->m_llInfo=new QLabel;
    this->m_llInfo->setMargin(8);
    this->m_llInfo->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    this->m_llInfo->setText(tr("捷温汽车系统(中国)有限公司\t\t柘园生物技术支持"));

    this->m_stackedWidget=new QStackedWidget;
    this->m_stackedWidget->addWidget(this->m_loginPart);
    this->m_stackedWidget->addWidget(this->m_waitingPart);
    this->m_stackedWidget->addWidget(this->m_loginFailPart);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->setMargin(0);
    this->m_vLayout->setSpacing(0);
    this->m_vLayout->addWidget(this->m_llBanner);
    this->m_vLayout->addWidget(this->m_stackedWidget);
    this->m_vLayout->addWidget(this->m_llInfo);
    this->setLayout(this->m_vLayout);

    this->m_stackedWidget->setCurrentWidget(this->m_loginPart);

    connect(this->m_loginPart,SIGNAL(ZSignalDoLogin()),this,SLOT(ZSlotDoLogin()));
    connect(this->m_loginPart,SIGNAL(ZSignalDoExit()),this,SLOT(ZSlotDoExit()));
    connect(this->m_loginFailPart,SIGNAL(ZSignalReturn()),this,SLOT(ZSlotShowLoginPart()));

    connect(this,SIGNAL(ZSignalOpFinished(qint32)),this,SLOT(ZSlotLoginOpFinished(qint32)));

    this->ZLoadUserList();
}
PLoginManager::~PLoginManager()
{
    delete this->m_llBanner;
    delete this->m_loginPart;
    delete this->m_waitingPart;
    delete this->m_loginFailPart;
    delete this->m_stackedWidget;
    delete this->m_llInfo;
    delete this->m_vLayout;
}
void PLoginManager::ZSlotDoLogin()
{

    this->m_stackedWidget->setCurrentWidget(this->m_waitingPart);

    PNetFrame_Login *netFrm=new PNetFrame_Login;
    netFrm->ZLogin(this->m_loginPart->m_cbUserName->currentText().trimmed(),this->m_loginPart->m_lePassword->text().trimmed());

    this->m_netFrmQueue.enqueue(netFrm);
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
}
void PLoginManager::ZSlotDoExit()
{
    this->reject();
}
void PLoginManager::ZSlotLoginOpFinished(qint32 retCode)
{
    if(retCode<0)
    {
        this->m_loginFailPart->ZSetFailMsg(tr("登录超时!\n无法连接到服务器:%1:%2!\n请检测网络连接状态!").arg(MyUserInfo::ZGetInstance()->m_PMSIp).arg(MyUserInfo::ZGetInstance()->m_PMSPort));
        this->m_stackedWidget->setCurrentWidget(this->m_loginFailPart);
    }
}
void PLoginManager::ZParseAckNetFrmXmlData()
{
    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Login"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="login")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    if(retCode<0)
                    {
                        //login failed.
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        this->m_loginFailPart->ZSetFailMsg(tr("登录失败!\n错误信息:[%1].").arg(errMsg));
                        this->m_stackedWidget->setCurrentWidget(this->m_loginFailPart);
                    }else{
                        //login success.
                        QString roleName=attr.value(QString("roleName")).toString();
                        QString realName=attr.value(QString("realName")).toString();
                        QString sex=attr.value(QString("sex")).toString();
                        QString mobile=attr.value(QString("mobile")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        QString permBits=attr.value(QString("permBits")).toString();
                        QString userName=tXmlReader.readElementText();
                        //qDebug()<<roleName<<realName<<sex<<mobile<<creator<<createTime<<permBits<<userName;
                        //save my info in global variable.
                        MyUserInfo::ZGetInstance()->m_UserInfo.m_userName=userName;
                        MyUserInfo::ZGetInstance()->m_UserInfo.m_roleName=roleName;
                        MyUserInfo::ZGetInstance()->m_UserInfo.m_realName=realName;
                        MyUserInfo::ZGetInstance()->m_UserInfo.m_Creator=creator;
                        MyUserInfo::ZGetInstance()->m_UserInfo.m_CreateTime=createTime;
                        MyUserInfo::ZGetInstance()->m_UserInfo.m_sex=sex;
                        QStringList permBitsList=permBits.split(",");
                        MyUserInfo::ZGetInstance()->m_RoleInfo.m_userManagerPerm=permBitsList.at(0).toInt();
                        MyUserInfo::ZGetInstance()->m_RoleInfo.m_templateEditPerm=permBitsList.at(1).toInt();
                        MyUserInfo::ZGetInstance()->m_RoleInfo.m_fileManagerPerm=permBitsList.at(2).toInt();
                        MyUserInfo::ZGetInstance()->m_RoleInfo.m_processEditPerm=permBitsList.at(3).toInt();
                        MyUserInfo::ZGetInstance()->m_RoleInfo.m_taskManagerPerm=permBitsList.at(4).toInt();
                        MyUserInfo::ZGetInstance()->m_RoleInfo.m_formDesignerPerm=permBitsList.at(5).toInt();
                        //save current user into user list file.
                        bool bExists=false;
                        for(qint32 i=0;i<this->m_loginPart->m_cbUserName->count();i++)
                        {
                            if(this->m_loginPart->m_cbUserName->itemText(i)==userName)
                            {
                                bExists=true;
                                break;
                            }
                        }
                        if(!bExists)
                        {
                            this->m_loginPart->m_cbUserName->addItem(userName);
                            this->ZSaveUserList();
                        }
                        this->accept();
                    }
                }
            }//Login.
        }//StarElement.
    }//while().
}
void PLoginManager::ZSlotShowLoginPart()
{
    this->m_stackedWidget->setCurrentWidget(this->m_loginPart);
}
void PLoginManager::ZLoadUserList()
{
    QFile tFile(QDir::currentPath()+"/PMSUser.xml");
    if(!tFile.open(QIODevice::ReadOnly))
    {
        return;
    }
    QString tUserXmlData(tFile.readAll());
    if(!tUserXmlData.isEmpty())
    {
        QXmlStreamReader tXmlReader(tUserXmlData);
        while(!tXmlReader.atEnd())
        {
            QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
            if(tTokenType==QXmlStreamReader::StartElement)
            {
                QString nodeName=tXmlReader.name().toString();
                if(nodeName==QString("User"))
                {
                    QString userName=tXmlReader.readElementText();
                    if(!userName.isEmpty())
                    {
                        this->m_loginPart->m_cbUserName->addItem(userName);
                    }
                }//User.
            }//StarElement.
        }//while().
    }
    tFile.close();
}
void PLoginManager::ZSaveUserList()
{
    QFile tFile(QDir::currentPath()+"/PMSUser.xml");
    if(!tFile.open(QIODevice::WriteOnly))
    {
        return;
    }
    QByteArray tUserXmlData;
    QXmlStreamWriter  tXmlWriter(&tUserXmlData);
    tXmlWriter.setAutoFormatting(true);
    tXmlWriter.writeStartDocument();
    tXmlWriter.writeStartElement(QString("NetPro"));
    tXmlWriter.writeAttribute(QString("dest"),QString("User"));
    for(qint32 i=0;i<this->m_loginPart->m_cbUserName->count();i++)
    {
        tXmlWriter.writeStartElement(QString("User"));
        tXmlWriter.writeCharacters(this->m_loginPart->m_cbUserName->itemText(i));
        tXmlWriter.writeEndElement();//User.
    }
    tXmlWriter.writeEndElement();//NetPro
    tXmlWriter.writeEndDocument();
    tFile.write(tUserXmlData);
    tFile.close();
}
void PLoginManager::ZLockUserName(QString userName)
{
    this->m_loginPart->m_cbUserName->setCurrentText(userName);
    this->m_loginPart->m_cbUserName->setEnabled(false);
}
