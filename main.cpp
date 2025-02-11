#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "taskmanager.h"

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qDebug() << "Starting MAVERICK...";

    TaskManager taskManager;
    engine.rootContext()->setContextProperty("taskManager", &taskManager);

    engine.load(QUrl(QStringLiteral("qrc:/DragDropWindow.qml")));
    if (engine.rootObjects().isEmpty()) {
        qDebug() << "Error: QML file failed to load!";
        return -1;
    }

    qDebug() << "MAVERICK successfully started!";
    return app.exec();
}
