#include "ztextwidget.h"
#include <QFontDatabase>
ZTextAttributeDialog::ZTextAttributeDialog(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("文本属性对话框"));

    this->m_lblFontFamily=new QLabel(tr("字体"));
    this->m_cbbFontFamily=new QComboBox;
    this->m_cbbFontFamily->setEditable(false);

    this->m_lblFontSize=new QLabel(tr("字号"));
    this->m_cbbFontSize=new QComboBox;
    this->m_cbbFontSize->setEditable(false);

    this->m_cbBold=new QCheckBox(tr("粗体"));
    this->m_cbItalic=new QCheckBox(tr("斜体"));

    this->m_llText=new QLabel(tr("文本"));
    this->m_leText=new QLineEdit;

    this->m_tbOkay=new QToolButton;
    this->m_tbOkay->setText(tr("Okay"));
    this->m_tbCancel=new QToolButton;
    this->m_tbCancel->setText(tr("Cancel"));
    this->m_gridLayout=new QGridLayout;

    this->m_gridLayout->addWidget(this->m_lblFontFamily,0,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbbFontFamily,0,1,1,1);

    this->m_gridLayout->addWidget(this->m_lblFontSize,1,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbbFontSize,1,1,1,1);

    this->m_gridLayout->addWidget(this->m_cbBold,2,0,1,1);
    this->m_gridLayout->addWidget(this->m_cbItalic,2,1,1,1);

    this->m_gridLayout->addWidget(this->m_llText,3,0,1,1);
    this->m_gridLayout->addWidget(this->m_leText,4,0,1,2);

    this->m_gridLayout->addWidget(this->m_tbOkay,5,0,1,1);
    this->m_gridLayout->addWidget(this->m_tbCancel,5,1,1,1);
    this->setLayout(this->m_gridLayout);


    //load all available font familys.
    QFontDatabase tFontDb;
    this->m_cbbFontFamily->addItems(tFontDb.families());
    this->m_cbbFontFamily->setCurrentIndex(0);
    connect(this->m_cbbFontFamily,SIGNAL(currentTextChanged(QString)),this,SLOT(ZSlotUpdateFontSize(QString)));
    this->ZSlotUpdateFontSize(this->m_cbbFontFamily->currentText());

    connect(this->m_tbOkay,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(this->m_tbCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));
}
ZTextAttributeDialog::~ZTextAttributeDialog()
{
    delete this->m_lblFontFamily;
    delete this->m_cbbFontFamily;

    delete this->m_lblFontSize;
    delete this->m_cbbFontSize;

    delete this->m_cbBold;
    delete this->m_cbItalic;

    delete this->m_llText;
    delete this->m_leText;

    delete this->m_tbOkay;
    delete this->m_tbCancel;
    delete this->m_gridLayout;
}
void ZTextAttributeDialog::ZSetText(QString text)
{
    this->m_leText->setText(text);
}
QString ZTextAttributeDialog::ZGetText()
{
    return this->m_leText->text();
}
void ZTextAttributeDialog::ZSetFontName(QString fontName)
{
    this->m_cbbFontFamily->setCurrentText(fontName);
}
QString ZTextAttributeDialog::ZGetFontName()
{
    return this->m_cbbFontFamily->currentText();
}

void ZTextAttributeDialog::ZSetFontSize(qint32 fontSize)
{
    this->m_cbbFontSize->setCurrentText(QString("%1").arg(fontSize));
}
qint32 ZTextAttributeDialog::ZGetFontSize()
{
    return this->m_cbbFontSize->currentText().toInt();
}

bool ZTextAttributeDialog::ZGetFontBold()
{
    return this->m_cbBold->isChecked();
}
void ZTextAttributeDialog::ZSetFontBold(bool bold)
{
    this->m_cbBold->setChecked(bold);
}
bool ZTextAttributeDialog::ZGetFontItalic()
{
    return this->m_cbItalic->isChecked();
}
void ZTextAttributeDialog::ZSetFontItalic(bool italic)
{
    this->m_cbItalic->setChecked(italic);
}
void ZTextAttributeDialog::ZSlotUpdateFontSize(QString fontFamily)
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

ZTextWidget::ZTextWidget()
{
    this->m_fontName=QString("Arial");
    this->m_fontSize=10;
    this->m_fontBold=false;
    this->m_fontItalic=false;
    this->m_llText=new QLabel;
    this->m_llText->setAlignment(Qt::AlignCenter);
    this->m_llText->setText(tr("PMS system Testing"));
    this->m_vLayout->addWidget(this->m_llText);
}
ZTextWidget::~ZTextWidget()
{
    delete this->m_llText;
}
void ZTextWidget::ZOpenAttributeDialog()
{
    ZTextAttributeDialog dia;
    dia.ZSetText(this->m_llText->text());
    dia.ZSetFontName(this->m_fontName);
    dia.ZSetFontSize(this->m_fontSize);
    dia.ZSetFontBold(this->m_fontBold);
    dia.ZSetFontItalic(this->m_fontItalic);
    if(dia.exec()==QDialog::Accepted)
    {
        this->m_fontName=dia.ZGetFontName();
        this->m_fontSize=dia.ZGetFontSize();
        this->m_fontBold=dia.ZGetFontBold();
        this->m_fontItalic=dia.ZGetFontItalic();
        QFont font(this->m_fontName);
        font.setPixelSize(this->m_fontSize);
        font.setBold(this->m_fontBold);
        font.setItalic(this->m_fontItalic);
        this->m_llText->setFont(font);
        this->m_llText->setText(dia.ZGetText());
    }
}
