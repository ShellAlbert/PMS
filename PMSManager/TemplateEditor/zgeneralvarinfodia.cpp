#include "zgeneralvarinfodia.h"
#include <QMessageBox>
ZGeneralVarInfoDia::ZGeneralVarInfoDia(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("普通变量对话框"));
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

    this->m_lblVarRange=new QLabel(tr("取值范围"));
    this->m_lblVarMin=new QLabel(tr("最小值"));
    this->m_letVarMin=new QLineEdit;
    this->m_lblVarMax=new QLabel(tr("最大值"));
    this->m_letVarMax=new QLineEdit;


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

    this->m_gridLayout->addWidget(this->m_lblVarRange,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_lblVarMin,3,0,1,1);
    this->m_gridLayout->addWidget(this->m_letVarMin,3,1,1,1);
    this->m_gridLayout->addWidget(this->m_lblVarMax,3,2,1,1);
    this->m_gridLayout->addWidget(this->m_letVarMax,3,3,1,1);

    this->m_gridLayout->addWidget(this->m_btnOkay,4,2,1,1);
    this->m_gridLayout->addWidget(this->m_btnCancel,4,3,1,1);
    this->setLayout(this->m_gridLayout);

    connect(this->m_btnOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_btnCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));

    connect(this->m_cbbVarType,SIGNAL(currentIndexChanged(QString)),this,SLOT(ZSlotDataTypeChanged(QString)));
}
ZGeneralVarInfoDia::~ZGeneralVarInfoDia()
{
    delete this->m_lblVarName;
    delete this->m_letVarName;

    delete this->m_lblVarType;
    delete this->m_cbbVarType;

    delete this->m_lblVarRange;
    delete this->m_lblVarMin;
    delete this->m_letVarMin;
    delete this->m_lblVarMax;
    delete this->m_letVarMax;

    delete this->m_btnOkay;
    delete this->m_btnCancel;

    delete this->m_gridLayout;
}
void ZGeneralVarInfoDia::ZSlotDataTypeChanged(QString type)
{
    if(type=="Digital")
    {
        this->m_lblVarRange->setVisible(true);
        this->m_lblVarMin->setVisible(true);
        this->m_letVarMin->setVisible(true);
        this->m_lblVarMax->setVisible(true);
        this->m_letVarMax->setVisible(true);
    }else{
        this->m_lblVarRange->setVisible(false);
        this->m_lblVarMin->setVisible(false);
        this->m_letVarMin->setVisible(false);
        this->m_lblVarMax->setVisible(false);
        this->m_letVarMax->setVisible(false);
    }
}
void ZGeneralVarInfoDia::ZSlotOkay()
{
    if(this->m_letVarName->text().isEmpty())
    {
        QMessageBox::critical(this,tr("错误提示"),tr("变量名称不能为空!"));
        return;
    }
    this->accept();
}
void ZGeneralVarInfoDia::ZSlotCancel()
{
    this->reject();
}
QString ZGeneralVarInfoDia::ZGetVarName()
{
    return this->m_letVarName->text().trimmed();
}
void ZGeneralVarInfoDia::ZSetVarName(QString name)
{
    this->m_letVarName->setText(name);
}

QString ZGeneralVarInfoDia::ZGetVarType()
{
    return this->m_cbbVarType->currentText().trimmed();
}
void ZGeneralVarInfoDia::ZSetVarType(QString type)
{
    this->m_cbbVarType->setCurrentText(type);
}
QString ZGeneralVarInfoDia::ZGetVarRule()
{
    if(this->ZGetVarType()=="Digital")
    {
        return QString("%1-X-%2").arg(this->m_letVarMin->text().trimmed()).arg(this->m_letVarMax->text().trimmed());
    }else{
        return QString("X");
    }
}
void ZGeneralVarInfoDia::ZSetVarRule(QString rule)
{

}
