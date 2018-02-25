#include "ztemplateinfodia.h"
#include <QXmlStreamReader>
#include <QDebug>
#include <QMessageBox>
ZTemplateInfoDia::ZTemplateInfoDia(TemplateInfoDiaType type,QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->setMinimumSize(200,100);

    this->m_llTemplateName=new QLabel(tr("模板名称"));
    this->m_leTempalteName=new QLineEdit;
    this->m_leTempalteName->setMaxLength(16);

    this->m_llVarSourcName=new QLabel(tr("变量源名称"));
    this->m_leVarSourceName=new QLineEdit;
    this->m_leVarSourceName->setMaxLength(16);

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
    case Type_NewTemplate:
        this->setWindowTitle(tr("创建新模板"));
        this->m_gridLayout->addWidget(this->m_llTemplateName,0,0,1,1);
        this->m_gridLayout->addWidget(this->m_leTempalteName,0,1,1,1);
        this->m_gridLayout->addWidget(this->m_tbOkay,1,0,1,1);
        this->m_gridLayout->addWidget(this->m_tbCancel,1,1,1,1);
        break;
    case Type_DelTemplate:
        this->setWindowTitle(tr("删除模板"));
        this->m_leTempalteName->setEnabled(false);
        this->m_gridLayout->addWidget(this->m_llTemplateName,0,0,1,1);
        this->m_gridLayout->addWidget(this->m_leTempalteName,0,1,1,1);
        this->m_gridLayout->addWidget(this->m_tbOkay,1,0,1,1);
        this->m_gridLayout->addWidget(this->m_tbCancel,1,1,1,1);
        break;
    case Type_GetTemplate:
        this->setWindowTitle(tr("获取模板"));
        this->m_leTempalteName->setEnabled(false);
        this->m_gridLayout->addWidget(this->m_llTemplateName,0,0,1,1);
        this->m_gridLayout->addWidget(this->m_leTempalteName,0,1,1,1);
        this->m_gridLayout->addWidget(this->m_tbOkay,1,0,1,1);
        this->m_gridLayout->addWidget(this->m_tbCancel,1,1,1,1);
        break;
    case Type_SaveTemplate:
        this->setWindowTitle(tr("保存模板"));
        this->m_leTempalteName->setEnabled(false);
        this->m_gridLayout->addWidget(this->m_llTemplateName,0,0,1,1);
        this->m_gridLayout->addWidget(this->m_leTempalteName,0,1,1,1);
        this->m_gridLayout->addWidget(this->m_tbOkay,1,0,1,1);
        this->m_gridLayout->addWidget(this->m_tbCancel,1,1,1,1);
        break;
    case Type_BindVarSource:
        this->setWindowTitle(tr("绑定变量源"));
        this->m_leTempalteName->setEnabled(false);
        this->m_leVarSourceName->setEnabled(false);
        this->m_gridLayout->addWidget(this->m_llTemplateName,0,0,1,1);
        this->m_gridLayout->addWidget(this->m_leTempalteName,0,1,1,1);
        this->m_gridLayout->addWidget(this->m_llVarSourcName,1,0,1,1);
        this->m_gridLayout->addWidget(this->m_leVarSourceName,1,1,1,1);
        this->m_gridLayout->addWidget(this->m_tbOkay,2,0,1,1);
        this->m_gridLayout->addWidget(this->m_tbCancel,2,1,1,1);
        break;
    case Type_UnbindVarSource:
        this->setWindowTitle(tr("解除绑定变量源"));
        this->m_leTempalteName->setEnabled(false);
        this->m_leVarSourceName->setEnabled(false);
        this->m_gridLayout->addWidget(this->m_llTemplateName,0,0,1,1);
        this->m_gridLayout->addWidget(this->m_leTempalteName,0,1,1,1);
        this->m_gridLayout->addWidget(this->m_llVarSourcName,1,0,1,1);
        this->m_gridLayout->addWidget(this->m_leVarSourceName,1,1,1,1);
        this->m_gridLayout->addWidget(this->m_tbOkay,2,0,1,1);
        this->m_gridLayout->addWidget(this->m_tbCancel,2,1,1,1);
        break;
    default:
        break;
    }

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
}
ZTemplateInfoDia::~ZTemplateInfoDia()
{
    delete this->m_llTemplateName;
    delete this->m_leTempalteName;
    delete this->m_llVarSourcName;
    delete this->m_leVarSourceName;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gridLayout;
}
void ZTemplateInfoDia::ZSetTemplateName(QString name)
{
    this->m_leTempalteName->setText(name);
}
QString ZTemplateInfoDia::ZGetTemplateName()
{
    return this->m_leTempalteName->text().trimmed();
}
void ZTemplateInfoDia::ZSetTemplateXmlData(QString templateXmlDta)
{
    this->m_templateXmlData=templateXmlDta;
}
void ZTemplateInfoDia::ZSetVarSourceName(QString name)
{
    this->m_leVarSourceName->setText(name);
}
QString ZTemplateInfoDia::ZGetVarSourceName()
{
    return this->m_leVarSourceName->text().trimmed();
}
void ZTemplateInfoDia::ZParseAckNetFrmXmlData()
{
    qDebug()<<"ZTemplateInfoDia::ParseAckNetFrm:"<<this->m_ackNetFrmXmlData;

    QXmlStreamReader tXmlReader(this->m_ackNetFrmXmlData);
    while(!tXmlReader.atEnd())
    {
        QXmlStreamReader::TokenType tTokenType=tXmlReader.readNext();
        if(tTokenType==QXmlStreamReader::StartElement)
        {
            QString nodeName=tXmlReader.name().toString();
            if(nodeName==QString("Template"))
            {
                QXmlStreamAttributes attr=tXmlReader.attributes();
                QString cmd=attr.value(QString("cmd")).toString();
                if(cmd=="add")
                {
                    QString creator=attr.value(QString("creator")).toString();
                    QString createTime=attr.value(QString("createTime")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString templateName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(templateName);
                    paraList.append(creator);                   
                    paraList.append(createTime);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("template","add",paraList,retCode);
                }else if(cmd=="del")
                {
                    QString creator=attr.value(QString("creator")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString templateName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(templateName);
                    paraList.append(creator);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("template","del",paraList,retCode);
                }else if(cmd=="get")
                {
                    QString creator=attr.value(QString("creator")).toString();
                    QString data=attr.value(QString("data")).toString();
                    QString fileSize=attr.value(QString("filesize")).toString();
                    QString varSourceData=attr.value(QString("varsource")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString templateName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(templateName);
                    paraList.append(creator);
                    paraList.append(QString(QByteArray::fromBase64(data.toUtf8())));
                    paraList.append(fileSize);
                    paraList.append(QString(QByteArray::fromBase64(varSourceData.toUtf8())));
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("template","get",paraList,retCode);
                }else if(cmd=="save")
                {
                    QString fileSize=attr.value(QString("filesize")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString templateName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(templateName);
                    paraList.append(fileSize);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("template","save",paraList,retCode);
                }else if(cmd=="bind")
                {
                    QString varSource=attr.value(QString("varsource")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString templateName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(templateName);
                    paraList.append(varSource);
                    paraList.append(creator);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("template","bind",paraList,retCode);
                }else if(cmd=="unbind")
                {
                    QString varSource=attr.value(QString("varsource")).toString();
                    QString creator=attr.value(QString("creator")).toString();
                    qint32 retCode=attr.value(QString("retCode")).toInt();
                    QString errMsg=attr.value(QString("errMsg")).toString();
                    QString templateName=tXmlReader.readElementText();
                    QStringList paraList;
                    paraList.append(templateName);
                    paraList.append(varSource);
                    paraList.append(creator);
                    paraList.append(errMsg);
                    this->ZGetAckNetFrmProcessWidget()->ZProcessAckNetFrm("template","unbind",paraList,retCode);
                }
            }//Template.
        }//StarElement.
    }//while().
}
void ZTemplateInfoDia::ZSlotOkay()
{
    if(MyUserInfo::ZGetInstance()->m_bOnLine==false)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("网络错误,未连接服务器!\n请等待连接服务器成功后再操作!"));
        return;
    }
    if(this->m_leTempalteName->text().trimmed().isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("模板名称不能为空!"));
        return;
    }
    PNetFrame_Template *netFrm=new PNetFrame_Template;
    switch(this->m_diaType)
    {
    case Type_NewTemplate:
        netFrm->ZAddTemplate(this->ZGetTemplateName());
        this->m_waitDia->ZSetTipsMsg(tr("正在创建新模板[%1]").arg(this->ZGetTemplateName()));
        break;
    case Type_DelTemplate:
        netFrm->ZDelTemplate(this->ZGetTemplateName());
        this->m_waitDia->ZSetTipsMsg(tr("正在删除模板[%1]").arg(this->ZGetTemplateName()));
        break;
    case Type_GetTemplate:
        netFrm->ZGetTemplate(this->ZGetTemplateName());
        this->m_waitDia->ZSetTipsMsg(tr("正在获取模板[%1]").arg(this->ZGetTemplateName()));
        break;
    case Type_SaveTemplate:
        netFrm->ZSaveTemplate(this->ZGetTemplateName(),this->m_templateXmlData);
        this->m_waitDia->ZSetTipsMsg(tr("正在保存模板[%1]").arg(this->ZGetTemplateName()));
        break;
    case Type_BindVarSource:
        netFrm->ZBindVarSource(this->ZGetTemplateName(),this->ZGetVarSourceName());
        this->m_waitDia->ZSetTipsMsg(tr("正在绑定变量源[%1]到模板[%2]").arg(this->ZGetVarSourceName()).arg(this->ZGetTemplateName()));
        break;
    case Type_UnbindVarSource:
        netFrm->ZUnbindVarSource(this->ZGetTemplateName(),this->ZGetVarSourceName());
        this->m_waitDia->ZSetTipsMsg(tr("正在解除绑定变量源[%1]从模板[%2]").arg(this->ZGetVarSourceName()).arg(this->ZGetTemplateName()));
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
void ZTemplateInfoDia::ZSlotCancel()
{
    this->reject();
}
