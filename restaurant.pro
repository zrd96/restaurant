#-------------------------------------------------
#
# Project created by QtCreator 2017-08-10T19:09:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = restaurant
TEMPLATE = app

LIBS += -L/usr/lib/mysql -lmysqlclient

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
    adminwindow.cpp \
    item.cpp \
    tableitem.cpp \
    aboutmewidget.cpp \
    rateitem.cpp \
    order.cpp \
    orderitem.cpp \
    rate.cpp \
    emptyresult.cpp \
    dishinfo.cpp \
    comment.cpp \
    dishinfohead.cpp \
    manager.cpp \
    managerwindow.cpp \
    messagedlg.cpp \
    aboutmechefpart.cpp \
    aboutmeclerkpart.cpp

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
    adminwindow.h \
    item.h \
    tableitem.h \
    aboutmewidget.h \
    rateitem.h \
    order.h \
    orderitem.h \
    rate.h \
    emptyresult.h \
    dishinfo.h \
    comment.h \
    dishinfohead.h \
    manager.h \
    managerwindow.h \
    messagedlg.h \
    aboutmechefpart.h \
    aboutmeclerkpart.h

FORMS += \
    logindlg.ui \
    chefwindow.ui \
    guestwindow.ui \
    clerkwindow.ui \
    adminwindow.ui \
    item.ui \
    tableitem.ui \
    aboutmewidget.ui \
    rateitem.ui \
    orderitem.ui \
    dishinfo.ui \
    comment.ui \
    dishinfohead.ui \
    managerwindow.ui \
    messagedlg.ui \
    aboutmechefpart.ui \
    aboutmeclerkpart.ui

RESOURCES += \
    res.qrc

DISTFILES +=
