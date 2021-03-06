TEMPLATE = app
TARGET   = qt-bfint
VERSION  = 0.2b

# for access in code
DEFINES += PROJECTVERSION=$$VERSION

# https://qt-project.org/doc/qt-5/qmake-variable-reference.html
DESTDIR = bin
BUILDDIR = build
OBJECTS_DIR = $${BUILDDIR}
MOC_DIR = $${BUILDDIR}
RCC_DIR = $${BUILDDIR}
UI_DIR = $${BUILDDIR}

DEPENDPATH += src 
INCLUDEPATH +=

# Input
FORMS   += src/UIMain.ui
HEADERS += src/BFInterpreter.hpp \
           src/UIMain.hpp
SOURCES += src/main.cpp          \
           src/BFInterpreter.cpp \
           src/UIMain.cpp
RESOURCES += resources/qt-bfint.qrc
