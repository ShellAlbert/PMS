#include "pmainwin.h"
#include <QDateTime>
PMainWin::PMainWin(QWidget *parent)
    : QWidget(parent)
{
    this->m_llBanner=new QLabel;
    //this->m_llBanner->setPixmap(QPixmap(":/images/images/banner.png"));
    this->m_treeWidget=new QTreeWidget;
    this->m_treeWidget->setColumnCount(4);
    QStringList headerList;
    headerList<<tr("客户端IP");
    headerList<<tr("登录用户");
    headerList<<tr("登录时间");
    headerList<<tr("刷新时间");
    this->m_treeWidget->setHeaderLabels(headerList);
    this->m_textEdit=new QTextEdit;
    this->m_textEdit->setStyleSheet("QTextEdit{background-color:black;color:white;}");

    this->m_split=new QSplitter(Qt::Vertical);
    this->m_split->addWidget(this->m_treeWidget);
    this->m_split->addWidget(this->m_textEdit);
    this->m_split->setStretchFactor(0,8);
    this->m_split->setStretchFactor(1,2);
    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->setMargin(0);
    this->m_vLayout->addWidget(this->m_llBanner);
    this->m_vLayout->addWidget(this->m_split);
    this->setLayout(this->m_vLayout);
}

PMainWin::~PMainWin()
{
    delete this->m_llBanner;
    delete this->m_treeWidget;
    delete this->m_textEdit;
    delete this->m_split;
    delete this->m_vLayout;
}
void PMainWin::ZSlotShowLogMsg(QString logMsg)
{
    if(logMsg.isEmpty())
    {
        return;
    }
    QString oldLogMsg=this->m_textEdit->toPlainText();
    this->m_textEdit->setText(QDateTime::currentDateTime().toString("[yyyy-MM-dd_hh:mm:ss],")+logMsg+"\n"+oldLogMsg);
}
void PMainWin::ZSlotUserLogin(QString addr,QString userName)
{
    QTreeWidgetItem *item=new QTreeWidgetItem;
    item->setText(0,addr);
    item->setText(1,userName);
    item->setText(2,QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss"));
    this->m_treeWidget->addTopLevelItem(item);
}
void PMainWin::ZSlotUserLogout(QString addr,QString userName)
{
    for(qint32 i=0;i<this->m_treeWidget->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=this->m_treeWidget->topLevelItem(i);
        if(item->text(0)==addr && item->text(1)==userName)
        {
            this->m_treeWidget->takeTopLevelItem(i);
            delete item;
            item=NULL;
            break;
        }
    }
}
void PMainWin::ZSlotHeartBeat(QString addr,QString userName)
{
    for(qint32 i=0;i<this->m_treeWidget->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=this->m_treeWidget->topLevelItem(i);
        if(item->text(0)==addr && item->text(1)==userName)
        {
            item->setText(3,QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss"));
            break;
        }
    }
}
