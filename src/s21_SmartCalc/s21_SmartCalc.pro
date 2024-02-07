QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../calculate.c \
    ../credit.c \
    ../deposit.c \
    ../helpfunc.c \
    ../parser.c \
    creditwindow.cpp \
    depositwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../calc.h \
    creditwindow.h \
    depositwindow.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    creditwindow.ui \
    depositwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    s21_SmartCalc.pro.user
