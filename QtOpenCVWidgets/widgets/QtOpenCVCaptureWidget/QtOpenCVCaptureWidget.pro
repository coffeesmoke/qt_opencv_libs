#-------------------------------------------------
#
# Project created by QtCreator 2012-06-21T12:34:55
#
#-------------------------------------------------

TARGET = QtOpenCVCaptureWidget
TARGET = $$qtLibraryTarget($$TARGET)
TEMPLATE = lib

DEFINES += QDESIGNER_EXPORT_WIDGETS

SOURCES += cqtopencvcapturewidget.cpp

HEADERS += cqtopencvcapturewidget.h\
    ../../runtime/capture/QtOpenCVCapture/cqtopencvcaptureobject.h \
    ../../include/qtopencv_global.h

#symbian {
#    MMP_RULES += EXPORTUNFROZEN
#    TARGET.UID3 = 0xE5C56A40
#    TARGET.CAPABILITY =
#    TARGET.EPOCALLOWDLLDATA = 1
#    addFiles.sources = QtOpenCVCaptureWidget.dll
#    addFiles.path = !:/sys/bin
#    DEPLOYMENT += addFiles
#}

unix:!symbian {
#    maemo5 {
#        target.path = /opt/usr/lib
#    } else {
        target.path = /usr/lib
#    }
    INSTALLS += target
}

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../runtime/capture/QtOpenCVCapture/release/ -lQtOpenCVCapture
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../runtime/capture/QtOpenCVCapture/debug/ -lQtOpenCVCapture
#else:symbian: LIBS += -lQtOpenCVCapture
#else:
unix: LIBS += -L/usr/lib -lQtOpenCVCapture

INCLUDEPATH += $$PWD/../../runtime/capture/QtOpenCVCapture

DEPENDPATH += /usr/lib
