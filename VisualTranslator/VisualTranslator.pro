TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11 qml_debug

SOURCES += main.cpp \
    model/yantranslate.cpp \
    model/instapicture.cpp \
    controller/appmanager.cpp \
    model/translator.cpp

RESOURCES += view/qml.qrc \
    view/image.qrc
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    model/yantranslate.h \
    model/instapicture.h \
    appmanager.h \
    controller/appmanager.h \
    model/translator.h
