#include "zuserinfodia.h"
#include "pgblpara.h"
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QDebug>
ZUserInfoDia::ZUserInfoDia(UserInfoDiaType type,QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{

    this->setMinimumSize(400,200);
    this->setStyleSheet("QDialog{background-color:#cce5f9;}");

    this->m_lblUserName=new QLabel(tr("用户名称(*)"));
    this->m_letUserName=new QLineEdit;

    this->m_lblRealName=new QLabel(tr("真实姓名"));
    this->m_letRealName=new QLineEdit;

    this->m_lblGrps=new QLabel(tr("分配角色"));
    this->m_cbbGrps=new QComboBox;
    this->m_cbbGrps->setEnabled(false);

    this->m_lblSex=new QLabel(tr("性别"));
    this->m_rbMale=new QRadioButton;
    this->m_rbMale->setText(tr("男"));
    this->m_rbFemale=new QRadioButton;
    this->m_rbFemale->setText(tr("女"));
    this->m_brpSex=new QButtonGroup;
    this->m_brpSex->addButton(this->m_rbMale);
    this->m_brpSex->addButton(this->m_rbFemale);
    this->m_rbMale->setChecked(true);

    this->m_lblPass=new QLabel(tr("登录密码(*)"));
    this->m_letPass=new QLineEdit;
    this->m_letPass->setEchoMode(QLineEdit::Password);
    this->m_letPass->setMaxLength(12);

    this->m_lblMobile=new QLabel(tr("手机号码"));
    this->m_letMobile=new QLineEdit;

    this->m_btnOkay=new QToolButton;
    this->m_btnOkay->setText(tr("确认"));
    this->m_btnCancel=new QToolButton;
    this->m_btnCancel->setText(tr("取消"));
    this->m_btnOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_btnOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_btnCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_lblUserName,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_letUserName,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_lblRealName,0,2,1,1);
    this->m_gridLayout->addWidget(this->m_letRealName,0,3,1,1);
    this->m_gridLayout->addWidget(this->m_lblGrps,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbbGrps,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_lblSex,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_rbMale,2,1,1,1);
    this->m_gridLayout->addWidget(this->m_rbFemale,2,2,1,1);

    this->m_gridLayout->addWidget(this->m_lblPass,3,0,1,1);
    this->m_gridLayout->addWidget(this->m_letPass,3,1,1,3);

    this->m_gridLayout->addWidget(this->m_lblMobile,4,0,1,1);
    this->m_gridLayout->addWidget(this->m_letMobile,4,1,1,3);

    this->m_gridLayout->addWidget(this->m_btnOkay,5,2,1,1);
    this->m_gridLayout->addWidget(this->m_btnCancel,5,3,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_btnOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_btnCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));

    this->m_diaType=type;
    switch(type)
    {
    case Type_NewUser:
        this->setWindowTitle(tr("添加新用户"));
        break;
    case Type_MdyUser:
        this->setWindowTitle(tr("编辑用户"));
        this->m_letUserName->setEnabled(false);
        break;
    case Type_DelUser:
        this->setWindowTitle(tr("删除用户"));
        this->m_letUserName->setEnabled(false);
        this->m_letRealName->setEnabled(false);
        this->m_rbMale->setEnabled(false);
        this->m_rbFemale->setEnabled(false);
        this->m_letPass->setEnabled(false);
        this->m_letMobile->setEnabled(false);
        break;
    default:
        break;
    }
}
ZUserInfoDia::~ZUserInfoDia()
{
    delete this->m_lblUserName;
    delete this->m_letUserName;

    delete this->m_lblRealName;
    delete this->m_letRealName;

    delete this->m_lblGrps;
    delete this->m_cbbGrps;

    delete this->m_lblSex;
    delete this->m_rbMale;
    delete this->m_rbFemale;
    delete this->m_brpSex;

    delete this->m_lblMobile;
    delete this->m_letMobile;

    delete this->m_btnOkay;
    delete this->m_btnCancel;

    delete this->m_gridLayout;
}
QString ZUserInfoDia::ZGetUserName()
{
    return this->m_letUserName->text().trimmed();
}
void ZUserInfoDia::ZSetUserName(QString userName)
{
    this->m_letUserName->setText(userName);
}

QString ZUserInfoDia::ZGetRealName()
{
    return this->m_letRealName->text().trimmed();
}
void ZUserInfoDia::ZSetRealName(QString realName)
{
    this->m_letRealName->setText(realName);
}
QString ZUserInfoDia::ZGetRoleName()
{
    return this->m_cbbGrps->currentText().trimmed();
}
void ZUserInfoDia::ZSetRoleName(QString roleName)
{
    this->m_cbbGrps->addItem(roleName);
}
qint32 ZUserInfoDia::ZGetSex()
{
    return this->m_rbMale->isChecked()?1:0;
}
void ZUserInfoDia::ZSetSex(qint32 sex)
{
    this->m_rbMale->setChecked(sex?true:false);
    this->m_rbFemale->setChecked(sex?false:true);
}

QString ZUserInfoDia::ZGetPassword()
{
    return this->m_letPass->text().trimmed();
}
void ZUserInfoDia::ZSetPassword(QString passwd)
{
    this->m_letPass->setText(passwd);
}

QString ZUserInfoDia::ZGetMobile()
{
    return this->m_letMobile->text().trimmed();
}
void ZUserInfoDia::ZSetMobile(QString mobile)
{
    this->m_letMobile->setText(mobile);
}
void ZUserInfoDia::ZParseAckNetFrmXmlData()
{
    //qDebug()<<"ZUserInfoDia::ParseAckNetFrm:"<<this->m_ackNetFrmXmlData;

    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("User"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString userName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(userName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString realName=attr.value(QString("realName")).toString();
                        QString roleName=attr.value(QString("roleName")).toString();
                        QString sex=attr.value(QString("sex")).toString();
                        QString mobile=attr.value(QString("mobile")).toString();
                        QString password=attr.value(QString("password")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        paraList.append(realName);
                        paraList.append(roleName);
                        paraList.append(sex);
                        paraList.append(mobile);
                        paraList.append(password);
                        paraList.append(creator);
                        paraList.append(createTime);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("user","add",paraList,retCode);
                }else if(cmd=="mdy")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString userName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(userName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString realName=attr.value(QString("realName")).toString();
                        QString roleName=attr.value(QString("roleName")).toString();
                        QString sex=attr.value(QString("sex")).toString();
                        QString mobile=attr.value(QString("mobile")).toString();
                        QString password=attr.value(QString("password")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        paraList.append(realName);
                        paraList.append(roleName);
                        paraList.append(sex);
                        paraList.append(mobile);
                        paraList.append(password);
                        paraList.append(creator);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("user","mdy",paraList,retCode);
                }else if(cmd=="del")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString userName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(userName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString roleName=attr.value(QString("roleName")).toString();
                        paraList.append(roleName);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("user","del",paraList,retCode);
                }
            }//Role.
        }//StarElement.
    }//while().
}
void ZUserInfoDia::ZSlotOkay()
{
    if(MyUserInfo::ZGetInstance()->m_bOnLine==false)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("网络错误,未连接服务器!\n请等待连接服务器成功后再操作!"));
        return;
    }

    switch(this->m_diaType)
    {
    case Type_NewUser:
        if(this->m_letUserName->text().isEmpty())
        {
            QMessageBox::critical(this,tr("错误提示"),tr("用户名不能为空!"));
            return;
        }
        if(this->m_letPass->text().isEmpty())
        {
            QMessageBox::critical(this,tr("错误提示"),tr("登录密码不能为空!"));
            return;
        }
        if(this->m_letPass->text().length()<6)
        {
            QMessageBox::critical(this,tr("错误提示"),tr("登录密码长度不能少于6位并且不能多于12位!\n当前长度:[%1].").arg(this->m_letPass->text().length()));
            return;
        }
        break;
    case Type_MdyUser:
        if(this->m_letPass->text().isEmpty())
        {
            QMessageBox::critical(this,tr("错误提示"),tr("登录密码不能为空!"));
            return;
        }
        if(this->m_letPass->text().length()<6)
        {
            QMessageBox::critical(this,tr("错误提示"),tr("登录密码长度不能少于6位并且不能多于12位!\n当前长度:[%1].").arg(this->m_letPass->text().length()));
            return;
        }
        break;
    case Type_DelUser:
        break;
    default:
        break;
    }

    PNetFrame_User *netFrm=new PNetFrame_User;
    switch(this->m_diaType)
    {
    case Type_NewUser:
        netFrm->ZAddUser(this->ZGetUserName(),this->ZGetRealName(),this->ZGetRoleName(),this->ZGetPassword(),this->ZGetSex()?"male":"female",this->ZGetMobile());
        this->m_waitDia->ZSetTipsMsg(tr("正在添加新用户[%1]").arg(this->ZGetUserName()));
        break;
    case Type_MdyUser:
        netFrm->ZMdyUser(this->ZGetUserName(),this->ZGetRealName(),this->ZGetRoleName(),this->ZGetPassword(),this->ZGetSex()?"male":"female",this->ZGetMobile());
        this->m_waitDia->ZSetTipsMsg(tr("正在修改用户[%1]").arg(this->ZGetUserName()));
        break;
    case Type_DelUser:
        netFrm->ZDelUser(this->ZGetUserName(),this->ZGetRoleName());
        this->m_waitDia->ZSetTipsMsg(tr("正在删除用户[%1]").arg(this->ZGetUserName()));
        break;
    default:
        break;
    }
    this->m_netFrmQueue.enqueue(netFrm);
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
    this->accept();
}
void ZUserInfoDia::ZSlotCancel()
{
    this->reject();
}
