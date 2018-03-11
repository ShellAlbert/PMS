#ifndef ZBARGRAPHWIDGET_H
#define ZBARGRAPHWIDGET_H
#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QToolButton>
#include <QGridLayout>
#include <QLineEdit>
#include <FormDesigner/zbasewidget.h>
#include <QBarSeries>
#include <QBarSet>
#include <QChartView>
using namespace QtCharts;
class ZBarGraphAttributeDialog:public QDialog
{
    Q_OBJECT
public:
    ZBarGraphAttributeDialog(QWidget *parent=0);
    ~ZBarGraphAttributeDialog();
private slots:
private:

};
class ZBarGraphWidget:public ZBaseWidget
{
    Q_OBJECT
public:
    ZBarGraphWidget();
    ~ZBarGraphWidget();
    void ZOpenAttributeDialog();
public:
    QList<QBarSet*> m_barSetList;
    QBarSeries *m_barSeries;
    QChartView  *m_chartView;
};
#endif // ZBARGRAPHWIDGET_H
