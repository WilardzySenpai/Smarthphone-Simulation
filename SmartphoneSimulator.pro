QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = SmartphoneSimulator
TEMPLATE = app

SOURCES += \
    main.cpp \
    camera.cpp \
    musicplayer.cpp \
    smartphone.cpp \
    mainwindow.cpp

HEADERS += \
    camera.h \
    musicplayer.h \
    smartphone.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target