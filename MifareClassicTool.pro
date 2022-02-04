QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Sources/apducommand.cpp \
    Sources/connect.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/mainwindowuiedit.cpp \
    Sources/scardoperations.cpp


HEADERS += \
    Headers/apducommand.h \
    Headers/commands.h \
    Headers/connect.h \
    Headers/mainwindow.h \
    Headers/scardoperations.h


FORMS += \
    Forms/mainwindow.ui

LIBS += -lwinscard -lz

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
