#include "zpdfviewer.h"
ZPdfViewer::ZPdfViewer(QWidget *parent) :
    QWidget(parent)
{
    this->m_ComboBox=new QComboBox;

    this->m_BtnFirstPage=new QToolButton;
    this->m_BtnFirstPage->setText(tr("首页"));
    connect(this->m_BtnFirstPage,SIGNAL(clicked(bool)),this,SLOT(ZSlotFirstPage()));

    this->m_BtnPriorPage=new QToolButton;
    this->m_BtnPriorPage->setText(tr("前一页"));
    connect(this->m_BtnPriorPage,SIGNAL(clicked(bool)),this,SLOT(ZSlotPriorPage()));

    this->m_BtnNextPage=new QToolButton;
    this->m_BtnNextPage->setText(tr("后一页"));
    connect(this->m_BtnNextPage,SIGNAL(clicked(bool)),this,SLOT(ZSlotNextPage()));

    this->m_BtnLastPage=new QToolButton;
    this->m_BtnLastPage->setText(tr("末页"));
    connect(this->m_BtnLastPage,SIGNAL(clicked(bool)),this,SLOT(ZSlotLastPage()));

    //scale factor.
    this->m_BtnScaleUp=new QToolButton;
    this->m_BtnScaleUp->setText(tr("放大"));
    this->m_BtnScaleUp->setIcon(QIcon(":/FileManager/images/FileManager/ZoomIn.png"));
    this->m_BtnScaleUp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(this->m_BtnScaleUp,SIGNAL(clicked(bool)),this,SLOT(ZSlotScaleUp()));

    this->m_BtnScaleDown=new QToolButton;
    this->m_BtnScaleDown->setText(tr("缩小"));
    this->m_BtnScaleDown->setIcon(QIcon(":/FileManager/images/FileManager/ZoomOut.png"));
    this->m_BtnScaleDown->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(this->m_BtnScaleDown,SIGNAL(clicked(bool)),this,SLOT(ZSlotScaleDown()));

    this->m_BtnScaleFit=new QToolButton;
    this->m_BtnScaleFit->setText(tr("适中"));
    this->m_BtnScaleFit->setIcon(QIcon(":/FileManager/images/FileManager/ZoomFit.png"));
    this->m_BtnScaleFit->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(this->m_BtnScaleFit,SIGNAL(clicked(bool)),this,SLOT(ZSlotScaleFit()));

    this->m_hlayoutTop=new QHBoxLayout;
    this->m_hlayoutTop->addStretch(1);
    this->m_hlayoutTop->addWidget(this->m_BtnFirstPage);
    this->m_hlayoutTop->addWidget(this->m_BtnPriorPage);
    this->m_hlayoutTop->addWidget(this->m_ComboBox);
    this->m_hlayoutTop->addWidget(this->m_BtnNextPage);
    this->m_hlayoutTop->addWidget(this->m_BtnLastPage);
    this->m_hlayoutTop->addStretch(1);
    this->m_hlayoutTop->addWidget(this->m_BtnScaleUp);
    this->m_hlayoutTop->addWidget(this->m_BtnScaleDown);
    this->m_hlayoutTop->addWidget(this->m_BtnScaleFit);

    //vlayout main.
    this->m_LabelImage=new QLabel;
    this->m_LabelImage->setBackgroundRole(QPalette::Base);
    this->m_LabelImage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->m_LabelImage->setScaledContents(true);


    this->m_ScrollArea=new QScrollArea;
    this->m_ScrollArea->setAlignment(Qt::AlignCenter);
    this->m_ScrollArea->setWidget(this->m_LabelImage);

    this->m_vlayoutMain=new QVBoxLayout;
    this->m_vlayoutMain->addLayout(this->m_hlayoutTop);
    this->m_vlayoutMain->addWidget(this->m_ScrollArea);
    this->m_vlayoutMain->setStretchFactor(this->m_hlayoutTop,0);
    this->m_vlayoutMain->setStretchFactor(this->m_ScrollArea,1);

    this->setLayout(this->m_vlayoutMain);

    //initial image factor.
    this->m_totalPages=0;
    this->m_currentPage=0;
    this->m_ImageFactor=1;
     this->m_bLeftButtonPressed=false;
    this->m_bCtrlButtonPressed=false;

    connect(this->m_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(ZSlotLoadPdfPage(qint32)));
    connect(this->m_ScrollArea->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(ZSlotScrollBarValueChanged(int)));
}
ZPdfViewer::~ZPdfViewer()
{
    delete this->m_ComboBox;
    delete this->m_BtnFirstPage;
    delete this->m_BtnPriorPage;
    delete this->m_BtnNextPage;
    delete this->m_BtnLastPage;
    //scale.
    delete this->m_BtnScaleUp;
    delete this->m_BtnScaleDown;
    delete this->m_BtnScaleFit;
    delete this->m_hlayoutTop;
    delete this->m_LabelImage;
    delete this->m_ScrollArea;
    delete this->m_vlayoutMain;

#ifdef USE_PDF
    if(this->m_document)
    {
        delete this->m_document;
    }
#endif
}
//load hard disk's pdf file with absolute path.
bool ZPdfViewer::ZLoadPdfFile(QString fileName)
{
#ifdef USE_PDF
    this->m_document=Poppler::Document::load(fileName);
    if (!this->m_document || this->m_document->isLocked())
    {
        // ... error message ....
        delete this->m_document;
        return false;
    }
    this->m_totalPages=this->m_document->numPages();
    for(qint32 i=0;i<this->m_totalPages;i++)
    {
        this->m_ComboBox->addItem(QString("%1 / %2").arg(i).arg(this->m_totalPages-1));
    }
    //current page is 0.
    this->m_currentPage=0;
    this->m_ComboBox->setCurrentIndex(0);
#endif
    return true;
}
void ZPdfViewer::mousePressEvent(QMouseEvent *event)
{
    this->m_bLeftButtonPressed=true;
    this->m_OldPos=event->pos();
    this->m_bCtrlButtonPressed=true;
    QWidget::mousePressEvent(event);
}
void ZPdfViewer::mouseMoveEvent(QMouseEvent *event)
{
    if(this->m_bLeftButtonPressed)
    {
        qDebug()<<event->pos();
        QPoint tNewPos;
        tNewPos.setX(this->pos().x()+event->pos().x()-this->m_OldPos.x());
        tNewPos.setY(this->pos().y()+event->pos().y()-this->m_OldPos.y());
        this->m_LabelImage->move(tNewPos);
        event->ignore();
        return;
    }
    QWidget::mouseMoveEvent(event);
}
void ZPdfViewer::mouseReleaseEvent(QMouseEvent *event)
{
    this->m_bLeftButtonPressed=false;
    this->m_bCtrlButtonPressed=false;
    QWidget::mouseReleaseEvent(event);
}
void ZPdfViewer::wheelEvent(QWheelEvent *event)
{
    if(this->m_bCtrlButtonPressed)
    {
        qDebug()<<event->delta();
        event->ignore();
        return;
    }
    QWidget::wheelEvent(event);
}
void ZPdfViewer::ZSlotLoadPdfPage(qint32 pageIndex)
{
#ifdef USE_PDF
    // Paranoid safety check
    if (this->m_document == 0)
    {
        // ... error message ...
        return;
    }
    // Access page of the PDF file
    // Document starts at page 0
    Poppler::Page* pdfPage = this->m_document->page(pageIndex);
    if (pdfPage == 0)
    {
        qDebug()<<"load page failed!";
        return;
    }

    // Generate a QImage of the rendered page
    //QImage image = pdfPage->renderToImage(this->physicalDpiX(), this->physicalDpiY(), 0, 0,tPageSize.width(),tPageSize.height());
    QImage image = pdfPage->renderToImage(this->m_ImageFactor*this->physicalDpiX(), this->m_ImageFactor*this->physicalDpiY());
    qDebug()<<"ImageSize:"<<image.size();
    if (image.isNull())
    {
        // ... error message ...
        return;
    }
    QPixmap tPixmap;
    if(tPixmap.convertFromImage(image))
    {
        //tPixmap=tPixmap.scaled(tPixmap.width()*this->m_ImageFactor,tPixmap.height()*this->m_ImageFactor);
        qDebug()<<"Pixmap scaled size:"<<tPixmap.size();
        this->m_LabelImage->setPixmap(tPixmap);
        this->m_LabelImage->setFixedSize(tPixmap.width(),tPixmap.height());
    }else{
        qDebug()<<"convert image to pixmap failed!";
    }
    // ... use image ...
    // after the usage, the page must be deleted
    delete pdfPage;
#endif
}
void ZPdfViewer::ZSlotFirstPage()
{
    this->m_currentPage=0;
    this->m_ComboBox->setCurrentIndex(0);
    this->ZSlotLoadPdfPage(this->m_currentPage);
}
void ZPdfViewer::ZSlotPriorPage()
{
    if(this->m_currentPage>0)
    {
        this->m_currentPage--;
        this->m_ComboBox->setCurrentIndex(this->m_ComboBox->currentIndex()-1);
        this->ZSlotLoadPdfPage(this->m_currentPage);
    }
}
void ZPdfViewer::ZSlotNextPage()
{
    if(this->m_currentPage<this->m_totalPages-1)
    {
        this->m_currentPage++;
        this->m_ComboBox->setCurrentIndex(this->m_ComboBox->currentIndex()+1);
        this->ZSlotLoadPdfPage(this->m_currentPage);
    }
}
void ZPdfViewer::ZSlotLastPage()
{
    this->m_currentPage=this->m_totalPages-1;
    this->m_ComboBox->setCurrentIndex(this->m_ComboBox->count()-1);
    this->ZSlotLoadPdfPage(this->m_currentPage);
}
void ZPdfViewer::ZSlotScaleUp()
{
    this->m_ImageFactor++;
    this->ZSlotLoadPdfPage(this->m_currentPage);
}
void ZPdfViewer::ZSlotScaleDown()
{
    if(this->m_ImageFactor>1)
    {
        this->m_ImageFactor--;
        this->ZSlotLoadPdfPage(this->m_currentPage);
    }
}
void ZPdfViewer::ZSlotScaleFit()
{
    this->m_ImageFactor=1;
    this->ZSlotLoadPdfPage(this->m_currentPage);
}
void ZPdfViewer::ZSlotScrollBarValueChanged(int scrollBarValue)
{
    if(0==scrollBarValue)
    {
        this->ZSlotPriorPage();
    }else if(this->m_ScrollArea->verticalScrollBar()->maximum()==scrollBarValue)
    {
        this->ZSlotNextPage();
    }
}
