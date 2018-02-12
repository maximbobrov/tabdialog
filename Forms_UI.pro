QT       += core gui sql printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



TARGET = "Forms Generator"
TEMPLATE = app

HEADERS       = tabdialog.h \
    pages.h \
    aes256.h \
    QRCodeGenerator.h \
    mypixmaplabel.h \
    commondata.h \
    mytranslatable.h \
    mysqltablemodel.h \
    dialog.h \
    dialog1.h \
    dialog2.h \
    mycoolbutton.h
SOURCES       = main.cpp \
                tabdialog.cpp \
    pages.cpp \
    generateformspage.cpp \
    aes256.c \
    QRCodeGenerator.cpp \
    mypixmaplabel.cpp \
    printandpreviewpage.cpp \
    commondata.cpp \
    edittablespage.cpp \
    mytranslatable.cpp \
    mysqltablemodel.cpp \
    dialog.cpp \
    dialog1.cpp \
    dialog2.cpp \
    mycoolbutton.cpp


RESOURCES += \
    tabdialog.qrc

LIBS         +=  -lpoppler-qt5
TRANSLATIONS += QtLanguage_ru.ts

VERSION = 1.0.0.1

DISTFILES +=
