# #####################################################################
# Automatically generated by qmake (2.01a) mer. dc. 2 10:12:42 2009
# #####################################################################
TEMPLATE = app
TARGET = QtShanoirDownload
DEPENDPATH += .

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.5

macx {

}

win32 {

}


INCLUDEPATH += .
INCLUDEPATH +=
DEFINES += 

CONFIG += x86_64 \
    Gui \
    xml

win32:CONFIG += release

include (qtsoap/src/qtsoap.pri)

LIBS += -L$$VISTAL_LIB_PATH

# Input
HEADERS += qt_shanoir.h \
    shanoirserverparameters.h

FORMS += qt_shanoir.ui \
    shanoirserverparameters.ui

SOURCES += main.cpp \
    qt_shanoir.cpp \
    shanoirserverparameters.cpp

QMAKE_INFO_PLIST = Info.plist
OTHER_FILES += Info.plist \
    css/MRView.css

ICON = IconeQuickMRView.icns

RESOURCES += css.qrc \
    icones.qrc