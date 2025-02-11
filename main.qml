import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "MAVERICK"
    visible: false

    Connections {
        target: taskManager
        function onDatabaseConnected() {
            mainWindow.visible = true
            dragDropWindow.visible = false
        }
    }
}
