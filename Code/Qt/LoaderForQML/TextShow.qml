import QtQuick
import QtQuick.Controls

Item {
    property real speed: 0

    id: item

    Row {
        anchors.centerIn: parent

        Label {
            text: "Speed: "
        }

        Text {
            text: item.speed
        }
    }
}
