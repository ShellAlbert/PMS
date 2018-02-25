#include "zsyspicdia.h"

ZSysPicDia::ZSysPicDia(QString prefix,QWidget *parent):QDialog(parent)
{
    this->setMinimumSize(400,200);
    this->setWindowTitle(tr("系统图库"));

    this->m_llPicPath=new QLabel;
    this->m_listWidget=new QListWidget;
    this->m_listWidget->setViewMode(QListView::IconMode);
    this->m_listWidget->setMovement(QListView::Static);
    this->m_listWidget->setResizeMode(QListView::Adjust);
    this->m_listWidget->setIconSize(QSize(48,48));
    this->m_btnOkay=new QToolButton;
    this->m_btnOkay->setText(tr("确认"));
    this->m_btnCancel=new QToolButton;
    this->m_btnCancel->setText(tr("取消"));
    this->m_btnOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_btnOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_btnCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_hLayoutBtn=new QHBoxLayout;
    this->m_hLayoutBtn->addWidget(this->m_btnOkay);
    this->m_hLayoutBtn->addWidget(this->m_btnCancel);

    this->m_vLayoutMain=new QVBoxLayout;
    this->m_vLayoutMain->addWidget(this->m_llPicPath);
    this->m_vLayoutMain->addWidget(this->m_listWidget);
    this->m_vLayoutMain->addLayout(this->m_hLayoutBtn);
    this->setLayout(this->m_vLayoutMain);

    connect(this->m_btnOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_btnCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));

    this->ZLoadSysPic(prefix);
}
ZSysPicDia::~ZSysPicDia()
{
    delete this->m_llPicPath;
    delete this->m_listWidget;
    delete this->m_btnOkay;
    delete this->m_btnCancel;
    delete this->m_hLayoutBtn;
    delete this->m_vLayoutMain;
}
void ZSysPicDia::ZSlotOkay()
{
    this->accept();
}
void ZSysPicDia::ZSlotCancel()
{
    this->reject();
}
void ZSysPicDia::ZLoadSysPic(QString prefix)
{
    this->m_pathPrefix=prefix;
    this->m_llPicPath->setText(tr("系统图库路径:%1").arg(prefix));
    for(qint32 i=1;i<=50;i++)
    {
        QString name=QString(":/%1/images/%2/%3.png").arg(prefix).arg(prefix).arg(i);
        QListWidgetItem *item=new QListWidgetItem(QIcon(name),QString("%1.png").arg(i));
        this->m_listWidget->addItem(item);
    }
}
QString ZSysPicDia::ZGetSelectedPic()
{
    QListWidgetItem *item=this->m_listWidget->currentItem();
    if(item)
    {
        return QString(":/%1/images/%2/%3").arg(this->m_pathPrefix).arg(this->m_pathPrefix).arg(item->text());
    }
    return QString("null");
}
