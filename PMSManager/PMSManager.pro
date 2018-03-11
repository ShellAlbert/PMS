#-------------------------------------------------
#
# Project created by QtCreator 2016-12-30T13:53:29
#
#-------------------------------------------------

QT       += core gui network printsupport xlsx charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PMSManager

TEMPLATE = app



SOURCES += main.cpp\
        pmainwin.cpp \
    UserManager/pusermanagerwin.cpp \
    UserManager/zgrpinfodia.cpp \
    UserManager/zuserinfodia.cpp \
    pgblpara.cpp \
    TemplateEditor/ptemplateeditor.cpp \
    Sheet/zcell.cpp \
    Sheet/zcelldelegate.cpp \
    Sheet/zcheckboxcell.cpp \
    Sheet/zauxsheet.cpp \
    Sheet/zsheet.cpp \
    TemplateEditor/zgeneralvarinfodia.cpp \
    TemplateEditor/zautovarinfodia.cpp \
    TemplateEditor/zfontinfodia.cpp \
    TemplateEditor/zcolorinfodia.cpp \
    TemplateEditor/zsyspicdia.cpp \
    FileManager/pfilemanager.cpp \
    ProcessEditor/pprocesseditor.cpp \
    ProcessEditor/pstepeditor.cpp \
    NetProtocol/pnetprotocol.cpp \
    NetProtocol/pnetframe.cpp \
    pwaitingdia.cpp \
    BasePart/zbaseinfodia.cpp \
    FileManager/zfolderinfodia.cpp \
    FileManager/zfileinfodia.cpp \
    FileManager/zpdfviewer.cpp \
    UserManager/zlistroleuserinfodia.cpp \
    UserManager/zimportroleuserinfodia.cpp \
    FileManager/zlistfolderfileinfodia.cpp \
    TemplateEditor/ztemplateinfodia.cpp \
    TemplateEditor/zlisttemplateinfodia.cpp \
    ProcessEditor/zprocessinfodia.cpp \
    TemplateEditor/zvarsourceinfodia.cpp \
    TemplateEditor/zvarinfodia.cpp \
    Logger/zlogmanager.cpp \
    TemplateEditor/zframeinfodia.cpp \
    ProcessEditor/zlistprocessinfodia.cpp \
    ProcessEditor/zlinktemplateselectdia.cpp \
    ProcessEditor/zlinkfileselectdia.cpp \
    ProcessEditor/zlinkroleselectdia.cpp \
    TaskManager/ptaskmanager.cpp \
    TaskManager/zlistprocesssteplinktemplatedia.cpp \
    TaskManager/zprocesssteplinktemplateselectdia.cpp \
    TaskManager/ztasksheet.cpp \
    SoftInfo/zsoftinfodia.cpp \
    TaskManager/ztaskinfodia.cpp \
    TaskManager/zlisttaskdia.cpp \
    TemplateEditor/zcomboboxdia.cpp \
    TemplateEditor/zspinboxdia.cpp \
    SysSetup/zsyssetupdia.cpp \
    LoginManager/ploginmanager.cpp \
    FormDesigner/pformdesigner.cpp \
    FormDesigner/ztextwidget.cpp \
    FormDesigner/zbasewidget.cpp \
    FormDesigner/ztablewidget.cpp \
    FormDesigner/zlinewidget.cpp \
    FormDesigner/zcheckboxwidget.cpp \
    FormDesigner/zspinboxwidget.cpp \
    FormDesigner/zdatetimewidget.cpp \
    FormDesigner/zrectanglewidget.cpp \
    UpdateManager/pupdatemanager.cpp \
    FormDesigner/zforminfodia.cpp \
    FormDesigner/zlistforminfodia.cpp \
    BackupManager/zbackupmanager.cpp \
    BackupManager/zbackupinfodia.cpp \
    BackupManager/zlistbackupinfodia.cpp

HEADERS  += pmainwin.h \
    UserManager/pusermanagerwin.h \
    UserManager/zgrpinfodia.h \
    UserManager/zuserinfodia.h \
    pgblpara.h \
    TemplateEditor/ptemplateeditor.h \
    Sheet/zcell.h \
    Sheet/zcelldelegate.h \
    Sheet/zcheckboxcell.h \
    Sheet/zauxsheet.h \
    Sheet/zsheet.h \
    TemplateEditor/zautovarinfodia.h \
    TemplateEditor/zgeneralvarinfodia.h \
    TemplateEditor/zfontinfodia.h \
    TemplateEditor/zcolorinfodia.h \
    TemplateEditor/zsyspicdia.h \
    FileManager/pfilemanager.h \
    ProcessEditor/pprocesseditor.h \
    ProcessEditor/pstepeditor.h \
    NetProtocol/pnetprotocol.h \
    NetProtocol/pnetframe.h \
    pwaitingdia.h \
    BasePart/zbaseinfodia.h \
    FileManager/zfolderinfodia.h \
    FileManager/zfileinfodia.h \
    FileManager/zpdfviewer.h \
    UserManager/zlistroleuserinfodia.h \
    UserManager/zimportroleuserinfodia.h \
    FileManager/zlistfolderfileinfodia.h \
    TemplateEditor/ztemplateinfodia.h \
    TemplateEditor/zlisttemplateinfodia.h \
    ProcessEditor/zprocessinfodia.h \
    TemplateEditor/zvarsourceinfodia.h \
    TemplateEditor/zvarinfodia.h \
    Logger/zlogmanager.h \
    TemplateEditor/zframeinfodia.h \
    ProcessEditor/zlistprocessinfodia.h \
    ProcessEditor/zlinktemplateselectdia.h \
    ProcessEditor/zlinkfileselectdia.h \
    ProcessEditor/zlinkroleselectdia.h \
    TaskManager/ptaskmanager.h \
    TaskManager/zlistprocesssteplinktemplatedia.h \
    TaskManager/zprocesssteplinktemplateselectdia.h \
    TaskManager/ztasksheet.h \
    SoftInfo/zsoftinfodia.h \
    TaskManager/ztaskinfodia.h \
    TaskManager/zlisttaskdia.h \
    TemplateEditor/zcomboboxdia.h \
    TemplateEditor/zspinboxdia.h \
    SysSetup/zsyssetupdia.h \
    LoginManager/ploginmanager.h \
    FormDesigner/pformdesigner.h \
    FormDesigner/ztextwidget.h \
    FormDesigner/zbasewidget.h \
    FormDesigner/ztablewidget.h \
    FormDesigner/zlinewidget.h \
    FormDesigner/zcheckboxwidget.h \
    FormDesigner/zspinboxwidget.h \
    FormDesigner/zdatetimewidget.h \
    FormDesigner/zrectanglewidget.h \
    UpdateManager/pupdatemanager.h \
    FormDesigner/zforminfodia.h \
    FormDesigner/zlistforminfodia.h \
    BackupManager/zbackupmanager.h \
    BackupManager/zbackupinfodia.h \
    BackupManager/zlistbackupinfodia.h

RESOURCES += \
    pms.qrc

RC_FILE += app.rc

DISTFILES += \
    DefaultUI.qss \
    BlueSkin.qss

INCLUDEPATH += $$PWD/FileManager/poppler
DEPENDPATH += $$PWD/FileManager/poppler
LIBS += -L$$PWD/FileManager/poppler -llibpoppler-qt5
