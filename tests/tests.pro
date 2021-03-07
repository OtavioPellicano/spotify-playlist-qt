QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

CORE_PATH = ../player/core

INCLUDEPATH += $$CORE_PATH

SOURCES += \
    $$CORE_PATH/UserConfig.cpp \

SOURCES +=  \
    tst_player.cpp
