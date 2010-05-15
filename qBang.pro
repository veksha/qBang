TEMPLATE = app
TARGET = 
DEPENDPATH += . \
    src \
    src\ui
INCLUDEPATH += .

# Input
HEADERS += src/ui/card.h \
    src/ui/renderer.h \
    src/ui/player.h \
    src/mainwindow.h \
    src/logic.h
    
FORMS += src/mainwindow.ui
SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/logic.cpp \
    src/ui/renderer.cpp \    
    src/ui/player.cpp
