import QtQuick
import QtQuick.Controls

Page {
    title: "Profile"

    Column {
        spacing: 10
        anchors.centerIn: parent

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Profile Screen"
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "next page"
            onClicked: stackView.push("qrc:/qml/Profile.qml")
        }
    }


}
