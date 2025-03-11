QT += core gui widgets sql multimedia

TARGET = MAVERICK
TEMPLATE = app
RESOURCES += resources.qrc


SOURCES += main.cpp \
           mainwindow.cpp \
           taskmanager.cpp \
           calendar.cpp \
           eisenhower.cpp \
           pomodoro.cpp

HEADERS += mainwindow.h \
           taskmanager.h \
           calendar.h \
           eisenhower.h \
           pomodoro.h

FORMS += mainwindow.ui \
         taskmanager.ui \
         calendar.ui \
         eisenhower.ui \
         pomodoro.ui
