#include "zdatacomparedialog.h"
#include <QMessageBox>
ZMinMaxCompareDialog::ZMinMaxCompareDialog(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("最小值/最大值对比"));
    this->m_tree=new QTreeWidget;
    this->m_tree->setColumnCount(3);
    QStringList labels;
    labels<<tr("目标单元格");
    labels<<tr("最小值单元格");
    labels<<tr("最大值单元格");
    this->m_tree->setHeaderLabels(labels);

    this->m_tbAdd=new QToolButton;
    this->m_tbAdd->setText(tr("增加"));
    this->m_tbAdd->setIcon(QIcon(":/common/images/common/add.png"));
    this->m_tbAdd->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbDel=new QToolButton;
    this->m_tbDel->setText(tr("移除"));
    this->m_tbDel->setIcon(QIcon(":/common/images/common/del.png"));
    this->m_tbDel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("确认"));
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("取消"));
    this->m_tbCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_hLayout=new QHBoxLayout;
    this->m_hLayout->addWidget(this->m_tbAdd);
    this->m_hLayout->addWidget(this->m_tbDel);
    this->m_hLayout->addStretch(1);
    this->m_hLayout->addWidget(this->m_tbOkay);
    this->m_hLayout->addWidget(this->m_tbCancel);

    this->m_vLayout=new QVBoxLayout;
    this->m_vLayout->addWidget(this->m_tree);
    this->m_vLayout->addLayout(this->m_hLayout);
    this->setLayout(this->m_vLayout);

    connect(this->m_tbAdd,SIGNAL(clicked(bool)),this,SLOT(ZSlotAdd()));
    connect(this->m_tbDel,SIGNAL(clicked(bool)),this,SLOT(ZSlotDel()));
    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));

    connect(this->m_tree,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ZSlotDoubleClicked(QModelIndex)));
}
ZMinMaxCompareDialog::~ZMinMaxCompareDialog()
{
    delete this->m_tree;
    delete this->m_tbAdd;
    delete this->m_tbDel;
    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_hLayout;
    delete this->m_vLayout;
}
QStringList ZMinMaxCompareDialog::ZGetDestMinMaxPair()
{
    QStringList pair;
    for(qint32 i=0;i<this->m_tree->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=this->m_tree->topLevelItem(i);
        QString destMinMax=item->text(0)+"/"+item->text(1)+"/"+item->text(2);
        pair.append(destMinMax);
    }
    return pair;
}
void ZMinMaxCompareDialog::ZSetDestMinMaxPair(QStringList pair)
{
    for(qint32 i=0;i<pair.size();i++)
    {
        QStringList destMinMaxList=pair.at(i).split("/");
        if(destMinMaxList.size()==3)
        {
            QTreeWidgetItem *item=new QTreeWidgetItem;
            item->setText(0,destMinMaxList.at(0));
            item->setText(1,destMinMaxList.at(1));
            item->setText(2,destMinMaxList.at(2));
            this->m_tree->addTopLevelItem(item);
        }
    }
}
void ZMinMaxCompareDialog::ZSlotAdd()
{
    ZMinMaxAddDia dia(this);
    if(dia.exec()==QDialog::Accepted)
    {
        QTreeWidgetItem *newItem=new QTreeWidgetItem;
        newItem->setText(0,dia.ZGetDestXY());
        newItem->setText(1,dia.ZGetMinXY());
        newItem->setText(2,dia.ZGetMaxXY());
        this->m_tree->addTopLevelItem(newItem);
    }
}
void ZMinMaxCompareDialog::ZSlotDel()
{
    QTreeWidgetItem *item=this->m_tree->currentItem();
    if(item)
    {
        this->m_tree->takeTopLevelItem(this->m_tree->indexOfTopLevelItem(item));
        delete item;
        item=NULL;
    }
}
void ZMinMaxCompareDialog::ZSlotOkay()
{
    this->accept();
}
void ZMinMaxCompareDialog::ZSlotCancel()
{
    this->reject();
}
void ZMinMaxCompareDialog::ZSlotDoubleClicked(QModelIndex index)
{
    QTreeWidgetItem *item=this->m_tree->topLevelItem(index.row());
    if(item)
    {
        emit this->ZSigHighlightCell(item->text(0),item->text(1),item->text(2));
    }
}
/////////////////////////////////
ZMinMaxAddDia::ZMinMaxAddDia(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("增加单元格对"));
    this->m_llDestCell=new QLabel(tr("目标单元格坐标(x,y)"));
    this->m_leDestCell=new QLineEdit;
    this->m_llMinCell=new QLabel(tr("最小值单元格坐标(x,y)"));
    this->m_leMinCell=new QLineEdit;
    this->m_llMaxCell=new QLabel(tr("最大值单元格坐标(x,y)"));
    this->m_leMaxCell=new QLineEdit;

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("确认"));
    this->m_tbOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_tbOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("取消"));
    this->m_tbCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_tbCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gLayout=new QGridLayout;
    this->m_gLayout->addWidget(this->m_llDestCell,0,0,1,1);
    this->m_gLayout->addWidget(this->m_leDestCell,0,1,1,1);

    this->m_gLayout->addWidget(this->m_llMinCell,1,0,1,1);
    this->m_gLayout->addWidget(this->m_leMinCell,1,1,1,1);

    this->m_gLayout->addWidget(this->m_llMaxCell,2,0,1,1);
    this->m_gLayout->addWidget(this->m_leMaxCell,2,1,1,1);

    this->m_gLayout->addWidget(this->m_tbOkay,3,0,1,1);
    this->m_gLayout->addWidget(this->m_tbCancel,3,1,1,1);

    this->setLayout(this->m_gLayout);

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
}
ZMinMaxAddDia::~ZMinMaxAddDia()
{
    delete this->m_llDestCell;
    delete this->m_leDestCell;

    delete this->m_llMinCell;
    delete this->m_leMinCell;

    delete this->m_llMaxCell;
    delete this->m_leMaxCell;

    delete this->m_tbOkay;
    delete this->m_tbCancel;

    delete this->m_gLayout;
}
QString ZMinMaxAddDia::ZGetDestXY()
{
    return this->m_leDestCell->text().trimmed();
}
QString ZMinMaxAddDia::ZGetMinXY()
{
    return this->m_leMinCell->text().trimmed();
}
QString ZMinMaxAddDia::ZGetMaxXY()
{
    return this->m_leMaxCell->text().trimmed();
}
void ZMinMaxAddDia::ZSlotOkay()
{
    //check the format & correction of dest cell.
    QString destXY=this->m_leDestCell->text().trimmed();
    QStringList destXYList=destXY.split(",");
    if(destXYList.size()!=2)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("目标单元格坐标输入不正确!"));
        return;
    }
    QString destXStr=destXYList.at(0);
    QString destYStr=destXYList.at(1);
    bool bOkDestX=false;
    bool bOkDestY=false;
    destXStr.toInt(&bOkDestX);
    destYStr.toInt(&bOkDestY);
    if(!bOkDestX || !bOkDestY)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("目标单元格坐标转换失败!"));
        return;
    }
    //check the format & correction of min cell.
    QString minXY=this->m_leMinCell->text().trimmed();
    QStringList minXYList=minXY.split(",");
    if(minXYList.size()!=2)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("最小值单元格坐标输入不正确!"));
        return;
    }
    QString minXStr=minXYList.at(0);
    QString minYStr=minXYList.at(1);
    bool bOkMinX=false;
    bool bOkMinY=false;
    minXStr.toInt(&bOkMinX);
    minYStr.toInt(&bOkMinY);
    if(!bOkMinX || !bOkMinY)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("最小值单元格坐标转换失败!"));
        return;
    }
    //check the format & correction of max cell.
    QString maxXY=this->m_leMaxCell->text().trimmed();
    QStringList maxXYList=maxXY.split(",");
    if(maxXYList.size()!=2)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("最大值单元格坐标输入不正确!"));
        return;
    }
    QString maxXStr=maxXYList.at(0);
    QString maxYStr=maxXYList.at(1);
    bool bOkMaxX=false;
    bool bOkMaxY=false;
    maxXStr.toInt(&bOkMaxX);
    maxYStr.toInt(&bOkMaxY);
    if(!bOkMaxX || !bOkMaxY)
    {
        QMessageBox::critical(this,tr("错误提示"),tr("最大值单元格坐标转换失败!"));
        return;
    }
    this->accept();
}
void ZMinMaxAddDia::ZSlotCancel()
{
    this->reject();
}

