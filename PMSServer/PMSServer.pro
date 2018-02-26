#-------------------------------------------------
#
# Project created by QtCreator 2017-01-06T15:22:28
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PMSServer
TEMPLATE = app


SOURCES += main.cpp\
        pmainwin.cpp \
    TcpServer/ptcpserver.cpp \
    NetPro/pnetpro.cpp \
    NetPro/pnetfrmrole.cpp \
    NetPro/pnetfrmuser.cpp \
    NetPro/pnetfrm.cpp \
    NetPro/pnetfrmfolder.cpp \
    NetPro/pnetfrmfile.cpp \
    NetPro/pnetfrmtemplate.cpp \
    NetPro/pnetfrmheartbeat.cpp \
    NetPro/pnetfrmprocess.cpp \
    NetPro/pnetfrmvarsource.cpp \
    NetPro/pnetfrmtask.cpp \
    NetPro/pnetfrmlogin.cpp \
    AES/TAesClass.cpp \
    NetPro/pnetfrmform.cpp \
    NetPro/pnetfrmbackup.cpp \
    pgblpara.cpp

HEADERS  += pmainwin.h \
    TcpServer/ptcpserver.h \
    NetPro/pnetpro.h \
    NetPro/pnetfrmrole.h \
    NetPro/pnetfrmuser.h \
    NetPro/pnetfrm.h \
    NetPro/pnetfrmfolder.h \
    NetPro/pnetfrmfile.h \
    NetPro/pnetfrmtemplate.h \
    NetPro/pnetfrmheartbeat.h \
    NetPro/pnetfrmprocess.h \
    NetPro/pnetfrmvarsource.h \
    NetPro/pnetfrmtask.h \
    NetPro/pnetfrmlogin.h \
    AES/TAesClass.h \
    NetPro/pnetfrmform.h \
    NetPro/pnetfrmbackup.h \
    pgblpara.h

RESOURCES += \
    pmsres.qrc
