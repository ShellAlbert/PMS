#include "zlistroleuserinfodia.h"
#include <QXmlStreamReader>
#include <QDebug>
ZListRoleUserInfoDia::ZListRoleUserInfoDia(QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setWindowTitle(tr("获取角色及用户列表"));
    this->m_llMsg=new QLabel(tr("获取角色及用户列表失败!\n命令请求超时!\n请检测网络连接状态和服务器状态!"));
    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("CLOSE"));
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_llMsg);
    this->m_vLayout->addWidget(this->m_tbOkay);
    this->setLayout(this->m_vLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(reject()));
}
ZListRoleUserInfoDia::~ZListRoleUserInfoDia()
{
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_vLayout;
}
void ZListRoleUserInfoDia::ZExecuteListOp()
{
    PNetFrame_Role *netFrm=new PNetFrame_Role;
    netFrm->ZListRole();
    this->m_waitDia->ZSetTipsMsg(tr("正在获取角色及用户列表..."));
    this->m_netFrmQueue.enqueue(netFrm);


    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(this->m_netFrmQueue.dequeue());
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
}
void ZListRoleUserInfoDia::ZParseAckNetFrmXmlData()
{
    //qDebug()<<"ZListRoleUserInfoDia::ParseAckNetFrm:"<<this->m_ackNetFrmXmlData;

    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Role"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="list")
                {
                    QString item=attr.value(QString("item")).toString();
                    if(item=="role")
                    {
                        QString parentName=attr.value(QString("parentName")).toString();
                        QString permBits=attr.value(QString("permBits")).toString();
                        QString roleMemo=attr.value(QString("roleMemo")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        QString roleName=tXmlReader.readElementText();
                        QStringList paraList;
                        paraList.append(roleName);
                        paraList.append(parentName);
                        paraList.append(permBits);
                        paraList.append(roleMemo);
                        paraList.append(creator);
                        paraList.append(createTime);
                        this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("role","list",paraList,0);
                    }else if(item=="user")
                    {
                        QString roleName=attr.value(QString("roleName")).toString();
                        QString realName=attr.value(QString("realName")).toString();
                        QString sex=attr.value(QString("sex")).toString();
                        QString mobile=attr.value(QString("mobile")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        QString lastLoginTime=attr.value(QString("lastLoginTime")).toString();
                        QString userName=tXmlReader.readElementText();
                        QStringList paraList;
                        paraList.append(userName);
                        paraList.append(roleName);
                        paraList.append(realName);
                        paraList.append(sex);
                        paraList.append(mobile);
                        paraList.append(creator);
                        paraList.append(createTime);
                        paraList.append(lastLoginTime);
                        this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("user","list",paraList,0);
                    }
                }//list.
            }//Role.
        }//StarElement.
    }//while().
}
