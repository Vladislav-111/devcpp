QT       += core gui
include ($$PWD/../Qt-Secret/src/Qt-Secret.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    crypt.cpp \
    customwidget.cpp \
    jsonModel.cpp \
    main.cpp \
    mainwindow.cpp \
    siteAdd.cpp \
    siteList.cpp

HEADERS += \
    crypt.h \
    customwidget.h \
    jsonModel.h \
    mainwindow.h \
    siteAdd.h \
    siteList.h

FORMS += \
    customwidget.ui \
    mainwindow.ui \
    siteAdd.ui \
    siteList.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
