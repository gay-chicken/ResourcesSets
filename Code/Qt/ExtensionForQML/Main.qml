import QtQuick

Window {
    width: 640
    height: 480
    visible: true

    Text {
        text: current === undefined ? "loading..." : current
        anchors.centerIn: parent
    }
}
