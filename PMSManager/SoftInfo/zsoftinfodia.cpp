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
    this->m_leAppName->setFocusPolicy(Qt::NoFocus);
    this->m_leAppName->setText(tr("PMS流水线综合管控系统"));

    this->m_llVersion=new QLabel(tr("版本号"));
    this->m_leVersion=new QLineEdit;
    this->m_leVersion->setFocusPolicy(Qt::NoFocus);
    this->m_leVersion->setText(MyUserInfo::ZGetInstance()->m_appVersion);

    this->m_llCompileDate=new QLabel(tr("编译日期"));
    this->m_leCompileDate=new QLineEdit;
    this->m_leCompileDate->setFocusPolicy(Qt::NoFocus);
    this->m_leCompileDate->setText(QString("%1 %2").arg(__DATE__).arg(__TIME__));

    this->m_llCopyright=new QLabel(tr("版权所有"));
    this->m_leCopyright=new QLineEdit;
    this->m_leCopyright->setFocusPolicy(Qt::NoFocus);
    this->m_leCopyright->setText(tr("北京柘园生物设备有限公司"));

    this->m_llMachineNo=new QLabel(tr("机器码"));
    this->m_leMachineNo=new QLineEdit;
    this->m_leMachineNo->setFocusPolicy(Qt::NoFocus);

    this->m_llRegisterNo=new QLabel(tr("注册码"));
    this->m_teRegisterNo=new QTextEdit;


    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llAppName,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leAppName,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_llVersion,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_leVersion,1,1,1,1);
    this->m_gridLayout->addWidget(this->m_llCompileDate,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_leCompileDate,2,1,1,1);
    this->m_gridLayout->addWidget(this->m_llCopyright,3,0,1,1);
    this->m_gridLayout->addWidget(this->m_leCopyright,3,1,1,1);
    this->m_gridLayout->addWidget(this->m_llMachineNo,4,0,1,1);
    this->m_gridLayout->addWidget(this->m_leMachineNo,4,1,1,1);
    this->m_gridLayout->addWidget(this->m_llRegisterNo,5,0,1,1);
    this->m_gridLayout->addWidget(this->m_teRegisterNo,6,0,1,2);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("OKAY"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("CANCEL"));
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_tbCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_tbOkay);
    this->m_hLayout->addWidget(this->m_tbCancel);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addLayout(this->m_gridLayout);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));

    //read cpu id.
    this->m_process=new QProcess(this);
    QString cmd=QDir::currentPath()+"/bin/wmic.exe";
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

    delete this->m_llCompileDate;
    delete this->m_leCompileDate;

    delete this->m_llCopyright;
    delete this->m_leCopyright;

    delete this->m_llMachineNo;
    delete this->m_leMachineNo;

    delete this->m_llRegisterNo;
    delete this->m_teRegisterNo;

    delete this->m_gridLayout;

    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayout;

    delete this->m_vLayout;

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
