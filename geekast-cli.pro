#-------------------------------------------------
#
# Project created by QtCreator 2011-03-26T23:51:46
#
#-------------------------------------------------

QT       += core \
            testlib \
            xml \
            network
QT       -= gui
TARGET = geekast-cli
CONFIG   += console
CONFIG   += qxt
QXT     += core
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    core.cpp \
    push.cpp \
    core_linux.cpp
#LIBS += -lsigar
LIBS += -L/usr/local/lib/ \
    -lQxtCore
LIBS += -Lexternal/hyperic-sigar-1.6.4/sigar-bin/lib/
LIBS += -L/externals/qxmpp/lib/libqxmpp.a \
        -lsigar-amd64-linux \
        -lqjson


HEADERS += \
    main.h \
    core.h \
    push.h \
    core_linux.h
INCLUDEPATH += external/hyperic-sigar-1.6.4/sigar-bin/include
INCLUDEPATH += /usr/include/qxt/
INCLUDEPATH += /usr/include/qxt/QxtCore
INCLUDEPATH += ./externals/
INCLUDEPATH += ./externals/qxmpp/src/
INCLUDEPATH += /usr/include/qjson
