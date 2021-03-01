QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/MainWindow.cpp \
    src/PlaylistDialog.cpp \
    src/PlaylistWizardDialog.cpp \
    src/SearchDialog.cpp \
    src/UserConfig.cpp \
    src/UserDialog.cpp \
    src/main.cpp

HEADERS += \
    src/MainWindow.hpp \
    src/PlaylistDialog.hpp \
    src/PlaylistWizardDialog.hpp \
    src/SearchDialog.hpp \
    src/UserConfig.hpp \
    src/UserDialog.hpp

FORMS += \
    form/MainWindow.ui \
    form/PlaylistDialog.ui \
    form/PlaylistWizardDialog.ui \
    form/SearchDialog.ui \
    form/UserDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
