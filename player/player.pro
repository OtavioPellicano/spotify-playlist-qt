QT       += core gui network networkauth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    client/dialog/MainWindow.cpp \
    client/dialog/PlaylistDialog.cpp \
    client/dialog/PlaylistWizardDialog.cpp \
    client/dialog/SearchDialog.cpp \
    client/dialog/UserDialog.cpp \
    core/UserConfig.cpp \
    core/Spotify.cpp

HEADERS += \
    client/dialog/MainWindow.hpp \
    client/dialog/PlaylistDialog.hpp \
    client/dialog/PlaylistWizardDialog.hpp \
    client/dialog/SearchDialog.hpp \
    client/dialog/UserDialog.hpp \
    core/UserConfig.hpp \
    core/Spotify.hpp

FORMS += \
    client/form/MainWindow.ui \
    client/form/PlaylistDialog.ui \
    client/form/PlaylistWizardDialog.ui \
    client/form/SearchDialog.ui \
    client/form/UserDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
