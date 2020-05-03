#-------------------------------------------------
#
# Project created by QtCreator 2018-03-17T19:59:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OfxGet
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

CONFIG(debug, debug|release) {
  DEFINES += OFXHOME_DEBUG
}
CONFIG(release, debug|release) {
  DEFINES += OFXHOME_RELEASE
}

SOURCES += \
    main.cpp \
    ofxget/ofxget.cc \
    ofxget/ofxhome.cc \
    ofxget/pugixml/pugixml.cpp \
    download.cpp \
    ofxget_widget.cpp \
    varswidget.cpp \
    deselectable_list_widget.cc \
    ofxhomeworker.cpp \
    waitingdialog.cpp \
    ofxgetmainwindow.cpp \
    preferences.cpp

HEADERS += \
    ofxget/ofxget.h \
    ofxget/ofxget_apps.h \
    ofxget/ofxhome.h \
    ofxget/pugixml/pugiconfig.hpp \
    ofxget/pugixml/pugixml.hpp \
    download.h \
    ofxget_widget.h \
    varswidget.h \
    deselectable_list_widget.h \
    ofxhomeworker.h \
    waitingdialog.h \
    ofxgetmainwindow.h \
    preferences.h

FORMS += \
    ofxget.ui \
    download.ui \
    waitingdialog.ui \
    ofxgetmainwindow.ui \
    preferences.ui

LIBS += -lcurl

RESOURCES += \
    textfiles.qrc \
    icons.qrc

DISTFILES += \
  ofxget/requests/accounts.txt \
  ofxget/requests/badrequest.txt \
  ofxget/requests/bank.txt \
  ofxget/requests/investment.txt \
  ofxget/requests/investment203.txt
