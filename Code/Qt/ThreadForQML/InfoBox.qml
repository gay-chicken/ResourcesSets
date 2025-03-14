import QtQuick

Item {

    Rectangle {
        anchors.fill: parent

        Text {
            text: "loading..."
            objectName: "qml_text"
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            onClicked: console.log("clicked")
        }
    }
}
