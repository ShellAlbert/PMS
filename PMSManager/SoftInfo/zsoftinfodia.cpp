#include "zsoftinfodia.h"
#include <pgblpara.h>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
ZSoftInfoDia::ZSoftInfoDia(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("软件信息"));
    this->setWindowIcon(QIcon(":/TaskBar/images/SoftInfo.png"));

    this->m_llAppName=new QLabel(tr("软件名称"));
    this->m_leAppName=new QLineEdit;
    this->m_leAppName->setEnabled(false);
    this->m_leAppName->setText(tr("PMS流水线综合管控系统"));

    this->m_llVersion=new QLabel(tr("版本号"));
    this->m_leVersion=new QLineEdit;
    this->m_leVersion->setEnabled(false);
    this->m_leVersion->setText(MyUserInfo::ZGetInstance()->m_appVersion);


    this->m_llMachineNo=new QLabel(tr("机器码"));
    this->m_leMachineNo=new QLineEdit;

    this->m_llRegisterNo=new QLabel(tr("注册码"));
    this->m_teRegisterNo=new QTextEdit;

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llAppName,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leAppName,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_llVersion,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_leVersion,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_llMachineNo,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_leMachineNo,2,1,1,1);
    this->m_gridLayout->addWidget(this->m_llRegisterNo,3,0,1,1);
    this->m_gridLayout->addWidget(this->m_teRegisterNo,4,0,1,2);
    this->m_gridLayout->addWidget(this->m_tbOkay,5,0,1,1);
    this->m_gridLayout->addWidget(this->m_tbCancel,5,1,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));

    //read cpu id.
    this->m_process=new QProcess(this);
    QString cmd=QDir::currentPath()+"/wmic.exe";
    qDebug()<<cmd;
    connect(this->m_process,SIGNAL(finished(int)),this,SLOT(ZSlotReadProcessResult(int)));
    this->m_process->start(cmd,QStringList()<<"cpu"<<"get"<<"ProcessorId");
}
ZSoftInfoDia::~ZSoftInfoDia()
{
    delete this->m_llAppName;
    delete this->m_leAppName;

    delete this->m_llVersion;
    delete this->m_leVersion;

    delete this->m_llMachineNo;
    delete this->m_leMachineNo;

    delete this->m_llRegisterNo;
    delete this->m_teRegisterNo;

    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gridLayout;

    delete this->m_process;
}
void ZSoftInfoDia::ZSlotOkay()
{
    //write register code to disk file.
    //should start app again.
    if(this->m_teRegisterNo->toPlainText().isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("请输入注册码!"));
        return;
    }
    QFile file(QDir::currentPath()+"/reg.no");
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(this->m_teRegisterNo->toPlainText().toUtf8());
        file.close();
        QMessageBox::information(this,tr("操作完成"),tr("注册完成!\n请重新启动软件完成注册!"));
    }
    this->accept();
}
void ZSoftInfoDia::ZSlotCancel()
{
    this->reject();
}
void ZSoftInfoDia::ZSlotReadProcessResult(int exitCode)
{
    if(exitCode==0)
    {
        QString cpuId=this->m_process->readAll();
        qint32 n1=cpuId.indexOf("\r\n");
        qint32 n2=cpuId.lastIndexOf("\r\n");
        qDebug()<<cpuId;
        qDebug()<<n1<<n2;
        QString machineNo=cpuId.mid(n1,n2-n1).trimmed();
        qDebug()<<machineNo;
        this->m_leMachineNo->setText(machineNo);
    }
}
