QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    gameover.cpp \
    home.cpp \
    main.cpp \
    map.cpp \
    mapmulti.cpp \
    multi.cpp \
    single.cpp

HEADERS += \
    about.h \
    clickablelabel.h \
    gameover.h \
    home.h \
    map.h \
    mapmulti.h \
    multi.h \
    single.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/cheese.png \
    images/milk.png \
    images/steak.png

RESOURCES += \
    resources.qrc
