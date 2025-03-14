import QtQuick
import QtMultimedia
import "qrc:/qml"

Window {
    width: 640
    height: 480
    visible: true
    color: "#000000"

    VideoContainer{
        anchors.fill: parent
    }

    ToolBar {
        width: parent.width
        height: 45
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
