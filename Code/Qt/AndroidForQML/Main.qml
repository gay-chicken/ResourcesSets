import QtQuick
import QtQuick.Controls
import "qrc:/qml"

ApplicationWindow {
    width: 1080 / 3
    height: 2340 / 3
    visible: true
/*
    header: ToolBar {
        ToolButton {
            // text: stackView.depth > 1 ? "\u25c0" : "\u2630"
            icon.source: stackView.depth > 1 ? "qrc:/image/back.png" : "qrc:/image/menu.png"
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Home {}
    }

    Component {
        id: aboutPage

        About {}
    }

    Drawer {
        id: drawer
        width: parent.width * 0.67
        height: parent.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                width: parent.width
                text: "Profile"
                onClicked: {
                    stackView.push("qrc:/qml/Profile.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                width: parent.width
                text: "About"
                onClicked: {
                    stackView.push(aboutPage)
                    drawer.close()
                }
            }
        }
    }
*/

    SwipeView {
        id: swipeView
        anchors.fill: parent

        Home {}
        About{}
        Profile{}
    }

    PageIndicator {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        currentIndex: swipeView.currentIndex
        count: swipeView.count
    }
}
