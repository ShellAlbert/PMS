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
#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QVariant>
#include <QPointF>
#include <QPointer>
#include <QAction>

#include "cutereport_globals.h"
#include "designer_globals.h"
#include "cutereport_types.h"

namespace CuteReport
{
    class ReportCore;
    class ReportInterface;
    class PageInterface;
    class PageManipulatorInterface;
    class BaseItemInterface;
    class PageAction;
    class RenderedPageInterface;
    class DatasetInterface;
    class FormInterface;
    class DesignerItemInterface;
}

class MainWindow;
class QSettings;
class QLabel;
class DesignerItemInterfaceObject;

namespace PropertyEditor {
    class EditorWidget;
    class Core;
}

enum Answer {AnswerOk, AnswerCancel};

namespace CuteDesigner{

class ModuleInterface;

class DESIGNER_EXPORTS Core : public QObject
{
    Q_OBJECT
    Q_FLAGS(StdAction StdActions)

public:
    //enum SignalType {SignalBefore, SignalAfter};
    enum StdAction {
        ActionUndo = 0x0001,
        ActionRedo = 0x0002,
        ActionCut = 0x0004,
        ActionCopy = 0x0008,
        ActionPaste = 0x0010,
        ActionDelete = 0x0020
    };
    Q_DECLARE_FLAGS(StdActions, StdAction)

    explicit Core(QWidget *winParent=0,QObject *parent = 0);
    explicit Core(QSettings * settings, QObject *parent = 0);
    ~Core();

    void setupMainWindow();
    MainWindow * mainWindow();

    void setCurrentReport(CuteReport::ReportInterface * report);
    CuteReport::ReportInterface* currentReport() const;

    void setCurrentPage(CuteReport::PageInterface*);
    CuteReport::PageInterface* currentPage();

    void setCurrentDataset(CuteReport::DatasetInterface*dataset);
    CuteReport::DatasetInterface* currentDataset();

    void setCurrentForm(CuteReport::FormInterface * form);
    CuteReport::FormInterface* currentForm();

    void setSettingValue(QString key, QVariant value);
    QVariant getSettingValue(QString key, QVariant defaultValue = QVariant());

    QSettings * settings();

    void switchToModule(CuteDesigner::ModuleInterface * module);
    void switchToModule(const QString & moduleName);

    void sync();

    void addToStatusBar(QLabel *label);

    void setDocumentTitles(int id, const QString & name);

    CuteReport::ReportCore * reportCore() {return m_reportCore;}

    QList<CuteDesigner::ModuleInterface *> modules() const;
    QList<CuteDesigner::ModuleInterface *> guiModules() const;

    PropertyEditor::EditorWidget * createPropertyEditor(QWidget *parent = 0);

    //TODO V2: move to common class for using in console without linking to CuteDesigner
    QString loadObjectDialog(const QStringList &fileExtensions = QStringList(), const QString &dialogTitle = QString());
    QString saveObjectDialog(const QStringList &fileExtensions = QStringList(), const QString &dialogTitle = QString());
    QString loadReportDialog();
    QString saveCurrentReportDialog();

    CuteReport::DesignerItemInterface *designerItemInterface() const;

    void emitNewReportBefore();
    void emitNewReportAfter(CuteReport::ReportInterface*report);
    void emitLoadReportBefore(QString url);
    void emitLoadReportAfter(CuteReport::ReportInterface* report);
    void emitDeleteReportBefore(CuteReport::ReportInterface* report);
    void emitDeleteReportAfter(CuteReport::ReportInterface* report);

signals:
    void ZSignalCloseEvent(QString name);
    void newReport_before();
    void newReport_after(CuteReport::ReportInterface*);
    void deleteReport_before(CuteReport::ReportInterface*);
    void deleteReport_after(CuteReport::ReportInterface*);
    void newPage_before(CuteReport::PageInterface*);
    void newPage_after(CuteReport::PageInterface*);
    void deletePage_before(CuteReport::PageInterface*);
    void deletePage_after(CuteReport::PageInterface*);
    void newItem_after(CuteReport::BaseItemInterface* item, QPointF pagePos);
    void activeObjectChanged(QObject * object);
    void loadReport_before(QString url);
    void loadReport_after(CuteReport::ReportInterface* report);
    void saveReport_before(CuteReport::ReportInterface* report);
    void saveReport_after(CuteReport::ReportInterface* report);
    void newPageActions(QList<CuteReport::PageAction*>);
    void renderingStarted();
    void newDataset_before(CuteReport::DatasetInterface*);
    void newDataset_after(CuteReport::DatasetInterface*);
    void deleteDataset_before(CuteReport::DatasetInterface*);
    void deleteDataset_after(CuteReport::DatasetInterface*);
    void initDone();
    void requestForReport(const QString & url);

    void currentReportChanged(CuteReport::ReportInterface * report);
    void currentPageChanged(CuteReport::PageInterface * page);
    void currentDatasetChanged(CuteReport::DatasetInterface * page);
    void currentFormChanged(CuteReport::FormInterface*);

    void appIsAboutToClose(bool * cancel);
    void closed();
public slots:
    bool newPage();
    void render();
    void stopRenderer();
    void moduleSwitched(int index);
    void showMetric(CuteReport::MetricType type, const QVariant &value);
private:
    void init();
    void saveSettings();
//    void restoreSettings();
    void initModules();
    void appendMenus();
    void _newPeportPage();

private slots:

    void slotInit();
    void _afterItemRemoved(CuteReport::BaseItemInterface*item);
    void slotMainWindowCloseRequest();
    void propertyEditorLog(int logLevel, const QString & module, const QString & shortMessage, const QString & fullMessage);
    void _rendererDone(CuteReport::ReportInterface*report, bool successful);
    void slotStdActionTriggered(CuteDesigner::Core::StdAction actionType, QAction*action);
    void reinitOptions();

private:
    CuteReport::ReportCore * m_reportCore;
    QSettings * m_settings;
    MainWindow * m_mainWindow;
    CuteReport::ReportInterface* m_currentReport;
    CuteReport::PageInterface* m_currentPage;
    CuteReport::DatasetInterface* m_currentDataset;
    CuteReport::FormInterface* m_currentForm;
    QList<CuteDesigner::ModuleInterface*> m_guiModules;
    QList<CuteDesigner::ModuleInterface*> m_modules;
    int m_prevModuleIndex;
    int m_currentModuleIndex;
    QMap<int, QString> m_documentTitles;
    DesignerItemInterfaceObject  * m_designerItemObject;
    int m_loadMethod;

    friend class ModuleInterface;

    //add by zhangshaoyan.
    QWidget *m_winParent;
};

} //namecpace

#endif // CORE_H

