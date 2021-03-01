QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SRCPATH = ../player/src

INCLUDEPATH += $$SRCPATH

SOURCES += \
    $$SRCPATH/UserConfig.cpp \

SOURCES +=  \
    tst_player.cpp
