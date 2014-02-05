TEMPLATE = app
TARGET = qt-bfint

# http://stackoverflow.com/questions/2580934/how-to-specify-different-debug-release-output-directories-in-qmake-pro-file/2583548#2583548
DESTDIR = build
OBJECTS_DIR = $${DESTDIR}
MOC_DIR = $${DESTDIR}
RCC_DIR = $${DESTDIR}
UI_DIR = $${DESTDIR}


DEPENDPATH += src
INCLUDEPATH +=

# Input
FORMS   += src/UIMain.ui
HEADERS += src/BFInterpreter.hpp \
           src/UIMain.hpp
SOURCES += src/main.cpp          \
           src/BFInterpreter.cpp \
           src/UIMain.cpp

