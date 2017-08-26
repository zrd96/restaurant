#-------------------------------------------------
#
# Project created by QtCreator 2017-08-10T19:09:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = restaurant
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    logindlg.cpp \
    admin.cpp \
    cart.cpp \
    chef.cpp \
    clerk.cpp \
    dish.cpp \
    guest.cpp \
    msg.cpp \
    mysqlmanager.cpp \
    person.cpp \
    staticdata.cpp \
    table.cpp \
    tools.cpp \
    guestwindow.cpp \
    chefwindow.cpp \
    clerkwindow.cpp \
    adminwindow.cpp

HEADERS += \
    logindlg.h \
    admin.h \
    cart.h \
    chef.h \
    clerk.h \
    datamanager.h \
    dish.h \
    guest.h \
    msg.h \
    mysqlmanager.h \
    person.h \
    staticdata.h \
    table.h \
    tools.h \
    guestwindow.h \
    chefwindow.h \
    clerkwindow.h \
    adminwindow.h

FORMS += \
    logindlg.ui \
    chefwindow.ui \
    guestwindow.ui \
    clerkwindow.ui \
    adminwindow.ui
