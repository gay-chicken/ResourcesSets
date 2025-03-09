import QtQuick
import QtQuick.Shapes

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Flow {
        spacing: 10

        Rectangle {
            width: 50
            height: 50
            radius: 10
            color: "red"
        }

    }
}
