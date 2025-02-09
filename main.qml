import QtQuick 2.9
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "MAVERICK"

    ColumnLayout {
        anchors.fill: parent

        TextField {
            id: taskName
            placeholderText: "Enter Task Name"
        }

        Button {
            text: "Add Task"
            onClicked: taskManager.addTask(taskName.text, "Test Tag", "2025-02-15")
        }

        Button {
            text: "Export to Text File"
            onClicked: taskManager.exportTasksToTxt()
        }
    }
}
