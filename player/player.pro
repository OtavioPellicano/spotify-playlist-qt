QT       += core gui network networkauth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/Player.cpp \
    core/SearchResults.cpp \
    core/Track.cpp \
    main.cpp \
    client/dialog/MainWindow.cpp \
    client/dialog/UserDialog.cpp \
    core/UserConfig.cpp \
    core/Spotify.cpp

HEADERS += \
    client/dialog/MainWindow.hpp \
    client/dialog/UserDialog.hpp \
    core/Player.hpp \
    core/SearchResults.hpp \
    core/Track.hpp \
    core/UserConfig.hpp \
    core/Spotify.hpp

FORMS += \
    client/form/MainWindow.ui \
    client/form/UserDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
