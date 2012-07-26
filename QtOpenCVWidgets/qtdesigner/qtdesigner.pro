CONFIG      += designer plugin debug_and_release
TARGET      = $$qtLibraryTarget(CQtOpenCVCollection)
TEMPLATE    = lib

DEFINES += QDESIGNER_EXPORT_WIDGETS

#HEADERS     = cqtopencvcapturewidgetplugin.h cqtopencvimagewidgetplugin.h cqtopencvcannywidgetplugin.h cqtopencvcollection.h
#SOURCES     = cqtopencvcapturewidgetplugin.cpp cqtopencvimagewidgetplugin.cpp cqtopencvcannywidgetplugin.cpp cqtopencvcollection.cpp
HEADERS     = cqtopencvcapturewidgetplugin.h  cqtopencvcollection.h
SOURCES     = cqtopencvcapturewidgetplugin.cpp cqtopencvcollection.cpp
RESOURCES   = icons.qrc

//target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

#include(cqtopencvimagewidget.pri)
include(cqtopencvcapturewidget.pri)
#include(cqtopencvcannywidget.pri)

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/release/ -lQtOpenCVCapture
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib/debug/ -lQtOpenCVCapture
#else:symbian: LIBS += -lQtOpenCVCapture
#else:
unix: LIBS += -L/usr/lib/ -lQtOpenCVCaptureWidget
# -lQtOpenCVCapture

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
