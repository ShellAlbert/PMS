#include "pupdatemanager.h"
#include <pgblpara.h>
#include <QDataStream>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QDateTime>
PUpdateManager::PUpdateManager(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("PMS系统在线升级"));

    this->m_bar=new QProgressBar;
    this->m_bar->setMaximum(0);
    this->m_llInfo=new QLabel;
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_bar);
    this->m_vLayout->addWidget(this->m_llInfo);
    this->setLayout(this->m_vLayout);

    this->m_byteWritten=0;
    this->m_nextBlockSize=0;

    this->m_tcpSocket=new QTcpSocket;
    this->m_tcpSocket->connectToHost(MyUserInfo::ZGetInstance()->m_PMSIp,MyUserInfo::ZGetInstance()->m_PMSPort+1);
    connect(this->m_tcpSocket,SIGNAL(readyRead()),this,SLOT(ZSlotCommunicate()));
    connect(this->m_tcpSocket,SIGNAL(disconnected()),this,SLOT(ZSlotDisconnect()));
}
PUpdateManager::~PUpdateManager()
{
    delete this->m_bar;
    delete this->m_llInfo;
    delete this->m_vLayout;
}
void PUpdateManager::ZSlotDisconnect()
{
    this->m_tcpSocket->deleteLater();
    this->reject();
}
void PUpdateManager::ZSlotCommunicate()
{
    QDataStream ds(this->m_tcpSocket);
    ds.setVersion(QDataStream::Qt_5_6);
    while(1)
    {
        qint32 bytes=(qint32)(this->m_tcpSocket->bytesAvailable());
        this->m_byteWritten+=bytes;
        if(this->m_bar->maximum())
        {
            this->m_bar->setValue(bytes);
        }
        if(this->m_nextBlockSize==0)
        {
            if(quint64(bytes)<sizeof(quint64))
            {
                break;
            }
            //total data size.
            ds>>this->m_nextBlockSize;
            this->m_bar->setMaximum((int)this->m_nextBlockSize);
            this->show();
        }
        if(quint64(bytes)<this->m_nextBlockSize)
        {
            break;
        }
        //protocol.
        quint16 protocol;
        ds>>protocol;
        switch(protocol)
        {
        case 0x0001:
        {
            ds>>this->m_versionS;
            if(this->m_version==this->m_versionS)
            {
                QMessageBox::information(this,tr("升级提示"),tr("当前版本已经是最新的啦!"));
                this->accept();
            }else{
                QByteArray block;
                QDataStream out(&block,QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_5_6);
                out<<quint64(0)<<quint16(0x0001);
                out.device()->seek(0);
                out<<quint64(block.size()-sizeof(quint64));
                this->m_tcpSocket->write(block);
            }
        }
            break;
        case 0x0002:
        {
            QByteArray block1;
            QByteArray block2;
            ds>>block1>>block2;
            QFile file("PMS.exe");
            if(file.open(QIODevice::WriteOnly))
            {
                if(block1.length()!=0)
                {
                    file.write(block1);
                }
                file.close();
            }
            //write version file.
            QFile versionFile(QDir::currentPath()+"/version");
            if(versionFile.open(QIODevice::WriteOnly))
            {
                versionFile.write(this->m_versionS.toUtf8());
                versionFile.write("\r\n");
                versionFile.write(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toUtf8());
                versionFile.close();
            }
            QMessageBox::information(this,tr("升级成功"),"软件版本从"+this->m_version+"升级到"+this->m_versionS);
            this->accept();
        }
            break;
        default:
            break;
        }
        this->m_nextBlockSize=0;
    }
}
