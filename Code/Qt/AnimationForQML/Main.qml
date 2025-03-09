import QtQuick
import "qrc:/qml"
import "qrc:/animation"

Window { 
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Image {
        property bool run: false

        id: image
        width: 100
        height: 100
        source: "qrc:/image/circle.png"

        MouseArea {
            anchors.fill: image
            onClicked: image.run = !image.run
        }
    }

    Rectangle {
        id: box
        width: 100
        height: 100
        gradient: Gradient {
            GradientStop { position: 0.0; color: "red" }
            GradientStop { position: 1.0; color: Qt.lighter("blue", 1) }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: animals.restart()
        }
    }

    /*------动画设计------*/
    RotationAnimation {
        target: image
        properties: "rotation"
        to: 360
        duration: 3000
        running: image.run
    }

    NumberAnimation {
        target: image
        properties: "x"
        to: root.width - image.width
        duration: 3000
        running: image.run
    }

    OpacityAnimator {
        target: image
        from: 1
        to: 0
        duration: 3000
        running: image.run
    }

    // SequentialAnimation {  // 同步执行
    ParallelAnimation {    // 异步执行
        id: animals
        NumberAnimation {
            id: animal
            target: box
            property: "x"
            from: 0
            to: root.width - box.width
            duration: 2000
            easing.type: Easing.InSine
        }

        NumberAnimation {
            target: box
            property: "y"
            from: 0
            to: root.height - box.height
            duration: 2000
            easing.type: Easing.InSine
        }
    }
}
