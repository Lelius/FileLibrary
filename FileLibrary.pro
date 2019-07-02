#-------------------------------------------------
#
# Project created by QtCreator 2019-06-07T10:27:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileLibrary
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

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    listform.cpp \
    cardeditform.cpp \
    exitform.cpp \
    cardinformation.cpp \
    applicabilitycard.cpp \
    changeaccountingcard.cpp \
    copyaccounting.cpp \
    issuanceofcopies.cpp \
    newfilelibraryform.cpp \
    cardviewform.cpp \
    applicabilityminiform.cpp \
    changeaccountingminiform.cpp \
    copyaccountingminiform.cpp

HEADERS += \
        mainwindow.h \
    listform.h \
    cardeditform.h \
    exitform.h \
    cardinformation.h \
    applicabilitycard.h \
    changeaccountingcard.h \
    copyaccounting.h \
    issuanceofcopies.h \
    newfilelibraryform.h \
    cardviewform.h \
    applicabilityminiform.h \
    changeaccountingminiform.h \
    copyaccountingminiform.h

FORMS += \
        mainwindow.ui \
    listform.ui \
    cardeditform.ui \
    exitform.ui \
    newfilelibraryform.ui \
    cardviewform.ui \
    applicabilityminiform.ui \
    changeaccountingminiform.ui \
    copyaccountingminiform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
