#include "zforminfodia.h"
#include <QXmlStreamReader>
#include <QDebug>
#include <QMessageBox>
ZFormInfoDia::ZFormInfoDia(FormInfoDiaType type,QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->m_llFormName=new QLabel(tr("报表名称"));
    this->m_leFormName=new QLineEdit;
    this->m_leFormName->setMaxLength(16);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));

    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gridLayout=new QGridLayout;
    this->setLayout(this->m_gridLayout);

    this->m_diaType=type;
    switch(type)
    {
    case Type_NewForm:
        this->setWindowTitle(tr("创建新报表"));
        this->m_gridLayout->addWidget(this->m_llFormName,0,0,1,1);
        this->m_gridLayout->addWidget(this->m_leFormName,0,1,1,1);
        this->m_gridLayout->addWidget(this->m_tbOkay,1,0,1,1);
        this->m_gridLayout->addWidget(this->m_tbCancel,1,1,1,1);
        break;
    case Type_DelForm:
        this->setWindowTitle(tr("删除报表"));
        this->m_leFormName->setEnabled(false);
        this->m_gridLayout->addWidget(this->m_llFormName,0,0,1,1);
        this->m_gridLayout->addWidget(this->m_leFormName,0,1,1,1);
        this->m_gridLayout->addWidget(this->m_tbOkay,1,0,1,1);
        this->m_gridLayout->addWidget(this->m_tbCancel,1,1,1,1);
        break;
    case Type_GetForm:
        this->setWindowTitle(tr("获取报表"));
        this->m_leFormName->setEnabled(false);
        this->m_gridLayout->addWidget(this->m_llFormName,0,0,1,1);
        this->m_gridLayout->addWidget(this->m_leFormName,0,1,1,1);
        this->m_gridLayout->addWidget(this->m_tbOkay,1,0,1,1);
        this->m_gridLayout->addWidget(this->m_tbCancel,1,1,1,1);
        break;
    case Type_SaveForm:
        this->setWindowTitle(tr("保存报表"));
        this->m_leFormName->setEnabled(false);
        this->m_gridLayout->addWidget(this->m_llFormName,0,0,1,1);
        this->m_gridLayout->addWidget(this->m_leFormName,0,1,1,1);
        this->m_gridLayout->addWidget(this->m_tbOkay,1,0,1,1);
        this->m_gridLayout->addWidget(this->m_tbCancel,1,1,1,1);
        break;
    default:
        break;
    }

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
}
ZFormInfoDia::~ZFormInfoDia()
{
    delete this->m_llFormName;
    delete this->m_leFormName;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gridLayout;
}
void ZFormInfoDia::ZSetFormName(QString name)
{
    this->m_leFormName->setText(name);
}
QString ZFormInfoDia::ZGetFormName()
{
    return this->m_leFormName->text().trimmed();
}
void ZFormInfoDia::ZSetFormXmlData(QString data)
{
    this->m_formXmlData=data;
}
void ZFormInfoDia::ZParseAckNetFrmXmlData()
{
    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Form"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString formName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(formName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString creator=attr.value(QString("creator")).toString();
                        QString createTime=attr.value(QString("createTime")).toString();
                        paraList.append(creator);
                        paraList.append(createTime);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("form","add",paraList,retCode);
                }else if(cmd=="del")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString formName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(formName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString creator=attr.value(QString("creator")).toString();
                        paraList.append(creator);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("form","del",paraList,retCode);
                }else if(cmd=="get")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString formName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(formName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString data=attr.value(QString("data")).toString();
                        QString creator=attr.value(QString("creator")).toString();
                        paraList.append(QString(QByteArray::fromBase64(data.toUtf8())));
                        paraList.append(creator);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("form","get",paraList,retCode);
                }else if(cmd=="save")
                {
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString formName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(formName);
                    if(retCode<0)
                    {
                        QString errMsg=attr.value(QString("errMsg")).toString();
                        paraList.append(errMsg);
                    }else{
                        QString fileSize=attr.value(QString("fileSize")).toString();
                        paraList.append(fileSize);
                    }
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("form","save",paraList,retCode);
                }
            }//Form.
        }//StarElement.
    }//while().
}
void ZFormInfoDia::ZSlotOkay()
{
    if(MyUserInfo::ZGetInstance()->m_bOnLine==false)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("网络错误,未连接服务器!\n请等待连接服务器成功后再操作!"));
        return;
    }
    if(this->m_leFormName->text().trimmed().isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("报表名称不能为空!"));
        return;
    }
    PNetFrame_Form *netFrm=new PNetFrame_Form;
    switch(this->m_diaType)
    {
    case Type_NewForm:
        netFrm->ZNewForm(this->ZGetFormName());
        this->m_waitDia->ZSetTipsMsg(tr("正在创建新报表[%1]").arg(this->ZGetFormName()));
        break;
    case Type_DelForm:
        netFrm->ZDelForm(this->ZGetFormName());
        this->m_waitDia->ZSetTipsMsg(tr("正在删除报表[%1]").arg(this->ZGetFormName()));
        break;
    case Type_GetForm:
        netFrm->ZGetForm(this->ZGetFormName());
        this->m_waitDia->ZSetTipsMsg(tr("正在获取报表[%1]").arg(this->ZGetFormName()));
        break;
    case Type_SaveForm:
        netFrm->ZSaveForm(this->ZGetFormName(),this->m_formXmlData);
        this->m_waitDia->ZSetTipsMsg(tr("正在保存报表[%1]").arg(this->ZGetFormName()));
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
void ZFormInfoDia::ZSlotCancel()
{
    this->reject();
}
