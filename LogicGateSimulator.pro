QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    canvas.cpp \
    component.cpp \
    connectionpoint.cpp \
    wire.cpp \
    andgate.cpp \
    inputcomponent.cpp \
    outputcomponent.cpp

HEADERS += \
    mainwindow.h \
    canvas.h \
    component.h \
    connectionpoint.h \
    wire.h \
    andgate.h \
    inputcomponent.h \
    outputcomponent.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target