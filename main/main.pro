QT      += core
QT      += gui
QT      += widgets
QT      += charts
QT      += sql
QT      += quickcontrols2
QT      += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    admintableviewaction.cpp \
    adminwindow.cpp \
    authwindow.cpp \
    center.cpp \
    centertableviewaction.cpp \
    centerwindow.cpp \
    config.cpp \
    createadminwindow.cpp \
    createcenterwindow.cpp \
    editadminwindow.cpp \
    editcenterwindow.cpp \
    evictwindow.cpp \
    family.cpp \
    functions.cpp \
    group.cpp \
    initials.cpp \
    main.cpp \
    mainwindow.cpp \
    migrant.cpp \
    migranttableviewaction.cpp \
    moreinfowindow.cpp \
    mymessagebox.cpp \
    myvalidator.cpp \
    personal.cpp \
    reportwindow.cpp \
    rootapplywindow.cpp \
    searchadminwindow.cpp \
    settlementwindow.cpp

HEADERS += \
    admin.h \
    admintableviewaction.h \
    adminwindow.h \
    authwindow.h \
    center.h \
    centertableviewaction.h \
    centerwindow.h \
    config.h \
    createadminwindow.h \
    createcenterwindow.h \
    editadminwindow.h \
    editcenterwindow.h \
    evictwindow.h \
    family.h \
    functions.h \
    group.h \
    headers.h \
    initials.h \
    mainwindow.h \
    migrant.h \
    migranttableviewaction.h \
    moreinfowindow.h \
    mymessagebox.h \
    mytableviewaction.h \
    myvalidator.h \
    personal.h \
    reportwindow.h \
    rootapplywindow.h \
    searchadminwindow.h \
    settlementwindow.h

FORMS += \
    adminwindow.ui \
    authwindow.ui \
    centerwindow.ui \
    createadminwindow.ui \
    createcenterwindow.ui \
    editadminwindow.ui \
    editcenterwindow.ui \
    evictwindow.ui \
    mainwindow.ui \
    moreinfowindow.ui \
    reportwindow.ui \
    rootapplywindow.ui \
    searchadminwindow.ui \
    settlementwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

DISTFILES += \

