/***************************************************************************
 *   This file is part of the CuteReport project                           *
 *   Copyright (C) 2012-2017 by Alexander Mikhalov                         *
 *   alexander.mikhalov@gmail.com                                          *
 *                                                                         *
 **                   GNU General Public License Usage                    **
 *                                                                         *
 *   This library is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 ***************************************************************************/
#include "datasetcontainer.h"
#include "ui_datasetcontainer.h"
#include "datasetinterface.h"
#include "fancytabs.h"
#include "designercore.h"
#include "dataseteditor.h"

#include <QDebug>
#include <QMessageBox>
#include <QToolButton>

DatasetContainer::DatasetContainer(DatasetEditor * datasetEditor, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatasetContainer),
    m_datasetEditor(datasetEditor)
{
    ui->setupUi(this);

    //connect(ui->cbDatasets, SIGNAL(activated(int)), this, SLOT(slotNewDataset(int)));
    connect(ui->pbDelete, SIGNAL(clicked()), this, SIGNAL(requestForDeleteDataset()));
    connect(ui->bProperties, SIGNAL(toggled(bool)), this, SLOT(slotPropertyButtonToggled(bool)));
    connect(ui->bTest, SIGNAL(clicked()), this, SLOT(populateClicked()));
    connect(ui->bCloseTest, SIGNAL(clicked()), this, SLOT(slotShowOptionsPage()));
    connect(ui->tabs, SIGNAL(CurrentChanged(int)), this, SLOT(slotCurrentDatasetChanged(int)));
    connect(ui->tabs, SIGNAL(tabDoubleClicked(int)), this, SLOT(slotTabDoubleClicked(int)));

    ui->tabs->hide();
    ui->bProperties->hide();

    ui->stackedWidget->setCurrentIndex(0);
}


DatasetContainer::~DatasetContainer()
{
    delete ui;
}


void DatasetContainer::saveSettings()
{
    m_datasetEditor->core()->setSettingValue("CuteReport_DatasetEditor/splitterState", ui->splitter->saveState());
    m_datasetEditor->core()->setSettingValue("CuteReport_DatasetEditor/splitter2State", ui->splitterTestPage->saveState());
    m_datasetEditor->core()->setSettingValue("CuteReport_DatasetEditor/tabMode", ui->tabs->mode());
    m_datasetEditor->core()->setSettingValue("CuteReport_DatasetEditor/propertiesShown", ui->bProperties->isChecked());
}


void DatasetContainer::reloadSettings()
{
    QVariant value;
    if ((value =  m_datasetEditor->core()->getSettingValue("CuteReport_DatasetEditor/splitterState")).isNull())
        ui->splitter->setSizes( QList<int>() << width()*1 << width()*0 );
    else
        ui->splitter->restoreState(value.toByteArray());

    if ((value =  m_datasetEditor->core()->getSettingValue("CuteReport_DatasetEditor/splitter2State")).isNull())
         ui->splitterTestPage->setSizes( QList<int>() << width()*0.8 << width()*0.2 );
    else
        ui->splitterTestPage->restoreState(value.toByteArray());

    ui->bProperties->setChecked(m_datasetEditor->core()->getSettingValue("CuteReport_DatasetEditor/propertiesShown", false).toBool());
    FancyTabWidget::Mode default_mode = FancyTabWidget::Mode_LargeSidebar;
    ui->tabs->SetMode(FancyTabWidget::Mode(m_datasetEditor->core()->getSettingValue("CuteReport_DatasetEditor/tabMode", default_mode).toInt()));
}


void DatasetContainer::addDatasetPlugins(QList<CuteReport::ReportPluginInterface*> datasets)
{
    foreach(CuteReport::ReportPluginInterface * plugin, datasets) {
        CuteReport::DatasetInterface * ds = static_cast<CuteReport::DatasetInterface *>(plugin);
        QToolButton * b = new QToolButton(this);
        b->setIcon(ds->icon());
        b->setToolTip(QString("增加数据源: %1").arg(ds->moduleFullName()));
        b->setIconSize(QSize(24,24));
        b->setAutoRaise(true);
        connect(b, SIGNAL(clicked()), this, SLOT(slotNewDatasetPressed()));
        ui->datasetButtonsLayout->addWidget(b);
        m_buttonModules.insert(b, ds->moduleFullName());
    }
}


void DatasetContainer::addPropertyEditor(QWidget * widget)
{
    m_propertyEditor = widget;
    ui->propertyEditorLayout->addWidget(widget);
    m_propertyEditor->setVisible(ui->bProperties->isChecked());
}


void DatasetContainer::addTab(QWidget * const widget, const QIcon & icon, const QString & name)
{
    ui->tabs->AddTab(widget, icon, name);
    ui->tabs->updateState();
}


void DatasetContainer::deleteTab(QString name)
{
    ui->tabs->deleteTab(name);
    ui->tabs->updateState();
}


void DatasetContainer::slotNewDatasetPressed()
{
    QWidget * w = qobject_cast<QWidget*>(sender());
    if (m_buttonModules.contains(w))
        emit requestForCreateDataset(m_buttonModules.value(w));
}


void DatasetContainer::slotCurrentDatasetChanged(int /*index*/)
{
    emit currentTabChanged(ui->tabs->current_text());
}


void DatasetContainer::slotTabDoubleClicked(int index)
{
    emit requestForRename(ui->tabs->tabText(index));
}


void DatasetContainer::slotPropertyButtonToggled(bool b)
{
    if (m_propertyEditor) {
        m_propertyEditor->setVisible(b);
    }
}


void DatasetContainer::populateClicked()
{
    slotShowDataPage();
    emit requestForPopulateDataset();
}


void DatasetContainer::slotShowDataPage()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void DatasetContainer::slotShowOptionsPage()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void DatasetContainer::setModel(QAbstractItemModel * model)
{
    ui->table->setModel(model);
}


void DatasetContainer::setError(QString error)
{
    ui->errors->setText(error);
}


void DatasetContainer::deleteAllTabs()
{
    ui->tabs->deleteAllTabs();
    ui->tabs->updateState();
}


void DatasetContainer::changeTabText(QString oldText, QString newText)
{
    for (int i=0; i< ui->tabs->tabsCount(); ++i)
        if (ui->tabs->tabText(i) == oldText) {
            ui->tabs->changeText(newText, i);
            return;
        }
}


void DatasetContainer::setCurrentTab(QString name)
{
    ui->tabs->blockSignals(true);
    for (int i=0; i<ui->tabs->tabsCount(); ++i)
        if (ui->tabs->tabText(i) == name) {
            ui->tabs->SetCurrentIndex(i);
            break;
        }
    ui->tabs->blockSignals(false);
}

