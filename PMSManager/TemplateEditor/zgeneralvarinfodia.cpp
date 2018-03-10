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

    //for Digital.
    this->m_lblVarRange=new QLabel(tr("取值范围"));
    this->m_lblVarMin=new QLabel(tr("最小值"));
    this->m_letVarMin=new QLineEdit;
    this->m_lblVarMax=new QLabel(tr("最大值"));
    this->m_letVarMax=new QLineEdit;

    //for String.
    this->m_lblRefValue=new QLabel(tr("参考值"));
    this->m_leRefValue=new QLineEdit;

    //for Datetime.
    this->m_lblStartTime=new QLabel(tr("起始时间"));
    this->m_dtStart=new QDateTimeEdit;
    this->m_lblEndTime=new QLabel(tr("结束时间"));
    this->m_dtEnd=new QDateTimeEdit;

    //for boolean.
    this->m_lblBoolean=new QLabel(tr("参考值"));
    this->m_cbBoolean=new QComboBox;
    this->m_cbBoolean->setEditable(false);
    this->m_cbBoolean->addItem(tr("true"));
    this->m_cbBoolean->addItem(tr("false"));

    this->m_btnOkay=new QToolButton;
    this->m_btnOkay->setText(tr("OKAY"));
    this->m_btnCancel=new QToolButton;
    this->m_btnCancel->setText(tr("CANCEL"));
    this->m_btnOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_btnOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_btnCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_lblVarName,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_letVarName,0,1,1,1);

    this->m_gridLayout->addWidget(this->m_lblVarType,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbbVarType,1,1,1,1);

    //for Digital.
    this->m_gridLayout->addWidget(this->m_lblVarRange,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_lblVarMin,3,0,1,1);
    this->m_gridLayout->addWidget(this->m_letVarMin,3,1,1,1);
    this->m_gridLayout->addWidget(this->m_lblVarMax,3,2,1,1);
    this->m_gridLayout->addWidget(this->m_letVarMax,3,3,1,1);

    //for String.
    this->m_gridLayout->addWidget(this->m_lblRefValue,4,0,1,1);
    this->m_gridLayout->addWidget(this->m_leRefValue,4,1,1,3);

    //for Datetime.
    this->m_gridLayout->addWidget(this->m_lblStartTime,5,0,1,1);
    this->m_gridLayout->addWidget(this->m_dtStart,5,1,1,1);
    this->m_gridLayout->addWidget(this->m_lblEndTime,5,2,1,1);
    this->m_gridLayout->addWidget(this->m_dtEnd,5,3,1,1);

    //for boolean.
    this->m_gridLayout->addWidget(this->m_lblBoolean,6,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbBoolean,6,1,1,1);

    this->m_gridLayout->addWidget(this->m_btnOkay,7,2,1,1);
    this->m_gridLayout->addWidget(this->m_btnCancel,7,3,1,1);
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

    //for Digitial.
    delete this->m_lblVarRange;
    delete this->m_lblVarMin;
    delete this->m_letVarMin;
    delete this->m_lblVarMax;
    delete this->m_letVarMax;

    //for String.
    delete this->m_lblRefValue;
    delete this->m_leRefValue;

    //for Datetime.
    delete this->m_lblStartTime;
    delete this->m_dtStart;
    delete this->m_lblEndTime;
    delete this->m_dtEnd;

    //for boolean.
    delete this->m_lblBoolean;
    delete this->m_cbBoolean;

    delete this->m_btnOkay;
    delete this->m_btnCancel;

    delete this->m_gridLayout;
}
void ZGeneralVarInfoDia::ZSlotDataTypeChanged(QString type)
{
    if(type=="Digital")
    {
        //Digital show.
        this->m_lblVarRange->setVisible(true);
        this->m_lblVarMin->setVisible(true);
        this->m_letVarMin->setVisible(true);
        this->m_lblVarMax->setVisible(true);
        this->m_letVarMax->setVisible(true);

        //String hide.
        this->m_lblRefValue->setVisible(false);
        this->m_leRefValue->setVisible(false);

        //Datetime hide.
        this->m_lblStartTime->setVisible(false);
        this->m_dtStart->setVisible(false);
        this->m_lblEndTime->setVisible(false);
        this->m_dtEnd->setVisible(false);

        //boolean hide.
        this->m_lblBoolean->setVisible(false);
        this->m_cbBoolean->setVisible(false);
    }else if(type=="String"){
        //Digital hide.
        this->m_lblVarRange->setVisible(false);
        this->m_lblVarMin->setVisible(false);
        this->m_letVarMin->setVisible(false);
        this->m_lblVarMax->setVisible(false);
        this->m_letVarMax->setVisible(false);

        //String show.
        this->m_lblRefValue->setVisible(true);
        this->m_leRefValue->setVisible(true);

        //Datetime hide.
        this->m_lblStartTime->setVisible(false);
        this->m_dtStart->setVisible(false);
        this->m_lblEndTime->setVisible(false);
        this->m_dtEnd->setVisible(false);

        //boolean hide.
        this->m_lblBoolean->setVisible(false);
        this->m_cbBoolean->setVisible(false);
    }else if(type=="Datetime")
    {
        //Digital hide.
        this->m_lblVarRange->setVisible(false);
        this->m_lblVarMin->setVisible(false);
        this->m_letVarMin->setVisible(false);
        this->m_lblVarMax->setVisible(false);
        this->m_letVarMax->setVisible(false);

        //String hide.
        this->m_lblRefValue->setVisible(false);
        this->m_leRefValue->setVisible(false);

        //Datetime show.
        this->m_lblStartTime->setVisible(true);
        this->m_dtStart->setVisible(true);
        this->m_lblEndTime->setVisible(true);
        this->m_dtEnd->setVisible(true);

        //boolean hide.
        this->m_lblBoolean->setVisible(false);
        this->m_cbBoolean->setVisible(false);
    }else if(type=="Boolean")
    {
        //Digital hide.
        this->m_lblVarRange->setVisible(false);
        this->m_lblVarMin->setVisible(false);
        this->m_letVarMin->setVisible(false);
        this->m_lblVarMax->setVisible(false);
        this->m_letVarMax->setVisible(false);

        //String hide.
        this->m_lblRefValue->setVisible(false);
        this->m_leRefValue->setVisible(false);

        //Datetime hide.
        this->m_lblStartTime->setVisible(false);
        this->m_dtStart->setVisible(false);
        this->m_lblEndTime->setVisible(false);
        this->m_dtEnd->setVisible(false);

        //boolean show.
        this->m_lblBoolean->setVisible(true);
        this->m_cbBoolean->setVisible(true);
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
        QString val;
        val+=this->m_letVarMin->text();
        val+="-X-";
        val+=this->m_letVarMax->text();
        return val;
    }else if(this->ZGetVarType()=="String"){
        return QString("X");
    }else if(this->ZGetVarType()=="Datetime")
    {
        QString val;
        val+=this->m_dtStart->dateTime().toString("yyyyMMddhhmmss");
        val+="-X-";
        val+=this->m_dtEnd->dateTime().toString("yyyyMMddhhmmss");
        return val;
    }else if(this->ZGetVarType()=="Boolean")
    {
        return QString("X");
    }
}
void ZGeneralVarInfoDia::ZSetVarRule(QString rule)
{
    if(this->ZGetVarType()=="Digital")
    {
        QStringList valList=rule.split("-X-");
        if(valList.size()!=2)
        {
            return;
        }
        this->m_letVarMin->setText(valList.at(0));
        this->m_letVarMax->setText(valList.at(1));

    }else if(this->ZGetVarType()=="String"){
        //nothing to do.
    }else if(this->ZGetVarType()=="Datetime")
    {
        QStringList valList=rule.split("-X-");
        if(valList.size()!=2)
        {
            return;
        }
        this->m_dtStart->setDateTime(QDateTime::fromString(valList.at(0),"yyyyMMddhhmmss"));
        this->m_dtEnd->setDateTime(QDateTime::fromString(valList.at(0),"yyyyMMddhhmmss"));
    }else if(this->ZGetVarType()=="Boolean")
    {
        //nothing to do.
    }
}
QString ZGeneralVarInfoDia::ZGetRefValue()
{
    if(this->ZGetVarType()=="Digital")
    {
        return this->m_leDigitalRefVal->text();
    }else if(this->ZGetVarType()=="String")
    {
        return this->m_leRefValue->text();
    }else if(this->ZGetVarType()=="Datetime")
    {
        return this->m_dtRefVal->dateTime().toString("yyyyMMddhhmmss");
    }else if(this->ZGetVarType()=="Boolean")
    {
        return this->m_cbBoolean->currentText();
    }else{
        return QString("Unknow");
    }
}
void ZGeneralVarInfoDia::ZSetRefValue(QString val)
{
    if(this->ZGetVarType()=="Digital")
    {
        this->m_leDigitalRefVal->setText(val);
    }else if(this->ZGetVarType()=="String")
    {
        this->m_leRefValue->setText(val);
    }else if(this->ZGetVarType()=="Datetime")
    {
        this->m_dtRefVal->setDateTime(QDateTime::fromString("yyyyMMddhhmmss"));
    }else if(this->ZGetVarType()=="Boolean")
    {
        this->m_cbBoolean->setCurrentText(val);
    }
}


