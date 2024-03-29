QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    expander.cpp \
    geometry.cpp \
    humancontroll.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mouse.cpp \
    qcustomplot.cpp \
    si.cpp \
    simulator.cpp \
    utils.cpp

HEADERS += \
    expander.h \
    geometry.h \
    humancontroll.h \
    mainwindow.h \
    map.h \
    mouse.h \
    qcustomplot.h \
    sensor.h \
    sensor_data.h \
    si.h \
    simulator.h \
    utils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
