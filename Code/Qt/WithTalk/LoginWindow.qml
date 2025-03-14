import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "qrc:/qml"

Window {
    property string nickname: "TN-mo"
    property string avatar: "qrc:/image/海绵宝宝.jpg"
    readonly property real dpi: 1

    id: root
    width: 278 * root.dpi
    height: 378 * root.dpi
    visible: true
    flags: Qt.Window | Qt.FramelessWindowHint | Qt.WindowDropShadowHint
    color: "transparent"

    /*界面背景*/
    Rectangle {
        id: background
        anchors.fill: parent
        radius: 3
        color: "#ffffff"
        border.color: "black"
        border.width: 1
    }

    /*标题栏*/
    Rectangle {
        id: toolbar
        width: parent.width
        height: 24 * root.dpi
        color: "transparent"
        anchors.top: root.top
        anchors.horizontalCenter: root.horizontalCenter

        Item {
            anchors.fill: parent

            DragHandler {
                grabPermissions: TapHandler.CanTakeOverFromAnything
                onActiveChanged: if (active) root.startSystemMove()
            }
        }

        Text {
            text: "WithTalk"
            color: "#aeaeb1"
            font.pixelSize: 12 * root.dpi
            anchors.left: toolbar.left
            anchors.verticalCenter: toolbar.verticalCenter
            anchors.leftMargin: 5
        }

        Row {
            width: 64 * root.dpi
            height: toolbar.height
            layoutDirection: Qt.RightToLeft
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: toolbar.right
            anchors.rightMargin: 0

            Rectangle {
                width: 32 * root.dpi
                height: toolbar.height
                radius: [0, 10, 0, 0] // FIX: 设置右上角为圆角失败

                Image {
                    width: 16
                    height: 16
                    source: "qrc:/image/close.png"
                    anchors.centerIn: parent
                }
                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: parent.color = "#fb7373"
                    onExited: parent.color = "white"
                    onClicked: Qt.quit()
                }
            }

            Rectangle {
                width: 32 * root.dpi
                height: toolbar.height

                Image {
                    width: 16
                    height: 16
                    source: "qrc:/image/setting.png"
                    anchors.centerIn: parent
                }
                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: parent.color = "#f3f3f3"
                    onExited: parent.color = "white"
                }
            }
        }
    }

    Rectangle {
        width: 80 * root.dpi
        height: 80 * root.dpi
        anchors.bottom: background.verticalCenter
        anchors.horizontalCenter: background.horizontalCenter

        color: "transparent"
        Image {
            id: avatar
            width: 80 * root.dpi
            height: 80 * root.dpi
            source: root.avatar
            anchors.bottom: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: nickname
            text: root.nickname
            anchors.top: avatar.bottom
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
        }
    }

    Rectangle {
        id: loginbutton
        width: 144 * root.dpi
        height: 36 * root.dpi
        color: "#07c160"
        radius: 5
        anchors.topMargin: 80 * root.dpi
        anchors.top: background.verticalCenter
        anchors.horizontalCenter: background.horizontalCenter

        Text {
            text: "登录"
            color: "white"
            font.pixelSize: 16
            anchors.centerIn: parent
        }

        MouseArea {
            hoverEnabled: true
            anchors.fill: parent
            onEntered: loginbutton.color = "#38cd7f"
            onExited: loginbutton.color = "#07c160"
            onClicked: console.log("login..")
        }
    }

}
