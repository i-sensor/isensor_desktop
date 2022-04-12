QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    NetworkManager/NetworkManager.cpp \
    SettingManager/SettingManager.cpp \
    main.cpp \
    isensor.cpp \
    Logger/Logger.cpp

HEADERS += \
    Constants/Constants.h \
    NetworkManager/NetworkManager.h \
    SettingManager/SettingManager.h \
    isensor.h \
    Logger/Logger.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ISensorSettings.ini
