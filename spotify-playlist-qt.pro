QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    player/src/MainWindow.cpp \
    player/src/PlaylistDialog.cpp \
    player/src/PlaylistWizardDialog.cpp \
    player/src/SearchDialog.cpp \
    player/src/UserDialog.cpp \
    player/src/main.cpp

HEADERS += \
    player/src/MainWindow.hpp \
    player/src/PlaylistDialog.hpp \
    player/src/PlaylistWizardDialog.hpp \
    player/src/SearchDialog.hpp \
    player/src/UserDialog.hpp

FORMS += \
    player/form/MainWindow.ui \
    player/form/PlaylistDialog.ui \
    player/form/PlaylistWizardDialog.ui \
    player/form/SearchDialog.ui \
    player/form/UserDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
