#-------------------------------------------------
#
# Project created by QtCreator 2020-07-23T10:55:28
#
#-------------------------------------------------

QT       += core gui network serialbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CANDI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += \
        widgets \
        src \
        src\can \

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        src/can/candi_interface.cpp \
        src\candi_version.cpp \
        src\debug.cpp \
        src\directory.cpp \
        widgets/about_widget.cpp \
        widgets/base_widget.cpp \
        widgets/monitor_widget.cpp

HEADERS += \
        mainwindow.h \
        src/can/candi_interface.hpp \
        src\candi_version.h \
        src\debug.hpp \
        src\directory.hpp \
        widgets/about_widget.hpp \
        widgets/base_widget.hpp \
        widgets/monitor_widget.hpp

FORMS += \
        mainwindow.ui \
        ui/about.ui \
        ui/can_connect.ui \
        ui/can_viewer.ui

UI_DIR = ui_generated/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
