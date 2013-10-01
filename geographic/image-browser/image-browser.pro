######################################################################
# Automatically generated by qmake (2.01a) Tue Oct 1 08:45:46 2013
######################################################################

QT += core gui webkit widgets webkitwidgets

TEMPLATE = app

DEPENDPATH += . src src/gui
INCLUDEPATH += . src/gui

#  Set destination base paths
debug:BUILD_BASE=debug
release:BUILD_BASE=release

#  Set destination directory
DESTDIR=$$BUILD_BASE

#  Set moc and object paths
OBJECTS_DIR =$$BUILD_BASE/build
MOC_DIR     =$$BUILD_BASE/build

# Input
HEADERS +=                      src/core/*.hpp  src/gui/*.hpp
SOURCES += src/imagebrowser.cpp src/core/*.cpp  src/gui/*.cpp


unix:!macx{

	message("using unix")

    TARGET = ImageBrowser.bin
    
    # Set the desired application icon
    ICON = ImageBrowser.icns

    #  GDAL Library
    #INCLUDEPATH += /usr/include/gdal
    #LIBS += -lgdal

    # Boost Library
    LIBS += -lboost_system -lboost_filesystem


}

