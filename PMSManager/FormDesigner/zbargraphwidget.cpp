#include "zbargraphwidget.h"
ZBarGraphAttributeDialog::ZBarGraphAttributeDialog(QWidget *parent):QDialog(parent)
{

}
ZBarGraphAttributeDialog::~ZBarGraphAttributeDialog()
{

}
ZBarGraphWidget::ZBarGraphWidget()
{
    //data set.
    QBarSet *m_set1=new QBarSet(tr("一月"));
    *m_set1<<22.5<<40<<29<<87<<25<<105;
    QBarSet *m_set2=new QBarSet(tr("二月"));
    *m_set1<<19<<33<<46<<69.3<<18<<98;
    this->m_barSetList.append(m_set1);
    this->m_barSetList.append(m_set2);

    //bar series.
    this->m_barSeries=new QBarSeries;
    this->m_barSeries->append(this->m_barSetList);

    this->m_chartView=new QChartView;
    this->m_chartView->setRenderHint(QPainter::Antialiasing);
    this->m_chartView->chart()->setTitle(tr("柱状图表"));
    this->m_chartView->chart()->addSeries(this->m_barSeries);
    this->m_chartView->chart()->legend()->setAlignment(Qt::AlignRight);
    //this->m_chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);

    this->m_vLayout->addWidget(this->m_chartView);
}
ZBarGraphWidget::~ZBarGraphWidget()
{
    for(qint32 i=0;i<this->m_barSetList.size();i++)
    {
        delete this->m_barSetList.at(i);
    }
    delete this->m_barSeries;
    delete this->m_chartView;
}
void ZBarGraphWidget::ZOpenAttributeDialog()
{
    ZBarGraphAttributeDialog dia;
    if(dia.exec()==QDialog::Accepted)
    {
    }
}
