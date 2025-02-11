QT       += core gui sql widgets  # Include necessary Qt modules
CONFIG   += c++17                # Set C++ standard to C++17

# Specify the source files
SOURCES  += main.cpp \
            taskmanager.cpp \
            database.cpp

# Specify the header files
HEADERS  += taskmanager.h \
            database.h

# Specify resource files (if you have QML files)
RESOURCES += qml.qrc