QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buffer.cpp \
    evaluation.cpp \
    expression.cpp \
    main.cpp \
    mainwindow.cpp \
    sentence.cpp \
    sentences.cpp \
    statement.cpp \
    tree.cpp \
    variables.cpp

HEADERS += \
    MyString.h \
    buffer.h \
    evaluation.h \
    exception.h \
    expression.h \
    mainwindow.h \
    sentence.h \
    sentences.h \
    statement.h \
    tree.h \
    variables.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
