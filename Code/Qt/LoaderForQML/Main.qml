import QtQuick
import "qrc:/qml"

Window {
    id: root
    width: 640
    height: 480
    visible: true

    DataLoad {
        id: dataload
        width: 300
        height: 300
        anchors.centerIn: parent
        state: "text"
        speed: 200
    }

    Row {
        property bool isChecked: true

        id: row
        width: parent.width
        height: parent.height / 6
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            width: root.width / 2
            height: parent.height
            color: row.isChecked ? "green" : "gray"

            Text {
                anchors.centerIn: parent
                text: "TextShow"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    row.isChecked = !row.isChecked
                    dataload.state = "text"
                }
            }
        }

        Rectangle {
            width: root.width / 2
            height: parent.height
            color: parent.isChecked ? "gray" : "green"

            Text {
                anchors.centerIn: parent
                text: "DrawShow"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    row.isChecked = !row.isChecked
                    dataload.state = "draw"
                }
            }
        }
    }
}
