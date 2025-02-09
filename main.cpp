#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "taskmanager.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    TaskManager taskManager;
    engine.rootContext()->setContextProperty("taskManager", &taskManager);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
