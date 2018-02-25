#include "zfontinfodia.h"
#include <QFontDatabase>
#include <QList>
ZFontInfoDia::ZFontInfoDia(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("字体对话框"));

    this->m_lblLeftTop=new QLabel(tr("左上角"));
    this->m_leLeftTop=new QLineEdit;
    this->m_leLeftTop->setEnabled(false);
    this->m_lblRightBottom=new QLabel(tr("右下角"));
    this->m_leRightBottom=new QLineEdit;
    this->m_leRightBottom->setEnabled(false);

    this->m_lblFontFamily=new QLabel(tr("字体"));
    this->m_cbbFontFamily=new QComboBox;
    this->m_cbbFontFamily->setEditable(false);

    this->m_lblFontSize=new QLabel(tr("字号"));
    this->m_cbbFontSize=new QComboBox;
    this->m_cbbFontSize->setEditable(false);

    this->m_cbBold=new QCheckBox(tr("粗体"));
    this->m_cbItalic=new QCheckBox(tr("斜体"));

    this->m_btnOkay=new QToolButton;
    this->m_btnOkay->setText(tr("确认"));
    this->m_btnCancel=new QToolButton;
    this->m_btnCancel->setText(tr("取消"));
    this->m_btnOkay->setIcon(QIcon(":/common/images/common/okay.png"));
    this->m_btnOkay->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->m_btnCancel->setIcon(QIcon(":/common/images/common/cancel.png"));
    this->m_btnCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    this->m_gridLayout=new QGridLayout;

    this->m_gridLayout->addWidget(this->m_lblLeftTop,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_leLeftTop,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_lblRightBottom,0,2,1,1);
    this->m_gridLayout->addWidget(this->m_leRightBottom,0,3,1,1);

    this->m_gridLayout->addWidget(this->m_lblFontFamily,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbbFontFamily,1,1,1,1);

    this->m_gridLayout->addWidget(this->m_lblFontSize,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbbFontSize,2,1,1,1);

    this->m_gridLayout->addWidget(this->m_cbBold,3,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbItalic,3,1,1,1);

    this->m_gridLayout->addWidget(this->m_btnOkay,4,2,1,1);
    this->m_gridLayout->addWidget(this->m_btnCancel,4,3,1,1);

    this->setLayout(this->m_gridLayout);

    connect(this->m_btnOkay,SIGNAL(clicked(bool)),this,SLOT(ZSlotOkay()));
    connect(this->m_btnCancel,SIGNAL(clicked(bool)),this,SLOT(ZSlotCancel()));

    //load all available font familys.
    QFontDatabase tFontDb;
    this->m_cbbFontFamily->addItems(tFontDb.families());
    this->m_cbbFontFamily->setCurrentIndex(0);
    connect(this->m_cbbFontFamily,SIGNAL(currentTextChanged(QString)),this,SLOT(ZSlotUpdateFontSize(QString)));
    this->ZSlotUpdateFontSize(this->m_cbbFontFamily->currentText());
}

ZFontInfoDia::~ZFontInfoDia()
{
    delete this->m_lblLeftTop;
    delete this->m_leLeftTop;
    delete this->m_lblRightBottom;
    delete this->m_leRightBottom;

    delete this->m_lblFontFamily;
    delete this->m_cbbFontFamily;

    delete this->m_lblFontSize;
    delete this->m_cbbFontSize;

    delete this->m_cbBold;
    delete this->m_cbItalic;

    delete this->m_btnOkay;
    delete this->m_btnCancel;
    delete this->m_gridLayout;
}
void ZFontInfoDia::ZSlotUpdateFontSize(QString fontFamily)
{
    if(fontFamily.isEmpty())
    {
        return;
    }
    //clear first.
    this->m_cbbFontSize->clear();

    //get all supported font sizes.
    QFontDatabase tFontDb;
    QList<int>  tFontSizeList=tFontDb.pointSizes(fontFamily);
    //if the font family does not contains font size information.
    //we only set the default size 16.
    if(tFontSizeList.count()<=0)
    {
        this->m_cbbFontSize->addItem(QString("16"));
        return;
    }

    for(qint32 i=0;i<tFontSizeList.count();i++)
    {
        this->m_cbbFontSize->addItem(QString("%1").arg(tFontSizeList.at(i)));
    }
}
void ZFontInfoDia::ZSlotOkay()
{
    this->accept();
}
void ZFontInfoDia::ZSlotCancel()
{
    this->reject();
}

QString ZFontInfoDia::ZGetFontFamily()
{
    return this->m_cbbFontFamily->currentText();
}
void ZFontInfoDia::ZSetFontFamily(QString fontFamily)
{
    this->m_cbbFontFamily->setCurrentText(fontFamily);
}

qint32 ZFontInfoDia::ZGetFontSize()
{
    return this->m_cbbFontSize->currentText().toInt();
}
void ZFontInfoDia::ZSetFontSize(qint32 fontSize)
{
    this->m_cbbFontSize->setCurrentText(QString("%1").arg(fontSize));
}

bool ZFontInfoDia::ZFontIsBold()
{
    return this->m_cbBold->isChecked();
}
void ZFontInfoDia::ZSetFontBold(bool bold)
{
    this->m_cbBold->setChecked(bold);
}

bool ZFontInfoDia::ZFontIsItalic()
{
    return this->m_cbItalic->isChecked();
}
void ZFontInfoDia::ZSetFontItalic(bool italic)
{
    this->m_cbItalic->setChecked(italic);
}
void ZFontInfoDia::ZSetLeftTop(qint32 x,qint32 y)
{
    this->m_leLeftTop->setText(QString("(%1,%2)").arg(x).arg(y));
}
void ZFontInfoDia::ZSetRightBottom(qint32 x,qint32 y)
{
    this->m_leRightBottom->setText(QString("(%1,%2)").arg(x).arg(y));
}
