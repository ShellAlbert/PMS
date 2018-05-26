#-------------------------------------------------
#
# Project created by QtCreator 2016-12-30T13:53:29
#
#-------------------------------------------------

QT       += core gui network printsupport xlsx charts xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PMSManager

TEMPLATE = app

HEADERS += \
    BackupManager/zbackupinfodia.h \
    BackupManager/zbackupmanager.h \
    BackupManager/zlistbackupinfodia.h \
    BasePart/zbaseinfodia.h \
    FileManager/poppler/ArthurOutputDev.h \
    FileManager/poppler/poppler-annotation-helper.h \
    FileManager/poppler/poppler-annotation-private.h \
    FileManager/poppler/poppler-annotation.h \
    FileManager/poppler/poppler-converter-private.h \
    FileManager/poppler/poppler-embeddedfile-private.h \
    FileManager/poppler/poppler-export.h \
    FileManager/poppler/poppler-form.h \
    FileManager/poppler/poppler-link-extractor-private.h \
    FileManager/poppler/poppler-link.h \
    FileManager/poppler/poppler-media.h \
    FileManager/poppler/poppler-optcontent-private.h \
    FileManager/poppler/poppler-optcontent.h \
    FileManager/poppler/poppler-page-private.h \
    FileManager/poppler/poppler-page-transition-private.h \
    FileManager/poppler/poppler-page-transition.h \
    FileManager/poppler/poppler-private.h \
    FileManager/poppler/poppler-qiodeviceoutstream-private.h \
    FileManager/poppler/poppler-qt5.h \
    FileManager/pfilemanager.h \
    FileManager/zfileinfodia.h \
    FileManager/zfolderinfodia.h \
    FileManager/zlistfolderfileinfodia.h \
    FileManager/zpdfviewer.h \
    FormDesigner/pformdesigner.h \
    FormDesigner/zbargraphwidget.h \
    FormDesigner/zbasewidget.h \
    FormDesigner/zcheckboxwidget.h \
    FormDesigner/zdatetimewidget.h \
    FormDesigner/zforminfodia.h \
    FormDesigner/zlinewidget.h \
    FormDesigner/zlistforminfodia.h \
    FormDesigner/zrectanglewidget.h \
    FormDesigner/zspinboxwidget.h \
    FormDesigner/ztablewidget.h \
    FormDesigner/ztextwidget.h \
    KDReports/KDReports.h \
    KDReports/KDReportsAbstractReportLayout_p.h \
    KDReports/KDReportsAbstractTableElement.h \
    KDReports/KDReportsAutoTableElement.h \
    KDReports/KDReportsCell.h \
    KDReports/KDReportsChartElement.h \
    KDReports/KDReportsChartTextObject_p.h \
    KDReports/KDReportsElement.h \
    KDReports/KDReportsElementData_p.h \
    KDReports/KDReportsErrorDetails.h \
    KDReports/KDReportsErrorDetails_p.h \
    KDReports/KDReportsFontScaler_p.h \
    KDReports/KDReportsFrame.h \
    KDReports/KDReportsGlobal.h \
    KDReports/KDReportsHeader.h \
    KDReports/KDReportsHeader_p.h \
    KDReports/KDReportsHLineElement.h \
    KDReports/KDReportsHLineTextObject_p.h \
    KDReports/KDReportsHtmlElement.h \
    KDReports/KDReportsImageElement.h \
    KDReports/KDReportsLayoutHelper_p.h \
    KDReports/KDReportsMainTable.h \
    KDReports/KDReportsPreviewDialog.h \
    KDReports/KDReportsPreviewWidget.h \
    KDReports/KDReportsReport.h \
    KDReports/KDReportsReport_p.h \
    KDReports/KDReportsReportBuilder_p.h \
    KDReports/KDReportsSpreadsheetReportLayout_p.h \
    KDReports/KDReportsTableBreakingLogic_p.h \
    KDReports/KDReportsTableBreakingSettingsDialog.h \
    KDReports/KDReportsTableElement.h \
    KDReports/KDReportsTableLayout_p.h \
    KDReports/KDReportsTextDocReportLayout_p.h \
    KDReports/KDReportsTextDocument_p.h \
    KDReports/KDReportsTextDocumentData_p.h \
    KDReports/KDReportsTextElement.h \
    KDReports/KDReportsUnit.h \
    KDReports/KDReportsVariableType.h \
    KDReports/KDReportsXmlElementHandler.h \
    KDReports/KDReportsXmlElementHandlerV2.h \
    KDReports/KDReportsXmlHelper.h \
    KDReports/KDReportsXmlParser_p.h \
    Logger/zlogmanager.h \
    LoginManager/ploginmanager.h \
    NetProtocol/pnetframe.h \
    NetProtocol/pnetprotocol.h \
    ProcessEditor/pprocesseditor.h \
    ProcessEditor/pstepeditor.h \
    ProcessEditor/zlinkfileselectdia.h \
    ProcessEditor/zlinkroleselectdia.h \
    ProcessEditor/zlinktemplateselectdia.h \
    ProcessEditor/zlistprocessinfodia.h \
    ProcessEditor/zprocessinfodia.h \
    Sheet/zauxsheet.h \
    Sheet/zcell.h \
    Sheet/zcelldelegate.h \
    Sheet/zcheckboxcell.h \
    Sheet/zsheet.h \
    SoftInfo/zsoftinfodia.h \
    SysSetup/zsyssetupdia.h \
    TaskManager/ptaskmanager.h \
    TaskManager/zlistprocesssteplinktemplatedia.h \
    TaskManager/zlisttaskdia.h \
    TaskManager/zprocesssteplinktemplateselectdia.h \
    TaskManager/ztaskinfodia.h \
    TaskManager/ztasksheet.h \
    TemplateEditor/ptemplateeditor.h \
    TemplateEditor/zautovarinfodia.h \
    TemplateEditor/zcolorinfodia.h \
    TemplateEditor/zcomboboxdia.h \
    TemplateEditor/zfontinfodia.h \
    TemplateEditor/zframeinfodia.h \
    TemplateEditor/zgeneralvarinfodia.h \
    TemplateEditor/zlisttemplateinfodia.h \
    TemplateEditor/zspinboxdia.h \
    TemplateEditor/zsyspicdia.h \
    TemplateEditor/ztemplateinfodia.h \
    TemplateEditor/zvarinfodia.h \
    TemplateEditor/zvarsourceinfodia.h \
    UpdateManager/pupdatemanager.h \
    UserManager/pusermanagerwin.h \
    UserManager/zgrpinfodia.h \
    UserManager/zimportroleuserinfodia.h \
    UserManager/zlistroleuserinfodia.h \
    UserManager/zuserinfodia.h \
    pgblpara.h \
    pmainwin.h \
    pwaitingdia.h \
    TaskManager/zadvancedfinddialog.h \
    Sheet/zdatacomparedialog.h

SOURCES += \
    BackupManager/zbackupinfodia.cpp \
    BackupManager/zbackupmanager.cpp \
    BackupManager/zlistbackupinfodia.cpp \
    BasePart/zbaseinfodia.cpp \
    FileManager/pfilemanager.cpp \
    FileManager/zfileinfodia.cpp \
    FileManager/zfolderinfodia.cpp \
    FileManager/zlistfolderfileinfodia.cpp \
    FileManager/zpdfviewer.cpp \
    FormDesigner/pformdesigner.cpp \
    FormDesigner/zbargraphwidget.cpp \
    FormDesigner/zbasewidget.cpp \
    FormDesigner/zcheckboxwidget.cpp \
    FormDesigner/zdatetimewidget.cpp \
    FormDesigner/zforminfodia.cpp \
    FormDesigner/zlinewidget.cpp \
    FormDesigner/zlistforminfodia.cpp \
    FormDesigner/zrectanglewidget.cpp \
    FormDesigner/zspinboxwidget.cpp \
    FormDesigner/ztablewidget.cpp \
    FormDesigner/ztextwidget.cpp \
    KDReports/KDReportsAbstractReportLayout.cpp \
    KDReports/KDReportsAbstractTableElement.cpp \
    KDReports/KDReportsAutoTableElement.cpp \
    KDReports/KDReportsCell.cpp \
    KDReports/KDReportsChartElement.cpp \
    KDReports/KDReportsChartTextObject.cpp \
    KDReports/KDReportsElement.cpp \
    KDReports/KDReportsErrorDetails.cpp \
    KDReports/KDReportsFontScaler.cpp \
    KDReports/KDReportsFrame.cpp \
    KDReports/KDReportsHeader.cpp \
    KDReports/KDReportsHLineElement.cpp \
    KDReports/KDReportsHLineTextObject.cpp \
    KDReports/KDReportsHtmlElement.cpp \
    KDReports/KDReportsImageElement.cpp \
    KDReports/KDReportsLayoutHelper.cpp \
    KDReports/KDReportsMainTable.cpp \
    KDReports/KDReportsPreviewDialog.cpp \
    KDReports/KDReportsPreviewWidget.cpp \
    KDReports/KDReportsReport.cpp \
    KDReports/KDReportsReportBuilder.cpp \
    KDReports/KDReportsSpreadsheetReportLayout.cpp \
    KDReports/KDReportsTableBreakingLogic.cpp \
    KDReports/KDReportsTableBreakingSettingsDialog.cpp \
    KDReports/KDReportsTableElement.cpp \
    KDReports/KDReportsTableLayout.cpp \
    KDReports/KDReportsTextDocReportLayout.cpp \
    KDReports/KDReportsTextDocument.cpp \
    KDReports/KDReportsTextDocumentData.cpp \
    KDReports/KDReportsTextElement.cpp \
    KDReports/KDReportsXmlElementHandler.cpp \
    KDReports/KDReportsXmlElementHandlerV2.cpp \
    KDReports/KDReportsXmlHelper.cpp \
    KDReports/KDReportsXmlParser.cpp \
    Logger/zlogmanager.cpp \
    LoginManager/ploginmanager.cpp \
    NetProtocol/pnetframe.cpp \
    NetProtocol/pnetprotocol.cpp \
    ProcessEditor/pprocesseditor.cpp \
    ProcessEditor/pstepeditor.cpp \
    ProcessEditor/zlinkfileselectdia.cpp \
    ProcessEditor/zlinkroleselectdia.cpp \
    ProcessEditor/zlinktemplateselectdia.cpp \
    ProcessEditor/zlistprocessinfodia.cpp \
    ProcessEditor/zprocessinfodia.cpp \
    Sheet/zauxsheet.cpp \
    Sheet/zcell.cpp \
    Sheet/zcelldelegate.cpp \
    Sheet/zcheckboxcell.cpp \
    Sheet/zsheet.cpp \
    SoftInfo/zsoftinfodia.cpp \
    SysSetup/zsyssetupdia.cpp \
    TaskManager/ptaskmanager.cpp \
    TaskManager/zlistprocesssteplinktemplatedia.cpp \
    TaskManager/zlisttaskdia.cpp \
    TaskManager/zprocesssteplinktemplateselectdia.cpp \
    TaskManager/ztaskinfodia.cpp \
    TaskManager/ztasksheet.cpp \
    TemplateEditor/ptemplateeditor.cpp \
    TemplateEditor/zautovarinfodia.cpp \
    TemplateEditor/zcolorinfodia.cpp \
    TemplateEditor/zcomboboxdia.cpp \
    TemplateEditor/zfontinfodia.cpp \
    TemplateEditor/zframeinfodia.cpp \
    TemplateEditor/zgeneralvarinfodia.cpp \
    TemplateEditor/zlisttemplateinfodia.cpp \
    TemplateEditor/zspinboxdia.cpp \
    TemplateEditor/zsyspicdia.cpp \
    TemplateEditor/ztemplateinfodia.cpp \
    TemplateEditor/zvarinfodia.cpp \
    TemplateEditor/zvarsourceinfodia.cpp \
    UpdateManager/pupdatemanager.cpp \
    UserManager/pusermanagerwin.cpp \
    UserManager/zgrpinfodia.cpp \
    UserManager/zimportroleuserinfodia.cpp \
    UserManager/zlistroleuserinfodia.cpp \
    UserManager/zuserinfodia.cpp \
    main.cpp \
    pgblpara.cpp \
    pmainwin.cpp \
    pwaitingdia.cpp \
    TaskManager/zadvancedfinddialog.cpp \
    Sheet/zdatacomparedialog.cpp


RESOURCES += \
    pms.qrc

RC_FILE += app.rc

DISTFILES += \
    DefaultUI.qss \
    BlueSkin.qss

INCLUDEPATH += $$PWD/FileManager/poppler
DEPENDPATH += $$PWD/FileManager/poppler
LIBS += -L$$PWD/FileManager/poppler -llibpoppler-qt5

INCLUDEPATH += $$PWD/CuteReport
LIBS += -L$$PWD/CuteReport -lCuteDesignerd -lCuteReportCored -lCuteReportWidgetsd -lCuteReportWidgetsThirdpartyd -lPropertyEditord
FORMS += \
    KDReports/previewdialogbase.ui \
    KDReports/tablebreakingdialogbase.ui \
    KDReports/previewdialogbase.ui \
    KDReports/tablebreakingdialogbase.ui

SUBDIRS += \
    PMSManager.pro

