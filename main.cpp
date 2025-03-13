#include "taskmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TaskManager window;
    window.show();
    return app.exec();
}
