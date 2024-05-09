QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminpage.cpp \
    agespinboxdelegate.cpp \
    floatspinboxdelegate.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    rolecltdialog.cpp \
    settingpage.cpp \
    tcomboxdelegate.cpp \
    userpage.cpp

HEADERS += \
    adminpage.h \
    agespinboxdelegate.h \
    const.h \
    floatspinboxdelegate.h \
    logindialog.h \
    mainwindow.h \
    rolecltdialog.h \
    settingpage.h \
    tcomboxdelegate.h \
    userpage.h

FORMS += \
    adminpage.ui \
    logindialog.ui \
    mainwindow.ui \
    rolecltdialog.ui \
    settingpage.ui \
    userpage.ui

INCLUDEPATH += D:\develop\opencv\opencv-build\install\include
LIBS += D:\develop\opencv\opencv-build\lib\libopencv_*.a


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    res.qrc
