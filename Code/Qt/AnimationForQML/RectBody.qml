import QtQuick

Item {
    signal clicked

    id: root
    width: 50
    height: 50

    Rectangle {
        anchors.fill: root
        color: "red"
    }
    MouseArea {
        anchors.fill: root
        onClicked: root.clicked()
    }

}
