import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Column {
        scale: 2.0
        anchors.centerIn: parent

        Image {
            id: image
            width: 200
            height: 200
            source: "qrc:/image/circle.png"
        }

        DelayButton {
            width: 100
            height: 40
            text: "loading"
            progress: image.progress
            onClicked: {

            }
        }
    }
}
