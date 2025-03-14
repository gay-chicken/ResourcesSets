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

        ProgressBar {
            from: 0
            to: 360
            value: item.speed
        }
    }
}
