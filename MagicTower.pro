#-------------------------------------------------
#
# Project created by QtCreator 2015-01-02T19:25:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MagicTower
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Hero.cpp \
    Tower_Map.cpp \
    ExternVar.cpp \
    fightwidget.cpp \
    fightfalsemsg.cpp \
    conversationwidget.cpp \
    aboutwidget.cpp \
    SaveLoadFunction.cpp

HEADERS  += mainwindow.h \
    Hero.h \
    Tower_Map.h \
    ExternVar.h \
    fightwidget.h \
    fightfalsemsg.h \
    conversationwidget.h \
    aboutwidget.h \
    SaveLoadFunction.h

FORMS    += mainwindow.ui \
    fightwidget.ui \
    fightfalsemsg.ui \
    conversationwidget.ui \
    aboutwidget.ui

RESOURCES += \
    src.qrc

OTHER_FILES +=
RC_FILE +=  \
    MagicTower.rc
