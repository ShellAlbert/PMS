#include "zlogmanager.h"
#include <QDateTime>
#include <QIcon>
ZLogManager::ZLogManager(QWidget *parent):QFrame(parent)
{
    this->setWindowTitle(tr("系统日志-System Log Message"));
    this->setWindowIcon(QIcon(":/TaskBar/images/SysLog.png"));
    this->m_textEdit=new QTextEdit;
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_textEdit);
    this->setLayout(this->m_vLayout);

    this->m_textEdit->setStyleSheet("QTextEdit{background-color:black;color:white;}");
}
ZLogManager::~ZLogManager()
{
    delete this->m_textEdit;
    delete this->m_vLayout;
}
void ZLogManager::closeEvent(QCloseEvent *event)
{
    event->ignore();
}
void ZLogManager::ZSlotAddLogMsg(QString logMsg)
{
    QString tOldLog=this->m_textEdit->toPlainText();
    this->m_textEdit->setText(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss],")+logMsg+"\n"+tOldLog);
}
