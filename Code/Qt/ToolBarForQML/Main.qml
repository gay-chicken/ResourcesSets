import QtQuick
import QtQuick.Controls // Slider
Window {
    id: root
    width: 640
    height: 480
    visible: true

    Timer {
        id: timer
        interval: 2000
        onTriggered: {
            hideBar.start()
            timer.stop()
        }

        Component.onCompleted: timer.start()
    }

    Rectangle {
        id: toolbar
        width: parent.width
        height: 45
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        gradient: Gradient {
            GradientStop { position: 0.0; color: "darkGray" }
            GradientStop { position: 1.0; color: "gray" }
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onPositionChanged: {
            toolbar.height = 45
            timer.restart()
        }
    }

    NumberAnimation {
        id: hideBar
        target: toolbar
        property: "height"
        from: toolbar.height
        to: 0
        duration: 500
        easing.type: Easing.InCubic
    }
}
