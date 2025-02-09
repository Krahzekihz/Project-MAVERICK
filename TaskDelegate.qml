import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: parent.width
    height: 50

    Row {
        spacing: 10
        anchors.fill: parent
        
        CheckBox {
            id: checkBox
            checked: model.status === "Completed"
            onCheckedChanged: taskManager.updateTaskStatus(model.id, checked ? "Completed" : "Ongoing")
        }
        
        Text {
            text: model.taskName
            font.pointSize: 14
            width: 200
            elide: Text.ElideRight
        }
        
        Button {
            text: "Hide"
            onClicked: taskManager.updateTaskStatus(model.id, "Hidden")
        }
    }
}
