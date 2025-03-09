import QtQuick

Window {
    width: 400
    height: 400
    visible: true
    title: qsTr("Hello World")

    Grid {
        rows: 3
        columns: 3
        spacing: 5

        Repeater {
            id: repeater
            model: 8
            Rectangle {
                required property int index
                width: 50
                height: 50
                color: "yellow"
                Text {
                    anchors.centerIn: parent
                    text: "Cell " + index
                }
            }
        }
    }
}
