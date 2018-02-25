#include "ztablewidget.h"
ZTableDialog::ZTableDialog(QWidget *parent):ZBaseInfoDia(ZBaseInfoDia::Dialog_End_By_Calling_Close,parent)
{
    this->m_tree=new QTreeWidget;
    this->m_tree->setColumnCount(3);
    QStringList header;
    header<<tr("列标题");
    header<<tr("数据源");
    header<<tr("过滤条件");
    this->m_tree->setHeaderLabels(header);
    this->m_tbAddCol=new QToolButton;
    this->m_tbMdyCol=new QToolButton;
    this->m_tbDelCol=new QToolButton;
    this->m_tbOkayCol=new QToolButton;
    this->m_tbCancelCol=new QToolButton;
    this->m_hLayout=new QHBoxLayout;

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_tree);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);
}
ZTableDialog::~ZTableDialog()
{
    delete this->m_tree;
    delete this->m_tbAddCol;
    delete this->m_tbMdyCol;
    delete this->m_tbDelCol;
    delete this->m_tbOkayCol;
    delete this->m_tbCancelCol;
    delete this->m_hLayout;
    delete this->m_vLayout;
}

ZTableWidget::ZTableWidget()
{
    this->m_tableWidget=new QTableWidget;
    this->m_tableWidget->setColumnCount(6);
    this->m_tableWidget->setRowCount(3);
    this->m_vLayout->addWidget(this->m_tableWidget);
}
ZTableWidget::~ZTableWidget()
{
    delete this->m_tableWidget;
}
void ZTableWidget::ZOpenAttributeDialog()
{
    ZTableDialog dia;
    if(dia.exec()==QDialog::Accepted)
    {

    }
}
