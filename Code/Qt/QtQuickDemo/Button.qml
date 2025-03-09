import QtQuick

Item {
    property alias text: label.text
    property alias color: button.color
    signal clicked

    id: root
    x: 12; y: 12
    width: 116
    height: 26

    Rectangle {
        id: button
        color: "gray"
        anchors.fill: root

        Text {
            id: label
            text: "Click"
            anchors.centerIn: button
        }

        MouseArea {
            anchors.fill: button
            onClicked: {
                console.log("inside logic")
                root.clicked()
            }
        }
    }
}
