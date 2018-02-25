#include "zcomboboxdia.h"
#include <QMessageBox>
ZComboBoxDia::ZComboBoxDia(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("组合框列表对话框"));

    this->m_llAddValue=new QLabel(tr("新列表值"));
    this->m_leAddValue=new QLineEdit;
    this->m_tbAdd=new QToolButton;
    this->m_tbAdd->setText(tr("ADD"));
    this->m_tbDel=new QToolButton;
    this->m_tbDel->setText(tr("DEL"));

    this->m_listWidget=new QListWidget;
    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));
    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_llAddValue,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leAddValue,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_tbAdd,0,2,1,1);
    this->m_gridLayout->addWidget(this->m_tbDel,0,3,1,1);
    this->m_gridLayout->addWidget(this->m_listWidget,1,0,1,4);
    this->m_gridLayout->addWidget(this->m_tbOkay,2,2,1,1);
    this->m_gridLayout->addWidget(this->m_tbCancel,2,3,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_tbAdd,SIGNAL(clicked(bool)),this,SLOT(ZSlotAdd()));
    connect(this->m_tbDel,SIGNAL(clicked(bool)),this,SLOT(ZSlotDel()));

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
}
ZComboBoxDia::~ZComboBoxDia()
{
    delete this->m_llAddValue;
    delete this->m_leAddValue;
    delete this->m_tbAdd;
    delete this->m_tbDel;

    delete this->m_listWidget;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gridLayout;
}
QStringList ZComboBoxDia::ZGetValueList()
{
    QStringList valList;
    for(qint32 i=0;i<this->m_listWidget->count();i++)
    {
        QListWidgetItem *item=this->m_listWidget->item(i);
        valList.append(item->text());
    }
    return valList;
}
void ZComboBoxDia::ZSetValueList(QStringList valueList)
{
    for(qint32 i=0;i<valueList.count();i++)
    {
        QListWidgetItem *item=new QListWidgetItem;
        item->setText(valueList.at(i));
        this->m_listWidget->addItem(item);
    }
}
void ZComboBoxDia::ZSlotAdd()
{
    QString name=this->m_leAddValue->text().trimmed();
    if(name.isEmpty())
    {
        return;
    }
    bool bFindIt=false;
    for(qint32 i=0;i<this->m_listWidget->count();i++)
    {
        QListWidgetItem *item=this->m_listWidget->item(i);
        if(item->text()==name)
        {
            bFindIt=true;
            break;
        }
    }
    if(!bFindIt)
    {
        QListWidgetItem *item=new QListWidgetItem;
        item->setText(name);
        this->m_listWidget->addItem(item);
    }
}
void ZComboBoxDia::ZSlotDel()
{
    QListWidgetItem *item=this->m_listWidget->currentItem();
    if(item)
    {
        this->m_listWidget->removeItemWidget(item);
        delete item;
        item=NULL;
    }
}
void ZComboBoxDia::ZSlotOkay()
{
    if(this->ZGetValueList().count()<=0)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("组合框取值列表为空,添加组件将失败!"));
        return;
    }
    this->accept();
}
void ZComboBoxDia::ZSlotCancel()
{
    this->reject();
}
