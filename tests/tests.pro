QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++17

TEMPLATE = app

CORE_PATH = ../player/core

INCLUDEPATH += $$CORE_PATH

SOURCES += \
    $$CORE_PATH/UserConfig.cpp \
    $$CORE_PATH/PlaylistConfig.cpp \
    $$CORE_PATH/Track.cpp \

SOURCES +=  \
    tst_player.cpp
