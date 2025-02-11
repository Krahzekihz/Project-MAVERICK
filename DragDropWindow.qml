import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: dragDropWindow
    visible: true
    width: 400
    height: 300
    title: "Drop Your Database Here"

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#f0f0f0"
        border.color: "black"
        border.width: 2
        radius: 10

        Text {
            anchors.centerIn: parent
            text: "Drag and drop your .accdb file here"
            font.pixelSize: 18
        }

        DropArea {
            anchors.fill: parent
            onDropped: (drop) => {
                if (drop.urls.length > 0) {
                    var filePath = drop.urls[0].toString().replace("file://", "")
                    taskManager.openDatabase(filePath)
                }
            }
        }
    }
}
