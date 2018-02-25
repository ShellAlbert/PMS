#include "zautovarinfodia.h"
#include <QMessageBox>
ZAutoVarInfoDia::ZAutoVarInfoDia(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("自动变量对话框"));
    this->setWindowIcon(QIcon(":/TaskBar/images/FileManager.png"));

    this->m_lblVarName=new QLabel(tr("变量名称(*)"));
    this->m_letVarName=new QLineEdit;

    this->m_lblVarType=new QLabel(tr("变量类型"));
    this->m_cbbVarType=new QComboBox;
    QStringList varTypes;
    varTypes<<"Digital";
    varTypes<<"String";
    varTypes<<"Boolean";
    varTypes<<"Datetime";
    this->m_cbbVarType->addItems(varTypes);
    this->m_cbbVarType->setEditable(false);

    this->m_lblVarAction=new QLabel(tr("触发动作"));
    this->m_cbbAction=new QComboBox;
    QStringList actList;
    actList<<tr("@load");
    actList<<tr("@click");
    this->m_cbbAction->addItems(actList);
    this->m_cbbAction->setEditable(false);

    this->m_lblVarActValue=new QLabel(tr("预定义值"));
    this->m_cbbVarActValue=new QComboBox;
    QStringList actTypes;
    actTypes<<tr("@sysdatetime");
    actTypes<<tr("@username");
    actTypes<<tr("@refcell");
    actTypes<<tr("@selfdef");
    this->m_cbbVarActValue->addItems(actTypes);
    this->m_cbbVarActValue->setEditable(false);
    this->m_letVarActValue=new QLineEdit;
    this->m_letVarActValue->setVisible(false);

    this->m_btnOkay=new QToolButton;
    this->m_btnOkay->setText(tr("Okay"));
    this->m_btnCancel=new QToolButton;
    this->m_btnCancel->setText(tr("Cancel"));
    this->m_btnOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_btnOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_btnCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_lblVarName,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_letVarName,0,1,1,1);

    this->m_gridLayout->addWidget(this->m_lblVarType,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbbVarType,1,1,1,1);

    this->m_gridLayout->addWidget(this->m_lblVarAction,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbbAction,2,1,1,1);
    this->m_gridLayout->addWidget(this->m_lblVarActValue,2,2,1,1);
    this->m_gridLayout->addWidget(this->m_cbbVarActValue,2,3,1,1);
    this->m_gridLayout->addWidget(this->m_letVarActValue,2,4,1,1);


    this->m_gridLayout->addWidget(this->m_btnOkay,3,3,1,1);
    this->m_gridLayout->addWidget(this->m_btnCancel,3,4,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_btnOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_btnCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));
    connect(this->m_cbbVarActValue,SIGNAL(currentIndexChanged(QString)),this,SLOT(ZSlotActionValueChanged(QString)));
}
ZAutoVarInfoDia::~ZAutoVarInfoDia()
{
    delete this->m_lblVarName;
    delete this->m_letVarName;

    delete this->m_lblVarType;
    delete this->m_cbbVarType;

    delete this->m_lblVarAction;
    delete this->m_cbbAction;

    delete this->m_lblVarActValue;
    delete this->m_cbbVarActValue;
    delete this->m_letVarActValue;

    delete this->m_btnOkay;
    delete this->m_btnCancel;

    delete this->m_gridLayout;
}
void ZAutoVarInfoDia::ZSlotActionValueChanged(QString text)
{
    if(text=="@selfdef" || text=="@refcell")
    {
        this->m_letVarActValue->setVisible(true);
    }else{
        this->m_letVarActValue->setVisible(false);
    }
}
void ZAutoVarInfoDia::ZSlotOkay()
{
    if(this->m_letVarName->text().isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("变量名称不能为空!"));
        return;
    }
    if(this->m_cbbVarActValue->currentText()=="@selfdef" && this->m_letVarActValue->text().isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("变量预定义值不能为空!"));
        return;
    }
    if(this->m_cbbVarActValue->currentText()==tr("@refcell") && this->m_letVarActValue->text().isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("引用目标单元格地址不能为空!"));
        return;
    }
    this->accept();
}
void ZAutoVarInfoDia::ZSlotCancel()
{
    this->reject();
}
QString ZAutoVarInfoDia::ZGetVarName()
{
    return this->m_letVarName->text().trimmed();
}
void ZAutoVarInfoDia::ZSetVarName(QString name)
{
    this->m_letVarName->setText(name);
}
QString ZAutoVarInfoDia::ZGetVarType()
{
    return this->m_cbbVarType->currentText().trimmed();
}
void ZAutoVarInfoDia::ZSetVarType(QString type)
{
    this->m_cbbVarType->setCurrentText(type);
}
QString ZAutoVarInfoDia::ZGetVarAction()
{
    return this->m_cbbAction->currentText().trimmed();
}
void ZAutoVarInfoDia::ZSetVarAction(QString act)
{
    this->m_cbbAction->setCurrentText(act);
}
QString ZAutoVarInfoDia::ZGetActionValue()
{
    QString actValue;
    if(this->m_cbbVarActValue->currentText()=="@refcell")
    {
         actValue=QString("@refcell:%1").arg(this->m_letVarActValue->text().trimmed());
    }else if(this->m_cbbVarActValue->currentText()=="@selfdef")
    {
        actValue=QString("@selfdef:%1").arg(this->m_letVarActValue->text().trimmed());
    }else{
        actValue=this->m_cbbVarActValue->currentText();
    }
    return actValue;
}
void ZAutoVarInfoDia::ZSetActionValue(QString value)
{
    if(value.startsWith("@refcell"))
    {
        this->m_cbbVarActValue->setCurrentText("@refcell");
        QStringList paraList=value.split(":");
        this->m_letVarActValue->setText(paraList.at(1));
    }else if(value.startsWith("@selfdef"))
    {
        this->m_cbbVarActValue->setCurrentText("@selfdef");
        QStringList paraList=value.split(":");
        this->m_letVarActValue->setText(paraList.at(1));
    }else{
        this->m_cbbVarActValue->setCurrentText(value);
    }
}
