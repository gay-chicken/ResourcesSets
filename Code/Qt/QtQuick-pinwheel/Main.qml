import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Image {
        id: background
        source:
            "file:///D://Desktop//ResourcesSets//Code//Qt//QtQuick-pinwheel//background.png"
        anchors.fill: parent
        asynchronous: true

        Behavior on rotation {
            NumberAnimation {
                duration: 300
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: background.rotation += 90
    }
}
