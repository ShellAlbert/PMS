#include "zimportroleuserinfodia.h"
#include <QXmlStreamReader>
#include <QDebug>
ZImportRoleUserInfoDia::ZImportRoleUserInfoDia(QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setWindowTitle(tr("导入角色及用户列表"));
    this->m_llMsg=new QLabel(tr("导入角色及用户列表失败!\n命令请求超时!\n请检测网络连接状态和服务器状态!"));
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
ZImportRoleUserInfoDia::~ZImportRoleUserInfoDia()
{
    delete this->m_llMsg;
    delete this->m_tbOkay;
    delete this->m_vLayout;
}
void ZImportRoleUserInfoDia::ZExecuteImportOp(QList<ZRoleInfo> roleList,QList<ZUserInfo> userList)
{
    this->m_waitDia->ZSetTipsMsg(tr("正在导入角色及用户列表"));
    //add role.
    for(qint32 i=0;i<roleList.count();i++)
    {
        PNetFrame_Role *netFrm=new PNetFrame_Role;
        QString permBits=QString("%1,%2,%3,%4,%5,%6").arg(roleList.at(i).m_userManagerPerm).arg(roleList.at(i).m_templateEditPerm).arg(roleList.at(i).m_fileManagerPerm).arg(roleList.at(i).m_processEditPerm).arg(roleList.at(i).m_taskManagerPerm).arg(roleList.at(i).m_formDesignerPerm);
        netFrm->ZAddRole(roleList.at(i).m_roleName,roleList.at(i).m_parentName,permBits,roleList.at(i).m_roleMemo);
        this->m_netFrmQueue.enqueue(netFrm);
    }
    //add user.
    for(qint32 i=0;i<userList.count();i++)
    {
        PNetFrame_User *netFrm=new PNetFrame_User;
        netFrm->ZAddUser(userList.at(i).m_userName,userList.at(i).m_realName,userList.at(i).m_roleName,userList.at(i).m_password,userList.at(i).m_sex,userList.at(i).m_mobile);
        this->m_netFrmQueue.enqueue(netFrm);
    }

    //post the first netFrm.
    PNetFrame *netFrm=this->m_netFrmQueue.dequeue();
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.lock();
    MyNetQueue::ZGetInstance()->m_sendQueue.enqueue(netFrm);
    MyNetQueue::ZGetInstance()->m_mutexSendQueue.unlock();
    MyNetQueue::ZGetInstance()->m_waitDiaMap.insert(netFrm->ZGetNetFrmSerialNo(),this);
}
void ZImportRoleUserInfoDia::ZParseAckNetFrmXmlData()
{
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
                if(cmd=="add")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString roleName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(roleName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString parentName=attr.value(QString("parentName")).toString();
                        QString permBits=attr.value(QString("permBits")).toString();
                        QString roleMemo=attr.value(QString("memo")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        paraList.append(parentName);
                        paraList.append(permBits);
                        paraList.append(roleMemo);
                        paraList.append(creator);
                        paraList.append(createTime);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("role","add",paraList,retCode);
                }
            }else if(nodeName==QString("User"))
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
                }
            }
        }//StarElement.
    }//while().
}
