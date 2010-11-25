TEMPLATE = app
TARGET = 
DEPENDPATH += . \
    src \
    src\ui
INCLUDEPATH += .

# Input
HEADERS += include/plugininterface.h \
src/pluginsystem.h \
    src/ui/card.h \
    src/ui/renderer.h \
    src/ui/player.h \
    src/mainwindow.h \
    src/cardgameengine.h
FORMS += src/mainwindow.ui
SOURCES += src/pluginsystem.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/cardgameengine.cpp \
    src/ui/renderer.cpp \
    src/ui/player.cpp
OTHER_FILES += 
RESOURCES += qBang.qrc
