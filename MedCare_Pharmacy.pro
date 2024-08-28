QT       += core gui
QT += core gui printsupport
QT += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addmemberdialog.cpp \
    billinputdialog.cpp \
    clickablelabel.cpp \
    customercare.cpp \
    customlistwidgetitem.cpp \
    customlistwidgetitemforstaff.cpp \
    custompushbutton.cpp \
    deliveryinputdialog.cpp \
    inputdialog.cpp \
    kanbanboard.cpp \
    main.cpp \
    mainwindow.cpp \
    medicinesmenu.cpp \
    profilemenu.cpp \
    salesandreports.cpp \
    signuppage.cpp \
    sliderdialog.cpp \
    staffmenu.cpp

HEADERS += \
    addmemberdialog.h \
    billinputdialog.h \
    clickablelabel.h \
    customercare.h \
    customlistwidgetitem.h \
    customlistwidgetitemforstaff.h \
    custompushbutton.h \
    deliveryinputdialog.h \
    emailLineEdit.h \
    inputdialog.h \
    kanbanboard.h \
    mainwindow.h \
    medicinesmenu.h \
    phoneinputDialog.h \
    phonelineedit.h \
    profilemenu.h \
    salesandreports.h \
    signuppage.h \
    sliderdialog.h \
    staffmenu.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
   resources.qrc


RESOURCES +=resources.rc


