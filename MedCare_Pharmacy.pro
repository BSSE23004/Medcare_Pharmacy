QT       += core gui
QT += core gui printsupport
QT += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    billinputdialog.cpp \
    customercare.cpp \
    customlistwidgetitem.cpp \
    customlistwidgetitemforstaff.cpp \
    custompushbutton.cpp \
    deliveryinputdialog.cpp \
    inputdialog.cpp \
    kanbanboard.cpp \
    main.cpp \
    mainwindow.cpp \
    salesandreports.cpp \
    staffmenu.cpp

HEADERS += \
    billinputdialog.h \
    customercare.h \
    customlistwidgetitem.h \
    customlistwidgetitemforstaff.h \
    custompushbutton.h \
    deliveryinputdialog.h \
    inputdialog.h \
    kanbanListWidget.h \
    kanbanboard.h \
    mainwindow.h \
    phonelineedit.h \
    salesandreports.h \
    staffmenu.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
   resources.qrc


RESOURCES +=resources.rc


