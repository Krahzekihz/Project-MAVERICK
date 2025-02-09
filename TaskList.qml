import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 640
    height: 480
    color: "#f0f0f0"

    Column {
        anchors.fill: parent
        spacing: 10

        // Title
        Text {
            text: "MAVERICK - To-Do List"
            font.bold: true
            font.pointSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Task Input Field
        Row {
            spacing: 10
            TextField {
                id: taskInput
                placeholderText: "Enter a task"
                width: 300
            }
            Button {
                text: "Add"
                onClicked: {
                    taskManager.addTask(taskInput.text)
                    taskInput.text = "" // Clear input after adding
                }
            }
        }

        // Task Sections
        Rectangle {
            width: parent.width
            height: parent.height - 100
            color: "white"
            border.color: "black"

            Column {
                spacing: 10
                anchors.fill: parent

                // Ongoing Tasks
                Text { text: "Ongoing"; font.bold: true }
                ListView {
                    id: ongoingList
                    width: parent.width
                    height: 150
                    model: taskManager.ongoingTasks
                    delegate: TaskDelegate {}
                }

                // Hidden Tasks
                Text { text: "Hidden"; font.bold: true }
                ListView {
                    id: hiddenList
                    width: parent.width
                    height: 100
                    model: taskManager.hiddenTasks
                    delegate: TaskDelegate {}
                }

                // Completed Tasks (Collapsible)
                CheckBox {
                    text: "Show Completed"
                    onCheckedChanged: completedList.visible = checked
                }
                ListView {
                    id: completedList
                    width: parent.width
                    height: 100
                    visible: false
                    model: taskManager.completedTasks
                    delegate: TaskDelegate {}
                }
            }
        }
    }
}
