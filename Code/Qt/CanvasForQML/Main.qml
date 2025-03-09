import QtQuick
import "qrc:/qml"

Window {
    width: 600
    height: 600
    visible: true

    Rectangle {
        width: 600
        height: 600
        border.color: "red"

        SaveDrawBoard {
            width: 300
            height: 300
            anchors.fill: parent
        }
    }


}
